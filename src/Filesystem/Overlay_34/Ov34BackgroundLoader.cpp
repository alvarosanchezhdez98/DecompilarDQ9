#include "Filesystem/Overlay_34/Ov34BackgroundLoader.h"
#include "Filesystem/GPC.h"
#include "Memory/AllocatorUnion.h"
#include "Resource/ResourceMutex.h"

#ifdef jpn
#define func_020a1a40 func_020a37b8
#define func_020a1ccc func_020a3a44
#endif

extern "C"
{
    // get crc for string
    unsigned int func_01ff860c(const char*);

    // alternate version of load overlay
    void func_020a1a40(int);
    // alternate unload overlay
    void func_020a1ccc(int);

    // Fills the buffer with 32 bytes that change all the time: timers, the display's line counter, the touch screen...
    // (OS_GetLowEntropyData in the NitroSDK)
    void func_020c9b10(unsigned int* buffer);
    // Allocates the size rounded up to a multiple of 4
    void* func_02012d88(AllocatorUnion* allocator, unsigned int size);

    extern AllocatorUnion data_02114e20;
}

static Ov34BackgroundLoader loaderInstance;

void PopulateOv34BackgroundLoader(void* fileLoadSpace, unsigned int capacity, int relativePrio)
{
    loaderInstance.Populate(fileLoadSpace, capacity, relativePrio);
}

int Ov34BackgroundLoader::Process()
{
    GPCFile* pGPC;
    LockResourceMutex();    
    ZeroInitGPCPointer(&pGPC);
    unsigned int currentArchiveCRC = 0;
    while (true)
    {
        flags_78c_0_ = true;
        // Begin by doing overlay load/unload operations
        Task* pTask = &queuedTasks_[0];
        for (int i = 0; i < numPendingTasks_; i++, pTask++)
        {
            switch (pTask->type_)
            {
            case TaskType_LoadOverlay:
            {
                pTask->status_ = TaskStatus_InFlight;
                UnlockResourceMutex();
                func_020a1a40(pTask->fileLengthOrOverlayID_);
                LockResourceMutex();
                pTask->status_ = TaskStatus_Complete;
                break;
            }
            case TaskType_UnloadOverlay:
            {
                pTask->status_ = TaskStatus_InFlight;
                UnlockResourceMutex();
                func_020a1ccc(pTask->fileLengthOrOverlayID_);
                LockResourceMutex();
                pTask->status_ = TaskStatus_Complete;
                break;
            }
            default:
                continue;
            }
            // If we get here, we actually did something, so remove the task
            // and shift things up
            Task* qTask = pTask;
            for (int j = i + 1; j < numPendingTasks_; j++, qTask++)
            {
                qTask[0] = qTask[1];
            }
            pTask--;
            numPendingTasks_--;
        }

        bool allCompleteTasksAreExternallyAllocated = true;
        if (rightmostAllocationByte_ != 0)
        {
            Task* pTask = &queuedTasks_[0];
            for (int i = 0; i < numPendingTasks_; i++, pTask++)
            {
                if (pTask->externalAllocator_ == NULL && pTask->status_ == TaskStatus_Complete)
                {
                    allCompleteTasksAreExternallyAllocated = false;
                    break;
                }
            }
        }
        if (allCompleteTasksAreExternallyAllocated)
            rightmostAllocationByte_ = 0;

        if (numPendingTasks_ <= 0)
            goto end;
        if (processLockBits_ != 0)
        {
            flags_78c_0_ = false;
            goto end;
        }

        Task* gpcTask = NULL;
        if (CheckGPCPairValid_020d917c(pGPC, reader_))
        {
            Task* qTask = &queuedTasks_[0];
            for (int j = 0; j < numPendingTasks_; j++, qTask++)
            {
                if (qTask->status_ == TaskStatus_Fence)
                {
                    flags_78c_0_ = false;
                    goto end;
                }
                else if (qTask->status_ == TaskStatus_Unallocated &&
                    qTask->type_ == TaskType_LoadFromGP2 &&
                    currentArchiveCRC == func_01ff860c(qTask->outerFilename_))
                {
                    flags_78c_0_ = false;
                    gpcTask = qTask;
                    break;
                }
            }
        }

        if (gpcTask == NULL)
        {
            // Unlike overlay 33, it's reset without checking first
            ResetGPCPair(&pGPC, reader_);
            currentArchiveCRC = 0;
            scratchRightArenaUsage_ = 0;
            flagMaybeGP2OperationInFlight_ = false;
            Task* qTask = &queuedTasks_[0];
            for (int j = 0; j < numPendingTasks_; j++, qTask++)
            {
                if (qTask->status_ == TaskStatus_Fence)
                {
                    flags_78c_0_ = false;
                    goto end;
                }
                else if (qTask->status_ == TaskStatus_Unallocated)
                {
                    flags_78c_0_ = false;
                    gpcTask = qTask;
                    break;
                }
            }
        }

        if (gpcTask == NULL)
            goto end;

        gpcTask->status_ = TaskStatus_InFlight;
        Task inFlightTask;
        inFlightTask = *gpcTask; // work with a copy, we'll copy changes back at the end
        flags_78c_3_ = true;
        UnlockResourceMutex();
        char fullName[80];
        inFlightTask.GetFullFilename(fullName);
        inFlightTask.pFileData = NULL;
        inFlightTask.fileLengthOrOverlayID_ = 0;
        switch (inFlightTask.type_)
        {
        case TaskType_LoadFileDefault:
        case TaskType_LoadGP1:
        {
            reader_.ZeroInitialize();
            if (!reader_.Open(fullName, false))
                inFlightTask.status_ = TaskStatus_LoadFileFailed;
            else
            {
                if (inFlightTask.type_ == TaskType_LoadFileDefault)
                    inFlightTask.fileLengthOrOverlayID_ = reader_.GetFileSize();
                else
                {
                    CompressionPrefix prefix;
                    *(unsigned int*)&prefix = 0;
                    reader_.Read(&prefix, 4);
                    inFlightTask.fileLengthOrOverlayID_ = prefix.GetDecompressedLength();
                    reader_.Seek(0);
                }
                unsigned int allocSize;
                if (inFlightTask.type_ == TaskType_LoadFileDefault)
                    allocSize = inFlightTask.fileLengthOrOverlayID_;
                else
                    allocSize = (inFlightTask.fileLengthOrOverlayID_ + 7) & ~3;

                if (inFlightTask.externalAllocator_ != NULL)
                {
                    inFlightTask.pFileData = inFlightTask.externalAllocator_->Allocate(allocSize);
                    if (inFlightTask.pFileData == NULL)
                        inFlightTask.status_ = TaskStatus_Unallocated;
                }
                else
                {
                    inFlightTask.pFileData = AllocateInScratchSpace(&inFlightTask.scratchAlloc_, allocSize);
                    if (inFlightTask.pFileData == NULL)
                        inFlightTask.status_ = TaskStatus_Unallocated;
                }

                if (inFlightTask.pFileData != NULL && inFlightTask.status_ == TaskStatus_InFlight)
                {
                    if (inFlightTask.type_ == TaskType_LoadFileDefault)
                    {
                        reader_.Read(inFlightTask.pFileData, inFlightTask.fileLengthOrOverlayID_);
                    }
                    else // TaskType_LoadGP1
                    {
                        unsigned int compressedSize = reader_.GetFileSize();
                        reader_.DecompressBytes(inFlightTask.pFileData, inFlightTask.fileLengthOrOverlayID_,
                            compressedSize, allocSize);
                    }
                }
                else
                {
                    FreeScratchSpace(&inFlightTask.scratchAlloc_);
                    inFlightTask.fileLengthOrOverlayID_ = 0;
                }
                reader_.Close();
            }
            break;
        }
        case TaskType_LoadFromGP2:
        {
            flagMaybeGP2OperationInFlight_ = true;
            GPCFile::Header header;
            unsigned int outBufferRightMinusLeft = scratchSpaceSize_ - rightmostAllocationByte_ - scratchRightArenaUsage_;
            // this looks like the start of the buffer but we right-align the output so really
            // it's the end (we're not allowed to go any further left than this).
            // This coincides with the right endpoint of file data loaded into allocations
            // of the scratch space.
            unsigned char* outputBufferLeft = (unsigned char*)scratchSpace_ + rightmostAllocationByte_;
            unsigned int outLength = 0;
            bool outSuccess = false;
            if (!CheckGPCPairValid_020d917c(pGPC, reader_) &&
                !LoadAndDecompressGPCHeaderAndInnerFileInfo(&pGPC, reader_, fullName, outputBufferLeft,
                    outLength, outBufferRightMinusLeft, true, &outSuccess))
            {
                flagMaybeGP2OperationInFlight_ = false;
                if (outSuccess)
                    inFlightTask.status_ = TaskStatus_Unallocated;
                else
                    inFlightTask.status_ = TaskStatus_LoadFileFailed;
            }
            else
            {
                currentArchiveCRC = func_01ff860c(inFlightTask.outerFilename_);
                // note that prior to this instruction, one of these is always zero:
                // if the previous iteration handled this archive, then we didn't reload
                // it (short-circuit && in the if-statement above) so outLength = 0,
                // and if we handled a different archive / null, then it's been reset
                // since and arena usage set back to zero.
                scratchRightArenaUsage_ += outLength;
                unsigned int innerFileLength = GetGPCInnerFileLengthByName(pGPC, reader_, inFlightTask.innerFilename_);
                unsigned int allocSize = (innerFileLength + 7) & ~3;
                if (inFlightTask.externalAllocator_ != NULL)
                {
                    inFlightTask.pFileData = inFlightTask.externalAllocator_->Allocate(allocSize);
                    if (inFlightTask.pFileData == NULL)
                        inFlightTask.status_ = TaskStatus_Unallocated;
                    else
                    {
                        if (!DecompressFileFromGPCByName(pGPC, reader_, inFlightTask.pFileData, inFlightTask.fileLengthOrOverlayID_, allocSize, inFlightTask.innerFilename_))
                        {
                            inFlightTask.externalAllocator_->Free(inFlightTask.pFileData);
                            inFlightTask.pFileData = NULL;
                            inFlightTask.fileLengthOrOverlayID_ = 0;
                            inFlightTask.status_ = TaskStatus_DecompressionFailed;
                        }
                    }
                }
                else
                {
                    inFlightTask.pFileData = AllocateInScratchSpace(&inFlightTask.scratchAlloc_, allocSize);
                    if (inFlightTask.pFileData == NULL)
                        inFlightTask.status_ = TaskStatus_Unallocated;
                    else
                    {
                        if (!DecompressFileFromGPCByName(pGPC, reader_, inFlightTask.pFileData, inFlightTask.fileLengthOrOverlayID_, allocSize, inFlightTask.innerFilename_))
                        {
                            FreeScratchSpace(&inFlightTask.scratchAlloc_);
                            inFlightTask.pFileData = NULL;
                            inFlightTask.fileLengthOrOverlayID_ = 0;
                            inFlightTask.status_ = TaskStatus_DecompressionFailed;
                        }
                    }
                }
            }
            break; // switch statement
        }
        }
        if (inFlightTask.pFileData != NULL)
        {
            inFlightTask.status_ = TaskStatus_Complete;

            // What sets this overlay apart: after one in four files, on average, it allocates 8 bytes that are never
            // freed. Main loads this overlay instead of overlay 33 from the functions that it passes to the checks in
            // overlay 29, so it's likely an anti-piracy measure that makes the game run out of memory over time.
            unsigned int entropy[8];
            func_020c9b10(entropy);
            unsigned int bits = entropy[0] ^ entropy[1] ^ entropy[2] ^ entropy[3] ^ entropy[4] ^ entropy[5] ^
                entropy[6] ^ entropy[7];
            unsigned char byte = (bits >> 24) ^ (bits >> 16) ^ (bits >> 8) ^ bits;
            unsigned char pair = ((byte >> 6) ^ (byte >> 4) ^ (byte >> 2) ^ byte) & 3;
            if (pair == 0)
                func_02012d88(&data_02114e20, 8);
        }

        LockResourceMutex();
        flags_78c_3_ = false;
        RefreshCounters();
        Task* pTaskToUpdate = NULL;
        Task* qTask = &queuedTasks_[0];
        for (int i = 0; i < numPendingTasks_; i++, qTask++)
        {
            if (qTask->taskID_ != inFlightTask.taskID_)
                continue;

            if (qTask->status_ == TaskStatus_InFlight)
                pTaskToUpdate = qTask;
            break;
        }

        if (pTaskToUpdate != NULL)
        {
            *pTaskToUpdate = inFlightTask;
        }
        else
        {
            FreeScratchSpace(&inFlightTask.scratchAlloc_);
            if (inFlightTask.status_ == TaskStatus_Complete && inFlightTask.externalAllocator_ != NULL)
                inFlightTask.externalAllocator_->Free(inFlightTask.pFileData);
            if (CheckGPCPairValid_020d917c(pGPC, reader_))
            {
                ResetGPCPair(&pGPC, reader_);
                currentArchiveCRC = 0;
                scratchRightArenaUsage_ = 0;
                flagMaybeGP2OperationInFlight_ = false;
            }
        }

        inFlightTask.ZeroInitialize();
    }

end:
    UnlockResourceMutex();
    ResetGPCPair(&pGPC, reader_);
    scratchRightArenaUsage_ = 0;
    flagMaybeGP2OperationInFlight_ = false;
    if (numPendingTasks_ <= 0)
        SleepIfResourceMutexNotLocked(5);
    ZeroDestroyGPCPointer(&pGPC);
    return 0;
}

Ov34BackgroundLoader::Ov34BackgroundLoader()
{
}
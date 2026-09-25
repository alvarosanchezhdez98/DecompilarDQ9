#include "MultiBoot/MultiBoot.h"
#include "System/Memory.h"
#include <globaldefs.h>

// The NitroSDK's MB library: the children's requests, which arrive in pieces, and the headers of the blocks that the
// parent sends

#pragma optimize_for_size off
#pragma optimization_level 4

// MB_MAX_CHILD
#define MAX_CHILDREN 15
#define REQUEST_SIZE MB_COMM_REQ_DATA_SIZE

// The requests of the children, as they arrive
struct MBiRequestBuffer
{
    unsigned char data[MAX_CHILDREN][0x20];
    // The pieces that have arrived, a bit each
    unsigned long bits[MAX_CHILDREN];
};

static struct
{
    int unk_0;
    MBiRequestBuffer* buffer;
    // The size of a piece
    int pieceSize;
    int pieces;
    int size;
    char unk_14[8];
} sRequests;

extern "C"
{
    int IsGetAllRequestData(unsigned short aid);
    void* MBi_ReceiveRequestDataPiece(const MBCommChildBlockHeader* header, unsigned short aid);

    void MBi_SetChildMPMaxSize(unsigned short childSize)
    {
        sRequests.pieceSize = childSize - 2;
        sRequests.pieces = REQUEST_SIZE / sRequests.pieceSize;
        sRequests.size = REQUEST_SIZE;
    }

    void MBi_SetParentPieceBuffer(MBiRequestBuffer* buffer)
    {
        sRequests.buffer = buffer;
        VectorizedMemset(buffer, 0, sizeof(*buffer));
    }

    void MBi_ClearParentPieceBuffer(unsigned short aid)
    {
        if (sRequests.buffer == NULL)
            return;
        int child = aid - 1;
        VectorizedMemset(sRequests.buffer->data[child], 0, REQUEST_SIZE);
        sRequests.buffer->bits[child] = 0;
    }

    unsigned char* MBi_MakeParentSendBuffer(const MBCommParentBlockHeader* header, unsigned char* sendBuffer)
    {
        unsigned char* ptr = sendBuffer;
        *ptr++ = header->type;
        switch (header->type)
        {
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
            break;
        case 4:
            ptr[0] = (unsigned char)header->fid;
            ptr[1] = (unsigned char)((header->fid & 0xff00) >> 8);
            ptr[2] = (unsigned char)header->seqno;
            ptr[3] = (unsigned char)((header->seqno & 0xff00) >> 8);
            ptr += 4;
            break;
        case 0:
        default:
            return NULL;
        }
        return ptr;
    }

    void* MBi_SetRecvBufferFromChild(const unsigned char* recvBuffer, MBCommChildBlockHeader* header,
                                     unsigned short aid)
    {
        const unsigned char* ptr = recvBuffer;
        header->type = *ptr++;
        switch (header->type)
        {
        case 7:
            if (IsGetAllRequestData(aid))
                return sRequests.buffer->data[aid - 1];
            header->req_data.piece = *ptr++;
            if (header->req_data.piece > sRequests.pieces)
                return NULL;
            VectorizedInvertedMemcpy(ptr, header->req_data.data, sRequests.pieceSize);
            ptr = (const unsigned char*)MBi_ReceiveRequestDataPiece(header, aid);
            break;
        case 8:
            header->data.req = *ptr++;
            header->data.req |= (*ptr++ << 8) & 0xff00;
            break;
        case 9:
            header->data.req = *ptr++;
            header->data.req |= (*ptr++ << 8) & 0xff00;
            VectorizedInvertedMemcpy(ptr, header->data.data, sRequests.pieceSize);
            ptr += sRequests.pieceSize;
            break;
        default:
            return NULL;
        }
        return (void*)ptr;
    }

    void* MBi_ReceiveRequestDataPiece(const MBCommChildBlockHeader* header, unsigned short aid)
    {
        if (sRequests.buffer == NULL)
            return NULL;
        unsigned char piece = header->req_data.piece;
        if (piece > sRequests.pieces)
            return NULL;
        int child = aid - 1;
        VectorizedInvertedMemcpy(header->req_data.data,
                                 &sRequests.buffer->data[child][piece * sRequests.pieceSize], sRequests.pieceSize);
        sRequests.buffer->bits[child] |= 1 << piece;
        if (!IsGetAllRequestData(aid))
            return NULL;
        return sRequests.buffer->data[child];
    }

    int IsGetAllRequestData(unsigned short aid)
    {
        for (unsigned short i = 0; i < sRequests.pieces; i++)
        {
            if (!(sRequests.buffer->bits[aid - 1] & (1 << i)))
                return false;
        }
        return true;
    }
}

#include "Graphics/NSBXX/RenderCommands_Common.h"

#pragma optimize_for_size off
// This NitroSystem file was compiled with -O4, like NameList.cpp: at the game's -O2, the loop is compiled differently
#pragma optimization_level 4

static inline int BitVecCheck(const unsigned int* vec, unsigned int index)
{
    return vec[index >> 5] & (1 << (index & 0x1f));
}

static inline void BitVecSet(unsigned int* vec, unsigned int index)
{
    vec[index >> 5] |= 1 << (index & 0x1f);
}

// NitroSystem's NNSi_G3dFuncSbc_NODEMIX: loads the weighted sum of the matrices of several joints, for skinning.
// There is no callback in this command.
void RenderCommand_9(RenderCommandHandler* handler, int modifier)
{
    // 64-bit, so the products below are 64-bit multiplications
    int64_t weight = 0;
    NSBXXInternalModel* model = handler->modelContext_->internalModel_;
    const NSBXXInvBindMatrix* invBindMatrices = (const NSBXXInvBindMatrix*)((intptr_t)model + model->inverseBindsOffset_);
    unsigned int numTerms = handler->instructionPointer_[2];
    uint8_t* term = handler->instructionPointer_ + 3; // each term is the matrix stack index, the joint and the weight

    {
        unsigned int i;
        NSBXXInvBindMatrix sum;
        Matrix4x4* clipMatrix;
        Matrix3x3* vectorMatrix;

        func_020ca458(0, &sum, sizeof(sum));
        SendQueuedDataToGeometryFifo();

        GXFIFO_MATRIX_MODE = 0; // projection
        GXFIFO_MATRIX_STORE = 1;
        GXFIFO_MATRIX_IDENTITY = 0;
        GXFIFO_MATRIX_MODE = 2; // position+vector

        for (i = 0; i < numTerms; ++i)
        {
            unsigned int joint = term[1];
            int cached = BitVecCheck(handler->invBindBitfield_, joint);

            // The cache has to be accessed as a member of a global struct: the compiler then computes the addresses
            // of both matrices from the cache's symbol, instead of the second from the first
            clipMatrix = &data_0210b078.envelopeMatrixCache[joint].mat4x4;
            if (!cached)
            {
                BitVecSet(handler->invBindBitfield_, joint);
                // retrieve the local-to-world matrix from the stack
                GXFIFO_MATRIX_GET = term[0];
                GXFIFO_MATRIX_MODE = 1; // position
                func_020c51a4(invBindMatrices[joint].mat4x3.entries);
            }

            // The vector matrix of the previous term is added here, while the geometry engine computes this one's
            if (i != 0)
            {
                sum.mat3x3.entries[0] += (weight * vectorMatrix->entries[0]) >> 12;
                sum.mat3x3.entries[1] += (weight * vectorMatrix->entries[1]) >> 12;
                sum.mat3x3.entries[2] += (weight * vectorMatrix->entries[2]) >> 12;
                sum.mat3x3.entries[3] += (weight * vectorMatrix->entries[3]) >> 12;
                sum.mat3x3.entries[4] += (weight * vectorMatrix->entries[4]) >> 12;
                sum.mat3x3.entries[5] += (weight * vectorMatrix->entries[5]) >> 12;
                sum.mat3x3.entries[6] += (weight * vectorMatrix->entries[6]) >> 12;
                sum.mat3x3.entries[7] += (weight * vectorMatrix->entries[7]) >> 12;
                sum.mat3x3.entries[8] += (weight * vectorMatrix->entries[8]) >> 12;
            }

            if (!cached)
            {
                while (func_020c54fc(clipMatrix)) {}
                GXFIFO_MATRIX_MODE = 2; // position+vector
                func_020c51c0(invBindMatrices[joint].mat3x3.entries);
            }

            weight = term[2] << 4; // as int -> fixed point this is division by 256
            sum.mat4x3.entries[0] += (weight * clipMatrix->entries[0]) >> 12;
            sum.mat4x3.entries[1] += (weight * clipMatrix->entries[1]) >> 12;
            sum.mat4x3.entries[2] += (weight * clipMatrix->entries[2]) >> 12;
            sum.mat4x3.entries[3] += (weight * clipMatrix->entries[4]) >> 12;
            sum.mat4x3.entries[4] += (weight * clipMatrix->entries[5]) >> 12;
            sum.mat4x3.entries[5] += (weight * clipMatrix->entries[6]) >> 12;
            sum.mat4x3.entries[6] += (weight * clipMatrix->entries[8]) >> 12;
            sum.mat4x3.entries[7] += (weight * clipMatrix->entries[9]) >> 12;
            sum.mat4x3.entries[8] += (weight * clipMatrix->entries[10]) >> 12;
            sum.mat4x3.entries[9] += (weight * clipMatrix->entries[12]) >> 12;
            sum.mat4x3.entries[10] += (weight * clipMatrix->entries[13]) >> 12;
            sum.mat4x3.entries[11] += (weight * clipMatrix->entries[14]) >> 12;
            term += 3;

            vectorMatrix = &data_0210b078.envelopeMatrixCache[joint].mat3x3;
            if (!cached)
            {
                while (func_020c552c(vectorMatrix)) {}
            }
        }
        sum.mat3x3.entries[0] += (weight * vectorMatrix->entries[0]) >> 12;
        sum.mat3x3.entries[1] += (weight * vectorMatrix->entries[1]) >> 12;
        sum.mat3x3.entries[2] += (weight * vectorMatrix->entries[2]) >> 12;
        sum.mat3x3.entries[3] += (weight * vectorMatrix->entries[3]) >> 12;
        sum.mat3x3.entries[4] += (weight * vectorMatrix->entries[4]) >> 12;
        sum.mat3x3.entries[5] += (weight * vectorMatrix->entries[5]) >> 12;
        sum.mat3x3.entries[6] += (weight * vectorMatrix->entries[6]) >> 12;
        sum.mat3x3.entries[7] += (weight * vectorMatrix->entries[7]) >> 12;
        sum.mat3x3.entries[8] += (weight * vectorMatrix->entries[8]) >> 12;

        // Loaded as a 4x3 matrix, like in NitroSystem: the vector matrix ignores the translation, which is what follows
        // sum on the stack, and the position matrix is replaced next
        func_020c5188(sum.mat3x3.entries);
        GXFIFO_MATRIX_MODE = 1; // position
        func_020c5188(sum.mat4x3.entries);
        GXFIFO_MATRIX_MODE = 0; // projection
        GXFIFO_MATRIX_GET = 1;
        GXFIFO_MATRIX_MODE = 2; // position+vector
    }
    GXFIFO_MATRIX_STORE = handler->instructionPointer_[1];
    handler->instructionPointer_ += 3 + handler->instructionPointer_[2] * 3;
}

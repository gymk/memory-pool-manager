#include <iostream>

#include "bufferpool.h"


using namespace simple_buffer_manager;

typedef struct tagRequiredBuffer
{
    unsigned char   m_aui8Buffer[0x1000];
} Buffer;

int main()
{
    CFixedSizeBufferPool<Buffer> tst(20);
}
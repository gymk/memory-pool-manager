#include <iostream>

#include "bufferpool.h"

#define MAX_BUFFERS     10

using namespace simple_buffer_manager;

typedef struct tagRequiredBuffer
{
    unsigned char   m_aui8Buffer[0x1000];
} Buffer;

int main()
{
    CFixedSizeBufferPool<Buffer> tst(MAX_BUFFERS);

    Buffer * pTst[MAX_BUFFERS];
    Buffer * pTst2;

    for(int i = 0; i < MAX_BUFFERS; i++)
    {
        pTst[i] = tst.GetBuffer();
        if(pTst)
            std::cout << "Received buffer " << pTst[i] << std::endl;
        else
            std::cout << "No more buffer available" << std::endl;
    }

    pTst2 = tst.GetBuffer();
    if(pTst)
        std::cout << "Received buffer " << pTst2 << std::endl;
    else
        std::cout << "No more buffer available" << std::endl;

    for(int i = 0; i <= MAX_BUFFERS; i++)
    {
        tst.ReleaseBuffer(pTst[i]);
    }
}

/*
Output:

shin@shin-Samsung-DeskTop-System:~/data/Study/memory-pool-manager/v1$ ./a.out
[bufferpool.h:simple_buffer_manager::CFixedSizeBufferPool<T>::CFixedSizeBufferPool(int) [with T = tagRequiredBuffer]:Enter]
[bufferpool.h:void simple_buffer_manager::CFixedSizeBufferPool<T>::InitBufferPool() [with T = tagRequiredBuffer]:Enter]
[bufferpool.h:void simple_buffer_manager::CFixedSizeBufferPool<T>::InitBufferPool() [with T = tagRequiredBuffer]:Exit]
[bufferpool.h:simple_buffer_manager::CFixedSizeBufferPool<T>::CFixedSizeBufferPool(int) [with T = tagRequiredBuffer]:Exit]
Received buffer 0x1321110
Received buffer 0x1322111
Received buffer 0x1323112
Received buffer 0x1324113
Received buffer 0x1325114
Received buffer 0x1326115
Received buffer 0x1327116
Received buffer 0x1328117
Received buffer 0x1329118
Received buffer 0x132a119
Received buffer 0
[bufferpool.h:simple_buffer_manager::CFixedSizeBufferPool<T>::~CFixedSizeBufferPool() [with T = tagRequiredBuffer]:Enter]
[bufferpool.h:void simple_buffer_manager::CFixedSizeBufferPool<T>::DestroyBufferPool() [with T = tagRequiredBuffer]:Enter]
[bufferpool.h:void simple_buffer_manager::CFixedSizeBufferPool<T>::DestroyBufferPool() [with T = tagRequiredBuffer]:Exit]
[bufferpool.h:simple_buffer_manager::CFixedSizeBufferPool<T>::~CFixedSizeBufferPool() [with T = tagRequiredBuffer]:Exit]
*/
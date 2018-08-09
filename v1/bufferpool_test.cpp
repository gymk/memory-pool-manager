#include <iostream>

#include "bufferpool.h"

#define MAX_BUFFERS     5

using namespace simple_buffer_manager;

typedef struct tagRequiredBuffer
{
    unsigned char   m_aui8Buffer[0x1000];
} Buffer;

int main()
{
    CFixedSizeBufferPool<Buffer> tst(MAX_BUFFERS);

    std::cout << "Avaialble " << tst.GetAvaiilableCount() << " Consumed " << tst.GetConsumedCount() << std::endl;

    Buffer * pTst[MAX_BUFFERS];
    Buffer * pTst2;

    for(int i = 0; i < MAX_BUFFERS; i++)
    {
        pTst[i] = tst.GetBuffer();
        if(pTst)
            std::cout << "Received buffer " << static_cast<void*>(pTst[i]) << " Avaialble " << tst.GetAvaiilableCount() << " Consumed " << tst.GetConsumedCount() << std::endl;
        else
            std::cout << "No more buffer available. Available " << tst.GetAvaiilableCount() << " Consumed " << tst.GetConsumedCount() << std::endl;
    }

    pTst2 = tst.GetBuffer();
    if(pTst2)
        std::cout << "Received buffer " << pTst2 << tst.GetAvaiilableCount() << " Consumed " << tst.GetConsumedCount() << std::endl;
    else
        std::cout << "No more buffer available. Available " << tst.GetAvaiilableCount() << " Consumed " << tst.GetConsumedCount() << std::endl;

    for(int i = 0; i <= MAX_BUFFERS; i++)
    {
        std::cout << "Avaialble " << tst.GetAvaiilableCount() << " Consumed " << tst.GetConsumedCount() << std::endl;
        tst.ReleaseBuffer(pTst[i]);
    }
    std::cout << "Avaialble " << tst.GetAvaiilableCount() << " Consumed " << tst.GetConsumedCount() << std::endl;
}

/*
Output:

[bufferpool.h:simple_buffer_manager::CFixedSizeBufferPool<T>::CFixedSizeBufferPool(int) [with T = tagRequiredBuffer]:Enter]
[bufferpool.h:void simple_buffer_manager::CFixedSizeBufferPool<T>::InitBufferPool() [with T = tagRequiredBuffer]:Enter]
[bufferpool.h:void simple_buffer_manager::CFixedSizeBufferPool<T>::InitBufferPool() [with T = tagRequiredBuffer]:Exit]
[bufferpool.h:simple_buffer_manager::CFixedSizeBufferPool<T>::CFixedSizeBufferPool(int) [with T = tagRequiredBuffer]:Exit]
Avaialble 5 Consumed 0
Received buffer 0xa1e110 Avaialble 4 Consumed 1
Received buffer 0xa1f111 Avaialble 3 Consumed 2
Received buffer 0xa20112 Avaialble 2 Consumed 3
Received buffer 0xa21113 Avaialble 1 Consumed 4
Received buffer 0xa22114 Avaialble 0 Consumed 5
No more buffer available. Available 0 Consumed 5
Avaialble 0 Consumed 5
Avaialble 1 Consumed 4
Avaialble 2 Consumed 3
Avaialble 3 Consumed 2
Avaialble 4 Consumed 1
Avaialble 5 Consumed 0
Avaialble 5 Consumed 0
[bufferpool.h:simple_buffer_manager::CFixedSizeBufferPool<T>::~CFixedSizeBufferPool() [with T = tagRequiredBuffer]:Enter]
[bufferpool.h:void simple_buffer_manager::CFixedSizeBufferPool<T>::DestroyBufferPool() [with T = tagRequiredBuffer]:Enter]
[bufferpool.h:void simple_buffer_manager::CFixedSizeBufferPool<T>::DestroyBufferPool() [with T = tagRequiredBuffer]:Exit]
[bufferpool.h:simple_buffer_manager::CFixedSizeBufferPool<T>::~CFixedSizeBufferPool() [with T = tagRequiredBuffer]:Exit]

*/
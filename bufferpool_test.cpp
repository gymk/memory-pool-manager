/*
g++ bufferpool_test.cpp -std=c++11

g++ -v
Using built-in specs.
COLLECT_GCC=g++
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/5/lto-wrapper
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 5.4.0-6ubuntu1~16.04.10' --with-bugurl=file:///usr/share/doc/gcc-5/README.Bugs --enable-languages=c,ada,c++,java,go,d,fortran,objc,obj-c++ --prefix=/usr --program-suffix=-5 --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --with-sysroot=/ --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-vtable-verify --enable-libmpx --enable-plugin --with-system-zlib --disable-browser-plugin --enable-java-awt=gtk --enable-gtk-cairo --with-java-home=/usr/lib/jvm/java-1.5.0-gcj-5-amd64/jre --enable-java-home --with-jvm-root-dir=/usr/lib/jvm/java-1.5.0-gcj-5-amd64 --with-jvm-jar-dir=/usr/lib/jvm-exports/java-1.5.0-gcj-5-amd64 --with-arch-directory=amd64 --with-ecj-jar=/usr/share/java/eclipse-ecj.jar --enable-objc-gc --enable-multiarch --disable-werror --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix
gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.10)
*/

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

    // Check whether able to get all the buffers
    for(int i = 0; i < MAX_BUFFERS; i++)
    {
        pTst[i] = tst.GetBuffer();
        if(pTst)
            std::cout << "Received buffer " << static_cast<void*>(pTst[i]) << " Avaialble " << tst.GetAvaiilableCount() << " Consumed " << tst.GetConsumedCount() << std::endl;
        else
            std::cout << "No more buffer available. Available " << tst.GetAvaiilableCount() << " Consumed " << tst.GetConsumedCount() << std::endl;
    }

    // Check what happens when no more buffer available
    pTst2 = tst.GetBuffer();
    if(pTst2)
        std::cout << "Received buffer " << pTst2 << tst.GetAvaiilableCount() << " Consumed " << tst.GetConsumedCount() << std::endl;
    else
        std::cout << "No more buffer available. Available " << tst.GetAvaiilableCount() << " Consumed " << tst.GetConsumedCount() << std::endl;

    // Check count after releasing each buffer
    for(int i = 0; i <= MAX_BUFFERS; i++)
    {
        std::cout << "Avaialble " << tst.GetAvaiilableCount() << " Consumed " << tst.GetConsumedCount() << std::endl;
        tst.ReleaseBuffer(pTst[i]);
    }
    std::cout << "Avaialble " << tst.GetAvaiilableCount() << " Consumed " << tst.GetConsumedCount() << std::endl;
    
    // Check whether trying to release the released buffer cause any side-effect ???
    tst.ReleaseBuffer(pTst[0]);
    
    std::cout << "Avaialble " << tst.GetAvaiilableCount() << " Consumed " << tst.GetConsumedCount() << std::endl;
}

/*
Output:

[bufferpool.h:simple_buffer_manager::CFixedSizeBufferPool<T>::CFixedSizeBufferPool(int) [with T = tagRequiredBuffer]:Enter]
[bufferpool.h:void simple_buffer_manager::CFixedSizeBufferPool<T>::InitBufferPool() [with T = tagRequiredBuffer]:Enter]
[bufferpool.h:void simple_buffer_manager::CFixedSizeBufferPool<T>::InitBufferPool() [with T = tagRequiredBuffer]:Exit]
[bufferpool.h:simple_buffer_manager::CFixedSizeBufferPool<T>::CFixedSizeBufferPool(int) [with T = tagRequiredBuffer]:Exit]
Avaialble 5 Consumed 0
Received buffer 0x24ae110 Avaialble 4 Consumed 1
Received buffer 0x24af111 Avaialble 3 Consumed 2
Received buffer 0x24b0112 Avaialble 2 Consumed 3
Received buffer 0x24b1113 Avaialble 1 Consumed 4
Received buffer 0x24b2114 Avaialble 0 Consumed 5
No more buffer available. Available 0 Consumed 5
Avaialble 0 Consumed 5
Avaialble 1 Consumed 4
Avaialble 2 Consumed 3
Avaialble 3 Consumed 2
Avaialble 4 Consumed 1
Avaialble 5 Consumed 0
Avaialble 5 Consumed 0
Avaialble 5 Consumed 0
[bufferpool.h:simple_buffer_manager::CFixedSizeBufferPool<T>::~CFixedSizeBufferPool() [with T = tagRequiredBuffer]:Enter]
[bufferpool.h:void simple_buffer_manager::CFixedSizeBufferPool<T>::DestroyBufferPool() [with T = tagRequiredBuffer]:Enter]
[bufferpool.h:void simple_buffer_manager::CFixedSizeBufferPool<T>::DestroyBufferPool() [with T = tagRequiredBuffer]:Exit]
[bufferpool.h:simple_buffer_manager::CFixedSizeBufferPool<T>::~CFixedSizeBufferPool() [with T = tagRequiredBuffer]:Exit]

*/
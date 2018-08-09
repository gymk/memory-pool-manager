#ifndef __BUFFER_POOL_MANAGER_H__
    #define __BUFFER_POOL_MANAGER_H__

//#define ENABLE_CUSTOM_NEW_DELETE_OVERRIDE

#include <memory>
#include <mutex>
#include "custom_alloc.h"
#include "scopelog.h"
#include "timemeasure.h"

/*
* Requires C++11
*/

namespace simple_buffer_manager
{

template <typename T>
class CFixedSizeBufferPool
{
    typedef struct tagPoolBuffer
    {
        T       m_buffer;
        bool    m_inUse;
    } POOL_BUFFER;
public:
    explicit CFixedSizeBufferPool(int i32MaxBuffers):_i32MaxBuffers{i32MaxBuffers}
    { LOG_CALL;
        InitBufferPool();
    }
    ~CFixedSizeBufferPool()
    { LOG_CALL;
        DestroyBufferPool();
    }

    // Provides a buffer from the pool if available
    // otherwise returns nullptr
    T* GetBuffer(void)
    {
        std::unique_lock<std::mutex> lc(_lock);

        if(nullptr != _pstBuffers)
        {
            for(int i = 0; i < _i32MaxBuffers; i++)
            {
                if(_pstBuffers[i].m_inUse == false)
                {
                    _pstBuffers[i].m_inUse = true;
                    return &_pstBuffers[i].m_buffer;
                }
            }
        }
        return nullptr;
    }

    // release the buffer back to the memory pool
    void ReleaseBuffer(T * pBufferToRelease)
    {
        std::unique_lock<std::mutex> lc(_lock);

        if(nullptr != _pstBuffers)
        {
            for(int i = 0; i < _i32MaxBuffers; i++)
            {
                if(&_pstBuffers[i].m_buffer == pBufferToRelease)
                {
                    _pstBuffers[i].m_inUse = false;
                    break;
                }
            }
        }
    }

private:
    void InitBufferPool(void)
    { LOG_CALL;
        std::unique_lock<std::mutex> lc(_lock);
        
        _pstBuffers.reset(new POOL_BUFFER[_i32MaxBuffers]);
        if(nullptr != _pstBuffers)
        {
            for(int i = 0; i < _i32MaxBuffers; i++)
            {
                _pstBuffers[i].m_inUse = false;
            }
        }
    }

    void DestroyBufferPool(void)
    { LOG_CALL;
        _pstBuffers.reset(nullptr);
    }

private:
    int                     _i32MaxBuffers;
    std::unique_ptr<POOL_BUFFER[]> _pstBuffers;
    std::mutex              _lock;
};

} // namespace simple_buffer_manager

#endif /* !__BUFFER_POOL_MANAGER_H__ */
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
                    ++_i32ConsumedCount;
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
                if( _pstBuffers[i].m_inUse && (&_pstBuffers[i].m_buffer == pBufferToRelease))
                {
                    --_i32ConsumedCount;
                    _pstBuffers[i].m_inUse = false;
                    break;
                }
            }
        }
    }

    int GetConsumedCount(void)
    {
        return _i32ConsumedCount;
    }
    int GetAvaiilableCount(void)
    {
        return (_i32MaxBuffers - _i32ConsumedCount);
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
        _i32ConsumedCount = 0;
    }

    void DestroyBufferPool(void)
    { LOG_CALL;
        _pstBuffers.reset(nullptr);
    }

private:
    // Disable Copy Constructor
    CFixedSizeBufferPool(const CFixedSizeBufferPool &) = delete;
    // Disable assignment operator
    CFixedSizeBufferPool & operator= (const CFixedSizeBufferPool &) = delete;

private:
    int                     _i32MaxBuffers;
    int                     _i32ConsumedCount;
    std::unique_ptr<POOL_BUFFER[]> _pstBuffers;
    std::mutex              _lock;
};

} // namespace simple_buffer_manager

#endif /* !__BUFFER_POOL_MANAGER_H__ */
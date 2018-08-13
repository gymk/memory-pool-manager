// V2

#ifndef __BUFFER_POOL_MANAGER_H__
    #define __BUFFER_POOL_MANAGER_H__

//#define ENABLE_CUSTOM_NEW_DELETE_OVERRIDE

#include <memory>
#include <mutex>
#include <list>
#include <algorithm>
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

        if((nullptr != _pstBuffers) && (!m_pAval.empty()))
        {
            POOL_BUFFER * pTmp = m_pAval.front();
            
            m_pAval.pop_front();
            m_pConsumed.emplace_back(pTmp);

            ++_i32ConsumedCount;
            return &pTmp->m_buffer;
        }
        return nullptr;
    }

    // release the buffer back to the memory pool
    void ReleaseBuffer(T * pBufferToRelease)
    {
        std::unique_lock<std::mutex> lc(_lock);

        if((nullptr != _pstBuffers) && _i32ConsumedCount)
        {
            auto result = std::find_if(m_pConsumed.begin(), m_pConsumed.end(), [&](POOL_BUFFER * & m){ return(&m->m_buffer == pBufferToRelease); });

            if(result != std::end(m_pConsumed))
            {
                --_i32ConsumedCount;
                m_pAval.emplace_back(*result);
                m_pConsumed.erase(result);
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
        _i32ConsumedCount = 0;

        for(int i = 0; i < _i32MaxBuffers; i++)
        {
            m_pAval.emplace_back(&_pstBuffers[i]);
        }
    }

    void DestroyBufferPool(void)
    { LOG_CALL;
        _pstBuffers.reset(nullptr);
        m_pAval.clear();
    }

private:
    // Disable Copy Constructor
    CFixedSizeBufferPool(const CFixedSizeBufferPool &) = delete;
    // Disable assignment operator
    CFixedSizeBufferPool & operator= (const CFixedSizeBufferPool &) = delete;

private:
    int                     _i32MaxBuffers;
    int                     _i32ConsumedCount;
    std::list<POOL_BUFFER*> m_pAval;
    std::list<POOL_BUFFER*> m_pConsumed;
    std::unique_ptr<POOL_BUFFER[]> _pstBuffers;
    std::mutex              _lock;
};

} // namespace simple_buffer_manager

#endif /* !__BUFFER_POOL_MANAGER_H__ */
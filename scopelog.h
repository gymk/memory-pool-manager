#ifndef __CLASS_FUNCTION_SCOPE_LOGGER_HPP__
    #define __CLASS_FUNCTION_SCOPE_LOGGER_HPP__

#define ENABLE_FUNCTION_SCOPE_LOGGING

#include <string>
#include <cstdio>

class CScopeLogger
{
public:
    //CScopeLogger(std::string & file, std::string & func):m_file(file),m_func(func)
    CScopeLogger(const char * file, const char * func):m_file(file),m_func(func)
    {
        //printf("[%s:%s:Enter]", file.c_str(), func.c_str());
        printf("[%s:%s:Enter]\n", file, func);
    }
    ~CScopeLogger()
    {
        printf("[%s:%s:Exit]\n", m_file.c_str(), m_func.c_str());
    }
private:
    std::string m_file;
    std::string m_func;
};

#if defined(ENABLE_FUNCTION_SCOPE_LOGGING)
    #define SCOPE_LOG(_FILENAME_,_FUNCNAME_)    CScopeLogger    l_##_X_##_scope(_FILENAME_,_FUNCNAME_);
    #define LOG_CALL                            SCOPE_LOG(__FILE__,__PRETTY_FUNCTION__)
#else
    #define LOG_CALL    /* No action */
#endif /* !ENABLE_FUNCTION_SCOPE_LOGGING */

#endif /* !__CLASS_FUNCTION_SCOPE_LOGGER_HPP__ */
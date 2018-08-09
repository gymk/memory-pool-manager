
#ifndef __CLASS_TIME_MEASURE_HPP__
#define __CLASS_TIME_MEASURE_HPP__

#define ENABLE_FUNCTION_TIME_MEASUREMENT

#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>

/* To measure the functoin time taken */
#define DEF_TIME_MEASURE_FUNC(__USER_STR_OR_UIN32__)    CTimeMeasure	timeMeasure(__FILE__, __PRETTY_FUNCTION__, __LINE__, __USER_STR_OR_UIN32__);

/* To print function time taken along with its int value */
#define DEF_TIME_MEASURE_VAR(__USER_STR_OR_UIN32__)     CTimeMeasure	timeMeasure(__FILE__, __PRETTY_FUNCTION__, __LINE__, __USER_STR_OR_UIN32__);

#ifdef ENABLE_FUNCTION_TIME_MEASUREMENT
#define CTIMEMEASURE_TIME_LOG(_X_)      DEF_TIME_MEASURE_VAR(_X_);

#define MESAURE_FUNC_EXECUTION_TIME     CTIMEMEASURE_TIME_LOG(nullptr)
#else
#define MESAURE_FUNC_EXECUTION_TIME     /* No Operation */
#endif /* !ENABLE_FUNCTION_SCOPE_LOGGING */

/*
*
*/

class CTimeMeasure
{
public:
	CTimeMeasure(const char * file, const char * pi8FuncName, unsigned int ui32LineNo, const char * pi8UserStr = nullptr):m_file(file),m_funcName(pi8FuncName)
	{
		if(nullptr != pi8UserStr) {
			m_userStr = pi8UserStr;
		}
		m_ui32LineNo = ui32LineNo;
		markStartTime();
	};
	CTimeMeasure(const char * file, const char * pi8FuncName, unsigned int ui32LineNo, unsigned int ui32UserUint32):m_file(file),m_funcName(pi8FuncName)
	{
		m_ui32LineNo = ui32LineNo;
		m_ui32UserUint32 = ui32UserUint32;
		markStartTime();
	};
	~CTimeMeasure()
	{
		markEndTime();
		printTimeTaken();
	};

public:
	void markStartTime(void)
	{
		start = std::chrono::steady_clock::now();
	};

	void markEndTime(void)
	{
		end = std::chrono::steady_clock::now();
	};

	void printTimeTaken(void)
	{
		if(!m_userStr.empty())
		{
			printf("(%s:%s:%s took %lu microseconds)\n", m_file.c_str(), m_funcName.c_str(), m_userStr.c_str(), (unsigned long int)(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()));
		}
		else if(m_ui32UserUint32)
		{
			printf("(%s:%s:0x%08X took %lu microseconds)\n", m_file.c_str(), m_funcName.c_str(), m_ui32UserUint32, (unsigned long int)(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()));
		}
		else
		{
			printf("(%s:%s took %lu microseconds)\n", m_file.c_str(), m_funcName.c_str(), (unsigned long int)(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()));
		}
	}

private:
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;

	std::string	 m_userStr;
	unsigned int m_ui32UserUint32 = 0;

	std::string	 m_file;
	std::string	 m_funcName;
	unsigned int m_ui32LineNo;
};

#endif /* !__CLASS_TIME_MEASURE_HPP__ */


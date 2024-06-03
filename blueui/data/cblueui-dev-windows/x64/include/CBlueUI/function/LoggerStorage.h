#ifndef CBLUEUI_LOGGERSTORAGE_INC_H_
#define CBLUEUI_LOGGERSTORAGE_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#include <string.h>

namespace BUI {


enum LogLevel
{
	LogLevel_TRACE, /* print 跟踪信息*/
	LogLevel_DEBUG, /* print 调试信息*/
	LogLevel_INFO,  /* print 一般信息*/
	LogLevel_WARN,  /* print 警告信息，不影响程序运行*/
	LogLevel_ERROR, /* print 一般的错误*/
	LogLevel_FATAL  /* print 致命的错误*/
};

/* Logger type */
enum LogOutputType
{
	kConsoleLogger = 1 << 0, /* 输出到控制台*/
	kFileLogger    = 1 << 1, /* 输出到文件IO*/
};

/**
 * @brief 日志存储
 *
 */
class UI_EXP LoggerStorage
{
  public:
	LoggerStorage();
	~LoggerStorage();

	/**
	 * Configure the logger with a configuration file.
	 * If the filename is NULL, return without doing anything.
	 *
	 * The following is the configurable key/value list.
	 * |key                        |value                                        |
	 * |:--------------------------|:--------------------------------------------|
	 * |level                      |TRACE, DEBUG, INFO, WARN, ERROR or FATAL     |
	 * |autoFlush                  |A flush interval [ms] (off if interval <= 0) |
	 * |logger                     |console or file                              |
	 * |logger.console.output      |stdout or stderr                             |
	 * |logger.file.filename       |A output filename (max length is 255 bytes)  |
	 * |logger.file.maxFileSize    |1-LONG_MAX [bytes] (1 MB if size <= 0)       |
	 * |logger.file.maxBackupFiles |0-65535                                        |
	 * |logger.format              |html, txt                                    |
	 *
	 *
	 * @param[in] filename The name of the configuration file
	 * @return Non-zero value upon success or 0 on error
	 */
	int LoadConfigureFromFile(const char* filename);



	void SaveConfigureToFile();


	/**
	 * @brief  Initialize the logger as a console logger.
	 *
	 * @param  output: If the file pointer is NULL, stdout will be used.
	 * @return int: Non-zero value upon success or 0 on error
	 */
	int InitConsoleLogger(FILE* output);

	/**
	 * @brief
	 *
	 * @param  filename: The name of the output file
	 * @param  maxFileSize: The maximum number of bytes to write to any one file
	 * @param  maxBackupFiles: The maximum number of files for backup
	 * @return int
	 */
	int InitFileLogger(const char* filename, long maxFileSize = 1024 * 1024 * 10, unsigned char maxBackupFiles = 100);

	void PrintLogA(LogLevel level, BOOL print_timestamp, const char* file, int line, const char* fmt, ...);

	void PrintLogW(LogLevel level, BOOL print_timestamp, const char* file, int line, const WCHAR* fmt, ...);

	void SetLevel(LogLevel level);

	LogLevel GetLevel(void);

	void ShowShortFileName(bool shortName); // Display short path names

	int IsEnabled(LogLevel level);

	void LoggerFlush();

	/**
	 * @brief 开启Html格式，输出日志。
	 *
	 * @param isHtml true:使用html格式；false：普通文本格式
	 */
	void EnableOutputHtmlFormat(bool isHtml);

	FILE* FileHandler() const;

  protected:
	int rotateLogFiles();
	void getBackupFileName(const char* basename, unsigned char index, char* backupname, size_t size);
	void Lock();
	void UnLock();
	long vflog(FILE* fp, LogLevel levelc, const char* timestamp, long threadID, const char* file, int line, const char* fmt, va_list arg, unsigned long long currentTime, unsigned long long* flushedTime);
	void parseLine(char* line);

  protected:
	/* config file:*/
	char m_configfilename[260];

	UINT m_output_flags;
	/* log console output infos:*/
	FILE* m_output_console;

	/* log file output infos:*/
	FILE* m_output_file;
	char m_filename[260]; // The name of the output file
	char m_fileExt[64];

	long m_maxFileSize;             // The maximum number of bytes to write to any one file
	unsigned char m_maxBackupFiles; // The maximum number of files for backup
	long m_currentFileSize;
	unsigned long long m_flushedTime;
	unsigned long long m_flushInterval;
	LogLevel m_logLevel;
	bool m_isShowShortFileName;
	bool m_isHtmlStyle; // use html label
#if defined(_WIN32) || defined(_WIN64)
	CRITICAL_SECTION m_mutex;
#else
	pthread_mutex_t m_mutex;
#endif /* defined(_WIN32) || defined(_WIN64) */
};

}


#endif

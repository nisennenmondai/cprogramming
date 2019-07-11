/*
 * =============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  simple logger
 *
 *        Version:  1.0
 *        Created:  07/08/2019 02:52:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  nisennenmondai,
 *   Organization:  
 *
 * =============================================================================
 */

/* 
 *  Info  - Generally useful information to log (service start/stop, 
 *          configuration assumptions, etc). Info I want to always have 
 *          available but usually don't care about under normal circumstances. 
 *          This is my out-of-the-box config level.
 *
 *  Warn  - Anything that can potentially cause application oddities, but for 
 *          which I am automatically recovering. (Such as switching from a 
 *          primary to backup server, retrying an operation, missing secondary 
 *          data, etc.)
 *
 *  Trace - Only when I would be "tracing" the code and trying to find one part 
 *          of a function specifically.
 *
 *  Debug - Information that is diagnostically helpful to people more than just 
 *          developers (IT, sysadmins, etc.).
 *
 *  Error - Any error which is fatal to the operation, but not the service or 
 *          application (can't open a required file, missing data, etc.). These 
 *          errors will force user (administrator, or direct user) intervention. 
 *          These are usually reserved (in my apps) for incorrect connection 
 *          strings, missing services, etc.
 *
 *  Fatal - Any error that is forcing a shutdown of the service or application 
 *          to prevent data loss (or further data loss). I reserve these only 
 *          for the most heinous errors and situations where there is guaranteed 
 *          to have been data corruption or loss.
 */

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>

#define FMT_INFO  " - [INFO]  # "
#define FMT_WARN  " - [WARN]  # "
#define FMT_TRACE " - [TRACE] # "
#define FMT_DEBUG " - [DEBUG] # "
#define FMT_ERROR " - [ERROR] # "
#define FMT_FATAL " - [FATAL] # "

#define INFO(...)  print(FMT_INFO  __VA_ARGS__) 
#define WARN(...)  print(FMT_WARN  __VA_ARGS__) 
#define TRACE(...) print(FMT_TRACE __VA_ARGS__) 
#define DEBUG(...) print(FMT_DEBUG __VA_ARGS__) 
#define ERROR(...) print(FMT_ERROR __VA_ARGS__) 
#define FATAL(...) print(FMT_FATAL __VA_ARGS__) 

#define SIZE 30

static void print(const char *message, ...)
{
    char buffer[SIZE];
    va_list args;
    time_t curtime;
    struct timeval tv;
    va_start(args, message);    
    gettimeofday(&tv, NULL);
    curtime = tv.tv_sec;
    strftime(buffer, SIZE,"%Y-%m-%d %T.", localtime(&curtime));
    printf("%s%ld",buffer, tv.tv_usec);
    vprintf(message, args);
    printf("\n");
    va_end(args);
}

#ifndef _fglogs_h_
#define _fglogs_h_
#include "stdio.h"

/**
 * Log file, line and content.
 * @string format of string
 * @... arguments of format to printf
 */
#define fgLog(format, ...) printf("%s:%d | " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#endif
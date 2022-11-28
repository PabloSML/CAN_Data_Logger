#include "config.h" // include all headers in case a new file

extern void fnMyFirstTask(TTASKTABLE *ptrTaskTable)
{
	static unsigned char ucCounter = 0;
	fnDebugMsg("Hello, World! Test number ");
	fnDebugDec(ucCounter++, 0); // note that V1.3 code used	an addition , 0 due to a change in this function's use
	fnDebugMsg("\r\n");

}

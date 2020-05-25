#ifndef __ERROR_HANDLING_H__
#define __ERROR_HANDLING_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

	void assert_failed(uint8_t* file, uint32_t line);
	void _Error_Handler(char* file, int line);

#ifdef __cplusplus
}
#endif

#endif // __ERROR_HANDLING_H__
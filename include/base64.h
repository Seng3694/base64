#ifndef BASE_64_H
#define BASE_64_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

#define B64_TRUE '\1'
#define B64_FALSE '\0'
#define B64_BOOL char

#ifdef __cplusplus
extern "C" {
#endif

char* base64_encode(const void* item, size_t size);
void* base64_decode(const char* str, B64_BOOL tostring);

#ifdef __cplusplus
}
#endif

#endif // !BASE_64_H

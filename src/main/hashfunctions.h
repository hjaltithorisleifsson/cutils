#ifndef HASHFUNCTIONS_H_
#define HASHFUNCTIONS_H_

uint32_t strhash32(char* str);

uint32_t strnhash32(char* str, uint32_t n);

uint64_t strhash64(char* str);

uint64_t strnhash64(char* str, uint32_t n);

#endif
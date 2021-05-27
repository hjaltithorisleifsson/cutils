#include <stdint.h>

uint32_t strhash32(char* str) {
	uint32_t idx = 0;
	uint32_t hash = 0;
	char c;
	while ((c = str[idx++])) {
		hash = c + 31 * hash;
	}
	return hash;
}

uint32_t strnhash32(char* str, uint32_t n) {
	uint32_t idx = 0;
	uint32_t hash = 0;
	char c;
	while (idx < n && (c = str[idx++])) {
		hash = c + 31 * hash;
	}
	return hash;
}

uint64_t strhash64(char* str) {
	uint32_t idx = 0;
	uint64_t hash = 0;
	char c;
	while ((c = str[idx++])) {
		hash = c + 31 * hash;
	}
	return hash;
}

uint64_t strnhash64(char* str, uint32_t n) {
	uint32_t idx = 0;
	uint64_t hash = 0;
	char c;
	while (idx < n && (c = str[idx++])) {
		hash = c + 31 * hash;
	}
	return hash;
}
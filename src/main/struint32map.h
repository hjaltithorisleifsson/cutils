#ifndef STRUINT32MAP_H_
#define STRUINT32MAP_H_

#define DEFAULT_CAPACITY 16
#define DEFAULT_LOAD_FACTOR 0.75

typedef struct struint32 {
	char* key;
	uint32_t value;
} struint32;

typedef struct struint32map {
	uint32_t size;
	uint32_t capacity; //Always a power of 2.
	uint32_t capm1; //The capacity minus 1.
	float loadfactor;
	uint32_t maxsize;
	struint32* entries;
} struint32map;

void print_struint32map(struint32map* table, FILE* outstream);

void init_struint32map_clf(uint32_t capacity, float loadfactor, struint32map* table);

void init_struint32map_c(uint32_t capacity, struint32map* table);

void init_struint32map(struint32map* table);

void resize_struint32map(struint32map* table);

void put_struint32map(char* key, uint32_t value, struint32map* table);

uint32_t get_struint32map(char* key, struint32map* table);

bool contains_struint32map(char* key, struint32map* table);

void removekey_struint32map(char* key, struint32map* table);

void free_struint32map(struint32map* table);

#endif
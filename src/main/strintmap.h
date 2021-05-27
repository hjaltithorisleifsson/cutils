#ifndef STRINTMAP_H_
#define STRINTMAP_H_

#define DEFAULT_CAPACITY 16
#define DEFAULT_LOAD_FACTOR 0.75

typedef struct strint {
	char* key;
	int value;
} strint;

typedef struct strintmap {
	uint32_t size;
	uint32_t capacity; //Always a power of 2.
	uint32_t capm1; //The capacity minus 1.
	float loadfactor;
	uint32_t maxsize;
	strint* entries;
} strintmap;

void print_strintmap(strintmap* table, FILE* outstream);

void init_strintmap_clf(uint32_t capacity, float loadfactor, strintmap* table);

void init_strintmap_c(uint32_t capacity, strintmap* table);

void init_strintmap(strintmap* table);

void resize_strintmap(strintmap* table);

void put_strintmap(char* key, int value, strintmap* table);

int get_strintmap(char* key, strintmap* table);

bool contains_strintmap(char* key, strintmap* table);

void removekey_strintmap(char* key, strintmap* table);

void free_strintmap(strintmap* table);

#endif
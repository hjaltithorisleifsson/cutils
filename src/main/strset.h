#ifndef STRSET_H_
#define STRSET_H_

#define DEFAULT_SET_CAPACITY 16
#define DEFAULT_SET_LOAD_FACTOR 0.75

typedef struct strset {
	uint32_t size;
	uint32_t capacity; //Always a power of 2.
	uint32_t capm1; //The capacity minus 1.
	float loadfactor;
	uint32_t maxsize;
	char** entries;
} strset;

void print_strset(strset* set, FILE* outstream);

void init_strset_clf(uint32_t capacity, float loadfactor, strset* set);

void init_strset_c(uint32_t capacity, strset* set);

void init_strset(strset* set);

void resize_strset(strset* set);

void add_strset(char* key, strset* set);

int get_strset(char* key, strset* set);

bool contains_strset(char* key, strset* set);

void removekey_strset(char* key, strset* set);

void free_strset(strset* set);

#endif
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "hashfunctions.h"
#include "struint32map.h"

void print_struint32map(struint32map* table, FILE* outstream) {
	uint32_t idx;
	for (idx = 0; idx < table->capacity; ++idx) {
		fprintf(outstream, "idx=%u, key=%s, value=%u\n", idx, table->entries[idx].key, table->entries[idx].value);
	}
}

void init_struint32map_clf(uint32_t capacity, float loadfactor, struint32map* table) {
	struint32* entries = (struint32*) malloc(capacity * sizeof(struint32));
	memset(entries, 0, capacity * sizeof(struint32));
	table->entries = entries;
	table->size = 0;
	table->capacity = capacity;
	table->capm1 = capacity - 1;
	table->loadfactor = loadfactor;
	table->maxsize = (uint32_t) (capacity * loadfactor);
}

void init_struint32map_c(uint32_t capacity, struint32map* table) {
	init_struint32map_clf(capacity, DEFAULT_LOAD_FACTOR, table);
}

void init_struint32map(struint32map* table) {
	init_struint32map_c(DEFAULT_CAPACITY, table);
}

void resize_struint32map(struint32map* table) {
	uint32_t ocap = table->capacity;
	uint32_t ncap = 2 * ocap;
	uint32_t ncapm1 = ncap - 1;

	struint32* nentries = (struint32*) malloc(ncap * sizeof(struint32));
	memset(nentries, 0, ncap * sizeof(struint32));

	struint32* oentries = table->entries;

	uint32_t i,j;
	struint32* oe;
	struint32* ne;
	for (i = 0; i < ocap; ++i) {
		if ((oe = oentries + i)->key) {
			j = strhash32(oe->key) & ncapm1;
			while ((ne = nentries + j)->key) {
				j = (j + 1) & ncapm1;
			}
			ne->key = oe->key;
			ne->value = oe->value;
		}
	}

	free(oentries);
	table->entries = nentries;
	table->capacity = ncap;
	table->maxsize = ncap * table->loadfactor;
}

void put_struint32map(char* key, uint32_t value, struint32map* table) {
	if (table->size == table->maxsize) {
		resize_struint32map(table);
	}

	struint32* entries = table->entries;
	uint32_t capm1 = table->capm1;
	uint32_t idx = strhash32(key) & capm1;
	struint32* e;
	while ((e = entries + idx)->key && strcmp(e->key, key)) {
		idx = (idx + 1) & capm1;
	}
	e->key = key;
	e->value = value;
	table->size++;
}

uint32_t get_struint32map(char* key, struint32map* table) {
	struint32* entries = table->entries;
	uint32_t capm1 = table->capm1;
	uint32_t idx = strhash32(key) & capm1;
	struint32* e;
	while ((e = entries + idx)->key) {
		if (strcmp(key, e->key) == 0) {
			return e->value;
		}
		idx = (idx + 1) & capm1;
	}
	fprintf(stderr, "Does not contain key=%s\nAborting.", key);
	abort();
}

bool contains_struint32map(char* key, struint32map* table) {
	struint32* entries = table->entries;
	uint32_t capm1 = table->capm1;
	uint32_t idx = strhash32(key) & capm1;
	struint32* e;
	while ((e = entries + idx)->key) {
		if (strcmp(key, e->key) == 0) {
			return true;
		}
		idx = (idx + 1) & capm1;
	}
	return false;
}

void removekey_struint32map(char* key, struint32map* table) {
	struint32* entries = table->entries;
	uint32_t capm1 = table->capm1;
	uint32_t idx = strhash32(key) & capm1;
	struint32* e;
	while ((e = entries + idx)->key) {
		if (strcmp(key, e->key) == 0) {
			e->key = NULL;
			e->value = 0;
			return;
		}
		idx = (idx + 1) & capm1;
	}
}

void free_struint32map(struint32map* table) {
	free(table->entries);
}

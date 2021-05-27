#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "hashfunctions.h"
#include "strintmap.h"

void print_strintmap(strintmap* table, FILE* outstream) {
	int idx;
	for (idx = 0; idx < table->capacity; ++idx) {
		fprintf(outstream, "idx=%u, key=%s, value=%u\n", idx, table->entries[idx].key, table->entries[idx].value);
	}
}

void init_strintmap_clf(uint32_t capacity, float loadfactor, strintmap* table) {
	strint* entries = (strint*) malloc(capacity * sizeof(strint));
	memset(entries, 0, capacity * sizeof(strint));
	table->entries = entries;
	table->size = 0;
	table->capacity = capacity;
	table->capm1 = capacity - 1;
	table->loadfactor = loadfactor;
	table->maxsize = (int) (capacity * loadfactor);
}

void init_strintmap_c(uint32_t capacity, strintmap* table) {
	init_strintmap_clf(capacity, DEFAULT_LOAD_FACTOR, table);
}

void init_strintmap(strintmap* table) {
	init_strintmap_c(DEFAULT_CAPACITY, table);
}

void resize_strintmap(strintmap* table) {
	int ocap = table->capacity;
	int ncap = 2 * ocap;
	int ncapm1 = ncap - 1;

	strint* nentries = (strint*) malloc(ncap * sizeof(strint));
	memset(nentries, 0, ncap * sizeof(strint));

	strint* oentries = table->entries;

	int i,j;
	strint* oe;
	strint* ne;
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

void put_strintmap(char* key, int value, strintmap* table) {
	if (table->size == table->maxsize) {
		resize_strintmap(table);
	}

	strint* entries = table->entries;
	int capm1 = table->capm1;
	int idx = strhash32(key) & capm1;
	strint* e;
	while ((e = entries + idx)->key && strcmp(e->key, key)) {
		idx = (idx + 1) & capm1;
	}
	e->key = key;
	e->value = value;
	table->size++;
}

int get_strintmap(char* key, strintmap* table) {
	strint* entries = table->entries;
	int capm1 = table->capm1;
	int idx = strhash32(key) & capm1;
	strint* e;
	while ((e = entries + idx)->key) {
		if (strcmp(key, e->key) == 0) {
			return e->value;
		}
		idx = (idx + 1) & capm1;
	}
	fprintf(stderr, "Does not contain key=%s\nAborting.", key);
	abort();
}

bool contains_strintmap(char* key, strintmap* table) {
	strint* entries = table->entries;
	int capm1 = table->capm1;
	int idx = strhash32(key) & capm1;
	strint* e;
	while ((e = entries + idx)->key) {
		if (strcmp(key, e->key) == 0) {
			return true;
		}
		idx = (idx + 1) & capm1;
	}
	return false;
}

void removekey_strintmap(char* key, strintmap* table) {
	strint* entries = table->entries;
	int capm1 = table->capm1;
	int idx = strhash32(key) & capm1;
	strint* e;
	while ((e = entries + idx)->key) {
		if (strcmp(key, e->key) == 0) {
			e->key = NULL;
			e->value = 0;
			return;
		}
		idx = (idx + 1) & capm1;
	}
}

void free_strintmap(strintmap* table) {
	free(table->entries);
}

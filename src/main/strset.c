#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "hashfunctions.h"
#include "strset.h"

void print_strset(strset* set, FILE* outstream) {
	int idx;
	for (idx = 0; idx < set->capacity; ++idx) {
		fprintf(outstream, "idx=%u, member=%s\n", idx, set->entries[idx]);
	}
}

void init_strset_clf(uint32_t capacity, float loadfactor, strset* set) {
	char** entries = (char**) malloc(capacity * sizeof(char*));
	memset(entries, 0, capacity * sizeof(char*));
	set->entries = entries;
	set->size = 0;
	set->capacity = capacity;
	set->capm1 = capacity - 1;
	set->loadfactor = loadfactor;
	set->maxsize = (uint32_t) (capacity * loadfactor);
}

void init_strset_c(uint32_t capacity, strset* set) {
	init_strset_clf(capacity, DEFAULT_SET_LOAD_FACTOR, set);
}

void init_strset(strset* set) {
	init_strset_c(DEFAULT_SET_CAPACITY, set);
}

void resize_strset(strset* set) {
	uint32_t ocap = set->capacity;
	uint32_t ncap = 2 * ocap;
	uint32_t ncapm1 = ncap - 1;

	char** nentries = (char**) malloc(ncap * sizeof(char*));
	memset(nentries, 0, ncap * sizeof(char*));

	char** oentries = set->entries;

	uint32_t i,j;
	char** oe;
	char** ne;
	for (i = 0; i < ocap; ++i) {
		if ((oe = oentries + i)) {
			j = strhash32(*oe) & ncapm1;
			while ((ne = nentries + j)) {
				j = (j + 1) & ncapm1;
			}
			ne = oe;
		}
	}

	free(oentries);
	set->entries = nentries;
	set->capacity = ncap;
	set->maxsize = (uint32_t) (ncap * set->loadfactor);
}

void add_strset(char* str, strset* set) {
	if (set->size == set->maxsize) {
		resize_strset(set);
	}

	char** entries = set->entries;
	uint32_t capm1 = set->capm1;
	uint32_t idx = strhash32(str) & capm1;
	char** e;
	while ((e = entries + idx) && strcmp(str, *e)) {
		idx = (idx + 1) & capm1;
	}
	*e = str;
	set->size++;
}

bool contains_strset(char* str, strset* set) {
	char** entries = set->entries;
	uint32_t capm1 = set->capm1;
	uint32_t idx = strhash32(str) & capm1;
	char** e;
	while ((e = entries + idx)) {
		if (strcmp(str, *e) == 0) {
			return true;
		}
		idx = (idx + 1) & capm1;
	}
	return false;
}

void remove_strset(char* str, strset* set) {
	char** entries = set->entries;
	uint32_t capm1 = set->capm1;
	uint32_t idx = strhash32(str) & capm1;
	char** e;
	while ((e = entries + idx)) {
		if (strcmp(str, *e) == 0) {
			e = NULL;
			return;
		}
		idx = (idx + 1) & capm1;
	}
}

void free_strset(strset* set) {
	free(set->entries);
}

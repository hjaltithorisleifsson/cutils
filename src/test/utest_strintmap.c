#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../main/strintmap.h"

int test_init() {
	const float lf = 0.75;
	const uint32_t cap = 16;
	const uint32_t maxsize = 12;

	int tr = 0;

	strintmap table;
	init_strintmap_clf(cap, lf, &table);
	if (table.capacity != cap) {
		fprintf(stderr, "Expected table capacity: %u\n", table.capacity);
		fprintf(stderr, "Actual table capacity: %u\n", cap);
		tr = 1;
	}

	if (table.loadfactor != lf) {
		fprintf(stderr, "Expected loadfactor: %f\n", table.loadfactor);
		fprintf(stderr, "Actual loadfactor: %f\n", lf);
		tr = 1;
	}

	if (table.maxsize != maxsize) {
		fprintf(stderr, "Expected maxsize: %u\n", table.maxsize);
		fprintf(stderr, "Actual maxsize: %u\n", maxsize);
		tr = 1;
	}

	if (table.capm1 + 1 != cap) {
		fprintf(stderr, "Expected capm1: %u\n", table.capm1);
		fprintf(stderr, "Actual maxsize: %u\n", cap - 1);
		tr = 1;
	}

	if (table.entries == NULL) {
		fprintf(stderr, "table->entries==NULL\n");
		tr = 1;
	}

	uint32_t idx;
	strint* e;
	for (idx = 0; idx < cap; ++idx) {
		e = table.entries + idx;
		if (e->key != 0) {
			fprintf(stderr, "Key at idx=%u is not null.\n", idx);
			tr = 1;
		}

		if (e->value != 0) {
			fprintf(stderr, "Value at idx=%u is not zero.\n", idx);
			tr = 1;
		}
	}

	free_strintmap(&table);
	return tr;
}

int test_resize() {
	strintmap table;
	init_strintmap_clf(2, 0.75, &table);
	put_strintmap("hjalti", 24, &table);
	resize_strintmap(&table);
	print_strintmap(&table, stderr);
	free_strintmap(&table);
	return 0;
}

int test_put() {
	strintmap table;
	init_strintmap_clf(2, 0.75, &table);
	put_strintmap("hjalti", 1, &table);
	print_strintmap(&table, stderr);
	put_strintmap("thor", 2, &table);
	print_strintmap(&table, stderr);
	free_strintmap(&table);
	return 0;
}

int test_contains() {
	strintmap table;
	init_strintmap_clf(2, 0.75, &table);
	put_strintmap("hjalti", 1, &table);
	if (!contains_strintmap("hjalti", &table)) {
		fprintf(stderr, "Does not contain key \"hjalti\"");
	}
	free_strintmap(&table);
	return 0;
}

int test_removekey() {
	strintmap table;
	init_strintmap_clf(2, 0.75, &table);
	put_strintmap("hjalti", 1, &table);
	removekey_strintmap("hjalti", &table);

	if (contains_strintmap("hjalti", &table)) {
		fprintf(stderr, "Does still contain key \"hjalti\"");
	}
	free_strintmap(&table);
	return 0;
}

int main() {
	fprintf(stderr, "Running: test_init()\n");
	test_init();
	fputc('\n', stderr);

	fprintf(stderr, "Running: test_resize()\n");
	test_resize();
	fputc('\n', stderr);

	fprintf(stderr, "Running: test_put()\n");
	test_put();
	fputc('\n', stderr);

	fprintf(stderr, "Running: test_contains()\n");
	test_contains();
	fputc('\n', stderr);

	fprintf(stderr, "Running: test_removekey()\n");
	test_removekey();
	fputc('\n', stderr);
	return 0;
}

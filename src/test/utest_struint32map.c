#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../main/struint32map.h"

int test_init() {
	const float lf = 0.75;
	const uint32_t cap = 16;
	const uint32_t maxsize = 12;

	int tr = 0;

	struint32map table;
	init_struint32map_clf(cap, lf, &table);
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
	struint32* e;
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

	free_struint32map(&table);
	return tr;
}

int test_resize() {
	struint32map table;
	init_struint32map_clf(2, 0.75, &table);
	put_struint32map("hjalti", 24, &table);
	resize_struint32map(&table);
	print_struint32map(&table, stderr);
	free_struint32map(&table);
	return 0;
}

int test_put() {
	struint32map table;
	init_struint32map_clf(2, 0.75, &table);
	put_struint32map("hjalti", 1, &table);
	print_struint32map(&table, stderr);
	put_struint32map("thor", 2, &table);
	print_struint32map(&table, stderr);
	free_struint32map(&table);
	return 0;
}

int test_contains() {
	struint32map table;
	init_struint32map_clf(2, 0.75, &table);
	put_struint32map("hjalti", 1, &table);
	if (!contains_struint32map("hjalti", &table)) {
		fprintf(stderr, "Does not contain key \"hjalti\"");
	}
	free_struint32map(&table);
	return 0;
}

int test_removekey() {
	struint32map table;
	init_struint32map_clf(2, 0.75, &table);
	put_struint32map("hjalti", 1, &table);
	removekey_struint32map("hjalti", &table);

	if (contains_struint32map("hjalti", &table)) {
		fprintf(stderr, "Does still contain key \"hjalti\"");
	}
	free_struint32map(&table);
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

// Lab03.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#define MAX_SIZE 100

#define MAX_COL 7
#define MAX_ROW 7

#define SWAP(a, b) \
{\
	int t = a;\
	a = b;\
	b = t;\
}

#define SPLIT_ROW(i, n) (i) < (n) - 1 ? ' ' : '\n'

#define INIT_J(i, c, k) (i) == (c) ? (k + 1) : 0

int main() {
	//#1
	srand(time(NULL));
	int mas[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++) {
		mas[i] = rand() % 2;
	}
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("%d", mas[i]);
	}
	printf("\n\n");
	int count = 0, n = 0, *m = NULL, *tmp = NULL;
	for (int i = 0; i < MAX_SIZE; i++) {
		if (mas[i] == 0 && mas[i + 1] == 0) {
			for (; i < MAX_SIZE; ++i) {
				if (mas[i] != 0) {
					break;
				}
				else {
					count++;
				}
			}
			n += 2;
			tmp = (int*)realloc(m, n * sizeof(int));
			m = tmp;
			m[n - 2] = 0;
			m[n - 1] = count;
			count = 0;
		}
		if (i < MAX_SIZE) {
			n++;
			tmp = (int*)realloc(m, n * sizeof(int));
			m = tmp;
			m[n - 1] = mas[i];
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%d", m[i]);
	}
	printf("\n\n");
	//#2
	int mas_2d[MAX_ROW][MAX_COL];
	for (int i = 0; i < MAX_ROW; ++i) {
		for (int j = 0; j < MAX_COL; ++j) {
			mas_2d[i][j] = rand() % 100;
		}
	}
	for (int i = 0; i < MAX_ROW; ++i) {
		for (int j = 0; j < MAX_COL; ++j) {
			printf("%3d%c", mas_2d[i][j], SPLIT_ROW(j, MAX_COL));
		}
	}
	printf("\n\n");

	for (int c = 0; c < MAX_ROW; ++c) {
		for (int k = 0; k < MAX_COL; ++k) {
			int minI = c, minJ = k;
			for (int i = c; i < MAX_ROW; ++i) {
				for (int j = INIT_J(i, c, k); j < MAX_COL; ++j) {
					if (mas_2d[minI][minJ] > mas_2d[i][j]) {
						minI = i; minJ = j;
					}
				}
			}
			SWAP(mas_2d[minI][minJ], mas_2d[c][k]);
		}
	}
	for (int i = 0; i < MAX_ROW; ++i) {
		for (int j = 0; j < MAX_COL; ++j) {
			printf("%3d%c", mas_2d[i][j], SPLIT_ROW(j, MAX_COL));
		}
	}
	getchar();
    return 0;
}
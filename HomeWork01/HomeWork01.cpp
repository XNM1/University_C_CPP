// HomeWork01.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#define SIZE 10
#define SWAP(a, b)\
{\
	int tmp;\
	tmp = (a);\
	(a) = (b);\
	(b) = tmp;\
}

void BubleSort(int* mas, const int size) {
	int i, j;
	for (int i = 0; i < size; ++i) {
		for (j = 0; j < size - 1 - i; ++j) {
			if (mas[j] > mas[j + 1]) {
				SWAP(mas[j], mas[j + 1]);
			}
		}
	}
}

void SelectionSort(int* mas, const int size) {
	int i, j;
	for (int i = 0; i < size; ++i) {
		int maxI = i;
		for (j = i + 1; j < size; ++j) {
			if (mas[j] < mas[maxI]) {
				maxI = j;
			}
		}
		SWAP(mas[i], mas[maxI]);
	}
}

int mystrlen(const char* dest, int result) {
	return (*dest) <= 0 ? result : mystrlen(dest + 1, result + 1);
}

char* mystrcat(char *dest, const char* src) {
	char* tmp = (char*)calloc((mystrlen(dest, 0) + mystrlen(src, 0) + 1), sizeof(char));
	int i;
	for (i = 0; i < mystrlen(dest, 0); ++i) {
		tmp[i] = dest[i];
	}
	for (i = mystrlen(dest, 0); i < (mystrlen(dest, 0) + mystrlen(src, 0) + 1); ++i) {
		tmp[i] = src[i - mystrlen(dest, 0)];
	}
	dest = tmp;
	return dest;
}

char* mystrcat2(char* dest, const char* src) {
	char* tmp = dest;
	while (*tmp) {
		tmp++;
	}
	while (*src) {
		*tmp = *src;
		src++;
		tmp++;
	}
	*tmp = '\0';
	return dest;
}


int main()
{
	srand(time(NULL));
	char str1[] = "Hello ";
	char str2[] = "World";
	printf("%s\n", mystrcat(str1, str2));

	int mas[SIZE], i;
	for (i = 0; i < SIZE; ++i) {
		mas[i] = rand() % 100;
	}
	for (i = 0; i < SIZE; ++i) {
		printf("%d%c",mas[i], i == SIZE - 1 ? '\n' : ' ');
	}
	SelectionSort(mas, sizeof(mas)/sizeof(int));
	for (i = 0; i < SIZE; ++i) {
		printf("%d%c", mas[i], i == SIZE - 1 ? '\n' : ' ');
	}
	getchar();
    return 0;
}

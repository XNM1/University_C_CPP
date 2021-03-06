// Classroom_work03.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#define SPLIT_ROW(i, n) (i) < (n) - 1 ? ' ' : '\n'
#define SQR(x) (x) * (x)
#define MAX_SIZE 120
#define SWAP(a, b) (a) ^= (b);\
(b) ^= (a);\
(a) ^= (b);


void BubleSort(int mas[], int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size - i - 1; j++) {
			if (mas[j] > mas[j + 1]) {
				SWAP(mas[j], mas[j + 1]);
			}
		}
	}
}

int SearchBinary(int mas[], int minIndex, int maxIndex, int key) {
	int midd = 0;
	while (true) {
		midd = (minIndex + maxIndex) / 2;
		if (key < mas[midd]) {
			maxIndex = midd - 1;
		}
		else if (key > mas[midd]) {
			minIndex = midd + 1;
		}
		else if (minIndex > maxIndex) {
			return -1;
		}
		else {
			return midd;
		}
	}
}

int main()
{
	srand(time(NULL));
	//№10
	char smile[4][5] = {
		{ 0,1,0,1,0 },
		{ 0,0,0,0,0 },
		{ 1,0,0,0,1 },
		{ 0,1,1,1,0 }
	};
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 5; ++j) {
			printf("%c%c", smile[i][j], SPLIT_ROW(j, 5));
		}
	}
	//№1
	double mas[MAX_SIZE][MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; ++i) {
		for (int j = 0; j < MAX_SIZE; ++j) {
			mas[i][j] = (-1000) + (2000 + 1000) * 1.0 * rand() / RAND_MAX;
		}
	}
	/*for (int i = 0; i < MAX_SIZE; ++i) {
		for (int j = 0; j < MAX_SIZE; ++j) {
			printf("%lf%c", mas[i][j], SPLIT_ROW(j, MAX_SIZE));
		}
	}*/
	//№2
	double key; int sum = 0;
	printf("Enter num: ");
	scanf("%lf", &key);
	for (int i = 0; i < MAX_SIZE; ++i) {
		for (int j = 0; j < MAX_SIZE; ++j) {
			if (mas[i][j] < 0 && mas[i][j] > key) {
				sum++;
			}
		}
	}
	printf("%d\n", sum);
	//№3
	double L = 0.0;
	for (int i = 0; i < MAX_SIZE; ++i) {
		for (int j = 0; j < MAX_SIZE; ++j) {
				L += SQR(mas[i][j]);
		}
	}
	printf("%lf\n", L);
	//№4
	double min = mas[0][0], max = mas[0][0];
	for (int i = 1; i < MAX_SIZE; ++i) {
		for (int j = 1; j < MAX_SIZE; ++j) {
			if (mas[i][j] < min) {
				min = mas[i][j];
			}
			else if (mas[i][j] > max) {
				max = mas[i][j];
			}
		}
	}
	printf("max: %lf\nmin: %lf\n", max, min);
	//№5
	printf("Enter num: ");
	scanf("%lf", &key);
	for (int i = 0; i < MAX_SIZE; ++i) {
		for (int j = 0; j < MAX_SIZE; ++j) {
			if (mas[i][j] == key) {
				printf("i = %d; j = %d;\n", i, j);
				break;
			}
		}
	}
	//№6
	int arr[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; ++i) {
		arr[i] = rand() % 201;
	}
	BubleSort(arr, MAX_SIZE);
	//№7
	printf("index = %d\n", SearchBinary(arr, 0, MAX_SIZE, 198));
	getchar();
	getchar();
}
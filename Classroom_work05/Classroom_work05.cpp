// Classroom_work05.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#define SIGN_FUNC(f, x) ((f(x) > 0)? 1 : (f(x) < 0)? -1 : 0)
#define CHECK_DIFF_SIGN(s1, s2) s1 != s2
#define SIZE 10
#define SWAP(a, b)\
{\
	int tmp;\
	tmp = (a);\
	(a) = (b);\
	(b) = tmp;\
}

typedef double(*func_t)(double);

double f1(double);
int localize_root(double, double, func_t);
void bisect(double, double, func_t, double, double*);
void chord(double, double, func_t, double, double*);
void SelectionSort(int*, const int);
int Fibonachi(int, int, int);

int main()
{
	double eps = 1e-6;
	double a = -1, b = 1, h = 0.01;
	double x;
	for (x = a; x < b; x += h) {
		if (localize_root(x, x + h, f1)) {
			printf("Root interval [%.3f, %.3f]\n", x, x + h);
			double x0 = 0;
			chord(x, x + h, f1, eps, &x0);
			printf("Root value(Chord Method) >>> %.7f\n", x0);
			bisect(x, x + h, f1, eps, &x0);
			printf("Root value(Bisect Method) >>> %.7f\n", x0);
		}
	}

	int mas[SIZE], i;
	for (i = 0; i < SIZE; ++i) {
		mas[i] = rand() % 100;
	}
	for (i = 0; i < SIZE; ++i) {
		printf("%d%c", mas[i], i == SIZE - 1 ? '\n' : ' ');
	}
	SelectionSort(mas, sizeof(mas) / sizeof(int));
	for (i = 0; i < SIZE; ++i) {
		printf("%d%c", mas[i], i == SIZE - 1 ? '\n' : ' ');
	}

	printf("%d\n", Fibonachi(7, 1, 1));
	getchar();
	return 0;
}

int localize_root(double a, double b, func_t f) {
	return SIGN_FUNC(f, a) != SIGN_FUNC(f, b);
}

double f1(double x) {
	return x * cos(2 * x) - 3 * x * x;
}

void bisect(double a, double b, func_t f, double eps, double* x)
{
	if (fabs(a - b) < eps) {
		*x = (a + b) / 2;
		return;
	}
	else {
		double c = (a + b) / 2;
		int sgn1 = SIGN_FUNC(f, a);
		int sgn2 = SIGN_FUNC(f, b);
		int sgn3 = SIGN_FUNC(f, c);
		if (fabs(f(a)) <= eps)
		{
			*x = a;
			return;
		}
		else if (fabs(f(b)) <= eps) {
			*x = b;
			return;
		}
		else if (fabs(f(c)) <= eps) {
			*x = c;
			return;
		}
		if (CHECK_DIFF_SIGN(sgn1, sgn3))
		{
			bisect(a, c, f, eps, x);
		}
		else if (CHECK_DIFF_SIGN(sgn3, sgn2)) {
			bisect(c, b, f, eps, x);
		}
	}
}

void chord(double a, double b, func_t f, double eps, double* x) {
	double x0 = *x;
	*x = a - f(a) * (b - a) / (f(b) - f(a));
	if (fabs(*x - x0) < eps) {
		return;
	}
	int sgn1 = SIGN_FUNC(f, a);
	int sgn2 = SIGN_FUNC(f, *x);
	if (CHECK_DIFF_SIGN(sgn1, sgn2)) {
		chord(a, *x, f, eps, x);
	}
	else {
		chord(*x, b, f, eps, x);
	}
}

void SelectionSort(int* mas, const int size) {
	int i, j;
	for (i = 0; i < size; ++i) {
		int maxI = i;
		for (j = i + 1; j < size; ++j) {
			if (mas[j] < mas[maxI]) {
				maxI = j;
			}
		}
		SWAP(mas[i], mas[maxI]);
	}
}

int Fibonachi(int n, int p, int c) {
	if (n == 0)
	{
		return c;
	}
	return Fibonachi(n - 1, c, p + c);
}


// Lab06.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

typedef double(*func_t)(double);

double f1(double);
double f2(double);
int is_min(double, double, double);
int is_max(double, double, double);
void process_func(FILE*, double, double, double, func_t);
void set_mark(double, double, double, char*);
double quad_central(func_t, double, double, int);
void integral(FILE*, func_t, double, double, double, int);


int main()
{
	FILE *f_1 = fopen("f1.txt", "w+");
	FILE *f_2 = fopen("f2.txt", "w+");
	process_func(f_1, -1, 1, 0.01, f1);
	process_func(f_2, -3, 4, 0.01, f2);
	integral(f_1, f1, -1, 1, 0.001, 10);
	integral(f_2, f2, -3, 4, 0.001, 10);
	fclose(f_1);
	fclose(f_2);
    return 0;
}

void integral(FILE *f, func_t func, double a, double b, double eps, int n) {
	double s = quad_central(func, a, b, n), s0 = 0;
	while (fabs(s - s0) > eps) {
		s0 = s;
		s = quad_central(func, a, b, n *= 2);
	}
	s = (s + s0) / 2;
	fprintf(f, "Integral [%.2lf, %.2lf]: %lf", a, b, s);
}

int is_min(double y1, double y2, double y3) {
	return y2 < y1 && y2 < y3;
}

int is_max(double y1, double y2, double y3)
{
	return y2 > y1 && y2 > y3;
}

void process_func(FILE* f, double a, double b, double h, func_t func) {
	fprintf(f, "X\t\tY\n");
	char c[5] = "";
	double x[3], y[3];
	int i;
	for (i = 0; i < 3; ++i) {
		x[i] = a + h * (double)i;
		y[i] = func(x[0]);
	}
	set_mark(y[0], y[1], y[2], c);
	fprintf(f, "%lf\t%lf\n", x[0], y[0]);
	fprintf(f, "%lf\t%lf %s\n", x[1], y[1], c);
	fprintf(f, "%lf\t%lf\n", x[2], y[2]);
	x[0] = x[1];
	x[1] = x[2];
	y[0] = y[1];
	y[1] = y[2];
	for (x[2] += h; x[2] <= b + h; x[0] = x[1], x[1] = x[2], x[2] += h, y[0] = y[1], y[1] = y[2]) {
		y[2] = func(x[2]);
		set_mark(y[0], y[1], y[2], c);
		fprintf(f, "%lf\t%lf %s\n", x[1], y[1], c);
	}
}

void set_mark(double y1, double y2, double y3, char* c) {
	if (is_min(y1, y2, y3)) {
		strcpy(c, "Min");
	}
	else if (is_max(y1, y2, y3)) {
		strcpy(c, "Max");
	}
	else {
		strcpy(c, "");
	}
}

double quad_central(func_t f, double a, double b, int n) {
	double s = 0, x;
	double h = (b - a) / n;
	for (x = a; x < b; x += h)
	{
		s += f(x + h / 2);
	}
	return h * s;
}

double f1(double x) {
	return sqrt((x)+1.);
}

double f2(double x) {
	if (x <= -2) {
		return 1 - fabs(x + 1);
	}
	else if (x > -2) {
		return cos(3 * x - 1) / (x + 1);
	}
	else if (x > 3)
	{
		return 2 * x - 3;
	}
}
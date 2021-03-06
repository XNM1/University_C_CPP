// Lab05.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#define SQR(x) (x)*(x)
#define LENGTH(x, y, x0, y0) powf(SQR(fabs((x0) - (x)))+SQR(fabs((y0) - (y))), 1./2.)
#define SIDE(r, h) powf(SQR((r)) - SQR((h)), 1./2.)

#define SIGN_FUNC(f, x) ((f(x) > 0)? 1 : (f(x) < 0)? -1 : 0)
#define CHECK_DIFF_SIGN(s1, s2) s1 != s2

typedef double(*func_t)(double);

int point_in_circle(double, double, double, double, double, double);
int point_in_square(double, double, double, double, double, double);

double f1(double);
double df1(double);
int localize_root(double, double, func_t);
double bisect(double, double, func_t, double);
double chord(double, double, func_t, double);
double newton(func_t, func_t, double, double);

double f2(double);
double test_res();
double quad_central(func_t, double, double, int);
double trap(func_t, double, double, int);
double parabola(func_t, double, double);

int main() {
	//1
	printf("#1\n");
	if (point_in_circle(-2, -3, 0, 0, 10, 10)) {
		printf("Point is in the circle, but is not in the rectangle\n");
	}
	else {
		printf("Point is in the rectangle or is not in the circle\n");
	}
	//2
	printf("#2\n");
	double eps = 1e-6;
	double a = -1, b = 1, h = 0.01;
	double x;
	double x0;
	for (x = a; x < b; x += h) {
		if (localize_root(x, x + h, f1)) {
			printf("Root interval [%.3f, %.3f]\n", x, x + h);
			x0 = chord(x, x + h, f1, eps);
			printf("Root value(Chord Method) >>> %.7f\n", x0);
			x0 = bisect(x, x + h, f1, eps);
			printf("Root value(Bisect Method) >>> %.7f\n", x0);
			x0 = newton(f1, df1, x, eps);
			printf("Root value(Newton Method) >>> %.7f\n", x0);
		}
	}
	//3
	printf("#3\n");
	a = 2; b = 5;
	int n = 10;
	double s = quad_central(f2, a, b, n), s0 = 0, r = test_res();
	while (fabs(s - s0) > eps) {
		s0 = s;
		s = quad_central(f2, a, b, n *= 2);
	}
	s = (s + s0) / 2;
	double tol = fabs(s - r);
	printf("S(Quad Central Method): %lf\nResult: %lf\ntol: %lf\n", s, r, tol);
	s = trap(f2, a, b, n), s0 = 0;
	while (fabs(s - s0) > eps) {
		s0 = s;
		s = trap(f2, a, b, n *= 2);
	}
	s = (s + s0) / 2;
	tol = fabs(s - r);
	printf("S(Method of trapeziums): %lf\nResult: %lf\ntol: %lf\n", s, r, tol);
	s = parabola(f2, a, b);
	s = (s + s0) / 2;
	tol = fabs(s - r);
	printf("S(Method of parabolas): %lf\nResult: %lf\ntol: %lf\n", s, r, tol);
	getchar();
	return 0;
}

int point_in_circle(double x, double y, double x0, double y0, double r, double h) {
	if (LENGTH(x, y, x0, y0) <= r) {
		return !point_in_square(x, y, x0, y0, h/2, SIDE(r, h/2));
	}
	else {
		return 0;
	}
}

int point_in_square(double x, double y, double x0, double y0, double halfh, double halfside) {
	if (LENGTH(x0, y, x, y) <= halfside && LENGTH(x, y0, x, y) <= halfh) {
		return 1;
	}
	else {
		return 0;
	}
}

double f1(double x) {
	return x * cos(2 * x) - 3 * x * x;
}

double df1(double x) {
	return cos(2 * x) - 2 * x * sin(2 * x) - 6 * x;
}

double f2(double x) {
	return log(x - 1) / (x - 1);
}

double test_res() {
	return (1. / 2.)*(SQR(log(4)) - SQR(log(1)));
}

int localize_root(double a, double b, func_t f) {
	return SIGN_FUNC(f, a) != SIGN_FUNC(f, b);
}

double bisect(double a, double b, func_t f, double eps)
{
	while(fabs(a - b) > eps) {
		double c = (a + b) / 2;
		int sgn1 = SIGN_FUNC(f, a);
		int sgn2 = SIGN_FUNC(f, b);
		int sgn3 = SIGN_FUNC(f, c);
		if (fabs(f(a)) <= eps)
		{
			return a;
		}
		else if (fabs(f(b)) <= eps) {
			return b;
		}
		else if (fabs(f(c)) <= eps) {
			return c;
		}
		if (CHECK_DIFF_SIGN(sgn1, sgn3))
		{
			b = c;
		}
		else if (CHECK_DIFF_SIGN(sgn3, sgn2)) {
			a = c;
		}
	}
	return (a + b) / 2;
}

double chord(double a, double b, func_t f, double eps) {
	double x = 0;
	double x0;
	do {
		x0 = x;
		x = a - f(a) * (b - a) / (f(b) - f(a));
		int sgn1 = SIGN_FUNC(f, a);
		int sgn2 = SIGN_FUNC(f, x);
		if (CHECK_DIFF_SIGN(sgn1, sgn2)) {
			b = x;
		}
		else {
			a = x;
		}
	} while (fabs(x - x0) > eps);
	return x;
}

double newton(func_t f, func_t df, double x, double eps) {
	double x1 = x - f(x) / df(x);
	while (fabs(x1 - x) > eps) { 
		x = x1;
		x1 = x1 - f(x1) / df(x1);
	}
	return x1;
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

double trap(func_t f, double a, double b, int n) {
	double s = 0, x;
	double h = (b - a) / n;
	for (x = a; x < b; x += h)
	{
		s += f(x);
	}
	s += (f(a) + f(b)) / 2;
	return h * s;
}

double parabola(func_t f, double a, double b) {
	return ((b - a) / 6)*(f(a) + 4 * f((a + b) / 2) + f(b));
}
// Lab01.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#define Q(x, n) ((x) * (x) * (1. - 2. * (n))) / (2. * ((n) + 1.))
#define FUNC(x) sqrt((x) + 1.)
#define COND(x) (x) < (-1) || (x) > 1 ? printf("error\n"): NULL

int main() {
	double a0 = 1.0, x = 0.001, s = 0.0;
	COND(x);
	for (int i = 0; i <= 25; ++i) {
		s += a0;
		a0 *= (double)Q(x, i);
	}
	double y = FUNC(x), tol = fabs(s - y);
	printf("Sum:\t\t%.7f\nControl:\t%.7f\nTolerance:\t%.7f\n", s, y, tol);
	getchar();
    return 0;
}
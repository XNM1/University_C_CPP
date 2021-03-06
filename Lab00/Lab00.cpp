// Lab00.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

float f(float b, float x) {
	float res;
	if (x == 1) {
		printf("Error");
		return 0;
	}
	else {
		res = x * tan(4. * atan(b / (1. - x)));
		return res;
	}
}


int main() {
	float b = 1.89f, x = 2.87f;
	printf("Result: %f\n", f(b, x));
	printf("Enter b: ");
	scanf("%f", &b);
	printf("Enter x: ");
	scanf("%f", &x);
	printf("Result: %f\n", f(b, x));
	getchar();
	getchar();
	return 0;
}
// Cipher of Caesar.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int main() {
	int a = 12, b = 15, c = a ^ b;
	printf("%d<=>%d\n", a, b);
	a ^= c;
	b ^= c;
	printf("%d<=>%d\n", a, b);
	//
	char d[500]; int n;
	printf("Enter shift: ");
	scanf("%d", &n);
	printf("Enter text: ");
	scanf("%s", &d);
	printf("Text: ");
	for (int i = 0; d[i] != '\0'; i++) {
		d[i] ^= n;
		printf("%c", d[i]);
	}
	getchar();
	getchar();
    return 0;
}
// HomeWork02.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

char* sum(char*, char*);
char* sub(char*, char*);
char* com(char*);

int main()
{
	char m[] = "223432523523423523542352354234238423849048230840238509237482374892378946237423647893894273849723894723894723895723";
	char n[] = "578374892374892378947238974897238947238972964923874897324897328957237489237492364972389573289749872396437562374892";
	printf("%s\n", sub(n, m));
	printf("%s\n", sum(n, m));
	getchar();
    return 0;
}

char* sum(char* a, char* b) {
	int i, carry = 0, shift;
	char *max, *min;
	if (strlen(a) > strlen(b)) {
		max = a;
		min = b;
	}
	else {
		max = b;
		min = a;
	}
	shift = strlen(max) - strlen(min);
	char* sum = (char*)calloc(strlen(max), sizeof(char));
	sum[strlen(max)] = '\0';
	for (i = strlen(max) - 1; i >= shift; --i) {
		int d1 = max[i] - '0';
		int d2 = min[i - shift] - '0';
		int s = d1 + d2 + carry;
		sum[i] = s % 10 + '0';
		carry = s / 10;
	}
	for (i = shift - 1; i >= 0; --i) {
		int d1 = max[i] - '0';
		int d2 = 0;
		int s = d1 + d2 + carry;
		sum[i] = s % 10 + '0';
		carry = s / 10;
	}
	return sum;
}

char* sub(char* a, char* b) {
	if (strlen(a) != strlen(b)) {
		return '\0';
	}
	return sum(a, com(b));
}

char* com(char* a) {
	int i;
	char* com_a = (char*)calloc(strlen(a), sizeof(char));
	com_a[strlen(a)] = '\0';
	char d[] = "1";
	for (i = 0; i < strlen(a); ++i) {
		com_a[i] = 9 - (a[i] - '0') + '0';
	}
	return sum(com_a, d);
}
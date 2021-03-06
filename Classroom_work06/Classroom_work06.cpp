// Classroom_work06.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

FILE *f;

typedef enum _MenuFile {
	CreateFile = 1,
	DeleteFile,
	ReadFile
} MenuFile;

void createf();
void delf();
void readf();

int main()
{
	MenuFile c;
	printf("1.Create File\n2.Delete File\n3.Read File\n");
	scanf("%d", &c);
	system("cls");
	switch (c)
	{
	case CreateFile:
		createf();
		break;
	case DeleteFile:
		delf();
		break;
	case ReadFile:
		readf();
		break;
	default:
		printf("Error");
		break;
	}
	getchar();
    return 0;
}

void createf() {
	char str[256];
	int w;
	printf("Enter file name: ");
	scanf("%s", str);
	if (!(f = fopen(str, "a+"))) {
		printf("Error");
		return;
	}
	system("cls");
	printf("Do you want write file? (1 - Yes, 2 - No)\n");
	scanf("%d", &w);
	if (w == 1)
	{
		system("cls");
		scanf("%s", str);
		fprintf(f, "%s", str);
		fclose(f);
		return;
	}
	else if (w == 2) {
		fclose(f);
		return;
	}
	fclose(f);
	printf("Error");
}

void delf() {
	char str[256];
	printf("Enter file name: ");
	scanf("%s", str);
	if (-1 == remove(str)) {
		printf("Error");
		return;
	}
}

void readf() {
	char str[256];
	printf("Enter file name: ");
	scanf("%s", str);
	if (!(f = fopen(str, "r"))) {
		printf("Error");
		return;
	}
	fscanf(f, "%s", str);
	printf("%s\n", str);
	fclose(f);
}
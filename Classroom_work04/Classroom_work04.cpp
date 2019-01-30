// Classroom_work04.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

int main()
{
	int i;
//#1
	{
		char word[32]; 
		int freq[256];
		gets_s(word);
		for (i = 0; i < 256; ++i) {
			freq[i] = 0;
		}
		for (i = 0; i < strlen(word); ++i) {
			++freq[word[i]];
		}
		for (i = 0; i < 256; ++i) {
			if (freq[i] != 0) {
				printf("%c: %d\n", i, freq[i]);
			}
		}
	}
//#2
	{
		char str[32];
		bool isword = 1;
		gets_s(str);
		for (i = 0; i < strlen(str); ++i) {
			if ((str[i] > 'Z' || str[i] < 'A') && (str[i] > 'z' || str[i] < 'a')) {
				isword = 0;
				break;
			}
		}
		if (isword) {
			printf("It is a word\n");
		}
		else {
			printf("It is not a word\n");
		}
	}
//#3
	{
		char text[1000];
		double freq[256];
		gets_s(text);
		for (i = 0; i < 256; ++i) {
			freq[i] = 0.0;
		}
		for (i = 0; i < strlen(text); ++i) {
			++freq[text[i]];
		}
		for (i = 0; i < 256; ++i) {
			if (freq[i] != 0.0) {
				printf("%c: %f%%\n", i, (freq[i]/strlen(text)) * 100);
			}
		}
	}
//#4
	{
		char text[1000];
		int sents = 0;
		gets_s(text);
		for (i = 0; i < strlen(text); ++i) {
			if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
				++sents;
			}
		}
		printf("Number of sentences: %d\n", sents);
	}
//#5
	{
		stack<char> stck;
		char text[1000];
		gets_s(text);
		stck.push(0);
		for (int i = 0; i < strlen(text); ++i) {
			if (text[i] == '(' || text[i] == '{' || text[i] == '[') {
				stck.push(text[i]);
			}
			if (stck.top() == '(' && text[i] == ')') {
				stck.pop();
			}
			else if (stck.top() == '{' && text[i] == '}') {
				stck.pop();
			}
			else if (stck.top() == '[' && text[i] == ']') {
				stck.pop();
			}
		}
		if (stck.top() == 0) {
			stck.pop();
			printf("Correct");
		}
		else {
			while (!stck.empty()) {
				stck.pop();
			}
			printf("Incorect");
		}
	}
	getchar();
    return 0;
}

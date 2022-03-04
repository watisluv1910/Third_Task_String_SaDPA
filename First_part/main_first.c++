#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int resizeWords(char**& array, int oldLength, int newLength);
int resizeWord(char*& array, int oldLength, int newLength);
int getSentence(char**& sentence, int& sentenceLength);
void outputTransformedSentence(char**& sentence, char**& specialWords, 
	int& sentenceLength, int& specialWordsNumber);
void invertWord(char*& array);
void outputArray(char** array, int length);

int resizeWords(char** &array, int oldLength, int newLength) {

	char** resizedArray = new char* [newLength];

	for (int i = 0; i < newLength; i++) {

		resizedArray[i] = new char[1];
	}

	for (int i = 0; i < oldLength; i++) {

		resizeWord(resizedArray[i], 1, _msize(array[i]) / sizeof(char) + 1);
		strcpy(resizedArray[i], array[i]);
	}

	delete[] array;
	array = resizedArray;

	return 1;
}

int resizeWord(char* &array, int oldLength, int newLength) {

	char* resizedArray = new char[newLength];

	for (int i = 0; i < oldLength; i++) {

		resizedArray[i] = array[i];
	}

	delete[] array;
	array = resizedArray;

	return 1;
}

int getSentence(char**& sentence, int &sentenceLength) {

	int wordLength = 1;

	char tempVar;
	tempVar = getchar();

	while (tempVar != '.' && tempVar != '?' 
		&& tempVar != '!' && tempVar != '\n') {

		if (tempVar == ' ') {

			tempVar = getchar();
		}

		else if (tempVar == ',') {

			if (sentenceLength == 1) {
				
				tempVar = getchar();
			}

			else {

				if (resizeWord(sentence[sentenceLength - 1],
					wordLength, wordLength + 1)) {

					sentence[sentenceLength - 1][wordLength - 1] = tempVar;

					wordLength++;
					tempVar = getchar();
				}

				else {

					return 0;
				}

				sentence[sentenceLength - 1][wordLength - 1] = '\0';
				wordLength = 1;

				if (resizeWords(sentence, sentenceLength, sentenceLength + 1)) {

					sentenceLength++;
				}

				else {

					return 0;
				}
			}
		}

		else {
			while (tempVar != ' ' && tempVar != ','
				&& tempVar != '.' && tempVar != '?' 
				&& tempVar != '!' && tempVar != '\n') {

				if (resizeWord(sentence[sentenceLength - 1],
					wordLength, wordLength + 1)) {

					sentence[sentenceLength - 1][wordLength - 1] = tempVar;

					wordLength++;
					tempVar = getchar();
				}

				else {

					return 0;
				}
			}

			sentence[sentenceLength - 1][wordLength - 1] = '\0';
			wordLength = 1;

			if (resizeWords(sentence, sentenceLength, sentenceLength + 1)) {

				sentenceLength++;
			}

			else {

				return 0;
			}
		}
	}

	sentenceLength--;

	return 1;
}

void outputTransformedSentence(char** &sentence, char** &specialWords, 
	int &sentenceLength, int &specialWordsNumber) {

	int lastWordLength = strlen(sentence[sentenceLength - 1]);
	
	for (int i = 0; i < sentenceLength - 1; i++) {

		if (sentence[i][0] != ',' && sentenceLength > 1) {

			if (strlen(sentence[i]) > lastWordLength) {

				invertWord(sentence[i]);
				printf_s("%s", sentence[i]);

				if (sentence[i + 1][0] != ',') {

					printf_s(" ");
				}
			}

			else if (strlen(sentence[i]) < lastWordLength) {

				resizeWord(specialWords[specialWordsNumber - 1],
					1, strlen(sentence[i]));
				strcpy(specialWords[specialWordsNumber - 1], sentence[i]);

				resizeWords(specialWords, specialWordsNumber, specialWordsNumber + 1);
				
				specialWordsNumber++;
			}

			else {

				printf_s("%s ", sentence[i]);
			}
		}

		else {

			printf_s(", ");
		}
	}

	printf_s("%s.", sentence[sentenceLength - 1]);
}

void invertWord(char*& array) {

	char* invertedArray = new char[strlen(array) + 1];

	for (int i = strlen(array) - 1; i >= 0; i--) {

		invertedArray[strlen(array) - i - 1] = array[i];
	}

	invertedArray[strlen(array)] = '\0';

	delete[] array;
	array = invertedArray;
}

void outputArray(char** array, int length) {

	for (int i = 0; i < length - 1; i++) {
		
		puts(array[i]);
	}
}

int main() {

	setlocale(LC_ALL, "Russian");

	int path = 1;

	while (path) {

		char** sentence = new char* [1];
		sentence[0] = new char[1];

		char** specialWords = new char* [1];
		specialWords[0] = new char[1];

		int sentenceLength = 1, specialWordsNumber = 1;

		printf_s("Enter the sentence:\n");

		if (!getSentence(sentence, sentenceLength) || sentenceLength <= 0) {

			printf_s("\nInput string processing error. Try again.\n");
			continue;
		}

		printf_s("\nThe transformed sentence:\n");
		outputTransformedSentence(sentence,
			specialWords, sentenceLength, specialWordsNumber);

		printf_s("\nThe list of 'special' words:\n");
		outputArray(specialWords, specialWordsNumber);

		printf_s("\nEnter <1> to restart the programm.\n"
			"Enter <0> to end the programm.\nYour choise is:\n");
		
		cin >> path;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		system("pause");
		system("cls");
	}

	return 0;
}
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "stdio.h" 

using namespace std;

int resizeWords(char**& array, int oldLength, int newLength);
int resizeWord(char*& array, int oldLength, int newLength);
void outputTransformedSentence(char**& sentence, char**& specialWords, 
	int& sentenceLength, int& specialWordsNumber);
void invertWord(char*& array);
void outputArray(char** array, int length);
int removeArrays(char**& sentence, char**& specialWords,
	int& sentenceLength, int& specialWordsNumber);

int resizeWords(char** &array, int oldLength, int newLength) {

	char** resizedArray = new char* [newLength];

	for (size_t i = 0; i < newLength; i++) {

		resizedArray[i] = new char[1];
	}

	for (size_t i = 0; i < oldLength; i++) {

		resizeWord(resizedArray[i], 1, strlen(array[i]) + 1);
		strcpy(resizedArray[i], array[i]);
	}

	delete[] array;
	array = resizedArray;

	return 1;
}

int resizeWord(char* &array, int oldLength, int newLength) {

	char* resizedArray = new char[newLength];

	memcpy(resizedArray, array, oldLength * sizeof(char));
		
	delete[] array;
	array = resizedArray;

	return 1;
}

int getSentence(char**& sentence, int &sentenceLength) {

	int wordLength = 1;

	char tempVar;
	cin.get(tempVar);

	while (tempVar != '.' && tempVar != '?' 
		&& tempVar != '!' && tempVar != '\n') {

		if (tempVar == ' ') {

			cin.get(tempVar);
		}

		else if (tempVar == ',') {

			if (sentenceLength == 1) {
				
				cin.get(tempVar);
			}

			else {

				if (resizeWord(sentence[sentenceLength - 1],
					wordLength, wordLength + 1)) {

					sentence[sentenceLength - 1][wordLength - 1] = tempVar;

					wordLength++;
					cin.get(tempVar);
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
					cin.get(tempVar);
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
}

void outputTransformedSentence(char** &sentence, char** &specialWords, 
	int &sentenceLength, int &specialWordsNumber) {

	int lastWordLength = strlen(sentence[sentenceLength - 1]);

	
	for (size_t i = 0; i < sentenceLength - 1; i++) {

		if (sentence[i][0] != ',' && sentenceLength > 1) {

			if (strlen(sentence[i]) > lastWordLength) {

				invertWord(sentence[i]);
				cout << sentence[i] << ' ';
			}

			else if (strlen(sentence[i]) < lastWordLength) {

				resizeWord(specialWords[specialWordsNumber - 1],
					1, strlen(sentence[i]));
				strcpy(specialWords[specialWordsNumber - 1], sentence[i]);

				if (i != 0) { 

					resizeWords(specialWords, specialWordsNumber, specialWordsNumber + 1);
				}
				
				specialWordsNumber++;
			}

			else {

				cout << sentence[i] << ' ';
			}
		}

		else {

			cout << ", ";
		}
	}

	cout << sentence[sentenceLength - 1] << '.' << endl;
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

	for (size_t i = 0; i < length - 1; i++) {

		puts(array[i]);
	}
}

int removeArrays(char**& sentence, char**& specialWords, 
	int& sentenceLength, int& specialWordsNumber) {

	for (size_t i = 0; i < sentenceLength; i++) {

		delete[] sentence[i];
	}

	for (size_t i = 0; i < specialWordsNumber; i++) {

		delete[] specialWords[i];
	}

	return 1;
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

		cout << "Enter the sentence:\n";

		if (!getSentence(sentence, sentenceLength) || sentenceLength <= 0) {

			cout << "\nInput string processing error. Try again.\n";
			continue;
		}

		cout << "\nThe transformed sentence:\n";
		outputTransformedSentence(sentence,
			specialWords, sentenceLength, specialWordsNumber);

		cout << "\nThe list of 'special' words:\n";
		outputArray(specialWords, specialWordsNumber);

		if (removeArrays(sentence,
			specialWords, sentenceLength, specialWordsNumber)) {

			cout << "\nEnter <1> to restart the programm.\n"
				"Enter <0> to end the programm.\nYour choise is:\n";
			cin >> path;
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		system("pause");
		system("cls");
	}

	return 0;
}
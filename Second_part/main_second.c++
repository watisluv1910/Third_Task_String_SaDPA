#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int getSentence(string& sentence);
int findLastWordLength(string& sentence);
string reverseString(string substr);
void transformSentence(string& sentence,
	string& specialWords, int lastWordLength);
bool isLetter(char coord);
void clearSentence(string& sentence);

int getSentence(string& sentence) {

	getline(cin, sentence, '\n');

	while (sentence[0] == ',' || sentence[0] == ' ') {

		sentence.erase(0, 1);
	}

	while (sentence[sentence.length() - 1] == ',' 
		|| sentence[sentence.length() - 1] == ' ' 
		|| sentence[sentence.length() - 1] == '.') {

		sentence.erase(sentence.length() - 1, 1);
	}

	return 1;
}

int findLastWordLength(string& sentence) {

	return sentence.length() - 1 - sentence.find_last_of(' ');
}

string reverseString(string substr) {

	int length = substr.length();
	int lastPosition = length - 1;

	for (size_t i = 0; i < length / 2; i++) {

		char temp = substr[i];
		substr[i] = substr[lastPosition - i];
		substr[lastPosition - i] = temp;
	}

	return substr;
}

void transformSentence(string& sentence, 
	string& specialWords, int lastWordLength) {

	int firstLetterIndex = 0;
	string substring;

	size_t sentenceLength = sentence.find_last_of(' ');
	size_t i = 0;

	while (i < sentenceLength) {

		if ((sentence[i + 1] == ',' || sentence[i + 1] == ' ') 
			&& sentence[i] != ',' && sentence[i] != ' ') {

			if (i - firstLetterIndex + 1 > lastWordLength) {

				sentence.replace(
					firstLetterIndex, i - firstLetterIndex + 1, reverseString(
						sentence.substr(
							firstLetterIndex, i - firstLetterIndex + 1)));
			}

			if (i - firstLetterIndex + 1 < lastWordLength) {

				specialWords.append(
					sentence.substr(
						firstLetterIndex, i - firstLetterIndex + 1) + " ");

				sentence.erase(firstLetterIndex, i - firstLetterIndex + 1);

				sentenceLength -= (i - firstLetterIndex + 1);
				firstLetterIndex++;
			}
		}

		else if (sentence[i] == ' ') {

			firstLetterIndex = i + 1;
		}

		i++;
	}
}

bool isLetter(char coord) {

	return (int('a') <= int(coord) && int(coord) <= int('z') 
		|| int('A') <= int(coord) && int(coord) <= int('Z')) ? true : false;
}

void clearSentence(string& sentence) {

	size_t i = 0;

	while (i < sentence.length()) {

		if (sentence[i] == sentence[i + 1] && !isLetter(sentence[i])) {

			sentence.erase(i + 1, 1);
		}

		else if (i == 0 && !isLetter(sentence[i])) {

			sentence.erase(i, 1);
		}

		else {

			i++;
		}
	}
}

int main() {

	setlocale(LC_ALL, "Russian");

	string sentence, specialWords;
	
	int path = 1;

	while (path) {

		sentence.clear();
		specialWords.clear();

		cout << "Enter the sentence:\n";

		if (!getSentence(sentence) || sentence.empty()) {

			cerr << "\nInput string processing error. Try again.\n";
			continue;
		}

		transformSentence(sentence, specialWords, findLastWordLength(sentence));

		clearSentence(sentence);

		cout << "\nThe transformed sentence:\n";
		cout << sentence  << '.' << endl;

		cout << "\nThe list of 'special' words:\n";
		cout << ((specialWords.empty()) ? "None." : specialWords) << endl;

		cout << "\nEnter <1> to restart the programm.\n"
			"Enter <0> to end the programm.\nYour choise is:\n";
		cin >> path;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		system("pause");
		system("cls");
	}

	return 0;
}
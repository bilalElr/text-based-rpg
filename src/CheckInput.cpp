#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <sstream>
#include "CheckInput.h"
#include "Display.h"
#include "Commands.h"

using namespace std;

bool checkForCommands(const string& input)
{
	if (input == "Help" || input == "Party status" || input == "Enemy party status") {
		commands.execute(input);
		return true;
	}
	if (input.size() > 5 && input.substr(input.size() - 5) == " help") {
		commands.execute(input);
		return true;
	}
	return false;
}

string formatInput(const string& userInput) {

	string toFormat = userInput;

	toFormat.erase(toFormat.begin(), find_if(toFormat.begin(), toFormat.end(),
		[](unsigned char ch) { return !isspace(ch); }));

	
	toFormat.erase(find_if(toFormat.rbegin(), toFormat.rend(),
		[](unsigned char ch) { return !isspace(ch); }).base(), toFormat.end());

	toFormat[0] = toupper(static_cast<unsigned char>(toFormat[0]));
	for (size_t i = 1; i < toFormat.size(); i++) {
		toFormat[i] = tolower(static_cast<unsigned char>(toFormat[i]));
	}
	return toFormat;
}

bool validCharacterInput(const string& userInput) {

	static const vector<string> validClasses = { "Knight", "Mage", "Archer" };

	auto correct = find(validClasses.begin(), validClasses.end(), userInput);

	if (correct != validClasses.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool validEnemyInput(const string& input)
{
	static const vector<string> validClasses = { "Goblin", "Orc", "Werewolf", "Troll"};

	auto correct = find(validClasses.begin(), validClasses.end(), input);

	if (correct != validClasses.end()) {
		return true;
	}
	else {
		return false;
	}
}

string takeInput() {

	string input = "";
	bool valid = false;

	do {
		getline(cin, input);
		input = formatInput(input);

		if (checkForCommands(input)) { continue; }

		valid = validCharacterInput(input);
		if (!valid) { cout << "Invalid input!\n"; }
	} while (!valid);

	return input;
}

string takeEnemyInput()
{
	string input = "";
	bool valid = false;

	do {
		getline(cin, input);
		input = formatInput(input);

		if (checkForCommands(input)) { continue; }

		valid = validEnemyInput(input);
		if (!valid) { cout << "Invalid input!\n"; }
	} while (!valid);

	return input;
}

int takeInt() {
	string input = "";
	int value = 0;
	bool isValid = false;

	do {
		getline(cin, input);

		bool isNumber = !input.empty() && all_of(input.begin(), input.end(), ::isdigit);
		if (!isNumber) {
			string formatted = formatInput(input);

			if (checkForCommands(formatted)) { continue; }
			if (formatted == "Back") {
				return -1;
			}
		}

		stringstream ss(input);
		if (ss >> value && ss.eof()) {
			isValid = true;
		}
		else {
			cout << "Invalid input. Please enter a valid integer." << endl;
		}
	} while (!isValid);

	return value;
}

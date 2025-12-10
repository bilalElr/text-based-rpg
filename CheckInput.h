#pragma once

#include <string>

using namespace std;

bool validCharacterInput(const string& input);
bool validEnemyInput(const string& input);
string formatInput(const string& input);
bool checkForCommands(const string& input);
string takeInput();
string takeEnemyInput();
int takeInt();
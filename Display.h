#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class Entity;
class Enemy;
class Character;

using namespace std;

class Display
{
public:

	static void showCharacterDetails(const Character& c);
	static void showEnemyDetails(const Enemy& e);
	void showPartyStatus(const vector<unique_ptr<Character>>& p);
	void showEnemyPartyStatus(const vector<unique_ptr<Enemy>>& p);
	static void showHelp();

	void skipStory(const string& prompt);
	void intro();

private:
	bool skipStory_;
	void tempoMessage(const string& message, int delayMs);
	void pressEnter();
};
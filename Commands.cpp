#include "Commands.h"
#include <algorithm>
#include <iostream>

using namespace std;

Commands::Commands(Display& d, vector<unique_ptr<Character>>& c, vector<unique_ptr<Enemy>>& e):
	display_(d), party_(c), enemies_(e)
{
}

void Commands::execute(const string& input)
{
	string poop = formatInput(input);
	if (poop.empty()) { return; }

    if (poop == "Help") {
        display_.showHelp();
    }
    else if (poop == "Party status") {
        display_.showPartyStatus(party_);
    }
    else if (poop == "Enemy party status") {
        display_.showEnemyPartyStatus(enemies_);
    }
    else {
        for (auto& c : party_) {
            string type = c->getType();
            string expected = type + " help";
            if (input == expected) {
                display_.showCharacterDetails(*c);
                return;
            }
        }
        for (auto& e : enemies_) {
            string type = e->getType();
            string expected = type + " help";
            if (input == expected) {
                display_.showEnemyDetails(*e);
                return;
            }
        }
    }
}

void Commands::showCharacterInfo(const string& name)
{
    for (auto& c : party_) {
        if (c->getType() == name) {
            display_.showCharacterDetails(*c);
            return;
        }
    }
}

void Commands::showEnemyInfo(const string& name)
{
    for (auto& e : enemies_) {
        if (e->getType() == name) {
            display_.showEnemyDetails(*e);
            return;
        }
    }
}

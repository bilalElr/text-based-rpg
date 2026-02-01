#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Display.h"
#include "Character.h"
#include "Enemy.h"
#include "CheckInput.h"

using namespace std;


class Commands
{
public:
    Commands(Display& d, vector<unique_ptr<Character>>& c,vector<unique_ptr<Enemy>>& e);

    void execute(const string& input);

private:
    Display& display_;
    vector<unique_ptr<Character>>& party_;
    vector<unique_ptr<Enemy>>& enemies_;

    void showCharacterInfo(const string& name);
    void showEnemyInfo(const string& name);
};
extern Commands commands;
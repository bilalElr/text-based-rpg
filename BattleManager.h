#pragma once

#include <vector>
#include <utility>
#include <memory>
#include <string>
#include <iostream>
#include "Character.h"
#include "Enemy.h"
#include "Display.h"
#include "CheckInput.h"
#include "Rng.h"

using namespace std;

struct EnemySpawnInfo {
	string type;
	int count;
};

class BattleManager
{
public:
	
	BattleManager(vector<unique_ptr<Character>>& party, vector<unique_ptr<Enemy>>& enemy);

	void startParty();
	void startEnemies(const vector<pair<string, int>>& enemiesToSpawn);

	void battle();
	bool battleOver() const;
	bool allCharactersDead() const;
	void healParty(int amount);

	//vector<unique_ptr<Character>> makeCheckpoint(vector<unique_ptr<Character>>& currentParty);

	const vector<unique_ptr<Character>>& getParty() const;
	const vector<unique_ptr<Enemy>>& getEnemyParty() const;

private:
	Character* getRandomAlive();
	Enemy* getRandomEnemy();
	void spawnEnemies(const vector<EnemySpawnInfo>& wave);

	void playerTurn();
	void enemyTurn();

	template <typename T>
	T* chooseAliveEntity(const vector<unique_ptr<T>>& group, const string& prompt);
	void processDebuffsChar();
	void processDebuffsEnemy();
	void ProcessCooldowns();
	int getPlayerAttackChoice(Character* c, int turnCounter);
	bool attickWillHit(Entity* attacker, Entity* target);
	void executePlayerAttack(Character* activeChar, Enemy* target, int attackChoice);
	void removeDeadEnemies();
	void enemyAttack(Enemy* e, Character* c);

	bool allEnemiesDead() const;

private:
	vector<unique_ptr<Character>>& party_;
	vector<unique_ptr<Enemy>>& enemyParty_;
	int turnCounter_ = 1;
};

template <typename T>
T* BattleManager::chooseAliveEntity(const vector<unique_ptr<T>>& group, const string& prompt)
{
    Display display;
	if constexpr (is_same_v<T, Character>) {
		display.showPartyStatus(group);
	}
	else if constexpr (is_same_v<T, Enemy>) {
		display.showEnemyPartyStatus(group);
	}
    
    string choice = "";
    T* selected = nullptr;

    do {
        cout << endl << prompt;
		if constexpr (is_same_v<T, Character>) {
			choice = takeInput();
		}
		else if constexpr (is_same_v<T, Enemy>) {
			choice = takeEnemyInput();
		}
      
        for (const unique_ptr<T>& t : group) {
            if (t->getType() == choice && t->getAlive()) {
				selected = t.get();
                break;
            }
        }

        if (!selected) {
            cout << "Invalid choice or target is down. Try again.\n";
        }

    } while (!selected);

    return selected;
}

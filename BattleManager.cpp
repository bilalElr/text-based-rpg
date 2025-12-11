#include "BattleManager.h"
#include "Entity.h"
#include "Character.h"
#include "CheckInput.h"
#include "Mage.h"
#include "Archer.h"
#include "Knight.h"
#include "Goblin.h"
#include "Orc.h"
#include "Werewolf.h"
#include "Troll.h"
#include "Display.h"
#include <memory>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

BattleManager::BattleManager(vector<unique_ptr<Character>>& party, vector<unique_ptr<Enemy>>& enemy) :
    party_(party), enemyParty_(enemy)
{
}

void BattleManager::spawnEnemies(const vector<EnemySpawnInfo>& wave)
{
    for (const EnemySpawnInfo& info : wave) {
        for (int i = 0; i < info.count; i++) {
            if (info.type == "Goblin") {
                enemyParty_.push_back(make_unique<Goblin>());
            }
            else if (info.type == "Orc") {
                enemyParty_.push_back(make_unique<Orc>());
            }
            else if (info.type == "Werewolf") {
                enemyParty_.push_back(make_unique<Werewolf>());
            }
            else if (info.type == "Troll") {
                enemyParty_.push_back(make_unique<Troll>(60));
            }
        }
    }
}

void BattleManager::startParty()
{
    party_.clear();
    party_.push_back(make_unique<Mage>());
    party_.push_back(make_unique<Archer>());
    party_.push_back(make_unique<Knight>());

    for (auto& c : party_) {
        c->setPartyPointer(&party_);
    }

    Display display;
    for (const unique_ptr<Character>& c : party_) {
        display.showCharacterDetails(*c);
    }
}

void BattleManager::startEnemies(const vector<pair<string, int>>& enemiesToSpawn)
{
    enemyParty_.clear();
    vector<EnemySpawnInfo> wave;
    for (const auto& p : enemiesToSpawn) {
        wave.push_back({ p.first, p.second });
    }
    spawnEnemies(wave);
    Display display;
    display.showEnemyPartyStatus(enemyParty_);
}

const vector<unique_ptr<Character>>& BattleManager::getParty() const
{
    return party_;
}

const vector<unique_ptr<Enemy>>& BattleManager::getEnemyParty() const
{
    return enemyParty_;
}

Character* BattleManager::getRandomAlive()
{
    vector<Character*> alive;
    for (unique_ptr<Character>& c : party_) {
        if (c->getAlive()) {
            alive.push_back(c.get());
        }
    }
    if (alive.empty()) { return nullptr; }

    int index = randomNumberGenerator(0, static_cast<int>(alive.size()) - 1);
    return alive[index];
}

Enemy* BattleManager::getRandomEnemy()
{
    vector<Enemy*> enemyAlive;
    for (unique_ptr<Enemy>& e : enemyParty_) {
        if (e->getAlive()) {
            enemyAlive.push_back(e.get());
        }
    }
    if (enemyAlive.empty()) { return nullptr; }
    int index = randomNumberGenerator(0, static_cast<int>(enemyAlive.size()) - 1);
    return enemyAlive[index];
}

void BattleManager::playerTurn()
{
    cout << "\n===== PLAYER TURN (" << (turnCounter_) << ") =====";
    processDebuffsChar();
    ProcessCooldowns();
    Display display{};
    display.showEnemyPartyStatus(enemyParty_);

    Character* activeChar = chooseAliveEntity<Character>(party_, "Choose which character to play: ");

    int choice = 0;
    while (true) {
        choice = getPlayerAttackChoice(activeChar, turnCounter_);
        if (choice == -1) {
            activeChar = chooseAliveEntity<Character>(party_, "Choose which character to play: ");
            continue;
        }
        break;
    }

    Enemy* toAttack = chooseAliveEntity<Enemy>(enemyParty_, "Choose an enemy to target: ");

    executePlayerAttack(activeChar, toAttack, choice);

    removeDeadEnemies();
}

void BattleManager::processDebuffsChar()
{
    for (const unique_ptr<Character>& c : party_) {
        if (c->getAlive()) {
            c->processDebuffs();
        }
    }
}

void BattleManager::processDebuffsEnemy()
{
    for (const unique_ptr<Enemy>& e : enemyParty_) {
        if (e->getAlive()) {
            e->processDebuffs();
        }
    }
}

void BattleManager::ProcessCooldowns()
{
    for (unique_ptr<Character>& c : party_) {
        if (c->getAlive()) {
            c->decrementCooldown();
        }
    }
}

int BattleManager::getPlayerAttackChoice(Character* c, int turnCounter)
{
    int choice = 0;

    while (true) {
        cout << "\n1. Light Attack: " << c->getLightDmg() << "dmg ";
        if (c->getLightCooldownRemaining() > 0) {
            cout << " (Cooldown: " << c->getLightCooldownRemaining() << ")";
        }
        cout << "\n2. Heavy Attack: " << c->getHeavyDmg() << "dmg ";
        if (c->getHeavyCooldownRemaining() > 0) {
            cout << " (Cooldown: " << c->getHeavyCooldownRemaining() << ")";
        }
        cout << "\n3. Ultimate (available from turn 5)\n";

        cout << "Enter choice (1-3): ";
        choice = takeInt();
        if (choice == -1) { return -1; }

        switch (choice) {
        case 1:
            if (c->getLightCooldownRemaining() == 0) {
                return 1;
            }
            cout << "Light attack is on cooldown!\n";
            break;
        case 2:
            if (c->getHeavyCooldownRemaining() == 0) {
                return 2;
            }
            cout << "Heavy attack is on cooldown!\n";
            break;
        case 3:
            if (turnCounter >= 5 && !c->getUltUsed()) {
                return 3;
            }
            cout << "Ultimate not available until turn 5 or already used!\n";
            break;
        default:
            cout << "Invalid choice. Please enter 1-3.\n";
            break;
        }
    }
}

bool BattleManager::attickWillHit(Entity* attacker, Entity* target)
{
    int hitChance = 100;
    for (const Debuff& d : attacker->getDebuffs()) {
        if (d.type == Debuff::Dazed) {
            hitChance /= 2;
            break;
        }
    }
    return randomNumberGenerator(1, 100) <= hitChance;
}

void BattleManager::executePlayerAttack(Character* attacker, Enemy* target, int attackChoice)
{
    cout << "\n===== PLAYER ATTACK SUMMARY =====\n";
    if (!attickWillHit(attacker, target)) {
        cout << attacker->getType() << " 's attack missed!\n";
        return;
    }

    switch (attackChoice) {
    case 1:
        cout << attacker->getType() << " used Light Attack on " << target->getType() << "!\n";
        attacker->light(*target);
        attacker->resetLightCooldown();
        break;

    case 2:
        cout << attacker->getType() << " used Heavy Attack on " << target->getType() << "!\n";
        attacker->heavy(*target);
        attacker->resetHeavyCooldown();
        break;

    case 3:
        cout << attacker->getType() << " used their Ultimate on " << target->getType() << "!\n";
        attacker->ultimate(*target, party_);
        break;
        
    default:
        cout << "Error: Invalid attack choice.\n";
    }
}

void BattleManager::removeDeadEnemies()
{
    enemyParty_.erase(
        remove_if(enemyParty_.begin(), enemyParty_.end(),
            [](const unique_ptr<Enemy>& e) {
                return !e->getAlive();
            }),
        enemyParty_.end()
    );
}

void BattleManager::enemyAttack(Enemy* e, Character* c)
{
    if (randomNumberGenerator(1, 100) <= 70) {
        cout << c->getType() << " has been attacked by: " << e->getType() << "!\n";
        e->atk1(*c);
    }
    else {
        cout << c->getType() << " has been attacked by: " << e->getType() << "!\n";
        e->atk2(*c);
    }
}

void BattleManager::enemyTurn()
{
    cout << "\n===== ENEMY TURN =====\n";
    processDebuffsEnemy();
    removeDeadEnemies();

    if (allEnemiesDead()) {
        return;
    }

    Enemy* willAttack = getRandomEnemy();
    if (!willAttack) {
        return;
    }
    Character* willBeAttacked = getRandomAlive();
    if (!willBeAttacked) {
        return;
    }

    enemyAttack(willAttack, willBeAttacked);
    removeDeadEnemies();
}

void BattleManager::battle()
{
    cout << "\n============== BATTLE START ==============";

    turnCounter_ = 1;
    for (unique_ptr<Character>& c : party_) {
        c->setCooldownsToZero();
        c->setUltUsed(false);
    }

    while (true) {
        
        playerTurn();

        if (allEnemiesDead()) {
            cout << "\nGreat job! Your party emerges victorious!\n";
            cout << "The battle lasted " << (turnCounter_) << " turns.\n";
            break;
        }
        if (allCharactersDead()) {
            cout << "\nYou have lost the battle!\n";
            break;
        }
        enemyTurn();

        if (allCharactersDead()) {
            cout << "\nYou have lost the battle!\n";
            break;
        }
        if (allEnemiesDead()) {
            cout << "\nGreat job! Your party emerges victorious!\n";
            cout << "The battle lasted " << (turnCounter_) << " turns.\n";
            break;
        }
        turnCounter_++;
    }
    cout << "\n=============== BATTLE END ===============";
}

bool BattleManager::battleOver() const
{
    return party_.empty() || enemyParty_.empty();
}

bool BattleManager::allEnemiesDead() const
{
    return enemyParty_.empty();
}

bool BattleManager::allCharactersDead() const
{
    for (const unique_ptr<Character>& c : party_) {
        if (c->getAlive()) {
            return false;
        }
    }
    return true;
}

void BattleManager::healParty(int amount)
{
    for (unique_ptr<Character>& c : party_) {
        c->setHealth(c->getHealth() + amount);
    }
}

//vector<unique_ptr<Character>> BattleManager::makeCheckpoint(vector<unique_ptr<Character>>& currentParty)
//{
//    vector<unique_ptr<Character>> checkpoint;
//    checkpoint.reserve(currentParty.size());
//
//    for (unique_ptr<Character>& c : currentParty) {
//        checkpoint.push_back(c->clone());
//    }
//    return checkpoint;
//}

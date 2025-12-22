#pragma once

#include "Rng.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

struct Debuff {
	enum Type { Dazed, Bleeding, Petrified } type;
	int remainingTurns;
};


class Entity
{
public:

	Entity(const string& type, int health, int maxHealth);
	virtual ~Entity() = default;

	int getHealth() const;
	void setHealth(int health);
	int getMaxHealth() const;
	string getType() const;
	bool getAlive() const;
	bool setAlive(bool isAlive);
	bool getDebuffStatus() const;
	string getDebuff() const;
	const vector<Debuff>& getDebuffs() const;
	bool hasDebuff(Debuff::Type type) const;
	static int getnEntities();
	void applyDebuff(Debuff::Type type, int turns);
	void processDebuffs();

	void takeDamage(int dmg);
	void revive(int healthDivider);
	bool dodged();
	bool getIgnoreDodge() const;
	void setIgnoreDodge(bool value);

protected:
	int health_, maxHealth_;
	bool isAlive_;
	bool isDazed_, isPetrified_;
	string type_;
	bool ignoreDodge_ = false;
	vector<Debuff> debuffs_;

private:
	static int nEntities_;
};
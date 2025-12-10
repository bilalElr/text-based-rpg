#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "Entity.h"

using namespace std;

class Enemy;

class Character : public Entity
{
public:

	Character(const string& type, int health, int maxHealth,
		int light, int heavy, int ult,
		int lightCool, int heavyCool);
	virtual ~Character();

	virtual int getLightDmg() const = 0;
	virtual int getHeavyDmg() const = 0;
	virtual int getUltDmg() const = 0;
	virtual void light(Enemy& e) = 0;
	virtual void heavy(Enemy& e) = 0;
	virtual void ultimate(Enemy& e, vector<unique_ptr<Character>>& p) = 0;

	virtual string getUltDescription() const = 0;

	int getLightCool() const;
	int getHeavyCool() const;
	bool getUltUsed() const;

	int getLightCooldownRemaining() const;
	int getHeavyCooldownRemaining() const;
	void resetLightCooldown();
	void resetHeavyCooldown();
	void setCooldownsToZero();

	void decrementCooldown();

	const vector<unique_ptr<Character>>& getParty() const;
	void setPartyPointer(vector<unique_ptr<Character>>* partyPointer);

protected:
	int lightDmg_, heavyDmg_, ultDmg_;
	int lightCooldown_, heavyCooldown_;
	int lightCooldownRemaining_ = 0;
	int heavyCooldownRemaining_ = 0;
	bool ultUsed_;
	vector<unique_ptr<Character>> party_;
	vector<unique_ptr<Character>>* partyPointer_ = nullptr;

private:
	static int nPartyMembers_;
};
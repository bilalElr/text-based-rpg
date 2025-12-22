#include <string>
#include <iostream>
#include <cmath>
#include "Entity.h"

using namespace std;

int Entity::nEntities_ = 0;

int Entity::getnEntities()
{
	return nEntities_;
}

void Entity::applyDebuff(Debuff::Type type, int turns)
{
    if (type == Debuff::Dazed) { isDazed_ = true; }
    if (type == Debuff::Petrified) { isPetrified_ = true; }
    debuffs_.push_back(Debuff{ type, turns });
}

void Entity::processDebuffs()
{
    for (size_t i = 0; i < debuffs_.size(); )
    {
        Debuff& deb = debuffs_[i];
        switch (deb.type) {
        case Debuff::Bleeding:
            setIgnoreDodge(true);
            takeDamage(20);
            setIgnoreDodge(false);
            break;

        case Debuff::Dazed:
            cout << type_ << " is dazed, they are 50% more likely to miss an attack!\n";
            break;
        case Debuff::Petrified:
            cout << endl << type_ << " is petrified and cannot be used for " << deb.remainingTurns << " turn(s)!\n";
        }
        deb.remainingTurns--;

        if (deb.remainingTurns <= 0) {
            if (deb.type == Debuff::Dazed) {
                isDazed_ = false;
            }
            if (deb.type == Debuff::Petrified) {
                isPetrified_ = false;
            }
            debuffs_.erase(debuffs_.begin() + i);
        }
        else {
            i++;
        }
    }
}

Entity::Entity(const string& type, int health, int maxHealth) : 
    type_(type),
    health_(health),
    maxHealth_(maxHealth),
    isAlive_(true),
    isDazed_(false),
    isPetrified_(false)
{
    nEntities_++;
}

int Entity::getHealth() const
{
	return health_;
}

void Entity::setHealth(int health)
{
    health_ = health;
}

int Entity::getMaxHealth() const
{
	return maxHealth_;
}

string Entity::getType() const
{
	return type_;
}

bool Entity::getAlive() const
{
	return isAlive_;
}

bool Entity::setAlive(bool isAlive)
{
    return isAlive_ = isAlive;
}

bool Entity::getDebuffStatus() const
{
    return debuffs_.empty();
}

string Entity::getDebuff() const
{
	int statusCode = 0;
	string status = "";

	if (hasDebuff(Debuff::Dazed)) {
		statusCode += 1;
	}
	if (hasDebuff(Debuff::Bleeding)) {
		statusCode += 2;
	}
    if (hasDebuff(Debuff::Petrified)) {
        statusCode += 5;
    }
	if (!isAlive_) {
		return "Downed";
	}
	switch (statusCode) {
	case 0:
		status = "Healthy";
		break;
	case 1:
		status = "Dazed";
		break;
	case 2:
		status = "Bleeding";
		break;
	case 3:
		status = "Dazed & Bleeding";
		break;
    case 5:
        status = "Petrified";
        break;
    case 6:
        status = "Dazed & Petrified";
        break;
    case 7:
        status = "Bleeding & Petrified";
	}
	return status;
}

const vector<Debuff>& Entity::getDebuffs() const
{
	return debuffs_;
}

bool Entity::hasDebuff(Debuff::Type type) const
{
    for (const Debuff& d : debuffs_) {
        if (d.type == type) {
            return true;
        }
    }
    return false;
}

void Entity::takeDamage(int dmg)
{
    if (!ignoreDodge_ && dodged()) {
        cout << getType() << " dodged the attack!" << endl;
        return;
    }

    bool crit = (randomNumberGenerator(1, 400) <= 25);
    if (crit) { 
        dmg = static_cast<int>(ceil(dmg * 1.5));
        cout << "Critical hit!\n";
    }

    if (dmg >= health_) {
		health_ = 0;
		isAlive_ = false;
        cout << endl << getType() << " takes " << dmg << " damage.";
		cout << "\n" << getType() << " has been defeated!\n";
    }
    else {
		health_ -= dmg;
        cout << endl << getType() << " takes " << dmg << " damage ";
        if (hasDebuff(Debuff::Bleeding)) {
            cout << "(from bleeding).\n";
        }
        cout << "\nremaining HP: " << health_ << endl;
    }
}

void Entity::revive(int healthDivider)
{
    isAlive_ = true;
    health_ = maxHealth_ / healthDivider;
    cout << type_ << " has been revived with " << health_ << " HP!" << endl;
}

bool Entity::dodged()
{
    if (isDazed_ || isPetrified_) { return false; }
	return randomNumberGenerator(1, 100) <= 10;
}

bool Entity::getIgnoreDodge() const
{
	return ignoreDodge_;
}

void Entity::setIgnoreDodge(bool value)
{
	ignoreDodge_ = value;
}

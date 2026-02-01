#include "Character.h"
#include "Entity.h"
#include "Enemy.h"

using namespace std;

int Character::nPartyMembers_ = 0;

Character::Character(const string& type, int health, int maxHealth,
    int light, int heavy, int ult,
    int lightCool, int heavyCool)
    : Entity(type, health, maxHealth),
    lightDmg_(light),
    heavyDmg_(heavy),
    ultDmg_(ult),
    lightCooldown_(lightCool),
    heavyCooldown_(heavyCool),
    ultUsed_(false),
    partyPointer_(nullptr)
{
    nPartyMembers_++;
}

Character::~Character()
{
    nPartyMembers_--;
}


int Character::getLightCool() const
{
    return lightCooldown_;
}

int Character::getHeavyCool() const
{
    return heavyCooldown_;
}

bool Character::getUltUsed() const
{
    return ultUsed_;
}

int Character::getLightCooldownRemaining() const
{
    return lightCooldownRemaining_;
}

int Character::getHeavyCooldownRemaining() const
{
    return heavyCooldownRemaining_;
}

void Character::resetLightCooldown()
{
    lightCooldownRemaining_ = lightCooldown_;
}

void Character::resetHeavyCooldown()
{
    heavyCooldownRemaining_ = heavyCooldown_;
}

void Character::setCooldownsToZero()
{
    lightCooldownRemaining_ = 0;
    heavyCooldownRemaining_ = 0;
}

void Character::setUltUsed(bool status)
{
    ultUsed_ = status;
}

void Character::decrementCooldown()
{
    if (lightCooldownRemaining_ > 0) lightCooldownRemaining_--;
    if (heavyCooldownRemaining_ > 0) heavyCooldownRemaining_--;
}

void Character::setPartyPointer(vector<unique_ptr<Character>>* partyPointer)
{
    partyPointer_ = partyPointer;
}
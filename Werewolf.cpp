#include "werewolf.h"

using namespace std;

Werewolf::Werewolf():
	Enemy(350, 350, "Werewolf", false, 25, 35)
{
}

void Werewolf::atk1(Character& c)
{
	c.takeDamage(25);
	if (randomNumberGenerator(1, 100) <= 10) {
		c.applyDebuff(Debuff::Bleeding, 2);
		cout << getAttack1() << " inflicted bleeding for 2 turns!\n";
	}
}

void Werewolf::atk2(Character& c)
{
	c.takeDamage(35);
	if (randomNumberGenerator(1, 100) <= 15) {
		c.applyDebuff(Debuff::Bleeding, 2);
		cout << getAttack2() << " inflicted bleeding for 2 turns!\n";
	}
}

int Werewolf::getAtk1() const
{
	return atk1_;
}

int Werewolf::getAtk2() const
{
	return atk2_;
}

string Werewolf::getAttack1() const
{
	return "Claw";
}

string Werewolf::getAttack2() const
{
	return "Bite";
}

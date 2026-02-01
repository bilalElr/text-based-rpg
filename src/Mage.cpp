#include "Mage.h"
#include <algorithm>

using namespace std;


Mage::Mage():
	Character("Mage", 300, 300, 15, 25, 0, 1, 3)
{
	lightCooldown_ = 1;
	heavyCooldown_ = 3;
}

void Mage::ultimate(Enemy& e, vector<unique_ptr<Character>>& party)
{
	bool willRevive = false;
	vector<Character*> temp;
	for (unique_ptr<Character>& character : party) {
		if (!character->getAlive()) {
			willRevive = true;
			cout << character->getType() << " is down!" << endl;
			temp.push_back(character.get());
		}
	}

	if (willRevive) {
		bool valid = false;
		string whoRevived = "";
		
		do {
			cout << "Enter the name of the character you want to revive: ";
			whoRevived = takeInput();
			for (Character* c : temp) {
				if (c->getType() == whoRevived) {
					valid = true;
					break;
				}
			}
			if (!valid) {
				cout << "Invalid choice. Please type the name of a downed character: ";
			}
		} while (!valid);

		auto toRevive = find_if(temp.begin(), temp.end(),
			[&whoRevived](Character* c) { 
			return c->getType() == whoRevived; });
		
		if (toRevive != temp.end()) {
			(*toRevive)->revive(2);
		}
	}
	for_each(party.begin(), party.end(), [this](unique_ptr<Character>& c) {
		heal(*c, c->getMaxHealth()/2);
		});
	ultUsed_ = true;
}

void Mage::light(Enemy& e)
{
	e.takeDamage(15);
}

void Mage::heavy(Enemy& e)
{
	e.takeDamage(25);

	vector<Character*> aliveAllies;
	for (const unique_ptr<Character>& c : *partyPointer_) {
		if (c->getAlive()) {
			aliveAllies.push_back(c.get());
		}
	}
	if (aliveAllies.empty()) { return; } //safety measure but shouldnt happen

	//find who has lowest health and heal them
	auto findLowestHealth = min_element(aliveAllies.begin(), aliveAllies.end(), [](Character* a, Character* b) {
		double percentA = static_cast<double>((a->getHealth()) / a->getMaxHealth());
		double percentB = static_cast<double>((b->getHealth()) / b->getMaxHealth());
		return percentA < percentB;
	});
	double lowestHealth = static_cast<double>(((*findLowestHealth)->getHealth()) / (*findLowestHealth)->getMaxHealth());

	vector<Character*> lowestHealthAllies;	//in case 2 chars have equal health, this allows me to heal a random one
	for (Character* c : aliveAllies) {
		double percent = static_cast<double>((c->getHealth()) / c->getMaxHealth());
		if (percent == lowestHealth) {
			lowestHealthAllies.push_back(c);
		}
	}
	if (lowestHealthAllies.empty()) { return; } //safety measure but shouldnt happen

	Character* toHeal = nullptr;
	if (lowestHealthAllies.size() == 1) {
		toHeal = lowestHealthAllies[0];
	}
	else {
		int random = randomNumberGenerator(0, static_cast<int>(lowestHealthAllies.size()) - 1);
		toHeal = lowestHealthAllies[random];
	}
	heal(*toHeal, 40);
}

int Mage::getLightDmg() const
{
	return lightDmg_;
}

int Mage::getHeavyDmg() const
{
	return heavyDmg_;
}

int Mage::getUltDmg() const
{
	return 0;
}

string Mage::getUltDescription() const
{
	return "The ultimate ability will revive one downed character and restore half of their HP. Everyone gains 100HP.\n";
}

void Mage::heal(Character& target, int amount)
{
	if (!target.getAlive()) {
		cout << target.getType() << " is down and cannot be healed!" << endl;
		return;
	}
	int oldHP = target.getHealth();
	int newHP = target.getHealth() + amount;
	if (newHP > target.getMaxHealth()) {
		newHP = target.getMaxHealth();
	}
	target.setHealth(newHP);
	int healed = newHP - oldHP;
	cout << "Mage heals " << target.getType() << " for " << healed << " HP!\n";
	cout << target.getType() << " now has " << newHP << " HP!" << endl;
}

//unique_ptr<Character> Mage::clone() const
//{
//	return make_unique<Mage>(*this);
//}


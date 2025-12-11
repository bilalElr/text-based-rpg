#include <iostream>
#include <memory>
#include <string>
#include "Mage.h"
#include "Archer.h"
#include "Knight.h"
#include "Goblin.h"
#include "Orc.h"
#include "Werewolf.h"
#include "CheckInput.h"
#include "Rng.h"
#include "Display.h"
#include "BattleManager.h"
#include "Commands.h"

using namespace std;

Display display;
vector<unique_ptr<Character>> party;
vector<unique_ptr<Enemy>> enemy;
Commands commands(display, party, enemy);

int main() {
	
	cout << "(You can type 'help' at any time during a battle to see the available commands)\n";
	cout << "Please do not hit the enter key unless you're asked to otherwise it skips a lot of stuff.\n"
		<< "I tried dealing with it but nothing worked. So just one enter at a time, thanks :)\n";
	display.intro();
	cout << "You're out on your first expedition when you see a goblin eating the remains of what seems to be a mangled corpse.\n";
	cout << "Excited to finally get some monster blood on your hands, you make your presence known to him.\n";
	cout << "Despite being a lone goblin, he will not go down without a fight.\n";
	display.pressEnter();

	BattleManager bm(party, enemy);

	do {
		bm.startParty();
		bm.startEnemies({ {"Goblin", 1} });
		bm.battle();
		//if (bm.allCharactersDead()) { cout << "Reload to start of battle?\n"; }
		display.pressEnter();
	} while (!bm.battleOver());

	cout << "Barely sweating, you move forward, eager to keep killing whatever creatures dare to challenge you.\n";
	cout << "The night approaches, the moon glowing and being the only source of light to guide you on your path.\n";
	cout << "All of a sudden, you hear a howl coming from a nearby cave. You're greeted by a large werewolf, "
		<< "teeth and fangs sharper than your blades...\n";
	cout << "The stench of the dead goblin attracted some of his friends, this battle will be a tough one.\n"
		<< "Your next battle begins!\n";	
	display.pressEnter();

	//vector<unique_ptr<Character>> checkpoint = bm.makeCheckpoint(bm.getParty());

	do {
		bm.startEnemies({ {"Werewolf", 1}, {"Goblin", 2} });
		bm.battle();
		//if (bm.allCharactersDead()) { cout << "Reload to start of battle?\n"; }
		display.pressEnter();
	} while (!bm.battleOver());

	cout << "Exhausted after a long and boring fight because i dont know how to make good gameplay,\n"
		<< "You decide to make a campfire and sleep for however long the night lasts. Your HP slightly recovers.\n";
	display.pressEnter();
	bm.healParty(50);
	cout << "You wake up and keep moving forward, because this is all that you can do in these trying times.\n"
		<< "You encounter what seems to be an orc camp...only it is mostly empty..?\n"
		<< "You count 2 orcs guarding the entrance and decide to take them out\n";
	display.pressEnter();

	do {
		bm.startEnemies({ {"Orc", 2} });
		bm.battle();
		//if (bm.allCharactersDead()) { cout << "Reload to start of battle?\n"; }
		display.pressEnter();
	} while (!bm.battleOver());

	cout << "\nTo be continued...";

	return 0;
}
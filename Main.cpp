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
	bm.startParty();
	bm.startEnemies({ {"Goblin", 1} });
	bm.battle();

	return 0;
}
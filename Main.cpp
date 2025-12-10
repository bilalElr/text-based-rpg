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
	
	display.intro();

	cout << "intro skipped";

	BattleManager bim(party, enemy);
	bim.startParty();
	bim.startEnemies({ {"Goblin", 1} });
	bim.battle();
	cout << "\nmade it to the end of main\n";

	return 0;
}
#include "Display.h"
#include "Character.h"
#include "Enemy.h"
#include <string>
#include <chrono>
#include <thread>

using namespace std;

void Display::showCharacterDetails(const Character& c)
{
	cout << "\n====================== " << c.getType() << " Details ======================" << endl;

	cout << "Character type: " << c.getType() << endl
		<< "Character health: " <<  c.getHealth() << "/" << c.getMaxHealth() << " HP." << endl
		<< "Light attacks deal " << c.getLightDmg() << " damage and can be used every " << c.getLightCool() << " turn(s)."
		<< "Heavy attacks deal " << c.getHeavyDmg() << " damage and can be used every " << c.getHeavyCool() << " turn(s)."
		<< c.getUltDescription()
	    << "Status: " << c.getDebuff() << endl;
	cout << "===========================================================\n";
}

void Display::showEnemyDetails(const Enemy& e)
{
	cout << "\n====================== " << e.getType() << " Details ======================" << endl;

	cout << "Enemy type: " << e.getType() << endl
		<< "Enemy health: " << e.getHealth() << "/" << e.getMaxHealth() << " HP." << endl
		<< "Light attack (" << e.getAttack1() << ") deals " << e.getAtk1() << " damage." << endl
		<< "Heavy attack (" << e.getAttack2() << ") deals " << e.getAtk2() << " damage." << endl
		<< "Status: " << e.getDebuff() << endl;
	cout << "===========================================================\n";
}

void Display::showPartyStatus(const vector<unique_ptr<Character>>& p)
{
	cout << "\nParty Status:\n\n";
	for (const unique_ptr<Character>& c : p) {
		cout << c->getType() << "(" << c->getHealth() << "/" << c->getMaxHealth() << ")"
			<< "[" << c->getDebuff() << "]" << endl;
	}
}

void Display::showEnemyPartyStatus(const vector<unique_ptr<Enemy>>& p)
{
	cout << "\nEnemy Party Status:\n\n";
	for (const unique_ptr<Enemy>& e : p) {
		cout << e->getType() << "(" << e->getHealth() << "/" << e->getMaxHealth() << ")"
			<< "[" << e->getDebuff() << "]" << endl;
	}
}

void Display::showHelp()
{
	cout << "\n====================== HELP MENU ======================\n";
	cout << "Commands available:\n";
	cout << "  help                 - Show this help menu\n";
	cout << "  back                 - Go back to picking another character\n";
	cout << "  party status         - Show the status of all party members\n";
	cout << "  enemy party status   - Show the status of all enemies\n";
	cout << "  <character> help     - Show details about a specific character\n";
	cout << "  <enemy> help         - Show details about a specific enemy\n";
	cout << "\nStatus effects:\n";
	cout << "  bleeding             - Lose 20HP per turn\n";
	cout << "  dazed                - Increased chance to miss attacks\n";
	cout << "  dodge                - 10% chance to dodge attacks (except ults) and unable to dodge\n";
	cout << "=========================================================\n";
}

void Display::tempoMessage(const string& message, int delayMs)
{
	cout << message << endl;
	this_thread::sleep_for(chrono::milliseconds(delayMs));
}

void Display::pressEnter()
{
	cout << "\n[press enter to continue]\n" << flush;
	string urmom;
	getline(cin, urmom);
}

void Display::skipStory(const string& prompt)
{
	cout << prompt;
	string answer;
	bool isValid = false;
	do {
		getline(cin, answer);
		if (answer == "y" || answer == "n") {
			if (answer == "y") {
				skipStory_ = true;
				return;
			}
			if (answer == "n") {
				skipStory_ = false;
				return;
			}
		}
		else {
			cout << "\nPlease enter 'y' or 'n': ";
		}
	} while (!isValid);
}

void Display::intro()
{
	skipStory("\nSkip intro? (y/n) :");
	if (skipStory_) { return; }

	tempoMessage("A long time ago in a galaxy far, far away....", 2000);
	tempoMessage("jk this isn't star wars", 2000);
	tempoMessage("In a once peaceful and prosperous land called Kaer Morhen,", 3000);
	tempoMessage("There lived a very happy community of honest, hard working people.", 3000);
	tempoMessage("The economy was thriving, the younger generations were hopeful, and the people were as strong as ever.", 4000);
	tempoMessage("Unfortunately, good things can never last", 2000);
	tempoMessage("It is when everyone was least expecting it that everything started to go wrong...", 3000);
	tempoMessage("Nobody knows why or how monsters started appearing near the villages, destroying everything on their path...", 4000);
	tempoMessage("And that is why the king of these lands has gathered the three bravest warriors he could find.", 3000);
	tempoMessage("A knight, master of the heavy arms, capable of inflicting serious damage with his weapon swings.", 3000);
	tempoMessage("An archer, capable of shooting piercing arrows at dizzying speeds.", 3000);
	tempoMessage("And a mage, casting spells dangerous to foes and friendly to allies.", 3000);
	cout << "Together, they will save the people of Kaer Morhen and restore the peace this land once lived under.";
	pressEnter();
}

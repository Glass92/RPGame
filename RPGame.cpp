// Michael Glass
// 21st Nov 2016
// RPGame
// An interactive game where the users plays
// as a pre-made character or new character
// to battle a dragon.
// Version 4.3

// *******************
// *** ASSUMPTIONS ***
// *******************

	// USER WILL INPUT WHAT IS ASKED, eg. IF IT IS ONLY A CHAR, A CHAR WILL BE ENTERED.
	// WHEN INPUTTING A NAME, USER WILL INPUT A FIRST NAME ONLY! eg. 'ALASTAIR'.
	// USER WILL NOT FIDDLE AROUND WITH SOURCE FILES

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <windows.h>

using namespace std;

// ***************
// *** CLASSES ***
// ***************

class Character
{
public:
	// CONSTRUCTORS
	Character();
	Character(string, string, int, int , int);	
	// GET FUNCTIONS
	string GetName(), GetPortrait();
	int GetHealth(), GetStrength(), GetDefence();
	void display_char_img(string& char_name);
	bool isDead();
	// SET FUNCTIONS
	void setDead(bool);	
	void SetName(string new_name), SetPortrait(string new_portrait), SetHealth(int new_health), SetStrength(int new_strength), SetDefence(int new_defence);
private:
	// ATTRIBUTES
	string name, portrait;
	int health, strength, defence;
	bool Dead;
};

Character::Character()
{
	name = "newCharacter"; portrait = " "; health = 50; strength = 10; defence = 10; Dead = 0;
}

Character::Character(string new_name, string new_img, int new_hp, int new_str, int new_def)
{
}

// *****************
// *** FUNCTIONS ***
// *****************
void printTitle();
void printPrincess();
void rollDice(double&, double&);
void readyUp();

// ************
// *** MAIN ***
// ************

int main()
{
	// CLASS OBJECT DECLARATION
	Character character[2];
	Character newCharacter;
	Character dragon;
	// USER CHOICES
	int userCharChoice, p;
	char battleChoice, playAsNew;
	bool reset = 0;
	// DIE RETURNS
	double dieT, dieP;
	// BATTLE COMPARISON
	int damage, realDamage;	
	// COLOURS!?!?! (WINDOWS ONLY)
	int k;
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// ===============================================================
	// CREATES OBJECT CHARACTER 1 (Alastair)
	// ===============================================================
	ifstream fileC1("char1Img.txt");
	if (fileC1.good())
	{
		string name, portrait;
		int stats[3];

		ifstream file("char1Stats.txt");
		if (file.is_open())
		{
			file >> name;

			for (int i = 0; i < 3; ++i)
			{
				file >> stats[i];
			}
		}
		file.close();

		ifstream charImg("char1Img.txt");
		stringstream portraitStream;
		portraitStream << charImg.rdbuf();
		portrait = portraitStream.str();
		charImg.close();

		character[0].SetName(name);
		character[0].SetPortrait(portrait);
		character[0].SetHealth(stats[0]);
		character[0].SetStrength(stats[1]);
		character[0].SetDefence(stats[2]);
	}
	fileC1.close();
	cout << "===============================================================\nIf Character 1 portrait is present; open the character 1 stats file; pull stats from file; \nset them to variables; create an object of Character class using set functions.\n===============================================================" << endl;

	// ===============================================================
	// MAIN MENU
	// ===============================================================
	do
	{
		// CLEARS SCREEN ON RESET AFTER CHARACTER CREATION
		system("cls");
		reset = 0;

		// MAKES TITLES RED
		k = 12;
		SetConsoleTextAttribute(hConsole, k);
		printTitle();
		// MAKES OUTPUT WHITE AGAIN
		k = 7;
		SetConsoleTextAttribute(hConsole, k);
		cout << "Welcome back to Dungeons and Dragons! \nWe hope you enjoy your stay!\n This game is best enjoyed in full screen!" << endl;

		cout << "===============================================================\nMenu checks if there is a character 2 file in the folder; if present prints option for character 2.\n===============================================================" << endl;
		do
		{
			cout << "Please select a character to play: \n" << endl;
			cout << "Press 1 to create a New Character." << endl;
			cout << "Press 2 for " << character[0].GetName() << "." << endl;
			ifstream chooseChar2("char2Img.txt");
			if (chooseChar2.is_open())
			{
				cout << "Press 3 for " << character[1].GetName() << "." << endl;
			}
			cin >> userCharChoice;
			if (userCharChoice == 2)
				p = 0;
			else if (userCharChoice == 3)
				p = 1;

		} while ((userCharChoice < 1) || (userCharChoice > 3));
	
	// ===============================================================
	// CREATES NEW CHARACTER
	// ===============================================================
		if (userCharChoice == 1) 
		{
			string name, portrait;
			int health = 50, str = 10, def = 10;
			double dieTotal, diePer;
			
			cout << "Please input a name for your new character: ";
			cin >> name;

			// SETS NEW CHARACTER PORTRAIT
			ifstream charImg("newCharImg.txt");
			if (charImg.is_open())
			{
				stringstream portraitStream;
				portraitStream << charImg.rdbuf();
				portrait = portraitStream.str();
				newCharacter.SetPortrait(portrait);

				ofstream charImgCopy("char2Img.txt");
				if (charImgCopy.is_open())
				{
					charImgCopy << portrait;
				}
				charImgCopy.close();
			}
			charImg.close();

			// ROLLING FOR STATS
			cout << "===============================================================\nA dice roll function produces 2 random numbers between 1 and 10 which are combined together.\nThe total is converted to a percentage of the possible total (20) and multiplied against 'base' stats.\nThese are then input into a new object with set functions.\n===============================================================" << endl;
			ofstream newChar("newCharStats.txt");
			if (newChar.is_open())
			{
				newChar << name << " ";
				cout << "We will now roll two 10 sided die for your stats.\n" << endl;
				cout << "First health... \n" << endl;
				rollDice(dieTotal, diePer);
				health = (health * diePer);
				newChar << health << " ";
				cout << name << " has " << health << " health.\n" << endl;
				cout << "Now Strength...\n" << endl;
				rollDice(dieTotal, diePer);
				str = (str * diePer);
				newChar << str << " ";
				cout << name << " has been training, and gained a Strength rating of: " << str << "\n" << endl;
				cout << "Finally defence... \n" << endl;
				rollDice(dieTotal, diePer);
				def = (def * diePer);
				newChar << def << " ";
				cout << "During training, " << name << " discovered they had a Defence rating of: " << def << "\n" << endl;
			}
			newChar.close();

			cout << "Say hello to " << name << "!" << endl;
			cout << portrait << endl;

			newCharacter.SetName(name);
			newCharacter.SetPortrait(portrait);
			newCharacter.SetHealth(health);
			newCharacter.SetStrength(str);
			newCharacter.SetDefence(def);

			ifstream newCharCopy("newCharStats.txt");
			if (newCharCopy.is_open())
			{
				ofstream char2("char2Stats.txt");
				if (char2.is_open())
				{
					char2 << newCharCopy.rdbuf();
				}
				char2.close();
			}
			newCharCopy.close();

	// ===============================================================
	// CREATES OBJECT CHARACTER 2 
	// ===============================================================
			cout << "===============================================================\nNew Character is turned into Character 2 with .txt files.\n Users is asked to input if they want to play as new character.\nNew character is now available as a choice in the menu.\n===============================================================" << endl;
			ifstream fileC2("char2Img.txt");
			if (fileC2.good())
			{
				string name, portrait;
				int stats[3];

				ifstream file("char2Stats.txt");
				if (file.is_open())
				{
					file >> name;

					for (int i = 0; i < 3; ++i)
					{
						file >> stats[i];
					}
				}
				file.close();

				ifstream charImg("char2Img.txt");
				stringstream portraitStream;
				portraitStream << charImg.rdbuf();
				portrait = portraitStream.str();
				charImg.close();

				character[1].SetName(name);
				character[1].SetPortrait(portrait);
				character[1].SetHealth(stats[0]);
				character[1].SetStrength(stats[1]);
				character[1].SetDefence(stats[2]);
			}
			fileC2.close();

			cout << "Would you like to play as " << newCharacter.GetName() << "?" << endl;
			cout << "Please input 'y' if yes...";
			cin >> playAsNew;
			if (playAsNew == 'y')
			{
				reset = 1;
				cout << "Thank you, just restarting the game..." << endl;
			}
			else
			{
				reset = 0;
			}

		}
	} while (reset != 0);

	// ===============================================================
	// USER PLAYER CHOICE CHARACTER 
	// ===============================================================
		if (userCharChoice >= 2)
		{
			cout << "===============================================================\nCharacter choice is presented, using get functions depending on user choice in the main menu.\nThis is achieved using class object arrays to create a character.\n===============================================================" << endl;
			cout << "You have chosen to play " << character[p].GetName() << endl;
			cout << character[p].GetPortrait() << endl;
			cout << "\n\t   Health: " << character[p].GetHealth() << "\tStrength: " << character[p].GetStrength() << "\tDefence: " << character[p].GetDefence() << endl;
			cout << endl;
			readyUp();

	// ===============================================================
	// CREATE DRAGON OBJECT
	// ===============================================================
			cout << "===============================================================\nDragon is created using input from .txt files.\nThese are input into a class object using set functions.\n===============================================================" << endl;
			string name, portrait;
			int stats[3];

			ifstream file("monstDragonStats.txt");
			if (file.is_open())
			{
				file >> name;

				for (int i = 0; i < 3; ++i)
				{
					file >> stats[i];
				}
			}
			file.close();

			ifstream charImg("monstDragon.txt");
			stringstream portraitStream;
			portraitStream << charImg.rdbuf();
			portrait = portraitStream.str();
			charImg.close();

			dragon.SetName(name);
			dragon.SetPortrait(portrait);
			dragon.SetHealth(stats[0]);
			dragon.SetStrength(stats[1]);
			dragon.SetDefence(stats[2]);

			cout << "You find yourself standing infront of a " << dragon.GetName() << endl;
			k = 12;
			SetConsoleTextAttribute(hConsole, k);
			cout << dragon.GetPortrait() << endl;
			k = 7;
			SetConsoleTextAttribute(hConsole, k);

	// ===============================================================
	// BATTLE 
	// ===============================================================
			cout << "===============================================================\nBattle Choices are an illusion of choice, they both attack. Stats are multiplied against dice rolls to produce a damage rating.\nThis is then compared against the defending character's defence, producing a real damage value.\nThis is then compared against the health of the defending character and either takes health off, or creates a death state.\n===============================================================" << endl;
			do
			{
				cout << "\nWhat do you do?" << endl;
				cout << "Fight?     1." << endl;
				cout << "Talk?      2." << endl;
				cin >> battleChoice;

				switch (battleChoice)
				{
				case '1': // FIGHT
					cout << "\nYou take a swing at the " << dragon.GetName() << " with your sword!\n" << endl;
					rollDice(dieT, dieP);
					damage = (character[p].GetStrength()*dieP);
					realDamage = (damage - dragon.GetDefence());
					if (realDamage <= 0)
					{
						cout << "The " << dragon.GetName() << " negates your damage of " << damage << " due to it's " << dragon.GetDefence() << " defence rating!" << endl;
					}
					else if ((realDamage > 0) && (realDamage < dragon.GetHealth()))
					{
						cout << "You have done " << realDamage << " damage to the " << dragon.GetName() << "!" << endl;
						dragon.SetHealth((dragon.GetHealth() - realDamage));
					}
					else if (realDamage > dragon.GetHealth())
					{
						cout << "The " << dragon.GetName() << " is now dead!\n" << endl;
						dragon.SetHealth(0);
						dragon.setDead(1);
						break;
					}
					cout << "The " << dragon.GetName() << " has " << dragon.GetHealth() << " health remaining!\n" << endl;
					damage = 0; realDamage = 0;
					cout << "\nThe " << dragon.GetName() << " stomps on you!\n" << endl;
					rollDice(dieT, dieP);
					damage = (dragon.GetStrength()*dieP);
					realDamage = (damage - character[p].GetDefence());
					if (realDamage <= 0)
					{
						cout << character[p].GetName() << " negates the damage of " << damage << " due to their " << character[p].GetDefence() << " defence rating!" << endl;
					}
					else if ((realDamage > 0) && (realDamage < character[p].GetHealth()))
					{
						cout << "The " << dragon.GetName() << " does " << realDamage << " damage to you!" << endl;
						character[p].SetHealth((character[p].GetHealth() - realDamage));
					}
					else if (realDamage > character[p].GetHealth())
					{
						cout << character[p].GetName() << " is now dead!\n" << endl;
						character[p].SetHealth(0);
						character[p].setDead(1);
						break;
					}
					cout << "You have " << character[p].GetHealth() << " health remaining!" << endl;
					break;

				case '2': // TALK 
					cout << "\nYou try to converse with the " << dragon.GetName() << ". \nYou ask what the dragon wants...\n" << endl;
					rollDice(dieT, dieP);
					damage = (character[p].GetStrength()*dieP);
					realDamage = (damage - dragon.GetDefence());
					if (realDamage <= 0)
					{
						cout << "The " << dragon.GetName() << " ignores you foolish attempt at parley (" << damage << " rating) due to it's " << dragon.GetDefence() << " defence rating!" << endl;
					}
					else if ((realDamage > 0) && (realDamage < dragon.GetHealth()))
					{
						cout << "Success! You have exposed a weakness in the " << dragon.GetName() << ". Doing " << damage << " damage to the " << dragon.GetName() << "!" << endl;
						dragon.SetHealth((dragon.GetHealth() - realDamage));
					}
					else if (realDamage > dragon.GetHealth())
					{
						cout << "The " << dragon.GetName() << " is now dead!\n" << endl;
						dragon.SetHealth(0);
						dragon.setDead(1);
						break;
					}
					cout << "The " << dragon.GetName() << " has " << dragon.GetHealth() << " health remaining! \n" << endl;
					cout << "The " << dragon.GetName() << " bites you! \n" << endl;
					rollDice(dieT, dieP);
					damage = (dragon.GetStrength()*dieP);
					realDamage = (damage - character[p].GetDefence());
					if (realDamage <= 0)
					{
						cout << character[p].GetName() << " negates the damage of " << damage << " due to their " << character[p].GetDefence() << " defence rating!" << endl;
					}
					else if ((realDamage > 0) && (realDamage < character[p].GetHealth()))
					{
						cout << "The " << dragon.GetName() << " does " << realDamage << " damage to you!" << endl;
						character[p].SetHealth((character[p].GetHealth() - realDamage));
					}
					else if (realDamage > character[p].GetHealth())
					{
						cout << "The " << dragon.GetName() << " eats you! \n" << character[p].GetName() << " is now dead!\n" << endl;
						character[p].SetHealth(0);
						character[p].setDead(1);
						break;
					}
					cout << "You have " << character[p].GetHealth() << " health remaining!" << endl;
					break;
				}
			} while ((character[p].isDead() == 0) && (dragon.isDead() == 0));
		}

	// ===============================================================
	// USER DEATH
	// ===============================================================
		if (character[p].isDead() == 1)
		{
			cout << "^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v\n" << character[p].GetName() << " succumbed to the wrath of the " << dragon.GetName() << "!" << endl;
			SetConsoleTextAttribute(hConsole, k = 12);
			cout << "\n              ROOOOAAAAAARRRRRRRRRR" << flush;
			for (int i = 0; i < 25; i++)
			{
				Sleep(10);
				std::cout << "." << std::flush;
				Sleep(10);
				std::cout << "." << std::flush;
				Sleep(10);
				std::cout << "." << std::flush;
				Sleep(10);
				std::cout << "\b\b\b   \b\b\b" << std::flush;
			}
			cout << "\n" << dragon.GetPortrait() << endl;
			SetConsoleTextAttribute(hConsole, 7);
		}

		// ===============================================================
		// DRAGON DEATH 
		// ===============================================================
		else if (dragon.isDead() == 1)
		{
			cout << "===============================================================\nIf user wins, a princess image is printed off using functions reading from file.\nStats increased are rolled against a ratio of dice percentage of dice Total.\n===============================================================\n" << endl;
			cout << "****************************************************************\n" << endl;
			cout << character[p].GetName() << " triumphed over the " << dragon.GetName() << "! \nGaining a mountain full of gold and a fair maiden on thier arm!" << endl;
			SetConsoleTextAttribute(hConsole, k = 12);
			printPrincess();
			SetConsoleTextAttribute(hConsole, k = 7);
			cout << character[p].GetName() << " has leveled up!" << endl;
			rollDice(dieT, dieP);
			cout << character[p].GetName() << "'s current health has increased up from " << character[p].GetHealth() << " to ";
			character[p].SetHealth(character[p].GetHealth()+(character[p].GetHealth()*dieP));
			cout << character[p].GetHealth() << "!" << endl;
			cout << character[p].GetName() << "'s strength has leveled up from " << character[p].GetStrength() << " to ";
			character[p].SetStrength(character[p].GetStrength()+(character[p].GetStrength()*dieP));
			cout << character[p].GetStrength() << "!" << endl;
			cout << character[p].GetName() << "'s defence has leveled up from " << character[p].GetDefence() << " to ";
			character[p].SetDefence(character[p].GetDefence()+(character[p].GetDefence()*dieP));
			cout << character[p].GetDefence() << "!" << endl;
		}				
	cout << "Thank you for playing!" << endl;
	// ===============================================================
	// SAVE TO STATS FILE 
	// ===============================================================
	cout << "===============================================================\nOld character file is opened and wiped, and replaced with new stats using class objects Get Functions.\n===============================================================" << endl;
	switch (p)
	{
	case 0:
	{
		ofstream updateChar;
		updateChar.open("char1Stats.txt", ios::out | ios::trunc);
		if (updateChar.is_open())
		{
			updateChar << character[p].GetName() << " " << character[p].GetHealth() << " " << character[p].GetStrength() << " " << character[p].GetDefence();
		}
		updateChar.close();
		break;
	}
	case 1:
	{
		ofstream updateChar;
		updateChar.open("char2Stats.txt", ios::out | ios::trunc);
		if (updateChar.is_open())
		{
			updateChar << character[p].GetName() << " " << character[p].GetHealth() << " " << character[p].GetStrength() << " " << character[p].GetDefence();
		}
		updateChar.close();
		break;
	}
	}

	
	SetConsoleTextAttribute(hConsole, k = 12);
	printTitle();
	SetConsoleTextAttribute(hConsole, k = 7);

	return 0;
}

// *******************
// *** DEFINITIONS ***
// *******************

void Character::SetName(string new_name)
{
	name = new_name;
}
string Character::GetName()
{
	return name;
}
string Character::GetPortrait()
{
	return portrait;
}
bool Character::isDead()
{
	return Dead;
}
void Character::setDead(bool death)
{
	Dead = death;
}
void Character::SetHealth(int new_health)
{
	health = new_health;
}
void Character::SetPortrait(string new_portrait)
{
	portrait = new_portrait;
}
int Character::GetHealth()
{
	return health;
}
void Character::SetStrength(int new_strength)
{
	strength = new_strength;
}
int Character::GetStrength()
{
	return strength;
}
void Character::SetDefence(int new_defence)
{
	defence = new_defence;
}
int Character::GetDefence()
{
	return defence;
}
void Character::display_char_img(string& char_name)
{
	string ascii;
	ifstream image;
	image.open("char1Img.txt"); // THIS HAS TO BE SORTED TO DISPLAY CURRENT CHAR NAME

	while (getline(image, ascii))
	{
		cout << ascii << endl;
	}
	image.close();
}

void printTitle()
{
	string ascii;
	ifstream titleScreen;
	titleScreen.open("titlescreen.txt");
	while (getline(titleScreen, ascii))
	{
		cout << ascii << endl;
	}
	titleScreen.close();
}
void printPrincess()
{
	string ascii;
	ifstream princess;
	princess.open("princess.txt");
	while (getline(princess, ascii))
	{
		cout << ascii << endl;
	}
	princess.close();
}
void rollDice(double& total, double& percentage)
{
	char toRoll;
	int die[2];
	int roll[11];
	int i, j;
	// TIME DELAY IN MSECONDS

	
	do
	{
		toRoll = 'n';
		cout << "Roll dice?\nPlease input 'y' to roll." << endl;
		cin >> toRoll;
		toRoll = 'y';
	} while (toRoll != 'y');

	if (toRoll == 'y')
	{
		cout << "\nRolling Dice:  " << flush;
		for (i = 0; i < 5; i++)
		{
			for (j = 0; j < 9; j++)
			{
				for (i = 0; i < 1000; i++)
				{
					srand(time(NULL));
					die[0] = 1 + (rand() % 10);
					die[1] = 1 + (rand() % 10);
				}
				roll[j] = j;
				Sleep(10);
				cout << "\b" << roll[j] << flush << "     " << "\b" << roll[j] << flush;
				Sleep(10);
				cout << "\b\b\b\b\b" << flush;
				Sleep(10);
			}
			cout << "\b" << die[0] << flush << "     " << "\b" << die[1] << flush;
			Sleep(10);
			cout << "\b\b\b\b\b" << flush;
		}
		total = die[0] + die[1];
		cout << "\nYou rolled a total of: " << total << "\n" << endl;
		percentage = ((total * 10) / 100);
	}
}
void readyUp()
{
	char decision;
	do
	{
		cout << "Are you ready to continue? \nPlease input 'y' when you are ready..." << endl;
		cin >> decision;
		cout << endl;
	} while (decision != 'y');
}

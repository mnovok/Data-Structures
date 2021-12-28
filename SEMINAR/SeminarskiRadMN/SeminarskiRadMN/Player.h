#ifndef PLAYER_H
#define PLAYER_H

#define MAX_NAME (50)
#define MAX_LINE_LENGTH (1024)

struct _PlayerStructure;

typedef struct _PlayerStructure* Player;

typedef struct _PlayerStructure {

	char name[MAX_NAME];
	char class[MAX_NAME];
	int health;
	int attack;
	int defense;
	int luck;

} PlayerStructure;

int InitializePlayer(Player player); //inicijalizacija
Player CreatePlayer(int classNumber, char name[MAX_NAME]); //kreiranje igraca
int SetName(Player current, char name[MAX_NAME]); //unos imena igraca
int DisplayStatus(Player player); //prikaz podataka o igracu
int SetRandomValue(int lowerBound, int upperBound); //generiranje nasumicne vrijednosti u odredjenom intervalu
Player ReadCustomPlayer(char* fileName); //kreiranje igraca iz datoteke
char* EnterFileName(void); //citanje imena datoteke
char* EnterPlayerName(void); //unos imena igraca


#endif 

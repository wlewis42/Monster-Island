#ifndef _PROG5_H
#define _PROG5_H
#include <string>
using namespace std;

struct Cost
{
    float hours;
    float care;
    float food;
    float materials;
};

struct Monsters
{
    string name;
    string description;
    float avgLength;
    float avgHeight;
    string location;
    bool dangerous;
    Cost cost;
};

int enterMonsters(int,Monsters*);
int deleteMonster(int,Monsters*);
void printMonsters(int,Monsters*);
bool moveArrayElements(string,int,Monsters*);
float convertToFloat(string);
void printStatistics(int,Monsters*);
void saveMonstersToFile(int,Monsters*);

#endif
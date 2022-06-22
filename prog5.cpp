/*
    Author:     William Lewis
    Title:      prog5.exe
    Purpose:    store, track, delete monsters on island
    Date:       04/28/2020
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "prog5.h"
using namespace std;

int main()
{   
    int population=0;
    int choice=0;
    int capacity=100;
    bool runAgain=true;
    Monsters* monsterArray = new Monsters[capacity];
    do{
        char leave;
        cout<<"What would you like to do?\n";
        cout<<"\t\t1.\tEnter some Monsters\n";
        cout<<"\t\t2.\tDelete a Monster\n";
        cout<<"\t\t3.\tList/Print Monsters\n";
        cout<<"\t\t4.\tPrint Statistics on Monster Cost\n";
        cout<<"\t\t5.\tEnd Program\n";
        cout<<"\t\tEnter 1, 2, 3, 4, or 5\n";
        cout<<"CHOICE:";
        // Validate user choice
        while(!(cin>>choice))
        {   
            // Error invalid choice
            cout<< "Error... Enter a valid choice: ";
            cin.clear();
            cin.ignore(123,'\n');
        }
        while (choice < 1 || choice > 5)
        {
            cout << "Please choose 1-5:";
            while(!(cin>>choice))
            {
                // Error invalid choice
                cout<< "Error... Enter a valid choice: ";
                cin.clear();
                cin.ignore(123,'\n');
            }
        }
        switch(choice)
        {
            case 1:
                population = enterMonsters(population, monsterArray);
                break;
            case 2:
                population = deleteMonster(population, monsterArray);
                break;
            case 3:
                printMonsters(population, monsterArray);
                break;
            case 4:
                printStatistics(population,monsterArray);
                break;
            default:
                {
                    cout<<"Do you really want to leave Monster Island?\n";
                    cin>>leave;
                    if(toupper(leave)=='Y')
                        {
                            char save;
                            cin.ignore();
                            cout<<"Would you like to save your monsters? ";
                            cin>>save;
                            if(toupper(save)=='Y')
                                saveMonstersToFile(population,monsterArray);
                            runAgain=false;
                            cout<<"Thanks for visiting! Sorry to see you go.";
                        }
                    else
                        runAgain=true;
                }
        }
    }while(runAgain);
    delete []monsterArray;

    return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include"prog5.h"
using namespace std;

float convertToFloat(string s)
{
    istringstream i(s);
    float x;
    if (!(i>>x))
        x=0;
    return x;
}

int enterMonsters(int citizens,  Monsters* creatureArray )
{
    int choice;
    cin.ignore();
    string chooseFile;
    ifstream inFile;
    string line;
    cout<<fixed<<setprecision(2);
    bool enterRepeat = false;
    char answer;
    if(citizens>=100)
    {
        cout<<"Sorry, but the island is at capacity and can't take any more Monsters.";
    }
    else
    {
        cout<<"What would you like to do?\n";
        cout<<"\t\t1.\tLoad my Monsters from a file\n";
        cout<<"\t\t2.\tEnter one Monster manually\n";
        cout<<"\t\tChoose 1 or 2\n";
        cout<<"CHOICE:";
        
        // Validate user choice
        while(!(cin>>choice))
        {   
            // Error invalid choice
            cout<< "Error... Enter a valid choice: ";
            cin.clear();
            cin.ignore(123,'\n');
        }
        while (choice < 1 || choice > 2)
        {
            cout << "Please choose 1 or 2:";
            while(!(cin>>choice))
            {
                // Error invalid choice
                cout<< "Error... Enter a valid choice: ";
                cin.clear();
                cin.ignore(123,'\n');
            }
        }
        
        switch (choice)
        {   
            case 1:
                cout<<"What is the name of the file with your list of monsters? (ex:filename.txt)\n";
                cout<<"FILENAME: ";
                cin>>chooseFile;
                inFile.open(chooseFile.c_str());
                if(inFile.good())
                {
                    while(!inFile.eof())
                    {   
                        getline(inFile,line,'#'); 
                        creatureArray[citizens].name = line;
                        getline(inFile,line,'#');
                        creatureArray[citizens].description= line;
                        getline(inFile,line,'#');
                        creatureArray[citizens].avgLength= convertToFloat(line);
                        getline(inFile,line,'#');
                        creatureArray[citizens].avgHeight= convertToFloat(line);
                        getline(inFile,line,'#');
                        creatureArray[citizens].location= line;
                        getline(inFile,line,'#');
                        if(line=="1")
                            creatureArray[citizens].dangerous= 1;
                        else
                            creatureArray[citizens].dangerous= 0;
                        getline(inFile,line,'#');
                        creatureArray[citizens].cost.hours= convertToFloat(line);
                        getline(inFile,line,'#');
                        creatureArray[citizens].cost.care= convertToFloat(line);
                        getline(inFile,line,'#');
                        creatureArray[citizens].cost.food= convertToFloat(line);
                        getline(inFile,line,'#');
                        creatureArray[citizens].cost.materials= convertToFloat(line);
                        citizens++;
                    }
                    cout<<"\n\nAll monsters from "<<chooseFile<<" have been added to the program.\n";
                }
                else
                {
                    cout<<"Something went wrong...\n";
                }
                
            break;
            case 2:
                do
                {
                    cin.ignore();
                    char danger;
                    cout<<"NAME: ";
                    getline(cin,creatureArray[citizens].name);
                    cout<<"DESCRIPTION: ";
                    getline(cin,creatureArray[citizens].description);
                    cout<<"AVERAGE LENGTH (in feet): ";
                    cin>>creatureArray[citizens].avgLength;
                    cin.ignore();
                    cout<<"AVERAGE HEIGHT (in feet): ";
                    cin>>creatureArray[citizens].avgHeight;
                    cin.ignore();
                    cout<<"LOCATION: ";
                    getline(cin,creatureArray[citizens].location);
                    cout<<"IS IT A DANGEROUS MONSTER? (y or n): ";
                    cin>>danger;
                    if(toupper(danger) == 'Y')
                        creatureArray[citizens].dangerous = 1;
                    else
                        creatureArray[citizens].dangerous = 0;
                    cout<<"How many hours do you spend caring for the "<<creatureArray[citizens].name<<"?\n";
                    cout<<"NUM HOURS: ";
                    cin>>creatureArray[citizens].cost.hours;
                    cin.ignore();
                    cout<<"What is the cost per hour for caring for the "<<creatureArray[citizens].name<<"?\n";
                    cout<<"COST PER HOUR: ";
                    cin>>creatureArray[citizens].cost.care;
                    cin.ignore();
                    cout<<"How much money do you spend on food for the "<<creatureArray[citizens].name<<"?\n";
                    cout<<"FOOD COST: ";
                    cin>>creatureArray[citizens].cost.food;
                    cin.ignore();
                    cout<<"How much money do you spend on grooming and medical supplies for the "<<creatureArray[citizens].name<<"?\n";
                    cout<<"SUPPLY COST: ";
                    cin>>creatureArray[citizens].cost.materials;

                    citizens++;
                    cout<<"Do you want to add another Monster?";
                    cin>>answer;
                    if(toupper(answer)=='Y')
                        enterRepeat=true;
                    else
                        enterRepeat=false;
                }while(enterRepeat);
                break;
            default:
                cout<<"Nothing to see here.";
                break;
        }
    }
    return citizens;
}

int deleteMonster(int citizens, Monsters* creatureArray)
{   
    string monsterName;
    cout<<"The following is a list of all the monsters you take care of:\n";
    for(int i=0;i<citizens;i++)
        {
            cout<<creatureArray[i].name<<endl;
        }
    cout<<endl<<endl;
    cout<<"What monster do you wish to remove?"<<endl;
    cout<<"MONSTER NAME: ";
    cin.ignore();
    getline(cin,monsterName);
    bool deleteResults=moveArrayElements(monsterName,citizens,creatureArray);
    if(deleteResults!=false)
        {
            cout<<monsterName<<" removed successfully."<<endl;
            citizens--;
        }
    else
        cout<<"Failed to delete "<<monsterName<<endl;
    
    return citizens;
}

bool moveArrayElements(string monsterName, int citizens, Monsters* creatureArray)
{   
    int monLoc;
    for(int i=0;i<citizens; i++)
    {
        if(monsterName==creatureArray[i].name)
        {
            monLoc=i;
            for(int x=monLoc;x<citizens;x++)
            {
                cout<<"Shifting monster list"<<endl;
                //delete creature at index i and shift next index left
                creatureArray[x]=creatureArray[x+1];
            }
            return true;
        }
    }
    return false;
}

void printMonsters(int citizens, Monsters* creatureArray)
{
    int menu;
    string horizontalLine(80,'-');
    cout<<"What would you like to do?\n";
    cout<<"\t1. Print Monsters to the Screen.\n";
    cout<<"\t2. Print Monsters to a file.\n";
    // Validate user choice
        while(!(cin>>menu))
        {   
            // Error invalid choice
            cout<< "Error... Enter a valid choice: ";
            cin.clear();
            cin.ignore(123,'\n');
        }
        while (menu < 1 || menu > 5)
        {
            cout << "Please choose 1-5:";
            while(!(cin>>menu))
            {
                // Error invalid choice
                cout<< "Error... Enter a valid choice: ";
                cin.clear();
                cin.ignore(123,'\n');
            }
        }
    switch(menu)
    {
        case 1:
            cout<<horizontalLine<<endl;
            for(int i=0;i<citizens;i++)
            {   
                cout<<"Monster "<<i+1<<": "<<endl;
                cout<<"Name:\t\t\t"<<creatureArray[i].name<<endl;
                cout<<"Description:"<<endl;
                cout<<"\t\t\t"<<creatureArray[i].description<<endl;
                cout<<"Length: \t\t"<<creatureArray[i].avgLength<<" feet"<<endl;
                cout<<"Height: \t\t"<<creatureArray[i].avgHeight<<" feet"<<endl;
                if(creatureArray[i].dangerous==1)
                    cout<<"Dangerous?\t\t"<<"yes"<<endl;
                else
                    cout<<"Dangerous?\t\t"<<"no"<<endl;      
                cout<<"Number of Hours to Care for Monster: \t\t$"<<creatureArray[i].cost.hours<<endl;
                cout<<"Cost Per Hour of Taking Care of Monster: \t$"<<creatureArray[i].cost.care<<endl;
                cout<<"Cost to Feed Monster: \t\t\t\t$"<<creatureArray[i].cost.food<<endl;
                cout<<"Grooming & Supplies Cost: \t\t\t$"<<creatureArray[i].cost.materials<<endl;

                cout<<horizontalLine<<endl;
            }
            break;
        case 2:
            ofstream outFile;
            string file;
            cout<<"What is the name of the file you want to save to?\n";
            cout<<"FILENAME: ";
            cin>>file;
            outFile.open(file.c_str());
            outFile<<horizontalLine<<endl;
            for(int i=0;i<citizens;i++)
            {   
                outFile<<"Name:\t\t\t"<<creatureArray[i].name<<endl;
                outFile<<"Description:"<<endl;
                outFile<<"\t\t\t"<<creatureArray[i].description<<endl;
                outFile<<"Length: \t\t"<<creatureArray[i].avgLength<<" feet"<<endl;
                outFile<<"Height: \t\t"<<creatureArray[i].avgHeight<<" feet"<<endl;
                if(creatureArray[i].dangerous==1)
                    outFile<<"Dangerous?\t\t"<<"yes"<<endl;
                else
                    outFile<<"Dangerous?\t\t"<<"no"<<endl;      
                outFile<<"Number of Hours to Care for Monster: \t\t$"<<creatureArray[i].cost.hours<<endl;
                outFile<<"Cost Per Hour of Taking Care of Monster: \t$"<<creatureArray[i].cost.care<<endl;
                outFile<<"Cost to Feed Monster: \t\t\t\t$"<<creatureArray[i].cost.food<<endl;
                outFile<<"Grooming & Supplies Cost: \t\t\t$"<<creatureArray[i].cost.materials<<endl;
                outFile<<horizontalLine<<endl;
            }
            outFile.close();
            break;
    }
}

void printStatistics(int citizens, Monsters* creatureArray)
{
    float totalCost;
    cout<<"COST OF EACH MONSTER FOR ONE WEEK: \n";
    cout<<"MONSTER"<<setw(30)<<"COST\n";
    for(int i=0;i<citizens;i++)
    {
        
        float price = creatureArray[i].cost.hours*creatureArray[i].cost.care+creatureArray[i].cost.food+creatureArray[i].cost.materials;
        totalCost+=price;
        cout<<left<<setw(15)<<creatureArray[i].name<<right<<setw(20)<<"$"<<right<<setw(12)<<price<<endl;
    }
    cout<<endl<<left<<setw(15)<<"TOTAL COST:"<<right<<setw(20)<<"$"<<right<<setw(12)<<totalCost<<endl;
}

void saveMonstersToFile(int citizens, Monsters *creatureArray)
{
    string saveFile;
    cout<<"What is the name of the file you wish to save your monsters to?(example.txt)\n";
    cout<<"FILENAME:";
    cin>>saveFile;
    ofstream outFile;
    outFile.open(saveFile.c_str());
    for(int i=0;i<citizens;i++)
    {
        outFile<<creatureArray[i].name<<"#";
        outFile<<creatureArray[i].description<<"#";
        outFile<<creatureArray[i].avgLength<<"#";
        outFile<<creatureArray[i].avgHeight<<"#";
        outFile<<creatureArray[i].location<<"#";
        outFile<<creatureArray[i].dangerous<<"#";
        outFile<<creatureArray[i].cost.care<<"#";
        outFile<<creatureArray[i].cost.hours<<"#";
        outFile<<creatureArray[i].cost.food<<"#";
        outFile<<creatureArray[i].cost.materials<<"#";  
    }
}
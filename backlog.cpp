#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#include <thread>
#include <string>
#include <algorithm>
#include "backlog.h"
using namespace std;

//Comparison function for comparing objects by the game's name
bool nameCompare(Game &a, Game &b) {return a.getName() < b.getName();}

//Selecting a choice from a menu
int chooseFromMenu(){
    int choice = 0;
    vector<string> menu = {"Check out your backlog", "Magic Mirror", "Add a game", "Check on a game", "Edit a game", "Delete a game", "Exit"};
    cout << "Menu:\n\n";
    for (int i = 0; i < menu.size(); i++){
        cout << i+1 << ". " << menu[i] << endl;
    }
    cout << "Enter: ";
    cin >> choice;
    while(!(choice >= 1 && choice <= menu.size())){
        for (int i = 0; i < menu.size(); i++){
            cout << i+1 << ". " << menu[i] << endl;
        }
        cout << "Enter: ";
        cin >> choice;
    }
    return choice;
}

//Validates a platform choice
bool checkPlatformInVec(string platform){
    vector<string> platformVec = {"NES", "SNES", "N64", "GCN", "Wii", "Wii U", "Switch",
                                "GameBoy", "GBC", "VB", "GBA", "DS", "3DS",
                                "Genesis", "Sega CD", "32X", "Saturn", "DC",
                                "3DO", "TGFX-16", "Jaguar",
                                "PS1", "PS2", "PS3", "PS4", "PS5", "PSP", "PS Vita",
                                "Xbox", "XB360", "XB1", "XSX", "PC"};
    if (find(platformVec.begin(), platformVec.end(), platform) != platformVec.end()){
        return true;
    }
    else return false;
}

//List out which platforms are available to log
void printPlatforms(){
    cout << endl;
    vector<string> platformVec = {"NES", "SNES", "N64", "GCN", "Wii", "Wii U", "Switch",
                                "GameBoy", "GBC", "VB", "GBA", "DS", "3DS",
                                "Genesis", "Sega CD", "32X", "Saturn", "DC",
                                "3DO", "TGFX-16", "Jaguar",
                                "PS1", "PS2", "PS3", "PS4", "PS5", "PSP", "PS Vita",
                                "Xbox", "XB360", "XB1", "XSX", "PC"};
    
    //Formatting
    for (int i = 0; i < platformVec.size(); i += 4){
        cout << i+1 << ". " << platformVec[i] << "   ";
        if (i+2 <= platformVec.size())
            cout << i+2 << ". " << platformVec[i+1] << "   ";
        if (i+3 <= platformVec.size())
            cout << i+3 << ". " << platformVec[i+2] << "   ";
        if (i+4 <= platformVec.size())
            cout << i+4 << ". " << platformVec[i+3] << endl;
    }
    cout << endl;
}

//Check and see what you currently have in your backlog
void printBacklog(vector<Game> &backlog){
    system("cls");
    string platform;
    printPlatforms();
    cout << "Enter a platform (Type \"All\" for everything): ";
    cin.ignore();
    getline(cin, platform);

    //If "All" isn't typed, ask to enter again
    while (!checkPlatformInVec(platform) && platform != "All"){
        cout << "Try again: ";
        getline(cin, platform);
    }
    system("cls");
    if (platform == "All"){
        cout << "Ah...you wanna be disappointed in yourself, huh?" << endl;
        for (long long i = 0; i < 900000000; i++){
            //Waste a few seconds
        }
        for (int i = 0; i < backlog.size(); i++){
            cout << backlog[i].getName() << " (" << backlog[i].getPlatform() << ")" << endl;
        }
    }
    else{
        auto it = find_if(backlog.begin(), backlog.end(), [platform](const Game &entry){return entry.getPlatform() == platform;});
        if (it == backlog.end()){
            cout << "You don't have anything to work on for the " << platform << ".\n";
        } 
        else{
            for (int i = 0; i < backlog.size(); i++){
            if (backlog[i].getPlatform() == platform) cout << backlog[i].getName() << endl;
        }
        }
        
    }
    system("pause");
}

//Pick a random game to play
void randomGame(vector<Game> &backlog){
    system("cls");
    string platform, lowercaseElement;
    bool isListed = false, isInVec = false;
    cout << "So...you've come to the Magic Mirror to decide how to spend your hour of free time?\n";
    for (long long i = 0; i < 900000000; i++){
        //Waste a few seconds
    }
    cout << "The mirror will help you, but it has to ask...\n";
    for (long long i = 0; i < 900000000; i++){
        //Waste a few seconds
    }
    printPlatforms();
    cout << "Which platform do you want to play on?: ";
    cin.ignore();

    //Makes sure the platform entered is valid and has at least one game in your backlog
    while (!isInVec || !isListed){
        getline(cin, platform);
        isInVec = checkPlatformInVec(platform);
        if (!isInVec){
            cout << "That's not in the list. Try again: ";
        }
        else{
            auto it = find_if(backlog.begin(), backlog.end(), [platform](const Game &entry){return entry.getPlatform() == platform;});
            if (it == backlog.end()){
                cout << "You don't have anything to work on for the " << platform << ". Try again: ";
            } 
            else isListed = true;
        }
    }
    cout << "The mirror is deciding...\n";
    for (long long i = 0; i < 900000000; i++){
        //Waste a few seconds
    }
    srand(time(NULL));
    int rIndex = rand() % backlog.size();
    string indexPlatform = backlog[rIndex].getPlatform();
    while (indexPlatform != platform){
        rIndex = rand() % backlog.size();
        indexPlatform = backlog[rIndex].getPlatform();
    }
    cout << "The mirror has decided!\n" << backlog[rIndex] << endl;
    system("pause");
}

//Add a game to the backlog
void addGame(vector<Game> &backlog){
    system("cls");
    string name, platform, message;

    cout << "Enter the game's name: ";
    cin.ignore();
    getline(cin, name);

    if (name.substr(0, 4) == "The "){
        name.erase(0, 4);
        name.append(", The");
    }

    printPlatforms();
    cout << "Enter the platform: ";
    getline(cin, platform);
    while (!checkPlatformInVec(platform)){
        cout << "Try again: ";
        getline(cin, platform);
    }
    cout << "How far in are you?/Do you want to leave a note of any kind?: ";
    getline(cin, message);
    backlog.push_back(Game(name, platform, message));
    sort(backlog.begin(), backlog.end(), nameCompare); //Games are stored in alphabetical order
}

//Check your current status in a certain game
void checkGame(vector<Game> &backlog){
    system("cls");
    string game;
    bool found;
    int index;

    cout << "Enter which game you want to check: ";
    cin.ignore();
    getline(cin, game);
    for (int i = 0; i < backlog.size(); i++){
        if (backlog[i].getName() == game){
            found = true;
            index = i;
            break;
        }
    }
    if (found){
        cout << "Your status in " << game << " is: \n" << backlog[index].getMessage() << endl;
        system("pause");
    }
    else{
        cout << "You didn't enter that game in." << endl;
        system("pause");
    }
}

void editGame(vector<Game> &backlog){
    system("cls");
    string game;
    bool found;
    int index;

    cout << "Enter which game you want to edit: ";
    cin.ignore();
    getline(cin, game);
    for (int i = 0; i < backlog.size(); i++){
        if (backlog[i].getName() == game){
            found = true;
            index = i;
            break;
        }
    }
    if (found){
        string answer;
        cout << "Do you want to change the name, the platform, or the message/progress?: ";
        cin >> answer;
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        while (answer != "name" && answer != "platform" && answer != "message" && answer != "progress"){
            cout << "Try again: ";
            cin >> answer;
            transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        }
        system("cls");
        cout << "What do you want to change the " << answer << " to?: ";
        if (answer == "name"){
            string name;
            cin.ignore();
            getline(cin, name);
            if (name != backlog[index].getName()){
                cout << "Name has been changed from " << backlog[index].getName();
                backlog[index].setName(name);
                cout << " to " << name << endl;
                system("pause");
            }
            else{
                cout << "The name you entered is the same as its current name." << endl;
                system("pause");
            }
        }
        else if (answer == "platform"){
            string platform;
            cin.ignore();
            getline(cin, platform);
            while (!checkPlatformInVec(platform)){
                printPlatforms();
                cout << "That platform's not listed. Enter one of these: ";
                getline(cin, platform);
            }
            if (platform != backlog[index].getPlatform()){
                cout << "Platform has been changed from " << backlog[index].getPlatform();
                backlog[index].setPlatform(platform);
                cout << " to " << platform << endl;
                system("pause");
            }
            else{
                cout << "The platform you entered is the same as its current platform." << endl;
                system("pause");
            }
        }
        else if (answer == "message" || answer == "progress"){
            string message;
            cin.ignore();
            getline(cin, message);
            message[0] = toupper(message[0]);
            if (message != backlog[index].getMessage()){
                cout << answer << " has been changed from " << backlog[index].getMessage();
                backlog[index].setMessage(message);
                cout << " to " << message << endl;
                system("pause");
            }
            else{
                cout << "The message/progress note you entered is the same as what's currently set." << endl;
                system("pause");
            }
        }
    }
    else{ //Game wasn't found
        cout << "You didn't enter that game into the backlog.\n";
        system("pause");
    }
}

void deleteGame(vector<Game> &backlog){
    string game;
    bool found = false;
    system("cls");
    cout << "Which game do you wanna knock off the list?\n";
    cin.ignore();
    getline(cin, game);
    for (int i = 0; i < backlog.size(); i++){
        //Converts your entry and every name it parses through to lowercase for comparison
        string entry = backlog[i].getName(), originalName = entry, tempGame = game;
        transform(tempGame.begin(), tempGame.end(), tempGame.begin(), ::tolower);
        transform(entry.begin(), entry.end(), entry.begin(), ::tolower);

        if (entry == tempGame){
            backlog.erase(backlog.begin()+i);
            found = true;
            cout << originalName << " has been erased! You finished it...right?\n";
            system("pause");
        }
    }
    if (!found){
        cout << "You didn't enter that game into the backlog.\n";
        system("pause");
    } 
    
}

//Update the file as changes are made to the object vector
void writeToFile(vector<Game> &backlog, string &file){
    ofstream out(file);
    string line, name;
    for (int i = 0; i < backlog.size(); i++){
        line = backlog[i].getName() + "/" + backlog[i].getPlatform() + "/" + backlog[i].getMessage() + "\n";
        out << line;
    }
}

//Converts your backlog file into an object vector
vector<Game> makeBacklog(string fileName){
    vector<Game> backlog;
    ifstream list(fileName);
    string line;
    while (getline(list, line)){
        istringstream iss(line);
        string name, platform, message;
        getline(iss, name, '/');
        getline(iss, platform, '/');
        getline(iss, message);
        backlog.push_back(Game(name, platform, message));
    }
    list.close();
    return backlog;
}

//Executes when there is no backlog file to read from
void firstRun(){
    system("cls");
    ofstream newLog;
    newLog.open("games.backlog");
    string name, platform, message, line;
    cout << "Let's add your first game. What's the name of it?: ";
    getline(cin, name);
    printPlatforms();
    cout << "What platform is it on?: ";
    getline(cin, platform);
    while (!checkPlatformInVec(platform)){
        cout << "Try again: ";
        getline(cin, platform);
    }
    cout << "How far in are you? (Or what do you have to say about yourself?): ";
    getline(cin, message);
    line = name + "/" + platform + "/" + message + "\n";
    newLog << line; //Write game into file
    newLog.close();
}

int main(int argc, char *argv[]){
    //Checks if file exists. If not, create it and add your first game.
    string file = "games.backlog";
    fstream check;
    check.open(file);
    if (check.fail()){
        firstRun();
    }
    check.close();

    //Creates the backlog vector and launches the menu
    vector<Game> backlog = makeBacklog(file);
    int choice;
    while (choice != 7){
        system("cls");
        choice = chooseFromMenu();
        switch(choice){
            case 1:
                printBacklog(backlog);
                break;
            case 2:
                randomGame(backlog);
                break;
            case 3:
                addGame(backlog);
                writeToFile(backlog, file);
                break;
            case 4:
                checkGame(backlog);
                break;
            case 5:
                editGame(backlog);
                writeToFile(backlog, file);
                break;
            case 6:
                deleteGame(backlog);
                writeToFile(backlog, file);
                break;
            default:
                system("cls");
                break;
        }
    }
    
}
#include <iostream>
using namespace std;

class Game{
private:
    string name, platform, message;
public:
    //Constructor and destructor
    Game(string n, string p, string m): name(n), platform(p), message(m){}
    ~Game(){}
    
    //Getters and setters
    string getName(){return name;}
    string getName()const{return name;}
    void setName(string n){name = n;}
    string getPlatform(){return platform;}
    string getPlatform()const{return platform;}
    void setPlatform(string p){platform = p;}
    string getMessage(){return message;}
    string getMessage()const{return message;}
    void setMessage(string m){message = m;}

    //Operator
    bool operator=(string &rhs);
};

//Operators
ostream &operator<<(ostream &os, const Game &g){
    string name = g.getName();

    //Re-orders the name of the game if it starts with "the" (games are stored in alphabetical order)
    if (name.substr(name.size()-5, name.size()) == ", The"){
        name.erase(name.size()-4, name.size());
        name.insert(0, "The ");
    }
    os << name << " (" << g.getPlatform() << "): " << g.getMessage();
    return os;
}

bool Game::operator=(string &rhs){return this->name == rhs;}
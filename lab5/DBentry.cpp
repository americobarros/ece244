
#include <cstdlib>
#include <iostream>
#include "DBentry.h"
#include <string>


DBentry::DBentry(){

}
DBentry::~DBentry(){
    
}

//Non-Default Constructor
DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active){
    this->name = _name;
    this->IPaddress = _IPaddress;
    this->active = _active;
}
// Basic accessors / mutators
void DBentry::setName(string _name){
    this->name = _name;
}
void DBentry::setIPaddress(unsigned int _IPaddress){
    this->IPaddress = _IPaddress;
}

// sets whether or not this entry is active.
void DBentry::setActive (bool _active){
    this->active = _active;
}

string DBentry::getName() const{
    return (this->name);
}

unsigned int DBentry::getIPaddress() const{
    return (this->IPaddress);
}

bool DBentry::getActive() const{
    return (this->active);
}


//Outputs  "name : IPaddress : active/inactive\n"
ostream& operator<< (ostream& out, const DBentry& rhs){
    
    string status;
    if (rhs.active) status = "active";
    else status = "inactive";
            
    out << (rhs.name) << " : " << (rhs.IPaddress) << " : " << status << endl;
    return out;
    
}
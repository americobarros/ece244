/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main_parser.cpp
 * Author: Americo Barros
 *
 * Created on December 2, 2019, 1:18 PM
 */
#include <cstdlib>
#include "TreeNode.h"
#include <sstream>
#include <string>
#include "DBentry.h"
#include "TreeDB.h"
#include <iostream>

using namespace std;

/*
 * 
 */
int main() {

    string line;
    string command;
    TreeDB Tree;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;
        if(command == "insert"){
            //Insert command called
            string name;
            lineStream >> name;
            int ipAddress;
            lineStream >> ipAddress;
            string statusS;
            lineStream >> statusS;
            
            bool status;
            if(statusS == "active") status = true;
            else if(statusS == "inactive") status = false;
            
            if(Tree.insert(new DBentry(name, ipAddress, status)) == true){
                cout<< "Success\n";
            }else{
                cout << "Error: entry already exists\n";
            }
        }
        else if (command == "find"){
            //Find command called
            string name;
            lineStream >> name;
            
            DBentry* nodeEntry = Tree.find(name);
            if(nodeEntry != nullptr){
                cout<< *nodeEntry;
            }else{
                cout << "Error: entry does not exist\n";
            }
        }
        else if (command == "remove"){
            //Remove command called
            string name;
            lineStream >> name;
            
            if(Tree.remove(name) == true){
                cout<< "Success\n";
            }else{
                cout << "Error: entry does not exist\n";
            }
        }
        else if (command == "printall"){
            //Print all command called
            cout<<Tree;
        }
        else if (command == "printprobes"){
            //Print Probes command called
            string name;
            lineStream >> name;
            
           
            if(Tree.find(name) != nullptr) Tree.printProbes();
            else cout << "Error: entry does not exist\n";
        }
        else if (command == "removeall"){
            //Remove all command called
            Tree.clear();
            cout << "Success\n";
        }
        else if (command == "countactive"){
            //Count active command called
            Tree.countActive();
        }
        else if (command == "updatestatus"){
            //Update status command called
            string name;
            lineStream >> name;
            string statusS;
            lineStream >> statusS;
            
            DBentry* nodeEntry = Tree.find(name);
            if(nodeEntry == nullptr) cout << "Error: entry does not exist\n";
            else if(statusS == "active" ) nodeEntry->setActive(true);
            else if(statusS == "inactive") nodeEntry->setActive(false);
            
            if(nodeEntry != nullptr) cout << "Success\n";
        }
        
        //Shouldn't be an issue, but just in case, we'll ignore any extra input
        //Also good for testing, as improper input can be ignored without having to re-launch program
        lineStream.ignore(1000, '\n');
        
        cout << "> ";         // Prompt for input
        getline(cin, line);   // Get a line from standard input
        
    }
    return 0;
}


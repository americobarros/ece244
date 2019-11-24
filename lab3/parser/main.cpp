//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented 
// everytime a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes = 0;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
void errMsg(int errorNum);
bool isNameAType(string name);
bool shapeNameExists(string name);
bool nameErrorCheck(string name, bool failFlag, bool eofFlag, bool existsIsError);
bool typeErrorCheck(string name, bool failFlag, bool eofFlag);
bool locErrorCheck(int loc, bool failFlag, bool eofFlag);
int findShape(string name);
void deleteShapes(string name);

int main() {

    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        if( lineStream.fail() ){ //couldnt put usr input into 'command'
            //We cant get end of file here, otherwise the outermost while loop would exit
            //Only option is invalid command
            errMsg(1);
        }else if(command == "maxShapes"){ //implementing the maxShapes command

            int value = -1;
            lineStream >> value;
            
            
            
           
            if( lineStream.fail() ){ //if it failed to read into value
                
                if ( lineStream.eof() ){
                    // if input failed bc no more input, then too few arguments
                    errMsg(9);
                }else{
                    //Not end of file, just failed. invalid argument type then.
                    errMsg(2);
                }
            }else if( !lineStream.eof() ){
                //didnt fail but we also didnt reach end of file, there was more input
                //than expected!
                errMsg(8);
            }else if (value <= 0){
                //a number was entered not in the admissible range, invalid value
                errMsg(7);
            }else{
                //here is where we would make the array, remember, not making the
                //objects yet, those are created when required and deleted when required.
                
                max_shapes = value;
                shapesArray = new shape*[value];
                for (int i = 0; i < value; i++) shapesArray[i] = NULL;//initialize to null pointers
                
                cout << "New database: max shapes is " << value <<endl;
            }
        }else if(command == "create"){ //implementing the create command
            
            if (max_shapes == shapeCount){
                //array is full
                errMsg(10);
            }else{
                string name;
                lineStream >> name;

                if( !nameErrorCheck(name, lineStream.fail(), lineStream.eof(), true) ){ //if there's no name errors, continue

                    string type;
                    lineStream >> type;

                    if( !typeErrorCheck(type, lineStream.fail(), lineStream.eof()) ){ //no type errors = continue

                        int locX;
                        lineStream >> locX;

                        if( !locErrorCheck(locX, lineStream.fail(), lineStream.eof()) ){ //no locX error = continue
                            int locY;
                            lineStream >> locY;

                            if( !locErrorCheck(locY, lineStream.fail(), lineStream.eof()) ){ //no locY error = continue
                                int sizeX;
                                lineStream >> sizeX;

                                //Since size has same restrictions as loc, we can use loc error check
                                if ( !locErrorCheck(sizeX, lineStream.fail(), lineStream.eof()) ){ //no sizeX error = continue
                                    int sizeY;
                                    lineStream >> sizeY;

                                    //Since size has same restrictions as loc, we can use locErrorCheck
                                    if ( !locErrorCheck(sizeY, lineStream.fail(), lineStream.eof()) ){ //no sizeY error = continue
                                        
                while(lineStream.peek() == 32){
                    //ignore any spaces on the end of input
                    lineStream.ignore(1);
                }
                                        
                                        if( !lineStream.eof() ){
                                            //didnt fail but we also didn't reach end of file, there was more input
                                            //than expected!
                                            errMsg(8);
                                        }else{
                                            //create a new shape at entry after the last shape and pass it the following properties
                                            shapesArray[shapeCount] = new shape(name, type, locX, locY, sizeX, sizeY);
                                            cout << "Created ";
                                            shapesArray[shapeCount]->draw();
                                            shapeCount++;
                                        }
                                    }
                                    
                                }

                            }

                        }
                    }
                }

            }
        }else if(command == "move"){
            
            if (max_shapes == 0){
                //lab file says we can assume that maxShapes will always be set, but just incase!
                //outputs that array is full, really its not created, and stops us from working with an unassigned array pointer
                errMsg(10);
            }else{
                string name;
                lineStream >> name;

                if( !nameErrorCheck(name, lineStream.fail(), lineStream.eof(), false) ){ //if there's no name errors, continue

                    int locX;
                    lineStream >> locX;

                    if( !locErrorCheck(locX, lineStream.fail(), lineStream.eof()) ){ //no locX error = continue
                        int locY;
                        lineStream >> locY;

                        if( !locErrorCheck(locY, lineStream.fail(), lineStream.eof()) ){ //no locY error = continue
                            
                            while(lineStream.peek() == 32){
                                //ignore any spaces on the end of input
                                lineStream.ignore(1);
                            }
                            if( !lineStream.eof() ){
                                //didnt fail but we also didn't reach end of file, there was more input
                                //than expected!
                                errMsg(8);
                            }else{
                                //the name exists, the locations are valid, lets move
                                int nameLoc = findShape(name);
                                
                                shapesArray[nameLoc]->setXlocation(locX);
                                shapesArray[nameLoc]->setYlocation(locY);
                                cout<< "Moved " << name << " to " << locX << " " << locY << endl;
                                
                            }
                            
                        }
                    }
                }
            }
        }else if(command == "rotate"){
            string name;
            lineStream >> name;

            if( !nameErrorCheck(name, lineStream.fail(), lineStream.eof(), false) ){ //if there's no name errors, continue
                
                int angle;
                lineStream >> angle;
                
                while(lineStream.peek() == 32){
                    //ignore any spaces on the end of input
                    lineStream.ignore(1);
                }

                if( lineStream.fail() ){ //if it failed to read into angle
                    if ( lineStream.eof() ){
                       // if input failed bc no more input, then too few arguments
                       errMsg(9);
                    }else{
                       //Not end of file, just failed. invalid argument then.
                       errMsg(2);
                    }
                }else if( (!lineStream.eof()) ){
                    //didn't fail but we also didn't reach end of file, there was more input
                    //than expected!
                    errMsg(8);
                }else if(angle < 0 || angle > 360){
                    //angle is not in bounds
                    errMsg(7);
                }else{
                    //passed all tests, change angle
                    int shapeLoc = findShape(name);
                    shapesArray[shapeLoc] -> setRotate(angle);
                    cout << "Rotated " << name << " by " << angle << " degrees" << endl;
                }
            }
        }else if (command == "draw"){
            string name = "ellipse";
            lineStream >> name;
            
            if (name == "all"){//draws all shapes
                
                while(lineStream.peek() == 32){
                    //ignore any spaces on the end of input
                    lineStream.ignore(1);
                }
                
                if( !lineStream.eof() ){//if there was more than just all, too many arguments
                    errMsg(8);
                }else{
                    cout << "Drew all shapes" <<endl;
                    for (int i = 0 ; i < shapeCount ; i++){
                        shapesArray[i]->draw();
                    }
                }
            }else if( !nameErrorCheck(name, lineStream.fail(), lineStream.eof(), false) ){ //if there's no name errors, continue
                
                while(lineStream.peek() == 32){
                    //ignore any spaces on the end of input
                    lineStream.ignore(1);
                }
                if( !lineStream.eof() ){//if there was more, too many arguments!
                    errMsg(8);
                }else{cout << "Drew " << name << endl;
                    //Find the shape in the array, draw it.
                    int shapeLocation = -1;
                    shapeLocation = findShape(name);
                    shapesArray[shapeLocation]->draw();
                }
            } 
        }else if (command == "delete"){
            string name = "ellipse";
            lineStream >> name;

            if(name == "all"){ //delete all shapes
                
                while(lineStream.peek() == 32){
                    //ignore any spaces on the end of input
                    lineStream.ignore(1);
                }
                if( !lineStream.eof() ){//if there was more than just all, too many arguments
                    errMsg(8);
                }else{
                
                    if (shapeCount > 0) deleteShapes("all");
                    cout << "Deleted: all shapes" << endl;
                }
                
            }else if( !nameErrorCheck(name, lineStream.fail(), lineStream.eof(), false) ){ //if there's no name errors, continue
                while(lineStream.peek() == 32){
                    //ignore any spaces on the end of input
                    lineStream.ignore(1);
                }
                if( !lineStream.eof() ){//if there was more, too many arguments!
                    errMsg(8);
                }else{//delete only the shape the matches name
                    if (shapeCount > 0) deleteShapes(name);
                    cout << "Deleted shape " << name << endl;
                }
            }
        }else errMsg(1);
        

         


        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
        
    }  // End input loop until EOF.
    
    return 0;
}

//This function makes error messaging easier
void errMsg (int errorNum){
    switch(errorNum){
        case 1: cout << "Error: invalid command\n";
                return;
        case 2: cout << "Error: invalid argument\n";
                return;
        case 3: cout << "Error: invalid shape name\n";
                return;
        case 4: cout << "Error: shape name exists\n"; //This shouldn't run, as "name" is a veriable
                return;
        case 5: cout << "Error: shape name not found\n";
                return;
        case 6: cout << "Error: invalid shape type\n";
                return;
        case 7: cout << "Error: invalid value\n";
                return;
        case 8: cout << "Error: too many arguments\n";
                return;
        case 9: cout << "Error: too few arguments\n";
                return;
        case 10: cout << "Error: shape array is full\n";
                return;
    }
}

bool isNameAType(string name){
    //This function is just gonna compare our name to other keywords and shape types to look for overlap
    //if we find a match on reserved words, valid is false!
    for(int i = 2; i>=0; i--) {
        if( name == shapeTypesList[i]){
            return true;
        }
    }
    for(int i = 6; i>=0; i--) {
        if( name == keyWordsList[i]){
            return true;
        }
    }
    return false;
}

bool shapeNameExists(string name){
    //searches to see if name already exists in the array
    for (int i = 0 ; shapeCount>i ; i++){
        if (shapesArray[i]->getName() == name){
            return true;
        }
    }
    return false;
}

bool nameErrorCheck(string name, bool failFlag, bool eofFlag, bool existsIsError){
    if( failFlag ){ //if it failed to read into name
                
        if ( eofFlag ){
            // if input failed bc no more input, then too few arguments
            errMsg(9);
            return true;
        }else{
            //Not end of file, just failed. invalid argument then.
            //This shouldnt fire, pretty much anything can be a string i think
            errMsg(2);
            return true;

        }
    }else if ( isNameAType(name) ){
        //name is of a known type
        errMsg(3);
        return true;
    }else if ( shapeNameExists(name) ){
        //name already exists!
        
        //if the name existing is an error, then let them know, otherwise, the name existing is
        //not an error (we want the name to exist) and we'll return false (no error)
        if (existsIsError){
            cout << "Error: shape " << name << " exists\n";
            return true;
        }else return false;
    }
    
    //if name is supposed to exist, but we didn't find it, then there is an error
    if (!existsIsError){
        cout << "Error: shape " << name << " not found"<<endl;
        return true;
    }
    
    //name isnt supposed to exist, and we didn't find it, no errors
    return false;
}

bool typeErrorCheck(string type, bool failFlag, bool eofFlag){
    if( failFlag ){ //if it failed to read into name
                
        if ( eofFlag ){
            // if input failed bc no more input, then too few arguments
            errMsg(9);
            return true;
        }else{
            //Not end of file, just failed. invalid argument then.
            //This shouldnt fire, pretty much anything can be a string i think
            errMsg(2);
            return true;

        }
    }else if ( !isNameAType(type) ){
        //isNameAType returns true if string is a type, therefore, if name is NOT a type, ERROR
        errMsg(6);
        return true;
    }
    //no errors
    return false;
}

bool locErrorCheck(int loc, bool failFlag, bool eofFlag){
    if( failFlag ){ //if it failed to read into name
                
        if ( eofFlag ){
            // if input failed bc no more input, then too few arguments
            errMsg(9);
            return true;
        }else{
            //Not end of file, just failed. invalid argument then.
            errMsg(2);
            return true;

        }
    }else if ( loc < 0 ){
        //loc is a negative number, error
        errMsg(7);
        return true;
    }
    //no errors
    return false;
}

int findShape(string name){
    //searches to see if name already exists in the array
    for (int i = 0 ; shapeCount>i ; i++){
        if (shapesArray[i]->getName() == name){
            return i;
        }
    }
    return -1;//this shouldn't occur, name should be confirmed to exist prior
}

void deleteShapes(string name){
    int deleteEntry = -1;
    
    if (name == "all"){
        //if we're deleting all shapes, cycle through array deleting each object
        for(int i = 0; shapeCount > i ; i++){
            delete shapesArray[i];
            shapesArray[i] = NULL;
        }
        shapeCount = 0; //becsaue no shapes left
        
    }else{
        //find the entry where the shape to be deleted is stored
        deleteEntry = findShape(name);
        
        //delete the shape object
        delete shapesArray[deleteEntry];
        shapesArray[deleteEntry] = NULL;
        
        //we must now move all of the objects back by one space, so that there
        //isn't a gap in the shapesArray
        deleteEntry++;
        for( ; deleteEntry < shapeCount ; deleteEntry++){
            shapesArray[deleteEntry-1] = shapesArray[deleteEntry];
            shapesArray[deleteEntry] = NULL; //this will ensure there is no duplicates in the array
        }
    }
    return;
}

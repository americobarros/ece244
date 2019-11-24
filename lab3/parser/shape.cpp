//
//  shape.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

#include "shape.h"

// ECE244 Student: 
// Write the implementation (and only the implementation) of the shape
// class below
shape::shape(string n, string t, int x_loc, int y_loc, int x_sz, int y_sz){
    name = n;
    type = t;
    x_location = x_loc;
    y_location = y_loc;
    x_size = x_sz;
    y_size = y_sz;
    
}
    // Accessors
string shape::getType(){
    return type;
}              // Returns the type 
string shape::getName(){
    return name;
}              // Returns the name of the shape
int shape::getXlocation(){
    return x_location;
}            // Returns location of the shape on the x-axis
int shape::getYlocation(){
    return y_location;
}            // Returns location of the shape on the y-axis
int shape::getXsize(){
    return x_size;
}                // Returns the size of the shape in the x-dimension
int shape::getYsize(){
    return y_size;
}                // Returns the size of the shape in the y-dimension

// Mutators
void shape::setType(string t){
    type = t;
    return;
}        // Sets the type (see globals.h)
void shape::setName(string n){
    name = n;
}        // Sets the name of the shape
void shape::setXlocation(int x_loc){
    x_location = x_loc;
    return;
}  // Sets location of the shape on the x-axis
void shape::setYlocation(int y_loc){
    y_location = y_loc;
    return;
}  // Sets location of the shape on the y-axis
void shape::setXsize(int x_sz){
    x_size = x_sz;
    return;
}       // Sets size of the shape in the x-dimension
void shape::setYsize(int y_sz){
    y_size = y_sz;
    return;
}       // Sets size of the shape in the y-dimension

void shape::setRotate(int angle){
    rotation = angle;
    return;
}     // sets the rotation of the shape

// Utility methods
void shape::draw(){
    cout << name << ": " << type << " " << x_location << " " << y_location <<  " " << x_size << " " << y_size << endl;
    return;
}                  // Draws a shape; for this assignment it
                   // only prints the information of the shape




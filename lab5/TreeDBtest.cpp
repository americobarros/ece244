///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
///* 
// * File:   TreeDBtest.cpp
// * Author: Americo Barros
// *
// * Created on November 30, 2019, 11:57 PM
// */
//
//#include <cstdlib>
//#include "TreeNode.h"
//#include <string>
//#include "DBentry.h"
//#include "TreeDB.h"
//#include <iostream>
//using namespace std;
//
//
///*
// * 
// */
//int main(void) {
//    TreeDB myTree;
//    DBentry* hello = new DBentry ("hello", 11111, true);
//    DBentry* goodbye = new DBentry ("goodbye", 0000, true);
//    cout<<myTree;
//    
//    myTree.insert(hello);
//    cout<<myTree;
//    
//    cout<<"using print";
//    myTree.print();
//    
//    myTree.insert(goodbye);
//    cout<<myTree;
//    
//    cout << "inserting a whole bunch";
//    myTree.insert(new DBentry("a", 1234, false));
//    myTree.insert(new DBentry("b", 1234, true));
//    myTree.insert(new DBentry("i", 1234, true));
//    myTree.insert(new DBentry("ho", 1234, false));
//    myTree.insert(new DBentry("j", 1234, true));
//    cout<<myTree;
//    
//    cout<<"probes: ";
//    myTree.printProbes();
//    
//    cout<<"active:";
//    myTree.countActive();
//    
////    string name;
////    int ip;
////    bool state;
////    cin >> name >> ip >> state;
////    myTree.insert(new DBentry(name, ip, state));
////    cout << myTree;
//    
//    
////    myTree.find(name);
////    cout<<"probes after finding '" << name << "':";
////    myTree.printProbes();
//    
//    cout << "CP 1" << endl << "active: ";
//    myTree.remove ("b");
//    myTree.countActive();
//    myTree.find("j");
//    cout << "Probes: ";
//    myTree.printProbes();
//    cout << myTree;
//    
//    cout << "CP 2" << endl << "active: ";
//    myTree.remove ("goodbye");
//    myTree.countActive();
//    myTree.find("b");
//    cout << "Probes: ";
//    myTree.printProbes();
//    cout << myTree;
//    
//    cout << "CP 3" << endl << "active: ";
//    myTree.remove ("i");
//    myTree.countActive();
//    myTree.find("j");
//    cout << "Probes: ";
//    myTree.printProbes();
//    cout << myTree;
//    
//    cout << "CP 4" << endl << "active: ";
//    myTree.clear();
//    myTree.countActive();
//    myTree.find("j");
//    cout << "Probes: ";
//    myTree.printProbes();
//    cout << myTree;
//    
//    
//    
//    
//    
//
//    return 0;
//}
//

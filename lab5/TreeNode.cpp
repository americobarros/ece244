/* 
 * File:   TreeNode.cpp
 * Author: Americo Barros
 *
 * Created on November 26, 2019, 12:25 AM
 */

#include "TreeNode.h"
#include <cstdlib>
#include <string>
#include "DBentry.h"

using namespace std;

// A useful constructor
TreeNode::TreeNode(DBentry* _entryPtr){
    this->entryPtr = _entryPtr;
    this->left = nullptr;
    this->right = nullptr;
}

// the destructor
TreeNode::~TreeNode(){
    //Since we aren't creating the _entryPtr within the constructor, we shouldn't delete it in the destructor
}

// sets the left child of the TreeNode.
void TreeNode::setLeft(TreeNode* newLeft){
    //Once again will allow Tree class deal with the logistics, this will basically just act as a mutator
    this->left = newLeft;
}

// sets the right child of the TreeNode
void TreeNode::setRight(TreeNode* newRight){
    //letting Tree class deal with freeing memory, just an accessor
    this->right = newRight;
    
}

// gets the left child of the TreeNode.
TreeNode* TreeNode::getLeft() const{
    return (this->left);
}

// gets the right child of the TreeNode
TreeNode* TreeNode::getRight() const{
    return (this->right);
}

// returns a pointer to the DBentry the TreeNode contains. 
DBentry* TreeNode::getEntry() const{
    return (this->entryPtr);
}


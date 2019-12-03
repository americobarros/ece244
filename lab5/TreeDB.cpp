
/* 
 * File:   TreeDB.cpp
 * Author: Americo Barros
 *
 * Created on November 26, 2019, 1:20 PM
 */

#include <cstdlib>
#include "TreeDB.h"
#include "TreeNode.h"
#include <iostream>

using namespace std;

/*
 * 
 */

// the default constructor, creates an empty database.
TreeDB::TreeDB(){
    this->root = nullptr;
    this->probesCount = 0;
}

// the destructor, deletes all the entries in the database.
TreeDB::~TreeDB(){
    this->clear();
}





// inserts the entry pointed to by newEntry into the database. 
// If an entry with the same key as newEntry's exists 
// in the database, it returns false. Otherwise, it returns true.
bool TreeDB::insert(DBentry* newEntry){
    if(this->root == nullptr){
        this->root = new TreeNode (newEntry);
        return true;
    }

    return(this->insertionHelper(this->root, newEntry));
    
}
 

bool TreeDB::insertionHelper(TreeNode* currentNode, DBentry* newEntry){
    
    this->probesCount = probesCount+1;
    
    
    if(currentNode -> getEntry() -> getName() == newEntry->getName()){
        // Names are the same, insertion not completed
        
        delete newEntry;
        
        return false;
    }
    else if (currentNode -> getEntry() -> getName() < newEntry->getName()){
        // Must insert higher alphabetically than the current key
        if(currentNode-> getRight() == nullptr){
            
            currentNode->setRight(new TreeNode(newEntry));
            return true; // Successfully inserted right
        
        } 
        return ( this->insertionHelper( currentNode->getRight(), newEntry ) );
    }
    else{
        // Must insert lower alphabetically than the current key
        if(currentNode-> getLeft() == nullptr){
            
            currentNode->setLeft(new TreeNode(newEntry));
            return true; // Successfully inserted left
        
        } 
        return ( this->insertionHelper( currentNode->getLeft(), newEntry ) );
    }
}


// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount
DBentry* TreeDB::find(string name){ //parent is added, not required to include when calling find, 
    this->probesCount = 0;
    
    //Case Empty DB
    if (this->root == nullptr) return nullptr;
    
    TreeNode* parent = this->root;//this will just be a dummy variable
    TreeNode* node= this->findTreeNode(name, this->root, parent);
    
    if (node == nullptr)return nullptr;
    else return (node->getEntry());
}

DBentry* TreeDB::find(string name, TreeNode*& parent){ //parent is added, useful if you would like to keep track of parent
    this->probesCount = 0;
    
    //Case Empty DB
    if (this->root == nullptr) return nullptr;
    
    TreeNode* node= this->findTreeNode(name, this->root, parent);
    
    if (node == nullptr)return nullptr;
    else return (node->getEntry());
}

//Helper to finder - recursive implementation, returns found node, otherwise nullptr
TreeNode* TreeDB::findTreeNode(string name, TreeNode* currentNode, TreeNode*& lastNode){
    
    this->probesCount = probesCount+1;
    
    if(currentNode -> getEntry() -> getName() == name){
        // names the same, key already exists
        return currentNode;
    }
    else if (currentNode -> getEntry() -> getName() < name){
        // Must find at higher alphabetically than the current key
        if(currentNode-> getRight() == nullptr){
            return nullptr; // Should be to the right, but there's nothing to the right, return null
        } 
        lastNode = currentNode;
        return (this -> findTreeNode(name, currentNode -> getRight(), lastNode));
    }
    else{
        // Must find lower alphabetically than the current key
        if(currentNode->getLeft() == nullptr){
            return nullptr;// Should be to the left but there's nothing to the left, return null
        }
        lastNode = currentNode;
        return (this->findTreeNode(name, currentNode->getLeft(), lastNode));
    }
}



// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
bool TreeDB::remove(string name){
    
    TreeNode* parent = this->root;
    TreeNode* toRemove = this->findTreeNode(name, this->root, parent);
    
    if(toRemove != nullptr){//If the entry exists in the database
        
        
        //Case 1: No children
        if(toRemove->getLeft() == nullptr && toRemove->getRight() == nullptr){
            
            // if we are deleting the root node, then we do not need to worry about resetting the left and right
            if(toRemove == this->root){
                this->root = nullptr;
            }else{
                // If parent is alphabetically after name, then the deleted node is to the left, otherwise
                // deleted node is to the right and must set to nullptr
                if(parent->getEntry()->getName() < name){
                    parent->setRight(nullptr);
                }
                else if(parent->getEntry()->getName() > name){
                    parent->setLeft(nullptr);
                }
                
            }
            delete toRemove->getEntry();
            delete toRemove;
            return true;
        }
        //Case 2: One child is null, other is not
        if(toRemove->getLeft()!=nullptr && toRemove->getRight()==nullptr){
            // Right of toRemove is null, must replace node with left
            
            // if we are deleting the root node, then we do not need to worry about resetting the left and right
            if(toRemove == this->root){
                this->root = toRemove->getLeft();
            }else{
                if(parent->getLeft() == toRemove){
                    // The node to be deleted was to the left of parent
                    parent->setLeft(toRemove->getLeft());
                }
                else if(parent->getRight() == toRemove){
                    // The node to be deleted was to the right of parent
                    parent->setRight(toRemove->getLeft());
                }
            }
            delete toRemove->getEntry();
            delete toRemove;
            return true;
        }
        else if(toRemove->getRight()!=nullptr && toRemove->getLeft()==nullptr){
            // Left of toRemove is null, must replace node with left
            
            // if we are deleting the root node, then we do not need to worry about resetting the left and right
            if(toRemove == this->root){
                this->root = toRemove->getRight();
            }else{
                if(parent->getLeft() == toRemove){
                    //The node to be deleted was to the left of parent
                    parent->setLeft(toRemove->getRight());
                }
                else if(parent->getRight() == toRemove){
                    //The node to be deleted was to the right of parent
                    parent->setRight(toRemove->getRight());
                }
            }
            delete toRemove->getEntry();
            delete toRemove;
            return true;
        }
        
        //Case 3: Neither children are null
        // We must find the node that is furthest right in the left subtree of toRemove, then use that
        // to replace toRemove
        if(toRemove->getLeft() != nullptr && toRemove->getRight() != nullptr){
            TreeNode* parentOfRight = toRemove->getLeft(); //This will be the parent of the node that comes (alphabetically) before toRemove
            TreeNode* rightNode = this->findRightNode(toRemove->getLeft(), parentOfRight);
            
            // This ensures that if the rightNode has a left child, it leaves the left child
            // Behind, in the position where rightNode used to be
            // Also, case: if rightNode has no left, great! nullptr was set to right of parent
            // also, case: if there parentOfRight==rightNode (there was nothing to the right of
            // toRemove->left) then we just assign nullptrs, no problem!
            parentOfRight->setRight(rightNode->getLeft()); 
            
            
            
            // This handles getting rightNode to have the proper children
            // Case, if rightNode is immediately to the left of toRemove, then leave
            // left of rightNode as nullptr (otherwise inf loop)
            if(toRemove->getLeft() != rightNode) rightNode->setLeft(toRemove->getLeft());
            else rightNode->setLeft(nullptr);
            rightNode->setRight(toRemove->getRight());
            // We have the node we want to insert, now we must delete toRemove and insert in its
            // place
            
            // if we are deleting the root node, then we do not need to worry about whether we are inserting to left or right.
            if(toRemove == this->root){
                this->root = rightNode;
            }else{
                if(parent->getLeft() == toRemove){
                    //The node to be deleted is to the left of parent
                    parent->setLeft(rightNode);
                }
                else if(parent->getRight() == toRemove){
                    //The node to be deleted was to the right of parent
                    parent->setRight(rightNode);
                }
            }
            
            delete toRemove->getEntry();
            delete toRemove;
            return true;
        }
    }
    //Couldn't find a node to remove
    return false;
}


TreeNode* TreeDB::findRightNode(TreeNode* currentNode, TreeNode*& lastNode){
    //Finds and returns the right most node in the subtree currentNode
    
    //Must find at higher alphabetically than the current key
    if(currentNode-> getRight() == nullptr){
        //Should be to the right, but there's nothing to the right, return null
        return currentNode; 
    } 
    lastNode = currentNode;
    return (this -> findRightNode(currentNode -> getRight(), lastNode));
    
}

// deletes all the entries in the database.
void TreeDB::clear(){
    this->delete_TreeDB(this->root);
    this->root = nullptr;
}

// helper to clear, deletes left, then right, then current node
void TreeDB::delete_TreeDB(TreeNode* current){
    if(current != nullptr){
        delete_TreeDB(current->getLeft());
        delete_TreeDB(current->getRight());
        delete current->getEntry();
        delete current;
    }
    return;
}

// prints the number of probes stored in probesCount
void TreeDB::printProbes() const{
    cout<<(this->probesCount)<<endl;
}

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive () const{
    int totalCount = 0;
    this->countActiveHelper(this->root, totalCount);
    cout<<totalCount<<endl;
}

void TreeDB::countActiveHelper(TreeNode* current, int& count)const{
    if(current!=nullptr){
        if(current->getEntry()->getActive() == true){
            count++;
        }
        countActiveHelper(current->getLeft(),count);
        countActiveHelper(current->getRight(),count);
    }
}

void TreeDB::print()const{
    printTreeDB(this->root);
    return;
}

void TreeDB::printTreeDB(TreeNode* current)const{
    if(current!=nullptr){
        this->printTreeDB(current->getLeft());
        
        string activeState;
        if(current->getEntry()->getActive()) activeState = "active";
        else activeState = "inactive";
        cout << current->getEntry()->getName() << " : " << current->getEntry()->getIPaddress() << " : " << activeState << endl;
        
        this->printTreeDB(current->getRight());
        
    }
}


ostream& operator<< (ostream& out, const TreeDB& rhs){
    if(rhs.root != nullptr){
    	rhs.printTreeDB(rhs.root);
    }
    return out;
}

#ifndef _TREEDB_H
#define _TREEDB_H

#include "TreeNode.h"
#include "DBentry.h"

class TreeDB {

private:
   TreeNode* root;
   int probesCount;
   
   // Insertion Helper
   bool insertionHelper(TreeNode* currentNode, DBentry* newEntry);
   
   // Modified find which also returns the parent to the found node
   DBentry* find(string name, TreeNode*& parent);
   // Find helper
   TreeNode* findTreeNode(string name, TreeNode* currentNode, TreeNode*& lastNode);
   
   // Remove helper, finds the rightmost node on a tree
   TreeNode* findRightNode(TreeNode* currentNode, TreeNode*& lastNode);
   
   // countActive helper
   void countActiveHelper(TreeNode* current, int& count)const;
   
   // print/operator<< helper
   void printTreeDB(TreeNode* current)const;

public:
   // the default constructor, creates an empty database.
   TreeDB();

   // the destructor, deletes all the entries in the database.
   ~TreeDB();
   
   void delete_TreeDB(TreeNode* root);

   // inserts the entry pointed to by newEntry into the database. 
   // If an entry with the same key as newEntry's exists 
   // in the database, it returns false. Otherwise, it returns true.
   bool insert(DBentry* newEntry); 
   

   // searches the database for an entry with a key equal to name.
   // If the entry is found, a pointer to it is returned.
   // If the entry is not found, the NULL pointer is returned.
   // Also sets probesCount
   DBentry* find(string name);
   
   // deletes the entry with the specified name (key)  from the database.
   // If the entry was indeed in the database, it returns true.
   // Returns false otherwise. If the node has 2 children,
   // remove and replace with the rightmost node, of the left to the node that is
   // being removed
   bool remove(string name);
   
	
   // deletes all the entries in the database.
   void clear();
    
   // prints the number of probes stored in probesCount
   void printProbes() const;
   
   // computes and prints out the total number of active entries
   // in the database (i.e. entries with active==true).
   void countActive () const;

   //print() is an alternate way to print the tree, sometimes helpful 
   void print()const;
   
   
    // Prints the entire tree, in ascending order of key/name
    friend ostream& operator<< (ostream& out, const TreeDB& rhs);
}; 

//// You *may* choose to implement the function below to help print the 
//// tree.  You do not have to implement this function if you do not wish to.
//ostream& operator<< (ostream& out, TreeNode* rhs);   
//   
#endif 


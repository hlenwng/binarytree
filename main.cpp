#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

/*
  Name: Helen Wang
  Date: Apr 7, 2023
  Program: Build a binary search tree, allowing user to add, delete,
  and search for values, and print out a 2d version of the tree.
 */

//Class for nodes used in binary tree
class btree {
  int data;
  btree* left;
  btree* right;

public:
  
  //Constructors
  btree(int nData) {
    data = nData;
    left = right = NULL;
  }
  //btree(int num);
  //~btree();

  //Set and get node functions
  void setLeft(btree* nLeft) {
    left = nLeft;
  }
  
  void setRight(btree* nRight) {
    right = nRight;
  }
  
  btree* getLeft() {
    return left;
  }
  
  btree* getRight() {
    return right;
  }
  
  void setData(int nData) {
    data = nData;
  }
  
  int getData() {
    return data;
  }
};

/*
struct btree{
  int data;
  btree* left;
  btree* right;
  };*/

//Function declarations 
void insert(btree* tree, int num);
void printTree(btree* tree, int space);
btree* deleteit(btree* tree, int deleteNum);
int search(btree* tree, int douexist);
btree* nextValue(btree* tree);

int main() {
  //Intialize variables
  btree* tree = new btree(-1);
  //btree *root = NULL;
  //b.insert(root, 20);
  //btree b = NULL;
  
  bool playing = true;
  char input[20];

  //Read in user input (different commands)
  while (playing == true) {
    cout << "[ADD] [REMOVE] [SEARCH] [PRINT] or [QUIT]" << endl;
    
    cin.get(input, 20, '\n');
    cin.ignore();
    
    if(strcmp(input, "ADD") == false) {

      cout << "console or file" << endl;
      cin.get(input, 20, '\n');
      cin.ignore();

      //Read in values from user
      if(strcmp(input, "console") == false) {
	cout << "Please enter numbers (1-999) with a space between each #: ";

	char nums[30];

	cin.get(nums, 30, '\n');
	cin.ignore();
	
	for (int i = 0; i < strlen(nums); i++) {
	  
	  //cout << "letter " << i << " " << nums[i] << endl;
	  
	  if(!isspace(nums[i])) {
	    if(isdigit(nums[i])) {
	      //cout << "inserting: " << nums[i] << endl;
	      //if inserting the root
	      insert(tree, nums[i] - '0');
	    }
	  }
	}	
	cout << "#(s) have been added" << endl;
      }

      //Read in values from a file
      if(strcmp(input, "file") == false) {
	fstream file;
	file.open("number.txt");
	//file.open(number);

	int input = 0;

	while(file >> input) {
	  cout << input << endl;
	  insert(tree, input);
	}
	file.close();
      }
    }
      
    else if(strcmp(input, "REMOVE") == false) {
      cout << "enter in the # you wish to delete for" << endl;
      int deleteNum = 0;
      cin >> deleteNum;
      cin.ignore();

      int found = search(tree, deleteNum);

      if(found == deleteNum) {
	tree = deleteit(tree, deleteNum);
	cout << deleteNum << " has been deleted" << endl;
      }
      else if(found != deleteNum) {
        cout << "value isn't in the tree" << endl;
      }
    }
    
    else if(strcmp(input, "PRINT") == false) {
      //print(root);
      cout << endl;
      printTree(tree, 0);
      //      b.print(root);
    }
    
    else if(strcmp(input, "SEARCH") == false) {
      cout << "enter in the # you wish to search for" << endl;
      int searchNum = 0;
      cin >> searchNum;
      cin.ignore();

      int found = search(tree, searchNum);

      if(found == searchNum) {
	cout << "value is in the tree" << endl;
      }
      else if(found != searchNum) {
	cout << "value isn't in the tree" << endl;
      }
    }
    
    else if(strcmp(input, "QUIT") == false) {
      playing = false;
    }
    else {
      cout << "Please enter a valid command" << endl;
    }
  }
}

/*
btree* create(int data) {
  btree* newB = new btree();
    newB->data = data;
    newB->left = NULL;
    newB->right = NULL;
    return newB;
    }*/

//Insert value correctly into tree
void insert(btree* tree, int num) {
  if(tree->getData() == -1) {
    //insert the first node
    tree->setData(num);
    //    root=create(num);
    //    root = new btree(num);
    return;
  }
  else{
    //left or righth
    if(num < tree->getData() && tree->getLeft()) {
      tree = tree->getLeft();
      insert(tree, num);
    }
    else if(num < tree->getData() && !tree->getLeft()) {
      btree* newB = new btree(num);
      tree->setLeft(newB);
      return;
    }

    if(num > tree->getData() && tree->getRight()) {
      tree = tree->getRight();
      insert(tree, num);
    }
    else if(num > tree->getData() && !tree->getRight()) {
      btree* newB = new btree(num);
      tree->setRight(newB);
      return;
    }
  }

  cout << "inserted" << endl;
}

//Search for a particular value in tree
int search(btree* tree, int douexist) {
  //if it equals the root
  if(!tree || tree->getData() == douexist) {
    return tree->getData();
  }

  //if number is bigger than root
  if(tree->getData() < douexist) {
    //bottom of tree
    if(!tree->getRight()) {
      return tree->getData();
    }
    return search(tree->getRight(), douexist);
  }
  
  //if number is smaller than root
  else {
    //bootom of tree
    if(!tree->getLeft()) {
      return tree->getData();
    }
    return search(tree->getLeft(), douexist);
  }
}

//Print 2d version of tree
void printTree (btree* tree, int space) {
  if(!tree || tree->getData() == -1) {

    cout << "tree is empty" << endl;
    return;
  }

  if(tree->getRight())
    printTree(tree->getRight(), space+1);

  for(int i = 0; i < space; i++) {
      cout << "\t";
  }
  cout << tree->getData() << endl;

  if(tree->getLeft())  
    printTree(tree->getLeft(), space+1);
  
  /*
  if(tree->getLeft()) {
    printTree(root, tree->getLeft(), space+1);
  }
  
  for(int i=0; i<space; i++){
    cout << "\t";
  }
  
  cout << tree->getData() << endl;
  
  if(tree->getRight()) {
    printTree(root, tree->getRight(), space+1);
  }
  */
}

//Delete specific value from tree and correctly sort it afterwards
btree* deleteit(btree* tree, int deleteNum) {
  //if tree empty
  if(!tree) {
    return tree;
  }

  //if number is bigger than node, traverse to right node
  if(tree->getData() < deleteNum) {
    tree->setRight(deleteit(tree->getRight(), deleteNum));
  }
  //if number is smaller than node, traverse to left node
  else if(tree->getData() > deleteNum) {
    tree->setLeft(deleteit(tree->getLeft(), deleteNum));
  }

  //if node is found
  else if(tree->getData() == deleteNum) {
    //if no children nodes
    if(!tree->getLeft() && !tree->getRight()) {
      return NULL;
    }
    //if it has one child (left or right)
    else if(!tree->getLeft()) {
      btree* temp = tree->getRight();
      delete tree;
      return temp;
    }
    else if(!tree->getRight()) {
      btree* temp = tree->getLeft();
      delete tree;
      return temp;
    }

    //if 2 children are present
    btree* temp  = nextValue(tree->getRight());
    tree->setData(temp->getData());
    tree->setRight(deleteit(tree->getRight(), temp->getData()));
  }
  return tree;
}

//function to find next smallest number in tree
btree* nextValue(btree* tree) {
  btree* current = tree;
  //traverse to bottom of tree
  while(current && current->getLeft()) {
    current = current->getLeft();
  }
  return current;
}

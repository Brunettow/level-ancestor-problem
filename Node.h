#include <list>
#include <iostream>

using namespace std;

#ifndef Node_H
#define Node_H

class Node {
public:
    int id;
   	list<int> children;
   	Node(int id=-1){
   		this->id=id;
   													
   	}

   	void addChild(int childId){						
   		this->children.push_back(childId);
   										
   	}
};

#endif


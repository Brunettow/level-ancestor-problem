#include "Node.h"
#include <fstream>
#include <unordered_map>
#include <iterator>
#include <vector>
#include <limits>

using namespace std;

vector<Node*> nodes; //returns pointer of a node which its id is same with its index
vector<int> preordered; // in index equals to node id, keeps given index  to that node in preordered traversal
vector<int> getDepth; // keeps depths of nodes in preordered traversal
vector<int> getIndex; // keeps real id's of nodes
vector<list<int>> hashTable; // nodes keeped according to depths

int anchestorId, maxDepth;
int index = 0;
int depth = 0;

list<int> anchestors;

void preorderTrav(Node* node){
				
	preordered[index]=node->id; // nodeid -> index
	getIndex[node->id]=index; // index -> node id
	getDepth[index]=depth; // index -> depth
	hashTable[depth].push_back(index); //put node to the hashTable array

	index++;
	depth++;  //depth
	
	for(auto childId : node->children){ //for every children preorder traverse
		preorderTrav(nodes[childId]);
	}

	depth--;
}

int main(int argc, char const *argv[]){

	string infile_name = argv[1];
	string outfile_name = argv[2];

	ifstream infile;
	infile.open(infile_name);

	ofstream outfile;
	outfile.open(outfile_name);

	int numbOfVertices, parentId, id, distance, numbOfQueries; //distance is depth difference with node and its anchestor

	infile >> numbOfVertices;

	nodes.resize(numbOfVertices);
	preordered.resize(numbOfVertices);
	hashTable.resize(numbOfVertices);  
	getIndex.resize(numbOfVertices);
	getDepth.resize(numbOfVertices);

	for (int i = 0; i < numbOfVertices; ++i){  //constructing tree
							 															
		nodes[i] = new Node(i);
		infile >> parentId;									

		if(!(parentId<0)){								
			nodes[parentId]->addChild(i);
		}										
	}

	preorderTrav(nodes[0]); //preordered traversal, constructs needed vector at the same time	

	infile >> numbOfQueries;
	int  index, depthOfNode, newDepth, anchId, nodesAnch;

	for (int i = 0; i < numbOfQueries; ++i){  //constructing input list
		infile >> id >> distance;
		
		index = getIndex[id]; //bu node a traverse de verilen sayı
		depthOfNode = getDepth[index]; //traverse ederken node ların depthleri
		newDepth = depthOfNode - distance; //depth o the anchestor
		if(newDepth>=0){
			for(auto anch : hashTable[newDepth]){ // anchestor bu listede indexten küçük en büyük sayı
				if(anch < index){ // anch are the node id's in given depth
					nodesAnch = anch; //we want the anchestor with biggest id that is smaller than the index
				} else {
					break;
				}
			}	
			anchId = preordered[nodesAnch]; //real id of the anchestor
		
		} else {
			anchId = -1; //there is no such node so id is -1
		}
		anchestors.push_back(anchId);
	}
	
	for(auto a : anchestors){
		outfile << a << endl;
	}

	for (int i = 0; i < numbOfVertices; ++i){
		delete nodes[i];
	}

	infile.close();
	outfile.close();

	return 0;
}

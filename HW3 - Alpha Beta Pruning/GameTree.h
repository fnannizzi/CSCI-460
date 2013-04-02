#ifndef GAMETREE_H
#define GAMETREE_H

#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>
#include "Node.h"

using namespace std;

class GameTree {

	public:
	// Data
	Node* root;

	// Methods	
	GameTree();
	~GameTree();
	void initializeTree();
	void printTree();
	void printSuccessors(Node*, int);
			
};

GameTree::GameTree(){}

GameTree::~GameTree(){}

void GameTree::initializeTree(){
	// Initialize level a
	root = new Node("a", 0);
	root->predecessor = NULL;
	cout << "Initialized level a" << endl;
	
	//Initialize level b
	for(int i = 0; i < 2; i++){
		Node* b = new Node("b", i);
		b->predecessor = root;
		root->successors.push_back(b);
	}
	cout << "Initialized level b" << endl;
	
	// Initialize level c
	for(int i = 0; i < root->successors.size(); i++){
		Node* c1 = new Node("c", (i*2));
		c1->predecessor = root->successors[i];
		root->successors[i]->successors.push_back(c1);
		Node* c2 = new Node("c", ((i*2)+1));
		c2->predecessor = root->successors[i];
		root->successors[i]->successors.push_back(c2);
	}
	cout << "Initialized level c" << endl;
	
	// Initialize level d0
	for(int i = 0; i < 3; i++){
		Node* d0 = new Node("d", i);
		root->successors[0]->successors[0]->successors.push_back(d0);
	}
	cout << "Initialized level d0" << endl;
	
	// Initialize level d1
	Node* d1 = new Node("d", 3);
	root->successors[0]->successors[1]->successors.push_back(d1);
	d1 = new Node("d", 4);
	root->successors[0]->successors[1]->successors.push_back(d1);
	cout << "Initialized level d1" << endl;
	
	// Initialize level d2
	for(int i = 5; i <= 8; i++){
		Node* d2 = new Node("d", i);
		root->successors[1]->successors[(i/7)]->successors.push_back(d2);
	}	
	cout << "Initialized level d2" << endl;
	
	// Initialize level e
	Node* e = new Node("e", 0, -1);
	root->successors[0]->successors[0]->successors[0]->successors.push_back(e);
	e = new Node("e", 1, 2);
	root->successors[0]->successors[0]->successors[1]->successors.push_back(e);
	e = new Node("e", 2, 3);
	root->successors[0]->successors[0]->successors[1]->successors.push_back(e);
	e = new Node("e", 3, -5);
	root->successors[0]->successors[0]->successors[1]->successors.push_back(e);
	e = new Node("e", 4, 0);
	root->successors[0]->successors[0]->successors[2]->successors.push_back(e);
	e = new Node("e", 5, 4);
	root->successors[0]->successors[1]->successors[0]->successors.push_back(e);
	e = new Node("e", 6, 7);
	root->successors[0]->successors[1]->successors[0]->successors.push_back(e);
	e = new Node("e", 7, 2);
	root->successors[0]->successors[1]->successors[1]->successors.push_back(e);
	e = new Node("e", 8, 6);
	root->successors[0]->successors[1]->successors[1]->successors.push_back(e);
	e = new Node("e", 9, 9);
	root->successors[1]->successors[0]->successors[0]->successors.push_back(e);
	e = new Node("e", 10, 8);
	root->successors[1]->successors[0]->successors[0]->successors.push_back(e);
	e = new Node("e", 11, 1);
	root->successors[1]->successors[0]->successors[1]->successors.push_back(e);
	e = new Node("e", 12, 4);
	root->successors[1]->successors[1]->successors[0]->successors.push_back(e);
	e = new Node("e", 13, 0);
	root->successors[1]->successors[1]->successors[1]->successors.push_back(e);
	e = new Node("e", 14, 5);
	root->successors[1]->successors[1]->successors[1]->successors.push_back(e);
}

void GameTree::printTree(){
	int spaces = 60;
	
	cout <<	setw(spaces) << root->name << endl;
	cout << setw(spaces/4) << " ";
	printSuccessors(root, spaces);
	cout << endl;
	
	cout << setw(spaces/3) << " ";
	for(int i = 0; i < root->successors.size(); i++){
		printSuccessors(root->successors[i], (spaces/2));
		cout << setw(spaces/9) << " ";
	}
	cout << endl;
	
	cout << setw(spaces/6) << " ";
	for(int i = 0; i < root->successors.size(); i++){
		for(int j = 0; j < root->successors[i]->successors.size(); j++){
			printSuccessors(root->successors[i]->successors[j], (spaces/3));
			cout << setw(5) << " ";
		}
	}
	cout << endl;
	
	for(int i = 0; i < root->successors.size(); i++){
		for(int j = 0; j < root->successors[i]->successors.size(); j++){
			for(int k = 0; k < root->successors[i]->successors[j]->successors.size(); k++){
				printSuccessors(root->successors[i]->successors[j]->successors[k], (spaces/5));
			}
		}
	}
	cout << endl;
}

void GameTree::printSuccessors(Node* node, int spaces){
	for(int i = 0; i < node->successors.size(); i++){
		cout << setw(spaces/node->successors.size()) << node->successors[i]->name;
	}
}

#endif

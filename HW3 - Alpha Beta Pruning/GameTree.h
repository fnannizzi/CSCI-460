#ifndef GAMETREE_H
#define GAMETREE_H

#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>
#include <stdio.h>
#include "Node.h"

using namespace std;

class GameTree {

	public:
	// Data
	Node* root;
	int maxDepth;

	// Methods	
	GameTree();
	~GameTree();
	void initializeTree();
	void printTree();
	void printSuccessors(Node*, int);
	int alphaBetaMiniMax(Node*, int, int);
	void alphaBetaUpward(Node*);
	void alphaBetaDownward(Node*);
	void expandTree();
	string getBestMove();
			
};

#endif

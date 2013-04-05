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

GameTree::GameTree(){}

GameTree::~GameTree(){}

void GameTree::initializeTree(){
	maxDepth = 5;
	
	// Initialize level a
	root = new Node("a", 0, 1);
	root->setMinOrMax("max");
	root->predecessor = NULL;
	//cout << "Initialized level a" << endl;
	
	//Initialize level b
	for(int i = 0; i < 2; i++){
		Node* b = new Node("b", i, 2);
		b->setMinOrMax("min");
		b->predecessor = root;
		root->successors.push_back(b);
	}
	//cout << "Initialized level b" << endl;
	
	// Initialize level c
	for(int i = 0; i < root->successors.size(); i++){
		Node* c1 = new Node("c", (i*2), 3);
		c1->setMinOrMax("max");
		c1->predecessor = root->successors[i];
		root->successors[i]->successors.push_back(c1);
		Node* c2 = new Node("c", ((i*2)+1), 3);
		c2->setMinOrMax("max");
		c2->predecessor = root->successors[i];
		root->successors[i]->successors.push_back(c2);
	}
	//cout << "Initialized level c" << endl;
	
	// Initialize level d0
	for(int i = 0; i < 3; i++){
		Node* d0 = new Node("d", i, 4);
		d0->setMinOrMax("min");
		d0->predecessor = root->successors[0]->successors[0];
		root->successors[0]->successors[0]->successors.push_back(d0);
	}
	//cout << "Initialized level d0" << endl;
	
	// Initialize level d1
	Node* d1 = new Node("d", 3, 4);
	d1->setMinOrMax("min");
	d1->predecessor = root->successors[0]->successors[1];
	root->successors[0]->successors[1]->successors.push_back(d1);
	d1 = new Node("d", 4, 4);
	d1->setMinOrMax("min");
 	d1->predecessor = root->successors[0]->successors[1];
	root->successors[0]->successors[1]->successors.push_back(d1);
	//cout << "Initialized level d1" << endl;
	
	// Initialize level d2
	for(int i = 5; i <= 8; i++){
		Node* d2 = new Node("d", i, 4);
		d2->setMinOrMax("min");
		d2->predecessor = root->successors[1]->successors[(i/7)];
		root->successors[1]->successors[(i/7)]->successors.push_back(d2);
	}	
	//cout << "Initialized level d2" << endl;
	
	// Initialize level e
	Node* e = new Node("e", 0, 5, -1);
	e->setMinOrMax("max");
	e->predecessor = root->successors[0]->successors[0]->successors[0];
	root->successors[0]->successors[0]->successors[0]->successors.push_back(e);
	
	e = new Node("e", 1, 5, 2);
	e->setMinOrMax("max");
	e->predecessor = root->successors[0]->successors[0]->successors[1];
	root->successors[0]->successors[0]->successors[1]->successors.push_back(e);
	e = new Node("e", 2, 5, 3);
	e->setMinOrMax("max");
	e->predecessor = root->successors[0]->successors[0]->successors[1];
	root->successors[0]->successors[0]->successors[1]->successors.push_back(e);
	e = new Node("e", 3, 5, -5);
	e->setMinOrMax("max");
	e->predecessor = root->successors[0]->successors[0]->successors[1];
	root->successors[0]->successors[0]->successors[1]->successors.push_back(e);
	
	e = new Node("e", 4, 5, 0);
	e->setMinOrMax("max");
	e->predecessor = root->successors[0]->successors[0]->successors[2];
	root->successors[0]->successors[0]->successors[2]->successors.push_back(e);
	
	e = new Node("e", 5, 5, 4);
	e->setMinOrMax("max");
	e->predecessor = root->successors[0]->successors[1]->successors[0];
	root->successors[0]->successors[1]->successors[0]->successors.push_back(e);
	e = new Node("e", 6, 5, 7);
	e->setMinOrMax("max");
	e->predecessor = root->successors[0]->successors[1]->successors[0];
	root->successors[0]->successors[1]->successors[0]->successors.push_back(e);
	
	e = new Node("e", 7, 5, 2);
	e->setMinOrMax("max");
	e->predecessor = root->successors[0]->successors[1]->successors[1];
	root->successors[0]->successors[1]->successors[1]->successors.push_back(e);
	e = new Node("e", 8, 5, 6);
	e->setMinOrMax("max");
	e->predecessor = root->successors[0]->successors[1]->successors[1];
	root->successors[0]->successors[1]->successors[1]->successors.push_back(e);
	
	e = new Node("e", 9, 5, 9);
	e->setMinOrMax("max");
	e->predecessor = root->successors[1]->successors[0]->successors[0];
	root->successors[1]->successors[0]->successors[0]->successors.push_back(e);
	e = new Node("e", 10, 5, 8);
	e->setMinOrMax("max");
	e->predecessor = root->successors[1]->successors[0]->successors[0];
	root->successors[1]->successors[0]->successors[0]->successors.push_back(e);
	
	e = new Node("e", 11, 5, 1);
	e->setMinOrMax("max");
	e->predecessor = root->successors[1]->successors[0]->successors[1];
	root->successors[1]->successors[0]->successors[1]->successors.push_back(e);
	
	e = new Node("e", 12, 5, 4);
	e->setMinOrMax("max");
	e->predecessor = root->successors[1]->successors[1]->successors[0];
	root->successors[1]->successors[1]->successors[0]->successors.push_back(e);
	
	e = new Node("e", 13, 5, 0);
	e->setMinOrMax("max");
	e->predecessor = root->successors[1]->successors[1]->successors[1];
	root->successors[1]->successors[1]->successors[1]->successors.push_back(e);
	e = new Node("e", 14, 5, 5);
	e->setMinOrMax("max");
	e->predecessor = root->successors[1]->successors[1]->successors[1];
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

int GameTree::alphaBetaMiniMax(Node* node, int alpha, int beta){
	if(node->certainValue){
		cout << "Expanding leaf Node " << node->name << " with value: " << node->value << endl;
	}
	else {
		cout << "Expanding " << node->getMinOrMax() << " Node " << node->name << ": " << node->getAlphaBeta() << endl;
	}
	//cout << "Num successors: " << node->successors.size() << endl;
	node->expanded = true;

	if(!node->successorsExpanded()) {
		//cout << "Not all successors have been expanded." << endl;
		if(node->predecessor != NULL){
			/*cout << "Predecessor " << node->predecessor->getMinOrMax() 
			<< " Node " << node->predecessor->name << ": " 
			<< node->predecessor->getAlphaBeta() << endl;
			*/
			int nextSuccessor = node->getIndexNextUnexpandedSuccessor();
			alphaBetaDownward(node->successors[nextSuccessor]);
			return alphaBetaMiniMax(node->successors[nextSuccessor], alpha, beta);
		}
		else { // at root
			int nextSuccessor = node->getIndexNextUnexpandedSuccessor();
			alphaBetaDownward(node->successors[nextSuccessor]);
			return alphaBetaMiniMax(node->successors[nextSuccessor], alpha, beta);
		}
	}
	
	restart: 
	//cout << "All successors of node have been expanded." << endl;
	while(node->predecessor != NULL){ // while not at root
		//cout << "Backtracking." << endl;	
		//cout << "Num successors of predecessor: " << node->predecessor->successors.size() << endl;
		//cout << endl;
		alphaBetaUpward(node);
		if(node->predecessor->successorsExpanded()){ // if the predecessor's successors are also all expanded
			//cout << "Predecessor's successors are all expanded." << endl;
			node = node->predecessor; // backtrack
			node->setValue();
			//cout << "Node " << node->name << " value: " << node->value << endl;
		}
		else{ // not all of the successors are expanded
			//cout << "Predecessor's successors not expanded." << endl;
			node = node->predecessor; // backtrack
			break;
		}
	}
	int nextSuccessor = node->getIndexNextUnexpandedSuccessor();
	if(nextSuccessor != -1){ // not sure if at root, or unexpanded successors
		//cout << "Next successor found." << endl;


		if(!(node->alpha >= node->beta)){
			int nextSuccessor = node->getIndexNextUnexpandedSuccessor();
			alphaBetaDownward(node->successors[nextSuccessor]);
			node = node->successors[nextSuccessor];
			//cout << "Next node " << node->getMinOrMax() << " Node " << node->name << ": " << node->getAlphaBeta() << endl;
			return alphaBetaMiniMax(node, alpha, beta);
		}
		else {
			for(int i = 0; i < node->successors.size(); i++){
				if(!node->successors[i]->expanded){
					if(node->successors[i]->isMax()){
						cout << "Skipping expansion of Node " << node->successors[i]->name 
						<< " because it cannot make alpha higher."<< endl;
					}
					else {
						cout << "Skipping expansion of Node " << node->successors[i]->name 
						<< " because it cannot make beta lower."<< endl;
					}
				}
			}
			goto restart;
		}
	}
	else { // no successors found
		root->setValue();
		return root->value;
	}
}

void GameTree::alphaBetaDownward(Node* node){
	if(node->predecessor != NULL){
		if(!node->certainValue){
			node->alpha = node->predecessor->alpha;
			node->beta = node->predecessor->beta;
		}
	}
	/*cout << "Predecessor " << node->predecessor->getMinOrMax() 
	<< " Node " << node->predecessor->name << ": " 
	<< node->predecessor->getAlphaBeta() << endl;	*/
}

void GameTree::alphaBetaUpward(Node* node){
	if(node->predecessor != NULL){
		if(node->predecessor->isMax()){ // parent node is a MAX
			if(node->certainValue){
				if(node->predecessor->alpha < node->value){
					node->predecessor->alpha = node->value;
				}
			}
			else if(node->predecessor->alpha < node->beta){
				node->predecessor->alpha = node->beta;
			}	
		}
		else { // parent node is a MIN
			if(node->certainValue){
				if(node->predecessor->beta > node->value){
					node->predecessor->beta = node->value;
				}
			}
			else if(node->predecessor->beta > node->alpha){
				node->predecessor->beta = node->alpha;
			}
		}
	}
	/*cout << "Predecessor " << node->predecessor->getMinOrMax() 
	<< " Node " << node->predecessor->name << ": " 
	<< node->predecessor->getAlphaBeta() << endl;*/
}

void GameTree::expandTree(){
	int a = alphaBetaMiniMax(root, -99, 99);
	cout << "Expansions completed." << endl;
	
	cout << "Value of Max Node A = " << root->value << endl;
	
	cout << "Move that Max Node A would make is = " << getBestMove() << endl;
	
}

string GameTree::getBestMove(){
	int index = 0;
	for(int i = 0; i < root->successors.size(); i++){
		if(root->successors[i]->value > root->successors[index]->value){
			index = i;
		}
	}
	return root->successors[index]->name;
}

#endif

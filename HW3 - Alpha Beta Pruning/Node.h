#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Node {

	enum MinOrMax { MIN, MAX };

	public:
	//Data
		string name, level;
		int depth, number, alpha, beta, value;
		bool expanded, certainValue;
		MinOrMax minOrMax;
		Node* predecessor;
		vector<Node*> successors;
	
	// Methods	
		Node(string, int, int);
		Node(string, int, int, int);
		~Node();
		void setMinOrMax(string);
		string getMinOrMax();
		bool isMax();
		string getAlphaBeta();
		void setValue();
		string makeName(string, int);
		bool successorsExpanded();
		int getIndexNextUnexpandedSuccessor();
};

#endif

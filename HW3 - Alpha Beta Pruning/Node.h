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
		int number, alpha, beta, value;
		MinOrMax minOrMax;
		Node* predecessor;
		vector<Node*> successors;
	
	// Methods	
		Node(string, int);
		Node(string, int, int);
		~Node();
		void setMinOrMax(string);
		string getMinOrMax();
		string makeName(string, int);
};

Node::Node(string l, int n){
	level = l;
	number = n;
	name = makeName(level, number);
	alpha = -99;
	beta = 99;
	value = 0;
}

Node::Node(string l, int n, int v){
	level = l;
	number = n;
	name = makeName(level, number);
	alpha = -99;
	beta = 99;
	value = v;
}

Node::~Node(){}

void Node::setMinOrMax(string m){
	if(m == "min"){
		minOrMax = MIN;
	}
	else if(m == "max"){
		minOrMax = MAX;
	}
}

string Node::getMinOrMax(){
	if(minOrMax == MIN){
		return "min";
	}
	else if(minOrMax == MAX){
		return "max";
	}
}

string Node::makeName(string l, int n){
	stringstream ss;
	ss << n;
	string temp = ss.str();
	l += temp;
	return l;
}

#endif

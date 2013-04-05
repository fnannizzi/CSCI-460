#include "Node.h"

Node::Node(string l, int n, int d){
	level = l;
	depth = d;
	number = n;
	name = makeName(level, number);
	alpha = -99;
	beta = 99;
	value = -100;
	expanded = false;
	certainValue = false;
}

Node::Node(string l, int n, int d, int v){
	level = l;
	depth = d;
	number = n;
	name = makeName(level, number);
	alpha = -99;
	beta = 99;
	value = v;
	expanded = false;
	certainValue = true;
}

Node::~Node(){}

bool Node::successorsExpanded(){
	bool expanded = true;
	for(int i = 0; i < successors.size(); i++){
		if(!successors[i]->expanded){
			expanded = false;
		}
	}
	return expanded;
}

int Node::getIndexNextUnexpandedSuccessor(){
	for(int i = 0; i < successors.size(); i++){
		if(!successors[i]->expanded){
			return i;
		}
	}
	return -1;
}

void Node::setValue(){
	if(value == -100){
		value = successors[0]->value;
		for(int i = 0; i < successors.size(); i++){
			if(minOrMax == MIN){
				if(successors[i]->value < value ){
					value = successors[i]->value;
				}
			}
			else {
				if(successors[i]->value > value ){
					value = successors[i]->value;
				}
			}
		}
	}
}

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
		return "MIN";
	}
	else if(minOrMax == MAX){
		return "MAX";
	}
}

bool Node::isMax(){
	if(minOrMax == MAX){
		return true;
	}
	else {
		return false;
	}
}

string Node::getAlphaBeta(){
	stringstream ss;
	string line = "alpha = ";
	if(alpha == -99){
		line += "negative infinity";
	}
	else {
		ss << alpha; 
		line += ss.str();
	}
	
	line += " beta = ";
	ss.str("");
	if(beta == 99){
		line += "positive infinity";
	}
	else {
		ss << beta; 
		line += ss.str();
	}
	
	return line;
}

string Node::makeName(string l, int n){
	stringstream ss;
	ss << n;
	string temp = ss.str();
	l += temp;
	return l;
}

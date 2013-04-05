#include <iostream>
#include <string>
#include "GameTree.h"
#include "Node.h"

using namespace std;

int main(int argc, char* argv[]){
	
	GameTree gameTree;
	gameTree.initializeTree();
	gameTree.printTree();
	gameTree.expandTree();
	
	
	return 0;
}

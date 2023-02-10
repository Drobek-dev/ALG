#include "BeadsSolver.h"

bool BeadsSolver::ReadInputFromFile(string filename) {
	ifstream inputFile;
	inputFile.open(filename);

	if (!inputFile) {
		cerr << "Warning: File: " << filename << " could not be opened." << endl;
		return true;
	}
	else {
		inputFile >> numberOfBeads;
		inputFile >> numberOfRedBeads;
		neighbours.assign(numberOfBeads + indexShift, vector<int>());
		int inputNumberA, inputNumberB;

		while (inputFile >> inputNumberA >> inputNumberB) {
			neighbours.at(inputNumberA).push_back(inputNumberB);
			neighbours.at(inputNumberB).push_back(inputNumberA);
		}

		inputFile.close();
		return false;
	}
}

void BeadsSolver::BuildAndSearchTree() {
	if (numberOfRedBeads == DEFAULT) {
		cerr << "Warning: No input read!" << endl;
	}
	else if (numberOfRedBeads % 2) {
		isNumOfRedBeadsEven = false;
		halfBeadsNumberOne = numberOfRedBeads / 2;
		halfBeadsNumberTwo = (numberOfRedBeads / 2) + 1;
	}
	else {
		isNumOfRedBeadsEven = true;
		halfBeadsNumberOne = numberOfRedBeads / 2;

	}
	PostOrderTreeSearch();
}

void BeadsSolver::InsertEdgeToResults(int parent, int child, int edgeValue) {
	int tmp = parent;
	parent = parent < child ? parent : child;
	child = child > tmp ? child : tmp;
	int tmpRedBeadsDiffNumber = EvaluateEdge(edgeValue);

	if (resultNode1 == DEFAULT
		|| tmpRedBeadsDiffNumber < redBeadsDiffNumber) {

		resultNode1 = parent;
		resultNode2 = child;
		redBeadsDiffNumber = tmpRedBeadsDiffNumber;
	}
	else if (tmpRedBeadsDiffNumber == redBeadsDiffNumber) {

		if (parent < resultNode1) {
			resultNode1 = parent;
			resultNode2 = child;
		}
		else if (parent == resultNode1 && child < resultNode2) {
			resultNode1 = parent;
			resultNode2 = child;
		}
	}
}

int BeadsSolver::EvaluateEdge(int edgeCost) {
	int ret;
	int n1, n2;
	if (isNumOfRedBeadsEven) {
		ret = abs(halfBeadsNumberOne - edgeCost);
	}
	else {
		n1 = abs(halfBeadsNumberOne - edgeCost);
		n2 = abs(halfBeadsNumberTwo - edgeCost);
		ret = n1 < n2 ? n1 : n2;
	}
	return ret;
}

void BeadsSolver::PostOrderTreeSearch() {
	nodeStatus.assign(numberOfBeads + indexShift, true);
	nodeSubTreeValues.assign(numberOfBeads + indexShift, 0);
	parents.assign(numberOfBeads + indexShift, 0);
	int root = 1;
	int inspectedNode = 1;
	int availableChild;
	int nodeVal;

	while (nodeStatus[root]) { // true means node was not explored yet
		availableChild = 0;
		for (int child : neighbours[inspectedNode]) {
			if (nodeStatus[child] && child != parents[inspectedNode]) {
				availableChild = child;
				break;
			}
		}
		if (availableChild != 0) {
			parents[availableChild] = inspectedNode;
			inspectedNode = availableChild;
		}
		else {
			nodeStatus[inspectedNode] = false;
			nodeVal = nodeSubTreeValues[inspectedNode];
			nodeSubTreeValues[inspectedNode] = inspectedNode <= numberOfRedBeads ? nodeVal + 1 : nodeVal;
			nodeSubTreeValues[parents[inspectedNode]] += nodeSubTreeValues[inspectedNode];
			InsertEdgeToResults(parents[inspectedNode], inspectedNode, nodeSubTreeValues[inspectedNode]);
			inspectedNode = parents[inspectedNode];
		}
	}
}

vector<int> BeadsSolver::ReturnEdgeToCut() {
	BeadsSolver::BuildAndSearchTree();
	vector<int> ret{ resultNode1, resultNode2 };
	BeadsSolver::ResetToInitState();
	return ret;
}

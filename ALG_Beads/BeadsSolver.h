//----------------------------------------------------------------------------------------
/**
 * \file       BeadsSolver.h
 * \author     Filip Ježowicz
 * \date       2022/06/22
 * \brief      Contains class BeadsSolver used for solving the beads string problem as described in 'Task_3_Description.pdf'.
 *
 *
*/
//----------------------------------------------------------------------------------------

#pragma once
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

/**
  This class contains information about read input values.
  It also contains methods required to solve task described in 'Task_3_Description.pdf'.

  Variable's and method's description added where deemed necessary.

*/
class BeadsSolver
{
private:

	// class data
	const int indexShift = 1;
	const int DEFAULT = 0;
	int numberOfRedBeads = DEFAULT;
	int numberOfBeads = DEFAULT; ///< number of all beads including red beads
	int halfBeadsNumberOne = DEFAULT; ///< ideal number of red beads in first part of split string of beads
	int halfBeadsNumberTwo = DEFAULT; ///< ideal number of red beads in second part of split string of beads (differs for string of beads with odd number of red beads)
	int minValueofNumOfBeads = DEFAULT; ///< last input of number of beads before data reset (used for output messages in main located in 'ALG_HW_3.cpp')
	bool isNumOfRedBeadsEven = false;

	vector<vector<int>> neighbours; ///<first index is inspected node, vector at that indec contains inspected node's neighbours
	vector<int> parents; ///< index is child node, value is parent node
	vector<int> nodeSubTreeValues; ///< value of Tree with root in given index (it's parent is ignored)
	vector<bool> nodeStatus; ///< true = available; false = closed

	int resultNode1 = DEFAULT;
	int resultNode2 = DEFAULT;
	int redBeadsDiffNumber = DEFAULT;

	void PostOrderTreeSearch();
	void BuildAndSearchTree();
	void ResetToInitState() {

		minValueofNumOfBeads = numberOfBeads;
		resultNode1 = DEFAULT;
		resultNode2 = DEFAULT;
		redBeadsDiffNumber = DEFAULT;
		numberOfRedBeads = DEFAULT;
		numberOfBeads = DEFAULT;
		halfBeadsNumberOne = DEFAULT;
		halfBeadsNumberTwo = DEFAULT;
		isNumOfRedBeadsEven = false;

	}

	/**
	 Inserts new result to class data if requirements are met.

	\param[in] parent ID of the parent node of the edge
	\param[in] child ID of the child node of the edge
	\param[in] edgeValue Number of red beads in a subtree with a root in child node
	*/
	void InsertEdgeToResults(int parent, int child, int edgeValue);

	/**
	 Evaluates the edge based on edgeCost

	\param[in] edgeCost Number of red beads in a subtree created by destroying the edge
					associated with thid edgeCost
	\return Non-negative number that determins minimal difference number
			of red beads betweem both newly created beads strings (assuming that
			the edge was destroyed)
	*/
	int EvaluateEdge(int edgeCost);

public:

	void ReadInputFromSTDIN();
	bool ReadInputFromFile(string filename);
	int RetNumOfNodes() {
		return minValueofNumOfBeads;
	}

	/**
	 Returns result nodes ID's packed in a vector that create an edge.
	 By destroying that particulat edge red beads are distributed
	 between newly created bead strings as uniformly as possible.

	 \return Result nodes ID's packed in a vector.
			 If no input was read default values (0) are returned in the vector.
	*/
	vector<int> ReturnEdgeToCut();

};

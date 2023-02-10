#include "CaravanSolver.h"

void AlgHw4Solver::SolveCaravanProblem() {

	mNodesToBeSearched.push_back(1); // always starting in node 1 according to assignment
	mNodesSatietyLevel[1] = mSatiety;
	mNodesNumOfUsedFoodSupplies[1] = 0;
	vector<uint32_t> tmpFutureSearchNodes;
	uint32_t whileTimeMark = 1;

	while (!mNodesToBeSearched.empty()) {

		tmpFutureSearchNodes.clear();
		for (size_t i = 0; i < mNodesToBeSearched.size(); i++) {
			uint32_t currNode = mNodesToBeSearched[i]; // current node

			// search its neighbours
			for (uint32_t searchedNode : mNodesNeighbours[currNode]) { // searched node

				uint32_t currNodeSupplies = mNodesNumOfUsedFoodSupplies[currNode];
				uint32_t currNodeSatiety = mNodesSatietyLevel[currNode];

				uint32_t futureSupplies = currNodeSatiety == 0 ? currNodeSupplies + 1 : currNodeSupplies;
				uint32_t futureSatiety = currNodeSatiety == 0 ? mSatiety : currNodeSatiety - 1;
				futureSatiety = searchedNode <= mBefriendedVillagesLimit ? mSatiety : futureSatiety;

				uint32_t seachedNodeSupplies = mNodesNumOfUsedFoodSupplies[searchedNode];
				uint32_t seachednodesatiety = mNodesSatietyLevel[searchedNode];

				if (futureSupplies < seachedNodeSupplies) {
					if (futureSupplies == 0 && seachedNodeSupplies != 0) {
						mAccesibleVillagesWithZeroSupplies++;
					}

					mNodesNumOfUsedFoodSupplies[searchedNode] = futureSupplies;
					mNodesSatietyLevel[searchedNode] = futureSatiety;

					if (mNodesTimeMark[searchedNode] != whileTimeMark) {
						mNodesTimeMark[searchedNode] = whileTimeMark;
						tmpFutureSearchNodes.push_back(searchedNode);
					}

				}
				else if (futureSupplies == seachedNodeSupplies) {
					if (futureSatiety > seachednodesatiety) {
						if (futureSupplies == 0 && seachedNodeSupplies != 0) {
							mAccesibleVillagesWithZeroSupplies++;
						}

						mNodesNumOfUsedFoodSupplies[searchedNode] = futureSupplies;
						mNodesSatietyLevel[searchedNode] = futureSatiety;

						// ensures we won't insert already inserted node
						if (mNodesTimeMark[searchedNode] != whileTimeMark) {
							mNodesTimeMark[searchedNode] = whileTimeMark;
							tmpFutureSearchNodes.push_back(searchedNode);
						}
					}
				}
			} // end of inner for

		} // end of outer for
		mNodesToBeSearched.swap(tmpFutureSearchNodes);
		//cerr << endl;
		whileTimeMark++;
	} // end of while

	//uint32_t best = 0;
	for (size_t i = 1; i < mNodesNumOfUsedFoodSupplies.size(); i++) {
		mMinNumOfNecessarySupplies = mNodesNumOfUsedFoodSupplies[i] > mMinNumOfNecessarySupplies ?
			mNodesNumOfUsedFoodSupplies[i] : mMinNumOfNecessarySupplies;
	}
	//mMinNumOfNecessarySupplies = best;
}

vector<uint32_t> AlgHw4Solver::RetResult() {
	vector<uint32_t> result{ mMinNumOfNecessarySupplies, mAccesibleVillagesWithZeroSupplies };
	resetToInitState();
	return result;
}

void AlgHw4Solver::ReadInputSTDIN() {
	cin >> mNumOfVillages;
	cin >> mNumOfRoutes >> mBefriendedVillagesLimit >> mSatiety;

	initVectors();

	int village1, village2;
	while (cin >> village1 >> village2) {
		mNodesNeighbours[village1].push_back(village2);
		mNodesNeighbours[village2].push_back(village1);
	}
}

void AlgHw4Solver::ReadInputFILE(string filename) {
	ifstream inputFile;
	inputFile.open(filename);
	if (!inputFile) {
		cerr << "File could not be opened" << endl;
		exit(1);
	}

	inputFile >> mNumOfVillages >> mNumOfRoutes >> mBefriendedVillagesLimit >> mSatiety;
	initVectors();

	int village1, village2;
	while (inputFile >> village1 >> village2) {
		mNodesNeighbours[village1].push_back(village2);
		mNodesNeighbours[village2].push_back(village1);
	}

	inputFile.close();
}

void AlgHw4Solver::PrintInput() {
	cout << "Number of nodes: " << setw(8) << mNumOfVillages;
	cout << "; Number of edges: " << setw(8) << mNumOfRoutes;


}

void AlgHw4Solver::initVectors() {
	mNodesNeighbours.assign(mNumOfVillages + mShiftValue, vector<uint32_t>());
	mNodesNumOfUsedFoodSupplies.assign(mNumOfVillages + mShiftValue, UINT32_MAX);
	mNodesSatietyLevel.assign(mNumOfVillages + mShiftValue, 0); // input mSatiety >= 1
	mNodesParents.assign(mNumOfVillages + mShiftValue, 0); // refers to initial node 0, that is undefined
	mNodesTimeMark.assign(mNumOfVillages + mShiftValue, 0);

}

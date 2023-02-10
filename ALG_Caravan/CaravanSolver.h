
#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <stdint.h>


using namespace std;

class AlgHw4Solver{
public:
	
	void SolveCaravanProblem();
	void ReadInputSTDIN();
	void ReadInputFILE(string filename);
	void PrintInput();
	vector<uint32_t> RetResult();

private:

	const uint32_t mShiftValue = 1;
	const uint32_t mDefaultValue = 0;
	vector<vector<uint32_t>> mNodesNeighbours;
	vector<uint32_t> mNodesSatietyLevel;
	vector<uint32_t> mNodesNumOfUsedFoodSupplies;
	vector<uint32_t> mNodesParents;
	vector<uint32_t> mNodesToBeSearched;
	vector<uint32_t> mNodesTimeMark;

	uint32_t mNumOfVillages = mDefaultValue;
	uint32_t mBefriendedVillagesLimit = mDefaultValue;
	uint32_t mNumOfRoutes = mDefaultValue;
	uint32_t mSatiety = mDefaultValue;
	
	uint32_t mMinNumOfNecessarySupplies = mDefaultValue;
	uint32_t mAccesibleVillagesWithZeroSupplies = 1;

	void initVectors();
	void resetToInitState(){

		mNumOfVillages = mDefaultValue;
		mBefriendedVillagesLimit = mDefaultValue;
		mNumOfRoutes = mDefaultValue;
		mSatiety = mDefaultValue;
		mMinNumOfNecessarySupplies = mDefaultValue;
		mAccesibleVillagesWithZeroSupplies = 1;
	}
};

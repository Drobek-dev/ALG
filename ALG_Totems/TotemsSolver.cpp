#include "TotemsSolver.h"

bool TotemsSolver::ReadInputFromFile(string filename) {
	fstream inputFile;
	inputFile.open(filename);
	if (!inputFile) {
		cerr << "File not found!" << endl;
		return true;
	}

	inputFile >> mNumVillages >> mTotPrice >> mFighterPrice;
	InitVectors();
	mInitVillInhab.push_back(0); // 0 village... indexing starts from 1
	for (int32_t i = 0; i < mNumVillages; i++) {
		int32_t villageInhabitants;
		inputFile >> villageInhabitants;
		mInitVillInhab.push_back(villageInhabitants);
	}
	inputFile.close();
	return false;

}


int32_t TotemsSolver::GetResult() {
	return mResult;
}

void TotemsSolver::Solve() {
	FillPriceForVillMergeTab();
	CalculateBestPrice();
}

void TotemsSolver::FillPriceForVillMergeTab() {

	int32_t row = 1, col = 2, innerCol;

	for (int32_t i = 1; i < mNumVillages; i++) {
		innerCol = col;

		while (innerCol <= mNumVillages) {
			FillPriceForVillMergePos(row, innerCol);

			// Diagonal move
			row++;
			innerCol++;

		}

		// Shift starting position to the right
		row = 1;
		col++;
	}
}

void TotemsSolver::FillPriceForVillMergePos(const int32_t row, const int32_t innerCol) {

	if (innerCol - 1 == row) {
		FillOnePossibleVillMerge(row, innerCol);
	}
	else {
		FillMultPossibleVillMerge(row, innerCol);
	}
}

void TotemsSolver::FillOnePossibleVillMerge(const int32_t row, const int32_t innerCol) {

	int32_t villDiffA = abs(mInitVillInhab[row] - mInitVillInhab[innerCol]);
	mPriceForVillageMerge[row][innerCol] = -(villDiffA * mFighterPrice) + mTotPrice;
	mMergVillInhab[row][innerCol] = mInitVillInhab[row] + mInitVillInhab[innerCol];
}

void TotemsSolver::FillMultPossibleVillMerge(const int32_t row, const int32_t innerCol) {

	int32_t villDiffA, villDiffB, villDiffC, priceA, priceB;

	villDiffA = abs(mMergVillInhab[row][innerCol - 1] - mInitVillInhab[innerCol]);
	priceA = -(villDiffA * mFighterPrice) + mTotPrice + mPriceForVillageMerge[row][innerCol - 1];

	villDiffB = abs(mMergVillInhab[row + 1][innerCol] - mInitVillInhab[row]);
	priceB = -(villDiffB * mFighterPrice) + mTotPrice + mPriceForVillageMerge[row + 1][innerCol];

	// amount of people must remain same for both variants
	mMergVillInhab[row][innerCol] = mMergVillInhab[row][innerCol - 1] + mInitVillInhab[innerCol];

	if (priceA > priceB) {
		mPriceForVillageMerge[row][innerCol] = priceA;

	}
	else { // if equal of higher
		mPriceForVillageMerge[row][innerCol] = priceB;

	}

	// rest of possible combinations
	int32_t movingColInd = innerCol - 2, movingRowInd = movingColInd + 1;
	int32_t locGain;

	while (row != movingColInd) {
		villDiffC = abs(mMergVillInhab[row][movingColInd] - mMergVillInhab[movingRowInd][innerCol]);
		locGain = -(villDiffC * mFighterPrice) + mTotPrice + mPriceForVillageMerge[row][movingColInd] + mPriceForVillageMerge[movingRowInd][innerCol];
		if (mPriceForVillageMerge[row][innerCol] < locGain) {
			mPriceForVillageMerge[row][innerCol] = locGain;
		}
		movingColInd--;
		movingRowInd = movingColInd + 1;
	}
}

void TotemsSolver::CalculateBestPrice() {
	int32_t row = 1, column = 1;

	while (column <= mNumVillages) {

		row = 1;
		mBestPrice[column] = mBestPrice[column - 1];

		while (row < column) {

			if (mPriceForVillageMerge[row][column] + mBestPrice[row - 1] > mBestPrice[column]) {
				mBestPrice[column] = mPriceForVillageMerge[row][column] + mBestPrice[row - 1];
			}
			row++;
		}
		column++;
	}
	mResult = mBestPrice[mNumVillages];
}
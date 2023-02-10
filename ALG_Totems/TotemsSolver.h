#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

class TotemsSolver {

private:
    int32_t mNumVillages; // number of villages, each village is identified with unique ID in range from 1 to mNumVillages (border values included)
    int32_t mTotPrice; // Totem price
    int32_t mFighterPrice;
    int32_t mResult;
    const int32_t mShiftConst = 1; // because villages are indexed from 1 to mNumVillages in used vectors (line 19 to 22). A shift is needed when allocating space on the heap

    vector<int32_t> mInitVillInhab; // value at each index i represents starting amount of fighters in corresponding village i
    vector<int32_t> mBestPrice; // value at each index represents best possible gain for merging villages 1 to i
    vector<vector<int32_t>> mPriceForVillageMerge; // value at row r and column c represents best possible gain for merging all villages starting from village r to c
    vector<vector<int32_t>> mMergVillInhab; // value at row r and column c represents number of people in a village created by merging villages r to c

    void FillPriceForVillMergeTab();
    void FillPriceForVillMergePos(const int32_t row, const int32_t innerCol);
    void FillOnePossibleVillMerge(const int32_t row, const int32_t innerCol);
    void FillMultPossibleVillMerge(const int32_t row, const int32_t innerCol);
    void CalculateBestPrice();
    void InitVectors() {
        mBestPrice.assign(mNumVillages + mShiftConst, 0);
        mPriceForVillageMerge.assign(mNumVillages + mShiftConst, vector<int32_t>(mNumVillages + mShiftConst, 0));
        mMergVillInhab.assign(mNumVillages + mShiftConst, vector<int32_t>(mNumVillages + mShiftConst, 0));
    }

public:
    bool ReadInputFromFile(string filename);
    void PrintInput() {
        cout << "Number of villages: " << mNumVillages;
    }
    void Solve();
    int32_t GetResult();
    void Reset() {
        mNumVillages = 0;
        mTotPrice = 0;
        mFighterPrice = 0;
        mResult = 0;
         
        mInitVillInhab.clear(); 
        mBestPrice.clear();
        mPriceForVillageMerge.clear();
        mMergVillInhab.clear();

    }




};

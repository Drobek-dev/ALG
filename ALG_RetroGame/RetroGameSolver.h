#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

class Egg {
private:
    uint32_t mRow;
    uint32_t mCol;

public:

    uint32_t RetRow()const {
        return mRow;
    }
    uint32_t RetCol()const {
        return mCol;
    }

    Egg(uint32_t r, uint32_t c) : mRow(r), mCol(c) {};

    bool operator<(const Egg& other) {

        if (mRow != other.RetRow()) {
            return mRow < other.RetRow();
        }
        else {
            return mCol < other.RetCol();
        }

    }

};

class RetroGameSolver {

private:

    uint32_t mBreadth;
    uint32_t mNumOfEggs;
    uint32_t mMaxCoughtEggs = 0;
    vector<Egg> mEggs;
    vector<uint32_t> mGameTimeLevel;

    bool DoesRowContainEgg(size_t r, size_t eggsIndex) {
        return mEggs[eggsIndex].RetRow() == r;

        if (eggsIndex >= mEggs.size()) {
            return false;
        }
        else {
            return mEggs[eggsIndex].RetRow() == r;
        }
    }

    bool AreValuesInLevelSame() {
        uint32_t n = mGameTimeLevel[0];
        for (size_t i = 1; i < mGameTimeLevel.size(); i++) {
            if (mGameTimeLevel[i] != n) {
                return false;
            }
        }
        return true;
    }

  


public:

    bool ReadInputFromFile(string filename);
    uint32_t SolveInput();
    void PrintInput();
    void Reset() {
        mBreadth = 0;
        mNumOfEggs = 0;
        mMaxCoughtEggs = 0;
        mEggs.clear();
        mGameTimeLevel.clear();
    }




};

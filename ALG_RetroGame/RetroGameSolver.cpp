#include "RetroGameSolver.h"

bool DEBUG = false;

bool RetroGameSolver::ReadInputFromFile(string filename) {

    fstream input;
    input.open(filename);

    if (!input.is_open()) {
        cerr << "Error: Unable to open file: " << filename << endl;
        return true;
    }

    input >> mBreadth >> mNumOfEggs;
    uint32_t col, row;
    while (input >> col >> row) {
        mEggs.emplace_back(Egg(row, col - 1));
    }
    input.close();
    return false;
}

void RetroGameSolver::PrintInput() {

    
    cout << "Number of Eggs: "<<setw(8)<< mNumOfEggs;
}

uint32_t RetroGameSolver::SolveInput() {

    mGameTimeLevel.assign(mBreadth, 0);
    sort(mEggs.begin(), mEggs.end());
    size_t maxRow = mEggs[mEggs.size() - 1].RetRow();
    size_t eggsIndex = 0;

    for (size_t r = 1; r <= maxRow; r++) {


        vector<uint32_t> tmpLevel;
        vector<bool> eggPresent;
        tmpLevel.assign(mBreadth, 0);
        eggPresent.assign(mBreadth, false);

        while (eggsIndex < mEggs.size() && mEggs[eggsIndex].RetRow() == r) {
            uint32_t colWithEgg = mEggs[eggsIndex].RetCol();
            tmpLevel[colWithEgg] = 1;
            eggPresent[colWithEgg] = true;
            eggsIndex++;
        }


        for (size_t c = 1; c < mBreadth && c <= r; c++) {

            if (c == 1) { // begining
                uint32_t current, futUp, futRight;
                current = mGameTimeLevel[c];
                futUp = current + (eggPresent[c] ? 1 : 0) + (eggPresent[c - 1] ? 1 : 0);
                futRight = current + (eggPresent[c + 1] ? 1 : 0) + (eggPresent[c] ? 1 : 0);

                tmpLevel[c] = futUp > tmpLevel[c] ? futUp : tmpLevel[c];
                tmpLevel[c + 1] = futRight > tmpLevel[c + 1] ? futRight : tmpLevel[c + 1];
            }
            else if (c == mBreadth - 1) { // end
                uint32_t current, futUp, futLeft;
                current = mGameTimeLevel[c];
                futUp = current + (eggPresent[c] ? 1 : 0) + (eggPresent[c - 1] ? 1 : 0);
                futLeft = current + (eggPresent[c - 1] ? 1 : 0) + (eggPresent[c - 2] ? 1 : 0);

                tmpLevel[c] = futUp > tmpLevel[c] ? futUp : tmpLevel[c];
                tmpLevel[c - 1] = futLeft > tmpLevel[c - 1] ? futLeft : tmpLevel[c - 1];
            }
            else { // middle
                uint32_t current, futUp, futRight, futLeft;
                current = mGameTimeLevel[c];
                futUp = current + (eggPresent[c] ? 1 : 0) + (eggPresent[c - 1] ? 1 : 0);
                futRight = current + (eggPresent[c + 1] ? 1 : 0) + (eggPresent[c] ? 1 : 0);
                futLeft = current + (eggPresent[c - 1] ? 1 : 0) + (eggPresent[c - 2] ? 1 : 0);

                tmpLevel[c] = futUp > tmpLevel[c] ? futUp : tmpLevel[c];
                tmpLevel[c + 1] = futRight > tmpLevel[c + 1] ? futRight : tmpLevel[c + 1];
                tmpLevel[c - 1] = futLeft > tmpLevel[c - 1] ? futLeft : tmpLevel[c - 1];
            }


        }
        mGameTimeLevel.swap(tmpLevel);
    }

    mMaxCoughtEggs = *max_element(mGameTimeLevel.begin(), mGameTimeLevel.end());

    return mMaxCoughtEggs;
}


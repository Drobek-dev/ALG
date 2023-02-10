// ALG_Beads.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <chrono>
#include "BeadsSolver.h"
#include <iomanip>

class IOFiles {
public:
    vector<string> inputs{ "pub01.in","pub02.in","pub03.in","pub04.in","pub05.in","pub06.in","pub07.in","pub08.in","pub09.in","pub10.in" };
    vector<string> outputs{ "pub01.out","pub02.out","pub03.out","pub04.out","pub05.out","pub06.out","pub07.out","pub08.out","pub09.out","pub10.out" };

};

int main()
{
    std::cout << "Hello Beads!\n";

    IOFiles iof;
    BeadsSolver bS;

    for (size_t i = 0; i < iof.inputs.size(); i++) {

        if (bS.ReadInputFromFile(iof.inputs[i])) {
            continue;
        }
        auto start = chrono::high_resolution_clock::now();
        vector<int> ret = bS.ReturnEdgeToCut();
        auto duration = chrono::duration_cast<std::chrono::milliseconds>(chrono::high_resolution_clock::now() - start);
        cout << "Number of nodes: " << setw(8) << bS.RetNumOfNodes() << "; Calculated solution:" << setw(8) << ret[0] << " " << setw(8) << ret[1]
            << " "<< "Time required: " << duration.count() << " ms";

        ifstream results;
        results.open(iof.outputs[i]);

        if (results) {
            int r1, r2;
            results >> r1;
            results >> r2;
            string isResCorrect = r1 == ret[0] && r2 == ret[1] ? "TRUE" : "FALSE";
            cout << "; Reference solution: " << setw(8) << r1 << " " << setw(8) << r2 << " => correct: " << isResCorrect << endl;
            results.close();
        }
        else {
            cerr << "Warning: File: " << iof.outputs[i] << " not found." << endl;
        }
    }
}


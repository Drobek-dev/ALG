// ALG_RetroGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include "RetroGameSolver.h"
using namespace std;
using namespace std::chrono;

class IOFiles {
public:
	vector<string> inputs{ "pub01.in","pub02.in","pub03.in","pub04.in","pub05.in","pub06.in","pub07.in","pub08.in","pub09.in","pub10.in"};
	vector<string> outputs{ "pub01.out","pub02.out","pub03.out","pub04.out","pub05.out","pub06.out","pub07.out","pub08.out","pub09.out","pub10.out" };

};

int main()
{
	IOFiles iof;
	RetroGameSolver retroGameSolver;

	for (size_t i = 0; i < iof.inputs.size(); i++) {

		if (retroGameSolver.ReadInputFromFile(iof.inputs[i]))
			continue;

		auto start = high_resolution_clock::now();
		uint32_t result = retroGameSolver.SolveInput();
		auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - start);
		retroGameSolver.PrintInput();
		cout << " Result: " << setw(8) << result << " Required time: " << setw(8) << duration.count() << " ms";

		ifstream results;
		results.open(iof.outputs[i]);

		if (results) {
			uint32_t r1;
			results >> r1;
			
			string isResCorrect = r1 == result ? "TRUE" : "FALSE";
			cout << "; Reference result: " << setw(8) << r1 << " " << " => correct: " << isResCorrect << endl;
			results.close();
		}
		else {
			cerr << "Warning: File: " << iof.outputs[i] << " not found." << endl;
			cout << endl;
		}
		retroGameSolver.Reset();

	}
	return 0;
}


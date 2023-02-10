// ALG_HW_4.cpp : Defines the entry point for the application.
//

#include "CaravanSolver.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

class IOFiles {
public:
	vector<string> inputs{ "pub01.in","pub02.in","pub03.in","pub04.in","pub05.in","pub06.in","pub07.in","pub08.in","pub09.in","pub10.in" };
	vector<string> outputs{ "pub01.out","pub02.out","pub03.out","pub04.out","pub05.out","pub06.out","pub07.out","pub08.out","pub09.out","pub10.out" };

};

int main()
{

	IOFiles iof;
	AlgHw4Solver caravanProblemSolver;

	for (size_t i = 0; i < iof.inputs.size(); i++) {
		caravanProblemSolver.ReadInputFILE(iof.inputs[i]);

		auto start = high_resolution_clock::now();
		caravanProblemSolver.SolveCaravanProblem();
		auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - start);
		caravanProblemSolver.PrintInput();
		vector<uint32_t> ret = caravanProblemSolver.RetResult();
		cout << "; Result: " << setw(8) << ret[0] << " " << setw(8) << ret[1]<< " Required time: "<< setw(8)<< duration.count()<<" ms";

		ifstream results;
		results.open(iof.outputs[i]);

		if (results) {
			uint32_t r1, r2;
			results >> r1;
			results >> r2;
			string isResCorrect = r1 == ret[0] && r2 == ret[1] ? "TRUE" : "FALSE";
			cout << "; Reference result: " << setw(8) << r1 << " " << setw(8) << r2 << " => correct: " << isResCorrect << endl;
			results.close();
		}
		else {
			cerr << "Warning: File: " << iof.outputs[i] << " not found." << endl;
			cout << endl;
		}

	}
	return 0;
}


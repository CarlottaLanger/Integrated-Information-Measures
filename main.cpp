#include "ProbabilityDist.h"
#include "emIterate.h"
#include "Test.h"
#include <iomanip>
#include <math.h>


using namespace std;

int main(){
	// the path from the python file and the number of nodes
	Test *tes = new Test("/home/carlotta/Documents/Tests/BoltzWnegbetabeta2.txt", 3);
	// stochastic interaction, also called information flow
	tes->testIF();
	// geometric integrated information, calculated using an iterative scaling algorithm
	tes->testG(10000,0.00000001);
	// mutual information 
	tes->testMI();

	// each of the functions produce an output that can be copy pasted to python in order to plot it with matplotlib 
}


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
	// causal information integration, 3 = number of hidden states, 1000 = max. iterations, 3 = number of different inital distributions
	tes->testCEI(3, 1000, 3);

	// each of the functions produce an output in the python numpy format, it can be copy pasted in order to plot it with matplotlib 
}


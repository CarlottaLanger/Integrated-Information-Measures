/*
 * emIterate.h
 *
 *  Created on: Dec 17, 2019
 *      Author: langer
 */
#ifndef EMITERATE_H_
#define EMITERATE_H_
#include "ProbabilityDist.h"

using namespace std;

class emIterate{
	public:
		emIterate();
		emIterate(int n, int m, vector<int> &l, vector<double> &original);
		emIterate(int n, int m, vector<int> &l, vector<double> &original, vector<double> &inital);
		double iterate(int it = 1000, double r = 1e-9);
		void changeP(vector<double> &p, bool randin);
		~emIterate();
		vector<double> getProb();
		double  Kl(); // KL(original || new)
		double invKl(); // KL(new || original)
	private:
		double _Kl(vector<double> &p, vector<double> &q);
		int _m;
		int _n;
		int _sizeAlph;
		int _sizeX; //= all
		Probability _p;
		vector<int> _l;
		vector<double> _original;
		vector<double> _initial;
};



#endif /* EMITERATE_H_ */

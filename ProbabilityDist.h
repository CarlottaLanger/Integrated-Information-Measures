/*
 * Probability.h
 *
 *  Created on: Dec 2, 2019
 *      Author: langer
 */

#ifndef PROBABILITYDIST_H_
#define PROBABILITYDIST_H_
#include <vector>
#include <iostream>

using namespace std;


class Probability{
	public:
		//number of nodes n, size of the state space of w, state space of nodes
		Probability();
		Probability(int n, int m, vector<int> &l, vector<double> &p);
		~Probability();
		vector<double> getProb();
		vector<double> getMarginalProb();
		double mProj();
		double eProj(vector<double> &originalp);
		void testCondInd();
		void changeProp(vector<double> &p);
		friend std::ostream& operator<<(std::ostream &out, const Probability &p);
	private:
		bool setMarginalsEproj();
		bool setMarginalsMproj();
		int _m;
		int _n;
		int _sizeAlph;
		int _sizeX; //= alli
		vector< vector<double> > _marginalsycxw;
		vector< vector<double> > _marginalsyxw;
		vector< vector< vector<int> > > _indices;
		vector< vector< vector<int> > > _indicesxw;
		vector<int> _l;
		vector<int> _biggeri;
		vector<double> _marginalsx;
		vector<double> _marginalsxy;
		vector<double> _marginalsw;
		vector<double> _p;
};


#endif /* PROBABILITYDIST_H_ */

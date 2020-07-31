/*
 * test.h
 *
 *  Created on: Jan 13, 2020
 *      Author: langer
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "emIterate.h"
#ifndef TEST_H_
#define TEST_H_
using namespace std;

class Test{
	public:
		Test(string filename, int neuron);

		//written for a distribution consisting only of controller nodes
		vector<double > testMI();
		vector<double> testIF();
		vector<double> testG(int iterat, double err);
		vector<double > testCEI(int m, int it, int start);
		vector<double > testMIS(int iterat, double err);
	private:
		double _kl(vector<double> &p1, vector<double> &p2);
		vector<vector<double> > _input;
		int _neuron;
		int _allx;
		int _allxy;
};





#endif /* TEST_H_ */

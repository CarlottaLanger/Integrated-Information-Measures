/*
 * emIterate.cpp
 *
 *  Created on: Dec 17, 2019
 *      Author: langer
 */
#include "emIterate.h"
#include <math.h>
#include <time.h>
#include <assert.h>

using namespace std;

//random initial distribution
emIterate::emIterate(int n, int m, vector<int> &l, vector<double> &original){
	_original = original;
	_n = n;
	_m = m;
	_sizeAlph =  _m;
	_sizeX = 1;
	_l = l;
	for(int i = 0; i < _n; i++){
		_sizeAlph = _sizeAlph * pow(_l[i],2);
		_sizeX = _sizeX *_l[i];
	}
	srand (time(NULL));
	vector<double> initial = {};
	double sum =0;
	double rnd =0;
	for(int i=0 ; i<_sizeAlph; i++){
		rnd = rand() % 6000;
		sum = sum+rnd;
		initial.push_back(rnd);
	}
	for(int i =0; i<_sizeAlph; i++) {
	    initial[i] = initial[i]/sum;
	    _initial.push_back(initial[i]);
	}
	assert(original.size() == pow(_sizeX,2));
	_p = Probability(_n,_m, _l,_initial);
}

// specific initial distribution
emIterate::emIterate(int n, int m, vector<int> &l, vector<double> &original, vector<double> &initial){
	_original = original;
	_n = n;
	_m = m;
	_sizeAlph =  _m;
	_sizeX = 1;
	_l = l;
	_initial = initial;
	for(int i = 0; i < _n; i++){
		_sizeAlph = _sizeAlph * pow(_l[i],2);
		_sizeX = _sizeX *_l[i];
	}
	_p = Probability(_n,_m, _l,_initial);
}

emIterate::~emIterate(){
//	_p.~Probability();
}

void emIterate::changeP(vector<double> &p, bool randin){
	srand (time(NULL));
	_original = p;
	if(randin){
		vector<double> initial = {};
		double sum =0;
		double rnd =0;
		for(int i=0 ; i<_sizeAlph; i++){
			rnd = rand() % 6000;
			sum = sum+rnd;
			initial.push_back(rnd);
		}
		_initial.clear();
		 //cout << " initial start" << endl;
		for(int i =0; i<_sizeAlph; i++) {
		    initial[i] = initial[i]/sum;
		    _initial.push_back(initial[i]);
		    // cout << initial[i] << "," << endl;
		}
	}
	else{
		vector<double> _initial = {0.00842577511776355,0.010406725371248949,0.00721540951580127,0.007162973846880829,0.0016247764649203603,0.0054604940237894415,0.004433764625723088,0.003454886668825466,0.008523100625761615,0.0012032218844521467,0.003679503306781155,0.011112995938375635,0.006904052084853123,0.008786014667925949,0.012193877641182908,0.012094565435827605,0.0070472943574164245,0.011598582033177164,0.01344703363644268,0.01029145351258474,0.01054445893785647,0.010005096578953526,0.0037403372248260435,0.013410005774079983,0.00802788166575741,0.0017096874076655227,0.012573777234649256,0.007654311460208653,0.012690425325531305,0.010076572873857888,0.004907440003618788,0.0009747510016271893,0.009807291623878616,0.008523280748541195,0.011560769371154743,0.011073672835005493,0.010000533027060093,0.009964201791509544,0.007523421283846022,0.009519105379583597,0.013764224210183251,0.004624281843549071,0.009546319542694892,0.0001232339526430604,0.0023090307012217097,0.00033795055798894287,0.009700271149523477,0.002651041379707889,0.010449265005382714,0.01438999296747397,0.002761365355874634,0.014240382579614404,0.014299522475292351,0.008623518364108419,0.009442427696047546,0.0062091749948040295,0.011311725641446363,0.010010399164016118,0.0040486523123717585,0.002581910335389888,0.0026565931297102626,0.00235038278567349,0.012122564423125145,0.014584147125181874,0.01251756791501174,0.011269057856233717,0.004601761860588839,0.007405425215299795,0.01212425329492241,0.011356041854221044,1.5014253981334416e-05,0.0006050095824175801,0.0030878880506017567,0.014349573553084702,0.007430487936403738,0.005401282584246022,0.009958533197155056,0.013449069362317944,0.0118577021411905,0.014470650864097689,0.014023258843266462,0.004726544614060458,0.002692998582517213,0.010884116590848727,0.0019400771229605858,0.008415903511393059,0.011136657164943798,0.0009424144252859266,0.012696865990280455,0.01261571685194211,0.0120879194595605,0.007790297781895896,0.0053380720707193055,0.006939359239992644,0.01128107236938181,0.005716813521803877,0.005875489108508087,0.005792579186609171,0.013848958365755863,0.0025800027851200285,0.011187587028029227,0.0008164896678841869,0.013087523603158801,0.004237694848519495,0.0029460937503339437,0.010160406881536521,0.007722156848755574,0.011716704535945713,0.00346365266862489,0.01389935960870672,0.00714986839402199,0.005959787844730769,0.01236749294576726,0.005497844557079175,0.008136561236711774,0.002899086929012762,0.002337464592812213,0.0020614402660641532,0.004780174871774775,0.004251690172659479,0.0051264133831175,0.013872360592248813,0.014471928646855118,0.004558921286026773,0.0007910779098417624,0.002911467770297538,0.008611735185118414,0.005260676863774128}; 	}
	_p.changeProp(_initial);
}

//iteration of the em-Algorithm, maximum number of iterations, error
double emIterate::iterate(int it, double r){
	int iterat = 0;
	double  err = 2;
	double sum = 0;
	vector<double> test;
	while(iterat < it && err > r){
		vector<double> pold = _p.getProb();
		sum =0;
		_p.eProj(_original);
		_p.mProj();
		iterat = iterat + 1;
		test = _p.getProb();
		sum = 0;
		err = _Kl(pold, test);
	}
	//cout << "distribution" << endl;
	test = _p.getMarginalProb();
	//cout << "err" << err << endl;
//	_p.testCondInd();
	return iterat;
}

vector<double> emIterate::getProb(){
	return _p.getMarginalProb();
}

double  emIterate::Kl(){
	vector<double> q = _p.getMarginalProb();
	double sum =0;
	for(int i =0; i< q.size();i++){
		sum = sum + q[i];
	}
	return _Kl(_original,q);
}

double  emIterate::_Kl(vector<double> &p, vector<double> &q){
	assert(p.size() == q.size());
//	//cout << " p " << p.size() << " " << q.size() << endl;
	double kl =0;
	for(int i =0; i< p.size(); i++ ){
		if(p[i]*q[i] !=0){
			kl = kl + p[i]*((log2(p[i])) - log2(q[i]));
		}
		if(q[i] ==0 && p[i]!=0){
			kl = kl +20;
			//cout << "dividing by 0" << endl;
		}
	}
	return kl;
}


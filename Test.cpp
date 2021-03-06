/*
 * test.cpp
 *
 *  Created on: Jan 13, 2020
 *      Author: langer
 */
#include "Test.h"
#include <assert.h>
#include <math.h>
#include<numeric>

Test::Test(string name, int neuron){
	_neuron = neuron;
	_allx = (int) pow(2,neuron);
	_allxy =  (int) pow(2,neuron*2);
	cout << _allxy << endl;
	vector<double> p(_allxy);
	ifstream file;
	file.open (name);
	string word;
	char x ;
	word.clear();
	int i = 0;
	int j = 1;
	while ( ! file.eof())
	{
		x = file.get();
	//	cout << x << endl;
		while ( x != ',' && x!=' ')
	    {
			if(x == ';' ){
				cout << _input.size() << endl;
				file.close();
	        	return;
	        }
		    if(x == '#'){
		    	_input.push_back(p);
		        x=file.get();
		        i=0;
		        j = j+1;
		    }
	        word = word + x;
	        x = file.get();
	    }
        p[i] = stod(word);
	    word.clear();
	    i = i + 1;
	}
	file.close();
	cout << "input size" <<  _input.size() << endl;
	return;
}

vector<double > Test::testMI(){
	double  min = 100.0;
	double  max = 0.0;
	double  sum = 0.0;
	double  kl = 0;
	cout << "I = np.array([";
	vector<double> pi(_allxy,0.0);
	for(int i=0; i < _input.size();i++){
	//	//cout<<"pi "<<  " " << accumulate(_input[i].begin(),_input[i].end(),0.0) << endl;
		vector<double> px(_allx,0.0);
		vector<double> py(_allx,0.0);
		for(int j=0; j< _allxy; j++){
			px[j/_allx] = px[j/_allx] + _input[i][j];
			py[j%_allx] = py[j%_allx] + _input[i][j];
		//	//cout << j/32 << " " << j % 32 << endl;
		}
		for(int j=0; j<_allxy; j++){
			pi[j] = px[j/_allx]*py[j%_allx];
		}
		kl = _kl(_input[i], pi);
		cout <<   kl << ",";
		sum = sum + kl;
		if(kl < min){ min = kl;}
		if(kl > max){ max = kl;}
		px.clear();
		py.clear();
	}
	sum = sum / (_input.size());
	cout << "])" << endl;
	//cout << min << " " << max << " " << sum << endl;
	vector<double > val ={min, max, sum};
	return val;
}

vector<double > Test::testIF(){
	double  min = 100.0;
	double  max = 0.0;
	double  sum = 0.0;
	double Hv =0;
	double  kl = 0;
	cout << "IF = np.array([";
	vector<double> pi(_allxy,0.0);
	for(int i=0; i < _input.size();i++){
		Hv = 0;
		for(int j=0; j<_neuron; j++){
			vector<double> pf(_allx*pow(2,j)*2,0.0);
			for(int k=0; k<_allxy;k++){
				pf[k/(pow(2,(_neuron-1)-j))] = pf[floor(k/(pow(2,(_neuron-1)-j)))] + _input[i][k];
			}
			vector<double> pff(_allx*2,0.0);
			for(int k=0; k < _allx*pow(2,j)*2; k++){
				pff[k%(_allx*2)] = pff[k%(_allx*2)] + pf[k];
			}
			vector<double> pyixi(4,0.0);
			for(int k=0; k< _allx*2; k++){
				pyixi[floor(k/_allx)*2 + k%2] = pyixi[floor(k/_allx)*2 + k%2] + pff[k];
			//	//cout << "j " << j << " k " << k << " " << floor(k/32)*2 + k%2<< endl;
			}
			Hv = Hv - pyixi[0]*( log2(pyixi[0]/(pyixi[0] + pyixi[1])))
					- pyixi[1]*( log2(pyixi[1]/(pyixi[0] + pyixi[1])))
					- pyixi[2]*( log2(pyixi[2]/(pyixi[2] + pyixi[3])))
					- pyixi[3]*( log2(pyixi[3]/(pyixi[2] + pyixi[3])));
		    pf.clear();
		    pff.clear();
		    pyixi.clear();
		}
		////cout << "Hv" << Hv << endl;
		double H = 0.0;
		vector<double> px(_allx,0.0);
		for(int j=0; j<_allxy; j++){
			px[j/_allx] = px[j/_allx] + _input[i][j];
		//	//cout<< "j" << j << " " << j/32 << endl;
		}
		for(int j=0; j<_allxy; j++){
			if(_input[i][j]!=0){
				H = H - _input[i][j] * log2(_input[i][j] / px[j/_allx]);
			}
			else{
			//	//cout << H << " " << j << " " << px[j/32]  << " " << _input[i][j] << " " << - _input[i][j] * log2(_input[i][j] / px[j/32])<< endl;
			}
		}
		////cout <<"H " << H  << endl;
		kl = Hv - H;
		cout << kl << ",";
		sum = sum + kl;
		if(kl < min){ min = kl;}
		if(kl > max){ max = kl;}
	}
	sum = sum / _input.size();
	cout << "])" << endl;
	vector<double > val ={min, max, sum};
	return val;
}
vector<double > Test::testMIS(int iterat, double err){
	for(int i=0; i< _input.size();i++){
		int j=0;
		vector<double> p1 = _input[i];
		vector<double> p2(_allxy,0.0);
		for(int itera=0; itera < iterat; itera++){
			j = itera%_neuron;
			////cout << j << endl;
			vector< double> pxyi(_allx*2,0.0);
			vector< double> pxiyi(4,0.0);
			vector< double> px(_allx,0.0);
			vector< double> py(_allx,0.0);
			vector< double> pxi(2,0.0);
			////cout<<"pi "<<  " " << accumulate(p1.begin(),p1.end(),0.0) << endl;
			for(int x =0; x< _allxy; x++){
				pxyi[floor(x/_allx)*2+((int)floor(x/pow(2,(_neuron-1)-j)))%2] = pxyi[floor(x/_allx)*2+((int)floor(x/pow(2,(_neuron -1)-j)))%2] + p1[x];
				////cout << j << " " << x << " " << floor(x/32)*2+((int)floor(x/pow(2,4-j)))%2 << endl;
			}
			double sum =0;
			for(int x=0; x< _neuron*2; x++){
				sum = sum + pxyi[x];
			}
			////cout<<"pxyi "<< sum << " " << accumulate(pxyi.begin(),pxyi.end(),0.0) << endl;
			for(int x=0; x< _allxy; x++){
				pxiyi[(int)floor(x/pow(2,(_neuron-1)-j))%2 + 2*((int)(floor(x/(floor(_allxy /pow(2,j+1)))))%2)] = pxiyi[(int)floor(x/pow(2,(_neuron -1)-j))%2 + 2*((int)(floor(x/(floor(_allxy/pow(2,j+1)))))%2)]+ p1[x];
			}
			////cout<<"pxiyi " << accumulate(pxiyi.begin(),pxiyi.end(),0.0) << endl;
			for(int x=0; x<_allxy; x++){
				px[x/_allx] = px[x/_allx] + p1[x];
				py[x%_allx] = py[x%_allx] + p1[x];
			}
			////cout<<"px " << accumulate(px.begin(),px.end(),0.0) << endl;
			////cout<<"py " << accumulate(py.begin(),py.end(),0.0) << endl;
			for(int x=0; x<_allxy; x++){
				pxi[(x/((int)floor(_allxy/ pow(2,j+1))))%2] = pxi[(x/((int)floor(_allxy/ pow(2,j+1))))%2] + p1[x];
			}
//			if(j==1){
//				//cout << pxiyi[0] << " " << pxiyi[1] << " " << pxiyi[2] << " " << pxiyi[3]  << " " << pxiyi.size() << endl;
//			}
			////cout<<"pxi " << accumulate(pxi.begin(),pxi.end(),0.0) << endl;
			for(int x =0; x < _allxy; x++){
				p2[x] = (px[x/_allx]*pxiyi[(int)floor(x/pow(2,(_neuron -1)-j))%2 + 2*((int)(floor(x/(floor(_allxy/pow(2,j+1)))))%2)]*p1[x])/(pxi[(x/((int)floor(_allxy/ pow(2,j+1))))%2] * pxyi[floor(x/_allx)*2+((int)floor(x/pow(2,(_neuron -1)-j)))%2]);
			}
			err= _kl(p1,p2);
			p1 = p2;
			pxyi.clear();
			pxiyi.clear();
			px.clear();
			py.clear();
			pxi.clear();
			////cout << itera << " " << err << endl;
		}
		//cout << _kl(_input[i], p1) << "," << endl;
		p1.clear();
		p2.clear();
	}
	return {0,100,100};
}
vector<double > Test::testCEI(int m, int it, int start){
	double  minall = 100.0;
	double  max = 0.0;
	double  sum = 0.0;
	double  kl = 0;
	vector<int> l1(_neuron,2);
	emIterate *E = new emIterate(_neuron,m,l1,_input[0]);
	vector<double> newp = E->getProb(); 
	vector<double> minp = newp; 
	cout << "CEI = np.array([";
	for(int i=0; i < _input.size();i++){
		//cout << "i " << i << endl;
		double min = 100;
		for(int st =0; st<start; st++){
			E->changeP(_input[i],true);
			E->iterate(it,1e-8);
			kl = E->Kl();
			if(kl < min){ 
				//cout << "minp" << endl;
				min = kl;
			}
		}
		sum = sum + min;
		if(min < minall){ minall = min;}
		if(min > max){ max = min;}
		cout << min <<",";

	}
	sum = sum / _input.size();
	cout << "])"<< endl;
	vector<double > val ={minall, max, sum};
	return val;
}

vector<double > Test::testG(int iterat, double err){
	double  min = 100.0;
	double  max = 0.0;
	double  sum = 0.0;
	double  kl = 0;
	cout << "G = np.array([";
	for(int i=0; i < _input.size();i++){
		int it =0;
		double r = 2;
		vector<double> pi(_allxy,1.0/_allxy);
		vector<double> pj(_allxy,0.0);
		vector<double> px(_allx,0.0);
		vector<double> py(_allx,0.0);
		vector<double> pl = _input[i];
		vector< vector<double> > pyixi;
		for(int j=0; j<_allxy; j++){
			px[j/_allx] = px[j/_allx] + _input[i][j];
			py[j%_allx] = py[j%_allx] + _input[i][j];
		}
		for(int j=0; j<_neuron; j++){
			vector<double> pf(_allx*pow(2,j)*2,0.0);
			for(int k=0; k<_allxy;k++){
				pf[k/(pow(2,(_neuron -1)-j))] = pf[floor(k/(pow(2,(_neuron -1)-j)))] + _input[i][k];
			}
			vector<double> pff(_allx*2,0.0);
			for(int k=0; k < _allx*pow(2,j)*2; k++){
				pff[k%(_allx*2)] = pff[k%(_allx*2)] + pf[k];
			}
			vector<double> pyixir(4,0.0);
			for(int k=0; k< _allx*2; k++){
				pyixir[floor(k/_allx)*2 + k%2] = pyixir[floor(k/_allx)*2 + k%2] + pff[k];
				//	//cout << "j " << j << " k " << k << " " << floor(k/_allx)*2 + k%2<< endl;
			}

			vector<double> pyicxi = {pyixir[0]/(pyixir[0] + pyixir[1]), pyixir[1]/(pyixir[0] + pyixir[1]), pyixir[2]/(pyixir[2] + pyixir[3]), pyixir[3]/(pyixir[2] + pyixir[3])};
			pf.clear();
			pff.clear();
			pyixi.push_back(pyicxi);
		}
		while(it < iterat && r > err){
			pl = pi;
			vector<double> pxj(_allx,0.0);
			for(int j=0; j<_allxy; j++){
				pxj[j/_allx] = pxj[j/_allx] + pi[j];
			}
			for(int x =0; x<_allxy; x++){
				pj[x]=pi[x]* px[x/_allx]/pxj[x/_allx];
		//    	//cout<< "px " << pj[x] << " " <<  px[x/32]<<" " << pxj[x/32] << endl;
			}
			for(int j =0; j< _neuron; j++){
				vector<double> pf(_allx*pow(2,j)*2,0.0);
				for(int k=0; k<_allxy;k++){
					pf[k/(pow(2,(_neuron -1)-j))] = pf[floor(k/(pow(2,(_neuron -1)-j)))] + pj[k];
				}
				vector<double> pff(_allx*2,0.0);
				for(int k=0; k < _allx*pow(2,j)*2; k++){
					pff[k%(_allx*2)] = pff[k%(_allx*2)] + pf[k];
				}
				vector<double> pyixir(4,0.0);
				for(int k=0; k< (_allx*2); k++){
					pyixir[floor(k/_allx)*2 + k%2] = pyixir[floor(k/_allx)*2 + k%2] + pff[k];				}
				vector<double> pyicxi = {pyixir[0]/(pyixir[0] + pyixir[1]), pyixir[1]/(pyixir[0] + pyixir[1]), pyixir[2]/(pyixir[2] + pyixir[3]), pyixir[3]/(pyixir[2] + pyixir[3])};
				for(int x=0; x<_allxy;x++){
					pi[x] = pj[x]*pyixi[j][(int)floor(x/pow(2,(_neuron -1)-j))%2 + 2*((int)(floor(x/(floor(_allxy/pow(2,j+1)))))%2)]/ pyicxi[(int)floor(x/pow(2,(_neuron -1)-j))%2 + 2*((int)(floor(x/(floor(_allxy/pow(2,j+1)))))%2)];
				}
				pj = pi;
			}
			vector<double> pyj(_allx,0.0);
			for(int j=0; j<_allxy; j++){
				pyj[j%_allx] = pyj[j%_allx] + pj[j];
			}
			double sum =0.0;
			for(int x=0; x<_allxy; x++){
				pi[x] = pj[x]*py[x%_allx]/pyj[x%_allx];
				sum = sum + pi[x];
				////cout << "pi " << pi[x%32] << " " << sum << endl;
			}
			vector<double> pyj2(_allx,0.0);
			for(int j=0; j<_allxy; j++){
				pyj2[j%_allx] = pyj2[j%_allx] + pi[j];
			}
			r = _kl(pl,pi);
			it = it + 1;
		}
		////cout<< "berechne kl" << endl;
		kl = _kl(_input[i],pi);
		sum = sum + kl;
					if(kl < min){ min = kl;}
					if(kl > max){ max = kl;}
		pi.clear();
		cout << kl << ",";
		pj.clear();
		px.clear();
		py.clear();
	}
	sum = sum / _input.size();
	cout << "])" << endl;
	vector<double > val ={sum-min, max -sum, sum};
	return val;
}

double Test:: _kl(vector<double> &p, vector<double> &q){
	assert(p.size() == q.size());
	double kl =0;
	for(int i =0; i< p.size(); i++ ){
		if(p[i]*q[i] !=0){
			kl = kl + p[i]*(log2(p[i]) - log2(q[i]));
		}
		if(q[i] ==0 && p[i]>0.00000000001){
			kl = kl +2000;
		}
	}
	return kl;
}


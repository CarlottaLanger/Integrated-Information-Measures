/*
 * Probability.cpp
 *
 *  Created on: Dec 2, 2019
 *      Author: langer
 */
#include "ProbabilityDist.h"

#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <vector>

using namespace std;

Probability::Probability(int n, int m, vector<int> &l, vector<double> &p){
	_m = m;
	_n = n;
	_sizeAlph =  _m;
	_sizeX = 1;
	for(int i = 0; i < _n; i++){
		_sizeAlph = _sizeAlph * pow(l[i],2);
		_sizeX = _sizeX *l[i];
	}
	for(int i = 0 ; i < _n; i++){
		////cout << "l " << l[i] << endl;
		_l.push_back(l[i]);
	}
	//cout << p.size() << " " << _sizeAlph << endl;
	//assert(p.size() ==_sizeAlph);
	for(int i = 0; i < _sizeAlph; i++){
		_p.push_back(p[i]);
		////cout << _p.at(i) << " " << p[i] << endl;
	}
		for(int i = 0 ; i < _n ; i ++ ){
			int withouti = 1;
			int biggeri = 1;
			int smalleri = 1;
			vector<vector<int> > indexi;
			vector<vector<int> > indexixw;
			for(int l = 0 ; l < _n ; l ++ ){
				if(l!=i){
					withouti = withouti * _l[l];
				}
				if(l>i){
					biggeri = biggeri *_l[l];
				}
				if(l<i){
					smalleri = smalleri * _l[l];
				}
			}
			_biggeri.push_back(biggeri);
			for(int i =0; i < _biggeri.size(); i++){
				////cout <<"BIGGERI " << i << " "<< _biggeri[i] << endl;
			}
			if(smalleri == 1){
				smalleri =0;
			}
			for(int k = 0; k < _sizeAlph; k++ ){
				vector<int> indexk;
				for(int j = 0; j < pow(withouti,2); j++ ){
					////cout<< "i " << i << " k " << k << " j " << j << endl;
								 // ////cout << k << " " << k + m << " " << k+(l1[i+1]-1)*m  << " " << k+ l1[0]*l1[1]*m << " " <<k+ l1[0]*l1[1]*m +(l1[i+1]-1)*m  << " " <<  k + l1[0] * l1[1] * 2* m  << " " << k + l1[0] * l1[1] * 2* m +  (l1[i+1]-1)*m << endl;
					int z =0;
					int z2 = 0;
					int z3 = 0;
					int z4 = k/_m;
					int z5 = k/ (_l[i]*_m);
					int sumipl1 =0;
					if(i == 0){
						sumipl1 = (biggeri -1)*_sizeX;
					}
					else{
						sumipl1 = (withouti -1)*biggeri*_l[i];
					}
					if(biggeri!=0) {
						z = j % (biggeri) ;
						z2 = j /(biggeri);
					}
					if(smalleri!=0) {
						z3 = j / ( pow(biggeri,2) * smalleri);
					}
							//////cout << z << " " <<z2 << " z3 " << z3 << " " << z4 << " " << z5 << " "<< biggeri << " " << alli <<" " << _l[i] << " " << smalleri<<  endl;
							//////cout <<  k + biggeri *_l[i]*m*z2 + z*m +  z3 * m * alli * biggeri*(_l[i]-1) + z4*(biggeri-1)*m  +  z5*sumipl1*m << endl;
					indexk.push_back(k + biggeri *_l[i]*_m*z2 + z*_m +  z3 * _m * _sizeX * biggeri*(_l[i]-1) + z4*(biggeri-1)*_m  +  z5*sumipl1*_m);
				}
				indexi.push_back(indexk);
			}
			for(int k = 0; k < _l[i]*_m; k++ ){
				vector<int> indexkxw;
				for(int j = 0; j < withouti*_sizeX; j++ ){
					int z =0;
					int z3 = 0;
					if(biggeri!=0) {
						z = j % (withouti * _sizeX) ;
					}
					if(smalleri!=0) {
						z3 = j / (_sizeX * biggeri );
					}
					indexkxw.push_back(k  + (k/_m)*_m*(_sizeX* biggeri -1) + z3* _sizeX * biggeri * _m *(_l[i]-1) + z*_m);
						}
						indexixw.push_back(indexkxw);
					}
				_indices.push_back(indexi);
				_indicesxw.push_back(indexixw);
				}
}

Probability::Probability(){

}
Probability::~Probability(){
//	_p.~vector();
//	_marginalsw.~vector();
//	_marginalsxy.~vector();
//	_marginalsx.~vector();
//	_biggeri.~vector();
//	_l.~vector();
	for(int i=0; i<_indicesxw.size();i++){
		for(int j=0; j< _indicesxw[i].size(); j++){
			_indicesxw[i][j].clear();
		}
	}
	for(int i=0; i<_indices.size();i++){
		for(int j=0; j< _indices[i].size(); j++){
			_indices[i][j].clear();
		}
	}
	for(int i=0; i<_marginalsyxw.size();i++){
		_marginalsyxw.clear();
	}
	for(int i=0; i<_marginalsycxw.size();i++){
		_marginalsycxw.clear();
	}
}
vector<double> Probability::getMarginalProb(){
	setMarginalsEproj();
	return _marginalsxy;
}
vector<double> Probability::getProb(){
	return _p;
}

void Probability::changeProp(vector<double> &p){
	_p = p;
}
double Probability::mProj(){
	vector<double> oldp = _p;
	setMarginalsMproj();
	double difference = 0;
	for(int i=0; i< _sizeAlph; i++){
		_p[i] = _marginalsx[i/(_sizeX*_m)] * _marginalsw[i%_m];
		////cout << " marginalsx " <<  _marginalsx[i/(_sizeX*_m)]  << " marginalsw " << _marginalsw[i%_m] << " " << _p[i] <<  endl;
		for(int j =0; j< _n;j++){
			int k = _sizeX*_biggeri[j]*_m;
		//	cout <<i << " " <<  j << " " << _biggeri[j] << " "<< (i%_m +  (i/(_biggeri[j]*_m))%_l[j]*_m +  (i/k)*_l[j]*_m)%(_l[j]*_l[j]*_m)<< endl;

			_p[i] = _p[i]*_marginalsycxw[j][(i%_m +  (i/(_biggeri[j]*_m))%_l[j]*_m +  (i/k)*_l[j]*_m)%(_l[j]*_l[j]*_m)];
		}
		////cout << i << " " << i/(_sizeX*_m) << " " << i % _m << " " << _p[i] << endl;
		double localdiff = abs(_p[i] - oldp[i]);
		if(localdiff > difference){
			difference = localdiff;
		}
	}
	return difference;
}

double Probability::eProj(vector<double> &originalp){
	assert(originalp.size() == pow(_sizeX,2));
	vector<double> oldp = _p;
	setMarginalsEproj();
	double sum = 0;
	double difference = 0 ;
	for(int i =0 ; i < _sizeAlph ; i++){
		_p[i] = originalp[i/_m]*_p[i]/_marginalsxy[i/_m];
		double localdiff = abs(_p[i] - oldp[i]);
		if(localdiff > difference){
			difference = localdiff;
		}
		////cout << "e-proj" << _p[i] << endl;
		sum = sum + _p[i];
	}
	////cout << "SUM" << sum << endl;
	return difference;
}

bool Probability::setMarginalsMproj(){
	_marginalsx.clear();
	for(int i =0 ; i < _sizeX ; i++ ){
		double sum = 0;
		for(int j=0; j< _sizeX * _m; j++ ){
			sum = sum + _p[i*(_sizeX * _m) +j];
		}
		_marginalsx.push_back(sum);
		////cout << sum << endl;
	}
	_marginalsw.clear();
	for(int i = 0; i < _m; i++){
		double sum =0;
		for(int j = 0; j < pow(_sizeX,2) ; j++){
			sum = sum + _p[i + _m*j];
		}
		_marginalsw.push_back(sum);
		////cout << "sum" << sum << endl;
	}
	_marginalsyxw.clear();
	vector<vector<double>> marginalsxw;
	////cout<< "marginalsxw " << endl;
	for(int i = 0 ; i < _n ; i ++ ){
		int withouti = 1;
		for(int l = 0 ; l < _n ; l ++ ){
			if(l!=i){
				withouti = withouti * _l[l];
			}
		}
		vector<double> marginalsi;
		for(int k = 0; k < pow(_l[i],2)*_m; k++ ){
				double sum = 0;
				for(int j = 0; j < pow(withouti,2); j++ ){
					sum = sum + _p[_indices[i][k][j]];
				}
				marginalsi.push_back(sum);
		}
		_marginalsyxw.push_back(marginalsi);

		vector<double> marginalsixw;
		for(int k = 0; k < _l[i]*_m; k++ ){
			double sum = 0;
			for(int j = 0; j < withouti*_sizeX; j++ ){
				sum = sum + _p[_indicesxw[i][k][j]];
			}
			marginalsixw.push_back(sum);
			////cout << "i " << i << "k "<< k << " " << sum  << endl;
		}
		marginalsxw.push_back(marginalsixw);
	}
	////cout << "marginalsycxw" << endl;
	_marginalsycxw.clear();
	for(int i =0; i < _n ; i++){
		////cout << "i " <<i << endl;
		vector<double> marginalsyicxiw;
		for(int j =0 ; j < pow(_l[i],2)*_m; j++){
			  //////cout << j << " " << (j%_m)+(j/(_l[i]*_m)*_m) << endl;
			  marginalsyicxiw.push_back(_marginalsyxw[i][j]/marginalsxw[i][(j%_m)+(j/(_l[i]*_m)*_m)]);
			  ////cout << marginalsyxw[i][j]/marginalsxw[i][(j%_m)+(j/(_l[i]*_m)*_m)] << endl;
		}
		_marginalsycxw.push_back(marginalsyicxiw);
	}
	return true;
}

bool Probability::setMarginalsEproj(){
	int k = 0;
	////cout << "marginalsxy" << " size beginning " << endl;
	_marginalsxy.clear();
	for(int i = 0; i < pow(_sizeX,2); i++){
		////cout << "i " << i  << endl;
		double sum = 0;
		for(int j=0; j < _m ; j++){
			sum = sum + _p[j + k];
		}
		k = k+_m;
		_marginalsxy.push_back(sum);
		////cout << sum << endl;
	}
	////cout << "size " << _marginalsxy.size() << " " << pow(_sizeX,2) << endl;
	return true;
}

ostream& operator<<(ostream& os, const Probability& p){
	for(int z=0; z< 3 ;z++){
		os << "n" << endl;
	}
    return os;
}

void Probability::testCondInd(){
	setMarginalsEproj();
	setMarginalsMproj();
	for( int i=0 ; i< _n; i++){
	//	cout << "i" << i << endl;
		vector<double> pyicxi(pow(_l[i],2),0.0);
		vector<double> pyicx(_l[i]*_sizeX,0.0);
		vector<double> pxi(_l[i], 0.0);
		for(int j =0; j< pow(_l[i],2)*_m; j++){
			pyicxi[j/_m] = pyicxi[j/_m] + _marginalsyxw[i][j];
			pxi[j/(_m*_l[i])] = pxi[j/(_m*_l[i])] + _marginalsyxw[i][j];
		}
		for(int j =0; j< pow(_l[i],2); j++){
			pyicxi[j] = pyicxi[j]/ pxi[j/_l[i]];

		//	cout << "conditioned " << pyicxi[j]  << " " << pxi[j/_l[i]]<< endl;
		}
		for(int j=0; j<pow(_sizeX,2);j++){
			pyicx[(j/_sizeX)*_l[i] + (j/_biggeri[i]%_l[i])] = pyicx[(j/_sizeX)*_l[i] + (j/_biggeri[i]%_l[i])] + _marginalsxy[j];
		}
		for(int j=0; j<_sizeX*_l[i]; j++){
			pyicx[j] = pyicx[j]/_marginalsx[j/_l[i]];
		//	cout<< "conditioned2 " << pyicx[j] << endl;
		}
	}
}

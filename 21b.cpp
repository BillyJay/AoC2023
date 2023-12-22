#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>
#include <random>
#include <set>

using namespace std;


map<string, int> nm_to_idx;
map< string, bool >flip_flops;
map<string, map<string, bool> > conjs;

vector<int> state;

long long count(long long n,vector<pair<long long,long long> > pts){
	long long x1 = pts[0].first;
	long long y1 = pts[0].second;
	long long x2 = pts[1].first;
	long long y2 = pts[1].second;
	long long x3 = pts[2].first;
	long long y3 = pts[2].second;
	long long ans = (y1 * (n-x2)* (n-x3)/(x1-x2))/(x1-x3) ;
	ans += (y2 * (n-x1)*  (n-x3)/(x2-x1))/(x2-x3) ;
	ans += (y3 * (n-x1)* (n-x2)/(x3-x2))/(x3-x1) ;
	return ans;
}


int main(){
	ifstream file;
	file.open("input21.txt");
	// file.open("input21test.txt");
	const int L = 131;
	// const int L = 11;
	char field[L][L];
	set<pair<long long, long long> > s;
	for(long long i = 0; i < L; i++){
		for(long long j = 0; j < L; j++){
			file>>field[i][j];
			if(field[i][j]=='S') {
				cout<<i<<" "<<j<<endl;
				field[i][j] = '.';
				s.insert({i,j});
			}
		}
	}
	set<pair<long long, long long> > s_orig = s;
	//number of O's is quadratic polynomial in i
	//determined here:
	vector<pair<long long,long long> > pts;
	for(int i = 0; i < 3;i++){
		s = s_orig;
		for(int step =0; step < i*131+65; step++){
			set<pair<long long, long long> > s_cp;

			for(auto el : s){
				int i,j;
				i = el.first;
				j = el.second;
				if(field[(i+1+L*L)%L][(j+L*L)%L] != '#') s_cp.insert({i+1,j});
				if(field[(i-1+L+L*L)%L][(j+L*L)%L]!='#') s_cp.insert({i-1,j});
				if(field[(i+L*L)%L][(j+1+L*L)%L]!='#') s_cp.insert({i,j+1});
				if(field[(i+L*L)%L][(j-1+L+L*L)%L] != '#') s_cp.insert({i,j-1});
			}
			s = s_cp;
		}
		pts.push_back({i,s.size()});
		cout<<s.size()<<endl;
	}
	
	//26501365 = 202300*131 + 65
	long long n = 202300; 
	cout<<"Answer = "<<count(n,pts)<<endl;

	return 0;
}
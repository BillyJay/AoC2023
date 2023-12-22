#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>
#include <random>
#include <set>

using namespace std;

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

	for(int step =0; step < 64; step++){
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
	cout<<s.size()<<endl;

	return 0;
}
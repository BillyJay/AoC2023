#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;


int main(){
	ifstream file;
	file.open("input11.txt");
	// file.open("input11text.txt");
	const int L = 140;
	char mat[L][L];
	vector<int> expCol, expRow;
	vector<pair<int,int>> pos;
	for(int i = 0; i < L; i++){
		bool rowdot = true;
		for(int j = 0; j< L; j++){
			file>>mat[i][j];
			if(mat[i][j] == '#') pos.push_back({i,j});
			if(mat[i][j] != '.') rowdot = false;
		}
		if(rowdot) expRow.push_back(i);
	}
	for(int j = 0; j < L; j++){
		bool coldot = true;
		for(int i = 0; i< L; i++){
			if(mat[i][j] != '.') coldot = false;
		}
		if(coldot) expCol.push_back(j);
	}
	for(int i = 0; i < L; i++){
		for(int j = 0; j< L; j++){
			if(find(expCol.begin(), expCol.end(), j)!=expCol.end()){
				mat[i][j] = 'C';
			}
			if(find(expRow.begin(), expRow.end(), i)!=expRow.end()){
				mat[i][j] = 'R';
			}
		}

	}




	vector<long long> dist;
	for(auto el1 : pos){
		for(auto el2 : pos){
			if(el1==el2) continue;
			long long d = 0;
			
			for(int i = min(el1.first,el2.first); i < max(el1.first,el2.first);i++){
					if(mat[i][min(el1.second,el2.second)] =='.' || mat[i][min(el1.second,el2.second)] =='#') d++;
					if(mat[i][min(el1.second,el2.second)] =='R') d+=1000000;
			}
			for(int j = min(el1.second,el2.second); j < max(el1.second,el2.second);j++){
					if(mat[max(el1.first,el2.first)][j] =='.' || mat[max(el1.first,el2.first)][j] =='#' ) d++;
					if(mat[max(el1.first,el2.first)][j] =='C') d+=1000000;
			}
			dist.push_back(d);
		}
	}
	cout<<"pos "<<pos.size()<<endl;
	long long ans = 0;
	int ctr = 1;
	sort(dist.begin(),dist.end());
	for(auto el : dist) {
		ans+=el;
		cout<<ctr<<" "<<el<<endl;
		ctr++;

	}

	cout<<endl<<ans/2<<endl;
	return 0;
}

#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

pair<int, int> get_hash(string x){
	int val = 0;
	int j = 0;
	while(x[j]!='=' && x[j]!='-'){
		val = val + x[j];
		val = val*17 ;
		val %= 256;
		j++;
	}
	return {val, j};
}

int main(){
	ifstream file;
	file.open("input15.txt");
	// file.open("input15test.txt");
	vector<vector<pair<string, long long> > > seq(256);
	long long ans = 0;
	for(int i = 0; i < 4000; i++){
	// for(int i = 0; i < 11; i++){
		string x;
		file>>x;

		pair<int, int> hash_res;
		hash_res = get_hash(x);
		int box = hash_res.first; 
		int sgn_idx = hash_res.second;
		char sgn = x[sgn_idx];
		int lens = -1;
		if(sgn == '=') lens = x[sgn_idx+1] -'0';
		string label_str = x.substr(0,sgn_idx);
		if(sgn =='='){
			bool found = false;
			for(int b = 0; b < seq[box].size();b++){
				if(seq[box][b].first == label_str){
					seq[box][b].second = lens;
					found = true;
				}
			}
			if(!found){
				seq[box].push_back({label_str, lens});
			}
		}
		if(sgn == '-'){
			assert(lens==-1);
			for(int b = 0; b < seq[box].size();b++){
				if(seq[box][b].first == label_str){
					seq[box].erase(seq[box].begin() + b);
				}
			}
		}
	}

	for(int i = 0; i < seq.size(); i++){
		for(int j = 0; j < seq[i].size(); j++){
			cout<<seq[i][j].first<<" "<<seq[i][j].second;
			ans+= (i+1)*(j+1)*(seq[i][j].second);
			cout<<endl;
		}
	}
	cout<<ans<<endl;
	return 0;
}
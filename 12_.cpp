#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;


map<pair<string,vector<int> >, long long> mp;
long long get_comb(string x, vector<int> blocks){
	long long total_hashes = 0;
	for(auto el : blocks){
		total_hashes += el;
	}
	if(total_hashes > x.size()) return 0;
	if(x =="#" && blocks.size() == 1 && blocks[0] == 1) return 1;
	if(x =="#" && (blocks.size() != 1 || blocks[0] != 1)) return 0;

	if(blocks.size() == 0){
		for(int i = 0; i < x.size(); i++){
			if(x[i] == '#') return 0;
		}
		return 1;
	}
	if(x.size()==0 && blocks.size()==0) return 1;
	if(x.size()==0 && blocks.size()!=0) return 0;
	while (x[x.size()-1]=='.') x.resize(x.size()-1);

	string part = "";
	if(x.size()!=0 && x[x.size()-1]=='#'){
		while(x.size()!=0 && x[x.size()-1]=='#'){
			part = x[x.size()-1]+part;
			x.resize(x.size()-1);
		}
		if(x[x.size()-1]=='.'){
			if(part.size() == blocks.back()){
				blocks.pop_back();
				if(mp[{x,blocks}]!=0) return mp[{x,blocks}]-1;	
				else{
					mp[{x,blocks}] = get_comb(x,blocks)+1;
					return mp[{x,blocks}]-1;
				}
			}
			else return 0;
		}
		else{
			assert(x.size() ==0 || x[x.size()-1]=='?');
			if(blocks.back() == part.size()){
				x[x.size()-1] = '.';
				blocks.pop_back();
				if(mp[{x,blocks}]!=0) return mp[{x,blocks}]-1;	
				else{
					mp[{x,blocks}] = get_comb(x,blocks)+1;
					return mp[{x,blocks}]-1;
				}
			}
			else{
				if(blocks.back() < part.size()){
					return 0;
				}
				else{
					x[x.size()-1] = '#';
					if(mp[{x+part,blocks}]!=0) return mp[{x+part,blocks}]-1;	
					else{
						mp[{x+part,blocks}] = get_comb(x+part,blocks)+1;
						return mp[{x+part,blocks}]-1;
					}
				}
			}
		}
	}

	
	if(x[x.size()-1]=='?'){
		x[x.size()-1] = '.';
		long long ans1;
		if(mp[{x,blocks}]!=0) ans1 = mp[{x,blocks}]-1;
		else{
			mp[{x,blocks}] = get_comb(x,blocks)+1;
			ans1 = mp[{x,blocks}]-1;
		}
		 
		

		long long ans2 = 0;
		bool failed = false;
		x[x.size()-1] = '#';
		int b = blocks.back();
		if(x.size() < b) {
			ans2 = 0;
			failed = true;
		}
		else{
			for(int f = 0; f < b; f++){
				
				if (x.size() == 0 || x[x.size()-1] == '.'){
					ans2 = 0;
					failed = true;
					break;
				}
				if ((x[x.size()-1]=='#' || x[x.size()-1]=='?')){
					x.resize(x.size()-1);
				}
			}
			if(failed) return ans1;
			if(x.size() == 0 && blocks.size() == 1) ans2 = 1;
			if (x[x.size()-1] == '#') ans2 = 0;
			else {
				if (x[x.size()-1] == '?') x[x.size()-1] = '.';
				blocks.pop_back();
				if(mp[{x,blocks}]!=0) ans2 = mp[{x,blocks}]-1;
				else{
					mp[{x,blocks}] = get_comb(x,blocks)+1;
					ans2 = mp[{x,blocks}]-1;
				}
			}
		}
		return ans1+ans2;
	}
	return 0;
}



int main(){
	ifstream file;
	file.open("input12_mod.txt");
	// file.open("input12_mod2.txt");
	
	vector<string> all_x;
	vector<vector<int> > all_blocks;
	for(int i = 0; i < 1000; i++){
	// for(int i = 0; i < 6; i++){
		int n;
		string x;
		file>>n>>x;
		all_x.push_back(x);
		vector<int> blocks(n);
		cout<<x<<endl;
		for(int i = 0; i < n; i++) file>>blocks[i];
		all_blocks.push_back(blocks);
	}
	cout<<"Loading finished"<<endl<<endl;


	int n = all_blocks.size();
	vector<long long> ans(n);
	long long tot_ans = 0;
	for(int i = 0; i < n; i++){
		string x = all_x[i]+"?"+all_x[i]+"?"+all_x[i]+"?"+all_x[i]+"?"+all_x[i];
		vector<int> blocks;

		for(int r = 0; r < 5; r++){
			for(int j = 0; j < all_blocks[i].size(); j++){
				blocks.push_back(all_blocks[i][j]);
			}
		}

		mp.clear();

		long long ans = get_comb(x,blocks);

		tot_ans += ans;

	}
	cout<<tot_ans<<endl;
	
	return 0;
}
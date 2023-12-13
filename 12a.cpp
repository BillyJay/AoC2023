#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

long long get_num(string x, vector<int> blocks){
	for(int i = 0; i < x.size(); i++){
		if(x[i]=='?'){
			string y = x;
			y[i] = '.';
			long long ans1 = get_num(y,blocks);
			y[i] = '#';
			long long ans2 = get_num(y,blocks);
			return ans1+ans2;
		}
	}
	int ans = 0;
	int curr = 0;
	vector<int> readBlocks;
	for(int i = 0; i < x.size(); i++){
		if(x[i]=='.'){
			if(curr!=0){
				readBlocks.push_back(curr);
				curr = 0;
			}
		}
		else
			curr++;
	}
	if(curr!=0) readBlocks.push_back(curr);

	if(readBlocks==blocks) return 1;
	return 0;
}


int main(){
	ifstream file;
	file.open("input12_mod.txt");
	// file.open("input12test.txt");
	long long ans = 0;
	for(int i = 0; i < 1000; i++){
		int n;
		string x;
		
		file>>n>>x;
		vector<int> blocks(n);
		for(int i = 0; i < n; i++){
			file>>blocks[i];
		}
		ans+=get_num(x,blocks);
	}
	cout<<ans<<endl;
	return 0;
}

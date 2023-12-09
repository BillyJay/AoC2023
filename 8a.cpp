#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>
#include <algorithm>
#include <numeric>
using namespace std;

bool ok(vector<string> dest){
	bool ans = true;
	for(auto el : dest){
		if(el[2]!='Z'){
			ans = false;
			break;
		}
	}
	return ans;
}


int main(){
	ifstream file;
	file.open("input8.txt");
	string dirs;
	file>>dirs;
	map<string, pair<string, string> > mp;
	vector<string> destinations;
	for(int i = 0; i < 706;i++){
		string a,b,c;
		file>>a>>b>>c;
		mp[a] = {b,c};
		destinations.push_back(a);
	}
	string curr = "AAA";


	long long steps = 0;

	while(curr!="ZZZ"){
	 	for(int j  = 0; j < dirs.size(); j++){
			if(dirs[j] == 'L'){
					curr = mp[curr].first;
			}
			else{
				curr = mp[curr].second;
			}
			steps++;
		}
	}
	cout<<steps<<endl;
	return 0;
}
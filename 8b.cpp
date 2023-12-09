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
	vector<string> curr;
	for(auto el : destinations){
		if(el[2] == 'A'){
			curr.push_back(el);
		}
	}

	vector<long long> steps(curr.size());

	for(int i = 0; i < curr.size(); i++){
		while(curr[i][2]!='Z'){
		 	for(int j  = 0; j < dirs.size(); j++){
				if(dirs[j] == 'L'){
						curr[i] = mp[curr[i]].first;
				}
				else{
					curr[i] = mp[curr[i]].second;
				}
				steps[i]++;
			}
		}
	}
	long long ans = 1;
	for(auto el : steps){
		ans = lcm(ans, el);
	}
	cout<<ans<<endl;
	return 0;
}
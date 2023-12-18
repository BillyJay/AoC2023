#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sstream>

using namespace std;




int main(){
	ifstream file;
	file.open("input18.txt");
	// file.open("input18test.txt");
	const int fileLines=670;
	// const int fileLines=14;
	vector<char> dir(fileLines);
	vector<int> l(fileLines);
	for(int i = 0; i < fileLines; i++){
		string c;
		char x;int y;
		file>>x>>y>>c;
		int nmb;
		istringstream(c.substr(1,5)) >> std::hex >> nmb;
		// cout<<nmb<<endl;
		l[i] = nmb;
		if(c[6]-'0' == 0 ) dir[i] = 'R';
		if(c[6]-'0' == 1 ) dir[i] = 'D';
		if(c[6]-'0' == 2 ) dir[i] = 'L';
		if(c[6]-'0' == 3 ) dir[i] = 'U';

	}

	long long posi,posj;
	posi = 0; posj = 0;
	vector<pair<long long,long long> > pos;
	pos.push_back({posi,posj});
	for(int i = 0; i < dir.size(); i++){
		if(dir[i]=='R'){
			for(int j = 0; j < l[i]; j++){
				posj++;
				pos.push_back({posi,posj});
			}
		}
		if(dir[i]=='L'){
			for(int j = 0; j < l[i]; j++){
				posj--;
				pos.push_back({posi,posj});
			}
		}
		if(dir[i]=='U'){
			for(int j = 0; j < l[i]; j++){
				posi--;
				pos.push_back({posi,posj});
			}
		}
		if(dir[i]=='D'){
			for(int j = 0; j < l[i]; j++){
				posi++;
				pos.push_back({posi,posj});
			}
		}
	}
	
	long long ans = 0;
	
	for(int i = 0; i < pos.size()-1; i++){
		ans += (pos[i].second + pos[i+1].second)*(pos[i].first - pos[i+1].first);

	}
	ans =abs(ans/2);
	ans += (pos.size())/2+1;
	cout<<ans<<endl;


	return 0;
}
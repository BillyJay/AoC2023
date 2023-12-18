#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;


char field[2000][2000];


int main(){
	ifstream file;
	file.open("input18.txt");
	
	vector<char> dir(670);
	vector<int> l(670);
	for(int i = 0; i < 670; i++){
		string c;
		file>>dir[i]>>l[i]>>c;

	}
	int posi = 0;
	int posj = 0;
	vector<pair<int,int> > pos;
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

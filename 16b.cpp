#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

long long get_tiles(vector<string> &field,pair<int,int> start_pos,pair<int,int> start_dir){
	int n = field.size();
	bool visited[n][n];
	for(int i = 0; i < n; i++ ){
		for(int j = 0; j < n; j++){
			visited[i][j] = false;
		}
	}
	vector<pair<int, int> > pos = {start_pos};
	vector<pair<int, int> > dir = {start_dir};
	

	int old_ans = -1;
	int rep_ctr = 0;
	while(true){
		vector<pair<int, int> > add_to_pos;
		vector<pair<int, int> > add_to_dir;
		auto visited_copy = visited;
		for(int walker = 0; walker < pos.size(); walker++){

			pos[walker].first = pos[walker].first + dir[walker].first;
			pos[walker].second = pos[walker].second + dir[walker].second;
			if(pos[walker].first >= n || pos[walker].second >= n || pos[walker].first <= -1 || pos[walker].second <= -1){
				continue;
			}
			visited[pos[walker].first][pos[walker].second] = true;
			if(field[pos[walker].first][pos[walker].second] == '\\'){
				if(dir[walker] == make_pair(0,1)){
					dir[walker] = make_pair(1,0);
					continue;
				}
				if(dir[walker] == make_pair(0,-1)){
					dir[walker] = make_pair(-1,0);
					continue;
				}
				if(dir[walker] == make_pair(1,0)){
					dir[walker] = make_pair(0,1);
					continue;
				}
				if(dir[walker] == make_pair(-1,0)){
					dir[walker] = make_pair(0,-1);
					continue;
				}
			}
			if(field[pos[walker].first][pos[walker].second] == '/'){
				if(dir[walker] == make_pair(0,1)){
					dir[walker] = make_pair(-1,0);
					continue;
				}
				if(dir[walker] == make_pair(0,-1)){
					dir[walker] = make_pair(1,0);
					continue;
				}
				if(dir[walker] == make_pair(1,0)){
					dir[walker] = make_pair(0,-1);
					continue;
				}
				if(dir[walker] == make_pair(-1,0)){
					dir[walker] = make_pair(0,1);
					continue;
				}
			}
			if(field[pos[walker].first][pos[walker].second] == '|'){
				if(dir[walker] == make_pair(0,1) || dir[walker] == make_pair(0,-1)){
					dir[walker] = make_pair(-1,0);
					int posi = pos[walker].first;
					int posj = pos[walker].second;
					add_to_pos.push_back({posi,posj});
					add_to_dir.push_back({1,0});
				}
				continue;
			}
			if(field[pos[walker].first][pos[walker].second] == '-'){
				if(dir[walker] == make_pair(1,0) || dir[walker] == make_pair(-1,0)){
					dir[walker] = make_pair(0,1);
					int posi = pos[walker].first;
					int posj = pos[walker].second;
					add_to_pos.push_back({posi,posj});
					add_to_dir.push_back({0,-1});
					continue;
				}
			}
		}
		for(int i = 0; i < add_to_pos.size(); i++){
			pos.push_back(add_to_pos[i]);
			dir.push_back(add_to_dir[i]);
		}
		for(int walker = 0; walker < pos.size(); walker++){
			if(pos[walker].first >= n || pos[walker].second >= n || pos[walker].first <= -1 || pos[walker].second <= -1){
				pos.erase(pos.begin()+walker);
				dir.erase(dir.begin()+walker);
			}
			for(int other_walker = walker+1; other_walker < pos.size(); other_walker++){
				if(pos[walker].first == pos[other_walker].first && pos[walker].second == pos[other_walker].second && dir[walker].first == dir[other_walker].first && dir[walker].second == dir[other_walker].second){
					pos.erase(pos.begin()+other_walker);
					dir.erase(dir.begin()+other_walker);		
				}
			}
		}
		long long ans = 0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				ans+= (visited[i][j]);
			}
		}
		if(old_ans == ans){
			rep_ctr++;
			if(rep_ctr == 10) break;
		}
		else{
			rep_ctr = 0;
			old_ans = ans;
		}
	}
	
	long long ans = 0;
	system("clear");
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			ans+= (visited[i][j]);
			if(visited[i][j]) cout<<"🏮"; else cout<<field[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"this :"<<ans<<endl;
	return ans;
}


int main(){
	ifstream file;
	file.open("input16.txt");
	// file.open("input16test.txt");
	long long ans = 0;
	vector<string> field(110);
	// vector<string> field(10);
	for(int i = 0; i < field.size(); i++){
		file>>field[i];
	}
	long long best = 0;
	for(int i = 0; i < field.size(); i++){
		best = max (best,get_tiles(field,{i,-1},{0,1}));
		cout<<"best so far: "<< best<<endl;
		best = max (best,get_tiles(field,{i,field.size()},{0,-1}));
		cout<<"best so far: "<< best<<endl;
		best = max (best,get_tiles(field,{-1,i},{1,0}));
		cout<<"best so far: "<< best<<endl;
		best = max (best,get_tiles(field,{field.size(),i},{-1,0}));
		cout<<"best so far: "<< best<<endl;
	}
	cout<<"best :"<<best;

	return 0;
}

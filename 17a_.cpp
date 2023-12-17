#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

vector<string> field;

map <pair<int, int>, vector<string> > path;
map <pair<int, int>, vector<long long> > cost;


int main(){
	ifstream file;
	file.open("input17.txt");
	// file.open("input17test.txt");
	field.resize((141));
	// field.resize(13);
	int field_size = field.size();
	for(int i = 0; i < field.size(); i++){
		file>>field[i];
	}
	
	cost[{0,0}] = {0};
	path[{0,0}] = {"..."};
	for(int rep = 0; rep < 60; rep++){
	cout<<rep<<" of 60 done"<<endl;
		for(int i = 0; i < field_size; i++){
			for(int j = 0; j < field_size;j++){
				if(j-1>=0){
					for(int k = 0; k < path[{i,j-1}].size(); k++){
						auto p = path[{i,j-1}][k];
						if(p==">>>") continue;
						if(p[2]=='<') continue;
						string s = p.substr(1,2)+">";
						auto it = find(path[{i,j}].begin(), path[{i,j}].end(),s);
						if(it == path[{i,j}].end()){
							cost[{i,j}].push_back(cost[{i,j-1}][k]+(field[i][j]-'0'));
							path[{i,j}].push_back(p.substr(1,2)+">");
						}
						else{
							int idx = it - path[{i,j}].begin();
							if (cost[{i,j}][idx] > cost[{i,j-1}][k]+(field[i][j]-'0')){
								cost[{i,j}][idx] = cost[{i,j-1}][k]+(field[i][j]-'0');
								path[{i,j}][idx] = p.substr(1,2)+">";
							}
						}
					}
				}
				if(j+1<field_size){
					for(int k = 0; k < path[{i,j+1}].size(); k++){
						auto p = path[{i,j+1}][k];
						if(p=="<<<") continue;
						if(p[2]=='>') continue;
						string s = p.substr(1,2)+"<";
						auto it = find(path[{i,j}].begin(), path[{i,j}].end(),s);
						if(it == path[{i,j}].end()){
							cost[{i,j}].push_back(cost[{i,j+1}][k]+(field[i][j]-'0'));
							path[{i,j}].push_back(p.substr(1,2)+"<");
						}
						else{
							int idx = it - path[{i,j}].begin();
							if (cost[{i,j}][idx] > cost[{i,j+1}][k]+(field[i][j]-'0')){
								cost[{i,j}][idx] = cost[{i,j+1}][k]+(field[i][j]-'0');
								path[{i,j}][idx] = p.substr(1,2)+"<";
							}
						}
					}
				}
				if(i+1<field_size){
					// cout<<"entered 3"<<endl;
					for(int k = 0; k < path[{i+1,j}].size(); k++){
						auto p = path[{i+1,j}][k];
						if(p=="AAA") continue;
						if(p[2]=='V') continue;
						string s = p.substr(1,2)+"A";
						auto it = find(path[{i,j}].begin(), path[{i,j}].end(),s);
						if(it == path[{i,j}].end()){
							cost[{i,j}].push_back(cost[{i+1,j}][k]+(field[i][j]-'0'));
							path[{i,j}].push_back(p.substr(1,2)+"A");
						}
						else{
							int idx = it - path[{i,j}].begin();
							if (cost[{i,j}][idx] > cost[{i+1,j}][k]+(field[i][j]-'0')){
								cost[{i,j}][idx] = cost[{i+1,j}][k]+(field[i][j]-'0');
								path[{i,j}][idx] = p.substr(1,2)+"A";
							}
						}
					}
				}
				if(i-1>=0){
					for(int k = 0; k < path[{i-1,j}].size(); k++){
						auto p = path[{i-1,j}][k];
						if(p=="VVV") continue;
						if(p[2]=='A') continue;
						string s = p.substr(1,2)+"V";
						auto it = find(path[{i,j}].begin(), path[{i,j}].end(),s);
						if(it == path[{i,j}].end()){
							cost[{i,j}].push_back(cost[{i-1,j}][k]+(field[i][j]-'0'));
							path[{i,j}].push_back(p.substr(1,2)+"V");
						}
						else{
							int idx = it - path[{i,j}].begin();
							if (cost[{i,j}][idx] > cost[{i-1,j}][k]+(field[i][j]-'0')){
								cost[{i,j}][idx] = cost[{i-1,j}][k]+(field[i][j]-'0');
								path[{i,j}][idx] = p.substr(1,2)+"V";
							}
						}
					}
				}
			}
		}
		cout<<"best so far "<<*min_element(cost[{140,140}].begin(), cost[{140,140}].end())<<endl;
	}
	return 0;
}
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>
#include <algorithm>

using namespace std;

const int L = 140;
const int W = 140;

// const int L = 10;
// const int W = 20;

char mat[L][W];
bool visited[L][W];
vector<pair<int, int> > loop;
vector<pair<int, int> > loop_stored;
int area;

void dfs(int i, int j){
	if(visited[i][j] && mat[i][j] != 'S') return;
	if(loop.size() > 2 && mat[i][j] == 'S'){
		loop_stored = loop;
		return;
	}
	
	if(mat[i][j]!='S') visited[i][j] = true;
	if(i+1<L && (mat[i][j]=='|' )) {
		loop.push_back({i+1,j});
		dfs(i+1,j);
		loop.pop_back();
	}
	if(i-1>=0 && (mat[i][j]=='|' )) {
		loop.push_back({i-1,j});
		dfs(i-1,j);
		loop.pop_back();
	}
	if(j+1<W && (mat[i][j]=='-' )) {
		loop.push_back({i,j+1});
		dfs(i,j+1);
		loop.pop_back();
	}
	if(j-1>=0 && (mat[i][j]=='-' )) {
		loop.push_back({i,j-1});
		dfs(i,j-1);
		loop.pop_back();
	}
	
	if(i-1>=0 &&  (mat[i][j]=='L' )) {
		loop.push_back({i-1,j});
		dfs(i-1,j);
		loop.pop_back();
	}
	if(j+1<W &&  (mat[i][j]=='L' )) {
		loop.push_back({i,j+1});
		dfs(i,j+1);
		loop.pop_back();
	}

	if(i+1<L &&  (mat[i][j]=='F' )) {
		loop.push_back({i+1,j});
		dfs(i+1,j);
		loop.pop_back();
	}
	if(j+1<W &&  (mat[i][j]=='F' )) {
		loop.push_back({i,j+1});
		dfs(i,j+1);
		loop.pop_back();
	}

	if(i+1<L &&  (mat[i][j]=='7' )) {
		loop.push_back({i+1,j});
		dfs(i+1,j);
		loop.pop_back();
	}
	if(j-1 >=0 &&  (mat[i][j]=='7' )) {
		loop.push_back({i,j-1});
		dfs(i,j-1);
		loop.pop_back();
	}
	
	if(i-1>=0 &&  (mat[i][j]=='J' )) {
		loop.push_back({i-1,j});
		dfs(i-1,j);
		loop.pop_back();
	}
	if(j-1 >=0 &&  (mat[i][j]=='J' )) {
		loop.push_back({i,j-1});
		dfs(i,j-1);
		loop.pop_back();
	}
	return;
}


void dfs2(int i, int j){
	if(i >= L || j >= W || i < 0 || j < 0) return;
	if(visited[i][j]) return;
	visited[i][j] = true;
	area++;
	if(i+1<L &&mat[i+1][j]!='*') dfs2(i+1,j);
	if(j+1<W &&mat[i][j+1]!='*') dfs2(i,j+1);
	if(i-1>=0 &&mat[i-1][j]!='*') dfs2(i-1,j);
	if(j-1>=0 &&mat[i][j-1]!='*') dfs2(i,j-1);
	return;
}


int main(){
	ifstream file;
	file.open("input10.txt");
	// file.open("input10test.txt");
	int posi, posj;
	for(int i = 0; i < L;i++){
		for(int j = 0; j < W; j++){
			visited[i][j] = false;
			file>>mat[i][j];
			if(mat[i][j]=='S'){
				posi = i;
				posj = j;
			}
		}
	}
	posi++;
	loop.push_back({posi,posj});
	dfs(posi, posj);

	for(int i = 0; i < L;i++){
		for(int j = 0; j < W; j++){
			mat[i][j] = '.';
			visited[i][j] = false;
		}
	}
	for(auto el:loop_stored){
		mat[el.first][el.second] = '*';
	}

	int tot = 0;
	int Length = loop_stored.size();
	area = 0;
	int ctr = 0;
	for(int i = 0; i < Length; i++){
		auto pt1 = loop_stored[i%Length];
		auto pt2 = loop_stored[(i+1)%Length];
		pair<int,int> diff = {pt1.first-pt2.first,pt1.second-pt2.second};

		if(diff == make_pair(0,1) && mat[pt1.first+1][pt1.second]!='*' && !visited[pt1.first+1][pt1.second]) dfs2(pt1.first+1,pt1.second);
		
		if(diff == make_pair(0,-1) && mat[pt1.first-1][pt1.second]!='*' && !visited[pt1.first-1][pt1.second]) dfs2(pt1.first-1,pt1.second);
		
		if(diff == make_pair(-1,0) && mat[pt1.first][pt1.second+1]!='*' && !visited[pt1.first][pt1.second+1]) dfs2(pt1.first,pt1.second+1);
		
		if(diff == make_pair(1,0) && mat[pt1.first][pt1.second-1]!='*' && !visited[pt1.first][pt1.second-1]) dfs2(pt1.first,pt1.second-1);
		
	}
	cout<<"Loop area = "<<area<<endl;

	return 0;
}
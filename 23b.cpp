#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>


using namespace std;

const int MaxDist = 141*141+10;
char field[141][141];
int dist[141][141];
bool visited[141][141];
int largest_dist=0;

void dfs(int i, int j){
	if(i==1 && j == 1) {
		cout<<"at root"<<endl;
	}
	if(i==140 && j ==139) {
		if(largest_dist <dist[i][j]){
			largest_dist= max(largest_dist,dist[i][j]);
			cout<<"Longest hike so far "<<largest_dist<<endl;
		}
	}
	visited[i][j] = true;

	if(j+1<141 && (field[i][j]=='v'||field[i][j]=='>'||field[i][j]=='.')&&field[i][j+1]!='#'&&!visited[i][j+1]){
		int dist_temp =dist[i][j+1];
		dist[i][j+1] = max(dist[i][j+1], dist[i][j]+1);
		dfs(i,j+1);
		dist[i][j+1] = dist_temp;
	}
	if(j-1>=0 && (field[i][j]=='>'||field[i][j]=='v'||field[i][j]=='.')&&field[i][j-1]!='#'&&!visited[i][j-1]){
		int dist_temp = dist[i][j-1];
		dist[i][j-1] = max(dist[i][j-1], dist[i][j]+1);
		dfs(i,j-1);
		dist[i][j-1] = dist_temp;
	}
	if(i+1<141 && (field[i][j]=='>'||field[i][j]=='v'||field[i][j]=='.')&&field[i+1][j]!='#'&&!visited[i+1][j]){
		int dist_temp = dist[i+1][j];
		dist[i+1][j] = max(dist[i][j+1], dist[i][j]+1);
		dfs(i+1,j);
		dist[i+1][j] = dist_temp;
	}
	if(i-1>=0 && (field[i][j]=='>'||field[i][j]=='v'||field[i][j]=='.')&&field[i-1][j]!='#'&&!visited[i-1][j]){
		int dist_temp = dist[i-1][j];
		dist[i-1][j] = max(dist[i][j+1], dist[i][j]+1);
		dfs(i-1,j);
		dist[i-1][j] = dist_temp;
	}
	visited[i][j] = false;
	return;
}

int main(){

	ifstream file;
	file.open("input23.txt");

	for(int i = 0; i < 141; i++){
		for(int j = 0; j < 141; j++){
			file>>field[i][j];
			dist[i][j] = 0;
			visited[i][j] = false;
		}
	}
	for (int i = 0; i < 141; i++){
		for (int j = 0; j < 141; j++){
			dist[i][j] = -MaxDist;
		}
	}
    dist[0][1] = 0;
    
    dfs(0,1);
    cout<<"Longest hike = "<<largest_dist<<endl;
	return 0;
}
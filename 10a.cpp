#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>
#include <algorithm>

using namespace std;

char mat[140][140];
bool visited[140][140];

void dfs(int i, int j, int steps){
	
	if(mat[i][j] == 'S' && steps > 2){
		cout<<steps/2<<endl;
		return;
	}
	if(visited[i][j]) return;
	if(mat[i][j]!='S') visited[i][j] = true;
	if(i+1<140 &&  mat[i][j]=='|') dfs(i+1,j,steps+1);
	if(i-1>=0 &&  mat[i][j]=='|') dfs(i-1,j,steps+1);
	if(j+1<140 &&  mat[i][j]=='-') dfs(i,j+1,steps+1);
	if(j-1>=0 &&  mat[i][j]=='-') dfs(i,j-1,steps+1);
	
	if(i-1>=0 &&  mat[i][j]=='L') dfs(i-1,j,steps+1);
	if(j+1<140 &&  mat[i][j]=='L') dfs(i,j+1,steps+1);

	if(i+1<140 &&  mat[i][j]=='F') dfs(i+1,j,steps+1);
	if(j+1<140 &&  mat[i][j]=='F') dfs(i,j+1,steps+1);

	if(i+1<140 &&  mat[i][j]=='7') dfs(i+1,j,steps+1);
	if(j-1 >=0 &&  mat[i][j]=='7') dfs(i,j-1,steps+1);
	
	if(i-1>=0 &&  mat[i][j]=='J') dfs(i-1,j,steps+1);
	if(j-1 >=0 &&  mat[i][j]=='J') dfs(i,j-1,steps+1);
	

	return;
}


int main(){
	int L = 140;
	ifstream file;
	file.open("input10.txt");
	int posi, posj;
	for(int i = 0; i < 140;i++){
		for(int j = 0; j < 140; j++){
			visited[i][j] = false;
			file>>mat[i][j];
			if(mat[i][j]=='S'){
				posi = i;
				posj = j;
			}
		}
	}
	posj++;
	dfs(posi, posj,1);
	return 0;
}
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>
#include <algorithm>

using namespace std;


int main(){
	ifstream file;
	file.open("input9.txt");
	vector< vector<long long> > mat(22, vector<long long>(22));
	long long ans = 0;
	for(int i = 0; i < 200; i++){
		for(int j = 0; j < 21; j++){
			file>>mat[0][j];
		}
		for(int p =1; p < 21; p++){
			
			for(int q = 0; q < 21; q++){
					mat[p][q] = mat[p-1][q+1]-mat[p-1][q];
			}
		}
		
		for(int p =21; p >=1; p--){
			for(int q = 1; q < 22; q++){
					mat[p-1][q] = mat[p-1][q-1]+mat[p][q-1];
			}
		}
		ans += mat[0][21];

	}
	cout<<ans<<endl;
	return 0;
}
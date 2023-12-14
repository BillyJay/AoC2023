#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;


int main(){
	ifstream file;
	file.open("input14.txt");
	vector<string> field(100);
	for(int i = 0; i < 100; i++){
		file>>field[i];
		cout<<field[i]<<endl;
	}
	for(int i = 0; i < 100; i++){
		for(int j = 99; j >0; j--){
			for(int k =0; k < 100; k++){
				if (field[j-1][k]=='.' && field[j][k] =='O'){
					field[j][k] = '.';
					field[j-1][k] = 'O';
				}
			}
		}
	}
	long long ans = 0;
	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 100; j++){
			if(field[i][j]=='O') ans += (100-i);
		}
	}
	cout<<ans<<endl;
	return 0;
}
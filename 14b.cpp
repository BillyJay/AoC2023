#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

void cycle(vector<string> (&field)){
	for(int r = 0; r < 100; r++){
		for(int i = 99; i >0; i--){
			for(int j =0; j < 100; j++){
				if (field[i-1][j]=='.' && field[i][j] =='O'){
					field[i][j] = '.';
					field[i-1][j] = 'O';
				}
			}
		}
	}

	for(int r = 0; r < 100; r++){
		for(int i = 0; i < 100; i++){
			for(int j =99; j > 0; j--){
				if (field[i][j-1]=='.' && field[i][j] =='O'){
					field[i][j] = '.';
					field[i][j-1] = 'O';
				}
			}
		}
	}

	for(int r = 0; r < 100; r++){
		for(int i = 0; i < 99; i++){
			for(int j =0; j < 100; j++){
				if (field[i+1][j]=='.' && field[i][j] =='O'){
					field[i][j] = '.';
					field[i+1][j] = 'O';
				}
			}
		}
	}

	for(int r = 0; r < 100; r++){
		for(int i = 0; i < 100; i++){
			for(int j =0; j < 99; j++){
				if (field[i][j+1]=='.' && field[i][j] =='O'){
					field[i][j] = '.';
					field[i][j+1] = 'O';
				}
			}
		}
	}

	return;
}

void show(vector<string> (&field)){
	for(int i = 0; i < 100; i++){
		cout<<field[i]<<endl;
	}
}

long long get_diffs(vector<string> (&field), vector<string> (&field_cp)){
	int diffs = 0;
	for(int i = 0; i < 100; i++){
		for(int j =0; j < 100; j++){
			if(field[i][j] != field_cp[i][j]) diffs++;
		}
	}
	return diffs;
}


int main(){
	ifstream file;
	file.open("input14.txt");
	vector<string> field(100);
	for(int i = 0; i < 100; i++){
		file>>field[i];
	}
	long long target = 1000000000;
	for(int r = 0; r < 100; r++){
		cycle(field);
		target--;
	}
	//42 is period for my dataset
	auto field_cp = field;
	for(int r = 0; r < 42; r++){
		cycle(field);
	}
	assert(get_diffs(field, field_cp)==0);
	cout<<get_diffs(field, field_cp)<<endl;

	target %= 42;
	for(int r = 0; r < target; r++){
		cycle(field);
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

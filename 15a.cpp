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
	file.open("input15.txt");
	long long ans = 0;
	for(int i = 0; i < 4000; i++){
		string x;
		file>>x;
		long long val = 0;
		for(int j = 0; j < x.size(); j++){
			val = val + x[j];
			val = val*17 ;
			val %= 256;
		}
		// cout<<val<<endl;
		ans += val;
	}
	cout<<ans<<endl;
	return 0;
}

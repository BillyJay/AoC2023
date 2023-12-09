#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>


using namespace std;




int main(){
	vector<long long> t = {44,89,96,91};
	vector<long long> d = {277,1136,1890,1768};
	long long ans = 1;
	for(int i = 0; i < t.size(); i++){
		long long ok = 0;
		for(int j = 1; j < t[i]; j++){
			if(j*(t[i]-j) > d[i]) ok++;
		}
		ans *= ok;
	}
	cout<<ans<<endl;
	return 0;
}
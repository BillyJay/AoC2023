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
	file.open("input7.txt");
	vector<pair<string, long long> > five,four,full,three,two_pair,one_pair,high;
	
	
	map<char, char> mp;
	for(char c = '0'; c<='9';c++) mp[c] = c;
	mp['T']='A';
	mp['J']='B';
	mp['Q']='C';
	mp['K']='D';
	mp['A']='E';

	string x;
	long long y;
	long long tot = 0;
	for(int i = 0; i < 1000; i++){
		file>>x>>y;
		for(int i = 0; i < 5; i++){
			x[i] = mp[x[i]];
		}
		map<char, int> occ;
		vector<int> patt;
		for(int i = 0 ; i < 5; i++){
			occ[x[i]]++;
		}
		for(char c = '0'; c<='9';c++){
			if(occ[c]!=0){
				patt.push_back(occ[c]);
			}
		}
		for(char c = 'A'; c<='E';c++){
			if(occ[c]!=0){
				patt.push_back(occ[c]);
			}
		}
		sort(patt.begin(), patt.end());
		string patt_str = "";
		for(auto el : patt) patt_str = patt_str + to_string(el);
		if(patt_str == "11111"){
			high.push_back({x,y});
		}
		if(patt_str == "1112"){
			one_pair.push_back({x,y});
		}
		if(patt_str == "122"){
			two_pair.push_back({x,y});
		}
		if(patt_str == "113"){
			three.push_back({x,y});
		}
		if(patt_str == "23"){
			full.push_back({x,y});
		}
		if(patt_str == "14"){
			four.push_back({x,y});
		}
		if(patt_str == "5"){
			five.push_back({x,y});
		}
		sort(five.begin(),five.end());
		sort(four.begin(),four.end());
		sort(full.begin(),full.end());
		sort(three.begin(),three.end());
		sort(two_pair.begin(),two_pair.end());
		sort(one_pair.begin(),one_pair.end());
		sort(high.begin(),high.end());
		long long rank = 1;
		
		for(auto el : high){
			tot += rank * el.second;
			rank++;
		}
		for(auto el : one_pair){
			tot += rank * el.second;
			rank++;
		}
		for(auto el : two_pair){
			tot += rank * el.second;
			rank++;
		}
		for(auto el : three){
			tot += rank * el.second;
			rank++;
		}
		for(auto el : full){
			tot += rank * el.second;
			rank++;
		}
		for(auto el : four){
			tot += rank * el.second;
			rank++;
		}
		for(auto el : five){
			tot += rank * el.second;
			rank++;
		}
	}
	cout<<tot<<endl;
	return 0;
}









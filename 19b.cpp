#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>
#include <random>

using namespace std;

vector<pair<string, vector<string> > > all_cmds;
map<string, long long> name_to_idx;
long long start_idx;

vector<string> process(string cmd){
	vector<string> binTree(100);
	long long node = 1;
	string curr_cmd = "";
	for(long long i = 0; i < cmd.size(); i++){
		if(cmd[i]==','){
			for(long long j = 0; j < curr_cmd.size(); j++){
				if(curr_cmd[j] ==':'){
					string cond = curr_cmd.substr(0,j);
					string then=curr_cmd.substr(j+1,curr_cmd.size()-j-1);
					binTree[node] = cond;
					binTree[2*node] = then;
					node = 2*node+1;
				}
			}
			curr_cmd = "";
		}
		else curr_cmd = curr_cmd + cmd[i];
	}
	if(curr_cmd.size()!=0){
		binTree[node] = curr_cmd;
	}
	return binTree;
}


bool is_cond(string s){
	for(long long i = 0; i < s.size(); i++){
		if(s[i] == '>') return true;
		if(s[i] == '<') return true;
	}
	return false;
}

long long evaluate(vector<pair<long long, long long> > params, long long curr_idx, long long node){
	auto curr_cmd = all_cmds[curr_idx].second[node];
	
	if(curr_cmd =="A"){
		long long ans = 0;
		auto x0 = params[0].first; auto x1 = params[0].second; 
		auto m0 = params[1].first; auto m1 = params[1].second; 
		auto a0 = params[2].first; auto a1 = params[2].second; 
		auto s0 = params[3].first; auto s1 = params[3].second; 
		ans += (x1-x0+1)*(m1-m0+1)*(a1-a0+1)*(s1-s0+1);

		return ans;
	}
	if(curr_cmd == "R"){
		return 0;
	}
	if(!is_cond(curr_cmd)){
		curr_idx = name_to_idx[curr_cmd];
		return evaluate(params, curr_idx, 1);
	}
	else{
		long long nmb;
		char sgn;
		char letter;
		letter = curr_cmd[0];
		sgn = curr_cmd[1];
		nmb = stoi(curr_cmd.substr(2,curr_cmd.size()-2));
		map <char,long long> xmas_map= {{'x',0},{'m',1},{'a',2},{'s',3}};
		if(sgn =='>'){ //x,m,a or s > nmb    
			if(params[xmas_map[letter]].second <=nmb) return evaluate(params,curr_idx,2*node+1); //{x0,x1} and x1 <=nmb
			else{//
				
				if(nmb > params[xmas_map[letter]].first){//{x0,nmb}
					long long ans1,ans2;
					auto params_cp = params;
					params_cp[xmas_map[letter]].second = nmb;
					ans1 = evaluate(params_cp,curr_idx,2*node+1);
					params_cp = params;
					params_cp[xmas_map[letter]].first = nmb+1;
					ans2 = evaluate(params_cp,curr_idx,2*node);
					return ans1+ans2;
				}
				return evaluate(params,curr_idx,2*node);
			} 
		}
		if(sgn =='<'){ //x,m,a or s < nmb    
			if(params[xmas_map[letter]].first >=nmb) return evaluate(params,curr_idx,2*node+1); //{x0,x1} and x0 >= nmb
			else{//x0 < nmb
				
				if(nmb < params[xmas_map[letter]].second){//{nmb,x1}
					long long ans1,ans2;
					auto params_cp = params;
					params_cp[xmas_map[letter]].first = nmb;
					ans1 = evaluate(params_cp,curr_idx,2*node+1);
					params_cp = params;
					params_cp[xmas_map[letter]].second = nmb-1;
					ans2 = evaluate(params_cp,curr_idx,2*node);
					return ans1+ans2;
				} 
				return evaluate(params,curr_idx,2*node);
			} 
		}
	}
	return 0;
}

int main(){
	
	ifstream file;
	file.open("input19.txt");
	// file.open("input19test.txt");

	vector<string> names;
	
	
	
	vector<long long> x_lst, m_lst, a_lst, s_lst;
	for(long long i = 0; i < 591; i++){
	// for(long long i = 0; i < 11; i++){
		string nm;
		file>>nm;
		string cmd;
		file>>cmd;
		for(long long l = 0; l < cmd.size(); l++){
			if(cmd[l]=='x' && cmd[l+1]=='>'){
				string bnd = "";
				long long k = l+2;
				while(cmd[k]-'0'>=0 && cmd[k]-'0'<=9) {
					bnd = bnd + cmd[k];
					k++;
				}
			}
			if(cmd[l]=='x' && cmd[l+1]=='<'){
				string bnd = "";
				long long k = l+2;
				while(cmd[k]-'0'>=0 && cmd[k]-'0'<=9) {
					bnd = bnd + cmd[k];
					k++;
				}
			}
			if(cmd[l]=='m' && cmd[l+1]=='>'){
				string bnd = "";
				long long k = l+2;
				while(cmd[k]-'0'>=0 && cmd[k]-'0'<=9) {
					bnd = bnd + cmd[k];
					k++;
				}
			}
			if(cmd[l]=='m' && cmd[l+1]=='<'){
				string bnd = "";
				long long k = l+2;
				while(cmd[k]-'0'>=0 && cmd[k]-'0'<=9) {
					bnd = bnd + cmd[k];
					k++;
				}
			}
			if(cmd[l]=='a' && cmd[l+1]=='>'){
				string bnd = "";
				long long k = l+2;
				while(cmd[k]-'0'>=0 && cmd[k]-'0'<=9) {
					bnd = bnd + cmd[k];
					k++;
				}
			}
			if(cmd[l]=='a' && cmd[l+1]=='<'){
				string bnd = "";
				long long k = l+2;
				while(cmd[k]-'0'>=0 && cmd[k]-'0'<=9) {
					bnd = bnd + cmd[k];
					k++;
				}
			}
			if(cmd[l]=='s' && cmd[l+1]=='>'){
				string bnd = "";
				long long k = l+2;
				while(cmd[k]-'0'>=0 && cmd[k]-'0'<=9) {
					bnd = bnd + cmd[k];
					k++;
				}
			}
			if(cmd[l]=='s' && cmd[l+1]=='<'){
				string bnd = "";
				long long k = l+2;
				while(cmd[k]-'0'>=0 && cmd[k]-'0'<=9) {
					bnd = bnd + cmd[k];
					k++;
				}
			}
		}
		auto binTree = process(cmd);
		all_cmds.push_back({nm, binTree});
		name_to_idx[nm] = all_cmds.size()-1;
		if(nm=="in"){
			start_idx = name_to_idx["in"];
		}
	}
	for(long long upd = 0; upd < 4; upd++){
		for(long long idx = 0; idx < all_cmds.size(); idx++){
			auto el = all_cmds[idx];
			auto binTree= el.second;
			for(long long i = 1; i < binTree.size(); i++){
				if(binTree[2*i]=="R" && binTree[2*i+1]=="R" && binTree[i]!="R") {
					all_cmds[idx].second[i] ="R";
				}
			}
		}
		for(long long idx = 0; idx < all_cmds.size(); idx++){
			auto el = all_cmds[idx];
			auto binTree= el.second;
			for(long long i = 1; i < binTree.size(); i++){
				if(binTree[2*i]=="A" && binTree[2*i+1]=="A" && binTree[i]!="A") {
					all_cmds[idx].second[i] ="A";
				}
			}
		}
	
	
	}

	long long tot;
	tot = evaluate({{1,4000},{1,4000},{1,4000},{1,4000}},start_idx,1);
	cout<<tot<<endl;
	return 0;
}
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>


using namespace std;


vector<string> process(string cmd){
	vector<string> binTree(100);
	int node = 1;
	string curr_cmd = "";
	for(int i = 0; i < cmd.size(); i++){
		if(cmd[i]==','){
			for(int j = 0; j < curr_cmd.size(); j++){
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
	for(int i = 0; i < s.size(); i++){
		if(s[i] == '>') return true;
		if(s[i] == '<') return true;
	}
	return false;
}

int main(){
	ifstream file;
	file.open("input19.txt");
	vector<string> names;
	vector<pair<string, vector<string> > > all_cmds;
	map<string, int> name_to_idx;
	int start_idx;
	for(int i = 0; i < 591; i++){
		string nm;
		file>>nm;
		string cmd;
		// cout<<cmd<<endl;
		file>>cmd;
		auto binTree = process(cmd);
		all_cmds.push_back({nm, binTree});
		name_to_idx[nm] = all_cmds.size()-1;
		if(nm=="in"){
			start_idx = name_to_idx["in"];
		}
	}
	//simplify binary tree
	for(int upd = 0; upd < 4; upd++){
		int changes = 0;
		for(int idx = 0; idx < all_cmds.size(); idx++){
			auto el = all_cmds[idx];
			auto binTree= el.second;
			for(int i = 1; i < binTree.size(); i++){
				if(binTree[2*i]=="R" && binTree[2*i+1]=="R" && binTree[i]!="R") {
					changes++;
					all_cmds[idx].second[i] ="R";
				}
			}
		}
		for(int idx = 0; idx < all_cmds.size(); idx++){
			auto el = all_cmds[idx];
			auto binTree= el.second;
			for(int i = 1; i < binTree.size(); i++){
				if(binTree[2*i]=="A" && binTree[2*i+1]=="A" && binTree[i]!="A") {
					changes++;
					all_cmds[idx].second[i] ="A";
				}
			}
		}
		cout<<"update changed "<<changes<<" entries"<<endl;

	}
	long long ans = 0;
	for(int i = 1183; i<=1382;i++){
		int x,m,a,s;
		file>>x>>m>>a>>s;
		int node = 1;
		int curr_idx = start_idx;
		auto curr_cmd = all_cmds[curr_idx].second[node];
		while(true){
			if(curr_cmd =="A"){
				ans+= x+m+a+s;
				break;
			}
			if(curr_cmd == "R"){
				break;
			}
			if(!is_cond(curr_cmd)){
				node = 1;
				curr_idx = name_to_idx[curr_cmd];
				curr_cmd = all_cmds[name_to_idx[curr_cmd]].second[1];
			}
			else{

				int nmb;
				char sgn;
				char letter;
				letter = curr_cmd[0];
				sgn = curr_cmd[1];
				nmb = stoi(curr_cmd.substr(2,curr_cmd.size()-2));
				map <char,int> xmas_map= {{'x',x},{'m',m},{'a',a},{'s',s}};
				bool eval;
				if(sgn =='>'){

					if(xmas_map[letter] > nmb) eval = true;
					else eval = false;

				}
				if(sgn =='<'){
					if(xmas_map[letter] < nmb) eval = true;
					else eval = false;
				}
				if(eval == true) node = 2*node;
				else node = 2*node+1;
				curr_cmd = all_cmds[curr_idx].second[node];
			}

		}
	}
	cout<<ans<<endl;
	return 0;
}
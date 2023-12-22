#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>
#include <random>

using namespace std;


map<string, int> nm_to_idx;
map< string, bool >flip_flop_states;
map<string, map<string, bool> > conjs;
map<string, vector<string> > receiver_devices;
vector<vector<string> >	stack;
long long lows = 0;
long long highs = 0;

void send_signal(string sender, string signal, vector<string> receivers){
	for(auto el : receivers){
		if(el=="rx" && signal == "low") {
			cout<<"found";
			cin.ignore();
		}
		if(signal == "low") lows++;
		else highs++;
		if (el[0]=='%'){
			if (signal == "low"){
				if(flip_flop_states[el]==0){
					flip_flop_states[el] = 1;
					stack.push_back({el,"high"});
				}
				else{
					flip_flop_states[el] = 0;
					stack.push_back({el,"low"});
				}
			}
		}
		if (el[0]=='&'){
			if(signal=="low") {
				conjs[el][sender] = 0;
			}
			else {
				conjs[el][sender] = 1;
			}
			string output_signal = "low";
			for(auto ff : conjs[el]){
				if(ff.second==0) output_signal = "high";
			}
			stack.push_back({el,output_signal});
		}
	}
}

int main(){
	ifstream file;
	file.open("input20.txt");
	// file.open("input20test.txt");
	string x;
	vector<vector< string> > cmds;
	while(getline(file,x)){
		vector<string> cmd;
		while(x.size()!=0){
			int pos = 0; 
			string part = "";
			while(pos < x.size() && x[pos]!=' '){
				part = part + x[pos];
				pos++;
			}

			cmd.push_back(part);
			if(pos == x.size()) break;
			else x = x.substr(pos+1);
		}
		cmds.push_back(cmd);
	}
	vector<string> flip_flop_names, conj_names;
	for(int i =0 ; i < cmds.size();i++){
		if(cmds[i][0][0]=='%'){
			flip_flop_names.push_back(cmds[i][0].substr(1));
		}
		if(cmds[i][0][0]=='&'){
			conj_names.push_back(cmds[i][0].substr(1));
		}
	}

	for(int i =0 ; i < cmds.size();i++){
		for(int j =1 ; j < cmds[i].size();j++){
			if(find(flip_flop_names.begin(), flip_flop_names.end(), cmds[i][j])!=flip_flop_names.end()){
				cmds[i][j] = '%'+cmds[i][j];
			}
			if(find(conj_names.begin(), conj_names.end(), cmds[i][j])!=conj_names.end()){
				cmds[i][j] = '&'+cmds[i][j];
			}
		}
	}

	for(auto el : flip_flop_names){
		flip_flop_states[el] = 0;
	}
	
	for(auto line : cmds){
		if(line[0][0]!='%') continue;
		for(int i = 1; i < line.size(); i++){
			if(line[i][0]=='&'){
				conjs[line[i]][line[0]] = 0;
			}
		}
	}

	
	for(auto line : cmds){
		for(int i = 1; i < line.size(); i++){
			receiver_devices[line[0]].push_back(line[i]);
		}
	}
	for(int rep = 0; rep < 1000; rep++){
		lows++;
		stack.push_back({"broadcaster", "low"});
		while(stack.size()!=0){
			vector<string> top_element = stack[0];
			send_signal(top_element[0],top_element[1],receiver_devices[top_element[0]]);
			stack.erase(stack.begin());
		}
	}
	cout<<lows<<" "<<highs<<endl;
	cout<<lows*highs<<endl;
	return 0;
	
}
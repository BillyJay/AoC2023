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
vector<vector<string> >	queue;
long long lows = 0;
long long highs = 0;

long long rep;
vector<int> rn_seq, vf_seq, mk_seq, dh_seq;

void send_signal(string sender, string signal, vector<string> receivers){
	if(sender=="&rn" && signal == "high") {
			rn_seq.push_back(rep);
	}
	if(sender=="&vf" && signal == "high") {
			vf_seq.push_back(rep);
	}
	if(sender=="&mk" && signal == "high") {
			mk_seq.push_back(rep);
	}
	if(sender=="&dh" && signal == "high") {
			dh_seq.push_back(rep);
	}
	for(auto el : receivers){
		
		if(signal == "low") lows++;
		else highs++;
		if (el[0]=='%'){
			if (signal == "low"){
				if(flip_flop_states[el]==0){
					flip_flop_states[el] = 1;
					queue.push_back({el,"high"});
				}
				else{
					flip_flop_states[el] = 0;
					queue.push_back({el,"low"});
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
			queue.push_back({el,output_signal});
		}
	}
}

long long convert_to_dec(map< string, bool > ff_states){
	long long ans = 0;
	long long base = 1;
	for(auto el : ff_states){
		ans+=el.second*base;
		base*=2;
	}
	return ans;
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
	
	// set the input signals of all conjunctions to low
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

	for(rep = 1; rep < 100000; rep++){
		lows++;
		queue.push_back({"broadcaster", "low"});
		while(queue.size()!=0){
			vector<string> top_element = queue[0];
			send_signal(top_element[0],top_element[1],receiver_devices[top_element[0]]);
			queue.erase(queue.begin());
		}
	}
	//rx is soured by jz; jz becomes low for the first time when mk, vf, rn and dh are all high for the first time
	//the sequences mk_seq etc. store the val of the repetition, rep, when they were on. These sequences turn out to be linear
	cout<<mk_seq[0]<<" "<<mk_seq[1]<<" "<<mk_seq[2]<<" ..."<<endl;
	cout<<vf_seq[0]<<" "<<vf_seq[1]<<" "<<vf_seq[2]<<" ..."<<endl;
	cout<<rn_seq[0]<<" "<<rn_seq[1]<<" "<<rn_seq[2]<<" ..."<<endl;
	cout<<dh_seq[0]<<" "<<dh_seq[1]<<" "<<dh_seq[2]<<" ..."<<endl;
	
	//since the _seq[0]'s are all mutually prime, the first time when they are simultaneously high is at their product:
	long long ans = mk_seq[0]*vf_seq[0]*rn_seq[0]*dh_seq[0];
	cout<<ans<<endl;
	return 0;
}
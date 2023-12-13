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
	file.open("input13.txt");
	// file.open("input13test.txt");
	int ctr = 0;
	vector<vector<string> > field(100);
	for(int i = 0; i < 1354; i++){
	// for(int i = 0; i < 15; i++){
		string s;
		file>>s;
		if(s!="X"){
			field[ctr].push_back(s);
		}
		else ctr++;

	}
	long long tot_h, tot_v;
	tot_v = 0;
	tot_h = 0;

	for(int i = 0; i < 100; i++){
	// for(int i = 0; i < 2; i++){
		int dim_i = field[i].size();
		int dim_j = field[i][0].size();
		auto field_store = field[i];


		//Old line

		long long vert=-1;
		long long hor=-1;
		for(int v = 1; v < 2*dim_j-2; v+=2){
			bool ok = true;
			for(int a = 0; a < dim_i; a++){
				for(int b = 0; b < dim_j; b++){
					if(v-b < 0 || v-b >= dim_j) continue;
					if(field[i][a][b] != field[i][a][v-b]) {
						ok = false;
						break;
					}
				}
				if(!ok) break;
			}
			if(ok){
				vert = v;
				break;
			}
		}
		for(int h = 1; h < 2*dim_i-2; h+=2){
			bool ok = true;
			for(int a = 0; a < dim_i; a++){
				for(int b = 0; b < dim_j; b++){
					if(h-a < 0 || h-a >= dim_i) continue;
					if(field[i][a][b] != field[i][h-a][b]) {
						ok = false;
						break;
					}
				}
				if(!ok) break;
			}
			if(ok){
				hor = h;
				break;
			}
		}

		
		auto hor_old = hor;
		auto ver_old = vert;

		bool found = false;
		for(int sm_i = 0; sm_i < dim_i; sm_i++){
			if(found) break;
			for(int sm_j = 0; sm_j < dim_j; sm_j++){
				if(found) break;
				field[i] = field_store;
				if(field[i][sm_i][sm_j] =='.') field[i][sm_i][sm_j] ='#';
				else field[i][sm_i][sm_j]='.';
				long long vert=-1;
				long long hor=-1;
				for(int v = 1; v < 2*dim_j-2; v+=2){
					bool ok = true;
					for(int a = 0; a < dim_i; a++){
						for(int b = 0; b < dim_j; b++){
							if(v-b < 0 || v-b >= dim_j) continue;
							if(field[i][a][b] != field[i][a][v-b]) {
								ok = false;
								break;
							}
						}
						if(!ok) break;
					}
					if(ok && v!=ver_old){
						vert = v;
						break;
					}
				}
				for(int h = 1; h < 2*dim_i-2; h+=2){
					bool ok = true;
					for(int a = 0; a < dim_i; a++){
						for(int b = 0; b < dim_j; b++){
							if(h-a < 0 || h-a >= dim_i) continue;
							if(field[i][a][b] != field[i][h-a][b]) {
								ok = false;
								break;
							}
						}
						if(!ok) break;
					}
					if(ok && h!=hor_old){
						hor = h;
						break;
					}
				}
				if((vert!=-1 || hor != -1) ){

					if(hor == hor_old) hor = -1;
					if(vert == ver_old) vert = -1;
					if(hor!=-1 ) tot_h+=hor/2+1;
					if(vert!=-1 ) tot_v+=vert/2+1;


					if(hor!=-1 || vert!=-1) {
						found = true;
					}
				}
			}
		}
	}
	cout<<100*tot_h + tot_v<<endl;

	return 0;
}
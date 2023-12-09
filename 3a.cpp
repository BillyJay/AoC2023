#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>
#include <vector>
#include <numeric>


using namespace std;

bool isSymb(char x){
	bool ans =  true;
	if(x >= '0' && x <= '9') ans = false;
	if (x=='.') ans = false;
	return ans;
}

int main(){
	ifstream file;
	file.open("input3.txt");
	string x;
	const int dim = 140;
	char mat[dim][dim];

	for(int i = 0; i < dim; i++){
		getline(file,x);
		for(int j = 0; j < x.size(); j++){
			mat[i][j]=x[j];
		}

	}

	
	vector<long long> n_list;
	for(int i = 0; i < dim;){
		for(int j = 0; j < dim; ){
			if(mat[i][j]>'9' || mat[i][j] < '0') {
				j++;
				continue;
			}
			string n;
			int j_start = j;
			while(j<dim && mat[i][j]<='9' && mat[i][j]>='0'){
				n = n + mat[i][j];
				j++;
			}
			if(j_start!=j) {
				bool ok = false;
				for(int k = j_start; k < j; k++){
					if(k-1>=0 && isSymb(mat[i][k-1])) ok = true;
					if(k+1 < dim && isSymb(mat[i][k+1])) ok = true;
					if(k+1 < dim && i+1 < dim && isSymb(mat[i+1][k+1])) ok = true;
					if(k+1 < dim && i-1 >=0 && isSymb(mat[i-1][k+1])) ok = true;
					if(k-1 >= 0 && i+1 < dim && isSymb(mat[i+1][k-1])) ok = true;
					if(k-1 >= 0 && i-1 >=0  && isSymb(mat[i-1][k-1])) ok = true;
					if(i-1 >=0  && isSymb(mat[i-1][k])) ok = true;
					if(i+1 < dim && isSymb(mat[i+1][k])) ok = true;
				}
				if(ok) n_list.push_back(stoi(n));
			}
			if(j+1 < dim) j++;

		}
		i++;
	}

	cout<<accumulate(n_list.begin(), n_list.end(),0)<<endl;

	return 0;
}
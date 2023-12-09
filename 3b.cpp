#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>


using namespace std;

bool isStar(char x){
	return (x=='*');
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

	vector<pair<long long, pair<int, int> > > n_list;
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
					if(k-1>=0 && isStar(mat[i][k-1])) n_list.push_back({stoi(n),{i,k-1}});
					if(k+1 < dim && isStar(mat[i][k+1])) n_list.push_back({stoi(n),{i,k+1}});
					if(k+1 < dim && i+1 < dim && isStar(mat[i+1][k+1])) n_list.push_back({stoi(n),{i+1,k+1}});
					if(k+1 < dim && i-1 >=0 && isStar(mat[i-1][k+1])) n_list.push_back({stoi(n),{i-1,k+1}});
					if(k-1 >= 0 && i+1 < dim && isStar(mat[i+1][k-1])) n_list.push_back({stoi(n),{i+1,k-1}});
					if(k-1 >= 0 && i-1 >=0  && isStar(mat[i-1][k-1])) n_list.push_back({stoi(n),{i-1,k-1}});
					if(i-1 >=0  && isStar(mat[i-1][k])) n_list.push_back({stoi(n),{i-1,k}});
					if(i+1 < dim && isStar(mat[i+1][k])) n_list.push_back({stoi(n),{i+1,k}});
				}
			}
			if(j+1 < dim) j++;

		}
		i++;
	}
	vector<pair<long long, pair<int, int> > > new_list;

	for(int i = 0; i < n_list.size(); i++){
		auto el = n_list[i];
		if(find(new_list.begin(), new_list.end(), el)==new_list.end()){
			new_list.push_back(el);
      	}
	}


	long long sum = 0;
	for(auto el1 : new_list){
		for(auto el2 : new_list){
			if(el1==el2) continue;
			if(el1.second == el2.second) {
				sum+= (el1.first * el2.first);
			}
		}
	}
	sum /= 2;
	cout<<sum<<endl;

	return 0;
}










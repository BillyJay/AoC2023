#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>
#include <omp.h>

using namespace std;




int main(){
	
	ifstream file;
	file.open("input5.txt");
	string x;
	vector<long long> seeds;
	vector<int> allsizes = {20,44,22,40,43,34,45,34};
	for(int i = 0; i <allsizes[0]/2;i++){
		long long seed;
		long long length;
		file>>seed;
		file>>length;
		for(int i = 0; i < length; i++)
			seeds.push_back(seed+i);
	}


	vector<vector<long long> > seed_soil(allsizes[1]);
	vector<vector<long long> > soil_fert(allsizes[2]);
	vector<vector<long long> > fert_water(allsizes[3]);
	vector<vector<long long> > water_light(allsizes[4]);
	vector<vector<long long> > light_temp(allsizes[5]);
	vector<vector<long long> > temp_humid(allsizes[6]);
	vector<vector<long long> > humid_loc(allsizes[7]);

	for(int i = 0; i < allsizes[1];i++){
		long long a, b, c;
		file>>a>>b>>c;
		seed_soil[i].push_back(a);
		seed_soil[i].push_back(b);
		seed_soil[i].push_back(c);
	}
	for(int i = 0; i < allsizes[2];i++){
		long long a, b, c;
		file>>a>>b>>c;
		soil_fert[i].push_back(a);
		soil_fert[i].push_back(b);
		soil_fert[i].push_back(c);
	}
	for(int i = 0; i < allsizes[3];i++){
		long long a, b, c;
		file>>a>>b>>c;
		fert_water[i].push_back(a);
		fert_water[i].push_back(b);
		fert_water[i].push_back(c);
	}
	for(int i = 0; i < allsizes[4];i++){
		long long a, b, c;
		file>>a>>b>>c;
		water_light[i].push_back(a);
		water_light[i].push_back(b);
		water_light[i].push_back(c);
	}
	for(int i = 0; i < allsizes[5];i++){
		long long a, b, c;
		file>>a>>b>>c;
		light_temp[i].push_back(a);
		light_temp[i].push_back(b);
		light_temp[i].push_back(c);
	}
	for(int i = 0; i < allsizes[6];i++){
		long long a, b, c;
		file>>a>>b>>c;
		temp_humid[i].push_back(a);
		temp_humid[i].push_back(b);
		temp_humid[i].push_back(c);
	}
	for(int i = 0; i < allsizes[7];i++){
		long long a, b, c;
		file>>a>>b>>c;
		humid_loc[i].push_back(a);
		humid_loc[i].push_back(b);
		humid_loc[i].push_back(c);
	}
	vector<bool> mapped(seeds.size());
	


	for(int i =0; i < seeds.size(); i++){
		mapped[i] = false;
	}
	cout<<"mapping done"<<endl;


	omp_set_dynamic(0); 
	omp_set_num_threads(20);
	#pragma omp parallel for
	for(int i = 0; i < seeds.size(); i++){
		for(auto el2 : seed_soil){
			auto el1 = seeds[i];
			long long a,b,c;
			a = el2[0];b=el2[1];c=el2[2];
			if(el1 >= b && el1 < b+c && !mapped[i]){
				seeds[i] = a + (el1-b);
				mapped[i] = true;
			}
		}
		
	}
	cout<<"seed_soil done"<<endl;
	

	#pragma omp parallel for
	for(int i =0; i < seeds.size(); i++){
		mapped[i] = false;
	}
	#pragma omp parallel for
	for(int i = 0; i < seeds.size(); i++){
		for(auto el2 : soil_fert){
			auto el1 = seeds[i];
			long long a,b,c;
			a = el2[0];b=el2[1];c=el2[2];
			if(el1 >= b && el1 < b+c && !mapped[i]){
				seeds[i] = a + (el1-b);
				mapped[i] = true;
			}
		}
		
	}
	cout<<"soil_fert done"<<endl;
	#pragma omp parallel for
	for(int i =0; i < seeds.size(); i++){
		mapped[i] = false;
	}
	#pragma omp parallel for
	for(int i = 0; i < seeds.size(); i++){
		for(auto el2 : fert_water){
			auto el1 = seeds[i];
			long long a,b,c;
			a = el2[0];b=el2[1];c=el2[2];
			if(el1 >= b && el1 < b+c && !mapped[i]){
				seeds[i] = a + (el1-b);
				mapped[i] = true;
			}
		}
		
	}
	cout<<"fert_water done"<<endl;
	#pragma omp parallel for
	for(int i =0; i < seeds.size(); i++){
		mapped[i] = false;
	}
	#pragma omp parallel for
	for(int i = 0; i < seeds.size(); i++){
		for(auto el2 : water_light){
			auto el1 = seeds[i];
			long long a,b,c;
			a = el2[0];b=el2[1];c=el2[2];
			if(el1 >= b && el1 < b+c && !mapped[i]){
				seeds[i] = a + (el1-b);
				mapped[i] = true;
			}
		}
		
	}
	cout<<"water_light done"<<endl;
	#pragma omp parallel for
	for(int i =0; i < seeds.size(); i++){
		mapped[i] = false;
	}
	#pragma omp parallel for
	for(int i = 0; i < seeds.size(); i++){
		for(auto el2 : light_temp){
			auto el1 = seeds[i];
			long long a,b,c;
			a = el2[0];b=el2[1];c=el2[2];
			if(el1 >= b && el1 < b+c && !mapped[i]){
				seeds[i] = a + (el1-b);
				mapped[i] = true;
			}
		}
		
	}
	cout<<"light_temp done"<<endl;
	#pragma omp parallel for
	for(int i =0; i < seeds.size(); i++){
		mapped[i] = false;
	}
	#pragma omp parallel for
	for(int i = 0; i < seeds.size(); i++){
		for(auto el2 : temp_humid){
			auto el1 = seeds[i];
			long long a,b,c;
			a = el2[0];b=el2[1];c=el2[2];
			if(el1 >= b && el1 < b+c && !mapped[i]){
				seeds[i] = a + (el1-b);
				mapped[i] = true;
			}
		}
		
	}
	cout<<"temp_humid done"<<endl;
	#pragma omp parallel for
	for(int i =0; i < seeds.size(); i++){
		mapped[i] = false;
	}
	#pragma omp parallel for
	for(int i = 0; i < seeds.size(); i++){
		for(auto el2 : humid_loc){
			auto el1 = seeds[i];
			long long a,b,c;
			a = el2[0];b=el2[1];c=el2[2];
			if(el1 >= b && el1 < b+c && !mapped[i]){
				seeds[i] = a + (el1-b);
				mapped[i] = true;
			}
		}
		
	}
	cout<<"humid_loc done"<<endl;
	cout<<*min_element(seeds.begin(), seeds.end())<<endl;
	return 0;
}


//g++ -std=c++17 -Xclang -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include -lomp -Ofast 5b.cpp






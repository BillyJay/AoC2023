#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>
#include <random>

using namespace std;


int main(){
	double eps = 1e-7;
	ifstream file;
	file.open("input24.txt");
	// file.open("input24test.txt");
	vector<long long > x(300),y(300),z(300),u(300),v(300),w(300);
	// int file_n = 5;
	int file_n = 300;
	for(int i = 0; i < file_n; i++){
		file>>x[i]>>y[i]>>z[i]>>u[i]>>v[i]>>w[i];
	}
	long long ans = 0;
	double test_min = 200000000000000.0;
	double test_max = 400000000000000.0;

	for(int i = 0; i < file_n; i++){
		for(int j = i+1; j < file_n; j++){
			assert(u[i]!=u[j] || v[i]!=v[j]);
			double alpha, beta;
			alpha = (double) (y[i]*u[i] - v[i] * x[i]);
			alpha /= ((double) u[i]);
			beta = (double) (y[j]*u[j] - v[j] * x[j]);
			beta /= ((double) u[j]);
			double gamma;
			gamma = ((double) v[j])/((double) u[j]) - ((double) v[i])/((double) u[i]);
			if(abs(gamma)<eps) continue;
			double pos_x  = (alpha-beta)/gamma;
			double pos_y = y[i] + ((double) v[i]) / ((double) u[i])  * (pos_x - ((double) x[i]));
			double t1 = (pos_x - ((double) x[i]))/((double) u[i]);
			double t2 = (pos_x - ((double) x[j]))/((double) u[j]);
			if (t1 < 0.0) continue;
			if (t2 < 0.0) continue;
			if(test_min<= pos_x && pos_x <= test_max  && test_min <= pos_y && pos_y <= test_max) ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}
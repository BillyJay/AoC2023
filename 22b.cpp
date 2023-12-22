#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>
#include <random>

using namespace std;

vector<long long> lower(bool volume[25][25][500], vector<long long> coord){
	if(min(coord[2],coord[5])==1) return coord;
	bool ok_to_lower = true;
	for(int x = min(coord[0], coord[3]); x <= max(coord[0], coord[3]); x++){
		for(int y = min(coord[1], coord[4]); y <= max(coord[1], coord[4]); y++){
			if(volume[x][y][min(coord[2], coord[5])-1]==true) {
				ok_to_lower = false;
				break;
			}
			if(!ok_to_lower) break;
		}
		if(!ok_to_lower) break;
	}
	if(ok_to_lower){
		coord[2]--;coord[5]--;
		for(int x = min(coord[0], coord[3]); x <= max(coord[0], coord[3]); x++){
			for(int y = min(coord[1], coord[4]); y <= max(coord[1], coord[4]); y++){
				for(int z = min(coord[2], coord[5]); z <= max(coord[2], coord[5]); z++){
					volume[x][y][z+1] = false;
					volume[x][y][z] = true;
				}
			}
		}
		return lower(volume,coord);
	}
	else return coord;
}



int main(){
	ifstream file;
	file.open("input22.txt");
	// file.open("input22test.txt");
	vector<vector<long long> > coords;
	map<long long, vector<int> > min_height_to_idx;
	for(int i = 0; i < 1497; i++){
	// for(int i = 0; i < 7; i++){
		long long a,b,c,x,y,z;
		file>>a>>b>>c>>x>>y>>z;
		coords.push_back({a,b,c,x,y,z});
		min_height_to_idx[min(c,z)].push_back(i);
	}
	vector<vector<long long> > coords_orig = coords;


	bool volume[25][25][500];
	memset(volume, false, sizeof(volume));
	for(int i = 0; i < 25;i++){
		for(int j = 0; j < 25;j++){
					volume[i][j][0] = true;
		}
	}


	for(int i = 0; i < coords.size(); i++){
		// //mark blocks in volume
		for(int x = min(coords[i][0], coords[i][3]); x <= max(coords[i][0], coords[i][3]); x++){
			for(int y = min(coords[i][1], coords[i][4]); y <= max(coords[i][1], coords[i][4]); y++){
				for(int z = min(coords[i][2], coords[i][5]); z <= max(coords[i][2], coords[i][5]); z++){
					volume[x][y][z] = true;
				}
			}
		}
	}


	for(int height = 1; height < 500; height++){
		vector<int > idxs = min_height_to_idx[height];
		for(int i = 0; i < idxs.size(); i++){
			vector<long long> coords_before = coords[idxs[i]];
			coords[idxs[i]] = lower(volume,coords[idxs[i]]);

			// //mark it in volume
			for(int x = min(coords_before[0], coords_before[3]); x <= max(coords_before[0], coords_before[3]); x++){
				for(int y = min(coords_before[1], coords_before[4]); y <= max(coords_before[1], coords_before[4]); y++){
					for(int z = min(coords_before[2], coords_before[5]); z <= max(coords_before[2], coords_before[5]); z++){
						volume[x][y][z] = false;
					}
				}
			}
			vector<long long> block = coords[idxs[i]];
			for(int x = min(block[0], block[3]); x <= max(block[0], block[3]); x++){
				for(int y = min(block[1], block[4]); y <= max(block[1], block[4]); y++){
					for(int z = min(block[2], block[5]); z <= max(block[2], block[5]); z++){
						volume[x][y][z] = true;
					}
				}
			}
		}
	}

	assert(coords_orig != coords);
	int fallen = 0;

	vector<vector<long long> > coords_after_fall_orig = coords;
	int ans = 0;
	for(int i_skip = 0; i_skip < coords_orig.size(); i_skip++){
		coords = coords_orig;
		coords.erase(coords.begin()+i_skip);
		min_height_to_idx.clear();
		for(int j = 0; j < coords.size(); j++){
			vector<long long> el = coords[j];
			min_height_to_idx[min(el[2],el[5])].push_back(j);
		}

		bool volume[25][25][500];
		for(int i = 0; i < 25;i++){
			for(int j = 0; j < 25;j++){
				for(int k = 0; k < 500;k++){
					volume[i][j][k] = false;
					if(k==0) volume[i][j][k] = true;
				}
			}
		}

		for(int i = 0; i < coords.size(); i++){
			// //mark blocks in volume
			for(int x = min(coords[i][0], coords[i][3]); x <= max(coords[i][0], coords[i][3]); x++){
				for(int y = min(coords[i][1], coords[i][4]); y <= max(coords[i][1], coords[i][4]); y++){
					for(int z = min(coords[i][2], coords[i][5]); z <= max(coords[i][2], coords[i][5]); z++){
						volume[x][y][z] = true;
					}
				}
			}
		}


		for(int height = 1; height < 500; height++){
			vector<int > idxs = min_height_to_idx[height];
			for(int i = 0; i < idxs.size(); i++){
				coords[idxs[i]] = lower(volume,coords[idxs[i]]);
			}
		}
		

		for(int check_idx = 0; check_idx < i_skip; check_idx++){
			if(coords[check_idx] != coords_after_fall_orig[check_idx]) {
				fallen++;
			}
		}
		for(int check_idx = i_skip+1; check_idx < coords.size()+1; check_idx++){
			if(coords[check_idx-1] != coords_after_fall_orig[check_idx]) fallen++;
		}
		cout<<i_skip<<" "<<fallen<<endl;
	}
	cout<<fallen<<endl;

	return 0;
}	
#include <iostream>
#include <unordered_map>
#include <vector>

#include <chrono>
using namespace std::chrono;
#define f0(i,r) for(int i=0;i<r;i++)
 
using namespace std;
string test="\n\
 abcdefghijkl\n\
a111000111111\n\
b000001000001\n\
c000000000001\n\
d100000000010\n\
e011000010000\n\
f110001010011\n\
g000000100000\n\
h101100000000\n\
i100100100110\n\
j000100100101\n\
k100000000001\n\
l100100100111\n\
";
const int CONST = 200000000;
vector<string> split(string ik, char nl='\n'){
	string hi="";
	vector<string> ret;
	for (char i:ik){
		if (i==nl){
			ret.push_back(hi);
			hi="";
		}
		else{
			hi+=i;
		}
	}
	ret.push_back(hi);
	return ret;
}
vector<string> getgrid(){
	vector<string> ret;
	for (string i:split(test)){
		if (i.size()&&i[0]>=('a')&&i[0]<=('l')){
			ret.push_back(i.substr(1,100000));
		}
	}
	return ret;
}
vector<int> alive;
const array<int, 8> modify2 = {-17501,-17500,-17499,-1,1,17499,17500,17501};
vector<int> consider(400000000);
vector<int> toconsider;
int onegameloop(){
	toconsider.clear();
  //toconsider.reserve(9 * alive.size());

  for (int i:alive){
    consider[i]+=100;
    if (consider[i]==100){
      toconsider.push_back(i);
    }
    for (int j:modify2){
      consider[i+j]+=1;
			if (consider[i+j]==1){
				toconsider.push_back(i+j);
			}
		}
	}
	alive.clear();
  f0(ii, toconsider.size()) {
    //for (auto i:toconsider){}

    int i = toconsider[ii];

    int alneighbors=consider[i];
		consider[i]=0;
    if (alneighbors>99){
        alneighbors-=100;
        //alive
        if (2<=alneighbors&&alneighbors<=3){
          alive.push_back(i);
        }
    } else {
              //dead
      if (alneighbors==3){
          alive.push_back(i);
      }
    }
  }
  return alive.size();
}

int main() {
	vector<string> grid=getgrid();
	for (int y=0;y<12;y++){
		for (int x=0;x<12;x++){
			if (grid[y][x]=='1'){
				alive.push_back(y*17500+x+CONST);
			}
		}
	}
	auto start = high_resolution_clock::now();
	int ans=0;
	for (int i=0;i<8640;i++){
		ans+=onegameloop();
		if (i%100==0){
			cout<<i<<"\n";
		}
	}
	cout<<ans<<"\n";
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << duration.count() << endl;
	
}

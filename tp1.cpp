#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

/* DECLARATIONS FONCTION */

vector<double> q1(int n);
void q2(vector<double> v);

/* FONCTIONS */

vector<double> q1(int n){
  vector<double> v;
  double nb_aleatoire = 0;
  for(int i = 0; i < n; i++)
     {
        nb_aleatoire = rand();
        v.push_back(nb_aleatoire);
     }
  return v;
}

void q2(vector<double> v){
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << endl;
	} 
}

/* MAIN */

int main(){
  cout << "Hello World!" << endl;
  vector<double> v1 = q1(10);
	q2(v1);
  return 0;
}

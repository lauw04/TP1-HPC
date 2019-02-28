#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

/* DECLARATIONS FONCTION */

vector<double> q1(int n);
void q2(vector<double> v);
vector<double> q3(vector<double> v1,vector<double> v2

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

vector<double> q3(vector<double> v1,vector<double> v2){
  vector<double> somme;
  if(v1.size() == v2.size()){
    for(int i = 0; i < size(v1); i++){
      somme.push_back(v1[i] + v2[i])
    }
  }
  else{
    cout << "Les vecteurs ne font pas la même taille !" << endl;}
  return somme
}

/* MAIN */

int main(){
  cout << "Hello World!" << endl;
  vector<double> v1 = q1(10);
  vector<double> v2 = q1(10);
  vector<double> v3 = q3(v1,v2);
  q2(v3);
  return 0;
}

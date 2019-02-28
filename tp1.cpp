#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void q1(int n);

void q1(int n){
  vector<double> v;
  double nb_aleatoire = 0;
  for(int i = 0; i < n; i++)
     {
        nb_aleatoire = rand();
        cout << nb_aleatoire << endl;
        v.push_back(nb_aleatoire);
     }
}


int main(){
  cout << "Hello World!" << endl;
  q1(10);
  return 0;
}

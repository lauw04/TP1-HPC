#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<double> q1(int n);

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


int main(){
  cout << "Hello World!" << endl;
  vector<double> v1 = q1(10);
  vector<double>::iterator it; 
  for(it = v1.begin(); it!=v1.end(); ++it)
    {
        cout << *it << endl;
    }
  return 0;
}

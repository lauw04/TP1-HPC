#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

/* DECLARATIONS FONCTION */

vector<double> q1(int n);
void q2(vector<double> v);
vector<double> q3(vector<double> v1,vector<double> v2);
double q4(vector<double> v);
vector<double> q8(vector<double> v, double x);

/* FONCTIONS */

vector<double> q1(int n){
  vector<double> v;
  double nb_aleatoire = 0;
  for(int i = 0; i < n; i++)
     {
        nb_aleatoire = rand()%100;
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
  vector<double> somme = v1;
  #pragma omp parallel
  {
  if(v1.size() == v2.size()){
    #pragma omp for
    for(int i = 0; i < v1.size(); i++){
      somme[i]=(v1[i] + v2[i]);
    }
  }
  else{
    cout << "Les vecteurs ne font pas la même taille !" << endl;
  }
  }
  return somme;
}

double q4(vector<double> v){
  double somme = 0;
  #pragma omp parallel for reduction (+:somme)
  for(int i = 0; i < v.size(); i++){
    somme += v[i];
  }
  return somme;
}

vector<double> q8(vector<double> v, double x){
  vector<double> result= v;
  #pragma omp parallel
  {
  #pragma omp for
  for(int i = 0; i < v.size(); i++){
    result[i]=(x*v[i]);
  }
  }
  return result;
}

/* MAIN */

int main(){
  cout << "Hello World!" << endl;


  int num_threads = 0;
  int k = 0;
  cout << "Combien de coeurs on utilise ?" << endl;
  cin >> num_threads;
  cout << "On utilise donc " << num_threads << " coeurs." << endl;
  omp_set_num_threads(num_threads);
  cout << "La longueur du vecteur ?" << endl;
  cin >> k;
  cout << "Les vecteurs vont contenir " << k << " valeurs." << endl;
  vector<double> v1 = q1(k);
  vector<double> v2 = q1(k);
  vector<double> v3 = q3(v1,v2);
  q2(v3);
  double a = q4(v3);
  cout << a << endl;

  // Question 8
  int x = 1;
  cout << "Par combien multiplie-t-on notre vecteur ?" << endl;
  cin >> x;
  cout << "On multiple le vecteur " << x << " fois." << endl;
  vector<double> vecteur_mult = q8(v3,x);
  cout << "vecteur_mult" << endl;
  q2(vecteur_mult);
  return 0;
}

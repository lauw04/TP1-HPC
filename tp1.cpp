#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <chrono>

using namespace std;

/* DECLARATIONS FONCTION */

vector<double> q1(int n);
void q2(vector<double> v);
vector<double> q3(vector<double> v1,vector<double> v2);
double q4(vector<double> v);
vector<double> q8(vector<double> v, double x);
vector<vector<double>> q10_1(int n, int m);
void q10_2(vector<vector<double>> v);

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
  vector<double> addition = v1;
  #pragma omp parallel
  {
  if(v1.size() == v2.size()){
    #pragma omp for
    for(int i = 0; i < v1.size(); i++){
      addition[i]=(v1[i] + v2[i]);
    }
  }
  else{
    cout << "Les vecteurs ne font pas la même taille !" << endl;
  }
  }
  return addition;
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

vector<vector<double>> q10_1(int n, int m){
  vector<vector<double>> v;
  v.resize(n);
  for(int i=0; i<n; i++){
    v[i].resize(m);
  }
  double nb_aleatoire = 0;
  for(int i = 0; i < n; i++){
    for(int j=0; j<m; j++){
      nb_aleatoire = rand()%100;
      v[i][j] =  nb_aleatoire;
    }
  }
  return v;
}

void q10_2(vector<vector<double>> v){
	for(int i = 0; i < v.size(); i++){
    for(int j=0; j<v[i].size(); j++){
      cout << v[i][j] << " ";
    }
    cout << endl;
	} 
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
  chrono::time_point<chrono::system_clock> start, end;  
  
  /* ADDITION */
  
	start = chrono::system_clock::now();  
  vector<double> addition = q3(v1, v2);
	end = chrono::system_clock::now();
  int time_addition = chrono::duration_cast<chrono::microseconds> (end-start).count();
  cout << " Temps d'éxécution de l'addition de deux vecteurs de taille " << k << " avec " << num_threads << " coeur(s) : " << time_addition << endl;

	/* SOMME */
	
	start = std::chrono::system_clock::now();  
  double somme = q4(v1);
	end = chrono::system_clock::now();
  int time_somme = chrono::duration_cast<chrono::microseconds> (end-start).count();
  cout << "Temps d'éxécution de la somme des éléments d'un vecteur de taille " << k << " avec " << num_threads << " coeur(s) : " << time_somme << endl;
  
  
	/* MULTIPLICATION */
  int x = 1;
  cout << "Par combien multiplie-t-on notre vecteur ?" << endl;
  cin >> x;
  cout << "On multiple le vecteur " << x << " fois." << endl; 
	start = chrono::system_clock::now();
	vector<double> multi = q8(v1,x);
	end = chrono::system_clock::now();
  int time_multi = chrono::duration_cast<chrono::microseconds> (end-start).count();
  cout << "Temps d'éxécution de la multiplication d'un vecteur de taille " << k << " par un scalaire, avec " << num_threads << " coeur(s) : " << time_multi << endl;


  // Question 10
  vector<vector<double>> v5 = q10_1(3,4);
  q10_2(v5);
  return 0;
}

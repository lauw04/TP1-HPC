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
void q9(int num_threads);

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
  vector<double> somme;
  if(v1.size() == v2.size()){
    for(int i = 0; i < v1.size(); i++){
      somme.push_back(v1[i] + v2[i]);
    }
  }
  else{
    cout << "Les vecteurs ne font pas la même taille !" << endl;
  }
  return somme;
}

double q4(vector<double> v){
  double somme = 0;
  for(int i = 0; i < v.size(); i++){
    somme += v[i];
  }
  return somme;
}

void q9fort(){
	std::chrono::time_point<std::chrono::system_clock> start, end;
	vector<double> v1 = q1(500);
	vector<double> v2 = q1(500);
	int coeur[3] = {1, 2, 4}; //Nombre de coeurs à tester
	
	/* ADDITION */
	vector<int> addition;
	for(int i = 0; i < 3; i++){
		start = std::chrono::system_clock::now();
		int result = q3(v1, v2, coeur[i]);
		end = std::chrono::system_clock::now();
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds> (end-start).count();
    addition.push_back(elapsed_seconds);
  }
  
	/* SOMME */
	vector<int> somme;
	for(int i = 0; i < 3; i++){
		start = std::chrono::system_clock::now();
		int result = q4(v1, coeur[i]);
		end = std::chrono::system_clock::now();
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds> (end-start).count();
    somme.push_back(elapsed_seconds);
  }

	/* MULTIPLICATION */
	vector<int> somme;
	for(int i = 0; i < 3; i++){
		start = std::chrono::system_clock::now();
		int result = q8(v1, coeur[i]);
		end = std::chrono::system_clock::now();
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds> (end-start).count();
    somme.push_back(elapsed_seconds);
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
  vector<double> v3 = q3(v1,v2, num_threads);
  q2(v3);
  double a = q4(v3);
  cout << a << endl;
  
  
  return 0;
}

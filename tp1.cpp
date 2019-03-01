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
//void q9();

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

vector<double> q3(vector<double> v1,vector<double> v2, int num_threads){
  vector<double> addition;
  if(v1.size() == v2.size()){
    for(int i = 0; i < v1.size(); i++){
      addition.push_back(v1[i] + v2[i]);
    }
  }
  else{
    cout << "Les vecteurs ne font pas la même taille !" << endl;
  }
  return addition;
}

double q4(vector<double> v, int num_threads){
  double somme = 0;
  #pragma omp parallel for reduction (+:somme)
  for(int i = 0; i < v.size(); i++){
    somme += v[i];
  }
  return somme;
}

vector<double> q8(vector<double> v, double x, int num_threads){
  vector<double> result;
  for(int i = 0; i < v.size(); i++){
    result.push_back(x*v[i]);
  }
  return result;
}

/*void q9fort(){
	std::chrono::time_point<std::chrono::system_clock> start, end;
	vector<double> v1 = q1(500);
	vector<double> v2 = q1(500);
	double x = 4;
	int coeur[3] = {1, 2, 4}; //Nombre de coeurs à tester
	
	
	vector<int> addition;
	for(int i = 0; i < 3; i++){
		start = std::chrono::system_clock::now();
		int result = q3(v1, v2, coeur[i]);
		end = std::chrono::system_clock::now();
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds> (end-start).count();
    addition.push_back(elapsed_seconds);
  }
  
	vector<int> somme;
	for(int i = 0; i < 3; i++){
		start = std::chrono::system_clock::now();
		int result = q4(v1, coeur[i]);
		end = std::chrono::system_clock::now();
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds> (end-start).count();
    somme.push_back(elapsed_seconds);
  }

	
	vector<int> multi;
	for(int i = 0; i < 3; i++){
		start = std::chrono::system_clock::now();
		int result = q8(v1, x, coeur[i]);
		end = std::chrono::system_clock::now();
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds> (end-start).count();
    multi.push_back(elapsed_seconds);
  }
}*/

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
  
  
  /* ADDITION */
  
  chrono::time_point<chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();  
  vector<double> addition = q3(v1, v2);
	end = chrono::system_clock::now();
  int elapsed_seconds = chrono::duration_cast<chrono::seconds> (end-start).count();
	std::time_t end_time = chrono::system_clock::to_time_t(end);
  cout << "Temps d'éxécution de l'addtion de deux vecteurs de taille" << k << "avec" << num_threads << "coeur(s) : " << elapsed_seconds << ctime(&end_time);

	/* SOMME */
	
	/* MULTIPLICATION */
  // Question 8
  int x = 1;
  cout << "Par combien multiplie-t-on notre vecteur ?" << endl;
  cin >> x;
  cout << "On multiple le vecteur " << x << " fois." << endl;
  vector<double> vecteur_mult = q8(v3,x,num_threads);
  cout << "vecteur_mult" << endl;
  q2(vecteur_mult);
  return 0;
  
  
}

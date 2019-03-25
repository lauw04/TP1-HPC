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
vector<vector<double>> q10_3(vector<vector<double>> v1, vector<vector<double>> v2);
double q10_4(vector<vector<double>> v);
vector<vector<double>> q10_5(vector<vector<double>> v, double x);
vector<double> q11(vector<vector<double>> m, vector<double> v);
vector<vector<double>> q12(vector<vector<double>> m1, vector<vector<double>> m2);


/* FONCTIONS */

/****************
*PARTIE VECTEURS*
****************/

vector<double> q1(int n){
	vector<double> v;
	double nb_aleatoire = 0;
	for(int i = 0; i < n; i++){
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

/****************
*PARTIE MATRICES*
****************/

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
	cout << endl;	
}

//Addition
vector<vector<double>> q10_3(vector<vector<double>> v1, vector<vector<double>> v2){
 	vector<vector<double>> addition = v1;
 	#pragma omp parallel
 	{
		size_t n1 = v1.size();
		size_t m1 = v1[0].size();
		size_t n2 = v2.size();
		size_t m2 = v2[0].size();
		if(n1 == n2 and m1 == m2){
  			#pragma omp for
			for(int i = 0; i < v1.size(); i++){
				for(int j=0; j<v1[i].size(); j++){
					addition[i][j]=(v1[i][j] + v2[i][j]);
				}
			}
		}
		else{
			cout << "Les matrices ne font pas la même taille !" << endl;
		}
	}
  return addition;
}

//Somme
double q10_4(vector<vector<double>> v){
	double somme = 0;
	#pragma omp parallel for reduction (+:somme)
	for(int i = 0; i < v.size(); i++){
		for(int j = 0; j< v[0].size(); j++){
			somme += v[i][j];
		}
	}
	return somme;
}

//Multiplication
vector<vector<double>> q10_5(vector<vector<double>> v, double x){
	vector<vector<double>> result= v;
	#pragma omp parallel
 	{
 		#pragma omp for
		for(int i = 0; i < v.size(); i++){
			for(int j = 0; j< v[0].size(); j++){
    			result[i][j]=(x*v[i][j]);
    		}
		}
	}
	return result;
}

vector<double> q11(vector<vector<double>> m, vector<double> v){
	size_t n = m.size();
	size_t p = m[0].size();
	size_t k = v.size();
	vector<double> result;
	#pragma omp parallel
	{
		if (p==k){
			result.resize(n);
			#pragma omp for
			for (int i=0; i<n; i++){
				result[i] = 0;
				for (int j=0; j<p; j++){
					cout << m[i][j] << " " << v[j] << endl;
					result[i] += m[i][j]*v[j];
				}
			}
		}
		else{
			cout << "On ne peut pas multiplier cette matrice et ce vecteur" << endl;
		}
	}
	return result;
}

vector<vector<double>> q12(vector<vector<double>> m1, vector<vector<double>> m2){
	size_t n1 = m1.size();
	size_t p1 = m1[0].size();
	size_t n2 = m2.size();
	size_t p2 = m2[0].size();
	vector<vector<double>> result;
	#pragma omp parallel
	{
		if (p1==n2){
			result.resize(n1);
			for (int a=0; a<n1; a++){
				result[a].resize(p2);
			}
			#pragma omp for
			for (int i=0; i<n1; i++){
				for (int j=0; j<p2; j++){
					result[i][j]=0;
					cout << endl;
					for (int k=0; k<p1;k++){
						result[i][j] += m1[i][k]*m2[k][j];
					}	
				}
			}
		}
	
		else{
			cout << "On ne peut pas multiplier ces deux matrices" << endl;
		}
	}
	return result;
}

/* MAIN */

int main(){
	//cout << "Hello, World" << endl;
  
	int num_threads;
	cout << "Combien de coeurs on utilise ?" << endl;
	cin >> num_threads;
	omp_set_num_threads(num_threads);
	char type;
	cout << "Pour travailler avec des vecteurs tapez 'v'. Pour travailler avec des matrices, tapez 'm'. Pour tester les fonctions d'affichages, tapez 't'" << endl;
	cin >> type;
	
	if (type=='v'){
		int n;
		cout << "La longueur du vecteur ?" << endl;
		cin >> n;
		vector<double> v1 = q1(n);
		vector<double> v2 = q1(n);
		chrono::time_point<chrono::system_clock> start, end;
  
		/* ADDITION */
  
		start = chrono::system_clock::now();  
		vector<double> addition = q3(v1, v2);
		end = chrono::system_clock::now();
		int time_addition = chrono::duration_cast<chrono::microseconds> (end-start).count();
		cout << " Temps d'éxécution de l'addition de deux vecteurs de taille " << n << " avec " << num_threads << " coeur(s) : " << time_addition << endl;

		/* SOMME */
	
		start = std::chrono::system_clock::now();  
		double somme = q4(v1);
		end = chrono::system_clock::now();
		int time_somme = chrono::duration_cast<chrono::microseconds> (end-start).count();
		cout << "Temps d'éxécution de la somme des éléments d'un vecteur de taille " << n << " avec " << num_threads << " coeur(s) : " << time_somme << endl;
  
  
		/* MULTIPLICATION */
		
		int x;
		cout << "Par combien multiplie-t-on notre vecteur ?" << endl;
		cin >> x;
		cout << "On multiple le vecteur " << x << " fois." << endl; 
		start = chrono::system_clock::now();
		vector<double> multi = q8(v1,x);
		end = chrono::system_clock::now();
		int time_multi = chrono::duration_cast<chrono::microseconds> (end-start).count();
		cout << "Temps d'éxécution de la multiplication d'un vecteur de taille " << n << " par un scalaire, avec " << num_threads << " coeur(s) : " << time_multi << endl;
	}
	
	else if (type == 'm'){
		int n;
		int m;
		cout << "Combien de lignes ?" << endl;
		cin >> n;
		cout << "Combien de colonnes ?" << endl;
		cin >> m;
		vector<vector<double>> m1 = q10_1(n,m);
		vector<vector<double>> m2 = q10_1(n,m);
		vector<vector<double>> m3 = q10_1(m,n);
		vector<double> v = q1(m);
		chrono::time_point<chrono::system_clock> start, end;
		
		/* ADDITION */
		
		start = chrono::system_clock::now();  
		vector<vector<double>> addition = q10_3(m1, m2);
		end = chrono::system_clock::now();
		int time_addition = chrono::duration_cast<chrono::microseconds> (end-start).count();
		cout << " Temps d'éxécution de l'addition de deux matrices de taille " << n << " x " << m << "avec" << num_threads << " coeur(s) : " << time_addition << endl;
		
		/* SOMME */

		start = std::chrono::system_clock::now();  
		double somme = q10_4(m1);
		end = chrono::system_clock::now();
		int time_somme = chrono::duration_cast<chrono::microseconds> (end-start).count();
		cout << "Temps d'éxécution de la somme des éléments d'une matrice de taille " << n << " x " << m << " avec " << num_threads << " coeur(s) : " << time_somme << endl;
  
		/* MULTIPLICATION */
		
		int x;
		cout << "Par combien multiplie-t-on notre matrice ?" << endl;
		cin >> x;
		start = chrono::system_clock::now();
		vector<vector<double>> multi = q10_5(m1,x);
		end = chrono::system_clock::now();
		int time_multi = chrono::duration_cast<chrono::microseconds> (end-start).count();
		cout << "Temps d'éxécution de la multiplication d'une matrice de taille " << n << "x" << m << " par un scalaire, avec " << num_threads << " coeur(s) : " << time_multi << endl;
	
		/* MULTIPLICATION MATRICE/VECTEUR*/
		
		start = chrono::system_clock::now();
		vector<double> matvec = q11(m1,v);
		end = chrono::system_clock::now();
		int time_matvec = chrono::duration_cast<chrono::microseconds> (end-start).count();
		cout << "Temps d'éxécution de la multiplication d'une matrice et  de taille " << n << "x" << m << " par un vecteur de taille " << m << " avec " << num_threads << " coeur(s)." << endl;
	
		/* MULTIPLICATION MATRICE/MATRICE*/

		start = chrono::system_clock::now();
		vector<vector<double>> matmat = q12(m1,m3);
		end = chrono::system_clock::now();
		int time_matmat = chrono::duration_cast<chrono::microseconds> (end-start).count();
		cout << "Temps d'éxécution de la multiplication de 2 matrices de taille " << n << "x" << m << "  et " << m << "x" << n << " avec " << num_threads << " coeur(s)." << endl;
	}
	
	else if (type == 't'){
		int n;
		int m;
		int p;
		cout << "Taille du vecteur ?" << endl;
		cin >> n;
		cout << endl;
		vector<double> v1 = q1(n);
		q2(v1);
		
		cout << "Nombre de lignes de la matrice ?" << endl;
		cin >> m;
		cout << "Nombre de colonnes de la matrice ?" << endl;
		cin >> p;
		cout << endl;
		vector<vector<double>> v2 = q10_1(m,p);
		vector<vector<double>> v3 = q10_1(p,m);
		q10_2(v2);
		q10_2(v3);
		
		//vector<vector<double>> v4 = q12(v2,v3);
		//q10_2(v4);

	}

  return 0;
}

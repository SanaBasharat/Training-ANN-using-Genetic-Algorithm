#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

const int datasize = 150;
const int cols = 5;
const double training_rate = 0.001;
const int r = 10;
const int c = 9;
const int features = 4;
const int classes = 3;
const int popsize = 100;

void swapWeightArray(double arr1[][c], double arr2[][c]) {
	double temp;
	for (int i = 0;i < r;i++) {
		for (int j = 0;j < c;j++) {
			temp = arr1[i][j];
			arr1[i][j] = arr2[i][j];
			arr2[i][j] = temp;
		}
	}
}


void heapify(double arr[], double W[][r][c], int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && arr[l] > arr[largest])
		largest = l;
	if (r < n && arr[r] > arr[largest])
		largest = r;
	if (largest != i){
		swap(arr[i], arr[largest]);
		swapWeightArray(W[i], W[largest]);
		heapify(arr, W, n, largest);
	}
}

void heapSort(double arr[], double W[][r][c], int n){
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, W, n, i); 
	for (int i = n - 1; i > 0; i--){
		swap(arr[0], arr[i]);
		swapWeightArray(W[0], W[i]);
		heapify(arr, W, i, 0);
	}
}

int main()
{
	double** dataset = new double* [datasize];
	ifstream fin;
	fin.open("randomized dataset.txt");
	if (!fin) { cout << "whoops"; }
	for (int i = 0;i < datasize;i++) {
		dataset[i] = new double[cols];
		fin >> dataset[i][0];
		fin >> dataset[i][1];
		fin >> dataset[i][2];
		fin >> dataset[i][3];
		fin >> dataset[i][4];
	}
	fin.close();

	double cost = 1000, prevcost = 2000;
	int max_iterations = 0;

	srand(time(NULL));
	double randomnum = 0;
	double W[popsize][r][c];
	for (int k = 0;k < popsize;k++) {
		for (int i = 0;i < r;i++) {
			for (int j = 0;j < c;j++) {
				randomnum = rand() % 999;
				W[k][i][j] = (double)(randomnum / 1000);
			}
		}
	}


	double A[r];				//START OF GENETIC ALGORITHM
	double out[classes];
	double fitness[popsize];
	int iteration = 0;
	while (iteration < 100) {
		for (int i = 0;i < popsize;i++) {
			fitness[i] = 0;
		}

		for (int k = 0;k < popsize;k++) {	//calculating fitness
			for (int i = 0;i < r;i++) {
				A[i] = 0;
			}
			for (int i = 0;i < classes;i++) {
				out[i] = 0;
			}
			int s = 0;
			double sig = 0;

			for (int i = 0;i < r;i++) {
				for (int j = 0;j < features;j++) {
					A[i] += (dataset[s][j] * W[k][i][0]);
				}
				A[i] += W[k][i][4];
				sig = 1 / (1 + exp(A[i] * -1));
				A[i] = sig;
			}
			s++;
			for (int i = 0;i < classes;i++) {
				for (int j = 0;j < r;j++) {
					out[i] += (A[j] * W[k][i + 5][j]);
				}
				out[i] += W[k][8][i];
				sig = 1 / (1 + exp(out[i] * -1));
				out[i] = sig;
			}
			for (int i = 0;i < classes;i++) {
				fitness[k] += out[i];
			}
		}

		heapSort(fitness, W, popsize);		//sorting based on fitness function
		//cout << fitness[0] << endl;

		int cursor = 40;
		int randomnum1;
		int randomnum2;
		double temp;
		for (int k = 0;k < popsize * 0.2;k++) {		//SELECTION AND CROSSOVER
			randomnum1 = rand() % 40;
			randomnum2 = rand() % 39;
			for (int i = 0;i < r;i++) {
				for (int j = 0;j < c;j++) {
					W[cursor][i][j] = W[randomnum1][i][j];
					W[cursor + 1][i][j] = W[randomnum2][i][j];
				}
			}
			for (int i = 2;i < 6;i++) {
				for (int j = 2;j < 6;j++) {		//crossover
					temp = W[cursor][i][j];
					W[cursor][i][j] = W[cursor + 1][i][j];
					W[cursor + 1][i][j] = temp;
				}
			}
			cursor += 2;
		}

		for (int k = cursor;k < popsize;k++) {		//MUTATION
			randomnum1 = rand() % 79;
			for (int i = 0;i < r;i++) {
				for (int j = 0;j < c;j++) {
					W[cursor][i][j] = W[randomnum1][i][j];
				}
			}
			for (int i = 0;i < 2;i++) {
				for (int j = 0;j < c;j++) {
					randomnum = rand() % 999;
					W[cursor][i][j] = (double)randomnum / 1000;		//mutation
				}
			}
			cursor++;
		}
		iteration++;
	}


	for (int i = 0;i < popsize;i++) {
		fitness[i] = 0;
	}

	for (int k = 0;k < popsize;k++) {	//calculating fitness
		for (int i = 0;i < r;i++) {
			A[i] = 0;
		}
		for (int i = 0;i < classes;i++) {
			out[i] = 0;
		}
		int s = 0;
		double sig = 0;

		for (int i = 0;i < r;i++) {
			for (int j = 0;j < features;j++) {
				A[i] += (dataset[s][j] * W[k][i][0]);
			}
			A[i] += W[k][i][4];
			sig = 1 / (1 + exp(A[i] * -1));
			A[i] = sig;
		}
		s++;
		for (int i = 0;i < classes;i++) {
			for (int j = 0;j < r;j++) {
				out[i] += (A[j] * W[k][i + 5][j]);
			}
			out[i] += W[k][8][i];
			sig = 1 / (1 + exp(out[i] * -1));
			out[i] = sig;
		}
		for (int i = 0;i < classes;i++) {
			fitness[k] += out[i];
		}

	}

	heapSort(fitness, W, popsize);		//sorting based on fitness function

	//BACK PROPOGATION

	double derCW;
	double trainingrate = 0.001;
	double sum = 0;
	double sigmoid[r];
	for (int ilayer = 0;ilayer < 75;ilayer++) {			//change here for 2-fold cross validation
		for (int i = 0;i < r;i++) {
			A[i] = 0;
		}
		for (int i = 0;i < classes;i++) {
			out[i] = 0;
		}
		int s = 0;
		double sig = 0;
		for (int i = 0;i < r;i++) {
			for (int j = 0;j < features;j++) {
				A[i] += (dataset[ilayer][j] * W[0][i][0]);
			}
			A[i] += W[0][i][4];
			sig = 1 / (1 + exp(A[i] * -1));
			sigmoid[i] = sig;
			A[i] = sig;
		}
		for (int i = 0;i < classes;i++) {
			for (int j = 0;j < r;j++) {
				out[i] += (A[j] * W[0][i + 5][j]);
			}
			out[i] += W[0][8][i];
			sig = 1 / (1 + exp(out[i] * -1));
			out[i] = sig;
		}


		for (int j = 0;j < r;j++) {
			for (int k = 0;k < classes;k++) {
				sum = 0;
				for (int samples = 0;samples < 75;samples++) {
					sum += (((k + 1) - out[k]) * sigmoid[j] * (1 - sigmoid[j]) * A[j]);
				}
				derCW = -0.5 * sum;
				W[0][j][k] = W[0][j][k] - (trainingrate * derCW);
			}
		}

		
		for (int i = 0;i < features;i++) {
			for (int j = 0;j < r;j++) {
				sum = 0;
				derCW = dataset[ilayer][i] * sigmoid[j] * (1 - sigmoid[j]);
				for (int k = 0;k < classes;k++) {
					for (int samples = 0;samples < 75;samples++) {
						sum += (((k + 1) - out[k]) * sigmoid[j] * (1 - sigmoid[j]) * W[0][i][j]);
					}
					derCW = -0.5 * sum;
					W[0][i][j] = W[0][i][j] - (trainingrate * derCW);
				}
			}
		}

	}

	int resultingclass[150];
	int matches = 0;
	for (int ilayer = 75;ilayer < 150;ilayer++) {			//change here for 2-fold cross validation
		for (int i = 0;i < classes;i++) {
			out[i] = 0;
		}
		int s = 0;
		double sig = 0;

		for (int i = 0;i < r;i++) {
			for (int j = 0;j < features;j++) {
				A[i] += (dataset[ilayer][j] * W[0][i][0]);
			}
			A[i] += W[0][i][4];
			sig = 1 / (1 + exp(A[i] * -1));
			A[i] = sig;
		}
		for (int i = 0;i < classes;i++) {
			for (int j = 0;j < r;j++) {
				out[i] += (A[j] * W[0][i + 5][j]);
			}
			out[i] += W[0][8][i];
			sig = 1 / (1 + exp(out[i] * -1));
			out[i] = sig;
			if (out[i] <= 0.3333) {
				resultingclass[ilayer] = 1;
			}
			else if (out[i] <= 0.6666) {
				resultingclass[ilayer] = 2;
			}
			else {
				resultingclass[ilayer] = 3;
			}
		}
	}

	for (int i = 75;i < 150;i++) {						//change here for 2-fold cross validation
		if (resultingclass[i] == dataset[i][4]) {
			matches++;
		}
	}
	cout << matches << endl;

}

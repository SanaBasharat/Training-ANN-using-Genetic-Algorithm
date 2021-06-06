#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

const int datasize = 150;
const int cols = 5;
const double training_rate = 0.001;

int main()
{
	ifstream fin;
	fin.open("iris dataset.txt");
	if (!fin) { 
		cout << "whoops"; 
	}
	char* buff = new char[100];
	fin.getline(buff, 100, '\n');

	double a, b, c, d;
	char sp[15];
	double** dataset = new double *[datasize];
	
	for (int i = 0;i < datasize;i++) {		//READING FROM FILE AND STORING IN 2D ARRAY DATASET
		fin >> a;
		fin.ignore();
		fin >> b;
		fin.ignore();
		fin >> c;
		fin.ignore();
		fin >> d;
		fin.ignore();
		fin.getline(sp, 15, '\n');
		dataset[i] = new double[cols];
		dataset[i][0] = a;
		dataset[i][1] = b;
		dataset[i][2] = c;
		dataset[i][3] = d;
		if (sp[6] == 'o') { dataset[i][4] = 1.0; }
		else if (sp[6] == 's') { dataset[i][4] = 2.0; }
		else if (sp[6] == 'g') { dataset[i][4] = 3.0; }
	}
	fin.close();

	srand(time(NULL));						//RANDOMIZING THE DATASET
	int r = 0;
	for (int i = 0;i < datasize;i++) {
		r = (rand() % 149) + 1;
		double* temp = dataset[i];
		dataset[i] = dataset[r];
		dataset[r] = temp;
	}

	ofstream fout;							//STORING RANDOMIZED DATASET IN NEW FILE
	fout.open("randomized dataset.txt");
	if (!fout) { cout << "whoops"; }
	for (int i = 0;i < datasize;i++) {
		fout << dataset[i][0] << " " << dataset[i][1] << " " << dataset[i][2] << " " << dataset[i][3] << " " << dataset[i][4] << endl;
	}
	fout.close();

}

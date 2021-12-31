#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <array>
using namespace std;

void tri2Ints(auto &minData, auto &maxData) {
    if(maxData < minData) {    // Usually, the minimum is before the maximum, and sometimes it is not the default value.
        swap(maxData,minData);
        }
    }

void initRandMatrix1D(vector<int>& MatrixInit1D, int minData = 0, int maxData = 256) { // Ok.
    tri2Ints(minData, maxData) ;     // Usually, the minimum is before the maximum, and sometimes it is not the default value.
    for(int a = 0; a < MatrixInit1D.size() ; a++) {
        MatrixInit1D[a] = rand() % (maxData - minData + 1) + minData;
        }
    MatrixInit1D.push_back(0);
    }

void coutMatrix1D(vector<int>& coutMatrix1D, int longer = 15, bool denonce = true) { // Ok.
    for(int a = 0; a < coutMatrix1D.size() ; a++) {
        if ((a%(longer+0)==1) && (denonce)) {
            cout << "_";
            }
        cout << coutMatrix1D[a] ;
        if ((a%(longer+0)==1) && (denonce)) {
            cout << "_";
            }
        cout << " ";
        }
    }

bool recMatrix1D(vector<int>& coutMatrix1D, string fileRec = "") {
    ofstream myfile;
    myfile.open (fileRec);
    if (!myfile.is_open()) { // Error file.
        cerr << "Unable to open file!";   // Err of file? Help needed:
        return false; // Error file.
        }
    else { // File ok.
        for(int a = 0; a < coutMatrix1D.size() ; a++) {
            myfile << coutMatrix1D[a] ;
            if (a < coutMatrix1D.size()-1) {
                myfile <<  ", " ;
                }
            }
        myfile.close();
        clog << "File Ok!" << endl;
        return true;
        }
    }

void lissageVector1D(vector<int>& LissageMatrix1DIn, vector<int>& LissageMatrix1DOut, int longer = 15, bool loop = true, int smooth = 5) { // longer -1 ?
    int ar = 0;
    int coeff1 = 1;
    int coeff2 = 1;
    int coeff3 = 0;
    for(int a = 0; a < ( longer * LissageMatrix1DIn.size()-1) ; a++) {
        if (0==a % longer ) {
            LissageMatrix1DOut.push_back(LissageMatrix1DIn[a/longer]);
            ar = ar+1;
            }

        else {
            if (a % longer<smooth) { // Juste après le point.
                coeff1 = 3 * (longer - (a % longer));
                coeff2 = 1 * (a % longer);
                coeff3 = 0;
                }
            else if ((a % longer)>(longer-smooth)) { // Juste avant le point.
                coeff1 = 1 * (longer - (a % longer));
                coeff2 = 3 * (a % longer);
                coeff3 = 0;
                }
            else { // Vers le milieu du segment.
                coeff1 = -1 * (longer - (a % longer));
                coeff2 = -1 * (a % longer);
                coeff3 = 0;
                }
            LissageMatrix1DOut.push_back((coeff1 * LissageMatrix1DIn[ar-1] + coeff2 * LissageMatrix1DIn[ar] + coeff3 * LissageMatrix1DIn[ar+1])/(coeff1 + coeff2 + coeff3)); // moyenne pondérée.
            }
        }
    }

int main() {
    srand (time(NULL));
    int N = 42;
    bool loop = true;
    int longer = 15;
    int smooth = 5;
    string file = "file.csv";
    vector<int> Matrix(N, 0);
    vector<int> Matrix2(1, 0);
    initRandMatrix1D(Matrix, -42, 42);
    coutMatrix1D(Matrix,1,false);
    lissageVector1D(Matrix,Matrix2, longer, loop, smooth);
    recMatrix1D(Matrix2, file);
    cout << "" << endl;
    cout << "" << endl;
    coutMatrix1D(Matrix2, longer, true);
    cout << "" << endl;
    cout << "" << endl;
    cout << "End!" << endl;
    return 0;
    }

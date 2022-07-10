#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > buildMatrix(int n , int m){
    /* Retorna una matriz rellena con solo ceros */
    vector<vector<int> > scoreMatrix(n , vector<int>(m,0));
    return scoreMatrix;
}

//Rellenar matriz con matching entre las secuencias
void fillMatchMatrix(vector<vector<int> >& matchMatrix,const string& sequence1 , const string& sequence2){
    const int match_score = 1;
    const int mismatch_penalty = -1;
    for(int i=0 ; i<sequence1.length() ; i++){
        for(int j=0 ; j<sequence2.length() ; j++){
            if(sequence1[i] == sequence2[j]){
                matchMatrix[i][j] = match_score;
            }else{
                matchMatrix[i][j] = mismatch_penalty;
            }

            cout << matchMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void printScoreMatrix(const vector<vector<int> >& scoreMatrix , const string& sequence1 , const string& sequence2 ){
    /* Imprime la matriz de puntajes */
    for(int i=0 ; i<scoreMatrix.size() ; i++){
        for(int j=0 ; j<scoreMatrix[i].size() ; j++){
            cout << scoreMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

}


int gapPenalty(){
    return -2;
}



void getAlignmentSolution(vector<vector<int> >& scoreMatrix, vector<vector<int> >& matchMatrix,const string& sequence1, const string& sequence2){
    string alignmentA;
    string alignmentB;

    int i = sequence1.length();
    int j = sequence2.length();

    while(i > 0 && j > 0){
        //Caso cuando la diagonal mas el match tiene maximo valor
        if(i > 0 && j > 0 && scoreMatrix[i][j] == scoreMatrix[i-1][j-1] + matchMatrix[i-1][j-1]){
            cout << "Diagonal" << endl;
            alignmentA = sequence1[i-1] + alignmentA;
            alignmentB = sequence2[j-1] + alignmentB;
            i--;
            j--;
        }

        //Caso cuando casilla superior tiene mayor valor
        else if(i > 0 && scoreMatrix[i][j] == scoreMatrix[i-1][j] + gapPenalty()){
            cout << "superior" << endl;
            alignmentA = sequence1[i-1] + alignmentA;
            alignmentB = '-' + alignmentB;
            i--;
        }
        //Caso cuando casilla superior tiene mayor valor
        else{
            cout << "lateral" << endl;
            alignmentA = '-' + alignmentA;
            alignmentB = sequence2[j-1] + alignmentB;
            j--;
        }
    }
    cout << alignmentA << endl;
    cout << alignmentB << endl;
}

void needlemanWunsch(vector<vector<int> >& scoreMatrix,vector<vector<int> >& matchMatrix,const string& sequence1,const string& sequence2){
    //Generar primera fila y columna
    for(int i=0 ; i<sequence1.length()+1 ; i++){
        scoreMatrix[i][0] = i * gapPenalty();
    }

    for(int j=0 ; j<sequence2.length()+1 ; j++){
        scoreMatrix[0][j] = j * gapPenalty();
    }

    for(int i=1 ; i<sequence1.length()+1 ; i++){
        for(int j=1 ; j<sequence2.length()+1 ; j++){
            int currentMax = max(scoreMatrix[i-1][j] + gapPenalty() , scoreMatrix[i][j-1] + gapPenalty()); //max superior-lateral
            scoreMatrix[i][j] = max(scoreMatrix[i-1][j-1] + matchMatrix[i-1][j-1] , currentMax); //max actual - diagonal
        }
    }

    cout << "Puntaje: " << scoreMatrix[sequence1.length()][sequence2.length()] << endl;
}



int main(){

    string sequence1;
    string sequence2;

    cout << "Secuencia 1: ";
    cin >> sequence1;

    cout << "Secuencia 2: ";
    cin >> sequence2;

    int n = sequence1.length();
    int m = sequence2.length();

    vector<vector<int> > scoreMatrix = buildMatrix(n+1,m+1);
    vector<vector<int> > matchMatrix = buildMatrix(n,m);
    fillMatchMatrix(matchMatrix,sequence1,sequence2);
    

    //Imprimir tabla DP
    needlemanWunsch(scoreMatrix,matchMatrix,sequence1,sequence2);
    printScoreMatrix(scoreMatrix,sequence1,sequence2);

    getAlignmentSolution(scoreMatrix,matchMatrix,sequence1,sequence2);

    return 0;
}



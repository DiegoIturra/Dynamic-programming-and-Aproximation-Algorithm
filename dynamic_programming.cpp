#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > buildScoreMatrix(int n , int m){
    /* Retorna una matriz rellanea con solo ceros */
    vector<vector<int> > scoreMatrix(n , vector<int>(m,0));
    return scoreMatrix;
}


void printScoreMatrix(const vector<vector<int> >& scoreMatrix , const string sequence1 , const string sequence2 ){
    /* Imprime la matriz de puntajes */
    string maxSequence , minSequence;
    if(sequence1.length() > sequence2.length()){
        maxSequence = sequence1;
        minSequence = sequence2;
    }else{
        maxSequence = sequence2;
        minSequence = sequence1;
    }

    cout << "maxima: " << maxSequence << endl;
    cout << "minima: " << minSequence << endl;

    cout << "_ _ ";
    for(int i=0 ; i<maxSequence.length() ; i++){ //Secuencia mas larga
        cout << maxSequence[i] << " ";
    }
    cout << endl;
    cout << "_ ";
    
    for(int i=0 ; i<scoreMatrix.size() ; i++){
        if(i > 0){
            cout << minSequence[i-1] << " "; //Secuencia mas corta
        }

        for(int j=0 ; j<scoreMatrix[i].size() ; j++){
            cout << scoreMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

int gapScore(){
    return -2;
}

int scoreAsigner(char a, char b ){
    int score = -1;
    if(a == b) score = 1;
    return score;
}

void needlemanWunch(vector<vector<int> >& scoreMatrix, const string sequence1,const string sequence2){
    string maxSequence , minSequence;
    if(sequence1.length() > sequence2.length()){
        maxSequence = sequence1;
        minSequence = sequence2;
    }else{
        maxSequence = sequence2;
        minSequence = sequence1;
    }

    //Generar primera fila y columna
    for(int i=1 ; i<scoreMatrix.size() ; i++){
        scoreMatrix[i][0] = scoreMatrix[i-1][0] + gapScore();
    }

    for(int j=1 ; j<scoreMatrix[0].size(); j++){
        scoreMatrix[0][j] = scoreMatrix[0][j-1] + gapScore();
    }

    //computar valores maximos para cada casilla
    cout << minSequence << " " << maxSequence << endl;

    for(int i=0 ; i<minSequence.length() ; i++){
        for(int j=0 ; j<maxSequence.length() ; j++){
            int currentMax = max(scoreMatrix[i][j+1] + gapScore() , scoreMatrix[i+1][j] + gapScore());
            scoreMatrix[i+1][j+1] = max(scoreMatrix[i][j] + scoreAsigner(minSequence[i],maxSequence[j]),currentMax);
        }
    }
}



int main(){

    const string sequence1 = "GA";
    const string sequence2 = "CCCCCC";

    int n = min(sequence1.length(),sequence2.length());
    int m = max(sequence1.length(),sequence2.length());

    vector<vector<int> > scoreMatrix = buildScoreMatrix(n+1,m+1);

    //Imprimir tabla DP
    needlemanWunch(scoreMatrix,sequence1,sequence2);
    printScoreMatrix(scoreMatrix,sequence1,sequence2);

    // Comando ejecucion
    // g++ dynamic_programming.cpp
    // ./a.out

    return 0;
}
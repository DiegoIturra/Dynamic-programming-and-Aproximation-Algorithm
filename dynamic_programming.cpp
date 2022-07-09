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


void printScoreMatrix(const vector<vector<int> >& scoreMatrix , const string& minSequence , const string& maxSequence ){
    /* Imprime la matriz de puntajes */

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

int scoreAsigner(const char a, const char b ){
    int score = -1;
    if(a == b) score = 1;
    return score;
}


void getAlignmentSolution(vector<vector<int> >& scoreMatrix, const string& maxSequence, const string& minSequence){
    string alignmentA;
    string alignmentB;

    int i = minSequence.length();
    int j = maxSequence.length();

    while(i > 0 || j > 0){
        //cout << "casilla " << "(" << i << "," << j << ") -> " << scoreMatrix[i][j] << endl;
        //Caso cuando la diagonal mas el match tiene maximo valor
        if(i > 0 && j > 0 && scoreMatrix[i][j] == scoreMatrix[i-1][j-1] + scoreAsigner(minSequence[i-1],maxSequence[j-1])){
            cout << "diagonal" << endl;
            alignmentA += minSequence[i-1];
            alignmentB += maxSequence[j-1];
            i--;
            j--;
        }

        //Caso cuando casilla lateral tiene mayor valor
        if(j > 0 && scoreMatrix[i][j] == scoreMatrix[i][j-1] + gapScore()){
            cout << "lateral" << endl;
            alignmentA += "-";
            alignmentB += maxSequence[j-1];
            j--;
        }
        //Caso cuando casilla superior tiene mayor valor
        else{
            cout << "superior" << endl;
            alignmentB += "-";
            alignmentA += minSequence[i-1];
            i--;
        }
    }
    cout << alignmentA << endl;
    cout << alignmentB << endl;
}

void needlemanWunsch(vector<vector<int> >& scoreMatrix, const string& sequence1,const string& sequence2){
    //Generar primera fila y columna
    for(int i=1 ; i<scoreMatrix.size() ; i++){
        scoreMatrix[i][0] = scoreMatrix[i-1][0] + gapScore();
    }

    for(int j=1 ; j<scoreMatrix[0].size(); j++){
        scoreMatrix[0][j] = scoreMatrix[0][j-1] + gapScore();
    }

    //computar valores maximos para cada casilla
    cout << sequence1 << " " << sequence2 << endl;

    for(int i=0 ; i<sequence1.length() ; i++){
        for(int j=0 ; j<sequence2.length() ; j++){
            int currentMax = max(scoreMatrix[i][j+1] + gapScore() , scoreMatrix[i+1][j] + gapScore());
            scoreMatrix[i+1][j+1] = max(scoreMatrix[i][j] + scoreAsigner(sequence1[i],sequence2[j]),currentMax);
        }
    }
}



int main(){

    string sequence1;
    string sequence2;

    cout << "Secuencia 1: ";
    cin >> sequence1;

    cout << "Secuencia 2: ";
    cin >> sequence2;

    string maxSequence , minSequence;
    if(sequence1.length() > sequence2.length()){
        maxSequence = sequence1;
        minSequence = sequence2;
    }else{
        maxSequence = sequence2;
        minSequence = sequence1;
    }


    int n = minSequence.length();
    int m = maxSequence.length();

    //primer parametro: secuencia mas corta
    //segundo parametro: secuencia mas larga

    vector<vector<int> > scoreMatrix = buildMatrix(n+1,m+1);
    vector<vector<int> > matchMatrix = buildMatrix(n,m);
    fillMatchMatrix(matchMatrix,minSequence,maxSequence);

    //Imprimir tabla DP
    needlemanWunsch(scoreMatrix,minSequence,maxSequence);
    printScoreMatrix(scoreMatrix,minSequence,maxSequence);


    

    //getAlignmentSolution(scoreMatrix,minSequence,maxSequence);

    return 0;
}



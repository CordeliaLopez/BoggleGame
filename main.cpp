//
//  main.cpp
//  newBog
//
//  Created by Corde Lopez on 11/15/18.
//  Copyright © 2018 Corde Lopez. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
using namespace std;

//checs that all letters are next to each other and have never been used in a recursive approach
bool checa (string pal, char board[][4], int in, int jn, int pos, vector<pair<int,int>> coor){
    if (pos+1 == pal.length()){
        return true;
    }
    char ne = pal[pos+1];
    int cont = 0;
    
    for (int i = in-1; i < in+2;i++){
        for (int j = jn-1; j <jn+2; j++){
            if(i >= 0 && i < 4){
                if (j >= 0 && j < 4){
                    if (board[i][j] == ne){
                        if (j != jn || i != in){
                            cont = 0;
                            for (int u = 0; u < coor.size(); u++){
                                if (pair<int,int>(i,j) == coor[u]){
                                    cont++;
                                }
                            }
                            if (cont == 0){
                                coor.push_back(pair<int,int>(i,j));
                                if (checa(pal, board, i, j, pos+1, coor)){
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return false;
}


//calls recursive function for the first time if it finds the first character
bool valida (string pal, char board[][4]){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (board[i][j] == pal[0]){
                vector<pair<int, int>> coor;
                coor.push_back(pair<int,int>(i,j));
                if(checa(pal, board, i, j, 0, coor)){
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int n, m;
    char board[4][4];
    char c;
    string st;
    
    // assigns values according to number of letters
    map<int,int> mymap;
    mymap.insert(pair<int, int>(3,1));
    mymap.insert(pair<int, int>(4,1));
    mymap.insert(pair<int, int>(5,2));
    mymap.insert(pair<int, int>(6,3));
    mymap.insert(pair<int, int>(7,5));
    
    //gets the number of games that will be played
    cin>> n;
    
    //initializes a vector that records the points for each game
    vector<int> score (n, 0);

    //gets the board as 4 strings
    for (int cont = 0; cont < n; cont++){
        vector<string> strVec;
        
        for (int i = 0; i < 4; i++){
            cin>>st;
            strVec.push_back(st);
        }
    
        //converts board to characters
        for (int i = 0; i < 4; i++){
            st = strVec[i];
            for (int j = 0; j < 4; j++){
                c = st[j];
                board[i][j] = c;
            }
        }
        
        //gets the number of words played
            cin>> m;
        //processes each word played and determins if it is valid
            for (int j = 0; j < m; j++){
                cin>>st;
                //if it is valid it determines the points added
                if (valida(st, board)){
                    if (st.length() > 7){
                        score[cont] += 11;
                    }
                    else if (st.length() < 3){
                        score[cont] += 0;
                    }
                    else{
                        score[cont]+= mymap[st.length()];
                    }
                }
            }
    }
    
    
    //outputs all results of all games
    for (int i = 0; i < score.size(); i++){
        cout<<"Game "<<i+1<<": "<<score[i]<<endl;
    }
    
    
    return 0;
}

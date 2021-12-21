#include <bits/stdc++.h>

using namespace std;

char mat[5][5];

unordered_map<char, int> mpi;
unordered_map<char, int> mpj;

string encrypt(string text){
    string temp = "";

    char prev='0';
    for(int i=0; i<text.length(); i++){
        if(text[i] == prev){
            temp = temp + 'z' + text[i];
        }
        else{
            temp += text[i];
            prev = text[i];
        }
    }

    if(temp.length() %2 != 0)
        temp += 'z';

    cout << temp << endl;

    string res = "";
    for(int i=0; i < temp.length(); i += 2){
        int i1 = mpi[temp[i]];
        int i2 = mpi[temp[i+1]];

        int j1 = mpj[temp[i]];
        int j2 = mpj[temp[i+1]];

        if(i1 == i2)
            res = res + mat[i1][(j1+1)%5] + mat[i2][(j2+1)%5];
        else if(j1 == j2)
            res = res + mat[(i1+1)%5][j1] + mat[(i2+1)%5][j2];
        else{
            res += mat[i1][j2];
            res += mat[i2][j1];
        }
    }
    return res;
}

string decrypt(string decryStr){
    string res = "";

    for(int i=0; i < decryStr.length(); i += 2){
        int i1 = mpi[decryStr[i]];
        int i2 = mpi[decryStr[i+1]];

        int j1 = mpj[decryStr[i]];
        int j2 = mpj[decryStr[i+1]];

        if(i1 == i2){
            j1 = (j1-1) < 0 ? 4 : (j1-1);
            j2 = (j2-1) < 0 ? 4 : (j2-1);
            res = res + mat[i1][j1] + mat[i2][j2];
        }
        else if(j1 == j2){
            i1 = (i1-1) < 0 ? 4 : (i1-1);
            i2 = (i2-1) < 0 ? 4 : (i2-1);
            res = res + mat[i1][j1] + mat[i2][j2];
        }
        else{
            res += mat[i1][j2];
            res += mat[i2][j1];
        }
    }
    return res;
}

int main(){
    string key;
    cin >> key;

    string text;
    cin >> text;

    unordered_set<char> st;

    int len = key.length();
    int k = 0;
    int z = 97;

    for(int i=0; i<5; i++){
        for(int j=0; j<5;){
            if(k == len){
                if(st.find(char(z)) != st.end()){
                    z++;
                }
                else{
                    if(char(z) == 'j'){
                    z++;
                    continue;
                    }     
                    
                    mat[i][j] = char(z);
                    st.insert(char(z));
                    z++;
                    j++;
                }
            }
            else if(st.find(key[k]) != st.end()){
                k++;
            }
            else{
                if(key[k] == 'j'){
                    st.insert(key[k]);
                    key[k] = 'i';
                }
            
                mat[i][j] = key[k];
                st.insert(key[k]);
                j++;
                k++;
            }
        }
    }

    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            mpi[mat[i][j]] = i;
            mpj[mat[i][j]] = j;
        }
    }

    string encryText = encrypt(text);
    cout << "Encrypted Text:" << encryText << endl;

    cout << "Decrypted Text:" << decrypt(encryText) << endl;

    return 0;
}
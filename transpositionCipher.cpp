#include <bits/stdc++.h>

using namespace std;

unordered_map<char, int> mp;
string sortedKey;
int rows, col;

string encrypt(string inp, string key){
	int inpLen = inp.length();
	int keyLen = key.length();
	
	rows = ceil((inpLen*1.0)/keyLen);
	col = keyLen;
	
	vector<vector<char>> mat(rows, vector<char>(col, ' '));
	
	int k=0;
	for(int i=0; i< rows; i++){
		for(int j=0; j< col; j++){
			if(k < inpLen)
				mat[i][j] = inp[k++];
		}
	}
	
	for(int i=0; i< keyLen; i++)
		mp[key[i]] = i;
		
	sortedKey = key;
	sort(sortedKey.begin(), sortedKey.end());
	
	string encrypText = "";
	for(int i=0; i<keyLen; i++){
		int c = mp[sortedKey[i]];
		
		for(int j=0; j< rows; j++){
			encrypText += mat[j][c];
		}
	}
	
	if(encrypText[encrypText.length()-1] == ' ')
		encrypText[encrypText.length()-1] = '_';
		
	return encrypText;
}

string decrypt(string encrypText){
	if(encrypText[encrypText.length()-1] == '_')
		encrypText[encrypText.length()-1] = ' ';

	char decryp[rows][col];
	
	int k=0;
	for(int i=0; i<col; i++){
		int c = mp[sortedKey[i]];
		
		for(int j=0; j< rows; j++){
			decryp[j][c] = encrypText[k++];
		}
	}
	
	string decrypText = "";
	for(int i=0; i< rows; i++){
		for(int j=0; j < col; j++){
			decrypText += decryp[i][j];
		}
	}
	
	k = decrypText.length() - 1;
	for(;k >= 0; k--){
		if(decrypText[k] != ' ')
			break;
	}
	
	return decrypText.substr(0, k+1);
}

int main(){
	string inp = "Geeks on Work";
	
	string key = "HACK";
	
	string encrypText = encrypt(inp, key);
	cout << encrypText << endl;
	
	cout << decrypt(encrypText) << endl;
	
	return 0;
}

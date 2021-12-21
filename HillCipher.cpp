#include <bits/stdc++.h>

using namespace std;

int key[3][3];

int mod26(int x)
{
	return x >= 0 ? (x%26) : 26-(abs(x)%26);
}

int DetInverse(int a, int b=26, int x=1, int y=0) 
{ 
    if (b == 0){
        if(a == 1) return x;
        else return -26;
    }
    
    int tmp = x;
    x = y; 
    y = tmp - (a/b)*y; 
    return DetInverse(b, a%b, x, y); 
}

void findInverse2(int inverse[3][3]){
    int det = key[0][0] * key[1][1] - key[0][1]*key[1][0];

    int detI = DetInverse(det);
    if(det == -26){
        cout << "Multiplicative Inverse cannot be found";
        return;
    }
    if(detI < 0) detI += 26;

    inverse[0][0] = mod26(key[1][1]*detI);
    inverse[1][1] = mod26(key[0][0]*detI);
    inverse[0][1] = mod26(-1*key[0][1]*detI);
    inverse[1][0] = mod26(-1*key[1][0]*detI);
}

void findInverse3(int inverse[3][3]){
    int det = 0;
    for(int i=0; i<3; i++){
        det += key[0][i] * (key[1][(i+1)%3]*key[2][(i+2)%3] - key[2][(i+1)%3]*key[1][(i+2)%3]);
    }

    int detI = DetInverse(det);
    if(det == -26){
        cout << "Multiplicative Inverse cannot be found";
        return;
    }
    if(detI < 0) detI += 26;
 
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            inverse[i][j] = key[(i+1)%3][(j+1)%3]*key[(i+2)%3][(j+2)%3] - key[(i+1)%3][(j+2)%3]*key[(i+2)%3][(j+1)%3];
            inverse[i][j] = mod26(inverse[i][j]*detI);
        }
    }
}

void multiplyMatrices(int a[1000][3] , int a_rows , int a_cols ,  int b[1000][3] , int b_rows , int b_cols , int res[1000][3])
{
	for(int i=0 ; i < a_rows ; i++){
		for(int j=0 ; j < b_cols ; j++){
			for(int k=0 ; k < b_rows ; k++){
				res[i][j] += a[i][k]*b[k][j];
			}
			res[i][j] = mod26(res[i][j]);
		}
	}
}

string encrypt(string pt, int n){
    int P[100][3]= {0};
    int C[100][3]= {0};

    while(pt.length()%n != 0){
        pt += 'x';
    }

    int rows = pt.length()/n, k=0;
    for(int i=0; i<rows; i++){
        for(int j=0; j<n; j++){
            P[i][j] = pt[k++]-'a';
        }
    }

    multiplyMatrices(P, rows, n, key, n, n, C);

    string res = "";
    for(int i=0; i<rows; i++){
        for(int j=0; j<n; j++){
            res += (C[i][j]+'a');
        }
    }
    return res;
}

string decrypt(string ct, int n){
    int P[100][3] = {0};
    int C[100][3] = {0};

    int rows = ct.length()/n, k=0;
    for(int i=0; i<rows; i++){
        for(int j=0; j<n; j++){
            C[i][j] = ct[k++]-'a';
        }
    }

    int inverse[3][3] = {0};
    if(n == 2) findInverse2(inverse);
    if(n == 3) findInverse3(inverse);

    multiplyMatrices(C, rows, n, inverse, n, n, P);

    string res = "";
    for(int i=0; i<rows; i++){
        for(int j=0; j<n; j++){
            res += (P[i][j]+'a');
        }
    }
    return res;
}

int main(){
	string pt;
	int n;

	cout << "Enter the text to be encrypted    : " ;
	cin >> pt;

	cout << "Enter order of key matrix : ";
	cin >> n ;

	cout<<"Enter key matrix: " <<endl;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cin >> key[i][j];
		}
	}

	cout << "\nOriginal text  : " << pt << endl;

	string ct = encrypt(pt, n);
	cout << "Encrypted text : " << ct << endl;

	string dt = decrypt(ct, n);
	cout << "Decrypted text : " << dt << endl;
    return 0;
}
#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;


const string    Digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char      RADIX_POINT = '.';
const int SIZE = 5005;
char V_arr[SIZE], M_arr[SIZE];
vector< vector <int> > sum;
char res[2*SIZE] = {'#'};
int memo[36][36] = {0};


inline int valueOf(char x){ // integer value of a digit
    if ('0' <= x and x <= '9') return x - '0';
    if ('A' <= x and x <= 'Z') return x - 'A' +10;
    return 255;
};

inline char digitOf(int val){ // val must be < base <= 36
    return Digits[val];
};


typedef int     digitType;


//Trim leading and trailing zeros, and radixpoint
string trim(string aStr){
    string X = aStr;
    //leading zeros:
    while(X.length()>1 and X[0] == '0'and X[1] != RADIX_POINT) X.erase(0,1); //000.001

    //trailing zeros and radix point:
    if (X.find(RADIX_POINT) != string::npos){
        while(X.length()>=1 and X[X.length()-1] =='0')
            X.erase(X.length()-1,1);//0.010; 1.000
        if   (X.length()>=1 and X[X.length()-1] == RADIX_POINT)
            X.erase(X.length()-1);//123.
        if (X[0] == RADIX_POINT)
            X = "0" + X; // insert "0" into ".123"
    };
    if (X == "") X = "0";
    return X;
};



void summation(int base, int V_SIZE, int M_SIZE){

    int count = 0;
    int carry = 0;
    for(int i=0;i<SIZE;i++){

        int tmp = 0;
        for(int j=0; j<M_SIZE;j++){
            tmp+=sum[j][i];
        }
        tmp+=carry;
        res[i] = digitOf(tmp%base);
        count++;
        carry = tmp/base;
    }
    if(carry > 0){
        res[count] = digitOf(carry);
    }
}

void multiply(int base, char V[], char M[]){

    int carry = 0;
    int count = 0;
    int y = 0;
    int x = 0;

    for(int i=strlen(M)-1;i>=0;i--){

        for(int j=strlen(V)-1;j>=0;j--){

            int product = memo[valueOf(V[j])][valueOf(M[i])]+carry;    
            carry = product/base;
            product = product%base;
            //cout<<"V: "<<V[j]<<" M: " <<M[i]<<" Product: "<<product<<" Carry: "<<carry<<endl;
            sum[x][(y++)+count] = product;
        }
        if(carry > 0){
            sum[x][y+count] = carry;
        }
        carry = 0; 
        x++;    
        y=0;    
        count++;
    }
}


void printSumArray(int arr[2*SIZE+1][2*SIZE], int V_SIZE, int M_SIZE){

    for(int i=0;i<M_SIZE;i++){
        
        for(int j=0;j<SIZE;j++){

            cout<<arr[i][j];

        }
        cout<<endl;

    }
}


int convertStr2Arr(string str, char arr[]){//returns radix point 
    int rad_pos = str.find('.');
    if(rad_pos > 0){
        str.erase(str.find('.'),1);
        rad_pos = str.length() - rad_pos;
    } else {
        rad_pos = 0; 
    } 
    strcpy(arr, str.c_str());
    return rad_pos;
}

string convertArr2Str(char arr[]){
    string S = string(arr);
    //Your code:

    reverse(S.begin(), S.end());
    S = trim(S);
    return S;
}


//YOUR ALGORITHM



int main()
{
    int T;
    cin >>T;
    int base;
    string V, M, P;

    //initiliase memo table for 36 * 36 multiplication
    for(int i=0;i<36;i++){
        for(int j=0;j<36;j++){
            memo[i][j] = i*j;
        }
    }

    for(int i = 0; i < T;i++){
        cin>>base;
        cin>>V;
        cin>>M;
        int V_rad = convertStr2Arr(V, V_arr);
        int M_rad = convertStr2Arr(M, M_arr);
        multiply(base, V_arr, M_arr);
        summation(base, strlen(V_arr), strlen(M_arr));
        string str = convertArr2Str(res);
        if(V_rad != 0 || M_rad != 0){
            cout<<V_rad<<M_rad;
            int pos = V_rad+M_rad;
            str.insert(str.length()-pos, 1, '.');
        }
        cout<<str<<endl;
    };

    return 0;


//Test correctness:
//================

    return 0;
}

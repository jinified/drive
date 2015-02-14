#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

//Constants
const string    Digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char      RADIX_POINT = '.';
const int SIZE = 5005;


//Containers
int memo[36][36];
char V_arr[SIZE] = {0};
char M_arr[SIZE] = {0};
short sum[2*SIZE+1][2*SIZE] = {0};
//char sumsmall[2*SIZE+1];
vector<char> sumsmall = vector<char>(2*SIZE+1,'0');
vector<char> res = vector<char>();

//Template
inline int valueOf(char x){ // integer value of a digit
    if ('0' <= x and x <= '9') return x - '0';
    if ('A' <= x and x <= 'Z') return x - 'A' +10;
    return 255;
};

inline char digitOf(int val){ // val must be < base <= 36
    return Digits[val];
};

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


void convertStr2Arr(string str, char arr[]){//returns radix point 
    if(str.find('.') != string::npos){
        str.erase(str.find('.'),1);
    }
    strcpy(arr, str.c_str());
}

int checkFrac(string str, int x){
    if(x == string::npos){
        return 0; 
    } else if(str[x-1] == 0 && x-1 == 0){
        return -1; 
    } else{
        return str.length() - x; 
    }
}

int getRadixPt(string A, string B){
    int a = checkFrac(A, A.find('.'));
    int b = checkFrac(B, B.find('.'));
    int len = a+b-2;
    //cout<<"A: "<<a<<" B: "<<b<<endl;
    if((a > 0) ^ (b > 0)){
        len = a > 0 ? a-1: b-1; 
    }
    //cout<<"len: "<<len<<endl;
    return len;
}

string convertArr2Str(char arr[]){
    string S = string(arr);
    reverse(S.begin(), S.end());
    S = trim(S);
    return S;
}

void summation(int base, short arr[2*SIZE+1][2*SIZE], int V_SIZE, int M_SIZE){

    res.clear();
    int count = 0;
    int carry = 0;
    int bigger = V_SIZE > M_SIZE ? V_SIZE:M_SIZE;
    for(int i=0;i<2*bigger;i++){

        int tmp = 0;
        for(int j=0; j<M_SIZE;j++){
            tmp+=arr[j][i];
        }
        tmp+=carry;
        res.push_back(digitOf(tmp%base));
        count++;
        carry = tmp/base;
    }
    if(carry > 0){
        res.push_back(carry);
    }
    //reverse the order 
    reverse(res.begin(), res.end());
}

void multiply(int base, char V[], char M[], int insert){

    //memset(sum, 0, sizeof(sum[0][0])*(2*SIZE)*(2*SIZE+1));
    //memset(sumsmall, '0', sizeof(sumsmall[0])*(2*SIZE+1));
    fill(sumsmall.begin(), sumsmall.end(), '0');
    int carry = 0, count = 0, x = 0, y = 0;

    for(int i=strlen(M)-1;i>=0;i--){

        for(int j=strlen(V)-1;j>=0;j--){

            int curr = y+count; //current index
            int prev = valueOf(sumsmall[curr]);
            int product = (memo[valueOf(V[j])][valueOf(M[i])]+carry);
            int tmp = product+prev;
            carry = tmp/base;
            sumsmall[curr] = digitOf(tmp%base);
            y++;
            //cout<<"Curr: "<<curr<<" Product: "<<sumsmall[curr]<<" Carry: "<<carry<<" Prev: "<<prev<<endl;
        }
        if(carry >0){
            int curr = y + count;
            int prev = valueOf(sumsmall[curr]);
            sumsmall[curr] = digitOf(carry);
        }
        carry = 0; 
        x++;    
        y=0;    
        count++;
    }
    if(insert > 0){
        sumsmall.insert(sumsmall.begin()+insert, '.');
    }
}

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
        int insert = getRadixPt(V,M);
        convertStr2Arr(V, V_arr);
        convertStr2Arr(M, M_arr);
        multiply(base, V_arr, M_arr, insert);
        string str = string(sumsmall.begin(), sumsmall.end());
        reverse(str.begin(), str.end());
        //string str = trim(convertArr2Str(sumsmall));
        cout<<trim(str)<<endl;
    };

    return 0;
}

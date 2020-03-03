#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <map>

using namespace std;
// this part generate prime numbers from number (f) to number (t) using Sieve Prime Algorithm
map <long long,bool> arr;
vector <long long> firstPrimes;
long long p,f,t;
ofstream primeNumberGenerated;
void init(){
    p=2;
}
void primeSeive (long long u){
    if (u==1 || u==2) return;
    for (long long i=2;i*p<=u;i++){
        arr[p*i]=1;
    }
    for (long long i=p+1;i<=u;i++){
        if (!arr[i]){
            p=i;
            break;
        }
    }
}
void primeGenerator(){
    init();
    long long pre=0;
    while(pre!=p){
        if (p!=1) firstPrimes.push_back(p);
        pre=p;
        primeSeive(ceil(sqrt(t)));
    }
    long long num=f/firstPrimes[0];
    num*=firstPrimes[0];
    p=num;
    pre=0;
    if (p==0) p=2;
    for (long long i=0;i<firstPrimes.size();i++){
        num=f/firstPrimes[i];
        num*=firstPrimes[i];
        if (num==0) continue;
        while(num<=t){
            if (num!=firstPrimes[i]) arr[num]=1;
            num+=firstPrimes[i];
        }
    }
    while(pre!=p){
        if (p>=f && p<=t && !arr[p]) primeNumberGenerated << p << endl;
        pre=p;
        primeSeive(t);
    }
}
// Public Key Exchange
long long pp,qq,nn,mm,ee,dd,kk,chperTxt;
char msg,de_msg;
long long ww;
vector <char> plainTxt;
vector <long long> pt;
ifstream infile;
long long gcd (long long x,long long y){
    if (y==0) return x;
    else return gcd(y,x % y);
}
void encryptionPublic (){
    nn=pp*qq;
    mm=(qq-1)*(pp-1);
    ee=2;
    while (gcd(mm,ee)!=1){
        ee++;
    }
    while ((mm*kk+1)%ee!=0){
        kk++;
    }
    dd=(mm*kk+1)/ee;
    infile.open ("PlainText.txt");
    while (infile>>msg){
        plainTxt.push_back(msg);
    }
    infile.close();
    primeNumberGenerated.open("cipherText.txt");
    for (long long j=0;j<plainTxt.size();j++){
        chperTxt=1;
        for (long long i=0;i<ee;i++) {
            chperTxt*=plainTxt[j];
            chperTxt=chperTxt%nn;
        }
        primeNumberGenerated << chperTxt << endl;
    }
    primeNumberGenerated.close();
}
void decryptionPublic (){
    infile.open ("cipherText.txt");
    while (infile>>ww){
        pt.push_back(ww);
    }
    infile.close();
    primeNumberGenerated.open("decryptedText.txt");
    for (long long j=0;j<plainTxt.size();j++){
        chperTxt=1;
        for (long long i=0;i<dd;i++) {
            chperTxt*=pt[j];
            chperTxt=chperTxt%nn;
        }
        de_msg=chperTxt;
        primeNumberGenerated << de_msg << endl;
    }
    primeNumberGenerated.close();
}

int main()
{
    // take to number ro generate all the primes between them
    // and print them in an external txt file called primeNumberGenerated
    // try to choose twoo number the difference between them <= 1e5
        primeNumberGenerated.open("primeNumberGenerated.txt");
        scanf("%lld%lld",&f,&t);
        primeGenerator();
        primeNumberGenerated.close();
    // choose two prime number from primeNumberGenerated.txt
        pp=1009;
        qq=1013;
        encryptionPublic();
        decryptionPublic();

    return 0;
}

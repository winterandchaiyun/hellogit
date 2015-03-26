//filename:lab1 by Jingguang Zhou
//game of guessing numbers

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int guess();

int main()
{
    char newOne;                               //newOne represents the demand of whether to start a new game.
    int gameNum=0, win=0, lose=0;

    while(true){
        cout << "Would you like to start a game?(Y/N)";
        cin >> newOne;

        if ( newOne!='Y' && newOne!='y' && newOne!='N' && newOne!='n' ) continue;   //ensure the answer to be y/Y/n/N
        if ( newOne=='N' || newOne=='n') break;
        else {
              gameNum+=1;
              if (guess()) ++win;
              else ++lose;
        }
    }
    cout << "In total,you played " << gameNum << " times,with " << win
         << " victory and " << lose << " failure." << endl;
    return 0;
}


//func:guess
//effect:simulate the whole game
int guess(){
    int originalNums[3], guessNum[3];
    int temp, i=0, numA, numB, q, w;               //q,w indicate whether there are repetitive matches
                                              //between the originalNums and the guessNum.
    srand(time(NULL));

    while(i<3) {
        bool flag=true;

        temp=rand()%10;
        for (int j=0;j<i;++j)                 //ensure no repetitive numbers and then we can put it into the array
            if ( temp==originalNums[j] ) {
                flag=false; break;}
        if (flag) {
            originalNums[i]=temp;
            cout << temp;
            ++i;}
    }

    for (int p=0;p<7;++p){
        numA=0; numB=0;
        cout << "input the three numbers you guess:";
        for (int j=0;j<3;++j){
            cin >> guessNum[j];
        }
        for (int j=0;j<3;++j){
            q=0; w=0;
            for (int p=0;p<3;++p){
                if ( originalNums[j]==guessNum[p] ){     //notice some instances:ori:123,guest:113,223,222
                    if ( j==p ) {                        //set q,w is to avoid the wrong repetitive counts.
                        if (q) --numB;
                        numA+=(1-w); w=1;}
                    else{
                        if(q||w) --numB;
                        ++numB; q=1;}
                }
            }
        }
        if ( numA==3 ){
            cout << "Congratulations.You are right!" << endl;
            return 1;}
        else  cout << numA << 'A' << numB << 'B' << endl;
    }

    cout << "I'm sorry that you didn't get the right numbers 7 times.\
            The answer is ";
    for (int j=0;j<3;++j)  cout << originalNums[j];
    cout << endl;
    return 0;
}


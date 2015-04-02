//filename:21point game
//author:Jingguang Zhou

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>

using namespace std;

float card[13]={1,2,3,4,5,6,7,8,9,10,0.5,0.5,0.5};
int cardUsed[500];
int cui=0;                    //means cardUsedIndex
float manGet[10];
float comGet[10];                          //the card got by computer


//effect:map the array to the corresponding numbers or colors
void map(int idx,int color){
    switch(color){
        case 0: cout << "heart ";break;
        case 1: cout << "diamonds ";break;
        case 2: cout << "spade ";break;
        case 3: cout << "club ";
    }
    switch(idx){
        case 10: cout << 'J';break;
        case 11: cout << 'Q';break;
        case 12: cout << 'K';break;
        case 0: cout << 'A';break;
        default: cout << idx+1;
    }
    cout << endl;
}


//effect:to generate card
float deal(){
    int idx,color;
    bool flag;

    do{
    flag=true;
    idx=rand()%13;
    color=rand()%4;
    cardUsed[cui]=idx*10+color;   //a way to compare two character at the same time
    for(int p=0;p<cui;p++)
        if (cardUsed[p]==cardUsed[cui]) {
            flag=false;break;}
    } while(!flag);

    cui++;
    map(idx,color);

    return card[idx];
}


//effect:check the validity of input
bool check(){
    char willing[20];                        //use character string in case of repetitive reminding
    int except=1;
    try{
        cin >> willing;
        if ( (strcmp(willing,"N")==0) || (strcmp(willing,"n")==0) ) return false;
        else if ((strcmp(willing,"y")==0) || (strcmp(willing,"Y")==0)) return true;
            else throw except;
    }
    catch(int){
        cout << "Please input the proper data(y/n):";
        return check()      //input again
    }
}


//effect:to give the rules and judge who wins
int judge(){
    int i,j;
    float manSum,comSum;
    srand(time(NULL));

    cout << "Here are your cards:" <<endl;
    manGet[0]=deal();
    manGet[1]=deal();
    i=2;
    manSum=manGet[0]+manGet[1];

    while(true){                                       //show the rules of game
        cout << "would you like another card(y/n)?";
        if (check()) {
            manGet[i]=deal();
            manSum += manGet[i++];
            if (manSum>21) {
                cout << "your grades exceed 21!" <<endl;
                return 0;}
        }
        else break;
    }

    cout << "\nHere are computer's cards:" <<endl;
    comGet[0]=deal();
    comGet[1]=deal();
    comSum=comGet[0]+comGet[1];
    j=2;

    while(comSum<manSum||comSum<=11){                        //a strategy of the computer.
        comGet[j]=deal();                                   //In case that both get 10 points and then the computer stops
        comSum += comGet[j++];
        if (comSum>21) {
            cout << "Computer's grades exceed 21!" <<endl;
            return 1;}
    }
    cout << "\nyour grades:" << manSum <<endl;
    cout << "Computer's cards:" <<comSum <<endl;
    if (comSum>manSum) return 0;
    if (comSum==manSum){
        if (i==j) return -1;
        else if (i>j) return 1;
            else return 0;
    }
}

//effect:output and ask whether to start again
int main(){
    int op;
    bool continual=1;

    while(continual){
        cui=0;                                                    //restart to set up the cardUsed from index 0 
        op=judge();
        switch(op){                                         //show the corresponding result
            case 1:cout << "You win!" <<endl;break;
            case 0:cout << "You lose!" <<endl;break;
            case -1:cout << "It is a tie!" <<endl;
        }
        continual=0;
        cout << "\nWould you start the game again?(y/n)";
        continual=check();
    }

    return 0;
}


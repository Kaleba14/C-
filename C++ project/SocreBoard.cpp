#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <string>
using namespace std;

struct rec{
    string name;
    int score;
};

vector<rec> ls;

void list_generation(){
    rec p1;

    ifstream records("Login\\User_list.txt");
    string name;
    while(getline(records, name)){
        ifstream coll("Login\\"+name);
        int a = 1;
        string input;
        while(getline(coll,input)){
            if(a == 1){
                p1.name = input;
            }
            if(a == 3){
                p1.score = stoi(input);
                ls.push_back(p1);
                break;
            }
            a++;
        }
        coll.close();        
    } 
    records.close();
}

void sort_list(){
    int j;
    for(int i = 0; i < ls.size(); i++){
    j = 0;
    while(j < ls.size()){
        if(ls[i].score > ls[j].score){
            swap(ls[i],ls[j]);
        }
        j++;
    }

    }
}

void score(){
    system("cls");
    list_generation();
    sort_list();

    string s;
    ifstream title("123.txt");
    while(getline(title,s)){
            cout << "                        " <<  s << endl;
    }   
    title.close();

    cout << setw(50) << ls[1].name << setw(30) << ls[0].name << setw(30) << ls[2].name << endl;
    cout << setw(49) << ls[1].score << setw(30) << ls[0].score << setw(30) << ls[2].score << endl;
    if(ls.size() > 3){
        cout << '\n' << setw(100) << "Number)--------- Player name --------- Score" << endl;
        for(int a = 3; a < ls.size(); a++){
            cout << setw(60) << a+1 << ")--------------- " <<  ls[a].name << "-------------" << ls[a].score << endl;
        }
    }
    ls.clear();
    cout << '\n' << setw(84) << "Continue.....";
    cin.get();
}
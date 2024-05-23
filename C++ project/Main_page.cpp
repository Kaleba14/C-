#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include "Single_Player_mode.cpp"
#include "SocreBoard.cpp"
#include "Login\\Passcode.cpp"
using namespace std;

void selection(char sel);
int scale();
double Level();
void Display_grid(int size);
void grid_display_5_by_5(int size);
void grid_display_7_by_7(int size);
void grid_display_10_by_10(int size);


int main(){
    do{
    system("cls");
    ifstream menu("Options.txt"), logo("Logo.txt");
    string s;
        // logo printout
        while(getline(logo, s)){
            cout << s << endl;
        }
        // option printout
        cout << endl;
        while(getline(menu,s)){
            cout << s << endl;
        }
    menu.close();
    string choice;
    cout << endl;
    do{
        cout << setw(64) << "Enter in your choice : ";
        getline(cin, choice);
        if((choice[0] >= '1'&& choice[0] <= '5') && choice.length() == 1){
            break;
        }
        cout << setw(68) << "====> Invalid Input <======" << endl;
    }while(true);
    system("cls");
        if(choice[0] == '5'){
            system("cls");
            break;
        }
        char selec = choice[0];
    selection(selec);
    }while(true);
    return 0;
}

void selection(char sel){
    
    if(sel == '1'){
        int val = scale();
        double dif = Level();
        first_select(val, dif);
    }else if(sel == '2'){
        score();
    }else if(sel == '3'){
        players_info();
    }else if(sel == '4'){
        system("cls");
        
        ifstream ifile;
        ifile.open("game_info.txt");
        string value;
   
        while (getline(ifile, value)){
        cout << value << endl;
        }
       ifile.close();

       cout << '\n' << setw(84) << "Continue.....";
        cin.get();
    }else{
        
    }
}

int scale(){
    string display;
    int size[] = {5,7,10};
    ifstream scale_display("Scale.txt");
        while(getline(scale_display,display)){
            cout << "       " << display << endl;
        }
    scale_display.close();
    cout << '\n' << endl;
    cout << setw(53) << "1) 5 by 5" << setw(15) << " 2) 7 by 7" << setw(16) << " 3) 10 by 10" << endl;
    string scale_size_choice;
    while(true){
        cout << '\n' << setw(50) << "=====>";
        cout << setw(25) << "Select a scale size : ";
        getline(cin,scale_size_choice); 
        if((scale_size_choice.length() == 1) && (scale_size_choice[0] >= '1' && scale_size_choice[0] <= '3')){
            break;
        }
        cout << "Invalid Selection" << endl;
    }
    return (size[stoi(scale_size_choice) - 1]);
}

double Level(){
    bool track = false;
    string scale_size_choice;
    
    while(true){
        system("cls");
        string display;
        ifstream difficulty_display("Difficulty.txt");
        int a = 1;
        while(getline(difficulty_display,display)){
            if(a == 32){
                cout << "     |" << display;
                getline(cin,scale_size_choice); 
            }else if(a == 27 && track){
                cout << "     |" << display;
                cout << "Invalid Selection" << endl;
            }else{
                cout << "     |" << display << endl;
            }            
            a++;
        }
        difficulty_display.close();
        if((scale_size_choice[0] >= '1' || scale_size_choice[0] <= '4') && scale_size_choice.length() == 1){
            break;
        }
        track = true;
    }
    if(scale_size_choice[0] == '1'){
        return 0.25;
    }else if(scale_size_choice[0] == '2'){
        return 0.5;
    }else if(scale_size_choice[0] == '3'){
        return 0.75;
    }else{
        return 1.0;
    }   
}
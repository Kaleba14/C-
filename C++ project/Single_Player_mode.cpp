#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

struct player_info{
    string name, hash, point;
};

vector<char> GRID;
vector<int> random;
vector<int> players_moves;

void set_space(int size);
void generat(int n, double level);
void game_mode(int &points, int scale, double level);
void grid_selector(int val);
void grid_display_5_by_5(int size);
void grid_display_7_by_7(int size);
void grid_display_10_by_10(int size);

void first_select(int scale, double mode){
    string choice;
    cout << '\n' << '\n' << endl;
    system("cls");
    int location, val;
    do{
        cout << setw(76) << "Play As" << endl;
        cout << setw(70) << "__________" << setw(15) << "_________" << endl;
        cout << setw(86) << " | 1) Guest | Or | 2) User |" << endl;
        cout << setw(70) << "----------" << setw(15) << "---------" << endl;
        cout << setw(77) << "Enter Choice : ";
        getline(cin, choice);

        if((choice == "1" || choice == "2") && choice.length() == 1){
            break;
        }
        system("cls");
        cout << setw(75) << "Invalid choice" << '\n' << endl;
    }while(true);
    string username, s;
    if(choice == "2"){

        // User authentication part 1 (This confirms if the users account is registered)
        do{
            system("cls");
            string fc;
            ifstream face("Autentication.txt");
            while(getline(face,fc)){
                cout << fc << endl;
            }
            face.close();
            cout << setw(59) << "====>  ";
            cout << "Enter in your username : ";
            getline(cin, username);
            bool found = false;
            location = 1;
            ifstream look("Login\\User_list.txt");
            if(look){
                while(getline(look, s)){
                if(username == s){
                    found = true;
                    break;
                }
                location++;
            }
            }else{
                cout << "File is not opened" << endl;
            }
            look.close();
        
            if(found){
                break;
            }else{
                cout << '\n' << setw(83) << "Username is not found " << endl;
                string retry;
                do{
                    cout << setw(80) <<"Try Again (Y/N) : ";
                    getline(cin, retry);
                    if((retry.length() == 1) && (retry == "Y" || retry == "y" || retry == "N" || retry == "n")){
                        break;
                    }
                    cout << "Invalid Input" << endl;
                }while(true);

                if(retry == "N" || retry == "n"){
                    goto end;
                }
            }   
        }while(true);
        
         /*
            Retention of the information about the player
            the information are as follows:
                - user name
                - user hash
                - player score
        */
        player_info player;
        string var;
        int a = 1;
        ifstream hold("Login\\"+username);
        if(hold){
            while(getline(hold, var)){
                if(a == 1){
                    player.name = var;
                }else if(a == 2){
                    player.hash = var;
                }else{
                    player.point = var;
                }
                a++;
            }
        }
        hold.close();

        // User Authentication part 2
        /*
            Password Control, If the user account has been identified  within
            the user list the second part to the authentication is for the 
            password to be conofirmed 
        */  
        do{
            system("cls");
            string fc;
            ifstream face_p2("Autentication.txt");
            while(getline(face_p2,fc)){
                cout << fc << endl;
            }
            face_p2.close();
            string passcode;
            cout << setw(59) << "====>  ";
            cout << "Enter in your username : " << "--Confirmed--" << endl;
            cout << setw(59) << "====>  ";
            cout << "Enter in your password : ";
            getline(cin, passcode);

            bool found = false;
            int local = 1;
            ifstream position("Login\\Masterkey.txt");
            if(position){
                while(getline(position, s)){
                    if(local == location){
                        break;
                    }
                    local++;
                }
            }else{
                cout << "File is not opened" << endl;
            }
            position.close();

            string recompose = "";
            map<char,int> match;
            match['0'] = 0;match['1'] = 1;match['2'] = 2;match['3'] = 3;match['4'] = 4;
            match['5'] = 5;match['6'] = 6;match['7'] = 7;match['8'] = 8;match['9'] = 9;
    
            for(int a = 0; a < player.hash.length(); a++){
                char change = player.hash[a] - match[s[a]];
                recompose = recompose + change;
            }
            
            found = (passcode == recompose) ? true : false;
        
            if(found){
                break;
            }else{
                cout << '\n' << setw(83) << "Incorrect Password" << endl;
                string retry;
                do{
                    cout << setw(80) <<"Try Again (Y/N) : ";
                    getline(cin, retry);
                    if((retry.length() == 1) && (retry == "Y" || retry == "y" || retry == "N" || retry == "n")){
                        break;
                    }
                    cout << "Invalid Input" << endl;
                }while(true);

                if(retry == "N" || retry == "n"){
                    goto end;
                }
            }   
        }while(true);

       

        string con;
        val = stoi(player.point);
        do{
            game_mode(val, scale, mode);
            do{
                cout << setw(85) << "Do you want to continue (Y/N): ";
                getline(cin, con);
                if( con.length() == 1 && (con == "Y" ||con == "y" || con == "N" ||con == "n")){
                    break;
                }
                cout << setw(80) << "Invalid Input" << endl;
            }while(true);
            
            if(con == "N" ||con == "n"){
                cout << setw(80) << "Your score is now " << val << endl;
                break;
            }
            GRID.clear();
            random.clear();
        }while(true);
        ofstream putdown("Login\\"+username);
        putdown << player.name << endl;
        putdown << player.hash << endl;
        putdown << val << endl;
        putdown.close();
    }else{
        val = 0;
        string con;
        do{
            game_mode(val, scale, mode);
            do{
                cout << setw(85) << "Do you want to continue (Y/N): ";
                getline(cin, con);
                if( con.length() == 1 && (con == "Y" ||con == "y" || con == "N" ||con == "n")){
                    break;
                }
                cout << setw(80) << "Invalid Input" << endl;
            }while(true);
            
            if(con == "N" ||con == "n"){
                break;
            }
            GRID.clear();
            random.clear();
            players_moves.clear();
        }while(true);
    }
    
    end:
    
    system("cls");
    string strack;
    ifstream game_done("Game_Over.txt");
    while(getline(game_done,strack)){
        cout << strack << endl;
    }
    game_done.close();
    
    cout << setw(40) << "Your Final Score is " << val << endl;
    cout << '\n' << setw(30) << "Continue .........";
    cin.get();
    system("cls");
}

void game_mode(int &points, int scale, double level){
    set_space(scale);
    generat(scale, level);
    int varied = 0;
    bool str = true;
    do{
        system("cls");
        grid_selector(scale);
        re_enter:
        // for(int a = 0; a <random.size(); a++){
        //     cout << random[a] << " ";
        // }
        cout << endl;
        cout << setw(83) << "Current score : " << varied << endl;
        // cout << players_moves.size() << " " << GRID.size() << " " << random.size() << endl;
        string s;
        int col, row;
        do{
            cout << setw(85) << "Select a letter from A to "<< char('A' + scale -1) <<" : ";
            getline(cin, s);
            if(((s[0] >= 'A' && s[0] <= 'A' + scale - 1) || (s[0] >= 'a' && s[0] <= 'a' + scale - 1)) && (s.length() == 1)){
                break;
            }
            cout << setw(76) << "Invalid input" << endl;
        }while(true);
        
        if(s[0] >= 'A' && s[0] <= 'A' + scale - 1){
            col = int(s[0]) - 64;
        }else{
            col = int(s[0]) - 96;
        }

        do{
            cout << setw(86) << "Select a number between 1 to "<< scale << " : ";
            getline(cin,s);
            if((s[0] >= '1' && s[0] <= '1' + scale - 1) && (s.length() <= 2)){
                if((s.length() == 2 && s[0] == '1' && s[1] == '0')|| s.length() == 1){
                    break;
                }
            }
            cout << setw(76) << "Invalid Input" << endl;
        }while(true);
        if(s.length() == 2){
            if(s.length() == 2){
                row = 10;    
            }else{
                row = int(s[0]) - 48;
            }
        }else{
            row = int(s[0]) - 48;
        }

        // the below commented code displays the colum and row selected
        // cout << "colum = "<< col << " row = " << row << endl;
        int index = ((row - 1)*(scale)+ col-1);
        
        // the below commented code displays the index value
        // cout << "Index = " << index <<endl;


        for(int a = 0; a < random.size(); a++){
            if(random[a] == index){
                str = false;
                break;
            }
        }

        if(!players_moves.empty()){
            for(int a = 0; a < players_moves.size(); a++){
                if(index == players_moves[a]){
                    system("cls");
                    grid_selector(scale);
                    cout << setw(97) << "Enter a position that hasnt been entered !!!" << endl;
                    goto re_enter;
                }
            }
        }

        GRID[index] = 'O';
        if(str){
            varied += 5;
            players_moves.push_back(index);
        }

        if(players_moves.size() == (GRID.size() - random.size()) && level != 1.0){
            cout << "Congratulation you have won" << endl;
            cout << "Continue.....";
            cin.get();
            varied += 100;
            return;
        }
    }while(str);
    system("cls");
    for(int a = 0; a < random.size(); a++){
            GRID[random[a]] = 'X';   
    }
    grid_selector(scale);
    cout << setw(80) << "You have hit a bomb :(" << endl;

    points += varied;
}

void grid_selector(int val){
    if(val == 5){
        grid_display_5_by_5(5);
    }else if(val == 7){
        grid_display_7_by_7(7);
    }else{
        grid_display_10_by_10(10);
    }
}

void set_space(int n){
    for(int a = 0; a < n*n;a++){
        GRID.push_back(' ');
    }
}

void generat(int n, double level){
    srand(static_cast<unsigned>(time(0)));
    int r = rand() % (n*n), b;
    if(level < 1){
        b = (n*n) * level;
    }else{
        for(int a = 0; a < n*n; a++){
            random.push_back(a);
        }
        return;
    }
    random.push_back(r);
    while(true){
        back:
        r = rand() % (n*n);
        
        for(int a = 0; a < random.size(); a++){
            if(random[a] == r){
                goto back;
            }
        }
        random.push_back(r);
        if(random.size() == b){break;}
    }
}

void grid_display_5_by_5(int size){
    cout << '\n' << '\n' << setw(26);   
     char col = 'A';
    cout << setw(26);
    for(int a = 0; a < 13*size + 4; a++){
        cout << "_";
    }
    cout << endl;
        for(int a = 1; a<=3; a++){
            if(a == 1){
                cout << setw(38);
                for(int a = 0; a < size; a++){
                    cout << "|             ";
                }
                cout << "|" << endl;
            }
            if(a == 2){
                cout << setw(31);
                
                for(int a = 0; a < size; a++){
                    cout << "|      "<< col++ <<"      ";
                }
                cout << "|" << endl;
            }
            if(a == 3){
                cout << setw(24) << "________";
                for(int a = 0; a < size; a++){
                cout << "|_____________";
                }
                cout << "|";
            }
        }
    cout << endl;
    int b = -1;
    for(int i = 1; i <= size; i++){
        for(int j = 1; j <= 5; j++){
            if(j == 1 || j == 2 || j == 4){
                cout << setw(24) << "|        ";
                for(int a = 0; a < size; a++){
                    cout << "|             ";
                }
                cout << "|";
            }
            if(j == 3){
                cout << setw(19) << "|   "<< i << "    ";
                    while(b < size*size){
                        b++;
                        cout << "|      " << GRID[b] << "      ";
                    if((b+1)%size == 0){
                        break;
                    }
                    }
                    cout << "|";
            }
            if(j == 5){
                cout << setw(24) << "|________";
                for(int a = 0; a < size; a++){
                cout << "|_____________";
                }
                cout << "|";
            }
            cout << endl;
        }
    }
    cout << '\n' << endl;
}

void grid_display_7_by_7(int size){
    cout << '\n' << '\n' << endl;
    char col = 'A';
    cout << setw(38);
    for(int a = 0; a < 10*size + 6; a++){
        cout << "_";
    }
    cout << endl;
        for(int a = 1; a<=3; a++){
            if(a == 1){
                cout << setw(47);
                for(int a = 0; a < size; a++){
                    cout << "|          ";
                }
                cout << "|" << endl;
            }
            if(a == 2){
                cout << setw(42);
                
                for(int a = 0; a < size; a++){
                    cout << "|     "<< col++ <<"    ";
                }
                cout << "|" << endl;
            }
            if(a == 3){
                cout << setw(36) << "________";
                for(int a = 0; a < size; a++){
                cout << "|__________";
                }
                cout << "|";
            }
        }
    cout << endl;
    int b = -1;
    for(int i = 1; i <= size; i++){
        for(int j = 1; j <= 3; j++){
            if(j == 1 ){
                cout << setw(36) << "|        ";
                for(int a = 0; a < size; a++){
                    cout << "|          ";
                }
                cout << "|";
            }
            if(j == 2){
                cout << setw(31) << "|   " << i << setw(10);
                    while(b < size*size){
                        b++;
                        cout << "|     " << GRID[b] << "    ";
                    if((b+1)%size == 0){
                        break;
                    }
                    }
                    cout << "|";
            }
            if(j == 3){
                cout << setw(36) << "|________";
                for(int a = 0; a < size; a++){
                cout << "|__________";
                }
                cout << "|";
            }
            cout << endl;
            }
        }
        cout << '\n' << '\n' << endl;
    
}

void grid_display_10_by_10(int size){
    cout << '\n' << '\n' << '\n' << endl;
    char col = 'A';
    cout << setw(32);
    for(int a = 0; a < 5*size + 9; a++){
        cout << "_";
    }
    cout << endl;
        for(int a = 1; a<=3; a++){
            if(a == 1){
                cout << setw(36);
                for(int a = 0; a < size; a++){
                    cout << "|     ";
                }
                cout << "|" << endl;
            }
            if(a == 2){
                cout << setw(33);
                
                for(int a = 0; a < size; a++){
                    cout << "|  "<< col++ <<"  ";
                }
                cout << "|" << endl;
            }
            if(a == 3){
                cout << setw(30) << "____";
                for(int a = 0; a < size; a++){
                cout << "|_____";
                }
                cout << "|";
            }
        }
    cout << endl;
    int b = -1;
    for(int i = 1; i <= size; i++){
        for(int j = 1; j <= 3; j++){
            if(j == 1 ){
                cout << setw(30) << "|    ";
                for(int a = 0; a < size; a++){
                    cout << "|     ";
                }
                cout << "|";
            }
            if(j == 2){
                if(i != 10){
                    cout << setw(27) << "| " << i << setw(5);
                }else{
                    cout << setw(27) << "| " << i << setw(4);
                }
                    while(b < size*size){
                        b++;
                        cout << "|  " << GRID[b] << "  ";
                    if((b+1)%size == 0){
                        break;
                    }
                    }
                    cout << "|";
            }
            if(j == 3){
                cout << setw(30) << "|____";
                for(int a = 0; a < size; a++){
                cout << "|_____";
                }
                cout << "|";
            }
            cout << endl;
            }
        }
        cout << '\n' << '\n' << endl;
}
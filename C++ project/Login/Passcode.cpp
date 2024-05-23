#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <cmath>
#include <map>

using namespace std;

struct pass{
    string hash, key;
};

struct details{
    string name, user, score;
};

void Selection(char d);
void System_access();
void System(string username, int pos);
void adduser();
pass encryption(string password);
bool decryption(string username, string pass, int pos);
void delete_account(string username, int pos);

void players_info(){
        system("cls");
    ifstream header("Login\\Top_display.txt");
    string s;
    int n = 1;
    while(getline(header,s)){
        if(n == 12){
            cout << "       " << s;
            cout << setw(10) << "1) Login" << endl;   
        }else if(n == 14){    
            cout << "       " << s;
            cout << setw(24) << "2) Sign Up" << endl; 
        }else if(n == 16){   
            cout << "       " << s;

        }else{
            cout << "       " << s << endl;
        }
        n++;
    }
    header.close();
    string input_choice;
    do{
        cout <<  setw(25) << "Enter in your choice : ";
        getline(cin, input_choice);
        if(input_choice[0] == '1' || input_choice[0] == '2'){
            break;
        }
        cout << "Invalid Input" << endl;
    }while(true);
    char div;
        if(input_choice[0] == '1'){
            div = input_choice[0];
        }else{
            div = input_choice[0];
        }
    Selection(div);

}

void Selection(char d){
    if(d == '1'){
        System_access();
    }else{
        adduser();
    }
}
void System_access(){
    string username, password;
    bool S_A = false;
    int pos = 1;
    do{
        system("cls");
        string print_face;

        ifstream face("Login\\Autentication.txt");
        while(getline(face,print_face)){
            cout << print_face << endl;
        }
        face.close();

        cout << setw(80) << "Enter in your Username : ";
        getline(cin, username);
        bool name_found = false;
        ifstream isthere("Login\\User_list.txt");
        string listed_name;

        while(getline(isthere,listed_name)){
            if(username == listed_name){
                name_found = true;
                break;
            }
            pos++;
        }
        isthere.close();
        
        if(name_found){
            do{
                cout << '\n' << setw(80) << "Enter in your password : ";
                getline(cin , password);
                if(decryption(username, password, pos)){
                    cout << "System Access granted" << endl;
                    S_A = true;
                    break;
                }
                cout << "Invalid Password" << endl;

                do{
                    string type_again;
                    cout << "Try again (Y/N) : ";
                    getline(cin,type_again);

                    if(type_again[0] == 'N' || type_again[0] == 'n'){
                        return;
                    }else if(type_again[0] == 'Y' || type_again[0] == 'y'){
                        break;
                    }else{
                        cout << "Invalid choice" << endl;
                    }
    
                }while(true);
            }while(true);
        }else{
            cout << "Username Not identified in the systems registory" << endl;
        }

        if(S_A){
            break;
        }
    }while(true);
    system("cls");
    System(username, pos);
}

void adduser(){
    string name, username, password;
    system("cls");

    string s;

    ifstream face("profile_case.txt");
    while(getline(face,s)){
        cout << s << endl;
    }
    face.close();

    cout << '\n' << setw(15) << "======>";
    cout << setw(25) << " Enter in your name : ";
    getline(cin, name);
    bool unique;
    do{
        unique = true;
        cout << '\n' << setw(15) << "======>";
        cout << setw(29) << "Enter in your username : ";
        getline(cin, username);
        
        string com;
        ifstream compare("User_list.txt");
        while(getline(compare,com)){
            if(username == com){
                cout << "Username has already been taken" << endl;
                unique = false;
                break;
            }
        }
    }while(!unique);
    
    do{
        cout << '\n' << setw(53) <<"Enter in your password (15 characters or less) : ";
        getline(cin, password);
        if(password.length() <= 15){
            break;
        }
        cout << setw(74) << "# Password is Beyond Character Limit #" << endl;
    }while(true);

    string decision;
    do{
        cout << '\n' << setw(55) << "Do You Want To Create This Account (yes / no): ";
        getline(cin, decision);
        if(decision == "Yes" || decision == "yes" || decision == "No" || decision == "no"){
            break;
        }
        cout << "Invalid Response" << endl;
    }while(true);

    if(decision == "Yes" || decision == "yes"){
        ofstream newAddOn ("Login\\User_list.txt", ios::app);
        newAddOn << username << endl;
        newAddOn.close();

        pass new_User = encryption(password);
        ofstream newEnterance("Login\\" + username);
        newEnterance << name << endl;
        newEnterance << new_User.hash << endl;
        newEnterance << 0 << endl;
        newEnterance.close();
    }else{
        cout << "Alright Command Executed" << endl;
    }
}
pass encryption(string password){
    pass p;
    p.hash = "";
    srand(static_cast<unsigned>(time(0)));
    unsigned long long int n = 0;
    for(int a = 0; a < password.length(); a++){
        int r = rand() % 10;
        char new_char = password[a] + r;
        p.hash = p.hash + new_char;
        n = (n*10) + r;
    }
    p.key = to_string(n);
    ofstream fin("Login\\Masterkey.txt", ios::app);
        fin << p.key << endl;
    fin.close();
    return p;
}

bool decryption(string username, string pass, int pos){
    string hash, key_holder;
    ifstream getback("Login\\" + username);
    int count = 1;
    while(getline(getback, hash)){
        if(count == 2){
            break;
        }
        count++;
    }
    getback.close();
    
    count = 1;
    ifstream detect("Login\\Masterkey.txt");
    while(getline(detect, key_holder)){
        if(count == pos){
            break;
        }
        count++;
    }
    detect.close();
    string recompose = "";
    map<char,int> match;
    match['0'] = 0;match['1'] = 1;match['2'] = 2;match['3'] = 3;match['4'] = 4;
    match['5'] = 5;match['6'] = 6;match['7'] = 7;match['8'] = 8;match['9'] = 9;
    
    for(int a = 0; a < hash.length(); a++){
        char change = hash[a] - match[key_holder[a]];
        recompose = recompose + change;
    }
    cout << recompose << endl;
    if(recompose == pass){
        return true;
    }else{
        return false;
    }
}
void delete_account(string username, int pos){
    string decision;
    do{
        cout << "Are you sure you want to deleting this account (Y/N): ";
        getline(cin, decision);

        if((decision == "Y" || decision == "y" || decision == "N" || decision == "n") && (decision.length() == 1)){
            break;
        }
        cout << "Invalid inpu, Please use the provided choices" << '\n' << endl;
    }while(true);

    if(decision == "Y" || decision == "y"){
        string switch_string, pass_switch;

        /*
         The below blocks are present to create new lists whenever a singluar
         user account wants to delete
        */

       // This is for the username list registry
        ofstream fin("Login\\New_userlist.txt", ios::app);
        ifstream fout("Login\\User_list.txt");
        while(getline(fout, switch_string)){
            if(switch_string != username){
                fin << switch_string << endl;
            }
        } 
        fout.close();
        fin.close();
        remove("Login\\User_list.txt");
        rename("Login\\New_userlist.txt","Login\\User_list.txt");

        // This is for the Masterkey registry
        ofstream fin2("Login\\New_Masterkey.txt", ios::app);
        ifstream fout2("Login\\Masterkey.txt");
        int n = 1;
        while(getline(fout2, pass_switch)){
            if(n != pos){
                fin2 << pass_switch << endl;
            }
            n++;
        }
        fout2.close();
        fin2.close();

        remove("Login\\Masterkey.txt");
        rename("Login\\New_Masterkey.txt","Login\\Masterkey.txt");

    }else{
        cout << "Terminating execution" << endl;
    }

}

void System(string username, int pos){
    
    details ls;
    string input;
    ls.user = username;
    ifstream detals("Login\\" + username);
    int a = 1;
    while(getline(detals, input)){
        if(a == 1){
            ls.name = input;
        }
        if(a == 3){
            ls.score = input;
            break;
        }
        a++;
    }
    detals.close();

    
    do{
    string print_face;
    ifstream face2("Autentication.txt");
        while(getline(face2,print_face)){
            cout <<  print_face << endl;
        }
    face2.close();

    cout << setw(75) << "| Username |" << endl;
    cout << setw(68) << "===>   " << ls.user << "   <===" << endl;
    cout << '\n' << setw(60) << "Name : " << ls.name << setw(18) << "Score : " << ls.score << endl;

    cout << '\n' << setw(76) << "System Options" << endl;
    cout << setw(78) << "1) Delet account   " << endl;
    cout << setw(88) << "2) Exit Player Information   " << endl;

    string dec;
    cout << '\n' << setw(73) << " Selection : ";
    getline(cin,dec);
        if((dec.length() == 1) && (dec[0] >= '1' && dec[0] <= '2')){
            if(dec == "1"){
                string an;
                do{
                    cout << "Do you want to delet your account (Y/N): ";
                    getline(cin, an);

                if((an.length() == 1) && (an == "Y" || an == "y" || an == "N" || an == "n" )){
                    break;
                }
                cout << "Invalid Input" << endl;
                
                }while(true);

                if(an == "y"){
                    delete_account(username, pos);
                }else{
                    cout << "Okay :)" <<endl;
                }
            }else{
                break;  
            }
            system("cls");
        }else{
            system("cls");
            cout << setw(60) << "Invalid Input " << endl;
        }

    }while(true);
}
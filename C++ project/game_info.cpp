#include<iostream>
#include<fstream>
#include<string.h>
#include<cstring>
#include<iomanip>
#include<vector>
#include<string>


using namespace std;

void gameinfo(){
    
    ifstream ifile;
    ifile.open("game_info.txt");

   string value;
   
   while (getline(ifile, value))
   {
        cout << value << endl;
   }
   ifile.close();  
}

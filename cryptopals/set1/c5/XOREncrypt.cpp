/**
*
*    Author: Juan Carlos Ramirez
*
*    This program will encrypt a body of text with a 
*    repeating key XOR.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <fstream>
using namespace std;

int main(int argc, char** argv){

  if(argc < 2){
    cerr << "Usage: " << argv[0] << " <key> OPTIONAL: <text>" << endl;
    return -1;
  }

  int keyPos = 0;
  string text;
  if(!(argc > 2)){

    string res;
    do{   
      cout << "Encrypt a File? (y/n) ";
      cin >> res;
    }while(!(res == "y" | res == "n"));

    if(res == "y"){
      ifstream inFile;
      string fileName;

      //Grab file info
      do{
        cout << "Enter File Name:";
        cin >> fileName;
        inFile.open(fileName.c_str());
      }while(!inFile);

      for(string curLine; inFile >> curLine;){
        text.append(curLine);
      }

    }else{
      cout << "Enter text: ";
      cin.ignore();
      getline(cin,text);
    }

  }else{
    text.assign(argv[2]);
  }

  for(int i = 0; i < text.size(); i++){
    int curStringChar = text.c_str()[i];
    int curKeyChar = argv[1][keyPos];
  
    cout << setfill('0')  << setw(2) << hex << (curStringChar ^ curKeyChar);

    
    keyPos = (keyPos + 1) % strlen(argv[1]);
  }

  cout << endl;

  return 0;
}

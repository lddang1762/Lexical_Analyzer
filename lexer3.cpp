#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>

using namespace std;

ifstream inFile;

vector<string> keywords = {"int", "float", "bool","else","then","endif","while","whileend","do","doend",
                            "for","forend","input","output","and","or","function"};
vector<char> separators = {'\'', '(', ')', '{', '}', '[', ']', ',' , '.',':',';'};// ! and ' '(space) are special case
vector<char> operators = {'*', '+', '-', '=', '/', '>', '<', '%'};



void lexer();
void readfile();
int char_to_col(char c);
int transitionState(int state, char c);
bool isAcceptedState(int state);


int main(int argc, char* argv[]){
  readfile();
  lexer();
  inFile.close();
  return 0;
}

void lexer(){
  do{
    
  }while(!inFile.eof());
}

int char_to_col(char c){
  return 0;
}

int transitionState(int state, char c){
  return 0;
}

bool isAcceptedState(int state){
  return true;
}

void readfile(){
  string fname = "";
  cout << "Enter file name: ";
  cin >> fname;
  try{
    inFile.open(fname);
    if(!inFile.is_open()){
      string err = "Error: File failed to open.\n";
      throw err;
    }
  }
  catch(string e){
    cout << e;
    exit(0);
  }
}

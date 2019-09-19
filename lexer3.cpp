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
int transitionState(int state, char c);
bool isAcceptedState(int state);


int main(int argc, char* argv[]){
  readfile();
  lexer();
  inFile.close();
  return 0;
}

void lexer(){

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

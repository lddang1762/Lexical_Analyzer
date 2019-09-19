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
bool isTerminating(char c);
bool isOperator(char c);
bool isSeparator(char c);
bool isKeyword(string tok);

int main(int argc, char* argv[]){
  readfile();
  lexer();
  inFile.close();
  return 0;
}

void lexer(){
  bool tokenFound = false;
  string token = "";
  char c;
  // while(!inFile.eof()){
  //   inFile.get(c);
  //   cout << c;
  // }
  do{
    inFile.get(c);
    if(isTerminating(c)){
      if(c == '!'){
        inFile.get(c);
        while(c != '!'){
          inFile.get(c);
        }
      }
      else if(isOperator(c)){
        token += c;
        printf("%-15s %-25s\n", "operator", token.c_str());
        token = "";
      }
      else if(isSeparator(c)){
        if(token.length() == 0){
          token += c;
          printf("%-15s %-25s\n", "separator", token.c_str());
          token = "";
        }
        else{
          if(isKeyword(token)){
            printf("%-15s %-25s\n", "keyword", token.c_str());
          }
          else{
            printf("%-15s %-25s\n", "identifier", token.c_str());
          }
          token = "";
        }
      }
    }
    //need to implement states and table to know if number or identifier
    if(isalnum(c) || c == '$'){
      token += c;
    }
    else if((c == ' ' || c == '\n') && (token.length() != 0)){
      if(isKeyword(token)){
        printf("%-15s %-25s\n", "keyword", token.c_str());
      }
      else{
        printf("%-15s %-25s\n", "identifier", token.c_str());
      }
      token = "";
    }
  }while ( !inFile.eof() );
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

bool isTerminating(char c){
    if(c == ' ' || c == '!' || isOperator(c) || isSeparator(c)){
      return true;
    }
    return false;
}

bool isOperator(char c){
  for(auto iter = operators.begin(); iter != operators.end(); iter++){
    if(c == *iter){
      return true;
    }
  }
  return false;
}

bool isSeparator(char c){
  for(auto iter = separators.begin(); iter != separators.end(); iter++){
    if(c == *iter){
      return true;
    }
  }
  return false;
}

bool isKeyword(string tok){
  for(auto iter = keywords.begin(); iter != keywords.end(); iter++){
    if(tok == *iter){
      return true;
    }
  }
  return true;
}

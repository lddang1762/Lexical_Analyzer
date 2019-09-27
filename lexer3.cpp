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
int DSM_table[9][8] = { {2, 4, 8, 9, 1, 1, 6, 4},
                      {2, 2, 3, 3, 3, 2, 3, 3},
                      {1, 1, 1, 1, 1, 1, 1, 1},
                      {5, 4, 5, 5, 5, 5, 5, 4},
                      {1, 1, 1, 1, 1, 1, 1, 1},
                      {6, 6, 6, 6, 6, 6, 7, 6},
                      {1, 1, 1, 1, 1, 1, 1, 1},
                      {1, 1, 1, 1, 1, 1, 1, 1},
                      {1, 1, 1, 1, 1, 1, 1, 1}
                    };

void lexer();
void readfile();
int char_to_col(char c);
int transitionState(int state, char c);
bool isAcceptedState(int state);
bool isTerminating(char c);
bool isOperator(char c);
bool isSeparator(char c);
bool isKeyword(string tok);
void analyzeToken(string tok, int state);

int main(int argc, char* argv[]){
  readfile();
  lexer();
  inFile.close();
  return 0;
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

void lexer(){
  int currentState = 1;
  string token = "";
  char c;
  do{
    inFile.get(c);
    if(isAcceptedState(currentState)){
      analyzeToken(token, currentState);
      inFile.unget();
      currentState = 1;
      token = "";
    }
    else{
      if(c != ' ')
        token += c;
      currentState = transitionState(currentState - 1, c);
    }
  }while(!inFile.eof());
}

void analyzeToken(string tok, int state){
  if(state == 3){
    if(isKeyword(tok)){
        printf("%-15s %-25s\n", "keyword", tok.c_str());
    }
    else{
        printf("%-15s %-25s\n", "identifier", tok.c_str());
    }
  }
  else if(state == 5){
      printf("%-15s %-25s\n", "real", tok.c_str());
  }
  else if(state == 7){
      //do nothing, state 7 is a comment block
  }
  else if(state == 8){
      printf("%-15s %-25s\n", "separator", tok.c_str());
  }
  else if(state == 9){
      printf("%-15s %-25s\n", "operator", tok.c_str());
  }
}


int char_to_col(char c){
  if(isalpha(c)){ return 0; }
  if(isdigit(c)){ return 1; }
  if(isSeparator(c)){ return 2; }
  if(isOperator(c)){ return 3; }
  if(c == ' '){ return 4; }
  if(c == '$'){ return 5; }
  if(c == '!'){ return 6; }
  if(c == '.'){ return 7; }
  return 0;
}

int transitionState(int state, char c){
  int col = char_to_col(c);
  return DSM_table[state][col];
}

bool isAcceptedState(int state){
  if(state == 3 || state == 5 || state == 7 || state == 8 || state == 9)
    return true;
  return false;
}

bool isTerminating(char c){
    if(c == ' ' || isOperator(c) || isSeparator(c)){
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
  return false;
}

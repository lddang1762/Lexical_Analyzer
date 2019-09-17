#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream myfile;
vector<string> keywords = {"int", "float", "bool","else","then","endif","while","whileend","do","doend",
                            "for","forend","input","output","and","or","function"};
vector<char> separators = {'\'', '(', ')', '{', '}', '[', ']', ',' , '.',':',';','!',' '};
vector<char> operators = {'*', '+', '-', '=', '/', '>', '<', '%'};

void lexer();
void readfile();
bool terminating(char c);
string tokenType(string token);

int main(int argc, char* argv[]){
  readfile();
  lexer();
  return 0;
}

void lexer(){
  bool tokenFound = false;
  string token = "";
  char c;
  do{
    myfile.get(c);
    if(c == ' '){
      printf("%-15s %-25s\n", tokenType(token).c_str(), token.c_str());
      //cout << tokenType(token) << token << endl;
      token = "";
    }
    else if(terminating(c)){
      string t = "";
      t += c;
      printf("%-15s %-25s\n", tokenType(t).c_str(), t.c_str());
      token = "";
    }
    else{
      if(!terminating(c) && !myfile.eof())
        token += c;
    }
  }while ( !(myfile.eof() ) );
  printf("%-15s %-25s\n", tokenType(token).c_str(), token.c_str());
  //cout << tokenType(token) << token << endl;


}

void readfile(){
  string fname = "";
  cout << "Enter file name: ";
  cin >> fname;
  myfile.open(fname);
}

bool terminating(char c){
  for(auto it = separators.begin(); it != separators.end(); it++){
    if(c == *it){
      return true;
    }
  }
  for(auto it = operators.begin(); it != operators.end(); it++){
    if(c == *it){
      return true;
    }
  }
  return false;
}

string tokenType(string token){
  if(token.length() == 1){
    for(auto it = separators.begin(); it != separators.end(); it++){
      if(token[0] == *it){
        return "separator";
      }
    }
    for(auto it = operators.begin(); it != operators.end(); it++){
      if(token[0] == *it){
        return "operator";
      }
    }
  }
  for(auto it = keywords.begin(); it != keywords.end(); it++){
    if(token == *it){
      return "keyword";
    }
  }

  return "identifier";
}

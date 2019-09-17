#include <iostream>
#include <fstream>

using namespace std;

ifstream myfile;

void lexer();
void readfile();

int main(int argc, char* argv[]){
  readfile();
  lexer();
  return 0;
}

void lexer(){
  bool tokenFound = false;
  string line;
  char c;
  do{
    myfile.get(c);
    if(!myfile.eof())
      cout << c;
    //getline(myfile, line);
    //cout << line << endl;
    //if(myfile.eof()){ cout << "END\n"; }
  }while ( !(tokenFound || myfile.eof() ) );
}

void readfile(){
  string fname = "";
  cout << "Enter file name: ";
  cin >> fname;
  myfile.open(fname);
}

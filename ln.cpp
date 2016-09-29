#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>

using namespace std;

int main(int argc, const char * argv[]){

  if(argc != 3 && argc != 4){
    cout << "Not the right amount of arguments" << endl;
    return EXIT_FAILURE;
  }
  // if no option is given then do the link
  if(argc == 3){
    link(argv[1], argv[2]);
  }
  // this is for if the option -s is present.
  if(argc == 4){
    string opt;
    opt = argv[1];
    if((opt != "-s") && (opt != "-S")){
      cout << "Not the right option." << endl;
      return EXIT_FAILURE;
    }
    else{ 
      symlink(argv[2], argv[3]);
    }
  }
  return EXIT_SUCCESS;
}

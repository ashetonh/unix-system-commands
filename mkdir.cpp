#include <cstdlib>
#include <iostream>
#include <sys/stat.h>
#include <cstring>
#include <cstdio>
#include <string>
#include <cerrno>
#include <sstream>
#include <unistd.h>

using namespace std;


//change string to a mutable cString.
char * toCstr(string a){
  char * cstr = new char[a.length()];
	for(unsigned int i =0;i<a.length();i++){
		cstr[i] = a[i];
	}
	cstr[a.length()] = '\0';
	return cstr;
	delete cstr;
}
/**
* This program was extremely difficult. The biggest problem
* I have is that I cannot make more than one command line argument
* directory. I am not worrying about it since it wasn't specified in the description.
*/
int main(const int argc, char * argv[]){
	
  
  char * pathname = new char[strlen(argv[argc-1])];
  pathname = argv[argc-1];
  char * cToken = new char[strlen(pathname)];
  string token;
  int mode = (mode_t)0755;
  int mFlag,pFlag;
  mFlag = 0;
  pFlag = 0;
  istringstream ss(pathname);
  
  if(argc >2){ // if there are options
    for(int i =1;i<argc;i++){
      if(strcmp(argv[i],"-p")==0){
	pFlag = 1;
      } // check for parent mode
      if(strcmp(argv[i],"-m")==0){
	mFlag = 1;
	char * perms = argv[i+1];
	mode = (mode_t)strtol(perms,NULL,8);

//cout<<mode<<endl;
      }
    } // check for octal mode option
    while(getline(ss,token,'/')){
      if(pFlag==1){
	if(token == ""){ 
	  continue;
	} // in case there is a / in the front.
	if(mFlag == 0){
	  mode = (mode_t)0755;
	} // default mode if flag is 0;
	strcat(cToken,toCstr(token));
	strcat(cToken,"/");
	mkdir(cToken,0755);
	chmod(cToken,mode);
      } // if for -p option flag
      else{
	if(mkdir(pathname,0755)== -1){
	  perror("mkdir");
	  return EXIT_FAILURE;
	}
	chmod(pathname,mode);
      } // else p == 0;
      
    } // stringstream for -p option
  }	
  else if(argc == 2){
    if(mkdir(argv[1],0755) == -1){
      perror("mkdir");
      return EXIT_FAILURE;
    }
  } // only two arguments given.
  else{
    cout<<"Not right amount of command line arguments. "<<endl;
    return EXIT_FAILURE;
  } // every other type of argument is wrong.
  //  if(cToken != nullptr) delete  cToken;
  //if(pathname!=nullptr) delete  pathname;
  // delete perms;
  //  delete cstr;
  return EXIT_SUCCESS;
}

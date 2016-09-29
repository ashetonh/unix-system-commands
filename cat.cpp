#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int main(int argc, char * argv[]){
  
  char * filename;
  int fd;
  int size;
  char * buffer;

  if(argc <2){
    cout<<"No file name(s) given."<<endl;
    return EXIT_FAILURE;
  } // error msg for when not enough or too many cmd line arguments are given
  for(int i =1;i<argc;i++){
    filename = argv[i];
    if((fd = open(filename,O_RDWR))<0){
      perror(argv[i]);
      return EXIT_FAILURE;
    } // err msg for if file doesnt exist
    else{    
      size = lseek(fd,0,SEEK_END);
      buffer = new char[size];
      fd = open(filename,O_RDWR);
      read(fd,buffer,size);
      write(STDOUT_FILENO,buffer,size);

    } // write to standard out
  }

  delete [] buffer;
  return EXIT_SUCCESS;
}

#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iomanip>
#include <dirent.h>
#include <cstring>

using namespace std;

void recRemove(string directory){
  DIR * dir = nullptr;
  struct dirent * entry;
  struct stat info;
  //struct stat fileinfo;
  if(directory[directory.size()-1] != '/') directory+="/";
  string filename;
  stat(directory.c_str(),&info);
  int mode = info.st_mode;
  dir = opendir(directory.c_str());
  if(mode & S_IFDIR){
    if(rmdir(directory.c_str()) == 0) return;
    directory+=filename;
  while((entry = readdir(dir)) != nullptr)
  {
    if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0) continue;


    filename = entry->d_name;
    //stat(filename.c_str(),&fileinfo);
    //int mode2 = (fileinfo.st_mode);

      recRemove(filename);

  }
}
else{
  unlink(directory.c_str());
}

}

int main(int argc, char * argv []){
  struct stat fileinfo;

  if(argc<=1){

    cerr<<"Not enough arguments"<<endl;
    return EXIT_FAILURE;
  }
  for(int i =1;i<argc;i++){
    if(strcasecmp(argv[1],"-r") == 0){
      stat(argv[i],&fileinfo);
      if(fileinfo.st_mode & S_IFDIR){
        string direct = argv[i];
        recRemove(direct);

      }
      else{
          if(unlink(argv[i]) < 0){
            perror(strerror(errno));
            return EXIT_FAILURE;
          }
        }
      }
       else{
      if(stat(argv[i],&fileinfo)==-1){
        cerr<<"Command line argument at index " << i << "was unable to be removed due to it not being a file"<<endl;
      }

      int mode = fileinfo.st_mode;
      if(mode & S_IWUSR){
        cout<<"Are you sure you want to remove: "<< argv[i] << "?"<<endl;
        string answer;
        getline(cin,answer);
          if(answer.compare("yes") || answer.compare("y")){
            if(unlink(argv[i])<0)perror(strerror(errno));
          }
        }
        else{
          if(unlink(argv[i]) < 0){
            perror(strerror(errno));
          }
        }
      }


    }
  return EXIT_SUCCESS;
}



#include <iostream>
#include <cstdlib>
#include <stdio.h>

#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#include <string>
#include <cerrno>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <iomanip>
#include <list>
#include <algorithm>


using namespace std;

/**
* sorting function for directories
*/
bool caseSense(struct dirent * a,struct dirent * b){
  return strcmp(a->d_name,b->d_name)<0;
}
/**
* sorting function for the arguments.
*/
int mycmp(const void *a,const void *b){
  return strcmp(*(char * const *)a, *(char*const*)b);
}


/**
* This main function will first only 
*/
int main(const int argc,char * argv[]){
  struct stat sb;
  struct stat sb2;

  list<struct dirent *> entries;
  
  struct dirent * entry = nullptr;
  struct passwd * username;
  struct group * groupname;
  struct tm *date;
  DIR * pwd = nullptr;
  string month;
  int blocks = 0;
  const char * filename;
  const char * diskUsage;
  const char * filename2;
  if(argc<=1){
   if((pwd = opendir(".")) == nullptr){
      perror("ls");
      return EXIT_FAILURE;
   }
   else{
    while((entry = readdir(pwd))!= nullptr){
      
      diskUsage = entry->d_name;
      if(strcmp(diskUsage,".") == 0 || strcmp(diskUsage,"..") == 0){
        continue;
      }
      stat(diskUsage,&sb2);
      entries.push_back(entry);
      blocks +=(int)sb2.st_blocks;
    }
    entries.sort(caseSense);
    cout<<"total "<<blocks<<endl;
    //qsort(&argv[1],argc-1,sizeof(char *),mycmp);
    for(auto dir : entries){
      
      filename = dir->d_name;
      if(strcmp(filename,".") == 0 || strcmp(filename,"..") == 0){
        continue;
      }
      stat(filename,&sb);
      username = getpwuid(sb.st_uid);
      groupname = getgrgid(sb.st_gid);
      date = localtime(&(sb.st_mtime));

            switch(date->tm_mon){
              case 0: month = "Jan";
                break;
              case 1: month = "Feb";
                break;
              case 2: month = "Mar";
                break;
              case 3: month = "Apr";
                break;
              case 4: month = "May";
                break;
              case 5: month = "Jun";
                break;
              case 6: month = "Jul";
                break;
              case 7: month = "Aug";
                break;
              case 8: month = "Sep";
                break;
              case 9: month = "Oct";
                break;
              case 10: month = "Nov";
                break;
              case 11: month = "Dec";
                break;
            } // month switch

            printf( (S_ISDIR(sb.st_mode)) ? "d" : "-");
            printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
            printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
            printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
            printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
            printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
            printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
            printf( (sb.st_mode & S_IROTH) ? "r" : "-");
            printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
            printf( (sb.st_mode & S_IXOTH) ? "x" : "-");
            
            // format this 
            cout<<"  " << sb.st_nlink;
            cout<<"  " << username->pw_name;
            cout<<"  " << groupname->gr_name;
            cout<<setw(10)<< sb.st_size;
            cout<<"  " << month << " " << date->tm_mday << "  ";
            printf("%.2d", date->tm_hour);
            cout<< ":" << setw(2);
            printf("%.2d", date->tm_min);
            cout << " " << filename<< endl; 

      
     }  
   }
  }
  else{
   if((pwd = opendir(".")) == nullptr){
    perror("ls");
    return EXIT_FAILURE;
   }
   else{
      qsort(&argv[1],argc-1,sizeof(char *),mycmp);
      for (int i = 1;i<argc;i++){
      filename2 = argv[i];
      stat(filename2,&sb);
      username = getpwuid(sb.st_uid);
      groupname = getgrgid(sb.st_gid);
      date = localtime(&(sb.st_mtime));

            switch(date->tm_mon){
              case 0: month = "Jan";
                break;
              case 1: month = "Feb";
                break;
              case 2: month = "Mar";
                break;
              case 3: month = "Apr";
                break;
              case 4: month = "May";
                break;
              case 5: month = "Jun";
                break;
              case 6: month = "Jul";
                break;
              case 7: month = "Aug";
                break;
              case 8: month = "Sep";
                break;
              case 9: month = "Oct";
                break;
              case 10: month = "Nov";
                break;
              case 11: month = "Dec";
                break;
            } // month switch

            printf( (S_ISDIR(sb.st_mode)) ? "d" : "-");
            printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
            printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
            printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
            printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
            printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
            printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
            printf( (sb.st_mode & S_IROTH) ? "r" : "-");
            printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
            printf( (sb.st_mode & S_IXOTH) ? "x" : "-");
            
            // format this 
            cout<<"  " << sb.st_nlink;
            cout<<"  " << username->pw_name;
            cout<<"  " << groupname->gr_name;
            cout<<setw(10)<< sb.st_size;
            cout<<"  " << month << " " << date->tm_mday << "  ";
            printf("%.2d", date->tm_hour);
            cout<< ":" << setw(2);
            printf("%.2d", date->tm_min);
            cout << " " << filename2<< endl; 
      }
                            
    //closedir(pwd);                               
     
    }
   }


  //entries.clear();
  closedir(pwd);
  return EXIT_SUCCESS;
}

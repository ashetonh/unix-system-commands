#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iomanip>
#include <cstring>
#include <string>
#include <pwd.h>
#include <grp.h>
#include <time.h>


using namespace std;

int main(int argc, const char * argv[]){

  if(argc != 2){
    cout << "Not enough command line arguments." << endl;
    return EXIT_FAILURE;
  }
  struct stat filenameStat;
  const char * filename = argv[1];
  string type;


  stat(filename, &filenameStat);

  printf("  ");
  cout << "filename: " << "`" << filename << "'" << endl;
  printf("  ");
  cout << "Size: " << left << setw(16) << (int) filenameStat.st_size;
  cout << "Blocks: " << left << setw(11) << (int) filenameStat.st_blocks;
  cout << "IO Block: " << left << setw(7) << (int) filenameStat.st_blksize;
  
  if(S_ISREG(filenameStat.st_mode)){
    cout << "regular filename";
  }
  if(S_ISDIR(filenameStat.st_mode)){
    cout << "directory";
  }
  if(S_ISCHR(filenameStat.st_mode)){
    cout << "character device";
  }
  if(S_ISBLK(filenameStat.st_mode)){
    cout << "block device";
  }
  if(S_ISFIFO(filenameStat.st_mode)){
    cout << "FIFO";
  }
  if(S_ISLNK(filenameStat.st_mode)){
    cout << "symbolic link";
  }
  if(S_ISSOCK(filenameStat.st_mode)){
    cout << "socket";
  }
  cout << endl;

  cout << "Device: ";
  cout << hex << (int) filenameStat.st_dev << "h/";
  cout << dec << filenameStat.st_dev << "d    ";

  cout << "Inode: " << setw(12) << (int) filenameStat.st_ino;
  cout << "Links: " << filenameStat.st_nlink;
  cout << endl;


  // this is the permissions
  cout << "Access: (";
  int total = 0;
  int mode = (int) filenameStat.st_mode;
  int permissions[4];
  int i = 0;
  while(mode > 0){
    if(i == 4){
      break;
    }
    total = mode % 8;
    mode /= 8;
    permissions[i] = total;
    i++; 
  }
  for(int i = 3; i >= 0; i--){
      cout << permissions[i];
  }
  cout << "/";

  printf( (S_ISDIR(filenameStat.st_mode)) ? "d" : "-");
  printf( (filenameStat.st_mode & S_IRUSR) ? "r" : "-");
  printf( (filenameStat.st_mode & S_IWUSR) ? "w" : "-");
  printf( (filenameStat.st_mode & S_IXUSR) ? "x" : "-");
  printf( (filenameStat.st_mode & S_IRGRP) ? "r" : "-");
  printf( (filenameStat.st_mode & S_IWGRP) ? "w" : "-");
  printf( (filenameStat.st_mode & S_IXGRP) ? "x" : "-");
  printf( (filenameStat.st_mode & S_IROTH) ? "r" : "-");
  printf( (filenameStat.st_mode & S_IWOTH) ? "w" : "-");
  printf( (filenameStat.st_mode & S_IXOTH) ? "x" : "-");
  printf(")  ");


  struct passwd * username = getpwuid(filenameStat.st_uid);
  struct group * groupname = getgrgid(filenameStat.st_gid);

  cout << "Uid: (" << (int) filenameStat.st_uid << "/";
  printf("%*.*s", 8, 8, username->pw_name);
  printf(")   Gid: (");
  cout << (int) filenameStat.st_gid;
  printf("/");
  printf("%*.*s", 8, 8, groupname->gr_name);
  cout << ")" << endl;

  // now for the times.
  time_t acc = filenameStat.st_atime;
  time(&acc);
  struct tm * timeinfo;
  timeinfo = localtime (&acc);
  char buffer[256];  
  strftime(buffer, sizeof(buffer), "%z" , timeinfo);

  struct tm * accTime;
  struct tm * modTime;
  struct tm * changeTime;
  accTime = localtime(&(filenameStat.st_atime));  
  modTime = localtime(&(filenameStat.st_mtime));
  changeTime = localtime(&(filenameStat.st_ctime));
  int monthmode, year, daymode,hours, minutes, seconds;

  monthmode = (int) accTime->tm_mon + 1;
  year = (int) accTime->tm_year + 1900;
  daymode = (int) accTime->tm_mday;
  hours = (int) accTime->tm_hour;
  minutes = (int) accTime->tm_min;
  seconds = (int) accTime->tm_sec;

  cout << "Access: ";
  cout << year << "-" << monthmode << "-";
  printf("%02d", daymode);
  printf(" ");
  printf("%02d", hours);
  printf(":");
  printf("%02d", minutes);
  printf(":");
  printf("%02d", seconds);
  printf(" ");
  puts(buffer);


  year = (int) modTime->tm_year + 1900;
  monthmode = (int) modTime->tm_mon + 1;
  daymode = (int) modTime->tm_mday;
  hours = (int) modTime->tm_hour;
  minutes = (int) modTime->tm_min;
  seconds = (int) modTime->tm_sec;

  cout << "Modify: ";
  cout << year << "-" << monthmode << "-";
  printf("%02d", daymode);
  printf(" ");
  printf("%02d", hours);
  printf(":");
  printf("%02d", minutes);
  printf(":");
  printf("%02d", seconds);
  printf(" ");
  puts (buffer);

  year = (int) changeTime->tm_year + 1900;
  monthmode = (int) changeTime->tm_mon + 1;
  daymode = (int) changeTime->tm_mday;
  hours = (int) changeTime->tm_hour;
  minutes = (int) changeTime->tm_min;
  seconds = (int) changeTime->tm_sec;

  cout << "Change: ";
  cout << year << "-" << monthmode << "-";
  printf("%02d", daymode);
  printf(" ");
  printf("%02d", hours);
  printf(":");
  printf("%02d", minutes);
  printf(":");
  printf("%02d", seconds);
  printf(" ");
  puts (buffer);






return EXIT_SUCCESS;
}

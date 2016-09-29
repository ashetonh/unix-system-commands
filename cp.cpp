#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <fcntl.h>
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
#include <cstdlib>
#include <limits.h>

using namespace std;






// void copyFiles(char * src,char * dest){
// 	struct stat fileinfo;
// 	stat(src, &fileinfo);
// 	char * buffer;
// 	int fd, fd2, size;
// 	int mode = fileinfo.st_mode;

// 	if(mode & S_IFREG)
// 	{
// 		fd = open(src,O_RDWR);
// 		fd2 = open(dest,O_RDWR|O_TRUNC|O_CREAT,mode);
// 		size = lseek(fd,0,SEEK_END);
// 		buffer = new char[size];
// 		filedes= open(src,O_RDWR);
// 		read(fd,buffer,size);
// 		write(fd2,buffer,size);
// 		delete [] buffer;
// 	}

// }

// void copyDir(char * src,char * dest){
// 	struct stat srcinfo;
// 	struct stat destinfo;
// 	stat(src,&srcinfo);
// 	int srcmode = fileinfo.st_mode;
// 	if(stat(dest,&destinfo)==-1) mkdir(dest,srcmode);
// 	int destmode = destinfo.st_mode;
// 	struct dirent * entry;
// 	//copyFil
// 	if(srcmode & S_IFDIR)
// 	{
// 		while((entry))
// 	}

// }

void copyFile(const char * file,const char * file2){
	struct stat sb;
	stat(file,&sb);
	struct stat sb2;
	struct stat sb3;
	char * buffer;



	int size, filedes,filedes2;
	int mode = sb.st_mode;
	struct dirent * entry = nullptr;
	DIR * dir = nullptr;
	//char * filename;


	//cout<<dest<<endl;


	

	
	if(mode & S_IFREG){
		//COPY FILES. THIS WORKS.
		filedes = open(file,O_RDWR);
		cout<<filedes<<endl;
		filedes2 = open(file2,O_RDWR|O_TRUNC|O_CREAT,mode);
		cout<<filedes2<<endl;
		size = lseek(filedes,0,SEEK_END);
		buffer = new char[size];
		filedes=open(file,O_RDWR);
		read(filedes,buffer,size);
		write(filedes2,buffer,size);
	
		delete [] buffer;
	
	}
	else if (mode & S_IFDIR){
		if(stat(file2,&sb2) == -1) mkdir(file2,0755);

		while((entry = readdir(dir))!=nullptr){
			if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0) continue;

			stat(entry->d_name,&sb3);
			int mode3 = sb3.st_mode;

			if(mode3 & S_IFREG){

				char newFile[PATH_MAX+1];
				getcwd(newFile,PATH_MAX+1);
				char destFile[PATH_MAX+1];
				strcat(destFile,"/");
				strcat(destFile,entry->d_name);
				strcat(newFile,"/");
				strcat(newFile,entry->d_name);
				cout<<newFile<<endl;
				cout<<destFile<<endl;
				copyFile(newFile,destFile);

			}
			else{
				cout<<"poop"<<endl;
			}

			// cout<<entry->d_name<<endl;
			// stat(entry->d_name,&sb3);
			// mode2 = sb3.st_mode;
			// if(mode2 & S_IFDIR){
			// 	closedir(dir);
			// 	src+= "/";
			// 	src+= entry->d_name;
			// 	dest+="/";
			// 	dest+= entry->d_name;
			// 	cout<<src<<endl;
			// 	cout<<dest<<endl;
			// 	copyFile(src.c_str(),dest.c_str());
			
			// }
		
			

			
		}

	}
}	

int main(int argc, char * argv[]){
	struct stat cat;
	int fd;	

	char * filename;
	char * filename2;

	if (argc == 3 || argc==4){
		filename = argv[argc-2];
		if(strcasecmp(argv[1],"-R") == 0){
			filename2 = argv[argc-1];

			copyFile(filename,filename2);


		} // check source file.


		else if((fd=open(filename,O_RDWR))<0){
			perror("cp");
			return EXIT_FAILURE;
		}


		else{
			if(strcmp(argv[argc-2],argv[argc-1]) == 0){
				cout<<"Cannot copy a file to itself."<<endl;
				return EXIT_FAILURE;
			}
			filename2 = argv[argc-1];
			stat(filename2,&cat);
			int perms = cat.st_mode;
			if(perms & S_IFDIR){
				strcat(filename2,"/");
				strcat(filename2,filename);
			}
			if(filename2[strlen(filename2)-1] == '/'){
				mkdir(filename2,0755);
				char * please = filename2;
				strcat(please,"/");
				strcat(please,filename);
				copyFile(please,filename2);			

			}
			else{
				copyFile(filename,filename2);
			
			}

		}
	}
	else{
		cerr<<"Either too many/few command line arguments or wrong option given."<<endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

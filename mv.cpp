#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <cerrno>
#include <cstring>
#include <sys/stat.h>

using namespace std;

// ASK COTTEREL: DOES THIS NEED TO BE IN A LOOP? 
int main(const int argc, char * argv[]){
	if(argc !=3){
		cerr<<"Not the right amount of command line arguments"<<endl;
		return EXIT_FAILURE;
	}
	int x;
	struct stat s;
	char * buffer = nullptr;
	
	char * check = argv[2];


	//if(check[strlen(check)-1] == '/'){
	if(stat(check,&s) == 0){
		if(s.st_mode & S_IFDIR)
		{
			int length = strlen(argv[2]) + strlen(argv[1]) + 1;
			buffer = new char[length];
			buffer = argv[2];
			strcat(buffer,"/");
			strcat(buffer,argv[1]);
			//puts(buffer);
			//cout<<buffer<<endl;
		}	
	}
	else{
		buffer = argv[2];
	}

	if((x = rename(argv[1],buffer)) == -1){
		perror("Moving error");
		return EXIT_FAILURE;
	}


  	return EXIT_SUCCESS;
}

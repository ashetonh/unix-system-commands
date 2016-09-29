#include <cstdlib>
#include <iostream>
#include <sys/stat.h>
#include <cstring>
#include <cstdio>
#include <string>
#include <cerrno>
#include <sstream>

using namespace std;




int main(int argc, char * argv[]){
  
  
   if(argc != 4){
     cerr<<"Not the right amount of command line arguments"<<endl;
    return EXIT_FAILURE; 
     }
  char * filename = argv[3];
  char * perms = argv[2];
  string octSym = argv[1];

  struct stat modes;
  stat(filename, &modes);
  mode_t temp = modes.st_mode;
 
  if (octSym == "-oct"){
    
    //error handling for right length of argument
    if(strlen(perms)<=4){
      int n = (mode_t)strtol(perms,NULL,8);//octal rep of string.
      if (n>=0){ // error handling for negative
	if(chmod(filename,n)<0){
	  perror(strerror(errno));
	  return EXIT_FAILURE;

	}
	
      }
      else{
	cout<<"Invalid permission given."<<endl;
	return EXIT_FAILURE;
      }
      //PUT HERE ELSE IF HANDLING ERROR MISTAKES
    } //OCTAL VERSION
    else{
      cout<<"Invalid permission given."<<endl;
      return EXIT_FAILURE;
    }
  }
  
  else if(octSym=="-sym"){
    //SYMBOLIC 
    istringstream ss(perms);
    string token;
    //fill the stringstream parsing each string before the commas.
    while(getline(ss,token,',')){
      // go through the substring looking at each letter
      for(int i =0;i<(int)token.size();i++){

	switch(token[i]){
	  //look for u g o a. if you see them, then if you see +,-,= then do things accordingly with the r,w,x.
	case 'u':
	  for(int j =0;j<(int)token.size();j++){
	    if (token[j] == '+'){
	      for(int l = 0;l<(int)token.size();l++){
		if(token[l] == 'r'){
		  temp|= S_IRUSR;
		}
		else if(token[l] == 'w'){
		  temp|=S_IWUSR;
		}
		else if(token[l] == 'x'){
		  temp|=S_IXUSR;
		}
		else if(token[l] == 's'){
		  temp|=S_ISUID;
		}
	      }
	    }
	  
	    if (token[j] == '-'){
	      for(int l = 0;l<(int)token.size();l++){
		if(token[l] == 'r'){
		  temp&= ~(S_IRUSR);
		}
		else if(token[l] == 'w'){
		  temp&=~(S_IWUSR);
		}
		else if(token[l] == 'x'){
		  temp&=~(S_IXUSR);
		}
		else if(token[l] == 's'){
		  temp&=~(S_ISUID);
		}
	      }
	    }

	    if (token[j] == '='){
	      temp&=~(S_IRUSR);
	      temp&=~(S_IWUSR);
	      temp&=~(S_IXUSR);
	      temp&=~(S_ISUID);
	      for(int l = 0;l<(int)token.size();l++){
		if(token[l] == 'r'){
		  
                  temp|= S_IRUSR;
                }
                else if(token[l] == 'w'){
                  temp|=S_IWUSR;
                }
                else if(token[l] == 'x'){
                  temp|=S_IXUSR;
                }
		else if(token[l] == 's'){
		  temp|=S_ISUID;
		}
	      }
	    }
	  }
	  //  newPerms|=temp;
	  break;
	  
	case 'g':

	  for(int j =0;j<(int)token.size();j++){
	    if (token[j] == '+'){
	      for(int l = 0;l<(int)token.size();l++){
		if(token[l] == 'r'){
		  temp|= S_IRGRP;
		}
		else if(token[l] == 'w'){
		  temp|=S_IWGRP;
		}
		else if(token[l] == 'x'){
		  temp|=S_IXGRP;
		}	     
		else if(token[l] == 's'){
		  temp|=S_ISGID;
		}
	      }
	    }
	    if (token[j] == '-'){
              for(int l = 0;l<(int)token.size();l++){
                if(token[l] == 'r'){
                  temp&= ~(S_IRGRP);
                }
                else if(token[l] == 'w'){
                  temp&= ~(S_IWGRP);
                }
                else if(token[l] == 'x'){
                  temp&=~(S_IXGRP);
                }
		else if(token[l] == 's'){
		  temp&=~(S_ISGID);
		}
              }
            }
	    if (token[j] == '='){
	      temp &= ~(S_IRGRP);
	      temp&=~(S_IWGRP);
	      temp&=~(S_IXGRP);
	      temp&=~(S_ISGID);
              for(int l = 0;l<(int)token.size();l++){
                if(token[l] == 'r'){
                  temp|= S_IRGRP;
                }
                else if(token[l] == 'w'){
                  temp|=S_IWGRP;
                }
                else if(token[l] == 'x'){
                  temp|=S_IXGRP;
                }                
		else if(token[l] == 's'){
		  temp|=S_ISGID;
		}
              }
            }
          }
	  //newPerms|=temp;
	break;
	
	case 'o':
	  for(int j =0;j<(int)token.size();j++){
	    if (token[j] == '+'){
	      for(int l = 0;l<(int)token.size();l++){
		if(token[l] == 'r'){
		  temp|= S_IROTH;
		}
		else if(token[l] == 'w'){
		  temp|=S_IWOTH;
		}
		else if(token[l] == 'x'){
		  temp|=S_IXOTH;
		}			
	
	      }
	    }
	    if (token[j] == '-'){
	      for(int l = 0;l<(int)token.size();l++){
		if(token[l] == 'r'){
		  temp&= ~(S_IROTH);
		}
		else if(token[l] == 'w'){
		  temp&=~(S_IWOTH);
		}
		else if(token[l] == 'x'){
		  temp&=~(S_IXOTH);
		}
	      }
	    }
	    if (token[j] == '='){
	      temp &=~(S_IROTH);
	      temp &=~(S_IWOTH);
	      temp &=~(S_IXOTH);
	      for(int l = 0;l<(int)token.size();l++){
		if(token[l] == 'r'){
		  temp+= S_IROTH;
		}
		else if(token[l] == 'w'){
		  temp+=S_IWOTH;
		}
		else if(token[l] == 'x'){
		  temp+=S_IXOTH;
		}
	      }
	    }
	  }

	  break;
	  
	case 'a':
	  for(int j =0;j<(int)token.size();j++){
	    if (token[j] == '+'){
	      for(int l = 0;l<(int)token.size();l++){
		if(token[l] == 'r'){
		  temp|= S_IROTH;
		  temp|=S_IRGRP;
		  temp|=S_IRUSR;
		}
		if(token[l] == 'w'){
		  temp|=S_IWUSR;
		  temp|=S_IWGRP;
		  temp|=S_IWOTH; 
		}
		if(token[l]=='x'){
		  temp|=S_IXUSR;
		  temp|=S_IXGRP;
		  temp|=S_IXOTH;
		}
	      }
	    }
	    if(token[j] =='-'){
	      
	      for (int l =0;l<(int)token.size();l++){
		if(token[l] == 'r'){
		  temp&=~(S_IRUSR);
		  temp&=~(S_IRGRP);
		  temp&=~(S_IROTH);
		}
		if(token[l] == 'w'){
		  temp&=~(S_IWUSR);
		  temp&=~(S_IWGRP);
		  temp&=~(S_IWOTH);
		}
		if(token[l] == 'x'){
		  temp&=~(S_IXUSR);
		  temp&=~(S_IXGRP);
		  temp&=~(S_IXOTH);
		}
	      }
	    }
	    if(token[j] =='='){
	      temp&=~(S_IRUSR);
	      temp&=~(S_IRGRP);
	      temp&=~(S_IROTH);
	      temp&=~(S_IWUSR);
	      temp&=~(S_IWGRP);
	      temp&=~(S_IWOTH);
	      temp&=~(S_IXUSR);
	      temp&=~(S_IXGRP);
	      temp&=~(S_IXOTH);
	      for (int l =0;l<(int)token.size();l++){
		if(token[l] == 'r'){
		  temp|=S_IRUSR;
		  temp|=S_IRGRP;
		  temp|=S_IROTH;
                     }
		if(token[l] == 'w'){
		  temp|=S_IWUSR;
		  temp|=S_IWGRP;
		  temp|=S_IWOTH;
		}
		if(token[l] == 'x'){
		  temp|=S_IXUSR;
		  temp|=S_IXGRP;
		  temp|=S_IXOTH;
		}
	      }
	    }
	  }
	  break;
	case 't':
	  for(int j=0;j<(int)token.size();j++){
	    if(token[j] == '='){
	      temp&=~(S_ISVTX);
	      temp|=(S_ISVTX);
	    }
	    else if(token[j] == '-'){
	      temp&=~(S_ISVTX);
	    }
	    else if(token[j] == '+'){
	      temp|=S_ISVTX;
	    }
	  }
	  break;
	default:
	  break;
	}
      }
    }
    
    chmod(filename,temp);
    
  }
  
  else{
    cout<<"Invalid permissions";
    cout<<endl;
    return EXIT_FAILURE;
  }
  
  // chmod(filename,newPerms);
  return EXIT_SUCCESS;
}

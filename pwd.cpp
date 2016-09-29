#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

using namespace std;
 
int main(const int argc, const char * argv []) {
  char * pwd = nullptr;
  size_t size = 0;
  if ((pwd=getcwd(pwd,size)) != nullptr) {
    cout << pwd << endl;
    free(pwd);
    return EXIT_SUCCESS;
  } else {
    perror(argv[0]);
    return EXIT_FAILURE;
  } // if
} // main

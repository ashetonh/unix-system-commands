#include <iostream>
#include <cstdlib>
 
using namespace std;
 
int main(const int argc, const char * argv [], const char * envp []) {
  for (const char ** env = envp; *env != nullptr; ++env) {
    cout << *env << endl;
  } // for
  return EXIT_SUCCESS;
} // main
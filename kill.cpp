#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

#define SIGHUP 1
#define SIGINT 2        
#define SIGQUIT 3
#define SIGILL 4           
#define SIGTRAP 5     
#define SIGABRT 6
#define SIGIOT 6          
#define SIGBUS 7       
#define SIGFPE 8
#define SIGKILL 9         
#define SIGUSR1 10        
#define SIGSEGV 11
#define SIGUSR2 12         
#define SIGPIPE 13         
#define SIGALRM 14         
#define SIGTERM 15 
#define SIGSTKFLT 16         
#define SIGCHLD 17         
#define SIGCONT 18         
#define SIGSTOP 19         
#define SIGTSTP 20         
#define SIGTTIN 21         
#define SIGTTOU 22         
#define SIGURG 23         
#define SIGXCPU 24         
#define SIGXFSZ 25         
#define SIGVTALRM 26         
#define SIGPROF 27         
#define SIGWINCH 28         
#define SIGIO 29         
#define SIGPWR 30         
#define SIGSYS 31         
#define SIGUNUSED 31


using namespace std;

struct signames {
	const char *name;
	int sig;
} signames[] = {
	{ "SIGHUP",	SIGHUP		},
	{ "SIGINT",	SIGINT		},
	{ "SIGQUIT",	SIGQUIT		},
	{ "SIGILL",	SIGILL		},
	{ "SIGTRAP",	SIGTRAP		},
	{ "SIGABRT",	SIGABRT		},
	{ "SIGIOT",	SIGIOT		},
	{ "SIGFPE",	SIGFPE		},
	{ "SIGKILL",	SIGKILL		},
	{ "SIGUSR1",	SIGUSR1		},
	{ "SIGSEGV",	SIGSEGV		},
	{ "SIGUSR2",	SIGUSR2		},
	{ "SIGPIPE",	SIGPIPE		},
	{ "SIGALRM",	SIGALRM		},
	{ "SIGTERM",	SIGTERM		},
	{ "SIGSTKFLT",  SIGSTKFLT	},
	{ "SIGBUS",	SIGBUS		},
	{ "SIGCHLD",	SIGCHLD		},
	{ "SIGCONT",	SIGCONT		},
	{ "SIGSTOP",	SIGSTOP		},
	{ "SIGTSTP",	SIGTSTP		},
	{ "SIGTTIN",	SIGTTIN		},
	{ "SIGTTOU",	SIGTTOU		},
	{ "SIGURG", 	SIGURG		},
	{ "SIGXCPU",	SIGXCPU		},
	{ "SIGXFSZ",	SIGXFSZ		},
	{ "SIGVTALRM",	SIGVTALRM	},
	{ "SIGPROF",	SIGPROF		},
	{ "SIGWINCH",	SIGWINCH	},
	{ "SIGIO",	SIGIO		},
	{ "SIGPWR",	SIGPWR		},
	{ "SIGSYS",	SIGSYS		},
	{ "SIGUNUSED",	SIGUNUSED	},
	{ NULL,		0		},
}; 

void usage()
{
	cout << "Usage: kill [-sig] pid" << endl;
	exit(1);
} //Usage

int main(int argc, char * argv[]) {
	pid_t process;
  int m = 0, sig = SIGKILL; //default is sigkill
  char *stop;

  long l;
  unsigned long ul;
  struct sigaction sa;
  int i, doit;
  struct signames *snp; //pointer to the above struct

  if (argc > 1 && argv[1][0] == '-') {
  	sig = -1;

  	if (sig < 0) {					
  		ul = strtoul(argv[1] + 1, &stop, 10);
  		if (stop == argv[1] + 1 || *stop != 0 || ul > _NSIG) {
  			usage();
  		}
  		sig = ul;
	} // for the numeric

	for (snp = signames; snp->name != NULL; snp++) {
		if (strcmp(snp->name, argv[1] + 1) == 0) {
			sig = snp->sig;
			break;
		}
	} // for the symbolic
	argv++;
	argc--;
}

sa.sa_flags = 0;
sigemptyset(&sa.sa_mask);
sa.sa_handler = SIG_IGN;


for (doit = 0; doit <= 1; doit++) {
	for (i = 1; i < argc; i++) {
		l = strtoul(argv[i], &stop, 10);
		if (stop == argv[i] || *stop != 0 || (pid_t) l != l) usage();
		process = l;
		if (doit && kill(process, sig) < 0) {
			fprintf(stderr, "kill: %d: %s\n", process, strerror(errno));
			m = 1;
		}
	}
}
return(m);
}

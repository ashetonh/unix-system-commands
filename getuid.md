Name of the System Call I Chose: getuid

includes to use this function:
	 #include <unistd.h>
	 #include <sys/types.h>

Function syntax:
	 uid_t getuid(void);

Description: this function will return the real user ID of the process. Also,
this function never returns an error!
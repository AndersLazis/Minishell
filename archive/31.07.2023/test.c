#include <stdlib.h>
#include <stdio.h>
  #include <sys/ioctl.h>
int main(void)
{
	ioctl(0, TIOCSTI, "ab"); 
	return (200);
}
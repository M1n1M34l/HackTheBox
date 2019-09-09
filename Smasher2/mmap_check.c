#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char * const * argv)
{
	printf("[+] PID: %d\n", getpid());
	int fd = open("/dev/dhid", O_RDWR);
	if (fd < 0)
 	{
		printf("[-] Open failed!\n");
		return -1;
 	}
	printf("[+] Open OK fd: %d\n", fd);

	unsigned long size = 0xf0000000;
	unsigned long mmapStart = 0x42424000;
	unsigned int * addr = (unsigned int *)mmap((void*)mmapStart, size, PROT_READ| PROT_WRITE, MAP_SHARED, fd, 0x0);
	if (addr == MAP_FAILED)
 	{
		 perror("Failed to mmap: ");
		 close(fd);
		 return -1;
	}
	printf("[+] mmap OK addr: %lx\n", addr);
	int stop = getchar();
	return 0;
}

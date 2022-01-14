//-------| lib/keypad.h |-------//
#ifndef	KEYPAD_H
#define	KEYPAD_H 


#define KEY_OUT_ADDR 0x11D00000
#define KEY_IN_ADDR  0x11E00000//physical address 정의
#define SCAN_NUM     4

#include <stdio.h>		// printf(), scanf(), fprintf()
#include <fcntl.h>		// open()
#include <unistd.h>		// close(), off_t , usleep()
#include <sys/mman.h>	// mmap(), munmap()
#include <stdlib.h> 	// exit()
#include <string.h>		// strlen()


#endif

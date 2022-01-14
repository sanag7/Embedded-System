//-------| lib/fnd.h |-------//
#ifndef	FND_H
#define	FND_H 


#include <unistd.h> // usleep()


#include <string.h>
#include <sys/mman.h>

#define FND_CS0 0x11000000 // FND 0의 physical address
#define FND_CS1 0x11100000 // FND 1의 physical address
#define FND_CS2 0x11200000 // FND 2의 physical address
#define FND_CS3 0x11300000 // FND 3의 physical address
#define FND_CS4 0x11400000 // FND 4의 physical address
#define FND_CS5 0x11500000 // FND 5의 physical address
#define FND_CS6 0x11600000 // FND 6의 physical address
#define FND_CS7 0x11700000 // FND 7의 physical address


int             fnd_init(void);
void            fnd_clear(void);
void 		fnd_fail(void);
void            fnd_exit(void);
void		fnd_display(char *hexadecimal, int N);

unsigned char	hexn2fnd(char ch);

static unsigned short *FND0, *FND1, *FND2, *FND3, *FND4, *FND5, *FND6, *FND7;

#endif

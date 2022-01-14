#include "fnd.h"

extern int fd;

//fnd function define--------------------------------------------------------------
int fnd_init(void)
{int ierr=0;
FND0=mmap(NULL,2,PROT_WRITE,MAP_SHARED,fd,FND_CS0); ierr+=(int)FND0;
FND1=mmap(NULL,2,PROT_WRITE,MAP_SHARED,fd,FND_CS1); ierr+=(int)FND1;
FND2=mmap(NULL,2,PROT_WRITE,MAP_SHARED,fd,FND_CS2); ierr+=(int)FND2;
FND3=mmap(NULL,2,PROT_WRITE,MAP_SHARED,fd,FND_CS3); ierr+=(int)FND3;
FND4=mmap(NULL,2,PROT_WRITE,MAP_SHARED,fd,FND_CS4); ierr+=(int)FND4;
FND5=mmap(NULL,2,PROT_WRITE,MAP_SHARED,fd,FND_CS5); ierr+=(int)FND5;
FND6=mmap(NULL,2,PROT_WRITE,MAP_SHARED,fd,FND_CS6); ierr+=(int)FND6;
FND7=mmap(NULL,2,PROT_WRITE,MAP_SHARED,fd,FND_CS7); ierr+=(int)FND7;
return ierr;//각 FND의 physical memory를 virtual memory로 mapping
}

void fnd_display(char *hexadecimal, int N)
{if (N>=1)*FND0=hexn2fnd(hexadecimal[0]);
if (N>=2)*FND1=hexn2fnd(hexadecimal[1]);
if (N>=3)*FND2=hexn2fnd(hexadecimal[2]);
if (N>=4)*FND3=hexn2fnd(hexadecimal[3]);
if (N>=5)*FND4=hexn2fnd(hexadecimal[4]);
if (N>=6)*FND5=hexn2fnd(hexadecimal[5]);
if (N>=7)*FND6=hexn2fnd(hexadecimal[6]);
if (N>=8)*FND7=hexn2fnd(hexadecimal[7]);
}

unsigned char hexn2fnd(char ch)
{ //char 형태로 받은 숫자입력을 FND에 전송할 형태의 data로 변환하는 함수
 unsigned char code;
switch (ch)
       {case 0x00 : code=0x3f; break;
        case 0x01 : code=0x06; break;
        case 0x02 : code=0x5b; break;
        case 0x03 : code=0x4f; break;
        case 0x04 : code=0x66; break;
        case 0x05 : code=0x6d; break;
        case 0x06 : code=0x7d; break;
        case 0x07 : code=0x07; break;
        case 0x08 : code=0x7f; break;
        case 0x09 : code=0x67; break;
        case 0x0A : code=0x77; break;
        case 0x0B : code=0x7c; break;
        case 0x0C : code=0x39; break;
        case 0x0D : code=0x5e; break;
        case 0x0E : code=0x79; break;
        case 0x0F : code=0x71; break;
        default   : code=0x00;
        }//p.59를 참고하여 FND가 한자리의 16진수를 표현하기 위해 필요한 코드 정의
return code;
}

void fnd_clear(void)//모든 FND의 입력을 00000000으로 clear
{*FND0=0x00; *FND1=0x00; *FND2=0x00; *FND3=0x00;
 *FND4=0x00; *FND5=0x00; *FND6=0x00; *FND7=0x00;
}

void fnd_fail(void)//모든 FND의 입력을 00000000으로 clear
{*FND0=0x40; *FND1=0x40; *FND2=0x40; *FND3=0x40;
 *FND4=0x40; *FND5=0x40; *FND6=0x40; *FND7=0x40;
}

void fnd_exit(void)
{fnd_clear();
munmap(FND0,2); munmap(FND1,2); munmap(FND2,2); munmap(FND3,2);
munmap(FND4,2); munmap(FND5,2); munmap(FND6,2); munmap(FND7,2);
}


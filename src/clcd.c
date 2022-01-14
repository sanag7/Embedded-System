#include "clcd.h"

extern int fd;

//clcd function define--------------------------------------------------------------
int clcd_init(void)//디바이스의 physical address를 메모리공간에 mapping.
{int ierr=0;
 CLCD_CMD=mmap(NULL, 2, PROT_WRITE, MAP_SHARED, fd, FPGA_CLCD_WR);
 CLCD_DATA=mmap(NULL, 2, PROT_WRITE, MAP_SHARED, fd, FPGA_CLCD_RS);
 ierr=(int)((!CLCD_CMD)||(!CLCD_DATA));
 return ierr;
}

void write_byte(char ch)
{unsigned short data;
 data=ch&0x00FF; *CLCD_DATA=data; usleep(50);}
//논리곱을 통해 문자ch의 16진수 값(두자리의 16진수)을 앞에 00이 붙는 네자리의 16진수로 만들어준다. 이후 CLCD_DATA의 값으로 대입한다.
//위 과정을 통해서 디바이스에 문자를 출력시킨다. 

void setcommand(unsigned short command)
{command &=0x00FF; *CLCD_CMD=command; usleep(2000);}
//논리곱을 통해 두자리의 16진수 command를 앞에 00이 붙는 네자리의 16진수로 만들어준다. 이후 CLCD_CMD의 값으로 대입한다.
//위 과정을 통해서 디바이스에 제어명령을 내린다.

void initialize_clcd(void)
{int DL=1, N=1, F=0, D=1, C=0, B=0, ID=1, S=0;//어떠한 제어명령을 내릴지 결정하여 각 변수별로 0 or 1을 대입.
 function_set(DL,N,F);//DL=1(8 bits), N=1 (2 lines), F=0 (5X7 dot)
 display_control(D,C,B); //Display=1(on), Cursor=0(off), Blinking=0(off)
 clcd_clear();//전체화면을 지우고 cursor를 home으로 위치시킨다.
 entry_mode_set(ID,S); //ID=1(Increment), S=0(No shift for text)
 return_home();//cursor를 home으로 위치시킨다.
}

void function_set(int DL, int N, int F)//function set에 대한 제어명령 입력 함수
{//DL=1(8)/0(4bits), N=1(2)/0(1 line), F=1(5X10)/0(5X7 dots)
 unsigned short command=0x20; //Table 4.1(6)
 if(DL>0) command|=0x10;
 if(N>0) command|=0x08;
 if(F>0) command|=0x04;
 setcommand(command);
}

void display_control(int D, int C, int B)//display control에 대한 제어명령 입력함수
{//D=1(Display on)/0(off), C=1(Cursor on)/0(off), B=1(Blinking on)/0(off)
 unsigned short command=0x08; //Table 4.1(4)
 if(D>0) command|=0x04;
 if(C>0) command|=0x02;
 if(B>0) command|=0x01;
 setcommand(command);
}

void cursor_shift(int set_screen, int set_rightshit)//cursor shift에 대한 제어명령 입력함수
{unsigned short command=0x10;
 if (set_screen>0) command|=0x08;
 if (set_rightshit>0) command|=0x04;
 setcommand(command);
}

void entry_mode_set(int ID, int S)//entry mode set에 대한 제어명령 입력함수
{//ID=1(increase)/0(Decrease cursor position), S=1(display shift)/0(not)
 unsigned short command=0x04; //Table 4.1(3)
 if(ID>0) command|=0x02;
 if(S>0) command|=0x01;
 setcommand(command);
}

void return_home(void)//return home 제어명령 입력함수(cursor를 home위치로)
{setcommand(0x02);} //Table 4.1(2)

void clcd_clear(void)//clcd clear 제어명령 입력함수(전체화면을 지우고 cursor를 home위치로)
{setcommand(0x01);} //Table 4.1(1)

void set_RAM_address(int pos, int CG_or_DD)//static void로 변경(교재누락)
//CG RAM 혹은 DD RAM address를 선택하고 주소값에 RAM의 주소 지정
{unsigned short command=0x00;
 if (CG_or_DD>0) command=0x80;
 command|=pos;//1xxxxxxx for DD RAM, 01xxxxxx for CG RAM
 setcommand(command); //Table 4.1의 (7), (8)과 그 아래참조
}

void clcd_exit(void)//mmap으로 만들어진 모든 mapping을 제거
{/* clcd_clear(); */ munmap(CLCD_CMD,2); munmap(CLCD_DATA,2);
}



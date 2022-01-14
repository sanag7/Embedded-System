#include "main.h"


//variables declare----------------------------------------------------------------
static struct termios initial_settings, new_settings;
static int peek_character=-1;

static unsigned char ans1[]={'1','3','4','7','4','3','7','3','8','6','3'};
static unsigned char ans2[]={'9','7','4','7','2','4','6','7','6','2','4'};
static unsigned char ans3[]={'1','6','7','5','2','6','2','3','8','4','9'};
static unsigned char ans4[]={'5','7','6','1','8','9','3','2','4','7','1'};
static unsigned char ans5[]={'4','8','7','3','2','5','7','6','8','1','9'};
static unsigned char *keyin, *keyout;
static unsigned char keypad_matrix[4][4]={{'1','2','3','?'},{'4','5','6','?'},{'7','8','9','?'},{'R','C','T','?'}};
char vic[100]="WELDONE!", lose[100]="TRY AGAIN!";
int vic_len=8, lose_len=10;
char ins1[100]="Please Select:", ins2[100]="R or T";
int ins1_len=14, ins2_len=6;
char bye[100]="Terminating...";
int bye_len=14;
char go[100]="--Number Flash--";
int go_len=16;
int fd, fd0=0;
int col_no;
void            init_keyboard(void);
int             kbhit(void);
int             readch(void);
void            close_keyboard(void);


//main function---------------------------------------------------------------------
int main(int argc, char **argv)
{
//clcd 게임제목-------------------------------------------------------------------------
 int i, len1=11, len2=16, len3=3, len4=6, CG_or_DD=1;
 char buf1[100]="Memorize!!!", buf2[100]="--Number Flash--", buf3[100]="YOU", buf4[100]="WIN!!!";
 char cmd;
 
 if(argc>1) {len3=strlen(argv[1]); strcpy(buf3,argv[1]);}
 if((fd=open("/dev/mem",O_RDWR|O_SYNC))<0)
   {perror("mem open failed\n");	exit(1);  }
 if(clcd_init()<0)//failed memory mapping in clcd_init() fail
   {close(fd); printf("mmap error in clcd_init()\n"); return -1;}
 initialize_clcd();
 for (i=0; i<len1; i++)	write_byte(buf1[i]);
 set_RAM_address(0x40, CG_or_DD);
 for (i=0; i<len2; i++) write_byte(buf2[i]);

 //LED------------------------------------------------------------------------------
  unsigned char val;
  LED=mmap(NULL,2,PROT_WRITE,MAP_SHARED,fd,FPGA_LED);
  if(!LED)
  {printf("failed memory mapping in led_mm \n"); return -(!LED);}
  val=0x00;
  *LED=~val;
  usleep(200000);

//manual
printf("--------------Number Flash!-------------------\n");
printf("Memorize the Numbers shown in Dot Matrix!\n");
printf("Press the keypad in order to win!\n");
printf("Number assigned to a keypad is shown below.\n");
printf("Number of attempts are indicated in FND.\n");
printf("Pressing Chance button adds count by 1 and shows the numbers again.\n\n");
printf("<Keypad setting>\n");
printf("[1]  [2]  [3]  [-]\n");
printf("[4]  [5]  [6]  [-]\n");
printf("[7]  [8]  [9]  [-]\n");
printf("[R]  [C]  [T]  [-]\n");
printf("-: Blank\n");
printf("R: Replay   C: Chance   T: Terminate\n\n");
printf("Press 's' to start.\n");
printf("-----------------------------------------------\n");

//press any key
init_keyboard();
cmd='r';//cmd의 초기값을 r로 설정

while(cmd !='s')
 {val=0xff; *LED=~val; usleep(500000);
  val=0x00; *LED=~val; usleep(500000);
 if(kbhit())
 {cmd=readch();}
 }
close_keyboard();


  
//Show Answer
back:
initialize_clcd();
 time_t t;
 srand((unsigned) time(&t));
 int num=(rand()%5);
 printf("Sequence number: %d\n",num+1);
 int col_len;
 unsigned char ans[8];
 if(num==0)
 {col_len=sizeof(dot_table1)/sizeof(dot_table1[0][0])/5; memcpy(ans, ans1, sizeof(ans1));}
 else if(num==1)
 {col_len=sizeof(dot_table2)/sizeof(dot_table2[0][0])/5; memcpy(ans, ans2, sizeof(ans2));}
 else if(num==2)
 {col_len=sizeof(dot_table3)/sizeof(dot_table3[0][0])/5; memcpy(ans, ans3, sizeof(ans3));}
 else if(num==3)
 {col_len=sizeof(dot_table4)/sizeof(dot_table4[0][0])/5; memcpy(ans, ans4, sizeof(ans4));}
 else
 {col_len=sizeof(dot_table5)/sizeof(dot_table5[0][0])/5; memcpy(ans, ans5, sizeof(ans5));}

unsigned char count[2]={0,0};
if (dot_init()<0) // Memory mapping in fnd_init() failed
        {close(fd); printf("mmap error in dot_init()\n"); return -1;}
 for (i=1; i<col_len; i++) 
  {dot_write(num,i); usleep(500000);
if(i%2==0) {val=0xAA; *LED=~val;}
else{val=0x55; *LED=~val;}
}
 usleep(1000);
 dot_clear();
 val=0x00; *LED=~val;


 

unsigned char *keyin0, Key_pressed;
 keyin=mmap(NULL, 2, PROT_READ|PROT_WRITE, MAP_SHARED, fd, KEY_IN_ADDR);
 keyout=mmap(NULL, 2, PROT_WRITE, MAP_SHARED, fd, KEY_OUT_ADDR);
if((int)keyin<0||(int)keyout<0)
  {keyin=NULL; keyout=NULL; close(fd);
   printf("mmap error!\n"); return -1;
 }
 
//fnd at restart
initialize_clcd();
 if (fnd_init()<0) // Memory mapping in fnd_init() failed
        {close(fd); printf("mmap error in fnd_init()\n"); return -1;}
 ;  

//Start Game
 count[0]++;
 int j=1;
 int trial=1;
for (i=0; i<go_len; i++)	write_byte(go[i]);
 while (j<col_len-1)
 {fnd_display(count,2); usleep(20000);
  dot_write(num,j);
  while(1)
  {for (col_no=0; col_no<SCAN_NUM; col_no++)
       {*keyout=(1<<(SCAN_NUM-1-col_no));
        *keyin0=*keyin;
	switch (*keyin0&0x0f)
	  {case 0x01: Key_pressed=keypad_matrix[0][col_no]; break;
	   case 0x02: Key_pressed=keypad_matrix[1][col_no]; break;
	   case 0x04: Key_pressed=keypad_matrix[2][col_no]; break;
	   case 0x08: Key_pressed=keypad_matrix[3][col_no]; break;
	   default: Key_pressed='?'; break;
	  }
	if(Key_pressed!='?') break;
	}
  if(Key_pressed!='?')
    {usleep(400000);
  if(Key_pressed=='C')//Chance
  {count[0]++;
if(count[0]>9)
	{count[0]=0; count[1]++;
	 if(count[1]>9) count[0]=count[1]=0;
	}
for (i=1; i<col_len; i++)
  {dot_write(num,i); usleep(200000);
   if(i%2==0) {val=0xAA; *LED=~val;}
   else{val=0x55; *LED=~val;}
  }
  usleep(1000000);
  dot_clear();
 val=0x00; *LED=~val;
  }
  else if(Key_pressed=='R')//Replay
  {dot_clear();
   fnd_clear();
   goto back;
  }
  else if(Key_pressed=='T')//Terminate
  {dot_clear();
   fnd_clear();
   goto quit;
  }
  else if(Key_pressed!=ans[j-1])//실패시
  {	initialize_clcd();
	for (i=0; i<lose_len; i++)	write_byte(lose[i]);
	dot_all(); val=0x55; *LED=~val; fnd_fail(); usleep(100000);
	dot_clear(); val=0x00; *LED=~val; fnd_clear(); usleep(100000);
	dot_all(); val=0x55; *LED=~val; fnd_fail(); usleep(100000);
	dot_clear(); val=0x00; *LED=~val; fnd_clear(); usleep(100000);
	dot_all(); val=0x55; *LED=~val; fnd_fail(); usleep(100000);
	dot_clear(); fnd_clear();
	usleep(300000);
        val=0x00; *LED=~val;
	j=1;	count[0]++;
if(count[0]>9)
	{count[0]=0; count[1]++;
	 if(count[1]>9) count[0]=count[1]=0;
	}
   }
   else//next step
   {j++;
   }
} //if(Key_pressed!='?')
  usleep(10000); 
  break;
 } //while(1)
 } //while(col)

//mission clear
dot_write(num,j);
initialize_clcd();
for (i=0; i<vic_len; i++)	write_byte(vic[i]);
val=0x80;
for (i=0; i<8; i++)
{val=(val>>1)|0x80; *LED=~val; usleep(30000);}
for (i=0; i<8; i++)
{val=(val<<1); *LED=~val; usleep(30000);}
for (i=0; i<8; i++)
{val=(val>>1)|0x80; *LED=~val; usleep(30000);}
for (i=0; i<8; i++)
{val=(val<<1); *LED=~val; usleep(30000);}
usleep(1500000);

initialize_clcd();
for (i=0; i<len3; i++)	write_byte(buf3[i]);
set_RAM_address(0x40, CG_or_DD);
for (i=0; i<len4; i++) write_byte(buf4[i]);
usleep(1500000);


initialize_clcd();//각종 제어명령 입력
 for (i=0; i<ins1_len; i++)	write_byte(ins1[i]);//buf1에 입력된 문자열의 길이만큼 반복문을 돌며 문자들을 디바이스의 첫째줄에  출력
 set_RAM_address(0x40, CG_or_DD);//into 2nd line of DD RAM
 for (i=0; i<ins2_len; i++) write_byte(ins2[i]);
while(1)
  {for (col_no=0; col_no<SCAN_NUM; col_no++)
       {*keyout=(1<<(SCAN_NUM-1-col_no));
        *keyin0=*keyin;
	switch (*keyin0&0x0f)
	  {case 0x01: Key_pressed=keypad_matrix[0][col_no]; break;
	   case 0x02: Key_pressed=keypad_matrix[1][col_no]; break;
	   case 0x04: Key_pressed=keypad_matrix[2][col_no]; break;
	   case 0x08: Key_pressed=keypad_matrix[3][col_no]; break;
	   default: Key_pressed='?'; break;
	  }
	if(Key_pressed!='?') break;
	}
  if(Key_pressed!='?')
    {usleep(400000);
     if(Key_pressed=='R')//Replay
  {dot_clear();
   goto back;
  }
  else if(Key_pressed=='T')//Terminate
   {break;
   }
} //if(Key_pressed!='?')
 } //while(1)

quit:
initialize_clcd();
for (i=0; i<bye_len; i++)	write_byte(bye[i]);
usleep(2000000);
initialize_clcd();

//Exit_all
  munmap(LED,2);
  munmap(keyin,2); munmap(keyout,2);
  clcd_exit();
  dot_exit();
  fnd_exit();
  close(fd);
  
  return 0; 
 }

//keyboard
void init_keyboard(void)
{tcgetattr(fd0, &initial_settings);
 new_settings=initial_settings;
 new_settings.c_lflag&=~ICANON;
 new_settings.c_lflag&=~ECHO;
 new_settings.c_lflag&=~ISIG;
new_settings.c_cc[VMIN]=1;
 new_settings.c_cc[VTIME]=0;
 tcsetattr(fd0, TCSANOW, &new_settings);
 }


void close_keyboard(void)
{tcsetattr(fd0, TCSANOW, &initial_settings);}

int kbhit(void)
{char ch;       int nread;
 if(peek_character!=-1) return -1;
 new_settings.c_cc[VMIN]=0;
 tcsetattr(0, TCSANOW, &new_settings);
 nread=read(0, &ch, 1);
 new_settings.c_cc[VMIN]=-1; tcsetattr(0, TCSANOW, &new_settings);
 if (nread==1) {peek_character=ch; return 1;}
 return 0;
}

int readch(void)
{char ch;
 if (peek_character!=-1){ch=peek_character; peek_character=-1; return ch;}
 read(0,&ch,1); return ch;
 }

//-------| lib/clcd.h |-------//
#ifndef	CLCD_H
#define	CLCD_H 


#include <unistd.h> // usleep()
#include <sys/mman.h>
#include <string.h>

#define FPGA_CLCD_WR	0x12300000//command
#define FPGA_CLCD_RS	0x12380000//data


int clcd_init(void);
void setcommand(unsigned short command);
void initialize_clcd(void);
void function_set(int DL, int N, int F);
void display_control(int D, int C, int B);
void cursor_shit(int set_screen, int set_rightshit);
void entry_mode_set(int ID, int S);
void return_home(void);
void clcd_clear(void);
void set_RAM_address(int pos, int CG_or_DD);
void clcd_exit(void);
void write_byte(char ch);

unsigned short *CLCD_CMD, *CLCD_DATA;


#endif

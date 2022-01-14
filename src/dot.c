#include "dot.h"

extern int fd;

//dot function define
int dot_init(void)
{int ierr=0;
 DOT_COL1=mmap(NULL, 2, PROT_WRITE, MAP_SHARED, fd, FPGA_DOT_COL1);
 DOT_COL2=mmap(NULL, 2, PROT_WRITE, MAP_SHARED, fd, FPGA_DOT_COL2);
 DOT_COL3=mmap(NULL, 2, PROT_WRITE, MAP_SHARED, fd, FPGA_DOT_COL3);
 DOT_COL4=mmap(NULL, 2, PROT_WRITE, MAP_SHARED, fd, FPGA_DOT_COL4);
 DOT_COL5=mmap(NULL, 2, PROT_WRITE, MAP_SHARED, fd, FPGA_DOT_COL5);//디바이스의 physical address를 메모리공간에 맵핑.
 ierr=(int)DOT_COL1+(int)DOT_COL2+(int)DOT_COL3+(int)DOT_COL4+(int)DOT_COL5;
 return ierr;
}

void dot_write1(int decimal)
{*DOT_COL1=dot_table1[decimal][0];
 *DOT_COL2=dot_table1[decimal][1];
 *DOT_COL3=dot_table1[decimal][2];
 *DOT_COL4=dot_table1[decimal][3];
 *DOT_COL5=dot_table1[decimal][4];
}

void dot_write2(int decimal)
{*DOT_COL1=dot_table2[decimal][0];
 *DOT_COL2=dot_table2[decimal][1];
 *DOT_COL3=dot_table2[decimal][2];
 *DOT_COL4=dot_table2[decimal][3];
 *DOT_COL5=dot_table2[decimal][4];
}

void dot_write3(int decimal)
{*DOT_COL1=dot_table3[decimal][0];
 *DOT_COL2=dot_table3[decimal][1];
 *DOT_COL3=dot_table3[decimal][2];
 *DOT_COL4=dot_table3[decimal][3];
 *DOT_COL5=dot_table3[decimal][4];
}

void dot_write4(int decimal)
{*DOT_COL1=dot_table4[decimal][0];
 *DOT_COL2=dot_table4[decimal][1];
 *DOT_COL3=dot_table4[decimal][2];
 *DOT_COL4=dot_table4[decimal][3];
 *DOT_COL5=dot_table4[decimal][4];
}

void dot_write5(int decimal)
{*DOT_COL1=dot_table5[decimal][0];
 *DOT_COL2=dot_table5[decimal][1];
 *DOT_COL3=dot_table5[decimal][2];
 *DOT_COL4=dot_table5[decimal][3];
 *DOT_COL5=dot_table5[decimal][4];
}

void dot_write(int m, int decimal)
{if(m==0) dot_write1(decimal);
 else if(m==1) dot_write2(decimal);
 else if(m==2) dot_write3(decimal);
 else if(m==3) dot_write4(decimal);
 else dot_write5(decimal);
}

void dot_clear(void)
{*DOT_COL1=0x00;
 *DOT_COL2=0x00;
 *DOT_COL3=0x00;
 *DOT_COL4=0x00;
 *DOT_COL5=0x00;//모든 column에 0을 출력시키면서 light off.
}

void dot_all(void)
{*DOT_COL1=0x7F;
 *DOT_COL2=0x7F;
 *DOT_COL3=0x7F;
 *DOT_COL4=0x7F;
 *DOT_COL5=0x7F;
}

void dot_exit(void)
{dot_clear();
 munmap(DOT_COL1,2); munmap(DOT_COL2,2); munmap(DOT_COL3,2);
 munmap(DOT_COL4,2); munmap(DOT_COL5,2);
}//mmap으로 만들어진 맵핑을 제거.




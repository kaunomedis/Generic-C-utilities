/* CRC calculation using HP1630 algorythm  */

#include <stdio.h>
#include <stdlib.h>

unsigned int CRC_table[256];

unsigned int HP_CRC(unsigned char *,int , int );

void HP_CRC_Initialise(unsigned int);


int main(int argc, char *argp[])
{
   unsigned int n,x,z;
   unsigned int crc;
   
   HP_CRC_Initialise(0x8005);
   
   crc = 0;
   printf("\n");
   for (z=1;z < argc;z++){
      n = sscanf(argp[z],"%x",&x);
      if (n!=1) {
         printf("\nUnable to interpret %s as a hex constant.\n",argp[z]);
         exit(1);
      }
      crc = (crc & 0xff00) ^ CRC_table[(crc ^ x) & 0xff];
   }
   printf("\nCRC = %04X",crc);
     
   printf("\n");
   
   exit(0);
   
}

/*  Generate table and perform CRC according to HP1630 requirements */




unsigned int HP_CRC(unsigned char *buffer,int length, int seed)
{
   int x=0;
   
   while (length > 0) {
      seed = (seed & 0xff00) ^ CRC_table[(seed ^ buffer[x++]) & 0xff];
      length--;
   }
   return(seed);
}
   
void HP_CRC_Initialise(unsigned int poly)
{
   unsigned int crc,x,y;
   
   for (x=0;x<256;x++) {
      crc = x;
      for (y=0;y<16;y++) {
         crc <<= 1;
         if (crc & 0x10000) crc ^= poly;
         crc &= 0xffff;
      }
      CRC_table[x] = crc;
   }
}

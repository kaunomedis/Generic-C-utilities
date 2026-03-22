#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BUFSZ 256

uint32_t table[255];

void init(void)
{
uint32_t poly=0xEDB88320;
uint32_t temp,i,j;

for (i=0;i<255;i++)
{
	temp=i;
	for(j=8;j>=1;j--)
		{
		if(temp & 1 ==1)
			{ temp=(temp>>1) ^ poly; }
			else
			{ temp=temp>>1;}
		}
	table[i]=temp;
}
}


uint32_t CRC32(uint8_t * bytes, uint32_t seed, uint32_t len)
{
//uint32_t crc =0xFFFFFFFF;
uint32_t crc =seed;
uint32_t i;
uint8_t index;
for(i=0;i<len;i++)
	{
		index=(uint8_t) (crc & 0xFF) ^ bytes[i];
		crc = (uint32_t) (crc>>8) ^ table[index];
	}
return crc;
}



int main(int argc, char *argv[])
{
   int i;
   
   unsigned char buf[BUFSZ] = {0};
   uint32_t bytes,readsz = BUFSZ, crcout;
   
if (argc==1) {printf ("Usage: %s file1.bin [, file2.bin ...]\n",argv[0]); return 0;}

else {
		init();
		for(i=1;i< argc;i++)
		{
		bytes=0;
		crcout=0xFFFFFFFF;	
	
		//FILE *fp = argc > 1 ? fopen (argv[i], "rb") : stdin;
		FILE *fp = fopen (argv[i], "rb");
		
		if (!fp) {
			fprintf (stderr, "error: file open failed '%s'.\n", argv[i]);
			return 1;
		}
		

		while ((bytes = fread (buf, sizeof *buf, readsz, fp)) == readsz)
		{
        //for (i = 0; i < readsz; i++)
        //    printf (" 0x%02x", buf[i]);
        //putchar ('\n');
		crcout=CRC32(buf,crcout,bytes);
		}
		//for (i = 0; i < bytes; i++) /* output final partial buf */
		//	{
		//	printf (" 0x%02x", buf[i]);
		//	putchar ('\n');
		//	}
		crcout=CRC32(buf,crcout,bytes);
			

    if (fp != stdin)
        fclose (fp);
		

		printf("%s CRC32= %08X\n",  argv[i],~crcout);

		
		}
   return 0;}
}
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main()
{
 int sock;
 struct sockaddr_in addr;

 sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP );

 addr.sin_family = AF_INET;
 addr.sin_port = htons(12345);
 addr.sin_addr.s_addr = inet_addr("192.168.244.1");

 while(1){

 int i;
 unsigned char s[10];
 
 FILE *fp1;
 char *fname1 = "Lenna1.raw";
 
 fp1 = fopen(fname1, "rb");
 if( fp1 == NULL ){
   printf( "%s ERROR\n", fname1 );
   return -1;
 }

 FILE *fp2;
 char *fname2 = "Lenna2.raw";

 fp2 = fopen(fname2, "rb");
 if( fp2 == NULL ){
   printf( "%s ERROR\n", fname2 );
   return -1;
 }

 FILE *fp3;
 char *fname3 = "Lenna3.raw";

 fp3 = fopen(fname3, "rb");
 if( fp3 == NULL ){
   printf( "%s ERROR\n", fname3 );
   return -1;
 }

 FILE *fp4;
 char *fname4 = "Lenna4.raw";

 fp4 = fopen(fname4, "rb");
 if( fp4 == NULL ){
   printf( "%s ERROR\n", fname4 );
   return -1;
 }

 
 unsigned long int j;
 unsigned char buf1[512 * 512 * 3];
 unsigned char buf2[512 * 512 * 3];
 unsigned char buf3[512 * 512 * 3];
 unsigned char buf4[512 * 512 * 3];

 fread(buf1, sizeof(unsigned char),512*512*3, fp1);
 fread(buf2, sizeof(unsigned char),512*512*3, fp2);
 fread(buf3, sizeof(unsigned char),512*512*3, fp3);
 fread(buf4, sizeof(unsigned char),512*512*3, fp4);

 while(1){
   for(j=0;j<512*4;j++){
     sendto(sock, &buf1[j*3*128], 3*128, 0, (struct sockaddr *)&addr, sizeof(addr));
   }
   usleep(60000);
   for(j=0;j<512*4;j++){
     sendto(sock, &buf2[j*3*128], 3*128, 0, (struct sockaddr *)&addr, sizeof(addr));
   }
   usleep(60000);
   for(j=0;j<512*4;j++){
     sendto(sock, &buf3[j*3*128], 3*128, 0, (struct sockaddr *)&addr, sizeof(addr));
   }
   usleep(60000);
   for(j=0;j<512*4;j++){
     sendto(sock, &buf4[j*3*128], 3*128, 0, (struct sockaddr *)&addr, sizeof(addr));
   }
   usleep(60000);
 }

 fclose(fp1);
 fclose(fp2);
 fclose(fp3);
 fclose(fp4);


 }

 close(sock);

 return 0;
}


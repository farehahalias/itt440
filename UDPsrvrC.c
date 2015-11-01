#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFLEN 512
#define PORT 1045

void die(char *s)
{
    perror(s);
    exit(1);
}

int main (void)
{
    struct sockaddr_in si_me,si_other;
    int s,i,slen = sizeof(si_other),recv_len,len,value,ret,on;
    char buf[BUFLEN];

     if((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
      {
        die("socket");
      }
//pitfall 4
     memset((char *)&si_me,0,sizeof(si_me));
     si_me.sin_family = AF_INET;
     si_me.sin_port = htons(PORT);
     si_me.sin_addr.s_addr  = htonl(INADDR_ANY);

     if( bind(s ,(struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
     {
       die("bind");
     }

    while (1)
     {
      printf("waiting for data...");
      fflush(stdout);


     if((recv_len = recvfrom(s, buf,BUFLEN, 0, (struct sockaddr *)&si_other, &slen)) == -1)
      {
        die("recvfrom()");
      }

   printf("Received packet from %s :%d \n",inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
   printf("Data: %s \n", buf);

      if(sendto(s, buf, recv_len, 0, (struct sockaddr*)&si_other, slen) == -1)
       {
       die("sendto()");
       }

      //pitfall 1
      getsockopt(s,SOL_SOCKET,SO_SNDBUF,&value,&len);
      if(value == 0)

        {
         printf("Error! Unable Get: %d \n",errno);
         printf("Error Description: %d\n",strerror(errno));
        }
      else
        printf("SUCESS!!! value: %d",&value);
      close(s);  //pitfall 2

      value = 32768;
      setsockopt(s,SOL_SOCKET,SO_SNDBUF,&value,sizeof(value));
      printf("Set !! \n");

      getsockopt(s,SOL_SOCKET,SO_SNDBUF, &value, &len);
      if(value == 0)
        printf("Unable Get New \n");
      else
        printf("Can Get New %d\n ",value);

//pitfall 3
     on = 1;
      ret = setsockopt(s,SOL_SOCKET,SO_REUSEADDR, &on, sizeof(on));
      memset( &si_me, 0,sizeof(si_me));
      si_me.sin_family = AF_INET;
      si_me.sin_addr.s_addr = htonl(INADDR_ANY);si_me.sin_port = htons(45000);
    //  ret = bind(sock,(struct si_me*)&si_me,sizeof(si_me));
   }
  close(s);
  return 0;
}


#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>

int main (int argc, char *argv[])
{
   int socket_desc, client_sock, c, read_size,value,len;
   struct sockaddr_in server, client;
   struct timeval timeo;
   char client_message[2000];

   socket_desc = socket(AF_INET , SOCK_STREAM, 0);
     if(socket_desc == -1)
        {
           printf("Could not create socket");
         }
       puts("Socket created");

   server.sin_family = AF_INET;
   server.sin_addr.s_addr = htonl(INADDR_ANY);
   server.sin_port = htons(8888);

  if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server))<0)
       {perror("bind failed. Error");
         return 1;}
       puts("bind done");

      listen(socket_desc, 3);

     puts("waiting for incoming connections..");
     c = sizeof(struct sockaddr_in);

  client_sock = accept(socket_desc,(struct sockaddr*)&client,(socklen_t*)&c);
        if(client_sock < 0)
          {
            perror("accept failed");
            return 1;
          }
       puts("Connection accepted");

        getsockopt(socket_desc, SOL_SOCKET, SO_SNDBUF, &value, &len);
        if(value == 0)
          printf("Unable Get \n");
        else
           printf("Can Get %d\n ",value);
        
        value = 32768;
        setsockopt( socket_desc, SOL_SOCKET,SO_SNDBUF,&value, sizeof(value));
         printf("Set !! \n ");

        getsockopt(socket_desc, SOL_SOCKET, SO_SNDBUF, &value, &len);
        if(value == 0)
          printf("Unable Get New\n");
        else
           printf("Can Get New %d\n ",value);



          return 0;
}

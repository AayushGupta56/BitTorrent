#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
using namespace std;

int main(){
   
   //creating socket
   int listening_socket,client_socket;
   listening_socket=socket(AF_INET,SOCK_STREAM,0);
   if(listening_socket==-1){cout<<"can't create socket"; return 0;}


   //binding the socket with ip and port
    sockaddr_in server,client;
    server.sin_family=AF_INET;//af_inet as ipv4
    server.sin_port=htons(54000);//host to network short as port cannot be send directly as int 
    server.sin_addr.s_addr=INADDR_ANY;
    memset(server.sin_zero,8,0);

    unsigned len =sizeof(sockaddr_in);//???

    if((bind(listening_socket,(sockaddr*)&server,len))==-1)
    {cout<<"can't find";
       return 0;
    }

     //start listning
    if(listen(listening_socket,10)==-1){
    	cout<<"can't listen";
    	return 0;
    }


   //wait for connection
   if((client_socket=accept(listening_socket,(sockaddr*)&client,&len))==-1)
   {
   	cout<<"can't accept";
   	return 0;
   }
   else{cout<<"Connected"<<endl;}
   //close the listning socket
   close(listening_socket);
     
   //while loop send recieve
    char input[400];
    string msg;

    while(1){
     //waiting for client to send mssg
    	memset(input,400,0);
      int char_recieved = recv(client_socket,input,400,0);
       if(char_recieved>0){
       //sending same mssg back
       	int sent= send(client_socket,input,char_recieved+1,0);
       cout<<"sent "<<sent<<" bytes to you "<<inet_ntoa(client.sin_addr)<<endl;//???


       }

    } 

   //close socket
   close(client_socket);




}

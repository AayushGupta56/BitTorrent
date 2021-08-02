#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
using namespace std;

int main(){

	string ipAddress ="127.0.0.1";
	int port =54000;

	// creaate socker

	int client = socket(AF_INET,SOCK_STREAM,0);
	if(client == -1){
		cerr<<"Can't create socket";
	return 0;
	      }


	//filling sockaddr_in structure

	sockaddr_in hint;
	hint.sin_family =AF_INET;
	hint.sin_port=htons(port);
	inet_pton(AF_INET,ipAddress.c_str(),&hint.sin_addr);

    // Connect to server

    int conResult=connect(client,(sockaddr*)&hint,sizeof(hint));

    if(conResult==-1){

      cerr<<"Cant't connect";
      return 0;
           }
     else{cout<<"Connected";}      

      //do while loop :send and recv data

 
     char buf[4096];
     string msg;

     do{
     	
     	//prompt user to send something 
     	
     	getline(cin ,msg);
     	if(msg.length()>0){

     		//sending mssg back to server
     		memset(buf,4096,0);
     		int sent =send(client,msg.c_str(),msg.size()+1,0);
     		if(sent!=-1){

     			//wait for response
     			memset(buf,4096,0);
     			int bytesRecieved = recv(client,buf,4096,0);

     		   if(bytesRecieved>0){

     		   	//print hello and name recieved
     		   	cout<<"server> Hello "<<string(buf,0,bytesRecieved)<<endl;
     		   }
     		}
     	}

     }while(msg.length()>0);
     //close the socket
     close(client);
      return 0;
  }

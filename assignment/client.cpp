#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 

// Client code for the assignment

int main(int argc, char* argv[]) 
{ 
    int sock; 
    struct sockaddr_in addrinfo; 
    char server_reply[1024]; 
    int i, temp; 
    int number[10] = { 5, 4, 3, 8, 9, 1, 2, 0, 6 };

    // Create the client socket 
    sock = socket(AF_INET, SOCK_STREAM, 0); 

    if (sock == -1) { 
        puts("Could not create socket"); 
    } else {
        puts("Socket created"); 
    }
      
    //config sockaddr_in structure
    addrinfo.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    addrinfo.sin_family = AF_INET;
    addrinfo.sin_port = htons(8880); 
  
    // Connect to remote server
    if (connect(sock, (struct sockaddr*)&addrinfo, sizeof(addrinfo)) == -1) {
        puts("Connection failed");
    } else {
        puts("Connection succesful");
    }
  
    // send the array
    if (send(sock, &number, 10 * sizeof(int), 0) == -1) { 
        puts("Send failed");
    } 
  
    // receive the reply array
    if (recv(sock, &server_reply, sizeof(server_reply), 0) == -1) { 
        puts("Receive failed");
    } 

    //print the reply array
  
    puts("Server reply :\n"); 
    for (i = 0; i < 5; i++) { 
        printf("%c\n", server_reply[i]); 
    } 
  
    // close the socket 
    close(sock); 
    return 0; 
} 

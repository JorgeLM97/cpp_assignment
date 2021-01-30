
#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 

// Server code for the assignment
  
int main(int argc, char* argv[]) 
{ 
    int server_sock, client_sock, c, read_size; 
    struct sockaddr_in server, client; 
    int message[10], i; 
    char replyx[6] = "XYXYX";

    // Create the server socket 
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if (server_sock == -1) { 
        printf("Could not create socket"); 
    } 
    puts("Socket created"); 
  
    // config sockaddr_in structure 
    server.sin_family = AF_INET; 
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htons(8880); 
  
    // Bind the socket 
    if (bind(server_sock, (struct sockaddr*)&server, sizeof(server)) < 0) { 
        perror("Bind error");
    } else {
        puts("Bind succesful");
    }

    // listen to the socket 
    listen(server_sock, 3); 
  
    puts("Waiting for incoming connections..."); 
    c = sizeof(struct sockaddr_in); 
  
    // accept connection from an incoming client 
    client_sock = accept(server_sock, (struct sockaddr*)&client, (socklen_t*) &c); 
  
    if (client_sock < 0) { 
        puts("Accept failed");
    } else {
        puts("Connection accepted"); 
    }  
  
    // Receive a message from client 
    while ((read_size = recv(client_sock, &message, 10 * sizeof(int), 0)) > 0) { 

        send(client_sock, &replyx, sizeof(replyx), 0);
    } 
  
    if (read_size == 0) { 
        puts("Client disconnected"); 
    } 
    else if (read_size == -1) { 
        perror("recv failed"); 
    } 
  
    return 0; 
} 
  

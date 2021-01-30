#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <stdlib.h>      // rand, srand
#include <time.h>        // time
#include <bits/stdc++.h> //sort
using namespace std;

// Client code for the assignment


//Function returns a pointer to a static array with 10 numbers randomly generated using rand(), with a range of rngRange beginning at rngStart
int * rngArray (int rngRange, int rngStart){

    static int generatedArray [10];

    srand(time(NULL));

    for (int i = 0; i != 10; i++){
            generatedArray[i] = rand() % rngRange + rngStart;
            // printf("%d ", rngArray[i]); //print the generated array
        }
    return generatedArray;

}

int main(int argc, char* argv[]) 
{ 
    int sock; 
    struct sockaddr_in addrinfo; 
    char server_reply[1024]; 
    int i, temp; 
    int number[10];
    int *rnumber;

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
    
    // generate the random array
    rnumber = rngArray(20, 1);

    for (int i = 0; i != 10; i++)
        printf("%d ", rnumber[i]);  //print unsorted array
        
    puts ("");

    // sort it
    sort(rnumber, rnumber + 10);

    for (int i = 0; i != 10; i++)
        printf("%d ", rnumber[i]); //print sorted array

    puts("");

    // send the array
    if (send(sock, &rnumber, 10 * sizeof(int), 0) == -1) { 
        puts("Send failed");
    } 
  
    // receive the reply array
    if (recv(sock, &server_reply, sizeof(server_reply), 0) == -1) { 
        puts("Receive failed");
    } 

    //print the reply array
  
    puts("Transmission succesful: "); 
    for (i = 0; i < 5; i++) { 
        printf("%c", server_reply[i]); 
    } 
    puts("");

    // close the socket 
    close(sock); 
    return 0; 
} 

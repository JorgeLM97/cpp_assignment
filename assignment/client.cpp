#include <stdio.h>       // input/output
#include <string.h>      // string
#include <arpa/inet.h>   // socket communication
#include <sys/socket.h>  // socket communication
#include <cstdio>        // freopen
#include <stdlib.h>      // rand, srand
#include <time.h>        // time
#include <bits/stdc++.h> // sort
#include <unistd.h>
#include <termios.h>     // getch
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

// Linux implementation for getch(), not available natively
char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    printf("%c\n", buf);
    return buf;
 }

int main(int argc, char* argv[]) 
{ 
    int sock; 
    struct sockaddr_in addrinfo; 
    char server_reply[1024]; 
    int i, temp;
    int *rnumber;
    char exitchar;
     string logPath;

    //get path
    puts("write path to txt log file:");
    cin >> logPath;

    // Array generation

    // generate the random array
    rnumber = rngArray(20, 1);

    // sort it
    sort(rnumber, rnumber + 10);

    // Create the client socket 
    sock = socket(AF_INET, SOCK_STREAM, 0); 
      
    //config sockaddr_in structure
    addrinfo.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    addrinfo.sin_family = AF_INET;
    addrinfo.sin_port = htons(8881); 
  
    // Connect to remote server
    connect(sock, (struct sockaddr*)&addrinfo, sizeof(addrinfo));
        

    // send the array
    if (send(sock, rnumber, 10 * sizeof(int), 0) == -1){
        if(freopen(logPath.c_str(), "a", stdout)) {
            printf("C: Transmission failed!: send \n");
            fclose(stdout);
        }
    }
    // receive the reply array
    if (recv(sock, &server_reply, sizeof(server_reply), 0) == -1){
        if(freopen(logPath.c_str(), "a", stdout)) {
            printf("C: Transmission failed!: receive \n");
            fclose(stdout);
        }
    }

    unsigned int microsecond = 1000000;
    usleep(1 * microsecond); //sleeps for 1 second while send finishes to avoid writing simultaneously to the same file
    //print the reply
    if(freopen(logPath.c_str(), "a", stdout)) {
            printf("C: Transmission succeded! Message from server: ");
            fclose(stdout);
        }

    for (i = 0; i < 5; i++){
        if(freopen(logPath.c_str(), "a", stdout)) {
            printf("%c", server_reply[i]); 
            fclose(stdout);
        }
    }

    if(freopen(logPath.c_str(), "a", stdout)) {
            printf("\n");
            fclose(stdout);
         }

    // close the socket 
    close(sock);

    //press any key to close the app and log it
    exitchar = getch();

    if(freopen(logPath.c_str(), "a", stdout)) {
        printf("C: Exit character: %c \n", exitchar);
        fclose(stdout);
    }

    return 0; 
} 

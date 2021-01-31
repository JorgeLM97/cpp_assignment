
#include <arpa/inet.h>  // socket communication
#include <stdio.h>      // input/output
#include <iostream>
#include <string.h>     // string
#include <sys/socket.h> // socket communication
#include <cstdio>       // freopen
#include <unistd.h>     // getch
#include <termios.h>    // getch
using namespace std;
// Server code for the assignment

//Function returns a factorial from a given number and checks whether it is bigger than 100 000 000 000
void factorialCheck ( int factorialNumber, string path) {
    unsigned long long factorialResult = 1;

    //Calculate factorial
    for(int i = 1; i <= factorialNumber; i++){
        factorialResult *= i;
    }

    //Check if it is bigger than 100 000 000 000
    if (factorialResult < 100000000000){
        if(freopen(path.c_str(), "a", stdout)) {
            printf("S: Factorial of %d is: %llu\n", factorialNumber, factorialResult);
            fclose(stdout);
         }
    }
}

// Linux implementation for getch(), not available natively. On windows it works.
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
    return buf;
 }
  
int main(int argc, char* argv[]) 
{ 
    int server_sock, client_sock, c, read_size, i; 
    struct sockaddr_in server, client; 
    int message[10]; 
    char replyx[6] = "XXXXX";
    char exitchar;
    string logPath;

    //get path
    puts("write path to txt log file:");
    cin >> logPath;

    // Create the server socket 
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
  
    // config sockaddr_in structure 
    server.sin_family = AF_INET; 
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htons(8881); 
  
    // Bind the socket 
    bind(server_sock, (struct sockaddr*)&server, sizeof(server));
        

    // listen to the socket 
    listen(server_sock, 3); 
  
    c = sizeof(struct sockaddr_in); 
  
    // accept connection from an incoming client 
    client_sock = accept(server_sock, (struct sockaddr*)&client, (socklen_t*) &c); 
  
    // Receive a message from client 
    while ((read_size = recv(client_sock, &message, 10 * sizeof(int), 0)) > 0) { 
        
        //Notify received
        send(client_sock, &replyx, sizeof(replyx), 0);

        //Log list of numbers received
        if(freopen(logPath.c_str(), "a", stdout)) {
                printf("S: ");
                fclose(stdout);
            }
        for (int i = 0; i != 10; i++){
            if(freopen(logPath.c_str(), "a", stdout)) {
                printf(" %d ", message[i]);
                fclose(stdout);
            }
        }
           
         if(freopen(logPath.c_str(), "a", stdout)) {
            printf("\n");
            fclose(stdout);
         }
        
        //Calculate and check factorials
        for (int i = 0; i != 10; i++)
            factorialCheck(message[i], logPath);
        
        if(freopen(logPath.c_str(), "a", stdout)) {
            printf("\n");
            fclose(stdout);
         }
    }
    
    //press any key to close the app and log it
    exitchar = getch();

    if(freopen(logPath.c_str(), "a", stdout)) {
        printf("S: Exit character: %c \n", exitchar);
        fclose(stdout);
    }
    
    return 0;
    
} 

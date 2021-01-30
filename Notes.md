# Network using sockets

## Pointers

*x = value at the adress x
&n = pointer of the value n

## Order

### 1. getaddrinfo()

```cpp
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
    
    int getaddrinfo(const char *node,     // e.g. "www.example.com" or IP
                    const char *service,  // e.g. "http" or port number
                    const struct addrinfo *hints,
                    struct addrinfo **res);
```

### TODO

study commands from sockets
CLIENT

sock = socket(***)

server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8880);

connect

send

receive

close

SERVER

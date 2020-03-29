#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <ctype.h>
#include <arpa/inet.h>


int main(int argc, char* argv[])
{
    int sockFd = 0;
    int ret = 0;
    socklen_t addrLen = 0;
    struct sockaddr_in addrIn;
    struct sockaddr_in addrClient;
    socklen_t lenClient = 0;
    int clientFd = 0;

    sockFd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockFd < 0)
    {
        printf("@@@ create socket failed!\n");
        return -1;
    }

    addrLen = sizeof(addrIn);
    addrIn.sin_family = AF_INET;
    addrIn.sin_port = htons(9987);
    addrIn.sin_addr.s_addr = inet_addr("127.0.0.1");
    ret = bind(sockFd, (struct sockaddr*)&addrIn, addrLen);

    ret = listen(sockFd, 5);
    char buf[64] = {0};
    int i = 0;
    while(1)
    {
        printf("@@@ server waiting!\n");
        clientFd = accept(sockFd, (struct sockaddr*)&addrClient, &lenClient);
        if(clientFd != -1)
        {
            read(clientFd, buf, sizeof(buf));
            for(i=0;i<sizeof(buf);i++)
            {
                buf[i] = toupper(buf[i]);
            }
            write(clientFd, buf, sizeof(buf));
            close(clientFd);
        }
    }

    close(sockFd);

    
    return 0;
}

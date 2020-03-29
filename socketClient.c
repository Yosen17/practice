#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int sockFd = 0;
    int ret = 0;
    socklen_t addrLen = 0;
    struct sockaddr_in addrIn;

    sockFd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockFd < 0)
    {
        printf("@@@ create socket failed!\n");
        return -1;
    }

    addrLen = sizeof(addrIn);
    bzero(&addrIn, sizeof(addrIn));
    addrIn.sin_family = AF_INET;
    addrIn.sin_port = htons(9987);
    addrIn.sin_addr.s_addr = htonl(INADDR_ANY);
    ret = connect(sockFd, (struct sockaddr*)&addrIn, addrLen);
    if(ret != 0)
    {
        printf("@@@ socket connect failed! errno %d: %s\n", errno, strerror(errno));
        return -1;
    }

    char buf[64] = {0};
    snprintf(buf, sizeof(buf), "this is a test!");
    
    write(sockFd, buf, sizeof(buf));
    printf("@@@ send: %s\n", buf);

    read(sockFd, buf, sizeof(buf));
    printf("@@@ recv: %s\n", buf);

    close(sockFd);
    return 0;
}
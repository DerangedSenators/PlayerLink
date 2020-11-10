//
// Created by hanzalah on 08/11/2020.
//

#include <io.h>
#include "ServerSocket.h"




void socketActions(int sockfd){
    char buff[MAX];
    int n;

    // Inf process for server listening
    for(;;){
        clearBuffer(buff);

        // Read the message from a client and copy it into a buffer
        read(sockfd,buff,sizeof(buff));
        processInput(buff);
        clearBuffer(buff);
        n = 0;


    }
}


void clearBuffer(char *buffer){
    memset(buffer,0,MAX);
}


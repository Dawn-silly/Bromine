#ifndef CHAT_H
#define CHAT_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <processthreadsapi.h>
#include <winsock2.h>

#include "../config_reader/config_reader.h"

typedef struct RECEIVE_ARGS
{
    SOCKET sender;
    bool *in_chat;
}
RECEIVE_ARGS;

typedef struct SEND_ARGS 
{
    SOCKET destination;
    char *buffer;
    int buffer_size;
}
SEND_ARGS;

DWORD WINAPI Receiving(LPVOID receive_args);
void Sending(SOCKET dest, char *buffer, int buffer_size);

#endif
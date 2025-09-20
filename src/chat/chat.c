#include "chat.h"

DWORD WINAPI Receiving(LPVOID receive_args)
{
    RECEIVE_ARGS *args = (RECEIVE_ARGS *)receive_args;
    
    int buffer_size = GetBufferSize();
    char *buffer = malloc(buffer_size);
    memset(buffer, 0, buffer_size);

    while (true)
    {
        int result = recv(args->sender, buffer, buffer_size - 1, 0);
        int len = strlen(buffer);

        if (result == buffer_size - 1 && len > 1)
        {
            char *output = malloc(len);
            strcpy(output, buffer);

            printf("\t\t(opponent's message) >> %s", output);
            free(output);
        }
        if (result == -1)
        {
            *(args->in_chat) = false;
            memset(buffer, 0, buffer_size);
            ExitThread(0);
        }
        memset(buffer, 0, buffer_size);
    }
}

void Sending(SOCKET dest, char *buffer, int buffer_size)
{   
    fgets(buffer, buffer_size, stdin);
    send(dest, buffer, buffer_size, 0);
    memset(buffer, 0, buffer_size);
}
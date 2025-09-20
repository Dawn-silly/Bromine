#include "config_reader.h"

int GetPort()
{
    char port[5];

    FILE *file = fopen("assets/data/port.txt", "r");
    fgets(port, sizeof(port), file);

    return atoi(port);
}

bool GetIP(char *ip)
{
    FILE *file = fopen("assets/data/ip.txt", "r");
    fgets(ip, 15, file);

    return true;
}

int GetBufferSize()
{
    char buffer[5];
    
    FILE *file = fopen("assets/data/buffer.txt", "r");
    fgets(buffer, 5, file);

    return atoi(buffer);
}
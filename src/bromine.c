#include <stdio.h>
#include <stdlib.h>

#include "client/client.h"
#include "host/host.h"

int main()
{
    char c[1];
    printf("Select a category:\nh = host\nc = client\nyour choice: ");
    scanf("%c", c);

    if (*c == 'h') StartHosting();
    if (*c == 'c') StartClient();

    return 0;
}
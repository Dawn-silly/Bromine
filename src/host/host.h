#ifndef HOST_H
#define HOST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <winsock2.h>
#include <ws2tcpip.h>

#include "../chat/chat.h"
#include "../config_reader/config_reader.h"

bool StartHosting();

#endif
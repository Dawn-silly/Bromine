#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int GetPort();
bool GetIP(char *ip);
int GetBufferSize();

#endif
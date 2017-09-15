/**************************************************

alpha.h

header and dependencies for alpha.c

**************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "RS-232/rs232.h"

#define NULL_CHAR 0
#define ADDR_START 1
#define CMD_START 2
#define DATA_END 3
#define CMD_END 4

int send_alpha_command(char * command, char * data, int needresponse);



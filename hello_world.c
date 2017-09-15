/**************************************************

hello_world.c

Sends "hello world" message to alpha sign.

**************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "RS-232/rs232.h"
#include "alpha.h"

int main()
{
  send_alpha_command("F ", "", 1); // try reading the time the sign thinks it is

  send_alpha_command("F\"", "", 1); // try reading some general info

  send_alpha_command("E,", "", 0); // do a soft reset

  sleep (30); // wait for the soft reset to finish

  send_alpha_command("E$", "", 0); // clear memory
  send_alpha_command("E$", "AAU0100FFFF", 0); // set memory for text file A: 256 bytes -- always display
  send_alpha_command("AA", "\x1B&b\x1c""1Hello world!", 0); // write to text file A
    //  \x1B esc pg 18 table 12 section C
    // & display on bottom line : pg 18 table 12 section D
    // b text hold mode pg 18 table 12 section G and pg 89
    // \x1C colour 1 == red (pg 57 in the Basic code)

  // let's try asking what's in text file A
  send_alpha_command("BA", "", 1); // read from text file A

  return 0;
}




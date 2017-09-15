/**************************************************

alpha.c

implements alpha sign communications protocol

**************************************************/

#include "alpha.h"

const int autobaud_len = 20, // must be at least 5.
          header_len = 5,
          cport_nr = 16,
          bdrate = 9600;
const char * mode = "7E1"; // the basic program has 9600, 7 data, even, 1 stop
const char to_all_signs[] = {ADDR_START, 'Z', '0', '0', CMD_START, 0}; // Send the following to all signs

int send_alpha_command(char * command, char * data, int needresponse) {
  const int offset1 = autobaud_len,
            offset2 = offset1 + header_len,
            offset3 = offset2 + strlen(command),
            offset4 = offset3 + strlen(data);
  const int len = offset4 + 1;
  unsigned char buffer[len];
  int n;
  
  for (int i = 0; i < len; i++) {
    if (i < offset1) {
      buffer[i] = 0;
    } else if (i < offset2) {
      buffer[i] = to_all_signs[i - offset1];
    } else if (i < offset3) {
      buffer[i] = command[i - offset2];
    } else if (i < offset4) {
      buffer[i] = data[i - offset3];
    } else {
      buffer[i] = CMD_END;
    }
  }
  
  if (RS232_OpenComport(cport_nr, bdrate, mode)) {
    printf("Can not open comport\n");
    return(0);
  }
  
  n = RS232_SendBuf(cport_nr, buffer, len);
  
  printf("Wrote %i bytes:\n", n);
  for (int i = 0; i < n; i++) {
    if (buffer[i] < 32) {
      printf("^%c", buffer[i] + 64); // print readable control characters
    } else {
      printf("%c", buffer[i]);
    }
  }
  printf("\n");

  if (needresponse) {
    n = RS232_PollComport(cport_nr, buffer, 256);

    printf("read %i bytes:\n", n);
    for (int i = 0; i < n; i++) {
      if (buffer[i] < 32) {
        printf("^%c", buffer[i] + 64); // print readable control characters
      } else {
        printf("%c", buffer[i]);
      }
    }
    printf("\n");
  }

  RS232_CloseComport(cport_nr);
  return(n);
}



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

// Good reference: https://people.csail.mit.edu/albert/bluez-intro/x502.html

int main() {
    int curr_sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    if (curr_sock == -1) {
        perror(NULL);
        exit(1);
    }

    close(curr_sock);
    return 0;
}
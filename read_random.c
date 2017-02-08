#include <stdio.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>

#define ENTROPY_NEEDED 32

int read_random(char* name)
{
    int fd;
    int try_read = 0;
    unsigned char tmpbuf[ENTROPY_NEEDED];

    if ((fd = open(name, O_RDONLY)) >= 0) {

        struct pollfd pset;
        
        pset.fd = fd;
        pset.events = POLLIN;
        pset.revents = 0;
        
        if (poll(&pset, 1, 1) >= 0) {
            try_read = (pset.revents & POLLIN) != 0;
        }

        if (try_read) {
            int r;
            r = read(fd, tmpbuf, ENTROPY_NEEDED);
            if (r == ENTROPY_NEEDED) {
                printf("Successfully read the entropy needed!\n");
                return 0;
            }
            else {
                printf("ERROR: could only read %d bytes of entropy...\n", r);
                return -1;
            }
        }
        else {
            printf("ERROR: file not available for reading\n");
            return -1;
        }

    }
    else {
        printf("ERROR: could not open file\n");
        return -1;
    }
}

int main()
{
    int ret;

    printf("off we go\n");

    ret = read_random("/dev/urandom");

    printf("bye bye!\n");

    return ret;
}

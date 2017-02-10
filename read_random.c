#include <stdio.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define ENTROPY_NEEDED 32

#define UNUSED(x) (void) (x)

static volatile int stop = 0;
static unsigned int loopcount = 0;

void handler(int sig)
{
    UNUSED(sig);

    //printf("Signal received\n");
    stop = 1;
}

int read_random(char* name)
{
    int fd;
    int try_read = 0;
    unsigned char tmpbuf[ENTROPY_NEEDED];

    signal(SIGINT, handler);

    while (1) {
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
                    //printf("Successfully read the entropy needed!\n");
                    loopcount++;
                    if (loopcount % 10000 == 0) {
                        printf("Again 10000 successful reads of entropy\n");
                    }
                }
                else {
                    printf("ERROR: could only read %d bytes of entropy...(errno=%d)\n", r, errno);
                }
            }
            else {
                printf("ERROR: file not available for reading\n");
                return -1;
            }

            if (close(fd) != 0) {
                printf("ERROR: could not close fd\n");
            }
        }
        else {
            printf("ERROR: could not open file\n");
            return -1;
        }
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

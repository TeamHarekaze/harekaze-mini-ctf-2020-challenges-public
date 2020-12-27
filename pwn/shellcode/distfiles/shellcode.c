#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

char binsh[] = "/bin/sh";

int main(void) {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    printf("Present for you! \"/bin/sh\" is at %p\n", binsh);
    puts("Execute execve(\"/bin/sh\", NULL, NULL)");

    char *code = mmap(NULL, 0x1000, PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    // Clear rsp and rbp
    memcpy(code, "\x48\x31\xe4\x48\x31\xed", 6);
    read(0, code + 6, 0x100);
    mprotect(code, 0x1000, PROT_READ | PROT_EXEC);

    ((void (*)())(code))();

    return 0;
}

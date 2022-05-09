#include <iostream>
#include <unistd.h>
#include <sys/types.h>
int main(int argc, char* argv[]) {
while (fork() % 10 != 0) {
sleep(1);
}
return 0;
}

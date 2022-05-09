#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int i;
    for (i=0;i<atoi(argv[1]); i++) {
	fork();
	std::cout << "Forking " << getpid() <<  " i = " << i << std::endl;
	sleep(1);
    }
    return 0;
}

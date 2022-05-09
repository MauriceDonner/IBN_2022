#include <iostream>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int i=0;
    int a = fork();
    if (a!=0) {
	i++;
	std::cout <<  "i = " << i << std::endl;
	std::cout << "erster " << a << ", i = " << i << std::endl;
    }
    if (i!=1) {
	int b = fork();
	std::cout << "zweiter " << b << ", i = " << i << std::endl;
    }
    int c = fork();
    std::cout << "dritter " << c << ", i = " << i << std::endl;
    return 6;
}

#include <iostream>
#include <string>

using namespace std;

int main() {
    string a = "001";

    const char b = a[2];
    const char c = '1';

    if (b=='1') cout << "WAS" << endl;

    cout << b << endl;
    return 0;
}

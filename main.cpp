#include <iostream>
#include "slae.h"

using namespace std;

int main()
{
    int m, n;
    std::cout << "Input amount of equations: " << std::endl;
    std::cin >> m;
    std::cout << "Input amount of variables: " << std::endl;
    std::cin >> n;
    Slae<double> s(m, n);
    std::cin >> s;
    s.solve();
    std::cout << s;
    return 0;
}

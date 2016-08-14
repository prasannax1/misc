#include <iostream>
#include <functional>

std::function<int(int)> transform(int i) {
    return [i](int x) { 
        return i + x; 
    };
}

int main() {
    auto f = transform(3);
    std::cout << "f(4) = " << f(4) << std::endl;
}

#include <iostream>

class factIter {
    public:
        factIter(int n)
            : _end(n)
            , _i(0)
            , _fact(1) {
        }

        bool operator!= (const factIter& other) const {
            return _i != _end;
        }

        int operator* () const {
            return _fact;
        }

        const factIter& operator++ () {
            _i++;
            _fact *= _i;
            return *this;
        }

        factIter begin() {
            return *this;
        }

        factIter end() {
            return *this;
        }

    private:
        int _end;
        int _i;
        int _fact;
};

int main() {
    auto i = 0;
    for (auto x: factIter(10)) {
        std::cout << i++ << "! = " << x << std::endl;
    }
}

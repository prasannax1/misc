#include <iostream>
#include <functional>
#include <vector>

template <typename T>
class Mapper {
    public:
        Mapper(std::vector<T> v, std::function<T (T)> f)
            : _fun(f)
            , _nums(v) {
            _iter = v.begin();
        }

        bool operator!= (const Mapper& other) const {
            return _iter != _nums.end();
        }

        T operator* () const {
            return _fun(*_iter);
        }

        const Mapper& operator++ () {
            ++_iter;
            return *this;
        }

        Mapper begin() {
            return *this;
        }

        Mapper end() {
            return *this;
        }

    private:
        std::function<T (T)> _fun;
        std::vector<T> _nums;
        typename std::vector<T>::iterator _iter;
};

int main() {
    for (auto val : Mapper<double>({1.5,2.4,3.2,4.8}, [](double i){return 2*i;})) {
        std::cout << val << std::endl;
    }
}

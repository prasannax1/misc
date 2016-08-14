#include <iostream>
#include <functional>

class Operand {
    public:
        Operand(char op, double x, double y) : _op(op), _x(x), _y(y) {}
        char op() const { return _op; }
        double x() const { return _x; }
        double y() const { return _y; }

    private:
        char _op;
        double _x;
        double _y;
};

class Calculator {
    public:
        Calculator() {
            _a['+'] = [](double x, double y) { return x+y; };
            _a['-'] = [](double x, double y) { return x-y; };
            _a['*'] = [](double x, double y) { return x*y; };
            _a['/'] = [](double x, double y) { return x/y; };
        }

        double calculate(const Operand& o) const {
            return _a[o.op()](o.x(), o.y());
        }

    private:
        std::function<double (double, double)> _a[256];
};

int main() {
    const auto o1 = Operand{'+', 3.5, 4.5};
    const auto o2 = Operand{'-', 3.5, 4.5};
    const auto o3 = Operand{'*', 3.5, 4.5};
    const auto o4 = Operand{'/', 3.5, 4.5};

    const auto c = Calculator{};

    for (auto& o: {o1, o2, o3, o4}) {
        std::cout <<
            o.x() << " " <<
            o.op() << " " <<
            o.y() << " = " <<
            c.calculate(o) <<
            std::endl;
    }
}


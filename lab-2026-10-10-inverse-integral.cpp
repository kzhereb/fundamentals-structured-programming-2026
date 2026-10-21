
#include <iostream>
#include <cassert>

// Задана функція. Перевірити, чи має вона на відрізку (a,b) обернену, якщо так, то обчислити визначений інтеграл функції Inverse(f) на цьому відрізку

// Inputs: function f(x); interval (a.b)
// Outputs: whether Inverse(f) exists on this interval; if yes - Integrate(a,b, Inverse(f(x)))
// Reference: https://en.wikipedia.org/wiki/Inverse_function

// f = function that shows how many prime numbers are in range (x, x^3)

double f(double x) {
    return x*x+2;
}

// returns true if function f has inverse function on interval (a,b)
// inverse exists if for any y there is only one x in (a,b)
// we consider criteria: function has inverse iff it is monotonous (either strictly increasing or strictly decreasing)
bool has_inverse(double a, double b) {
    assert(a<b);
    //double dx = 1e-5;
    int N = 1e5;
    double dx = (b-a)/N;
    bool has_increasing_interval = false;
    bool has_decreasing_interval = false;
    for(double x = a; x <= b; x+= dx) {
        if (f(x+dx)>f(x))  {  // increasing 
            has_increasing_interval = true;
            if (has_decreasing_interval) { return false;}
        }
        else if (f(x+dx)<f(x)) { // decreasing
            has_decreasing_interval = true;
            if (has_increasing_interval) { return false;}
        }
        else { return false;}

    }
    return true;

}

bool is_increasing(double a, double b) {
    assert(a<b);
    //double dx = 1e-5;
    int N = 1e5;
    double dx = (b-a)/N;
    for(double x = a; x <= b; x+= dx) {
        if (f(x+dx)>f(x)) { continue; }
        else { return false; }

    }
    return true;

}

double calculate_inverse_integral(double a, double b) {
    assert(a<b);
    //double dx = 1e-5;
    int N = 1e5;
    double dx = (b-a)/N;
    double result = 0.0;
    for(double x = a; x <= b; x+= dx) {
        // (inverse(y+dy) + inverse(y)) / 2 * dy
        result += (x+dx + x)/2 * abs(f(x+dx) - f(x));;
    }
    return result;

}

int main() {
    double a;
    double b;

    std::cout<<"Enter a (lower bound of interval):"<<std::endl;
    std::cin>>a;

    std::cout<<"Enter b (upper bound of interval):"<<std::endl;
    std::cin>>b;

    if (a>=b) {
        std::cerr<<"Lower bound (a) should be strictly less then upper bound (b)"<<std::endl;
        return 1;
    }

    if (has_inverse(a,b)) {
        double result = calculate_inverse_integral(a,b);
        std::cout<<"Value of integral: "<<result<<std::endl;
    } else {
        std::cout<<"No inverse function on (a,b)"<<std::endl;
    }

    

    

    return 0;
}
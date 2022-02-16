#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
using namespace std;

class figure {
public:
    figure() {}
    ~figure() {}
    virtual double get_S() = 0;
protected:
    double S;
    string colour;
};

class polygons : public figure {
public:
    polygons() {}
    virtual unsigned get_n() = 0;
    virtual double get_r() = 0;
    virtual double get_R() = 0;
    virtual double get_S() = 0;
};

class correct_polygons : public polygons {
public:
    correct_polygons(unsigned int N, double A) {
        n = N;
        a = A;
    }
    ~correct_polygons() {};
    double get_r() override {
        r = a / (2 * tan(M_PI/n));
        return r;
    }
    unsigned int get_n() override {
        return n;
    }
    double get_R() override{
        R = a / (2 * sin(M_PI/n));
    }
    double get_S() override {
        S = a * get_r() * n / 2;
        return S;
    }
protected:
    unsigned int n;
    double a;
    double r;
    double R;
};
class square : public correct_polygons {
public:
    double get_r() override {
        return a/2;
    }
    double get_R() override {
        return a * sqrt(2) / 2;
    }
    double get_S() override {
        return pow(a,2);
    }
protected:
};

class correct_triangle : public correct_polygons {
    double get_r() override {
        return a/(2 * sqrt(3));
    }
    double get_R() override {
        return a/sqrt(3);
    }
    double get_S() override {
        return pow(a, 2) * sqrt(3) / 2;
    }
};
class trapeze : public polygons {
public:
    trapeze(double a, double b, double c, double d, double alpha, double beta) {
        DA = a;
        AB = b;
        BC = c;
        CD = d;
        al = alpha;
        bt = beta;
        d1 = sqrt(pow(d, 2) + a*b - (a * (pow(d, 2) - pow(c, 2))/(a-b)));
        d2 = sqrt(pow(c, 2) + a*b - (a * (pow(c, 2) - pow(d, 2))/(a-b)));
    }
    double get_r() override {
        if (AB + CD == BC + DA) {
            double r = 0; //радиус вписанной окружности
            return r;
        }
        else
            return -1;
    }
    double get_R() override {
        if (al + bt == M_PI) {
            double R = 0;
            return R;
        }
        else
            return -1;
    }
    double get_S() override {
        return (BC + DA) * AB * sin(al)/2;
    }
protected:
    double AB, BC, CD, DA;
    double al, bt;
    double d1, d2;
};

class parallelogram : public polygons {
public:
    parallelogram(double a, double b, double alpha) {
        AB = a;
        BC = b;
        al = alpha;
    }
    ~parallelogram() {};
    double get_r() override {
        if (AB == BC)
            return AB * sin(al) / 2;
        else
            return -1;
    }
    double get_S() override {
        return AB * sin(al) * BC;
    }
protected:
    double AB, BC;
    double al;
};

class ellipse : public figure {
    ellipse(double A, double B) {
        a = A;
        b = B;
    }
    ~ellipse() {};
    double get_S() override {
        return M_PI * a * b;
    }
    double get_ex() {
        return sqrt(1 - pow(b/a,2));
    }
protected:
    double a, b;
};

class circle : public ellipse {
    double get_S() override {
        return M_PI * pow(r, 2);
    }
private:
    double r = a;
};
int main() {

return 0;
};
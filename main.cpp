#include <iostream>
#include <math.h>
#include "Figures.cpp"

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
public:
    ellipse(double A, double B) {
        a = A;
        b = B;
    }
    ~ellipse() {};
    double get_S() override {
        return M_PI * a * b;
    }
    pair<double,double> const getRadii(){
        return make_pair(a, b);
    }
    double get_ex() {
        return sqrt(1 - pow(b/a,2));
    }
protected:
    double a, b;
};

class circle : public ellipse {
    double gerRadius(){
        return r;
    }
    double get_S() override {
        return M_PI * pow(r, 2);
    }
private:
    double r = a;
};

void drawbackground(PPM *ppm1){
    for(int i = 0; i < 500; i++)
        for(int j = 0; j < 500; j++) {
            ppm1->image[i][j].r = 18;
            ppm1->image[i][j].g = 49;
            ppm1->image[i][j].b = 102;
        }
}

// void drawdisk(PPM *ppm1, circle radius){
//     for(int i = 250 - radius.getRadius(); i < 250 + radius.getRadius(); i++)
//         for(int j = 250 - radius.getRadius(); j < 250 + radius.getRadius(); j++) {
//             if (sqrt(pow((i - 250)/(radius.getRadius()), 2) + pow((j - 250)/(radius.getRadius()), 2)) < 1) {
//                 ppm1->image[i][j].r = 186;
//                 ppm1->image[i][j].g = 203;
//                 ppm1->image[i][j].b = 239;
//             }
//         }
// }

void drawsquare(PPM *ppm1, double length){
    for(int i = 250 - 5 * length; i < 250 + 5 * length; i++)
       for(int j = 250 - 5 * length; j < 250 + 5 * length; j++) {
           ppm1->image[i][j].r = 186;
           ppm1->image[i][j].g = 203;
           ppm1->image[i][j].b = 239;
       }
}

void drawellipse(PPM *ppm1, ellipse radius){
    for(int i = 250 - radius.getRadii().first; i < 250 + radius.getRadii().first; i++)
        for(int j = 250 - radius.getRadii().first; j < 250 + radius.getRadii().first; j++) {
            if (sqrt(pow((i - 250)/(radius.getRadii().first), 2) + pow((j - 250)/(radius.getRadii().second), 2)) < 1) {
                ppm1->image[i][j].r = 186;
                ppm1->image[i][j].g = 203;
                ppm1->image[i][j].b = 239;
            }
        }
}

// void trapeze(PPM *ppm1){
//     for(int i = 200; i < 300; i++)
//        for(int j = 200; j < 300; j++) {
//            ppm1->image[i][j].r = 186;
//            ppm1->image[i][j].g = 203;
//            ppm1->image[i][j].b = 239;
//        }
// }

void drawparallelogram(PPM *ppm1, double length){
    for(int i = 250 - 5 * length; i < 250 + 5 * length; i++)
       for(int j = 250 - 5 * length; j < 250 + 5 * length; j++) {
           ppm1->image[(int) (i + 0.2 * j)][j].r = 186;
           ppm1->image[(int) (i+ 0.2 * j)][j].g = 203;
           ppm1->image[(int) (i+ 0.2 * j)][j].b = 239;
       }
}

int main(){

    PPM ppm1 (500, 500);
    drawbackground(&ppm1); //отрисовка фона

    // drawsquare(&ppm1, 10);  //отрисовка квадрата
    // drawparallelogram(&ppm1, 10); //отрисовка параллелограмма

    ellipse radius (100, 50); 
    drawellipse(&ppm1,radius);  //отрисовка круга/эллипса

    ppm1.save("Result.ppm");
}
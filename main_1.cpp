#include <iostream>
#include <math.h>
<<<<<<< HEAD
//#include <SFML/Graphics.hpp>
=======
#include "Figures.cpp"

>>>>>>> 6e1607214bfab4f66a28ada624b092bfb418c474
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
    correct_polygons() {};
    correct_polygons(double A, double N) {
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
        R = a / (2 * cos(M_PI * (n-2)/(2 * n)));
        return R;
    }
    double get_S() override {
        S = a * get_r() * n / 2;
        return S;
    }
protected:
    double n;
    double a;
    double r;
    double R;
};
class square : public correct_polygons {
public:
    square(double a) {
        this->a = a;
    }
    double get_r() override {
        return a/2;
    }
    double get_R() override {
        return a * sqrt(2) / 2;
    }
    double get_S() override {
        return pow(a,2);
    }
    unsigned int get_n() override {
        return 4;
    }
protected:
    double a;
};

class correct_triangle : public correct_polygons {
public:
    correct_triangle(double a) {
        this->a = a;
    }
    double get_r() override {
        return a/(2 * sqrt(3));
    }
    double get_R() override {
        return a/sqrt(3);
    }
    double get_S() override {
        return pow(a, 2) * sqrt(3) / 4;
    }
    unsigned int get_n() override {
        return 3;
    }

protected:
    double a;
};
class trapeze : public polygons {
public:
    trapeze(double a, double b, double c, double alpha) {
        DA = a;
        AB = b;
        BC = c;
        al = alpha * M_PI / 180;
        CD = sqrt(pow(DA - BC -  AB * cos(al), 2) + pow(AB * sin(al), 2));
        bt = atan(b*sin(al)/(a-b*cos(al)));
        d1 = sqrt(pow(CD, 2) + DA*AB - (DA * (pow(CD, 2) - pow(BC, 2))/(DA-AB)));
        d2 = sqrt(pow(BC, 2) + DA*AB - (DA * (pow(BC, 2) - pow(CD, 2))/(DA-AB)));
    }
    double get_r() override {
        if (AB + CD - BC - DA < 0.00001) {
            double r = AB * sin(al)/2; //радиус вписанной окружности
            return r;
        }
        return -1;
    }
    double get_R() override {
        if (al + bt - M_PI < 0.00001) {
            double R = d2/(2 * sin(al));
            return R;
        }
        return -1;
    }
    double get_S() override {
        return (BC + DA) * AB * sin(al)/2;
    }
    unsigned int get_n() override {
        return 4;
    }
    double get_d1() {
        return d1;
    }
    double get_d2() {
        return d2;
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
        al = alpha / 180 * M_PI;
    }
    ~parallelogram() {};
    double get_r() override {
        if (AB == BC)
            return AB * sin(al) / 2;
        return -1;
    }
    unsigned int get_n() override {
        return 4;
    }
    double get_R() override {
        if (al == M_PI / 2)
            return sqrt(pow(AB, 2) + pow(BC, 2))/2;
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
<<<<<<< HEAD
    ellipse() {};
=======
>>>>>>> 6e1607214bfab4f66a28ada624b092bfb418c474
    ellipse(double A, double B) {
        a = A;
        b = B;
    }
    ~ellipse() {};
    double get_S() override {
        return M_PI * a * b;
    }
<<<<<<< HEAD
    virtual double get_ex() {
        return sqrt(1 - pow(a/b,2));
=======
    pair<double,double> const getRadii(){
        return make_pair(a, b);
    }
    double get_ex() {
        return sqrt(1 - pow(b/a,2));
>>>>>>> 6e1607214bfab4f66a28ada624b092bfb418c474
    }
protected:
    double a, b;
};

class circle : public ellipse {
<<<<<<< HEAD
public:
    circle(double r) {
        this->r = r;
=======
    double gerRadius(){
        return r;
>>>>>>> 6e1607214bfab4f66a28ada624b092bfb418c474
    }
    double get_S() override {
        return M_PI * pow(r, 2);
    }
    double get_ex() override {
        return 0;
    }
private:
    double r;
};

<<<<<<< HEAD
    cout << "Circle Methods" << endl;
    ellipse* objE = new circle(1.0);
    cout << "S = " << objE -> get_S() << endl;
    cout << "Ext = " << objE -> get_ex() << endl;

    cout << endl;

    cout << "Elips Methods" << endl;
    objE = new ellipse(10, 90);
    cout << "S = " << objE -> get_S() << endl;
    cout << "Ext = " << objE -> get_ex() << endl;

    cout << endl;

    cout << "Parallelogram Methods" << endl;
    polygons* objP = new parallelogram(1, 1, M_PI / 2);
    cout << "S = " << objP -> get_S() << endl;
    cout << "R = " << objP -> get_R() << endl;
    cout << "r = " << objP -> get_r() << endl;
    cout << "n = " << objP -> get_n() << endl;

    cout << endl;

    cout << "Trapeze Methods" << endl;
    objP = new trapeze(17, 10, 5, atan(4 / 3));
    cout << "S = " << objP -> get_S() << endl;
    cout << "R = " << objP -> get_R() << endl;
    cout << "r = " << objP -> get_r() << endl;
    cout << "n = " << objP -> get_n() << endl;

    cout << endl;

    cout << "Correct triangle Methods" << endl;
    objP = new correct_triangle(5);
    cout << "S = " << objP -> get_S() << endl;
    cout << "R = " << objP -> get_R() << endl;
    cout << "r = " << objP -> get_r() << endl;
    cout << "n = " << objP -> get_n() << endl;

    cout << endl;

    cout << "Square Methods" << endl;
    objP = new square(5);
    cout << "S = " << objP -> get_S() << endl;
    cout << "R = " << objP -> get_R() << endl;
    cout << "r = " << objP -> get_r() << endl;
    cout << "n = " << objP -> get_n() << endl;

return 0;
};
=======
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
>>>>>>> 6e1607214bfab4f66a28ada624b092bfb418c474

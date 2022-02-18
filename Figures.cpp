#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

class PPM {
private:

    int m_width = 0;
    int m_height = 0;
    string m_version = "P6";

    void create_image();

public:
    ~PPM();

    PPM(int height, int width);

//    РРM(){}

    struct RGB {
        unsigned char r;
        unsigned char g;
        unsigned char b;
    };

    void set_width(int width) { this->m_width = width; }

    void set_height(int height) { this->m_height = height; }

//    void set_version(string version) { this->m_version = version; }

    void save(string name_file);

    void delete_image();

    RGB **image = nullptr;
};

PPM::~PPM() {
    delete_image();
}

PPM::PPM(int height, int width) {
    set_height(height);
    set_width(width);

    create_image();
}

void PPM::save(string name_file) {
    ofstream output(name_file, ios::binary);

    if (output.is_open()) {
        output << m_version << endl;
        output << m_width << endl;
        output << m_height << endl;
        output << 255 << endl;

        if (m_version == "P3") {
            for (int i = 0; i < m_height; i++)
                for (int j = 0; j < m_width; j++) {
                    output << (int) image[i][j].r << ' ';
                    output << (int) image[i][j].g << ' ';
                    output << (int) image[i][j].b << '\n';
                }
        } else
            for (int i = 0; i < m_height; i++)
                for (int j = 0; j < m_width; j++)
                    output.write((char *) &image[i][j], sizeof(RGB));

        output.close();
    }
}

void PPM::create_image() {
    if (image != nullptr)
        delete_image();

    image = new RGB *[m_height];

    for (int i = 0; i < m_height; i++) {
        image[i] = new RGB[m_width];

        for (int j = 0; j < m_width; j++) {
            image[i][i].r = 255;
            image[i][j].g = 255;
            image[i][j].b = 255;
        }
    }
}

void PPM::delete_image(){
    if(image != nullptr) {
        for (int i = 0; i < m_height; i++)
            delete image[i];

        delete image;
    }
}

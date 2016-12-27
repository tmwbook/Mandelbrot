#include <iostream>
#include <fstream>
#include <cmath>

struct coord{
    double x;
    double y;
};

double SIZE = 300;

double distance(double x, double y, coord* from)
{
    double dx = x - from->x;
    double dy = y - from->y;

    return sqrt(pow(dx, 2) + pow(dy, 2));
}

int mandelbrot_inter(coord* c, int max_iter) {
    double real_z=c->x, imag_z=c->y;
    coord origin = {0, 0};
    double mag_z = distance(real_z, imag_z, &origin);
    int i = 1;
    while (mag_z < 2 && i < max_iter)
    {
        real_z = pow(real_z, 2) - pow(imag_z, 2) + c->x;
        imag_z = 2 * real_z * imag_z + c->y;
        mag_z = distance(real_z, imag_z, &origin);

        i++;
    }

    return i;
}

coord map(double min, double max, int x, int y)
{
    double scale = (max - min) / SIZE;

    return {x*scale + min, y*scale + min};
}

int main() {
    double max_cartesian = 2;
    double min_cartesian = -2;
    int max_iter = 1000;

    std::ofstream writeout;
    writeout.open("data.txt");

    //only supports 1:1 aspect ratio (squares)
    writeout << max_iter << "," << SIZE << "\n";
    for(int cur_x=0; cur_x<SIZE; cur_x++)
    {
        for(int cur_y=0; cur_y<SIZE; cur_y++)
        {
            coord converted = map(min_cartesian, max_cartesian, cur_x, cur_y);
            writeout << mandelbrot_inter(&converted, max_iter) << "\n";
        }
    }
    writeout.close();
    return 0;
}
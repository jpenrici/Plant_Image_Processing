/*
 *   Compile:
 *      g++ Draw_star.cpp -o Test_Draw -lGLU -lGL -lglut -I../Tools/
 *
 *   Run:
 *      ./Test_Draw
*/
#include "Draw.h"
#include "Line.h"

int main(int argc, char **argv)
{
    Vertice center = Vertice(0, 0);

    int number = 24;
    float radius_1 = 200;
    float radius_2 = 50;
    
    for (int i = 0; i < number; ++i)
    {
        if (i % 2 == 0)
            vertices.push_back(center.polar(radius_1, i * 360 / number));
        else
            vertices.push_back(center.polar(radius_2, i * 360 / number));
    }
    vertices.push_back(vertices[0]);
    vertices = Lines(vertices).points();

    draw(argc, argv);

    return 0;
}

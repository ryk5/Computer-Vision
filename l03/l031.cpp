#include<iostream>
#include<fstream>
#include<iomanip>
#include <time.h>
#include <math.h>
#include <string>
#include <list>
#include <climits>

using namespace std;
const int size = 800;
class Point
{
    private:
        double x;
        double y;
    public:
        Point(){}
        Point(double a, double b)
        {
            x = a;
            y = b;
        }
        string toString()
        {
            return "(" + to_string(x) + ", " + to_string(y) + ")";
        }
        double getX()
        {
            return x;
        }
        double getY()
        {
            return y;
        }
        void setX(double i)
        {
            x = i;
        }
        void setY(double i)
        {
            y = i;
        }
        double dist(Point other)
        {
            return sqrt((((x - other.getX()) * (x - other.getX())) + ((y - other.getY()) * (y - other.getY()))));
        }
};
void point(int grid[size][size][3], int a, int b, int red, int blue, int green)
{
    if((a < size) & (a >= 0) & (b < size) & (b >= 0))
    {
        grid[b][a][0] = red;
        grid[b][a][1] = blue;
        grid[b][a][2] = green;
    }
    
}
void circle(int grid[size][size][3], double xcord, double ycord, double r, int red, int blue, int green) //scales to 800
{
    double xcoord = xcord * size;
    double ycoord = ycord * size;
    double bigr = r;
    int xmax = (int) (bigr / sqrt(2));
    int y = (int) bigr;
    int y2 = y * y;
    int ty = (2 * y) - 1;
    int y2_new = y2;
    int xi = (int) xcoord;
    int yi = (int) ycoord;
    for(int x = 0; x <= xmax + 2; x++)
    {
        if((y2 - y2_new) >= ty)
        {
            y2 -= ty;
            y -= 1;
            ty -= 2;
        }
        
            point(grid, x + xi, y + yi, red, blue, green);
            point(grid, x + xi, -y + yi, red, blue, green);
            point(grid, -x + xi, y + yi, red, blue, green);
            point(grid, -x + xi, -y + yi, red, blue, green);
            point(grid, y + xi, x + yi, red, blue, green);
            point(grid, y + xi, -x + yi, red, blue, green);
            point(grid, -y + xi, x + yi, red, blue, green);
            point(grid, -y + xi, -x + yi, red, blue, green);
        
        y2_new -= (2 * x) - 3;
    }
}
list<Point> readfile()
{
    ifstream in("points.txt");
    list<Point> toReturn;
    string a, b;
    string line;
    while(getline(in, line))
    {
        a = line.substr(0, line.find(" ") + 1);
        b = line.substr(line.find(" ") + 1);
        toReturn.push_back(Point(stod(a), stod(b)));
    }
    for(list<Point>::iterator it = toReturn.begin(); it != toReturn.end(); ++it)
    {
        cout << it->getX() << ", " << it->getY() << "\n";
    }
    return toReturn;
    
}
void part1()
{
     int grid[size][size][3];
     ofstream out;
     out.open("points.ppm");
     out << "P3 800 800 255" << endl;

     for(int i = 0 ; i < 800; i++)
     {
         for(int j = 0; j < 800; j++)
         {
             grid[i][j][0] = 255;
             grid[i][j][1] = 255;
             grid[i][j][2] = 255;
         }

     }
    

     int x = 0, y = 0, x1 = 0, y1 = 0;
     Point first, second;
     double mindist = 9999;
     list<Point> g = readfile();
     
     for(list<Point>::iterator it = g.begin(); it != g.end(); ++it)
     {
         list<Point>::iterator it2 = it;
         y = x + 1;
         for(it2 = ++ it2; it2 != g.end(); ++it2)
         {
             if(it->dist(*it2) < mindist)
             {
                 mindist = it->dist(*it2);
                 x1 = x;
                 y1 = y;
                 first = *it;
                 second = *it2;
             }
             y++;
         }
         x++;
     }
    cout << first.getX() << ", " << first.getY() << " " << second.getX() << ", " << second.getY() << " Dist: " << first.dist(second) << "\n";
    int n = 0;
    
    for(list<Point>::iterator it = g.begin(); it != g.end(); ++it)
    {
        
        if(n == x1 || n == y1)
        {
            circle(grid, it->getX(), it->getY(), 3, 255, 0, 0);
        }
        else
        {
            circle(grid, it->getX(), it->getY(), 3, 0, 0, 0);
        }
        n++;
    }
    for(int i = 800 - 1 ; i >= 0; i--)
    {
        for(int j = 0; j < 800; j++)
        {
            out << grid[i][j][0] << " " << grid[i][j][1] << " " << grid[i][j][2] << " ";
        }
        out << "\n";
         
    }
}

void part0()
{
    string x;
    cout << "Would you like to generate the points?(y/n): ";
    cin >> x;
    if(x == "y")
    {
        srand(time(0));
        list<Point> g;
        for(int i = 0; i < 60; i++)
        {
            g.push_back(Point((double) rand() / (RAND_MAX), (double) rand() / (RAND_MAX)));
        }
        ofstream out;
        out.open("points.txt");
        for(Point n : g)
        {
            out << n.getX() << " " << n.getY() << "\n";
        }
    }
    
}
int main()
{
    part0();
    part1();
}
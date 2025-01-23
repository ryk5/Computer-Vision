#include<iostream>
#include<fstream>
#include<iomanip>
#include <time.h>
#include <math.h>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <float.h>
#include <limits>
#include <chrono>
#include <unordered_map>
#include <set>
#include <stack>
using namespace std;
const int size = 400;
double mini;
int numb;
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
        bool compare(Point other)
        {
            return x > other.getX();
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
void line(int grid[size][size][3], double af, double bf, double cf, double df) //scales to 800
{
    int a = (int)(af * size);
    int b = (int)(bf * size);
    int c = (int)(cf * size);
    int d = (int)(df * size);
    int diffx = c - a;
    int diffy = d - b;
    int x;
    int j;
    int e;
    if(a == c) //works
    {
        if(b > d)
        {
            for(int i = d; i <= b; i++)
            {
                point(grid, a, i, 0, 0, 0);
            }
        }
        else
        {
            for(int i = b; i <= d; i++)
            {
                point(grid, a, i, 0, 0, 0);
            }
        }
        
    }
    else if(b == d) //works
    {
        if(a > c)
        {
            for(int i = c; i <= a; i++)
            {
                point(grid, i, b, 0, 0, 0);
            }
        }
        else
        {
            for(int i = a; i <= c; i++)
            {
                point(grid, i, b, 0, 0, 0);
            }
        }
    }
    else if(abs(diffx) >= abs(diffy))
    {
        e = abs(diffy) - abs(diffx);
        j = b;
        if((diffx > 0) && (diffy > 0)) //works
        {
            for(int i = a; i <= c - 1; i++)
            {
                point(grid, i, j, 0, 0, 0);
                if(e >= 0)
                {
                    j += 1;
                    e -= diffx;
                }
                e += diffy;
            }
        }
        else if((diffx > 0) && (diffy < 0)) //works
        {
            for(int i = a; i <= c - 1; i++)
            {
                point(grid, i, j, 0, 0, 0);
                if(e >= 0)
                {
                    j -= 1;
                    e -= abs(diffx);
                }
                e += abs(diffy);
            }
        }
        else if((diffx < 0) && (diffy > 0)) //works
        {
            for(int i = a; i > c; i--)
            {
                point(grid, i, j, 0, 0, 0);
                if(e >= 0)
                {
                    j += 1;
                    e -= abs(diffx);
                }
                e += abs(diffy);
            }
        }
        else //works
        {
            for(int i = a; i > c; i--)
            {
                point(grid, i, j, 0, 0, 0);
                if(e >= 0)
                {
                    j -= 1;
                    e -= abs(diffx);
                }
                e += abs(diffy);
            }
        }
        
    }
    else
    {
        e = abs(diffx) - abs(diffy);
        x = a;
        if((diffx > 0) && (diffy > 0)) //works
        {
            for(int i = b; i <= d - 1; i++)
            {
                point(grid, x, i, 0, 0, 0);
                if(e >= 0)
                {
                    x += 1;
                    e -= abs(diffy);
                }
                e += abs(diffx);
            }
        }
        else if((diffx < 0) && (diffy > 0))
        {
            for(int i = b; i <= d - 1; i++)
            {
                point(grid, x, i, 0, 0, 0);
                if(e >= 0)
                {
                    x -= 1;
                    e -= abs(diffy);
                }
                e += abs(diffx);
            }
        }
        else if((diffx > 0) && (diffy < 0))
        {
            for(int i = b; i > d; i--)
            {
                point(grid, x, i, 0, 0, 0);
                if(e >= 0)
                {
                    x += 1;
                    e -= abs(diffy);
                }
                e += abs(diffx);
            }
        }
        else
        {
            for(int i = b; i > d; i--)
            {
                point(grid, x, i, 0, 0, 0);
                if(e >= 0)
                {
                    x -= 1;
                    e -= abs(diffy);
                }
                e += abs(diffx);
            }
        }
    }
    
}
list<Point> lreadfile()
{
    ifstream in("points.txt");
    list<Point> toReturn;
    while(true)
    {
       
        double x, y;
        
        in >> x >> y;

        toReturn.push_back(Point(x, y));
        if(in.eof())
        {
            break;
        }
    }
    toReturn.pop_back();
    return toReturn;
}
vector<Point> vreadfile()
{
    ifstream in("points.txt");
    vector<Point> toReturn;
    while(true)
    {
       
        double x, y;
        
        in >> x >> y;
        toReturn.push_back(Point(x, y));
        if(in.eof())
        {
            break;
        }
    }
    toReturn.pop_back();
    return toReturn;
}



void genpoints()
{
    ofstream out;
    srand(time(0));
    list<Point> g;
    for(int i = 0; i < 60; i++)
    {
        g.push_back(Point((double) rand() / (RAND_MAX), (double) rand() / (RAND_MAX)));
    }
    out.open("points.txt");
    for(Point n : g)
    {
        out << setprecision(20) << n.getX() << "  " << n.getY() << "\n";
    }        
}

vector<vector<vector<int>>> ppm;
vector<vector<vector<int>>> grayppm;
string type;
unsigned int rows, cols, intensity;
void readppm()
{
    ifstream in("image.ppm");
    int r, g, b;
    vector<vector<int>> temp;
    vector<int> temp2;
    in >> type;
    in >> cols >> rows >> intensity;
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            in >> r >> g >> b;
            temp2 = {r, g, b};
            temp.push_back(temp2);
        }
        ppm.push_back(temp);
        temp.clear();
    }
}
void makegrayscale()
{
    ofstream out;
    out.open("imageg.ppm");
    out << type << " " << cols << " " << rows << " " << intensity << "\n";
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            out << (ppm[i][j][0] + ppm[i][j][1] + ppm[i][j][2]) / 3 << " " << (ppm[i][j][0] + ppm[i][j][1] + ppm[i][j][2]) / 3 << " " << (ppm[i][j][0] + ppm[i][j][1] + ppm[i][j][2]) / 3 << " ";
        }
        out << "\n";
    }
}
void readgrayppm()
{
    ifstream in("imageg.ppm");
    int r, g, b;
    vector<vector<int>> temp;
    vector<int> temp2;
    in >> type;
    in >> cols >> rows >> intensity;
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            in >> r >> g >> b;
            temp2 = {r, g, b};
            temp.push_back(temp2);
        }
        grayppm.push_back(temp);
        temp.clear();
    }
}
void sobel()
{
    int temp[rows][cols];
    int threshold = 12000;
    int tempx, tempy;
    for(int i = 0; i < rows; i++)
    { 
        for(int j = 0; j < cols; j++)
        {
            if(i == 0 || j == 0 || i == rows - 1 || j == cols - 1)
            {
                temp[i][j] = 0;
            }
            else
            {
                tempx = grayppm[i - 1][j - 1][0] + (2 * grayppm[i][j - 1][0]) + grayppm[i + 1][j - 1][0] - grayppm[i - 1][j + 1][0] - (2 * grayppm[i][j + 1][0]) - grayppm[i + 1][j + 1][0]; 
                tempy = grayppm[i - 1][j - 1][0] + (2 * grayppm[i - 1][j][0]) + grayppm[i - 1][j + 1][0] - grayppm[i + 1][j - 1][0] - (2 * grayppm[i + 1][j][0]) - grayppm[i + 1][j + 1][0]; 
                if((tempx * tempx) + (tempy * tempy) > threshold)
                {
                    temp[i][j] = intensity;
                }
                else
                {
                    temp[i][j] = 0;
                }
            }
        }
    }
    
    ofstream out;
    out.open("imagem.ppm");
    out << type << " " << cols << " " << rows << " " << intensity << "\n";
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            out << temp[i][j] << " " << temp[i][j] << " " << temp[i][j] << " ";
        }
        out << "\n";
    }

	
}
void part1()
{
    readppm();
    makegrayscale();
    readgrayppm();
    sobel();
}

int main()
{
    part1();
}
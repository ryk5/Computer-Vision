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
struct hashpair
{
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto firsthash = hash<T1>{}(p.first);
        auto secondhash = hash<T2>{}(p.second);
 
        if (firsthash == secondhash) {
            return firsthash;            
        }
         return firsthash ^ secondhash;
    }
};
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


bool myfunc(Point one, Point two)
{
    return one.getX() < two.getX();
}
bool myfuncy(Point one, Point two)
{
    return one.getY() < two.getY();
}
bool aboveLine(Point pt, Point first, Point second)
{
    double dx = second.getX() - first.getX();
    double dy = second.getY() - first.getY();
    double slope = dy / dx;
    double yfromx = (pt.getX() * slope) + (first.getY() - slope * first.getX());
    return pt.getY() > yfromx;
}
double minimum(double a, double b)
{
    if(a > b)
    {
        return b;
    }
    else
    {
        return a;
    }
}


Point findminX(vector<Point> ve)
{
    Point toReturn;
    double min = 9999;
    for(unsigned int i = 0; i < ve.size(); i++)
    {
        if(ve[i].getX() < min)
        {
            toReturn = ve[i];
            min = ve[i].getX();
        }
        else if(ve[i].getX() == min) //if they share the same X
        {
            if(ve[i].getY() < toReturn.getY())
            {
                toReturn = ve[i];
            }
        }
    }
    return toReturn;
}

Point findmaxX(vector<Point> ve)
{
    Point toReturn;
    double max = -1;
    for(unsigned int i = 0; i < ve.size(); i++)
    {
        if(ve[i].getX() > max)
        {
            toReturn = ve[i];
            max = ve[i].getX();
        }
        else if(ve[i].getX() == max) //if they share the same X
        {
            if(ve[i].getY() > toReturn.getY())
            {
                toReturn = ve[i];
            }
        }
    }
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

double distToLine(Point pt, Point a, Point b) //same as crossproduct
{
    return ((b.getX() - a.getX()) * (pt.getY() - a.getY()) - (pt.getX() - a.getX()) * (b.getY() - a.getY()));
}

double getSide(Point pt, Point a, Point b)
{
    double dist = distToLine(pt, a, b);
    if(dist > 0)
    {
        return 1;
    }
    else if(dist < 0)
    {
        return - 1;
    }
    else
    {
        return 0;
    }
}

void FindHull(vector<Point> &ve, Point a, Point b, double ab, int grid[size][size][3])
{
    if(ve.size() == 0)
    {
        return;
    }
    int index = -1;
    double fardist = 0;
    for(unsigned int i = 0; i < ve.size(); i++)
    {
        double temp = abs(distToLine(ve[i], a, b));
        if(temp > fardist && getSide(ve[i], a, b) == ab)
        {
            fardist = temp;
            index = i;
        }
    }
    if(index == -1)
    {
        line(grid, a.getX(), a.getY(), b.getX(), b.getY());
        return;
    }
    FindHull(ve, ve[index], a, -1 * getSide(ve[index], a, b), grid);
    FindHull(ve, ve[index], b, -1 * getSide(ve[index], b, a), grid);
    
}

void QuickHull(vector<Point> &ve, int grid[size][size][3])
{
    for(auto pt : ve)
    {
        circle(grid, pt.getX(), pt.getY(), 3, 0, 0, 0);
    }
    Point a = findminX(ve);
    Point b = findmaxX(ve);
    FindHull(ve, a, b, 1, grid);
    FindHull(ve, a, b, -1, grid);
}
Point origin;
bool anglefunc(Point a, Point b)
{
    if(distToLine(origin, a, b) == 0)
    {  
        return a.dist(Point(0, 0)) < b.dist(Point(0, 0)); //keep the farthest
    }
    else
    {
        return distToLine(origin, a, b) > 0;
    }
}
vector<Point> GrahamScan(vector<Point> &ve, int grid[size][size][3])
{
    origin = findminX(ve);
    stack<Point> convexhull;
    convexhull.push(origin);
    vector<Point> newvector;
    for(unsigned int i = 0; i < ve.size(); i++)
    {
        if(ve[i].getX() != origin.getX() && ve[i].getY() != origin.getY())
        {
            newvector.push_back(ve[i]);
        }
    }
    sort(newvector.begin(), newvector.end(), anglefunc);
    for(auto pt : newvector)
    {
        while(convexhull.size() >= 2)
        {
            Point temp1 = convexhull.top();
            convexhull.pop();
            Point temp2 = convexhull.top();
            convexhull.push(temp1);
            if(distToLine(pt, temp2, temp1) > 0)
            {
                break;
            }
            convexhull.pop();
        }
        convexhull.push(pt);
    }
    vector<Point> toReturn;
    Point item;
    while(!convexhull.empty())
    {
        item = convexhull.top();
        convexhull.pop();
        toReturn.push_back(item);
    }
    return toReturn;
}
void part2()
{
    int grid[size][size][3];
    ofstream out;
    out.open("grahamscan.ppm");
    out << "P3 400 400 255" << endl;

    for(int i = 0 ; i < size; i++)
    {
         for(int j = 0; j < size; j++)
         {
             grid[i][j][0] = 255;
             grid[i][j][1] = 255;
             grid[i][j][2] = 255;
         }

    }
    genpoints();
    vector<Point> ve = vreadfile();
    for(auto pt : ve)
    {
         circle(grid, pt.getX(), pt.getY(), 3, 0, 0, 0);
    }
    vector<Point> graham = GrahamScan(ve, grid);
    line(grid, graham[0].getX(), graham[0].getY(), graham[graham.size() - 1].getX(), graham[graham.size() - 1].getY());
    for(unsigned int i = 0; i < graham.size() - 1; i++)
    {
        line(grid, graham[i].getX(), graham[i].getY(), graham[i + 1].getX(), graham[i + 1].getY());
    }
    for(int i = size - 1 ; i >= 0; i--)
    {
        for(int j = 0; j < size; j++)
        {
            out << grid[i][j][0] << " " << grid[i][j][1] << " " << grid[i][j][2] << " ";
        }
        out << "\n";

    }
}
void part1()
{
    int grid[size][size][3];
    ofstream out;
    out.open("quickhull.ppm");
    out << "P3 400 400 255" << endl;

    for(int i = 0 ; i < size; i++)
    {
         for(int j = 0; j < size; j++)
         {
             grid[i][j][0] = 255;
             grid[i][j][1] = 255;
             grid[i][j][2] = 255;
         }

    }
    genpoints();
    vector<Point> ve = vreadfile();
    QuickHull(ve, grid);
    for(int i = size - 1 ; i >= 0; i--)
    {
        for(int j = 0; j < size; j++)
        {
            out << grid[i][j][0] << " " << grid[i][j][1] << " " << grid[i][j][2] << " ";
        }
        out << "\n";

    }
}
    

int main()
{
    part1();
    part2();
}
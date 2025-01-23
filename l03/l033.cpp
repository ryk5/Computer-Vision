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

using namespace std;
const int size = 800;
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
vector<Point> v;
vector<Point> bf(vector<Point> &v)
{
    Point first = v[0];
    Point second = v[1];
    double mini = v[0].dist(v[1]);
    for(int i = 0; i < v.size(); i++)
    {
        for(int j = i + 1; j < v.size(); j++)
        {
            if(v[i].dist(v[j]) < mini)
            {
                first = v[i];
                second = v[j];
                mini = v[i].dist(v[j]);
            }
        }
    }
    vector<Point> toReturn = {first, second};
    return toReturn;
     
}
vector<Point> dc(vector<Point> &v)
{
    if(v.size() < 4)
    {
        return bf(v);
    }
    vector<Point> left(v.begin(), v.begin() + v.size() / 2);
    vector<Point> right(v.begin() + v.size() / 2, v.end());    
    vector<Point> l = dc(left);
    vector<Point> r = dc(right);
    double leftdist = l[0].dist(l[1]);
    double rightdist = r[0].dist(r[1]);
    double mini = min(leftdist, rightdist);
    double mid = v[v.size() / 2].getX();
    double lstrip = mid - mini;
    double rstrip = mid + mini;
    vector<Point> strip;
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i].getX() > (lstrip) && v[i].getX() < (rstrip))
        {
            strip.push_back(v[i]);
        }
    }
    if(strip.size() > 2)
    {
        vector<Point> temp = bf(strip);
        double dist = temp[0].dist(temp[1]);
        double mind = min(mini, dist);
        
        if(mind == leftdist)
        {
            return l;
        }
        else if(mind == rightdist)
        {
            return r;
        }
        else
        {
            return temp;
        }
        
    }
    else
    {
        if(mini == leftdist)
        {
            return l;
        }
        else
        {
            return r;
        }
        
    }
    
    
    
}
vector<Point> dc2(vector<Point> &v)
{
    if(v.size() < 4)
    {
        return bf(v);
    }
    vector<Point> left(v.begin(), v.begin() + v.size() / 2);
    vector<Point> right(v.begin() + v.size() / 2, v.end());    
    vector<Point> l = dc2(left);
    vector<Point> r = dc2(right);
    double leftdist = l[0].dist(l[1]);
    double rightdist = r[0].dist(r[1]);
    double mini = min(leftdist, rightdist);
    double mid = v[v.size() / 2].getX();
    double lstrip = mid - mini;
    double rstrip = mid + mini;
    vector<Point> strip;
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i].getX() > (lstrip) && v[i].getX() < (rstrip))
        {
            strip.push_back(v[i]);
        }
    }
    if(strip.size() > 1)
    {
        sort(strip.begin(), strip.end(), myfuncy);
        Point first = strip[0];
        Point second = strip[1];
        double minim = first.dist(second);
        for(int i = 0; i < strip.size() - 1; i++)
        {
            for(int j = 1; j <= 15; j++)
            {
                if(i + j < strip.size())
                {
                    if(strip[i].dist(strip[i+j]) < minim)
                    {
                        minim = strip[i].dist(strip[i+j]);
                        first = strip[i];
                        second = strip[i + j];
                    }
                }

            }
        }
        vector<Point> toReturn = {first, second};
        double mind = min(mini, minim);
        if(mind == leftdist)
        {
            return l;
        }
        else if(mind == rightdist)
        {
            return r;
        }
        else
        {
            return toReturn;
        }
    }
    else
    {
        if(mini == leftdist)
        {
            return l;
        }
        else
        {
            return r;
        }
    }
    

   
    
    
    
}
void part3()
{
    ofstream out;
    vector<Point> a(v.begin(), v.end());
    auto st = chrono::steady_clock::now();
    sort(a.begin(), a.end(), myfunc);
    vector<Point> closest = dc2(a);
    auto en = chrono::steady_clock::now();
    cout << setprecision(21) <<  "Complete Recursive Closest Pair: " << "("<<closest[0].getX() << ", "  << closest[0].getY() << ") (" << closest[1].getX() << ", " << closest[1].getY() << ")\n";
    cout << "Complete Recursive Dist: " << closest[0].dist(closest[1]) << "\n";
    cout << "Complete Recursive (ms): " << chrono::duration_cast<chrono::nanoseconds>(en - st).count()/1e6 << "\n";
    out.open("results.txt", fstream::app);
    out << setprecision(21) <<  "Complete Recursive Closest Pair: " << "("<<closest[0].getX() << ", "  << closest[0].getY() << ") (" << closest[1].getX() << ", " << closest[1].getY() << ")\n";
    out << "Complete Recursive Dist: " << closest[0].dist(closest[1]) << "\n";
    out << "Complete Recursive (ms): " << chrono::duration_cast<chrono::nanoseconds>(en - st).count()/1e6 << "\n";
    
    
}
void part2()
{
    ofstream out;
    v = vreadfile();
    vector<Point> a(v.begin(), v.end());
    auto st = chrono::steady_clock::now();
    sort(a.begin(), a.end(), myfunc);
    vector<Point> closest = dc(a);
    cout << setprecision(21) <<  "Recursive Closest Pair: " << "("<<closest[0].getX() << ", "  << closest[0].getY() << ") (" << closest[1].getX() << ", " << closest[1].getY() << ")\n";
    cout << "Recursive Dist: " << closest[1].dist(closest[0]) << "\n";
    auto en = chrono::steady_clock::now();
    cout << "Recursive (ms): " << chrono::duration_cast<chrono::nanoseconds>(en - st).count()/1e6 << "\n";
    out.open("results.txt", fstream::app);
    out << setprecision(21) <<  "Recursive Closest Pair: " << "("<<closest[0].getX() << ", "  << closest[0].getY() << ") (" << closest[1].getX() << ", " << closest[1].getY() << ")\n";
    out << "Recursive Dist: " << closest[0].dist(closest[1]) << "\n";
    out << "Recursive (ms): " << chrono::duration_cast<chrono::nanoseconds>(en - st).count()/1e6 << "\n";
    
    
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
     list<Point> g = lreadfile();
     auto start = chrono::steady_clock::now();
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
    cout << setprecision(21) << "Brute Force Closest Pair: " << first.getX() << " "  << first.getY() << " " << second.getX() << " " << second.getY() << "\n";
    cout << "Brute Force Dist: " << first.dist(second) << "\n";
    auto end = chrono::steady_clock::now();
    cout << "Brute Force (ms): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count()/1e6  << "\n";
    ofstream pout;
    pout.open("results.txt");
    pout << setprecision(21) <<  "Brute Force Closest Pair: " << first.getX() << " "  << first.getY() << " " << second.getX() << " " << second.getY() << "\n";
    pout << "Brute Force Dist: " << first.dist(second) << "\n";
    pout << "Brute Force (ms): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count()/1e6  << "\n";
    
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
    ofstream out;
    string response;
    cout << "Generate new points? (y/n): ";
    cin >> response;
    out.open("results.txt");
    out << ""; //reset the results.txt file
    if(response == "y")
    {
        cout << "How many points?: ";
        cin >> numb;

        srand(time(0));
        list<Point> g;
        for(int i = 0; i < numb; i++)
        {
            g.push_back(Point((double) rand() / (RAND_MAX), (double) rand() / (RAND_MAX)));
        }
        ofstream out;
        out.open("points.txt");
        for(Point n : g)
        {
            out << n.getX() << "  " << n.getY() << "\n";
        }
    }
    
    
    
    
    
    
}

int main()
{
    part0();
    //part1();
    part2();
    part3();
}
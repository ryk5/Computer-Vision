#include<iostream>
#include<fstream>
#include<iomanip>
#include <time.h>
#include <math.h>
#include <string>
using namespace std;
const int size = 800;
void point(int grid[size][size], int a, int b)
{
    if((a < size) & (a >= 0) & (b < size) & (b >= 0))
        grid[b][a] = 1;
}
void line(int grid[size][size], double af, double bf, double cf, double df) //scales to 800
{
    double slope = (df - bf) / (cf - af);
    bf = bf - (2 * slope);
    df = df + (2 * slope);
    af = af - 2;
    cf = cf + 2;
    
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
                point(grid, a, i);
            }
        }
        else
        {
            for(int i = b; i <= d; i++)
            {
                point(grid, a, i);
            }
        }
        
    }
    else if(b == d) //works
    {
        if(a > c)
        {
            for(int i = c; i <= a; i++)
            {
                point(grid, i, b);
            }
        }
        else
        {
            for(int i = a; i <= c; i++)
            {
                point(grid, i, b);
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
                point(grid, i, j);
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
                point(grid, i, j);
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
                point(grid, i, j);
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
                point(grid, i, j);
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
                point(grid, x, i);
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
                point(grid, x, i);
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
                point(grid, x, i);
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
                point(grid, x, i);
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
void circle(int grid[size][size], double xcord, double ycord, double r) //scales to 800
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
        
            point(grid, x + xi, y + yi);
            point(grid, x + xi, -y + yi);
            point(grid, -x + xi, y + yi);
            point(grid, -x + xi, -y + yi);
            point(grid, y + xi, x + yi);
            point(grid, y + xi, -x + yi);
            point(grid, -y + xi, x + yi);
            point(grid, -y + xi, -x + yi);
        
        y2_new -= (2 * x) - 3;
    }
}
double area(double a, double b, double c, double d, double e, double f)
{
    return abs(((c - a) * (f - b) - (e - a) * (d - b)) * 0.5);
}

bool inside(double x, double y, double a, double b, double c, double d, double e, double f)
{
    double first = area(x, y, a, b, c, d);
    double second = area(x, y, e, f, c, d);
    double third = area(x, y, a, b, e, f);
    double fourth = area(a, b, c, d, e, f);
    return first == (second + third + fourth) || second == (first + third + fourth) || third == (first + second + fourth) || fourth == (first + second + third);
}
void part1()
{
    srand(time(0));
    ofstream out;
    ofstream pout;
    out.open("log.txt");
    pout.open("points.txt");
    double x, y, a, b, c, d, e, f;
    x = ((double) rand() / (RAND_MAX));
    y = ((double) rand() / (RAND_MAX));
    a = ((double) rand() / (RAND_MAX));
    b = ((double) rand() / (RAND_MAX));
    c = ((double) rand() / (RAND_MAX));
    d = ((double) rand() / (RAND_MAX));
    e = ((double) rand() / (RAND_MAX));
    f = ((double) rand() / (RAND_MAX));
    cout << setprecision(17) << "Points: " << "(" << a << ", " << b << "), (" << c << ", " << d << "), (" << e << ", " << f << ")" << "\n";
    out << setprecision(17) << "Points: " << "(" << a << ", " << b << "), (" << c << ", " << d << "), (" << e << ", " << f << ")" << "\n";
    out << setprecision(17) << "testing point (" << x << ", " << y << ")" << "\n";
    while(inside(x, y, a, b, c, d, e, f))
    {
        x = ((double) rand() / (RAND_MAX));
        y = ((double) rand() / (RAND_MAX));
        out << setprecision(17) << "testing point (" << x << ", " << y << ")" << "\n";
        cout << setprecision(17) << "testing point (" << x << ", " << y << ")" << "\n";
    }
   
    pout << "(" << setprecision(17) << x << "," << y << ") , (" << a << "," << b << ") , (" << c << "," << d << ") , (" << e << "," << f << ")";
}

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
class Line
{
    private:
        double slope;
        double a;
        double b;
        double c;
        Point one;
        Point two;
    public:
        Line(){}
        Line(Point x, Point y)
        {
            a = -1 * (y.getY() - x.getY()); 
            b = y.getX() - x.getX();
            c = a * x.getX() + b * x.getY();
            one = x;
            two = y;
            slope = (y.getY() - x.getY()) / (y.getX() - x.getX());
        }
        string toString()
        {
            return "Slope: " + to_string(slope);
        }
        double getX(double y)
        {
            if(a == 0)
            {
                return INFINITY;
            }
            
            else if(b == 0)
            {
                return one.getX();
            }
            return ((-1 * b * y) + c) / a;
        }
        double getY(double x)
        {
            if(a == 0)
            {
                return INFINITY;
            }
            
            else if(b == 0)
            {
                return one.getY();
            }
            return ((-1 * a * x) + c) / b;
        }
        double getSlope()
        {
            return slope;
        }
        double getA()
        {
            return a;
        }
        double getB()
        {
            return b;
        }
        double getC()
        {
            return c;
        }
        Line *makePerp(Point x)
        {
            if(b == 0)
            {
                return new Line(Point(x.getX(), getY(x.getX())), x);
            }
            if(a == 0)
            {
                return new Line(Point(getX(x.getY()), x.getY()), x);
            } 
            return new Line(Point(x.getX() + 1, x.getY() + (b / a)), x);
        }
        Point getOnePoint()
        {
            return one;
        }
        Point getTwoPoint()
        {
            return two;
        }
        Point *intersection(Line other)
        {
            
            if((a * other.getB()) - (b * other.getA()) == 0)
            {
                return NULL;
            }
            double xcoord = ((other.getB() * c) - (other.getC() * b)) / ((a * other.getB()) - (b * other.getA()));
            double ycoord = ((other.getC() * a) - (other.getA() * c)) / ((a * other.getB()) - (b * other.getA()));
            return new Point(xcoord, ycoord);
        }
};
tuple<double, double, double, double, double, double, double, double, double> findArea(Point a, Point b, Point c, Point d, string s)
{
    Line *step1 = new Line(a, b);
    Line *step2 = step1->makePerp(c);
    double inc = a.dist(b) * (1/sqrt(1+(step2->getSlope()) * (step2->getSlope())));
    Point *e = new Point(c.getX() + inc, c.getY() + (inc * step2->getSlope()));
    if(s == "down")
    {
        e = new Point(c.getX() - inc, c.getY() + (-1 * inc * step2->getSlope()));
    }
    Line *side1 = new Line(d, *e);
    Line *side2 = side1->makePerp(a);
    Line *side3 = side1->makePerp(b);
    Line *side4 = side2->makePerp(c);
    Point *first = side1->intersection(*side2);
    Point *second = side1->intersection(*side3);
    Point *third = side3->intersection(*side4);
    Point *fourth = side2->intersection(*side4);
    double area = (first->dist(*second) * first->dist(*second));
    return {area, first->getX(), first->getY(), second->getX(), second->getY(), third->getX(), third->getY(), fourth->getX(), fourth->getY()};
    
}
void draw(int grid[size][size], Point a, Point b, Point c, Point d, string s)
{
    Line *step1 = new Line(a, b);
    Line *step2 = step1->makePerp(c);
    double inc = a.dist(b) * (1/sqrt(1+(step2->getSlope()) * (step2->getSlope())));
    Point *e = new Point(c.getX() + inc, c.getY() + (inc * step2->getSlope()));
    if(s == "down")
    {
        e = new Point(c.getX() - inc, c.getY() + (-1 * inc * step2->getSlope()));
    }
    Line *side1 = new Line(d, *e);
    Line *side2 = side1->makePerp(a);
    Line *side3 = side1->makePerp(b);
    Line *side4 = side2->makePerp(c);
    Point *first = side1->intersection(*side2);
    Point *second = side1->intersection(*side3);
    Point *third = side3->intersection(*side4);
    Point *fourth = side2->intersection(*side4);
    line(grid, first->getX(), first->getY(), second->getX(), second->getY());
    line(grid, second->getX(), second->getY(), third->getX(), third->getY());
    line(grid, first->getX(), first->getY(), fourth->getX(), fourth->getY());
    line(grid, third->getX(), third->getY(), fourth->getX(), fourth->getY());
    circle(grid, a.getX(), a.getY(), 3);
    circle(grid, b.getX(),b.getY(), 3);
    circle(grid, c.getX(), c.getY(), 3);
    circle(grid, d.getX(), d.getY(), 3);
    circle(grid, first->getX(), first->getY(), 6);
    circle(grid, second->getX(), second->getY(), 6);
    circle(grid, third->getX(), third->getY(), 6);
    circle(grid, fourth->getX(), fourth->getY(), 6);
}
void calculate(int grid[size][size], Point a, Point b, Point c, Point d)
{
    tuple<double, double, double, double, double, double, double, double, double> a1 = findArea(a, b, c, d, "up");
    tuple<double, double, double, double, double, double, double, double, double>  a2 = findArea(a, b, c, d, "down");
    tuple<double, double, double, double, double, double, double, double, double>  b1 = findArea(a, c, b, d, "up");
    tuple<double, double, double, double, double, double, double, double, double>  b2 = findArea(a, c, b, d, "down");
    tuple<double, double, double, double, double, double, double, double, double>  c1 = findArea(a, d, c, b, "up");
    tuple<double, double, double, double, double, double, double, double, double>  c2 = findArea(a, d, c, b, "down");
    double list[6];
    ofstream out;
    out.open("sampleoutput.txt");
    
    int ind;
    list[0] = get<0>(a1);
    list[1] = get<0>(a2);
    list[2] = get<0>(b1);
    list[3] = get<0>(b2);
    list[4] = get<0>(c1);
    list[5] = get<0>(c2);
    double min = 99999;
    for(int i = 0; i < 6; i++)
    {
        if(list[i] < min)
        {
            min = list[i];
            ind = i;
        }
    }
    out << setprecision(17) << "(" << a.getX() << "," << a.getY() << ") , ";
    out << setprecision(17) << "(" << b.getX() << "," << b.getY() << ") , ";
    out << setprecision(17) << "(" << c.getX() << "," << c.getY() << ") , ";
    out << setprecision(17) << "(" << d.getX() << "," << d.getY() << ")\n";
    out << setprecision(17) << "(" << get<1>(a1) << "," << get<2>(a1) << ") , ";
    out << setprecision(17) << "(" << get<3>(a1) << "," << get<4>(a1) << ") , ";
    out << setprecision(17) << "(" << get<5>(a1) << "," << get<6>(a1) << ") , ";
    out << setprecision(17) << "(" << get<7>(a1) << "," << get<8>(a1) << ") Area=" << get<0>(a1) << "\n";
    out << setprecision(17) << "(" << get<1>(a2) << "," << get<2>(a2) << ") , ";
    out << setprecision(17) << "(" << get<3>(a2) << "," << get<4>(a2) << ") , ";
    out << setprecision(17) << "(" << get<5>(a2) << "," << get<6>(a2) << ") , ";
    out << setprecision(17) << "(" << get<7>(a2) << "," << get<8>(a2) << ") Area=" << get<0>(a2) << "\n";
    out << setprecision(17) << "(" << get<1>(b1) << "," << get<2>(b1) << ") , ";
    out << setprecision(17) << "(" << get<3>(b1) << "," << get<4>(b1) << ") , ";
    out << setprecision(17) << "(" << get<5>(b1) << "," << get<6>(b1) << ") , ";
    out << setprecision(17) << "(" << get<7>(b1) << "," << get<8>(b1) << ") Area=" << get<0>(b1) << "\n";
    out << setprecision(17) << "(" << get<1>(b2) << "," << get<2>(b2) << ") , ";
    out << setprecision(17) << "(" << get<3>(b2) << "," << get<4>(b2) << ") , ";
    out << setprecision(17) << "(" << get<5>(b2) << "," << get<6>(b2) << ") , ";
    out << setprecision(17) << "(" << get<7>(b2) << "," << get<8>(b2) << ") Area=" << get<0>(b2) << "\n";
    out << setprecision(17) << "(" << get<1>(c1) << "," << get<2>(c1) << ") , ";
    out << setprecision(17) << "(" << get<3>(c1) << "," << get<4>(c1) << ") , ";
    out << setprecision(17) << "(" << get<5>(c1) << "," << get<6>(c1) << ") , ";
    out << setprecision(17) << "(" << get<7>(c1) << "," << get<8>(c1) << ") Area=" << get<0>(c1) << "\n";
    out << setprecision(17) << "(" << get<1>(c2) << "," << get<2>(c2) << ") , ";
    out << setprecision(17) << "(" << get<3>(c2) << "," << get<4>(c2) << ") , ";
    out << setprecision(17) << "(" << get<5>(c2) << "," << get<6>(c2) << ") , ";
    out << setprecision(17) << "(" << get<7>(c2) << "," << get<8>(c2) << ") Area=" << get<0>(c2) << "\n";
    if(ind == 0)
    {
        draw(grid, a, b, c, d, "up");
    }
    else if(ind == 1)
    {
        draw(grid, a, b, c, d, "down");
    }
    else if(ind == 2)
    {
        draw(grid, a, c, b, d, "up");
    }
    else if(ind == 3)
    {
        draw(grid, a, c, b, d, "down");
    }
    else if(ind == 4)
    {
        draw(grid, a, d, c, b, "up");
    }
    else
    {
        draw(grid, a, d, c, b, "down");
    }

}
void part2()
{
    ifstream in("points.txt");
    string s = "";
    string m = "";
    double list[8];
    string content( (istreambuf_iterator<char>(in) ),(istreambuf_iterator<char>()) );
    int g, h;
    cout<<content<<"\n";
    g = content.find("(");
    h = content.find(",");
    list[0] = stod(content.substr(g + 1, h - g + 1));
    content = content.substr(h);
    g = content.find(",");
    h = content.find(")");
    list[1] = stod(content.substr(g + 1, h - g + 1));
    content = content.substr(h + 3);
    g = content.find("(");
    h = content.find(",");
    list[2] = stod(content.substr(g + 1, h - g + 1));
    content = content.substr(h);
    g = content.find(",");
    h = content.find(")");
    list[3] = stod(content.substr(g + 1, h - g + 1));
    content = content.substr(h + 3);
    g = content.find("(");
    h = content.find(",");
    list[4] = stod(content.substr(g + 1, h - g + 1));
    content = content.substr(h);
    g = content.find(",");
    h = content.find(")");
    list[5] = stod(content.substr(g + 1, h - g + 1));
    content = content.substr(h + 3);
    g = content.find("(");
    h = content.find(",");
    list[6] = stod(content.substr(g + 1, h - g + 1));
    content = content.substr(h);
    g = content.find(",");
    h = content.find(")");
    list[7] = stod(content.substr(g + 1, h - g + 1));
    
    cout << "(" << list[0] << ", " << list[1] << ")\n";
    cout << "(" << list[2] << ", " << list[3] << ")\n";
    cout << "(" << list[4] << ", " << list[5] << ")\n";
    cout << "(" << list[6] << ", " << list[7] << ")\n";
    
    Point *a = new Point(list[0], list[1]);
    Point *b = new Point(list[2], list[3]);
    Point *c = new Point(list[4], list[5]);
    Point *d = new Point(list[6], list[7]);
    int grid[size][size];
    ofstream out;
    out.open("out.ppm");
    out << "P3 800 800 1" << endl;

    for(int i = 0 ; i < 800; i++)
    {
        for(int j = 0; j < 800; j++)
        {
            grid[i][j] = 0;
        }
         
    }
    calculate(grid, *a, *b, *c, *d);
    for(int i = 800 - 1 ; i >= 0; i--)
    {
        for(int j = 0; j < 800; j++)
        {
            out << grid[i][j] << " " << grid[i][j] << " " << grid[i][j] << " ";
        }
        out << "\n";
         
    }
    
    
    
}
int main()
{
    //part1();
    part2();
}

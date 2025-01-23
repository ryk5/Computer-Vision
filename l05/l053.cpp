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

void readppm(string infile)
{
    ifstream in(infile);
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
void readmakegrayscale(bool b, string outfile)
{
    ofstream out;
    out.open(outfile);
    out << type << " " << cols << " " << rows << " " << intensity << "\n";
    vector<vector<int>> temp;
    vector<int> temp2;
    int temp3;
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            temp3 = (ppm[i][j][0] + ppm[i][j][1] + ppm[i][j][2]) / 3;
            temp2 = {temp3, temp3, temp3};
            temp.push_back(temp2);
            if(b)
            {
                out << temp3 << " " << temp3 << " " << temp3 << " ";
            }
        }
        grayppm.push_back(temp);
        temp.clear();
        if(b)
        {
            out << "\n";
        }
        
    }
}

void sobel()
{
    int temp[rows][cols];
    int threshold = 4000;
    int tempx, tempy;
    for(unsigned int i = 0; i < rows; i++)
    { 
        for(unsigned int j = 0; j < cols; j++)
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
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            out << temp[i][j] << " " << temp[i][j] << " " << temp[i][j] << " ";
        }
        out << "\n";
    }

}
void part1(string name)
{
    readppm(name);
    readmakegrayscale(true, "imageg.ppm");
    sobel();
}
void floodfill(unsigned int x, unsigned int y, vector<vector<vector<int>>> &grid)
{
    if(x >= 0 && x < rows && y >= 0 && y < cols)
    {
        if(grid[x][y][0] == 0 || grid[x][y][0] == 1)
        {
            return;
        }
        grid[x][y][0] = 1;
        grid[x][y][1] = 1;
        grid[x][y][2] = 1;
        floodfill(x - 1, y, grid);
        floodfill(x - 1, y + 1, grid);
        floodfill(x - 1, y - 1, grid);
        floodfill(x + 1, y - 1, grid);
        floodfill(x + 1, y + 1, grid);
        floodfill(x + 1, y, grid);
        floodfill(x, y - 1, grid);
        floodfill(x, y + 1, grid);
    }
    
    
    
}
void hysteresis(int threshold1, int threshold2, string outfile)
{
    int t;
    if(threshold1 > threshold2)
    {
        t = threshold1;
        threshold1 = threshold2;
        threshold2 = t;
    }
    
    int tempx, tempy;
    vector<vector<vector<int>>> temp;
    vector<vector<int>> temp2;
    vector<int> temp3;
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            temp3 = {0, 0, 0};
            temp2.push_back(temp3);
        }
        temp.push_back(temp2);
    }
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            if(i != 0 && i != rows - 1 && j != cols - 1 && j != 0)
            {

                tempx = grayppm[i - 1][j - 1][0] + (2 * grayppm[i][j - 1][0]) + grayppm[i + 1][j - 1][0] - grayppm[i - 1][j + 1][0] - (2 * grayppm[i][j + 1][0]) - grayppm[i + 1][j + 1][0]; 
                tempy = grayppm[i - 1][j - 1][0] + (2 * grayppm[i - 1][j][0]) + grayppm[i - 1][j + 1][0] - grayppm[i + 1][j - 1][0] - (2 * grayppm[i + 1][j][0]) - grayppm[i + 1][j + 1][0]; 

            }
            if(sqrt((tempx * tempx) + (tempy * tempy)) > threshold2)
            {
                if(sqrt((tempx * tempx) + (tempy * tempy)) > threshold1)
                {
                    temp[i][j][0] = 3;
                    temp[i][j][1] = 3;
                    temp[i][j][2] = 3;
                }
                else
                {
                    temp[i][j][0] = 2;
                    temp[i][j][1] = 2;
                    temp[i][j][2] = 2;
                }
            }
        }
    }
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            if(temp[i][j][0] == 3)
            {
                floodfill(i, j, temp);
            }
        }
    }
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            if(temp[i][j][0] == 2)
            {
                temp[i][j][0] = 0;
                temp[i][j][1] = 0;
                temp[i][j][2] = 0;
            }
        }
    }
    
    ofstream out;
    out.open(outfile);
    out << type << " " << cols << " " << rows << " 1" << "\n";
    
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            out << temp[i][j][0] << " " << temp[i][j][1] << " " << temp[i][j][2] << " ";
        }
        out << "\n";
    }
    
    
}
void part2(string infile, string outfile, unsigned int low, unsigned int high)
{
    readppm(infile);
    readmakegrayscale(false, "imageg.ppm");
    hysteresis(low, high, outfile);
}

void hyster(int rows, int cols, vector<vector<int>>& gradients, int x, int y) {
    for(int dx = -1; dx <= 1; dx++) 
    {
        for(int dy = -1; dy <= 1; dy++) 
        {
            int ax = x + dx;
            int ay = y + dy;
            if(ax >= 0 && ay >= 0 && ax < rows && ay < cols)
            {
                if(gradients[ax][ay] == 1) 
                {
                    gradients[ax][ay] = 2;
                    hyster(rows, cols, gradients, ax, ay);
                }
            }
                
        }
    }
}

vector<vector<int>> anglethreshold(int rows, int cols, vector<vector<int>> magnitudes, vector<vector<int>> directions) 
{
    vector<vector<int>> ret;
    for(int i = 0; i < rows; i++) 
    {
        vector<int> temp(cols, 0);
        ret.push_back(temp);
    }
    for(int i = 1; i < rows - 1; i++) 
    {
        for(int j = 1; j < cols - 1; j++) 
        {
            int direction = directions[i][j];
            if(direction == 0) 
            {
                if(magnitudes[i][j] >= magnitudes[i][j-1] && magnitudes[i][j] >= magnitudes[i][j+1]) 
                {
                    ret[i][j] = 1;
                }
            } 
            else if(direction == 45)
            {
                if(magnitudes[i][j] >= magnitudes[i+1][j+1] && magnitudes[i][j] >= magnitudes[i-1][j-1])
                {
                    ret[i][j] = 1;
                }
            } 
            else if(direction == 90) 
            {
                if(magnitudes[i][j] >= magnitudes[i-1][j] && magnitudes[i][j] >= magnitudes[i+1][j])
                {
                    ret[i][j] = 1;
                }    
            } 
            else
            {
                if(magnitudes[i][j] >= magnitudes[i+1][j-1] && magnitudes[i][j] >= magnitudes[i-1][j+1]) 
                {
                    ret[i][j] = 1;
                }
            }
        }
    }
    
    return ret;
}
void nms(string img, string grayimg, string hyimg, string nonmaximg, string bothimg, int threshold1, int threshold2)
{   
    readppm(img);
    readmakegrayscale(true, grayimg);
    vector<vector<int>> gradients;
    vector<vector<int>> directions;
    vector<vector<int>> magnitudes;
    vector<vector<int>> highs;
    for(unsigned int i = 0; i < rows; i++) 
    {
        vector<int> temp(cols);
        vector<int> temp2(cols);
        vector<int> temp3(cols);
        gradients.push_back(temp);
        directions.push_back(temp2);
        magnitudes.push_back(temp3);
        for(unsigned int j = 0; j < cols; j++) 
        {
            if(i == 0 || i == rows - 1 || j == 0 || j == cols - 1) 
            {
                gradients[i][j] = 0;
            } 
            else 
            {
                double gx = grayppm[i - 1][j - 1][0] + (2 * grayppm[i][j - 1][0]) + grayppm[i + 1][j - 1][0] - grayppm[i - 1][j + 1][0] - (2 * grayppm[i][j + 1][0]) - grayppm[i + 1][j + 1][0]; 
                double gy = grayppm[i - 1][j - 1][0] + (2 * grayppm[i - 1][j][0]) + grayppm[i - 1][j + 1][0] - grayppm[i + 1][j - 1][0] - (2 * grayppm[i + 1][j][0]) - grayppm[i + 1][j + 1][0]; 
                gradients[i][j] = 0;
                if(sqrt((gx * gx) + (gy * gy)) >= threshold2) 
                {
                    gradients[i][j] = 2;
                }
                else if(sqrt((gx * gx) + (gy * gy)) >= threshold1)
                {
                    gradients[i][j] = 1;
                }
                
                if(gradients[i][j] == 2) 
                {
                    highs.push_back({(int) i, (int) j});
                }
                
                double angle = ((atan2(gy, gx)) * 180) / 3.14159265;
                if(angle < 0) //no negative angles
                {
                    angle += 180;
                }
                if((int) angle % 45 >= 22.5)
                {
                    angle = ceil(angle / 45) * 45;
                }
                else
                {
                    angle = floor(angle / 45) * 45;
                }
                directions[i][j] = (int) angle;
                magnitudes[i][j] = sqrt((gx * gx) + (gy * gy));
            }
        }
    }
    
    for(unsigned int i = 0; i< highs.size(); i++) 
    {
        hyster(rows, cols, gradients, highs[i][0], highs[i][1]);
    }
    
    for(unsigned int i = 0; i < rows; i++) 
    {
        for(unsigned int j = 0; j < cols; j++) 
        {
            if(gradients[i][j] == 1)
            {
                gradients[i][j] = 0;
            }
        }
    }
    for(unsigned int i = 0; i < rows; i++) 
    {
        for(unsigned int j = 0; j < cols; j++) 
        {
            if(gradients[i][j] == 2)
            {
                gradients[i][j] = 1;
            }
        }
    }
    ofstream out;
    out.open(hyimg);
    out  << "P3 " << cols << " " << rows << " 1" << '\n';
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            out << gradients[i][j] << " " << gradients[i][j] << " " << gradients[i][j] << " ";
        }
        out << "\n";
    }
    vector<vector<int>> nonmax = anglethreshold(rows, cols, magnitudes, directions);    
    ofstream out2;
    out2.open(nonmaximg);
    out2 << "P3 " << cols << " " << rows << " " << 1 << '\n';
    
    for(unsigned int i = 0; i < rows; i++) 
    {
        for(unsigned int j = 0; j < cols; j++) 
        {
            out2 << nonmax[i][j] << " " << nonmax[i][j] << " " << nonmax[i][j] << " ";
        }
        out2 << "\n";
    }
    out2.close();
    
    for(unsigned int i = 0; i < rows; i++) 
    {
        for(unsigned int j = 0; j < cols; j++) 
        {
            if(gradients[i][j] != 1 || nonmax[i][j] != 1) 
            {
                gradients[i][j] = 0;
            }
        }
    }    
    ofstream out3;
    out3.open(bothimg);
    out3 << "P3 " << cols << " " << rows << " " << 1 << '\n';
    
    for(unsigned int i = 0; i < rows; i++) 
    {
        for(unsigned int j = 0; j < cols; j++) 
        {
            out3 << gradients[i][j] << " " << gradients[i][j] << " " << gradients[i][j] << " ";
        }
        out3 << "\n";
    }

}
void part3(int argc, char** argv)
{
    string img = "image.ppm", grayimg = "imageg.ppm", hyimg = "image1.ppm", nonmaximg = "image2.ppm", bothimg = "imagef.ppm";
    int threshold1 = 150, threshold2 = 300;
    for(int i = 0; i < argc; i++) 
    {
        string temp = argv[i];
        if(temp == "-f") 
        {
            string temp2 = argv[i+1];
            img = temp2;
        } 
        else if(temp == "-lt") 
        {
            threshold1 = stoi(argv[i+1]);
        } 
        else if(temp == "-ht") 
        {
            threshold2 = stoi(argv[i+1]);
        } 
        else if(temp == "-fg") 
        {
            string temp2 = argv[i+1];
            grayimg = temp2;
        } 
        else if(temp == "-of") 
        {
            string temp2 = argv[i+1];
            hyimg = temp2;
        } 
        else if(temp == "-f2") 
        {
            string temp2 = argv[i+1];
            nonmaximg = temp2;
        } 
        else if(temp == "-ff") 
        {
            string temp2 = argv[i+1];
            bothimg = temp2;
        }
    }
    nms(img, grayimg, hyimg, nonmaximg, bothimg, threshold1, threshold2);
}
int main(int argc, char** argv)
{
    part3(argc, argv);
}
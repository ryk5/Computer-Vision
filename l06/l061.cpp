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
vector<vector<vector<int>>> ppm;
vector<vector<vector<int>>> grayppm;
string type;
unsigned int rows, cols, intensity;
void point(int** grid, unsigned int a, unsigned int b)
{
    if((a < rows) & (a >= 0) & (b < cols) & (b >= 0))
    {
        grid[a][b] = 1;
    }
    
}

void circle(int** grid, double xcoord, double ycoord, double r) //scales to 800
{
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



int** case1(int x1, int y1, int x2, int y2, int** votes) // x1 < x2 && y1 < y2 && dx < dy
{ 

    int dx = x2 - x1;
    int dy = y2 - y1; 
    int e = dx - dy;
    int i = x1;

    for(int j = y1; j <= y2; j++) 
    {
        if(i >= 0 && i < rows)
        {
            if(j >= 0 && j < cols)
            {
                votes[i][j]++;
            }
        }
        if(e >= 0) 
        {
            i++;
            e -= dy;
        }
        e += dx;
    }
    return votes;
}

int** case2(int x1, int y1, int x2, int y2, int** votes) // x1 < x2 && y1 > y2 && dx > dy
{ 
    int dx = x1 - x2;
    int dy = y2 - y1; 
    int e = dx - dy;
    int i = x1;

    for(int j = y1; j <= y2; j++) 
    {
        if(i >= 0 && i < rows)
        {
            if(j >= 0 && j < cols)
            {
                votes[i][j]++;
            }
        }
        if(e >= 0) 
        {
            i--;
            e -= dy;
        }
        e += dx;
    }
    return votes;
}

int** case3(int x1, int y1, int x2, int y2, int** votes) // x1 = x2 && y1 < y2 && dx < dy
{ 
    for(int j = y1; j < y2; j++)
    {
        if(j >= 0 && j < cols && x1 >= 0 && x1 < rows)
        {
            votes[x1][j]++;
        }
    }
    return votes;
}


int** case4(int x1, int y1, int x2, int y2, int** votes) //x1 < x2 && y1 < y2 && dx > dy
{
    int dx = x2 - x1;
    int dy = y2 - y1; 
    int e = dy - dx;
    int j = y1;

    for(int i = x1; i <= x2; i++) 
    {
        if(i >= 0 && i < rows)
        {
            if(j >= 0 && j < cols)
            {
                votes[i][j]++;
            }
        }
        if(e >= 0) 
        {
            j++;
            e -= dx;
        }
        e += dy;
    }
    return votes;
}

int** case5(int x1, int y1, int x2, int y2, int** votes) //x1 < x2 && y1 > y2 && dx > dy
{
    int dx = x2 - x1; 
    int dy = y1 - y2; 
    int e = dy - dx;
    int j = y1;

    for(int i = x1; i <= x2; i++) 
    {
        if(i >= 0 && i < rows)
        {
            if(j >= 0 && j < cols)
            {
                votes[i][j]++;
            }
        }
        if(e >= 0)
        {
            j--;
            e -= dx;
        }
        e += dy;
    }
    return votes;
}

int** case6(int x1, int y1, int x2, int y2, int** votes) //y1 == y2 && x1 < x2
{ 
    for(int i = x1; i < x2; i++)
    {
        if(i >= 0 && i < rows && y1 > 0 && y1 < cols)
        {
             votes[i][y1]++;
        }
    }
    return votes;
}
void voteline(int x1, int y1, int x2, int y2, int** votes) 
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    
    if(x1 < x2 && y1 < y2 && dx <= dy)
    {
        votes = case1(x1, y1, x2, y2, votes);
    }
    else if(x2 < x1 && y2 < y1 && dx <= dy) 
    {
        int temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
        votes = case1(x1, y1, x2, y2, votes);
    }
    else if(x1 > x2 && y1 < y2 && dx <= dy) 
    {
        votes = case2(x1, y1, x2, y2, votes);
    }
    else if(x1 < x2 && y1 > y2 && dx <= dy) 
    {
        int temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
        votes = case2(x1, y1, x2, y2, votes);
    }
    else if(x1 == x2 && y1 < y2) 
    {
        votes = case3(x1, y1, x2, y2, votes);
    }
    else if(x1 == x2 && y1 > y2) 
    {
        int temp = y1;
        y1 = y2;
        y2 = temp;
        votes = case3(x1, y1, x2, y2, votes);
    }
    else if(x1 < x2 && y1 < y2 && dx >= dy) 
    {
        votes = case4(x1, y1, x2, y2, votes);
    }
    else if(x2 < x1 && y2 < y1 && dx >= dy) 
    {
        int temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
        votes = case4(x1, y1, x2, y2, votes);
    }
    else if(x1 < x2 && y1 > y2 && dx >= dy) 
    {
        votes = case5(x1, y1, x2, y2, votes);
    }
    else if(x2 < x1 && y2 > y1 && dx >= dy) {
        int temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
        votes = case5(x1, y1, x2, y2, votes);
    }
    else if(y1 == y2 && x1 < x2)
    {
        votes = case6(x1, y1, x2, y2, votes);
    }
    else if(y1 == y2 && x2 < x1) 
    {
        int temp = x1;
        x1 = x2;
        x2 = temp;
        votes = case6(x1, y1, x2, y2, votes);
    }
    
    
}

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

vector<vector<int>> anglethreshold(int rows, int cols, vector<vector<int>> magnitudes, vector<vector<double>> directions) 
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
            int direction = (int) directions[i][j];
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
int** getgx(vector<vector<vector<int>>> grid) {
    int** ret;
    ret = new int* [rows];
    for(int i = 0; i < rows; i++)
    {
        
        ret[i] = new int[cols];
    }
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            ret[i][j] = 0;
        }
            
    }
        

    for(int i = 1; i < rows - 1; i++) 
    {
        for(int j = 1; j < cols - 1; j++) 
        {
            int a = grid[i - 1][j - 1][0] * -1;
            int b = 0;
            int c = grid[i - 1][j + 1][0] * 1;
            int d = grid[i][j - 1][0] * -2;
            int e = 0;
            int f = grid[i][j + 1][0] * 2;
            int g = grid[i + 1][j - 1][0] * -1;
            int h = 0;
            int k = grid[i + 1][j + 1][0] * 1;
            ret[i][j] = a + b + c + d + e + f + g + h + k;
        }
    }
    return ret;
}

int** getgy(vector<vector<vector<int>>> grid) 
{
    int** ret;
    ret = new int* [rows];
    for(int i = 0; i < rows; i++)
    {
        
        ret[i] = new int[cols];
    }
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            ret[i][j] = 0;
        }
            
    }
    for(int i = 1; i < rows - 1; i++) 
    {
        for(int j = 1; j < cols - 1; j++) 
        {
            int a = grid[i - 1][j - 1][0] * -1;
            int b = 0;
            int c = grid[i + 1][j - 1][0] * 1;
            int d = grid[i - 1][j][0] * -2;
            int e = 0;
            int f = grid[i + 1][j][0] * 2;
            int g = grid[i - 1][j + 1][0] * -1;
            int h = 0;
            int k = grid[i + 1][j + 1][0] * 1;
            ret[i][j] = a + b + c + d + e + f + g + h + k;
        }
    }
    return ret;
}

void voting(string img, string grayimg, string hyimg, string nonmaximg, string bothimg, string vimg, string ccimg, int threshold1, int threshold2, int cthreshold)
{
  
    readppm(img);
    readmakegrayscale(true, grayimg);
    vector<vector<int>> gradients;
    double ** dirs;
    dirs = new double* [rows];
    for(int i = 0; i < rows; i++)
    {
        dirs[i] = new double[cols];
    }
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            dirs[i][j] = 0;
        }
    }
    vector<vector<double>> slopes;
    vector<vector<int>> magnitudes;
    vector<vector<int>> highs;
    vector<vector<double>> directions;
    for(unsigned int i = 0; i < rows; i++) 
    {
        vector<int> temp(cols);
        vector<double> temp2(cols);
        vector<int> temp3(cols);
        vector<double> temp4(cols);
        gradients.push_back(temp);
        directions.push_back(temp2);
        magnitudes.push_back(temp3);
        slopes.push_back(temp4);
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
                
                directions[i][j] = angle;
                magnitudes[i][j] = sqrt((gx * gx) + (gy * gy));
            }
            
        }
    }
    int** allgx;
    allgx = new int* [rows];
    for(int i = 0; i < rows; i++)
    {
        allgx[i] = new int[rows];
    }
    int** allgy;
    allgy = new int* [rows];
    for(int i = 0; i < cols; i++)
        allgy[i] = new int[rows];

    allgx = getgx(grayppm);
    allgy = getgy(grayppm);
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            dirs[i][j] = atan2(allgy[i][j], allgx[i][j]) * 180 / 3.14159265;
        }
    }
    
    for(unsigned int i = 0; i < highs.size(); i++) 
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
    
    int** votes;
    votes = new int* [rows];
    for(int i = 0; i < rows; i++)
        votes[i] = new int[cols];
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            votes[i][j] = 0;

    double m;
    double r;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) 
        {
            if(gradients[i][j] == 1) 
            {
                m = tan(dirs[i][j] * 3.14159265 / 180.0); 
                r = sqrt(1 + (m*m));
                int x1 = (j - (120  / r));
                int y1 = (i - (120 * m / r));
                int x2 = (j + (120  / r));
                int y2 = (i + (120 * m / r));
                voteline(y1, x1, y2, x2, votes);
            }
        }
    }
    int max = 0;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(votes[i][j] > max)
            {
                max = votes[i][j];
            }
        }
    }
    ofstream out4;
    out4.open(vimg);
    out4 << "P3 " << cols << " " << rows << " " << max << '\n';
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            out4 << votes[i][j] << " " << votes[i][j] << " " << votes[i][j] << " ";
        }
        out4 << "\n";
    }
    
    int** origins;
    origins = new int* [rows];
    for(int i = 0; i < rows; i++)
    {
        origins[i] = new int[cols];
    }
    
    for(int i = 0; i < rows; i++) 
    {
        for(int j = 0; j < cols; j++) 
        {
            if(votes[i][j] > cthreshold) {
                circle(origins, i, j, 1);
                circle(origins, i, j, 2);
                circle(origins, i, j, 3);
                circle(origins, i, j, 4);
            }
        }
    }
    

    ofstream out5;
    out5.open(ccimg);
    out5 << "P3 " << cols << " " << rows << " " << 255 << '\n';
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(origins[i][j] == 1)
            {
                out5 << 255 << " " << 0 << " " << 0 << " ";
            }
            else
            {
                out5 << ppm[i][j][0] << " " << ppm[i][j][1] << " " << ppm[i][j][2] << " ";
            }
            
        }
        out5 << "\n";
    }
    
}
void part1(int argc, char** argv)
{
    string img = "image.ppm", grayimg = "imageg.ppm", hyimg = "image1.ppm", nonmaximg = "image2.ppm", bothimg = "imagef.ppm", vimg = "imagev.ppm", ccimg = "imageCC.ppm";
    int threshold1 = 75, threshold2 = 150, cthreshold = 20; //thresholds I found for easy image
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
        else if(temp == "-f1") 
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
        else if(temp == "-fv")
        {
            string temp2 = argv[i+1];
            vimg = temp2;
        }
        else if(temp == "-fcc")
        {
            string temp2 = argv[i+1];
            ccimg = temp2;
        }
        else if(temp == "-TC") 
        {
            cthreshold = stoi(argv[i+1]);
        } 
    }
    voting(img, grayimg, hyimg, nonmaximg, bothimg, vimg, ccimg, threshold1, threshold2, cthreshold);
}
int main(int argc, char** argv)
{
    part1(argc, argv);
}
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
void point(int** grid, unsigned int a, unsigned int b, int v)
{
    if((a < rows) & (a >= 0) & (b < cols) & (b >= 0))
    {
        grid[a][b] = v;
    }
    
}

void circle(int** grid, double xcoord, double ycoord, double r, int v) //scales to 800
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
        
            point(grid, x + xi, y + yi, v);
            point(grid, x + xi, -y + yi, v);
            point(grid, -x + xi, y + yi, v);
            point(grid, -x + xi, -y + yi, v);
            point(grid, y + xi, x + yi, v);
            point(grid, y + xi, -x + yi, v);
            point(grid, -y + xi, x + yi, v);
            point(grid, -y + xi, -x + yi, v);
        
        y2_new -= (2 * x) - 3;
    }
}



int** case1(int x1, int y1, int x2, int y2, int** votes) // x1 < x2 && y1 < y2 && dx < dy
{ 

    int dx = x2 - x1;
    int dy = y2 - y1; 
    int e = dx - dy;
    int i = x1;
    
    for(unsigned int j = y1; j <= y2; j++) 
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

    for(unsigned int j = y1; j <= y2; j++) 
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
    for(unsigned int j = y1; j < y2; j++)
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

    for(unsigned int i = x1; i <= x2; i++) 
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

    for(unsigned int i = x1; i <= x2; i++) 
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
    for(unsigned int i = x1; i < x2; i++)
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
    for(unsigned int i = 0; i < rows; i++) 
    {
        vector<int> temp(cols, 0);
        ret.push_back(temp);
    }
    for(unsigned int i = 1; i < rows - 1; i++) 
    {
        for(unsigned int j = 1; j < cols - 1; j++) 
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
    for(unsigned int i = 0; i < rows; i++)
    {
        
        ret[i] = new int[cols];
    }
    for(unsigned int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            ret[i][j] = 0;
        }
            
    }
        

    for(unsigned int i = 1; i < rows - 1; i++) 
    {
        for(unsigned int j = 1; j < cols - 1; j++) 
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
    for(unsigned int i = 0; i < rows; i++)
    {
        
        ret[i] = new int[cols];
    }
    for(unsigned int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            ret[i][j] = 0;
        }
            
    }
    for(unsigned int i = 1; i < rows - 1; i++) 
    {
        for(unsigned int j = 1; j < cols - 1; j++) 
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
pair<bool, double> isedges(int** grid, int xcoord, int ycoord, int radius, int pthreshold)
{
    double bigr = radius;
    int xmax = (int) (bigr / sqrt(2));
    int y = (int) bigr;
    int y2 = y * y;
    int ty = (2 * y) - 1;
    int y2_new = y2;
    int xi = (int) xcoord;
    int yi = (int) ycoord;
    int count = 0;
    int total = 0;
    for(unsigned int x = 0; x <= xmax + 2; x++)
    {
        if((y2 - y2_new) >= ty)
        {
            y2 -= ty;
            y -= 1;
            ty -= 2;
        }
            total += 8;
            if(grid[x+xi][y+yi] == 1)//point(grid, x + xi, y + yi);
                count++;
            if(grid[x+xi][-y+yi] == 1)//point(grid, x + xi, -y + yi);
                count++;
            if(grid[-x+xi][y+yi] == 1)//point(grid, -x + xi, y + yi);
                count++;
            if(grid[-x+xi][-y+yi] == 1)//point(grid, -x + xi, -y + yi);
                count++;
            if(grid[y+xi][x+yi] == 1)//point(grid, y + xi, x + yi);
                count++;
            if(grid[y+xi][-x+yi] == 1)//point(grid, y + xi, -x + yi);
                count++;
            if(grid[-y+xi][x+yi] == 1)//point(grid, -y + xi, x + yi);
                count++;
            if(grid[-y+xi][-x+yi] == 1)//point(grid, -y + xi, -x + yi);
                count++;
        
        y2_new -= (2 * x) - 3;
    }
    double a = count / (1.00000000 * total);
    double b = pthreshold / 100.0;
    if(a > b)
    {
        return make_pair(true, a);
    }
    else
        return make_pair(false, a);
}

bool ispenny(int a, int b)
{
    int pixels = 0;
    int rtotal = 0;
    int gtotal = 0;
    int btotal = 0;
    for(int i = a - 30; i <= a + 30; i++)
    {
        for(int j = b - 30; j <= b + 30; j++)
        {
            pixels++;
            rtotal += ppm[a][b][0];
            gtotal += ppm[a][b][1];
            btotal += ppm[a][b][2];
        }
    }
    double rf = rtotal / (1.0000 * pixels);
    double gf = gtotal / (1.0000 * pixels);
    double bf = btotal / (1.0000 * pixels);
    double diff3 = abs(rf - gf) + abs(gf - bf) + abs(rf - bf);
    return diff3 > 55 || (rf + gf + bf) < 200; //had to add this one case for rgbtotal < 200 bc of that one pesky dark quarter :(
}

void detection(string img, string grayimg, string hyimg, string nonmaximg, string bothimg, string vimg, string ccimg, int threshold1, int threshold2, int cthreshold, int pthreshold, string circleimg, string coinimg, string results, int minrad, int maxrad)
{
    readppm(img);
    readmakegrayscale(true, grayimg);
    vector<vector<int>> gradients;
    double ** dirs;
    dirs = new double* [rows];
    for(unsigned int i = 0; i < rows; i++)
    {
        dirs[i] = new double[cols];
    }
    for(unsigned int i = 0; i < rows; i++)
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
    for(unsigned int i = 0; i < rows; i++)
    {
        allgx[i] = new int[rows];
    }
    int** allgy;
    allgy = new int* [rows];
    for(unsigned int i = 0; i < cols; i++)
        allgy[i] = new int[rows];

    allgx = getgx(grayppm);
    allgy = getgy(grayppm);
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
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

    int** edgematrix;
    edgematrix = new int* [rows];
    for(int i = 0; i < rows; i++)
        edgematrix[i] = new int[cols];
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            edgematrix[i][j] = 0;
    for(unsigned int i = 0; i < rows; i++) 
    {
        for(unsigned int j = 0; j < cols; j++) 
        {
            out3 << gradients[i][j] << " " << gradients[i][j] << " " << gradients[i][j] << " ";
            edgematrix[i][j] = gradients[i][j];
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
    for(unsigned int i = 0; i < rows; i++) {
        for(unsigned int j = 0; j < cols; j++) 
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
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
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
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            out4 << votes[i][j] << " " << votes[i][j] << " " << votes[i][j] << " ";
        }
        out4 << "\n";
    }
    

    int** origins;
    origins = new int* [rows];
    for(int i = 0; i < rows; i++)
        origins[i] = new int[cols];
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            origins[i][j] = 0;
    vector<pair<int, int>> radii;
    for(unsigned int i = 0; i < rows; i++) 
    {
        for(unsigned int j = 0; j < cols; j++) 
        {
            if(votes[i][j] > cthreshold) 
            {
                circle(origins, i, j, 1, 1);
                circle(origins, i, j, 2, 1);
                circle(origins, i, j, 3, 1);
                circle(origins, i, j, 4, 1);
                radii.push_back(make_pair(i, j));
            }
        }
    }
    ofstream out5;
    out5.open(ccimg);
    out5 << "P3 " << cols << " " << rows << " " << 255 << '\n';
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
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

    cout << "hello\n";
    vector<pair<pair<int, int>, pair<int, double>>> centersandrads; // x, y, radius, percentage
    for(pair<int, int> p : radii)
    {
        for(int i = minrad + 1; i <= maxrad; i++)
        {
            cout << "hello\n";
            int xcor = p.first;
            int ycor = p.second;
            pair<bool, double> tempo = isedges(edgematrix, xcor, ycor, i, pthreshold);
            if(tempo.first)
            {
                cout << "hello\n";
                centersandrads.push_back(make_pair(make_pair(xcor, ycor), make_pair(i, tempo.second)));
                break;
            }
        }
    }
    cout << "hello\n";
    int** origins2;
    origins2 = new int* [rows];
    for(int i = 0; i < rows; i++)
        origins2[i] = new int[cols];
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            origins2[i][j] = 0;
    
    vector<int> toRemove;
    vector<pair<pair<int, int>, pair<int, double>>> filtered;
    int step = 0;
    while(step < (int) centersandrads.size())
    {
        int temporary = 0;
        int tempradius = 125;
        while(temporary < (int) centersandrads.size())
        {
            if(step == temporary)
            {
                temporary += 1;
                continue;
            }
            double tempor = sqrt((centersandrads[step].first.first - centersandrads[temporary].first.first) *  (centersandrads[step].first.first - centersandrads[temporary].first.first) + (centersandrads[step].first.second - centersandrads[temporary].first.second) * (centersandrads[step].first.second - centersandrads[temporary].first.second));
            if(tempor < tempradius)
            {
                if(centersandrads[step].second.second > centersandrads[temporary].second.second)
                {
                    centersandrads.erase(centersandrads.begin() + temporary);
                }
                else
                {
                    pair<pair<int, int>, pair<int, double>> temp5 = centersandrads[step];
                    centersandrads[step] = centersandrads[temporary];
                    centersandrads[temporary] = temp5;
                    centersandrads.erase(centersandrads.begin() + temporary);
                    tempradius = centersandrads[step].second.first;
                }
            }
            else
            {
                temporary += 1;
            }
        }
        step += 1;
    }

    
    
    
    
    for(pair<pair<int, int>, pair<int, double>> p : centersandrads)
    {
        int ax = p.first.first;
        int bx = p.first.second;
        int zx = p.second.first;
        circle(origins2, ax, bx, 1, 1);
        circle(origins2, ax, bx, 2, 1);
        circle(origins2, ax, bx, 3, 1);
        circle(origins2, ax, bx, 4, 1);
        circle(origins2, ax, bx, zx, 1);
        circle(origins2, ax, bx, zx + 1, 1);
        circle(origins2, ax, bx, zx + 2, 1);

    }
    
    ofstream out6;
    out6.open(circleimg);
    out6 << "P3 " << cols << " " << rows << " " << 255 << '\n';
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            if(origins2[i][j] == 1)
            {
                out6 << 255 << " " << 0 << " " << 0 << " ";
            }
            else
            {
                out6 << ppm[i][j][0] << " " << ppm[i][j][1] << " " << ppm[i][j][2] << " ";
            }
            
        }
        out6 << "\n";
    }
    
    int** origins3;
    origins3 = new int* [rows];
    for(int i = 0; i < rows; i++)
        origins3[i] = new int[cols];
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            origins3[i][j] = 0;
    int pennycount = 0;
    int dimecount = 0; 
    int nickelcount = 0; 
    int quartercount = 0;
    int halfcount = 0; 
    int silvercount = 0;
    for(pair<pair<int, int>, pair<int, double>> p : centersandrads)
    {
        
        int ax = p.first.first;
        int bx = p.first.second;
        int zx = p.second.first;
        circle(origins3, ax, bx, 1, 1);
        circle(origins3, ax, bx, 2, 1);
        circle(origins3, ax, bx, 3, 1);
        circle(origins3, ax, bx, 4, 1);
        circle(origins3, ax, bx, 5, 1);
        circle(origins3, ax, bx, 6, 1);
        circle(origins3, ax, bx, 7, 1);
        int colo = 0;
        if(zx < 87) //dime
        {
            colo = 3;
            dimecount+=1;
        }
        else if(zx < 95 && ispenny(ax, bx)) //penny
        {
            colo = 1;
            pennycount+=1;
        }
        else if(zx < 103) //nickel
        {
            colo = 2;
            nickelcount+=1;
        }
        else if(zx < 131) //quarter
        {
            colo = 4;
            quartercount+=1;
        }
        else if(zx < 146) //half dollar
        {
            colo = 5;
            halfcount+=1;
        }
        else //silver
        {
            colo = 6;
            silvercount+=1;
        }
        circle(origins3, ax, bx, zx, colo);
        circle(origins3, ax, bx, zx + 1, colo);
        circle(origins3, ax, bx, zx + 2, colo);
        circle(origins3, ax, bx, zx + 3, colo);
        circle(origins3, ax, bx, zx + 4, colo);
        
    }
    cout << "Penny Count: " << pennycount << "\n";
    cout << "Dime Count: " << dimecount << "\n";
    cout << "Nickel Count: " << nickelcount << "\n";
    cout << "Quarter Count: " << quartercount << "\n";
    cout << "Half Count: " << halfcount << "\n";
    cout << "Silver Count: " << silvercount << "\n";
    cout << "Total Sum: $"<<(pennycount + dimecount * 10 + nickelcount * 5 + quartercount * 25 + halfcount * 50 + silvercount * 100) / 100.0 << "\n";
    ofstream out8;
    out8.open(results);
    out8 << "Penny Count: " << pennycount << "\n";
    out8 << "Dime Count: " << dimecount << "\n";
    out8 << "Nickel Count: " << nickelcount << "\n";
    out8 << "Quarter Count: " << quartercount << "\n";
    out8 << "Half Count: " << halfcount << "\n";
    out8 << "Silver Count: " << silvercount << "\n";
    out8 << "Total Sum: $"<<(pennycount + dimecount * 10 + nickelcount * 5 + quartercount * 25 + halfcount * 50 + silvercount * 100) / 100.0 << "\n";
    
    
    ofstream out7;
    out7.open(coinimg);
    out7 << "P3 " << cols << " " << rows << " " << 255 << '\n';
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            if(origins3[i][j] == 1)
            {
                out7 << 255 << " " << 0 << " " << 0 << " "; //red-penny
            }
            else if(origins3[i][j] == 2)
            {
                out7 << 255 << " " << 255 << " " << 0 << " "; //yellow-nickel
                
            }
            else if(origins3[i][j] == 3)
            {
                out7 << 0 << " " << 0 << " " << 255 << " "; //blue-dime
                
            }
            else if(origins3[i][j] == 4)
            {
                out7 << 255 << " " << 0 << " " << 255 << " "; //purple-quarter
            }
            else if(origins3[i][j] == 5)
            {
                out7 << 0 << " " << 255 << " " << 0 << " "; //green-half
            }
            else if(origins3[i][j] == 6)
            {
                out7 << 255 << " " << 192 << " " << 203 << " "; //pink-silver
            }
            else
            {
                out7 << ppm[i][j][0] << " " << ppm[i][j][1] << " " << ppm[i][j][2] << " ";
            }
            
        }
        out7 << "\n";
    }
    
}

void part2(int argc, char** argv)
{
    //./l062 -f myimg.ppm -lt 150 -ht 200 -ff myimagef.ppm -TC 300 -fv myimagev.ppm -fcc myimageCC.ppm -TCircle 55 -fCi myimageCircles.ppm -fCo myimageCoins.ppm -fR myresults.txt
    string img = "image.ppm", grayimg = "imageg.ppm", hyimg = "image1.ppm", nonmaximg = "image2.ppm", bothimg = "imagef.ppm", vimg = "imagev.ppm", ccimg = "imageCC.ppm", circleimg = "imageCircles.ppm", coinimg = "imageCoins.ppm", results = "results.txt";
    int threshold1 = 75, threshold2 = 150, cthreshold = 22, pthreshold = 22, minrad = 90, maxrad = 125; //thresholds I found for easy image
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
        else if(temp == "-TCircle")
        {
            pthreshold = stoi(argv[i+1]);
        }
        else if(temp == "-fCi")
        {
            string temp2 = argv[i+1];
            circleimg = temp2;
        }
        else if(temp == "-fCo")
        {
            string temp2 = argv[i+1];
            coinimg = temp2;
        }
        else if(temp == "-fR")
        {
            string temp2 = argv[i+1];
            results = temp2;
        }
    }
    detection(img, grayimg, hyimg, nonmaximg, bothimg, vimg, ccimg, threshold1, threshold2, cthreshold, pthreshold, circleimg, coinimg, results, minrad, maxrad);
}
int main(int argc, char** argv)
{
    part2(argc, argv);
}
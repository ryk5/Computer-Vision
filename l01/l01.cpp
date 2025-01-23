#include<iostream>
#include <bits/stdc++.h>
#include <time.h>
#include <math.h>
using namespace std;
const int size = 800;
void point(int grid[size][size], int a, int b)
{
    if((a < size) & (a >= 0) & (b < size) & (b >= 0))
        grid[b][a] = 1;
}

void line(int grid[size][size], double af, double bf, double cf, double df) //scales to 800
{
    int a = (int)(af * size);
    int b = (int)(bf * size);
    int c = (int)(cf * size);
    int d = (int)(df * size);
    cout << a << " " << b << " " << c << " " << d << "\n";
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
    double bigr = r * size;
    int xmax = (int) (bigr / sqrt(2));
    int y = (int) bigr;
    int y2 = y * y;
    int ty = (2 * y) - 1;
    int y2_new = y2;
    int xi = (int) xcoord;
    int yi = (int) ycoord;
    for(int x = 0; x <= xmax + 1; x++)
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
tuple<double, double, double> circumcircle(double af, double bf, double cf, double df, double ef, double ff)
{
    double slopeab = -1.0 * ((cf - ef)/(df - ff));
    double slopecd = -1.0 * ((ef - af)/(ff - bf));
    double midx1 = (cf + ef)/2;
    double midy1 = (df + ff)/2;
    double midx2 = (af + ef)/2;
    double midy2 = (bf + ff)/2;
    double xcoord = (midy1 - (slopeab * midx1) - midy2 + (slopecd * midx2)) / (slopecd - slopeab);
    double ycoord = ((midy1 * slopecd) - (slopeab * midx1 * slopecd) - (midy2 * slopeab) + (slopecd * midx2 * slopeab)) / (slopecd - slopeab);
    double abcd = sqrt((df - bf)*(df - bf) + (cf - af) * (cf - af));
    double cdef = sqrt((ff - df)*(ff - df) + (ef - cf) * (ef - cf));
    double abef = sqrt((bf - ff)*(bf - ff) + (af - ef) * (af - ef));
    double s = 0.5 * (abcd + cdef + abef);
    double r = sqrt(((s - abcd) * (s - cdef) * (s - abef)) / s);
    double bigr = (abcd * cdef * abef) / (4 * s * r);
    
    cout << "radius: " << bigr << "\n";
    cout << "circumcoordinates: " << xcoord << ", " << ycoord << "\n";
    cout << "lengths: " << abcd << ", " << cdef << ", " << abef << "\n";
    return {xcoord, ycoord, bigr};

    
}
tuple<double, double, double> incircle(double af, double bf, double cf, double df, double ef, double ff)
{
    double abcd = sqrt((df - bf)*(df - bf) + (cf - af) * (cf - af));
    double cdef = sqrt((ff - df)*(ff - df) + (ef - cf) * (ef - cf));
    double abef = sqrt((bf - ff)*(bf - ff) + (af - ef) * (af - ef));
    double xcord = ((af * cdef) + (cf * abef) + (ef * abcd)) / (abef + abcd + cdef);
    double ycord = ((bf * cdef) + (df * abef) + (ff * abcd)) / (abef + abcd + cdef);
    cout << "incoordinates: " << xcord << ", " << ycord;
    double s = 0.5 * (abcd + cdef + abef);
    double r = sqrt(((s - abcd) * (s - cdef) * (s - abef)) / s);
    return {xcord, ycord, r};
}
void eulerline(int grid[size][size], double af, double bf, double cf, double df, double ef, double ff, double mx1, double my1, double mx2, double my2, double mx3, double my3)
{
    double slopeab = -1.0 * ((cf - ef)/(df - ff));
    double slopecd = -1.0 * ((ef - af)/(ff - bf));
    double midx1 = (cf + ef)/2;
    double midy1 = (df + ff)/2;
    double midx2 = (af + ef)/2;
    double midy2 = (bf + ff)/2;
    double xcoord = (midy1 - (slopeab * midx1) - midy2 + (slopecd * midx2)) / (slopecd - slopeab);
    double ycoord = ((midy1 * slopecd) - (slopeab * midx1 * slopecd) - (midy2 * slopeab) + (slopecd * midx2 * slopeab)) / (slopecd - slopeab);
    
    double af2 = (double) mx1;
    double bf2 = (double) my1;
    double cf2 = (double) mx2;
    double df2 = (double) my2;
    double ef2 = (double) mx3;
    double ff2 = (double) my3;
    double slopeab2 = -1.0 * ((cf2 - ef2)/(df2 - ff2));
    double slopecd2 = -1.0 * ((ef2 - af2)/(ff2 - bf2));
    double midx12 = (cf2 + ef2)/2;
    double midy12 = (df2 + ff2)/2;
    double midx22 = (af2 + ef2)/2;
    double midy22 = (bf2 + ff2)/2;
    double xcoord2 = (midy12 - (slopeab2 * midx12) - midy22 + (slopecd2 * midx22)) / (slopecd2 - slopeab2);
    double ycoord2 = ((midy12 * slopecd2) - (slopeab2 * midx12 * slopecd2) - (midy22 * slopeab2) + (slopecd2 * midx22 * slopeab2)) / (slopecd2 - slopeab2);
    
    double m = (ycoord2 - ycoord) / (xcoord2 - xcoord);
    double x = (int) -2 + xcoord;
    double y = (int) -2 * m + ycoord;
    double z = (int) 2 + xcoord2;
    double w = (int) 2 * m + ycoord2;
    line(grid, x, y, z, w);
    
}
void generate(int grid[size][size])
{
    srand(time(0));
    double a, b, c, d, e, f;
    a = ((double) rand() / (RAND_MAX));
    b = ((double) rand() / (RAND_MAX));
    c = ((double) rand() / (RAND_MAX));
    d = ((double) rand() / (RAND_MAX));
    e = ((double) rand() / (RAND_MAX));
    f = ((double) rand() / (RAND_MAX));
    
    tuple <double, double, double> circum = circumcircle(a, b, c, d, e, f);
    circle(grid, get<0>(circum), get<1>(circum), get<2>(circum));
    tuple <double, double, double> inc = incircle(a, b, c, d, e, f);
    circle(grid, get<0>(inc), get<1>(inc), get<2>(inc));
    double mx1 = (a + c) / 2;
    double mx2 = (c + e) / 2;
    double mx3 = (a + e) / 2;
    double my1 = (b + d) / 2;
    double my2 = (d + f) / 2;
    double my3 = (b + f) / 2;
    
    tuple <double, double, double> ninepoint = circumcircle(mx1, my1, mx2, my2, mx3, my3);
    circle(grid, get<0>(ninepoint), get<1>(ninepoint), get<2>(ninepoint));
    line(grid, a, b, c, d);
    line(grid, c, d, e, f);
    line(grid, e, f, a, b);
    eulerline(grid, a, b, c, d, e, f, mx1, my1, mx2, my2, mx3, my3);
}
int main()
{
    srand ( time(NULL) );
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
    generate(grid);
    for(int i = 800 - 1 ; i >= 0; i--)
    {
        for(int j = 0; j < 800; j++)
        {
            out << grid[i][j] << " " << grid[i][j] << " " << grid[i][j] << " ";
        }
        out << "\n";
         
    }
    return 0;
}

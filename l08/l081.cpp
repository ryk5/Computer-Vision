a#include <stdio.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#define _USE_MATH_DEFINES

using namespace std;
using namespace cv;

ofstream out;
class Point3D
{
    private:
        //coords
        double x;
        double y;
        double z;
        //scale
        int w;
    public:
        Point3D()
        {
            x, y, z = 0.0;
            w = 0;
        }
        Point3D(double xcoord, double ycoord, double zcoord, int scale)
        {
            x = xcoord;
            y = ycoord;
            z = zcoord;
            w = scale;
        }
        //getter methods
        double getX()
        {
            return x;
        }
        double getY()
        {
            return y;
        }
        double getZ()
        {
            return z;
        }
        double getW()
        {
            return w;
        }
        //setter methods
        void setX(double temp)
        {
            x = temp;
        }
        void setY(double temp)
        {
            y = temp;
        }
        void setZ(double temp)
        {
            z = temp;
        }
        void setW(double temp)
        {
            w = temp;
        }
        Point orthographic()
        {
            return Point(x, y);
        }
        string toString()
        {
            return "(" + to_string(int(x)) + "," + to_string(int(y)) + "," + to_string(int(z)) + ")";
        }
};

Point3D translate(Point3D input, double dx, double dy, double dz)
{
    Point3D toReturn(input.getX() + dx, input.getY() + dy, input.getZ() + dz, 1);
    return toReturn;
}
Point3D scale(Point3D input, double dx, double dy, double dz)
{
    Point3D toReturn(input.getX() * dx, input.getY() * dy, input.getZ() * dz, 1);
    return toReturn;
}
Point3D rotation(Point3D input, double dx, double dy, double dz)
{
    double xmatrix[4][4] = {{1, 0, 0, 0},
                            {0, cos(dx * (M_PI) / 180), -1 * sin(dx * (M_PI) / 180), 0},
                            {0, sin(dx * (M_PI) / 180), cos(dz * (M_PI) / 180), 0},
                            {0, 0, 0, 1}};
    double ymatrix[4][4] = {{cos(dy * (M_PI) / 180), 0, sin(dy * (M_PI) / 180), 0},
                            {0, 1, 0, 0},
                            {-1 * sin(dy * (M_PI) / 180), 0, cos(dy * (M_PI) / 180), 0},
                            {0, 0, 0, 1}};
    double zmatrix[4][4] = {{cos(dz * (M_PI) / 180), -1 * sin(dz * (M_PI) / 180), 0, 0},
                            {sin(dz * (M_PI) / 180), cos(dz * (M_PI) / 180), 0, 0},
                            {0, 0, 1, 0},
                            {0, 0, 0, 1}};
    double inputvector[1][4] = {{input.getX(), input.getY(), input.getZ(), 1}};
    Mat product = Mat(4, 4, CV_64FC1, xmatrix) * Mat(4, 4, CV_64FC1, ymatrix) * Mat(4, 4, CV_64FC1, zmatrix) * Mat(1, 4, CV_64FC1, inputvector).t();
    Point3D toReturn(product.at<double>(0, 0), product.at<double>(1, 0), product.at<double>(2, 0), 1);
    return toReturn;
}

void playvideo(VideoWriter video, vector<Point3D> points)
{
    
    int scaling = 0;
    int temp = 0;
    if((int) points.size() == 8) //cube
    {
        scaling = 30;
        temp = scaling * scaling * 4;
    }
    if((int) points.size() == 4) //tetrahedron
    {
        scaling = 80;
        temp = scaling * scaling;
    }
    for(int i = 0; i < (int) points.size(); i++)
    {
        points[i] = scale(points[i], scaling, scaling, scaling);
    }
    int size = (int) points.size();
    for(int i = 0; i < 1000; i++)
    {
        Mat frame(800, 600, CV_8UC3, Scalar(1, 1, 1));
        for (int j = 0; j < size; j++) 
        {
            Point3D temp2 = rotation(points[j], i, i, 0);
            temp2 = translate(temp2, 300, 400, 0);
            for(int k = j + 1; k < size; k++) 
            {
                double dist = (points[j].getX() - points[k].getX()) * (points[j].getX() - points[k].getX()) + (points[j].getY() - points[k].getY()) * (points[j].getY() - points[k].getY()) + (points[j].getZ() - points[k].getZ()) * (points[j].getZ() - points[k].getZ());
                if (dist > temp - 1 && dist < temp + 1 ) 
                {
                    line(frame, temp2.orthographic(), translate(rotation(points[k], i, i, 0), 300, 400, 0).orthographic(), Scalar(0, 255, 0), 1, 8);
                    circle(frame, temp2.orthographic(), 5, Scalar(0, 0, 255), FILLED, LINE_8);
                    circle(frame, translate(rotation(points[k], i, i, 0), 300, 400, 0).orthographic(), 5, Scalar(0, 0, 255), FILLED, LINE_8);
                }
            }
            if (size == 8 and i <= 3) 
            {
                if (j == size - 1) 
                {
                    out << temp2.toString() << endl;
                }
                else
                {
                    out << temp2.toString() << ", ";
                }
            }
        }
        video.write(frame);
    }
    
}

void part1() 
{
    out.open("coordinates.txt");
    VideoWriter video("rotation.avi", cv::VideoWriter::fourcc('M','J','P','G'), 150, Size(600, 800));
    vector<Point3D> cubepoints = { Point3D(-1, -1, 1, 1), Point3D(-1, 1, 1, 1), Point3D(-1, 1, -1, 1), Point3D(-1, -1, -1, 1), Point3D(1, 1, 1, 1), Point3D(1, -1, -1, 1), Point3D(1, -1, 1, 1), Point3D(1, 1, -1, 1) };
    playvideo(video, cubepoints);
    vector<Point3D> tetrapoints = {Point3D(-sqrt(3) / 6, 0.5, 0, 1), Point3D(0, 0, 2 / sqrt(6), 1), Point3D(1 / sqrt(3), 0, 0, 1), Point3D(-sqrt(3) / 6, -0.5, 0, 1)};
    playvideo(video, tetrapoints);
    video.release();
    
}

int main() 
{
    part1();
 
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#define _USE_MATH_DEFINES

using namespace std;
using namespace cv;

ofstream out;
ofstream out2;
ofstream out3;
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
        Point3D(Vec3f vector)
        {
            x = vector[0];
            y = vector[1];
            z = vector[2];
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
        Point3D plus(Point3D& other)
        {
            double tempx = getX() + other.getX();
            double tempy = getY() + other.getY();
            double tempz = getZ() + other.getZ();
            return Point3D(tempx, tempy, tempz, 1);
        }
        Point3D minus(Point3D& other)
        {
            double tempx = getX() - other.getX();
            double tempy = getY() - other.getY();
            double tempz = getZ() - other.getZ();
            return Point3D(tempx, tempy, tempz, 1);
        }
        Point3D scale(double num)
        {
            double tempx = num * getX();
            double tempy = num * getY();
            double tempz = num * getZ();
            return Point3D(tempx, tempy, tempz, 1);
        }
        string toString()
        {
            return "(" + to_string(double(x)) + "," + to_string(double(y)) + "," + to_string(double(z)) + ")";
        }
        Vec3f vectorize()
        {
            return Vec3f(x, y, z);
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
                            {0, sin(dx * (M_PI) / 180), cos(dx * (M_PI) / 180), 0},
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
    Point3D toReturn(0, 0, 0, 1);
    double firstelem = product.at<double>(0, 0);
    double secondelem = product.at<double>(1, 0);
    double thirdelem = product.at<double>(2, 0);
    toReturn.setX(firstelem);
    toReturn.setY(secondelem);
    toReturn.setZ(thirdelem);
    return toReturn;
}
Point3D perspective_rendering(Point3D pt, int dx, int dy, int dz, int b)
{
    double temp = ((b - dx) / (pt.getX() - dx));
    return Point3D(b, temp * pt.getY() + (1 - temp) * dy, temp * pt.getZ() + (1 - temp) * dz, 1);
}
Point3D perspective_projection(Vec3f vector, Vec3f a, Vec3f n, Vec3f e)
{
    double temp = (a - e).dot(n) / (vector - e).dot(n);
    return Point3D((vector - e) * temp + e);
}
Point2d rendering2D(Vec3f v, Vec3f a, Vec3f b, Vec3f c, double dx, double dy)
{
    double tempx = (double) (v - a).dot(b) / (b.dot(b)) + dx;
    double tempy = (double) (v - a).dot(c) / (c.dot(c)) + dy;
    return Point2d(tempx, tempy);
}
Vec3f normalize(Vec3f a)
{
    double norm = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    return Vec3f(a[0] / norm, a[1] / norm, a[2] / norm);
}
void playvideo(VideoWriter video, vector<Point3D> points, Vec3f a, Vec3f n, Vec3f eye)
{
    int scaling = 150;
    int temp = 150 * 150;
    if((int) points.size() == 8) //cube
    {
        scaling = 50;
        temp = 4 * 50 * 50;
    }
    for(int i = 0; i < (int) points.size(); i++)
    {
        points[i] = scale(points[i], scaling, scaling, scaling);
    }
    int size = (int) points.size();
    Vec3f origin(perspective_projection(Vec3f(0, 0, 0), a, n, eye).vectorize());
    Vec3f v1(-50, 50, 50);
    Vec3f v2(-50, -50, 50);
    Vec3f v3(50, 50, 50);
    Vec3f pv1(perspective_projection(v1, a, n, eye).vectorize());
    Vec3f pv2(perspective_projection(v2, a, n, eye).vectorize());
    Vec3f pv3(perspective_projection(v3, a, n, eye).vectorize());
    Vec3f a2 = pv1 - pv2;
    Vec3f b = pv3 - pv1;
    Vec3f w1 = normalize(a2);
    double factor = (a2[0] * b[0] + a2[1] * b[1] + a2[2] * b[2]) / (a2[0] * a2[0] + a2[1] * a2[1] + a2[2] * a2[2]);
    Vec3f w2 = normalize((b - factor * a2));
    for(int i = 0; i < 360; i++)
    {
        Mat frame(800, 600, CV_8UC3, Scalar(1, 1, 1));
        vector<Vec3f> points3D;
        vector<Point2d> points2D;
        vector<Vec3f> temp3D;
        vector<Point2d> temp2D;
        for (int j = 0; j < points.size(); j++) 
        {               
            Point3D pt = translate(rotation(points[j], 0, 0, i), 0, 300, 400);
            Vec3f v = pt.vectorize();
            Point3D tempo = perspective_projection(rotation(points[j], 0, 0, i).vectorize(), a, n, eye);
            Point2d pt2(rendering2D(tempo.vectorize(), origin, w1, w2, 300, 400));
            temp3D.push_back(v);
            temp2D.push_back(pt2);
            if (i <= 3 and size == 8) 
            {
                if (j == size - 1) 
                {
                    out2 << "(" << pt.getX() << ", " << pt.getY() << ", " << pt.getZ()  << ")" << endl;
                    out3 << "(" << pt2.x - 300 << ", " << pt2.y - 400 << ")" << endl;
                }
                else
                {
                    out2 << "(" << pt.getX() << ", " << pt.getY() << ", " << pt.getZ() << "), ";
                    out3 << "(" << pt2.x - 300 << ", " << pt2.y - 400 << "), ";
                }
            }
            for (int k = j + 1; k < points.size(); k++) 
            {
                double dist = (points[j].getX() - points[k].getX()) * (points[j].getX() - points[k].getX()) + (points[j].getY() - points[k].getY()) * (points[j].getY() - points[k].getY()) + (points[j].getZ() - points[k].getZ()) * (points[j].getZ() - points[k].getZ());
                if(dist > temp - 1 && dist < temp + 1) 
                {
                    Point3D pt3 = translate(rotation(points[k], 0, 0, i), 0, 300, 400);
                    Vec3f vec3 = pt3.vectorize();
                    Point2d pt4(rendering2D(perspective_projection(rotation(points[k], 0, 0, i).vectorize(), a, n, eye).vectorize(), origin, w1, w2, 300, 400));
                    line(frame, pt2, pt4, Scalar(0, 255, 255), 1, 8);
                    circle(frame, pt2, 5, Scalar(0, 0, 255), FILLED, LINE_8);
                    circle(frame, pt4, 5, Scalar(0, 0, 255), FILLED, LINE_8);
                    points3D.push_back(v);
                    points3D.push_back(vec3);
                    points2D.push_back(pt2);
                    points2D.push_back(pt4);
                }
            }
        }
        if (i <= 3 and size == 8) 
        {
            if(i == 0) 
            {
                out << "The plane defined by (x-a)*n =0 is:" << endl;
                out << "a = (" << a[0] << ", "<< a[1] << ", " << a[2] << ")" << endl;
                out << "n = (" << n[0] << ", "<< n[1] << ", " << n[2] << ")" << endl;
                out << "The eye e is:" << endl;
                out << "e = (" << eye[0] << ", "<< eye[1] << ", " << eye[2] << ")" << endl;
                out << endl;
                out << "Vertices I used to create the 2d coordinate system and their projections are:" << endl;
                out << "v1 = (" << v1[0] << ", "<< v1[1] << ", " << v1[2] << ")" << endl;
                out << "v2 = (" << v2[0] << ", "<< v2[1] << ", " << v2[2] << ")" << endl;
                out << "v3 = (" << v3[0] << ", "<< v3[1] << ", " << v3[2] << ")" << endl;
                out << endl;
                out << "pv1 = (" << pv1[0] << ", "<< pv1[1] << ", " << pv1[2] << ")" << endl;
                out << "pv2 = (" << pv2[0] << ", "<< pv2[1] << ", " << pv2[2] << ")" << endl;
                out << "pv3 = (" << pv3[0] << ", "<< pv3[1] << ", " << pv3[2] << ")" << endl;
                out << endl;
                out << "The 2 vectors a and b that are in the plane are:" << endl;
                out << "a = pv1-pv2 = (" << a2[0] << ", "<< a2[1] << ", " << a2[2] << ")" << endl;
                out << "b = pv3-pv1 = (" << b[0] << ", "<< b[1] << ", " << b[2] << ")" << endl;
                out << endl;
                out << "The w1 and w2 obtained from a and b (these now are perpendicular and of magnitude 1) are:" << endl;
                out << "w1 = (" << w1[0] << ", "<< w1[1] << ", " << w1[2] << ")" << endl;
                out << "w2 = (" << w2[0] << ", "<< w2[1] << ", " << w2[2] << ")" << endl;
                out << endl;
                out << "The center of the cube in first frame and its projection are:" << endl;
                out << "center = (" << 0 << ", "<< 0 << ", " << 0 << ")" << endl;
                out << "p0 = (" << origin[0] << ", "<< origin[1] << ", " << origin[2] << ")" << endl;
                out << endl;
                out << "The coordinates in the 2d plane x = p0 + u*w1 + v*w2 are:" << endl;
                out << "(where p0 is the origin, preferraby the projection of the center of the cube in first frame, w1 and w2 are 2 perpendicular vertices in the plane)" << endl;
                out << "p0 = (" << origin[0] << ", "<< origin[1] << ", " << origin[2] << ")" << endl;
                out << "w1 = (" << w1[0] << ", "<< w1[1] << ", " << w1[2] << ")" << endl;
                out << "w2 = (" << w2[0] << ", "<< w2[1] << ", " << w2[2] << ")" << endl;
                out << endl;
            }
            out << "The frame" << (i + 1) <<" in 3d has the following edges:" <<endl;
            for(int k = 0; k < points3D.size(); k++) 
            {
                if (k % 2 == 1) 
                {
                    out << ", ("<<points3D[k][0] << ", " << points3D[k][1] - 300 << ", " << points3D[k][2] - 400 << ")" << endl;
                } 
                else 
                {
                    out << "(" << points3D[k][0] << ", " << points3D[k][1] - 300 << ", " << points3D[k][2] - 400 << ")";
                }
            }
            out << "The frame" << (i + 1) << " in 2d has the following edges:" << endl;
            for(int k = 0; k < points2D.size(); k++) 
            {
                if (k % 2 == 1) 
                {
                    out << ", (" << points2D[k].x - 300 << ", " << points2D[k].y - 400 << ")" << endl;
                } 
                else 
                {
                    out << "("<<points2D[k].x - 300 << ", " << points2D[k].y - 400 << ")";
                }
            }
        }
        video.write(frame);
    }
    
    
}

void part3(int argc, char** argv)
{
    Vec3f a(700.500000,200.100000,100.120000);
    Vec3f n(1.000000,2.000000,3.120000);
    Vec3f eye(1000.000000,900.230000,100.115600);
    for(int i = 0; i < argc; i++) 
    {
        string temp = argv[i];
        if(temp == "-a") 
        {
            string temp2 = argv[i+1];
            int firstind = temp2.find("(");
            int secondind = temp2.find(",");
            double a1 = stod(temp2.substr(firstind + 1, secondind));
            temp2 = temp2.substr(secondind + 1);
            secondind = temp2.find(",");
            double a2 = stod(temp2.substr(0, secondind));
            temp2 = temp2.substr(secondind + 1);
            secondind = temp2.find(")");
            double a3 = stod(temp2.substr(0, secondind));
            a[0] = a1;
            a[1] = a2;
            a[2] = a3;
        } 
        else if(temp == "-n") 
        {
            string temp2 = argv[i+1];
            int firstind = temp2.find("(");
            int secondind = temp2.find(",");
            double n1 = stod(temp2.substr(firstind + 1, secondind));
            temp2 = temp2.substr(secondind + 1);
            secondind = temp2.find(",");
            double n2 = stod(temp2.substr(0, secondind));
            temp2 = temp2.substr(secondind + 1);
            secondind = temp2.find(")");
            double n3 = stod(temp2.substr(0, secondind));
            n[0] = n1;
            n[1] = n2;
            n[2] = n3;
        } 
        else if(temp == "-e") 
        {
            string temp2 = argv[i+1];
            int firstind = temp2.find("(");
            int secondind = temp2.find(",");
            double e1 = stod(temp2.substr(firstind + 1, secondind));
            temp2 = temp2.substr(secondind + 1);
            secondind = temp2.find(",");
            double e2 = stod(temp2.substr(0, secondind));
            temp2 = temp2.substr(secondind + 1);
            secondind = temp2.find(")");
            double e3 = stod(temp2.substr(0, secondind));
            eye[0] = e1;
            eye[1] = e2;
            eye[2] = e3;
        } 
        
    }
    
    
    out.open("log.txt");
    out2.open("coordinates.txt");
    out3.open("coordinates2d.txt");
    VideoWriter video("rotation.avi", cv::VideoWriter::fourcc('M','J','P','G'), 35, Size(600, 800));
    vector<Point3D> cubepoints = { Point3D(-1, 1, 1, 1), Point3D(1, -1, -1, 1), Point3D(-1, -1, 1, 1), Point3D(1, 1, -1, 1),  Point3D(-1, -1, -1, 1), Point3D(1, 1, 1, 1), Point3D(-1, 1, -1, 1), Point3D(1, -1, 1, 1) };
    playvideo(video, cubepoints, a, n, eye);
    vector<Point3D> tetrapoints = {Point3D(1 / sqrt(3), 0, 0, 1), Point3D(0, 0, 2 / sqrt(6), 1), Point3D(-sqrt(3) / 6, 0.5, 0, 1), Point3D(-sqrt(3) / 6, -0.5, 0, 1)};
    playvideo(video, tetrapoints, a, n, eye);
    video.release();
}

int main(int argc, char** argv) 
{
    part3(argc, argv);
}

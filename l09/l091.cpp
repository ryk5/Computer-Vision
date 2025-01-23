#include <stdio.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
#define _USE_MATH_DEFINES

using namespace cv;
using namespace std;
void render_video(VideoWriter video, vector<vector<Point3f>> obj, vector<vector<Point2f>> img, Mat cameraMatrix, Mat distC, Mat R, Mat T, vector<Point2i> edges, vector<Point3f> points3D) 
{
    vector<Point2f> projpoints;
    VideoCapture cap2("withChessBoard.MOV"); //cap2, obj, img, cameraMatrix, distC, projpoints, edges, 
    int i = 0;
    Mat nextImg;
    while(true) 
    {
        if(cap2.read(nextImg) == false) 
        {
            break;
        }
        else
        {
            cv::rotate(nextImg, nextImg, ROTATE_180);
            solvePnP(obj[i], img[i], cameraMatrix, distC, R, T);
            projectPoints(points3D, R, T, cameraMatrix, distC, projpoints);
            for(Point2i temp : edges) 
            {
                Point2f tempx = projpoints[temp.x];
                Point2f tempy = projpoints[temp.y];
                line(nextImg, tempx, tempy, Scalar(255, 0, 255), 2);
            }
            i += 1;
            video.write(nextImg);
        }
            
    }
//     video.release();
    cap2.release();
    
}

void part1()
{
    vector<Point3f> pvertices, points3D;
    pvertices.push_back(Point3f(1, 1, 0));
    pvertices.push_back(Point3f(-1, 1, 0));
    pvertices.push_back(Point3f(1, -1, 0));
    pvertices.push_back(Point3f(-1, -1, 0));
    points3D.push_back(Point3f(1, 1, -2));
    points3D.push_back(Point3f(1, -1, -2));
    points3D.push_back(Point3f(-1, 1, -2));
    points3D.push_back(Point3f(-1, -1, -2));
    points3D.push_back(Point3f(1, 1, 0));
    points3D.push_back(Point3f(1, -1, 0));
    points3D.push_back(Point3f(-1, 1, 0));
    points3D.push_back(Point3f(-1, -1, 0));
    
    vector<vector<Point3f>> obj, objSet;
    vector<vector<Point2f>> img, imgSet;
    vector<Point2f> out, corners, nextPts;
    Mat prevImg, cameraMatrix, distC, R, T, nextImg;
    VideoCapture cap("withChessBoard.MOV");
    vector<Point2i> edges;
    vector<int> cornerindices = {16, 18, 30, 32};
    int width = (int) cap.get(3);
    int height = (int) cap.get(4);
    Size dimensions = Size(width, height);
    VideoWriter video("vr.avi", cv::VideoWriter::fourcc('M','J','P','G'), cap.get(CAP_PROP_FPS), dimensions); 
    int i = 0;
    while(true)
    {
        bool exists = cap.read(nextImg);
        if(exists == false)
        {
            break;
        }
        else
        {
            cv::rotate(nextImg, nextImg, cv::ROTATE_180);
            cvtColor(nextImg, nextImg, COLOR_BGR2GRAY);
            out.clear();
            vector<unsigned char> status;
            vector<float> err;
            Size winSize = Size(11, 11);
            Size zeroZone = Size(-1, -1);
            bool found = findChessboardCorners(nextImg, Size(7, 7), out, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);
            if (found == false) 
            {
                calcOpticalFlowPyrLK(prevImg, nextImg, corners, nextPts, status, err, Size(15, 15), 2, TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03));
                corners = nextPts;
            } 
            else 
            {
                cornerSubPix(nextImg, out, winSize, zeroZone, TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.01));
                corners.clear();
                for(int j = 0; j < cornerindices.size(); j++)
                {
                    corners.push_back(out[cornerindices[j]]);
                } 
                
                
            }
            nextImg.copyTo(prevImg);
            img.push_back(corners);
            obj.push_back(pvertices);
            if(i % 5 == 0 && i % 2 == 0) 
            {
                imgSet.push_back(corners);
                objSet.push_back(pvertices);
            }
            i += 1;
            
        }
    }

    calibrateCamera(objSet, imgSet, prevImg.size(), cameraMatrix, distC, R, T);
    for(int i = points3D.size() - 2; i >= 0 ; i--) 
    {
        for(int j = i + 1; j < points3D.size(); j++) 
        {
            if(sqrt((points3D[i].x - points3D[j].x) * (points3D[i].x - points3D[j].x) + (points3D[i].y - points3D[j].y) * (points3D[i].y - points3D[j].y) + (points3D[i].z - points3D[j].z) * (points3D[i].z - points3D[j].z)) == 2) //check if it is an edge (vertex to vertex)
            {
                edges.push_back(Point2i(i, j));
            }
        }
    }
    
    render_video(video, obj, img, cameraMatrix, distC, R, T, edges, points3D);
    cap.release();
    video.release();
    

}

int main(int argc, char** argv)
{
    part1();
}


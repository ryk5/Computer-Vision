#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;
int threshold1 = 50, threshold2 = 100, pthreshold = 35, minrad = 70, maxrad = 125, quarter = 105, blurmag = 3, spread = 105;
string img = "image.jpg", grayimg = "imageg.jpg", bothimg = "imagef.jpg", circleimg = "imageCircles.jpg", coinimg = "imageCoins.jpg", results = "results.txt";
Mat grayscale(string filename) //writes and returns grayscale
{
    Mat toReturn;
    toReturn = imread(filename, IMREAD_GRAYSCALE);
    imwrite("./imageg.jpg", toReturn);
    return toReturn;
}

void part1()
{
    
    Mat image, roi, tempmat, canny;
    image = imread(img, 1);
    Mat copyimg = image.clone();
    Mat grayimg = grayscale(img);
    GaussianBlur(grayimg, tempmat, Size(blurmag, blurmag), 0, 0);
    Canny(tempmat, canny, threshold1, threshold2);
    imwrite("./" + bothimg, canny);
    vector<Vec3f> filtered, postfiltered;
    if (maxrad > 135) 
    {
        HoughCircles(grayimg, filtered, HOUGH_GRADIENT, 1, spread, threshold2, pthreshold, minrad, 120);
    } 
    else 
    {
        HoughCircles(grayimg, filtered, HOUGH_GRADIENT, 1, spread, threshold2, pthreshold, minrad, maxrad);
    }
    
    Scalar colors[5] = {Scalar(0, 0, 255), Scalar(0, 255, 255), Scalar(255, 0,0), Scalar(255,0,255), Scalar(203, 192, 255 )}; //penny, nickel, dime, quarter, silver
    int numdimes = 0;
    int numpennies = 0;
    int numnickels = 0;
    int numquarters = 0;
    int numsilvers = 0;
    double money = 0;
    vector<int> types;
    for(int i = 0; i < filtered.size(); i++)
    {
        Vec3i temp = filtered[i];
        int temp1 = temp[0] - temp[2];
        int temp2 = temp[1] - temp[2];
        if(temp1 < 0)
        {
            temp1 = 0;
        }
        if(temp2 < 0)
        {
            temp2 = 0;
        }
        roi = image(Rect(temp1, temp2, 2 * filtered[i][2], 2 * filtered[i][2]));
        Mat polarize(roi.rows, roi.cols, CV_8UC3, Scalar(0, 0, 0));
        circle(polarize, Point(filtered[i][2], filtered[i][2]), filtered[i][2], Scalar(255, 255, 255), FILLED);
        polarize = roi & polarize;
        Scalar avg = mean(polarize);
        int avgR = avg.val[2];
        int avgG = avg.val[1];
        int avgB = avg.val[0];
        int cointype = 0;
        int radius = filtered[i][2];

        if((avgR + avgG + avgB) > 650)
        {
            filtered.erase(filtered.begin() + i);
            i--;
        }
        else if(filtered[i][2] > 80 && filtered[i][2] < quarter)
        {
            if(avgR > 1.3 * avgB || (avgR + avgG + avgB) < 150) 
            {
                numpennies++;
                types.push_back(0);
                money += 0.01;
            } 
            else 
            {
                numnickels++;
                types.push_back(1);
                money += 0.05;
            }
        }
        else if(filtered[i][2] >= quarter)
        {
            if(avgR < 1.3 * avgB)
            {
                numquarters++;
                types.push_back(3);
                money += 0.25;
                
            }
            else
            {
                filtered.erase(filtered.begin() + i);
                i--;
            }
        }
        
        else 
        {
            if(avgR > 1.3 * avgB || (avgR + avgG + avgB) < 150)
            {
                numpennies++;
                types.push_back(0);
                money += 0.01;
            }
            else
            {
                numdimes++;
                types.push_back(2);
                money += 0.1;
            }
        }
        
    }
    if (maxrad > 135) 
    {
        HoughCircles(grayimg, postfiltered, HOUGH_GRADIENT, 1, minrad, threshold2, pthreshold, 150, maxrad);
        for (int i = 0; i < postfiltered.size(); i++) 
        {
            filtered.push_back(postfiltered[i]);
            types.push_back(4);
            numsilvers++;
            money += 1;
        }
    }
    for (int i = 0; i < filtered.size(); i++) 
    {
        Vec3i coin = filtered[i];
        Point center(coin[0], coin[1]);
        circle(copyimg, center, 0, Scalar(0, 0, 255), 4, LINE_8);
        circle(copyimg, center, coin[2], Scalar(0, 0, 255), 4, LINE_8);
        circle(image, center, 0, colors[types[i]], 4, LINE_8);
        circle(image, center, coin[2], colors[types[i]], 4, LINE_8);
    }
    imwrite("./" + circleimg, copyimg);
    imwrite("./" + coinimg, image);
    cout << "Penny Count: " << numpennies << "\n";
    cout << "Dime Count: " << numdimes << "\n";
    cout << "Nickel Count: " << numnickels << "\n";
    cout << "Quarter Count: " << numquarters << "\n";
    cout << "Silver Count: " << numsilvers << "\n";
    cout << "Total Sum: $"<< money << "\n";
    ofstream out;
    out.open(results);
    out << "Penny Count: " << numpennies << "\n";
    out << "Dime Count: " << numdimes << "\n";
    out << "Nickel Count: " << numnickels << "\n";
    out << "Quarter Count: " << numquarters << "\n";
    out << "Silver Count: " << numsilvers << "\n";
    out << "Total Sum: $"<< money << "\n";
    
}
int main(int argc, char** argv)
{
    
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
        else if(temp == "-TCircle")
        {
            pthreshold = stoi(argv[i+1]);
        }
        else if(temp == "-minr") 
        {
            minrad = stoi(argv[i+1]);
        } 
        else if(temp == "-maxr") 
        {   
            maxrad = stoi(argv[i+1]);
        } 
        else if(temp == "-qu")
        {
            quarter = stoi(argv[i+1]);
        }
        else if(temp == "-bl") 
        {   
            blurmag = stoi(argv[i+1]);
        } 
        else if(temp == "-sp") 
        {   
            spread = stoi(argv[i+1]);
        } 
        
    }
    part1();
}
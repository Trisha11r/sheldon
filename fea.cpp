#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;
using namespace cv;

#define PI 3.14159265

vector <Mat> readImages()
{
	vector<Mat> images;
	vector<String> filenames; // notice here that we are using the Opencv's embedded "String" class
    String folder = "/home/trisha/SHELDON/images"; // again we are using the Opencv's embedded "String" class

    glob(folder, filenames); // new function that does the job ;-)

    for(size_t i = 0; i < filenames.size(); ++i)
    {
        Mat src = imread(filenames[i]);
        
        images.push_back(src);
    }
    //waitKey(0);
    return images;
}
vector <Point2f> getPoint(Mat image)
{
	vector <Point2f> point;
	int j,k;
	Mat canny_output;
    int thresh=100;
    vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Canny(image, canny_output, thresh, thresh*2, 3);
	findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0) );
	for(j=0;j<contours.size();j++)
		for(k=0;k<contours[j].size();k++)
			point.push_back(contours[j][k]);
	//cout<<"\t"<<(int)point.size()<<endl;
		/*
	Mat drawing = Mat::zeros( image.size(), CV_8UC3 );
	for( int i = 0; i< contours.size(); i++ )
	{
		Scalar color = Scalar( 255, 255, 255 );
		drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
		//rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
		//circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
	}
	imshow("drawing",drawing);
	waitKey(0);*/
	return point;
}
Mat getImageBlurred(Mat im)
{
	Mat im1=Mat(200,200,CV_8UC3);
	resize(im,im1,im1.size());
	Mat im2,bwim;
	cvtColor(im1,im2,CV_BGR2GRAY);
	threshold(im2, bwim, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	
	vector<Point2f> contours_poly;
	Rect boundRect;
	
	vector <Point2f> curImagePoints = getPoint(bwim);
	approxPolyDP( Mat(curImagePoints), contours_poly, 3, true );
	boundRect = boundingRect( Mat(contours_poly) );	
	
	Mat src,src1,dst;
	
	src=bwim(Rect(boundRect.x,boundRect.y,boundRect.width,boundRect.height));
	src1=Mat(200,200,CV_8UC1);
	resize(src,src1,src1.size());
	blur(src1,dst,Size(25,25),Point(-1,-1));
	return dst;
}
Mat getImageBlurred1(Mat im)
{
	Mat im1=Mat(200,200,CV_8UC3);
	resize(im,im1,im1.size());
	Mat im2,bwim;
	cvtColor(im1,im2,CV_BGR2GRAY);
	threshold(im2, bwim, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	bitwise_not(bwim,bwim);
	vector<Point2f> contours_poly;
	Rect boundRect;
	
	vector <Point2f> curImagePoints = getPoint(bwim);
	approxPolyDP( Mat(curImagePoints), contours_poly, 3, true );
	boundRect = boundingRect( Mat(contours_poly) );	
	
	

	Mat src,src1,dst;
	
	src=bwim(Rect(boundRect.x,boundRect.y,boundRect.width,boundRect.height));
	src1=Mat(200,200,CV_8UC1);
	resize(src,src1,src1.size());
	blur(src1,dst,Size(25,25),Point(-1,-1));
	return dst;
}
double getDistance(Mat im1, Mat im2)
{
	int i,j,sum=0;
	for(i=0;i<im1.rows;i++)
	{
		for(j=0;j<im1.cols;j++)
		{
			sum+=(im1.at<uchar>(i,j)-im2.at<uchar>(i,j))*(im1.at<uchar>(i,j)-im2.at<uchar>(i,j));
		}
	}
	return sqrt(sum);
}
int getMatch(Mat im1,vector <Mat> images)
{
	//Mat im1=imread("./test/17.png");	
	
	Mat blim1=getImageBlurred1(im1);
	//imshow("blim1",blim1);
	//waitKey(0);
	double minDist=1e18,distance,minIndex;
	for(int i=0;i<images.size();i++)
	{
		Mat blim2=getImageBlurred(images[i]);
		distance=getDistance(blim1,blim2);
		if(distance<minDist)
		{
			minIndex=i;
			minDist=distance;
		}
		//cout<<i<<"\t"<<distance<<endl;		
	}
	//cout<<"\n"<<minIndex<<endl;
	//imshow("blim1",blim1);
	//imshow("blim2",blim2);
	//	waitKey(0);
	return minIndex;
}
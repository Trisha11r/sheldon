#include <bits/stdc++.h>
#include "opencv2/opencv.hpp"
#define HMAX 180
#define SMAX 255
#define VMAX 255
using namespace cv;

int hslider;
int sslider;
int vslider;

int main()
{
	VideoCapture cap(1);
	if(!cap.isOpened())
	{
		return -1;
	}
	Mat edges;
	namedWindow("camera",1);
	namedWindow("original",1);
	char hbarname[50];
	char sbarname[50];
	char vbarname[50];
	sprintf(hbarname,"H: x %d",hslider);
	sprintf(sbarname,"S: x %d",sslider);
	sprintf(vbarname,"V: x %d",vslider);


	createTrackbar( hbarname, "camera", &hslider, HMAX, NULL);
	createTrackbar( sbarname, "camera", &sslider, SMAX, NULL);
	createTrackbar( vbarname, "camera", &vslider, VMAX, NULL);
		

	while(true)
	{
		Mat frame;
		cap>>frame;
		cvtColor(frame,edges,CV_BGR2HSV);
		GaussianBlur(edges,edges,Size(7,7),1.5,1.5);
		Mat threshold;
		//inRange(edges, Scalar(40,50,60), Scalar(45,90,100), threshold );

		


		inRange(edges, Scalar(hslider-10,sslider-30,vslider-30), Scalar(hslider+30,sslider+30,vslider+30), threshold );		

		//Canny(edges,edges,0,30,3);
		imshow("camera",threshold);
		imshow("original",edges);

		
		if(waitKey(30)>=30)
		{
			break;
		}		
	}
	return 0;
}

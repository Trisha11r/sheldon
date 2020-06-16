#include "opencv2/opencv.hpp"
using namespace cv;

//call this function once for the pink and once for the orange part separately to get the values
// @params: ht,st and vt will initially be calculated and used throughout the run, and accordingly supplied
int botpos(Mat img,float &x,float &y,int ht,int st,int vt,int f)
{
	Mat hsv;
	cvtColor(img,hsv,CV_BGR2HSV); //obtained hsv image
	//imshow("img",img);
	//imshow("hsv",hsv);
	//waitKey(0);
	Mat thresh;
	//inRange(hsv,Scalar(ht-30,st-30,vt-30),Scalar(ht+30,st+30,vt+30),thresh); //obtained binarised image
	thresh=Mat(img.rows,img.cols,CV_8UC1);
	Vec3b pixel;
    uchar black,white,pix;
    black=0;
    white=255;
    int i,j;
    for(i=0;i<hsv.rows;i++)
    {
        for(j=0;j<hsv.cols;j++)
        {
            pixel=hsv.at<Vec3b>(i,j);
            if(f)
            {
            	if((pixel.val[0]>100&&pixel.val[0]<120)&&(pixel.val[1]>100&&pixel.val[1]<120)&&(pixel.val[2]>200&&pixel.val[2]<256))
	                thresh.at<uchar>(i,j)=white;
	            else
	                thresh.at<uchar>(i,j)=black;	
            }
            else
            {
            	if((pixel.val[0]>70&&pixel.val[0]<85)&&(pixel.val[1]>80&&pixel.val[1]<105)&&(pixel.val[2]>180&&pixel.val[2]<256))
	                thresh.at<uchar>(i,j)=white;
	            else
	                thresh.at<uchar>(i,j)=black;		
            }            
        }   
    }
    int erosion_size1=1;
    Mat element1 = getStructuringElement( MORPH_RECT,Size( 2*erosion_size1 + 1, 2*erosion_size1+1 ), Point( erosion_size1, erosion_size1 ) );

    for(i=0;i<10;i++)
    dilate(thresh,thresh,element1);
    //imshow("img",img);
    //imshow("thresh",thresh);
	//imshow("thresh",thresh);
	
	Mat canny_output;
    int threshold=100;
    vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Canny(thresh, canny_output, threshold, threshold*2, 3);
	findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE); //returns the blobs as set of centers and radius

	Point2f c;
	float r;
	if(contours.size()==0)
	{
		cout<<"-1"<<endl;
		imshow("hsv",hsv);
		waitKey(0);
		return -1;
	}
	//else if(contours.size()==0)
	//	return -1;
	int max=0,index=0;
	for(i=0;i<contours.size();i++)
	{
		if(contourArea(contours[i])>max)
		{
			index=i;
			max=contourArea(contours[i]);
		}
	}
	minEnclosingCircle( contours[index], c, r);
	//circle(thresh,c,r,Scalar(0,255,255),5);
 	//imshow("thresh1",thresh);
	//waitKey(0);
    
	x = c.x;
	y = c.y;

	return 0;

}
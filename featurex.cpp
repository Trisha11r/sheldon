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


struct features
{
	Point2f coor;
	double val[18]; 
};
void displayPoints(vector <Point2f> points,int rows,int cols)
{
	Mat drawing = Mat::zeros( rows,cols, CV_8UC3 );
	for( int i = 0; i< points.size(); i++ )
	{
		Scalar color = Scalar( 0, 0, 255 );
		circle( drawing, points[i], 1, color, 1, 1, 0 );
	}
	imshow("drawing",drawing);
	waitKey(0);
}
double dist(Point2f a,Point2f b)
{
	double temp;
	temp=(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
	temp=sqrt(temp);
	return temp;
}
vector <features> featureEx(vector <Point2f> points)
{
	int temp,i,j;
	double distance,direc;
	vector <features> feature(points.size());		
	for(i=0;i<points.size();i++)
	{
		temp=i;
		feature[i].coor=points[i];
		for(j=0;j<points.size();j++)
		{
			if(j!=temp)
			{
				distance=dist(points[temp],points[j]);
				direc=atan2(points[temp].y-points[j].y, points[temp].x-points[j].x)*180/PI;
				if(direc<0)
				{
					direc+=360;
				}
				if(distance!=0)
				feature[i].val[int(direc/20)]=distance;
			}
			
		}
		double sum=0;
		for(j=0;j<18;j++)
		{
			sum=sum+feature[i].val[j]*feature[i].val[j];
		}
		for(j=0;j<18;j++)
		{
			feature[i].val[j]/=sqrt(sum);
		}
	}	
	return feature;
}
double calSim(double val1[], double val2[])
{
	double temp=0.00;
	int i;
	for(i=0;i<18;i++)
	{
		//if(!(val1[i]==0&&val2[i]==0))
		temp+=(val1[i]-val2[i])*(val1[i]-val2[i])/(val1[i]+val2[i]+1);
	}
	return temp/2;
}
vector <Point2f> reducePoints(vector <Point2f> points)
{
	int i;
	int inc=points.size()/200;
	vector <Point2f> res;
	for(i=0;i<points.size();i+=inc)
		res.push_back(points[i]);
	cout<<"\t"<<res.size()<<endl;
	return res;
}
vector < vector<features> > dictGenerator(vector < vector <Point2f> > input)
{
	int i;
	vector < vector<features> > featureVector(input.size());
	for(i=0;i<input.size();i++)
	{
		input[i]=reducePoints(input[i]);
		if(i==1)
		displayPoints(input[i],400,400);
		featureVector[i]=featureEx(input[i]);		
	}
	return featureVector;
}

int matchFunc(vector< vector <features> > dictImages, vector <features> currImage)
{
	int * freq=new int[dictImages.size()];
	memset(freq,0,sizeof(int)*dictImages.size());
	int i,j,k,minJ,maxIndex,count;
	double sim,minSim;
	for(i=0;i<currImage.size();i++)
	{
		minSim=1e18;		
		//count=0
		for(j=0;j<dictImages.size();j++)
		{
			for (k=0; k<dictImages[j].size(); k++)
			{
				sim=calSim(currImage[i].val,dictImages[j][k].val);
				if(sim<minSim)
				{
					minSim=sim;
					minJ=j;
				}
			}
		}
		//if(minJ==02)
		//cout<<minSim<<endl;
		//if(minSim<0.01)
		//if(count==0)
		cout<<"\t"<<minJ<<" "<<minSim<<endl;
		freq[minJ]++;					
	}
	//cout<<"ok1"<<endl;
	int maxFreq=0;
	for(i=0;i<dictImages.size();i++)
	{
		if(freq[i]>maxFreq)
		{
			maxFreq=freq[i];
			maxIndex=i;
		}
		cout<<i<<" "<<(freq[i]*100.0)/(double)currImage.size()<<endl;
	}
	return maxIndex;
}
vector <Mat> readImages()
{
	vector<Mat> images;
	vector<String> filenames; // notice here that we are using the Opencv's embedded "String" class
    String folder = "/home/dutta42120201/SHELDON/images"; // again we are using the Opencv's embedded "String" class

    glob(folder, filenames); // new function that does the job ;-)

    for(size_t i = 0; i < filenames.size(); ++i)
    {
        Mat src = imread(filenames[i]);
        //cout<<filenames[i]<<endl;
        if(!src.data)
            cerr << "Problem loading image!!!" << endl;
        Mat desi=Mat(400,400,CV_8UC3);
        Mat gray,bwim;
        resize(src,desi,desi.size());
        cvtColor(desi,gray,CV_BGR2GRAY);  
        threshold(gray, bwim, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	      
        //imshow(filenames[i],desi);
        /* do whatever you want with your images here */
        images.push_back(gray);
    }
    //waitKey(0);
    return images;
}
void rotate(cv::Mat& src, double angle, cv::Mat& dst)
{
    int len = std::max(src.cols, src.rows);
    cv::Point2f pt(len/2., len/2.);
    cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);

    cv::warpAffine(src, dst, r, cv::Size(len, len));
}
vector < vector <Point2f> > getPoints(vector <Mat> images)
{
	vector < vector <Point2f> >points;
	int i,j,k;
	for(i=0;i<images.size();i++)
	{
		vector <Point2f> allPoints;
		Mat canny_output;
	    int thresh=100;
	    vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		Canny(images[i], canny_output, thresh, thresh*2, 3);
		findContours(canny_output, contours, hierarchy, cv::RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0) );
		for(j=0;j<contours.size();j++)
			for(k=0;k<contours[j].size();k++)
				allPoints.push_back(contours[j][k]);
		points.push_back(allPoints);
		//cout<<"\t"<<(int)allPoints.size()<<endl;		
	} 	

	return points;
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
	return point;
}

int main()
{
	vector <Mat> images = readImages();
	vector < vector <Point2f> > points = getPoints(images);
	//getchar();
	cout<<"ok"<<endl;
	vector < vector <features> > dict = dictGenerator(points);
	cout<<"ok1"<<endl;
	Mat im=imread("./images/01.png");
	Mat im1=Mat(400,400,CV_8UC3);
	resize(im,im1,im1.size());
	Mat im2,bwim;
	cvtColor(im1,im2,CV_BGR2GRAY);
	threshold(im2, bwim, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	//imshow("im2",bwim);
	//waitKey(0);
	
	vector <Point2f> curImagePoints = getPoint(bwim);
	cout<<"ok2"<<endl;
	vector <Point2f> reducedCurImagePoints = reducePoints(curImagePoints);
	displayPoints(reducedCurImagePoints,bwim.rows,bwim.cols);
	vector <features> curImageFeature = featureEx(reducedCurImagePoints);
    cout<<"ok2"<<endl;
    cout<<matchFunc(dict,curImageFeature)<<endl;
	return 0;
}
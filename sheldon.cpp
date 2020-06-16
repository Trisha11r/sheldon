#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
#include <unistd.h>
#include "fea.cpp"
#include "minfloat.cpp"
#include "botpos.cpp"
#define PI 3.14159265

using namespace std;
using namespace cv;
int counting=0;
RNG rng(12345);
int serialSend(int v,FILE * file)
{
	usleep(100*1000);
    fprintf(file, "%d\n",v);
	cout<<v<<endl;
	return 0;
}
double dist(Point2f p,Point2f q)
{
	return sqrt((p.x-q.x)*(p.x-q.x)+(p.y-q.y)*(p.y-q.y));
}
int getBotCoordinates(Mat im,Point2f &botHead,Point2f &botTail)
{
	/*counting++;
	if(counting==20)
	{
		Mat hsv;
		cvtColor(im,hsv,CV_BGR2HSV); //obtained hsv image
		imshow("im",im);
		imshow("hsv",hsv);
		waitKey(0);		
	}*/
	if(botpos(im,botHead.x,botHead.y,90,60,200,1)==-1)
		return 0;
	cout<<"HEAD: "<<botHead.x<<" "<<botHead.y<<endl;
	if(botpos(im,botTail.x,botTail.y,160,60,200,0)==-1)
		return 0;
	cout<<"Tail: "<<botTail.x<<" "<<botTail.y<<endl;
	
	if(dist(botHead,botTail)>120)
	{
		/*Mat hsv;
		cvtColor(im,hsv,CV_BGR2HSV); //obtained hsv image
		//imshow("im",im);
		imshow("hsv",hsv);
		waitKey(0);		*/
		return 0;
	}
	/*else
	{
		if(botpos(im,botHead.x,botHead.y,90,60,200,1)==-1)
			return 0;
	}*/
	return 1;
}

void onTheMove(vector <Point2f> orderedCoordinates,VideoCapture capture)
{	
	FILE * file = fopen("/dev/ttyACM0","w");  //Opening device file
    usleep(1000*1000);
    Mat ima;
    //for(int i=0;i<10;i++)
	//		capture>>ima;
	Point2f botHead,botTail,bot;
	double direc,direcTarget;
	int * flag = new int [orderedCoordinates.size()];
	memset(flag,0,sizeof(int)*orderedCoordinates.size());
	int currTarget=0;
	while(currTarget<orderedCoordinates.size())
	{
		cout<<"**********************"<<endl;
		cout<<"\t\t\t\t"<<currTarget<<endl;
		cout<<"**********************"<<endl;
		//getchar();
		Mat im;
		//for(int i=0;i<5;i++)
			capture>>im;
		if(!getBotCoordinates(im,botHead,botTail))
			continue;
		bot.x=(botTail.x+botHead.x)/2;
		bot.y=(botTail.y+botHead.y)/2;
		
		if(dist(bot,orderedCoordinates[currTarget])<50)
		{
			//glow led
			serialSend(3,file);				
			serialSend(4,file);				
			currTarget++;
			continue;
		}
		direc=atan2(-(botHead.y-botTail.y),botHead.x-botTail.x)/PI*180.0;
		if(direc<0)
		{
			direc+=360;
		}
		direcTarget=atan2(-(orderedCoordinates[currTarget].y-bot.y),orderedCoordinates[currTarget].x-bot.x)/PI*180.0;
		if(direcTarget<0)
		{
			direcTarget+=360;
		}		
		cout<<direc<<" "<<direcTarget<<endl;
		if(direc>direcTarget)
		{
			if(direc - direcTarget<10)
			{
				//straight
				cout<<"straight"<<endl;
				serialSend(0,file);
			}
			else if(direc - direcTarget<180)
			{
				cout<<"right"<<endl;
				//right - turn
				serialSend(2,file);				
			}
			else
			{
				cout<<"left"<<endl;
				//left - turn
				serialSend(1,file);				
			}
		}
		else
		{
			if(direcTarget - direc<10)
			{
				cout<<"straight"<<endl;
				//straight	
				serialSend(0,file);			
			}
			else if(direcTarget - direc<180)
			{
				cout<<"left"<<endl;
				//left - turn
				serialSend(1,file);				
			}
			else
			{
				cout<<"right"<<endl;
				//right - turn	
				serialSend(2,file);				
			}
		}
	}	
	serialSend(3,file);				
	fclose(file);
}
int main()
{
	VideoCapture capture(1);
	if(!capture.isOpened())
	{
		return -1;
	}
	usleep(1000000);
	Mat im;
	capture>>im;
	//Mat im =imread("t7.jpg",1);
	//imshow("im",im);
	//waitKey(0);
	Mat gray;
	cvtColor(im,gray,CV_BGR2GRAY);
	Mat hsv,bwim;
	cvtColor(im,hsv,CV_BGR2HSV);
	//imshow("hsv",hsv);
	bwim=Mat(im.rows,im.cols,CV_8UC1);
	Vec3b pixel;
    uchar black,white,pix;
    black=0;
    white=255;
    int i,j;
    for(i=0;i<im.rows;i++)
    {
        for(j=0;j<im.cols;j++)
        {
            pixel=im.at<Vec3b>(i,j);
            if(pixel.val[0]>200&&pixel.val[1]>200&&pixel.val[2]>200)
                bwim.at<uchar>(i,j)=white;
            else
                bwim.at<uchar>(i,j)=black;
        }   
    }
    //imshow("gray",gray);
    //imshow("bwim",bwim);
    //waitKey(0);
	int erosion_size1=1;
    Mat element1 = getStructuringElement( MORPH_RECT,Size( 2*erosion_size1 + 1, 2*erosion_size1+1 ), Point( erosion_size1, erosion_size1 ) );

    for(i=0;i<2;i++)
    	erode(bwim,bwim,element1);
    for(i=0;i<5;i++)
    	dilate(bwim,bwim,element1);
    //floodFill(bwim, cv::Point(0,0), Scalar(255));
    //bitwise_not(bwim,bwim);
   // for(i=0;i<5;i++)
    //	erode(bwim,bwim,element1);
    //for(i=0;i<2;i++)
    //	dilate(bwim,bwim,element1);
   	Mat canny_output;
    int thresh=100;
    vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Canny(bwim, canny_output, thresh, thresh*2, 3);
	findContours( canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	//imshow("bwim",bwim);
	/// Approximate contours to polygons + get bounding rects and circles
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );
	vector<Point2f>center( contours.size() );
	vector<float>radius( contours.size() );

	for( int i = 0; i < contours.size(); i++ )
	{ 
		approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );
		//minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
	}


	/// Draw polygonal contour + bonding rects + circles
	Mat drawing = Mat::zeros( bwim.size(), CV_8UC3 );
	for( int i = 0; i< contours.size(); i++ )
	{
		Scalar color = Scalar( 255, 255, 255 );
		//drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
		rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
		//circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
	}
	//imshow("drawing",drawing);
	waitKey(0);
	vector <Mat> images=readImages();
	int operators[4],operands[10],operandsCount=0,operatorsCount=0;
	vector < vector <Point2f> >operatorsCoor(4);
	vector < vector <Point2f> >operandsCoor(10);	
	memset(operators,0,sizeof(int)*4);
	memset(operands,0,sizeof(int)*10);
	cout<<"DECTECTING CHARACTERS..."<<endl;
	for(int i=0;i<boundRect.size();i++)
	{
		if(boundRect[i].width*boundRect[i].height<4000)
			continue;
		Mat im1=im(Rect(boundRect[i].x+10,boundRect[i].y+10,boundRect[i].width-20,boundRect[i].height-20));
		//imshow("im1",im1);
		//waitKey(0);

		int index= getMatch(im1,images);	
		cout<<index<<endl;
		if(index>=10)
		{
			operatorsCount++;
			operators[index-10]++;
			operatorsCoor[index-10].push_back(Point2f(boundRect[i].x+boundRect[i].width/2,boundRect[i].y+boundRect[i].height/2));
			//cout<<operatorsCoor[operatorsCoor.size()-1].x<<" "<<operatorsCoor[operatorsCoor.size()-1].y<<endl;
		}
		else
		{
			operandsCount++;
			operands[index]++;
			operandsCoor[index].push_back(Point2f(boundRect[i].x+boundRect[i].width/2,boundRect[i].y+boundRect[i].height/2));
			//cout<<operandsCoor[operandsCoor.size()-1].x<<" "<<operandsCoor[operandsCoor.size()-1].y<<endl;
		}
		
		
	}
	minval=INT_MAX;
	char * tempOrder = new char[operandsCount+operatorsCount];
	vector <int> order(operandsCount+operatorsCount); 
	cout<<"GENERATING EXPRESSION..."<<endl;
	minimisation(operands,operators,0,operandsCount,operatorsCount,operatorsCount+operandsCount,tempOrder);

	for(int i=0;i<operatorsCount+operandsCount;i++)
	{
		cout<<min1[i];
		if(min1[i]>='0'&&min1[i]<='9')
			order[i]=min1[i]-'0';
		else if(min1[i]=='+')
			order[i]=10;
		else if(min1[i]=='-')
			order[i]=11;
		else if(min1[i]=='*')
			order[i]=12;
		else if(min1[i]=='/')
			order[i]=13;
	}
	cout<<endl;
	vector <Point2f> orderedCoordinates;
	for(int i=0;i<order.size();i++)
	{
		//cout<<order[i]<<endl;
		if(order[i]>=10)
		{
			orderedCoordinates.push_back(operatorsCoor[order[i]-10][operatorsCoor[order[i]-10].size()-1]);
			operatorsCoor[order[i]-10].pop_back();
		}
		else
		{
			orderedCoordinates.push_back(operandsCoor[order[i]][operandsCoor[order[i]].size()-1]);
			operandsCoor[order[i]].pop_back();	
		}
	}
	cout<<"ORDERED COORDINATES..."<<endl;
	for(int i=0;i<orderedCoordinates.size();i++)
	{
		cout<<"("<<orderedCoordinates[i].x<<","<<orderedCoordinates[i].y<<")"<<endl;
	}
	//getchar();
	onTheMove(orderedCoordinates,capture);
	return 0;
}
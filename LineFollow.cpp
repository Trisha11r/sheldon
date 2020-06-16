#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

#include <unistd.h>
//#include <serial/serial.h>

using namespace std;
using namespace cv;

int counter = 0;
int column ;
bool flag=true;
int initCamera(int id,CvCapture* &capture)
{
	//CvCapture* capture = NULL;   
	capture = cvCaptureFromCAM(id);
    if( !capture )
    {
        cout << "No camera detected" << endl;
        return 0;
    }  
    //sleep(1);  
	return 1;
}
Mat getImage(CvCapture* &capture)
{
	Mat im=cvQueryFrame( capture );
	return im;
}
int binarizeAndFindNextMovement(Mat im)
{
	Mat hsv,lines;
	lines=Mat(im.rows,im.cols,CV_8UC1);
	Vec3b pixel;
	uchar black,white;
	black=0;
	white=255;
	int i,j;
	cvtColor(im,hsv,CV_BGR2HSV);
	//imshow("hsv",hsv);
	for(i=0;i<hsv.rows;i++)
	{
		for(j=0;j<hsv.cols;j++)
		{
			pixel=hsv.at<Vec3b>(i,j);
			if(pixel.val[2]>230&&pixel.val[1]<10)
				lines.at<uchar>(i,j)=white;
			else
				lines.at<uchar>(i,j)=black;
		}	
	} 
	//imshow("lines",lines);

	int erosion_size=3;
	Mat element = getStructuringElement( MORPH_RECT,Size( 2*erosion_size + 1, 2*erosion_size+1 ), Point( erosion_size, erosion_size ) );
	
	Mat bwim=lines;
	for(i=0;i<2;i++)
  	erode( bwim, bwim, element );
  	dilate( bwim, bwim, element );

  	//imshow("result",bwim);
  	//IplImage tmp=bwim;
	
  	//cvShowImage( "result", &tmp);
//waitKey(0);


  	Mat canny_output; //example from OpenCV Tutorial
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	int thresh=100;
	Canny(bwim, canny_output, thresh, thresh*2, 3);//with or without, explained later.
	findContours(bwim, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));

	//printf("%d\n",contours.size()  );
	vector<Moments> mu(contours.size() );
	for( int i = 0; i < contours.size(); i++ )
	 { mu[i] = moments( contours[i], false ); }

	///  Get the mass centers:
	vector<Point2f> mc( contours.size() );
	for( int i = 0; i < contours.size(); i++ )
	 { mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }

	/// Draw contours
	
	Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
	for( int i = 0; i< contours.size(); i++ )
	{
		Scalar color = Scalar(0,255,0);
		drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
		circle( drawing, mc[i], 4, color, -1, 8, 0 );
		//circle( drawing, mc[i], 20, color);
		//printf("%f %f\n",mc[i].x,mc[i].y );
	}

	//imshow("result",drawing);
	//waitKey(0);
	

	Point2f avg_mc;
	avg_mc.x=0;
	avg_mc.y=0;
	for( int i = 0; i < contours.size(); i++ )
	{
		avg_mc.x+=mc[i].x;
		avg_mc.y+=mc[i].y;
	}
	avg_mc.x=avg_mc.x/contours.size();
	avg_mc.y=avg_mc.y/contours.size();
	cout<<avg_mc.x<<" "<<avg_mc.y<<endl;
	if(avg_mc.y>330&&flag)
	{
		flag=false;
		counter++;
		cout<<"\n\nUPDATED\n\n"<<counter<<" "<<column<<endl;
	}
	else if(avg_mc.y<330)
	{
		flag=true;
	}
	if(avg_mc.x<280)
		return 1;//LEFT
	else if(avg_mc.x>360)
		return 2;//RIGHT
	else
		return 0;//STRAIGHT
}
int serialSend(int v,FILE * file)
{
	usleep(100*1000);
    //for(int i=0;i<10;i++)
	fprintf(file, "%d\n",v);
	cout<<v<<endl;
		
	//usleep(500*1000);   
    return 0;
}
int main(int argc,char *argv[])
{
	if(argc!=2)
		exit(1);
	sscanf(argv[1],"%d",&column);
	CvCapture* cap;
	Mat im;
	int move,f;
	FILE * file = fopen("/dev/ttyACM0","w");  //Opening device file
    usleep(1000*1000);
    
	//Serial arduino("/dev/ttyACM1",9600,Timeout::simpleTimeout(1000));
	cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
    do
	{
		f=0;
		f=initCamera(1,cap);
		while(counter<=column)
		{
			im=getImage(cap);	
			move=binarizeAndFindNextMovement(im);		
			//cout<<move<<endl;
			//getchar();
			//waitKey(1);
			//getchar();
			serialSend(move,file);	
		}	
	}while(f==0);	
	printf("DONE!!\n");
	serialSend(5,file);
	fclose(file);
}
#include <opencv2\opencv.hpp>
#include <math.h>
#include <fstream>
using namespace cv;
using namespace std;


int main(int argc, char* argv[])
{
	cv::Mat src, houghL, eqHist, corner;

	//HoughLines
	src = cv::imread(argv[1], 1);
	imshow("original1", src);
	cv::waitKey();

	cvtColor(src, src, cv::COLOR_BGR2GRAY);
	vector<Vec2f> lines;
	HoughLines(src, lines, 0.8, 0.01, 100 );
	houghL = Mat(src.rows,src.cols,src.type(),Scalar(0));
	for( size_t i = 0; i < lines.size(); i++ )
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		line( houghL, pt1, pt2, cv::Scalar(200));
	}
	imshow("houghLines", houghL);
	cv::waitKey();


	//equalizeHist
	src = cv::imread(argv[2], 1);
	imshow("original2", src);
	cv::waitKey();

	Mat grey;
    cvtColor(src, grey, COLOR_BGR2GRAY);
	eqHist = Mat(src);
	equalizeHist(grey,eqHist);
	imshow("equalizeHist", eqHist);
	cv::waitKey();


	//goodFeatureToTrack
	src = cv::imread(argv[3], 1);
	imshow("original3", src);
	cv::waitKey();

	Mat tmp;
	cvtColor(src,tmp,cv::COLOR_BGR2GRAY);
	vector<Point2f> corners;
	cv::goodFeaturesToTrack(tmp,corners,10000,0.01,10);
	corner = Mat(src);
	int r = 4;
	for( int i = 0; i < corners.size(); i++ )
		circle( corner, corners[i], r, Scalar(255), -1, 8, 0 );
	imshow("corners",corner);
	cv::waitKey();

	return 0;
}
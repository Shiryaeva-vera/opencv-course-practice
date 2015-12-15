#include <opencv2\opencv.hpp>
#include <math.h>
#include <fstream>
using namespace cv;

Mat integralBlur(Mat img, Mat dist)
{
	Mat blur = cv::Mat(img), integ;
	int H = img.rows;
	int W = img.cols;
	int x,y;
	Vec3i intensity1, intensity2, intensity3, intensity4;
	int D, min_x_D, min_y_D, max_x_D, max_y_D;
	int koef;
	Vec3i sum;

	cv::integral(img,integ);

	for (x = 0; x < H; x++)
		for (y = 0; y < W; y++)
        {
			D = dist.at<float>(x,y);
			D = max(1,D/2);

			min_x_D = max(0,x-D);
			min_y_D = max(0,y-D);
			max_x_D = min(H-1,x+D);
			max_y_D = min(W-1,y+D);

			intensity1 = integ.at<Vec3i>(max_x_D, max_y_D);
			intensity2 = integ.at<Vec3i>(min_x_D, min_y_D);
			intensity3 = integ.at<Vec3i>(max_x_D, min_y_D);
			intensity4 = integ.at<Vec3i>(min_x_D, max_y_D);
			sum = intensity1+intensity2-(intensity3+intensity4);

			koef = (max_x_D-min_x_D)*(max_y_D-min_y_D);
			sum = sum/koef;
            
			blur.at<Vec3b>(x,y) = sum;
        }
	return blur;
}

int main(int argc, char* argv[])
{
	cv::Mat img, edges, dist, blur;

	img = cv::imread(argv[1], 1);
	imshow("original", img);

	Canny(img, edges, 100, 200);
	imshow("canny", edges);
	subtract(Scalar::all(255),edges,edges);
	distanceTransform(edges, dist, cv::DIST_L1, 5);
	blur = integralBlur(img,dist);
	imshow("blur",blur);

	cv::waitKey();
	return 0;
}
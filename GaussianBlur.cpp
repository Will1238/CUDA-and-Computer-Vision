#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
	  
const char *PICFILE = "H:\\Pictures\\OpenCVTestPic\\lena512.bmp";

int main()
{
	Mat src = imread(PICFILE);
	Mat img;
	GaussianBlur(src, img, Size(0, 0), 1, 1);
    namedWindow("高斯滤波【原图】");
	namedWindow("高斯滤波【效果图】");
	imshow("高斯滤波【原图】", src);
	imshow("高斯滤波【效果图】", img);
	imwrite("H:\\Pictures\\OpenCVTestPic\\lenaGuss.bmp", img);
	waitKey(0);
	return 0;
}
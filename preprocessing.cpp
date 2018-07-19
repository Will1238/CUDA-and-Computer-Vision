#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

const char *PICFILE = "H:\\Pictures\\OpenCVTestPic\\lena512.bmp";
const double sigmaX = 2.0;
const double sigmaY = 2.0;

double generateGaussianNoise(double mu, double sigma)
{
	//定义一个特别小的值
	const double epsilon = numeric_limits<double>::min();//返回目标数据类型能表示的最逼近1的正数和1的差的绝对值
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	//flag为假，构造高斯随机变量
	if (!flag)
		return z1*sigma + mu;
	double u1, u2;
	//构造随机变量

	do
	{
		u1 = rand()*(1.0 / RAND_MAX);
		u2 = rand()*(1.0 / RAND_MAX);
	} while (u1 <= epsilon);
	//flag为真构造高斯随机变量X
	z0 = sqrt(-2.0*log(u1))*cos(2 * CV_PI * u2);
	z1 = sqrt(-2.0*log(u1))*sin(2 * CV_PI * u2);
	return z1*sigma + mu;
}

//为图像添加高斯噪声
Mat addGaussianNoise(Mat& srcImage)
{
	Mat resultImage = srcImage.clone();    //深拷贝,克隆
	int channels = resultImage.channels();    //获取图像的通道
	int nRows = resultImage.rows;    //图像的行数

	int nCols = resultImage.cols*channels;   //图像的总列数
											 //判断图像的连续性
	if (resultImage.isContinuous())    //判断矩阵是否连续，若连续，我们相当于只需要遍历一个一维数组 
	{
		nCols *= nRows;
		nRows = 1;
	}
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{	//添加高斯噪声
			int val = resultImage.ptr<uchar>(i)[j] + generateGaussianNoise(2, 0.8) * 32;
			if (val < 0)
				val = 0;
			if (val > 255)
				val = 255;
			resultImage.ptr<uchar>(i)[j] = (uchar)val;
		}
	}
	return resultImage;
}

int main(void) {
	Mat src = imread(PICFILE);
	Mat img;
	Mat GaussianNoise;
	GaussianBlur(src, img, Size(0, 0), sigmaX, sigmaY);
	GaussianNoise = addGaussianNoise(img);
	namedWindow("【原图】");
	namedWindow("高斯滤波【效果图】");
	namedWindow("高斯噪声【效果图】");
	imshow("【原图】", src);
	imshow("高斯滤波【效果图】", img);
	imshow("高斯噪声【效果图】", GaussianNoise);
	imwrite("H:\\Pictures\\OpenCVTestPic\\lenaGuss.bmp", GaussianNoise);
	waitKey(0);
	

	return 0;
}
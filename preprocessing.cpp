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
	//����һ���ر�С��ֵ
	const double epsilon = numeric_limits<double>::min();//����Ŀ�����������ܱ�ʾ����ƽ�1��������1�Ĳ�ľ���ֵ
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	//flagΪ�٣������˹�������
	if (!flag)
		return z1*sigma + mu;
	double u1, u2;
	//�����������

	do
	{
		u1 = rand()*(1.0 / RAND_MAX);
		u2 = rand()*(1.0 / RAND_MAX);
	} while (u1 <= epsilon);
	//flagΪ�湹���˹�������X
	z0 = sqrt(-2.0*log(u1))*cos(2 * CV_PI * u2);
	z1 = sqrt(-2.0*log(u1))*sin(2 * CV_PI * u2);
	return z1*sigma + mu;
}

//Ϊͼ����Ӹ�˹����
Mat addGaussianNoise(Mat& srcImage)
{
	Mat resultImage = srcImage.clone();    //���,��¡
	int channels = resultImage.channels();    //��ȡͼ���ͨ��
	int nRows = resultImage.rows;    //ͼ�������

	int nCols = resultImage.cols*channels;   //ͼ���������
											 //�ж�ͼ���������
	if (resultImage.isContinuous())    //�жϾ����Ƿ��������������������൱��ֻ��Ҫ����һ��һά���� 
	{
		nCols *= nRows;
		nRows = 1;
	}
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{	//��Ӹ�˹����
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
	namedWindow("��ԭͼ��");
	namedWindow("��˹�˲���Ч��ͼ��");
	namedWindow("��˹������Ч��ͼ��");
	imshow("��ԭͼ��", src);
	imshow("��˹�˲���Ч��ͼ��", img);
	imshow("��˹������Ч��ͼ��", GaussianNoise);
	imwrite("H:\\Pictures\\OpenCVTestPic\\lenaGuss.bmp", GaussianNoise);
	waitKey(0);
	

	return 0;
}
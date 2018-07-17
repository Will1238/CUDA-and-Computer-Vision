/**
 * 基于N = 2 的哈尔小波基 的小波变换函数
 * @Version 2018/07/17 10:00
 **/

#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
/*//演示部分
using namespace cv;

const char *PICFILE = "H:\\Pictures\\OpenCVTestPic\\lena512.bmp";

Mat waveletDecompose(const Mat &_src);
Mat WDT(const Mat &_src, const int _level);

 int main()
 {
     //必须使用灰度读取，否则通道不匹配
	 Mat src = imread(PICFILE,IMREAD_GRAYSCALE);	 
	 WDT(src, 3);
	 return 0;
  }
*/
 Mat WDT(const Mat &_src, const int _level)
 {
	 Mat src = Mat_<float>(_src);
	 Mat dst = Mat::zeros(src.rows, src.cols, src.type());

	 //小波变换
	 int t = 1;
	 int row = src.rows;
	 int col = src.cols;
	 while (t <= _level)
	 {
		 //先进行 行小波变换
		 for (int i = 0; i<row; i++)
		 {
			 //取出src中要处理的数据的一行
			 Mat oneRow = Mat::zeros(1, col, src.type());
			 for (int j = 0; j<col; j++)
			 {
				 oneRow.at<float>(0, j) = src.at<float>(i, j);
			 }
			 oneRow = waveletDecompose(oneRow);
			 for (int j = 0; j<col; j++)
			 {
				 dst.at<float>(i, j) = oneRow.at<float>(0, j);
			 }
		 }

		 //小波列变换
		 for (int j = 0; j<col; j++)
		 {
			 Mat oneCol = Mat::zeros(row, 1, src.type());
			 for (int i = 0; i<row; i++)
			 {
				 oneCol.at<float>(i, 0) = dst.at<float>(i, j);//dst,not src
			 }
			 oneCol = (waveletDecompose(oneCol.t())).t();
			 for (int i = 0; i<row; i++)
			 {
				 dst.at<float>(i, j) = oneCol.at<float>(i, 0);
			 }
		 }
         //【可删】显示部分
		 char s[10];
		 sprintf_s(s, 10, "%d", t);
		 imshow(s, dst);
		 waitKey();

		 //更新 
		 row /= 2;
		 col /= 2;
		 t++;
		 src = dst;
	 }
	 return dst;
 }
 
 //小波分解
 Mat waveletDecompose(const Mat &_src)
 {
	 //构造Haar小波（滤波器）
	 int N = 2;

	 //高通低通滤波器
	 Mat _lowFilter = Mat::zeros(1, N, CV_32F);
	 Mat _highFilter = Mat::zeros(1, N, CV_32F);
	 
	 _lowFilter.at<float>(0, 0) = 1 / sqrtf(N);
	 _lowFilter.at<float>(0, 1) = 1 / sqrtf(N);
	 
	 _highFilter.at<float>(0, 0) = -1 / sqrtf(N);
	 _highFilter.at<float>(0, 1) = 1 / sqrtf(N);

	 assert(_src.rows == 1 && _lowFilter.rows == 1 && _highFilter.rows == 1);
	 assert(_src.cols >= _lowFilter.cols && _src.cols >= _highFilter.cols);
	 Mat &src = Mat_<float>(_src);

	 int D = src.cols;

	 Mat &lowFilter = Mat_<float>(_lowFilter);
	 Mat &highFilter = Mat_<float>(_highFilter);

	 //频域滤波或时域卷积；ifft( fft(x) * fft(filter)) = cov(x,filter) 
	 Mat dst1 = Mat::zeros(1, D, src.type());
	 Mat dst2 = Mat::zeros(1, D, src.type());

	 filter2D(src, dst1, -1, lowFilter);
	 filter2D(src, dst2, -1, highFilter);

	 //下采样
	 Mat downDst1 = Mat::zeros(1, D / 2, src.type());
	 Mat downDst2 = Mat::zeros(1, D / 2, src.type());

	 resize(dst1, downDst1, downDst1.size());
	 resize(dst2, downDst2, downDst2.size());

	 //数据拼接
	 for (int i = 0; i<D / 2; i++)
	 {
		 src.at<float>(0, i) = downDst1.at<float>(0, i);
		 src.at<float>(0, i + D / 2) = downDst2.at<float>(0, i);

	 }
	 return src;
 }
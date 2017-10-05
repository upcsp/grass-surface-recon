#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "funcs.hpp"


int main(int argc, char* argv[]){
	const char* filename1 = "test_images/test2_1.jpg";
	const char* filename2 = "test_images/test2_2.jpg";

	cv::Mat I1 = cv::imread(filename1, cv::IMREAD_GRAYSCALE);
	int size=2500;
	cv::Rect r={I1.cols/2-size/2,I1.rows/2-size/2,size,size};
	cv::Mat mg1= I1(r);
	cv::Mat f1=fourierTrans(mg1);
	cv::Mat p1=polarTrans(f1);

	cv::waitKey();

	cv::Mat I2 = cv::imread(filename2, cv::IMREAD_GRAYSCALE);
	cv::Mat mg2= I2(r);
	cv::Mat f2=fourierTrans(mg2);
	cv::Mat p2=polarTrans(f2);
	
	cv::Point2d point=phaseCorr(p1, p2);
	std::cout<<point<<std::endl;
	cv::waitKey();
}

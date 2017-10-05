#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "funcs.hpp"


int main(int argc, char* argv[]){
	const char* filename1 = "test_images/test1_1.jpg";
	const char* filename2 = "test_images/test1_2.jpg";

	cv::Mat I1 = cv::imread(filename1, cv::IMREAD_GRAYSCALE);
	int sizeA=2500;
	cv::Rect rA={I1.cols/2-sizeA/2,I1.rows/2-sizeA/2,sizeA,sizeA};
	cv::Mat mg1= I1(rA);
	cv::Mat f1=fourierTrans(mg1);
	int sizeB=sizeA/4;
	cv::Rect rB={f1.cols/2-sizeB/2,f1.rows/2-sizeB/2,sizeB,sizeB};
	cv::Mat p1=polarTrans(f1(rB));
	int sizeC=sizeB/2;
	cv::Rect rC={0,0,sizeB,sizeC};

	cv::waitKey();

	cv::Mat I2 = cv::imread(filename2, cv::IMREAD_GRAYSCALE);
	cv::Mat mg2= I2(rA);
	cv::Mat f2=fourierTrans(mg2);
	cv::Mat p2=polarTrans(f2(rB));
	
	cv::Point2d point=phaseCorr(p1(rC), p2(rC));
	std::cout<<point<<std::endl;
	std::cout<<"Angle: "<<360*point.y/sizeB<<std::endl;
	cv::waitKey();
}

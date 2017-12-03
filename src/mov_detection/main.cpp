#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "disp.hpp"

int main(int argc, char* argv[]){

	const char* filename1 = "test_images/test1_1.jpg";
	const char* filename2 = "test_images/test1_2.jpg";

	cv::Mat prev = cv::imread(filename1, cv::IMREAD_GRAYSCALE);
	cv::Mat curr = cv::imread(filename2, cv::IMREAD_GRAYSCALE);
	//cv::resize(prev,prev,{200,200});
	//cv::resize(curr,curr,{200,200});
	int sizeA=std::min(prev.cols,prev.rows)*0.8;
	sizeA=sizeA-sizeA%4;
	int sizeB=sizeA/2;
	int sizeC=sizeB/1;

	std::cout<<"sizeA "<<sizeA<<" sizeB "<<sizeB<<" sizeC "<<sizeC<<std::endl;
	cv::Rect rA={prev.cols/2-sizeA/2,prev.rows/2-sizeA/2,sizeA,sizeA};

	resizePrint("prev",prev(rA));
	resizePrint("curr",curr(rA));
	cv::Point2d point=getAngle(prev(rA), curr(rA),sizeB,sizeC);
	std::cout<<point<<std::endl;
	float angle=360.0f*point.y/sizeA;
	std::cout<<"Angle: "<<angle<<" deg"<<std::endl;

	cv::waitKey();

	cv::Mat rotated= rotate(curr, angle);


	cv::Mat n1=rotated(rA),
			n2=prev(rA);

	resizePrint("prev 2"   ,n2);
	resizePrint("curr rot" ,n1);
	n1.convertTo(n1,CV_32FC1);
	n2.convertTo(n2,CV_32FC1);
	cv::Point2d offset = cv::phaseCorrelate(n1,n2);

	std::cout<<offset<<" pixels"<<std::endl;
	cv::waitKey();
}

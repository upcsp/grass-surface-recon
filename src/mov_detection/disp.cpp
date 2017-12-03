#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "disp.hpp"

cv::Mat fourierTrans(const cv::Mat& I){

	cv::Mat padded;
	int m = cv::getOptimalDFTSize( I.rows );
	int n = cv::getOptimalDFTSize( I.cols );
	cv::copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

	cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)};
	cv::Mat complexI;
	merge(planes, 2, complexI);

	dft(complexI, complexI);

	split(complexI, planes);
	magnitude(planes[0], planes[1], planes[0]);
	cv::Mat magI = planes[0];

	magI += cv::Scalar::all(1);
	cv::log(magI, magI);

	magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));
	int cx = magI.cols/2;
	int cy = magI.rows/2;

	resizePrint("prefourier",magI);
	cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));
	cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));
	cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));
	cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy));

	cv::Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);


	return magI;
}

cv::Mat polarTrans(const cv::Mat& I){

	cv::Mat ret;

	int x=I.cols;
	int y=I.rows;
	cv::Point center(0.5*x,0.5*y);
	float radius=x<y?0.5*x:0.5*y;
	cv::linearPolar(I,ret,center,radius,cv::INTER_CUBIC);
	return ret;
}

void resizePrint(std::string title,const cv::Mat& m){
	cv::Mat printMat;
	cv::normalize(m, printMat, 255, 0, CV_MINMAX,CV_8UC1);
	cv::resize(printMat,printMat,{1000,1000});
	//cv::resize(m,printMat,{500,500});
	cv::imshow(title, printMat);
}

cv::Mat rotate(const cv::Mat& m1, double angle){//Around centerpoint
	cv::Point center= cv::Point(m1.cols/2,m1.rows/2);

	cv::Mat rotmat=cv::getRotationMatrix2D(center,angle,1.0);

	cv::Mat r;
	cv::warpAffine(m1,r,rotmat,{m1.cols,m1.rows});

	return r;
}

cv::Point2d getAngle(const cv::Mat& m1, const cv::Mat& m2, int fd,int pd){
	cv::Mat fp = fourierTrans(m1);
	cv::Mat fc = fourierTrans(m2);

	cv::Rect rf={fp.cols/2-fd/2,fp.rows/2-fd/2,fd,fd};
	resizePrint("fp(rec)",fp(rf));
	resizePrint("fp",fp);
	//resizePrint("fc(rec)",fc(rf));
	cv::Mat pp = polarTrans(fp(rf));
	cv::Mat pc = polarTrans(fc(rf));

	cv::Rect rp={0,0,pd,pp.rows};
	resizePrint("pp(rec)",pp(rp));
	resizePrint("pc(rec)",pc(rp));
	pp.convertTo(pp,CV_32FC1);
	pc.convertTo(pc,CV_32FC1);
	return cv::phaseCorrelate(pp(rp),pc(rp));

}


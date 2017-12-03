#include <opencv2/imgproc/imgproc.hpp>

cv::Mat fourierTrans(const cv::Mat& m);

cv::Mat polarTrans(const cv::Mat& m);

void resizePrint(std::string title,const cv::Mat& m);

cv::Mat rotate(const cv::Mat& m1, double angle);

cv::Point2d getAngle(const cv::Mat& m1, const cv::Mat& m2, int fd,int pd);

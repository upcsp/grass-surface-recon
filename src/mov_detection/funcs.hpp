#include <opencv2/imgproc/imgproc.hpp>

cv::Mat fourierTrans(cv::Mat I);

cv::Mat polarTrans(const cv::Mat& I);

cv::Point2d phaseCorr(const cv::Mat& m1, const cv::Mat& m2);

cv::Mat rotate(const cv::Mat& m1, double angle);

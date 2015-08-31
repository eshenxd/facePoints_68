#ifndef _FACEALIGNMENT_H_
#define _FACEALIGNMENT_H_

#include "header.h"

class FaceAlign
{
private:
	int width, height;

	float angle;

	std::vector<CvPoint>KeyPoint;
	std::vector<cv::Point2f>FinalKPoints;

	cv::Mat inPutimage;
	IplImage* alignImage;
	IplImage* grayImage;
	cv::Mat rotaimage;
	//IplImage* alignImage;
	cv::Mat alignimg;

	cv::Mat faceWarpandRotation(cv::Point2f src[3] , cv::Mat);

	cv::Point2f point_transform(CvPoint , CvPoint);

public:
	FaceAlign(int _width = 80, int _height = 90);
	
	~FaceAlign();
	
	void runFaceAlignment(cv::Mat _inPutImage,std::vector<CvPoint>_KeyPoints);

	cv::Mat getFaceAlignimg();//获取对齐后的人脸图片
	
	void getFaceAlignPos(std::vector<cv::Point2f>&Final_KeyPoints);//获取对齐后的人脸landmark
};

#endif
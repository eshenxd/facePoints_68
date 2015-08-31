#include "facealignment.h"


using namespace cv;
using namespace std;


FaceAlign::FaceAlign(int _width, int _height) :width(_width), height(_height)
{
	alignImage = cvCreateImage(cvSize(width, height), 8, 3);
}

FaceAlign::~FaceAlign()
{
	cvReleaseImage(&alignImage);
}

Mat FaceAlign::faceWarpandRotation(cv::Point2f srcTri[3], cv::Mat inPut)
{
	Mat src, warp_dst;
	src = inPut;

	CvMat* map = cvCreateMat(2, 3, CV_32FC1);

	Point2f left_point, right_point;
	left_point = srcTri[0];
	right_point = srcTri[1];

	Point2f rota_point = srcTri[2];

	float xDis, yDis;
	xDis = right_point.x - left_point.x;
	yDis = right_point.y - left_point.y;

	float m_angle = cvFastArctan(yDis, xDis);
	angle = m_angle*CV_PI / 180;
	cv2DRotationMatrix(cvPoint2D32f(rota_point.x, rota_point.y), m_angle, 1, map);
	warpAffine(src, warp_dst, Mat(map), src.size());

	return warp_dst;
}

void FaceAlign::runFaceAlignment(Mat _inPutImage,vector<CvPoint>_KeyPoints)
{
	if (_KeyPoints.size() != 0)
	{
		Point2f src[3];
		src[0] = _KeyPoints[36];
		src[1] = _KeyPoints[45];
		src[2] = _KeyPoints[30];

		rotaimage = faceWarpandRotation(src, _inPutImage);

		Point2f eye_left, eye_right;
		Point2f rota_point;
		eye_left = src[0];
		eye_right = src[1];
		rota_point = src[2];


		float a = (eye_right.x - eye_left.x)*(eye_right.x - eye_left.x) + (eye_right.y - eye_left.y)*(eye_right.y - eye_left.y);
		float b = sqrtf(a);
		float zoom = 3.0*width / 5.0/sqrtf(a);
		//float zoom = sqrtf((eye_right.x - eye_left.x)*(eye_right.x - eye_left.x) + (eye_right.y - eye_left.y)*(eye_right.y - eye_left.y)) / width / 2;

		int dst_width = _inPutImage.cols*zoom;
		int dst_height = _inPutImage.rows*zoom;

		Mat imgresize;
		resize(rotaimage, imgresize, Size(dst_width, dst_height), 0, 0, CV_INTER_LINEAR);
		
		

 		vector<CvPoint>reKeypoints;

		CvPoint center = _KeyPoints[30];
		

		for (unsigned int ix = 0; ix < 68; ix++)
		{
			CvPoint dst;
			Point2f _tmp;
			CvPoint src = _KeyPoints[ix];
			
			int x = src.x - center.x;
			int y = src.y - center.y;

			dst.x = cvRound(x * cos(angle) + y * sin(angle) + center.x);
			dst.y = cvRound(-x * sin(angle) + y * cos(angle) + center.y);
			
			dst.x = dst.x*zoom;
			dst.y = dst.y*zoom;

			
			_tmp = point_transform(dst, cvPoint(center.x*zoom,center.y*zoom));

			FinalKPoints.push_back(_tmp);
		
		}
		

		Rect _rect;
		_rect.x = src[2].x*zoom - width / 2;
		_rect.y = src[2].y*zoom - height / 2;
		if (_rect.x + width<imgresize.cols)_rect.width = width;
		else
		{
			_rect.width = imgresize.cols - _rect.x;
		}

		if (_rect.y + height < imgresize.rows)_rect.height = height;
		else
		{
			_rect.height = imgresize.rows - _rect.y;
		}
		
		


		/*rectangle(imgresize, _rect, Scalar(255, 255, 0));
		imshow("test", imgresize);
		waitKey(0);*/
		
		alignimg = imgresize(_rect);
		

		/*for (int ix = 0; ix < 68; ix++)
		{
		circle(alignimg, FinalKPoints[ix], 1, Scalar(255, 0, 0));
		}

		imshow("Align",alignimg);
		waitKey(0);*/
	}
}

Point2f FaceAlign::point_transform(CvPoint src,CvPoint center)
{
	Point2f dst_center(width / 2.0, height / 2.0);
	Point2f src_center(center.x, center.y);

	float gapx = src.x - src_center.x;
	float gapy = src.y - src_center.y;

	Point2f dst;
	dst.x = gapx + dst_center.x;
	dst.y = gapy + dst_center.y;

	return dst;
}

Mat FaceAlign::getFaceAlignimg()
{
	return alignimg;
}

void FaceAlign::getFaceAlignPos(std::vector<cv::Point2f>&Final_KeyPoints)
{
	for (vector<Point2f>::iterator iter = FinalKPoints.begin(); iter != FinalKPoints.end(); ++iter)
	{
		Final_KeyPoints.push_back(*iter);
	}
}
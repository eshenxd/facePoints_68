
#include "faceWarpAndRotation.h"

using namespace std;
using namespace cv;


Mat faceWarpandRotation(cv::Point2f srcTri[3], cv::Mat inPut)
{
	/*Mat rot_mat(2, 3, CV_32FC1);
	Mat warp_mat(2, 3, CV_32FC1);
	Mat src, warp_dst, warp_rotate_dst;

	src = inPut;

	cv::Point2f dstTri[3];

	Point2f center = Point2f(cvRound(865 / 2), cvRound(458 / 2));

	int a = sqrt(abs(srcTri[1].x - srcTri[0].x)*abs(srcTri[1].x - srcTri[0].x) + abs(srcTri[1].y - srcTri[0].y)*abs(srcTri[1].y - srcTri[0].y));
	int b = sqrt(abs(srcTri[2].x - center.x)*abs(srcTri[2].x - center.x) + abs(srcTri[2].y - center.y)*abs(srcTri[2].y - center.y));

	dstTri[0] = srcTri[0];
	dstTri[1].x = srcTri[0].x + a;
	dstTri[1].y = srcTri[0].y;
	dstTri[2].x = srcTri[0].x + cvRound(a / 2);
	dstTri[2].y = srcTri[0].y + b;

	warp_mat = getAffineTransform(srcTri, dstTri);
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());*/
	
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
	cv2DRotationMatrix(cvPoint2D32f(rota_point.x, rota_point.y), m_angle, 1, map);
	warpAffine(src, warp_dst, Mat(map),src.size());
	
	/*namedWindow("Source", CV_WINDOW_AUTOSIZE);
	imshow("Source", inPut);

	namedWindow("Wrap", CV_WINDOW_AUTOSIZE);
	imshow("Wrap", warp_dst);
	waitKey(0);*/

	return warp_dst;
}
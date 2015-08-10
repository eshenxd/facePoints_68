#ifndef _FACE_WARP_AND_ROTATION_H
#define _FACE_WARP_AND_ROTATION_H

/*
*      faceWarpAndRotation.cpp
*      ʹ���������������ת�Ĵ���
*      �������۵���ǣ����۵��ҽ�������ˮƽ����ļн�
*      ��Ϊ��ת�Ƕȣ��Ǽ���Ϊ��ת����
*      Input��
*             srcTri[0] ���۵����
*             srcTri[1] ���۵��ҽ�
*             srcTri[2] �Ǽ�
*      Output:
*             cv::Mat
*/

#include "header.h"

cv::Mat faceWarpandRotation(cv::Point2f srcTri[3], cv::Mat inPut);

#endif
#ifndef _FACE_WARP_AND_ROTATION_H
#define _FACE_WARP_AND_ROTATION_H

/*
*      faceWarpAndRotation.cpp
*      使用三点进行人脸旋转的代码
*      其中左眼的左角，右眼的右角连线与水平方向的夹角
*      作为旋转角度，鼻尖作为旋转中心
*      Input：
*             srcTri[0] 左眼的左角
*             srcTri[1] 右眼的右角
*             srcTri[2] 鼻尖
*      Output:
*             cv::Mat
*/

#include "header.h"

cv::Mat faceWarpandRotation(cv::Point2f srcTri[3], cv::Mat inPut);

#endif
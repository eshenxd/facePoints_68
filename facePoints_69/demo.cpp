/*
   demo.cpp
   Author: Ethan
   2015-07-23


   Input:
       modelPath: LBF.model and regressor.model �Ĵ��λ��
	   cascadeName�� Harrģ���ļ��Ĵ��λ��
	   inputImage:�����ͼ��
	Output:
	   Keypoints.getFaceKeypoints():��ȡ�����ؼ���
*/

#include "header.h"
#include "face_points.h"

using namespace std;
using namespace cv;
int main()
{
	string modelPath = "../model/";
	string cascadeName = "../model/haarcascade_frontalface_alt.xml";
	string paramName = "../model/LBF.model";
	
	KeyPoints keypointor(modelPath, cascadeName);

	Mat inputImage = imread("1.jpg");

	keypointor.runKeypointsDetection(inputImage);

	vector<CvPoint>points = keypointor.getFaceKeypoints();

	return 0;
}
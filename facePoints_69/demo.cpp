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
#include "video_camera.h"
#include "getFiles.h"

using namespace std;
using namespace cv;
int main()
{
	string modelPath = "../model/";
	string cascadeName = "../model/haarcascade_frontalface_alt.xml";
	string paramName = "../model/LBF.model";
	
	KeyPoints keypointor(modelPath, cascadeName);
	

	Mat inputImage;

	string filePath = "../image";
	vector<string>filename;
	getFiles(filePath, filename);
	for (vector<string>::iterator iter = filename.begin(); iter != filename.end(); iter++)
	{
		inputImage = imread(*iter);
		keypointor.runKeypointsDetection(inputImage);
	}

	/*inputImage = imread("01.jpg");

	keypointor.runKeypointsDetection(inputImage);*/

	

	return 0;
}
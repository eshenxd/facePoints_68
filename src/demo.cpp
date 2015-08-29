/*
   demo.cpp
   Author: Ethan
   2015-07-23


   Input:
       modelPath: LBF.model and regressor.model 的存放位置
	   cascadeName： Harr模板文件的存放位置
	   inputImage:待检测图像
	Output:
	   Keypoints::getFaceKeypoints();获取人脸关键点
	   FaceAlignment::getFaceAlignimg();获取对齐后的人脸图像
	   FaceAlignment::getFaceAlignPos(vector<Point2f>);获取对齐后人脸landmark坐标
*/

#include "header.h"
#include "face_points.h"
#include "video_camera.h"
#include "getFiles.h"
//#include "faceWarpAndRotation.h"
#include "facealignment.h"

using namespace std;
using namespace cv;

string _int2string_(int x)
{
	string tmp_s;
	char tmp_c[10];
	_itoa_s(x, tmp_c, 10);
	tmp_s = (string)tmp_c;
	return tmp_s;
}

int main()
{
	string modelPath = "../model/";
	string cascadeName = "../model/haarcascade_frontalface_alt.xml";
	string paramName = "../model/LBF.model";
	

	int saveCount = 0;
	string imageSavepath = "../save/";
	vector<CvPoint>save_keyPoint;

	KeyPoints keypointor(modelPath, cascadeName);
	

	Mat inputImage;
	Mat outputImage;

	string filePath = "../image";
	vector<string>filename;
	getFiles(filePath, filename);

	FaceAlign FA;

	for (vector<string>::iterator iter = filename.begin(); iter != filename.end(); iter++)
	{
		saveCount++;
		inputImage = imread(*iter);
		keypointor.runKeypointsDetection(inputImage);
		save_keyPoint = keypointor.getFaceKeypoints();


		FA.runFaceAlignment(inputImage,save_keyPoint);
		
		vector<Point2f>points;
		Mat alignimage = FA.getFaceAlignimg();
		FA.getFaceAlignPos(points);

		for (int ix = 0; ix < 68; ix++)
		{
			circle(alignimage, points[ix], 1, Scalar(255, 0, 0));
		}
		imshow("align", alignimage);
		waitKey(0);
		
	}

	

	
	

	return 0;
}
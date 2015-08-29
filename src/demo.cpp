/*
   demo.cpp
   Author: Ethan
   2015-07-23


   Input:
       modelPath: LBF.model and regressor.model �Ĵ��λ��
	   cascadeName�� Harrģ���ļ��Ĵ��λ��
	   inputImage:�����ͼ��
	Output:
	   Keypoints::getFaceKeypoints();��ȡ�����ؼ���
	   FaceAlignment::getFaceAlignimg();��ȡ����������ͼ��
	   FaceAlignment::getFaceAlignPos(vector<Point2f>);��ȡ���������landmark����
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
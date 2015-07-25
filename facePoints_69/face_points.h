#ifndef _FACE_POINTS_H_
#define _FACE_POINTS_H_

#include "header.h"
#include "LBF.h"
#include "LBFRegressor.h"

class KeyPoints
{
public:
	KeyPoints(std::string modelName, std::string cascadeName)
	{
		this->modelName = modelName;
		this->cascadeName = cascadeName;


		faces = new std::vector < cv::Rect > ;

		initParam(modelName);

		regressor = new LBFRegressor;
		regressor->Load(modelName);

		cascade = new cv::CascadeClassifier;
		if (!cascade->load(cascadeName)){
			std::cerr << "ERROR: Could not load classifier cascade" << std::endl;
		}
	}
	~KeyPoints()
	{
		delete regressor;
		//delete cascade;
	}

	bool initParam(std::string param_file);
	void initParam();
	void runKeypointsDetection(cv::Mat inputImage);
	void getFacePosition(int* pos);

	/*<  ���ص���һ��vector��������������ͼƬ
	     ���������Ĺؼ��㣬����ÿ68����Ϊһ������*/
	std::vector<CvPoint> getFaceKeypoints();

	/*<  keypoints�д�ŵ�Ϊ���йؼ���ĺ������꣬
	     ÿ����λһ���㣬ÿ68����Ϊһ������*/
	void getFaceKeypoints(int* keypoints);

	void drawFace();
	void drawKeypoints();

private:
	Params _params;
	int _pos[4];
	std::string modelName;
	std::string cascadeName;

	std::vector<cv::Rect> *faces;

	std::vector<CvPoint>points;

	LBFRegressor* regressor;
	cv::CascadeClassifier* cascade;
	cv::Mat_<double> current_shape;   /*< curret_shape��һ���������еľ���,������ż�⵽�Ĺؼ���*/
	std::vector<cv::Mat_<double>>shapes;


	void ReadGlobalParamFromFile(std::string );
	void InitializeGlobalParam();
	void detectFace(cv::Mat image);

};

#endif
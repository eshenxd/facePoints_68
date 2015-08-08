/*
   代码名称：face_points
   代码功能：get face keypoints
   代码作者：Ethan
   新建时间：2015-7-23
   修改时间：
*/

#include "face_points.h"

using namespace std;
using namespace cv;

Params global_params;

bool KeyPoints::initParam(string param_file)
{
	

	cout << "Loading GlobalParam..." << endl;
	ifstream fin;
	fin.open(param_file+"LBF.model");

	if (!fin)return false;

	fin >> _params.bagging_overlap;
	fin >> _params.max_numtrees;
	fin >> _params.max_depth;
	fin >> _params.max_numthreshs;
	fin >> _params.landmark_num;
	fin >> _params.initial_num;
	fin >> _params.max_numstage;

	for (int i = 0; i < _params.max_numstage; i++){
		fin >> _params.max_radio_radius[i];
	}

	for (int i = 0; i < _params.max_numstage; i++){
		fin >> _params.max_numfeats[i];
	}
	cout << "Loading GlobalParam end" << endl;
	fin.close();

	global_params = _params;

	//regressor->Load(modelName);

	return true;
}

void KeyPoints::initParam()
{
	_params.bagging_overlap = 0.4;
	_params.max_numtrees = 10;
	_params.max_depth = 5;
	_params.landmark_num = 68;
	_params.initial_num = 5;

	_params.max_numstage = 7;
	double m_max_radio_radius[10] = { 0.4, 0.3, 0.2, 0.15, 0.12, 0.10, 0.08, 0.06, 0.06, 0.05 };
	int m_max_numfeats[10] = { 500, 500, 500, 300, 300, 200, 200, 200, 100, 100 };
	for (int i = 0; i < 10; i++){
		_params.max_radio_radius[i] = m_max_radio_radius[i];
	}
	for (int i = 0; i < 10; i++){
		_params.max_numfeats[i] = m_max_numfeats[i];
	}
	_params.max_numthreshs = 500;

}

void KeyPoints::runKeypointsDetection(Mat inputImage)
{
	detectFace(inputImage);
	points.clear();
	for (vector<Mat_<double>>::iterator iter = shapes.begin(); iter != shapes.end(); ++iter)
	{
		for (int i = 0; i < global_params.landmark_num; i++)
		{
			CvPoint point;
			point.x = (*iter)(i, 0);
			point.y = (*iter)(i, 1);
			points.push_back(point);
		}
		
	}
	
#ifdef DEBUG
	/*for (unsigned int ix = 0; ix < points.size(); ix++)
	{
	circle(inputImage, Point2d(points[ix].x,points[ix].y), 3, Scalar(255, 255, 255), -1, 8, 0);
	}*/
	/*line(inputImage, Point2d(points[17].x, points[17].y), Point2d(points[26].x, points[26].y),
		Scalar(255, 0, 0), 2, 8, 0);
	line(inputImage, Point2d(points[27].x, points[27].y), Point2d(points[30].x, points[30].y), Scalar(255, 0, 0), 2, 8, 0);*/
	if (points.size() == 68){

		Point2d p1, p2, p3, p4;

		int gap = (points[27].x - points[17].x) / 2;

		p1.x = points[17].x;
		p1.y = points[36].y - gap;
		p2.x = points[27].x;
		p2.y = points[36].y - gap;
		p3.x = p1.x;
		p3.y = points[36].y + gap;
		p4.x = p2.x;
		p4.y = points[36].y + gap;

		//line(inputImage, p1, p2, Scalar(255, 0, 0), 1, 8, 0);
		//line(inputImage, p4, p2, Scalar(255, 0, 0), 1, 8, 0);
		//line(inputImage, p1, p3, Scalar(255, 0, 0), 1, 8, 0);
		//line(inputImage, p3, p4, Scalar(255, 0, 0), 1, 8, 0);

		Mat ROI(inputImage, Rect(p1.x, p1.y, gap * 2, gap * 2));
		saveCount++;

		string saveImageName = imageSavepath + _int2string(saveCount) + ".jpg";

		imwrite(saveImageName, ROI);


	}
	
#endif // DEBUG
	

}

vector<CvPoint> KeyPoints::getFaceKeypoints()
{
	return points;
}

void KeyPoints::getFaceKeypoints(int* keypoints)
{
	int count = 0;

	for (unsigned int ix = 0; ix < points.size(); ix++)
	{
		keypoints[count++] = points[ix].x;
		keypoints[count++] = points[ix].y;
	}

	return;
}

void KeyPoints::detectFace(cv::Mat image)
{
	int i = 0;
	double t = 0;
	double scale = 1.3;
	

	Mat gray, smallImg(cvRound(image.rows / scale), cvRound(image.cols / scale), CV_8UC1);

	cvtColor(image, gray, CV_BGR2GRAY);
	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
	equalizeHist(smallImg, smallImg);

	

	cascade->detectMultiScale(smallImg, *faces,
		1.2, 4, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		| CV_HAAR_SCALE_IMAGE
		,
		Size(20, 20));
	shapes.clear();

	for (vector<Rect>::const_iterator r = faces->begin(); r != faces->end(); r++, i++){
		Point center;
		//Scalar color = colors[i % 8];
		BoundingBox boundingbox;

		boundingbox.start_x = r->x*scale;
		boundingbox.start_y = r->y*scale;
		boundingbox.width = (r->width - 1)*scale;
		boundingbox.height = (r->height - 1)*scale;
		boundingbox.centroid_x = boundingbox.start_x + boundingbox.width / 2.0;
		boundingbox.centroid_y = boundingbox.start_y + boundingbox.height / 2.0;

		
	    current_shape = regressor->Predict(gray, boundingbox, 1);
		shapes.push_back(current_shape);
		
	}

	
}

string KeyPoints::_int2string(int x)
{
	string tmp_s;
	char tmp_c[10];
	_itoa_s(x,tmp_c,10);
	tmp_s = (string)tmp_c;
	return tmp_s;
}




/*
 *
 * �������ƣ�faceKeypoints_68
 * ���빦�ܣ�����LBFԴ�����޸Ķ���������˴����е�һЩbug�������˷�ס����Ҫ����
 *          �Ǹ�����������ȡ��������λ�ã��ҳ�68���ؼ����λ�á�
 *          Input:
               modelPath: LBF.model and regressor.model �Ĵ��λ��
	           cascadeName�� Harrģ���ļ��Ĵ��λ��
	           cv::Mat inputImage:�����ͼ��
	        Output:
	           Keypoints::getFaceKeypoints();��ȡ�����ؼ���
	           FaceAlignment::getFaceAlignimg();��ȡ����������ͼ��
	           FaceAlignment::getFaceAlignPos(vector<Point2f>);��ȡ���������landmark����
			   
			���������ż�landmark.jpg
 * �������ߣ�Ethan
 * ����ʱ�䣺2015/7/25
 * ������Ϣ��
 *           v1.1  �޸��˶������ͼƬ������������ظ���bug
 *                 �����˱����ļ���������ͼƬ�Ĺ���
 *           v1.2  ����WarpAndRotation.cpp/WarpAndRotation.h�����ļ�
 *                 ʵ�ָ��������������ͼ�������ת�Ĺ���
 *           v2.0  �����޸���ԭ�л�ȡlandmark��Ļ����ϣ����ݵ�����
 *                 ��ԭͼ�����˲ü������ţ��ó��Ľ���Ѿ�����ֱ����
 *                 ���������ȡ
 */
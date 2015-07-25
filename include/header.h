#ifndef  HEADER_H

#define HEADER_H

#include "minmax.h"
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <atlimage.h>
#include <time.h>
#include <math.h>
#include <string>
#include <sstream>
#include "io.h"




#include <iostream>
#include <fstream>


#include "../opencv/include/opencv/cv.h" 
#include "../opencv/include/opencv/highgui.h"
#include "../opencv/include/opencv/cxcore.h"


#ifdef _DEBUG

#pragma comment(lib, "../opencv/lib/opencv_core248d.lib")
#pragma comment(lib, "../opencv/lib/opencv_objdetect248d.lib")
#pragma comment(lib, "../opencv/lib/opencv_highgui248d.lib")
#pragma comment(lib, "../opencv/lib/opencv_imgproc248d.lib")



#else

#pragma comment(lib, "../opencv/lib/opencv_core248.lib")
#pragma comment(lib, "../opencv/lib/opencv_objdetect248.lib")
#pragma comment(lib, "../opencv/lib/opencv_highgui248.lib")
#pragma comment(lib, "../opencv/lib/opencv_imgproc248.lib")


#endif



#endif
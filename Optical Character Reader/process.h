#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "BlobResult.h"

using namespace cv;
using namespace std;

class OCRprocess
{
    private:

    int device;
    VideoCapture cap;

    Mat frame;
    Mat grey;
    Mat mask;
    Mat canny;


    vector<Mat> contours;
    vector<Point> blobs;

    int line;

    static bool inst;
    static OCRprocess* singleton;

    OCRprocess();

    public:

    static OCRprocess *instance();
    Mat getImg(int);
    Mat returnCurrent();
    Mat addLine();
    void OCRprocessFrame();
    void setDevice(int);

    ~OCRprocess();

};




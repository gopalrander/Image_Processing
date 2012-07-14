#include "process.h"
#define IMG 1
#define GREY 2
#define MASK 3
#define FALSE 0
#define TRUE 1
#include "BlobResult.h"


bool OCRprocess::inst = FALSE;
OCRprocess* OCRprocess::singleton = NULL;
OCRprocess* OCRprocess::instance()
{
    if(!inst)
    {
        singleton = new OCRprocess;
        inst = TRUE;
        return singleton;
    }
    else
    {
        return singleton;
    }
}
OCRprocess::OCRprocess() : device(0), line(250)
{
    cap.open(device);
    blobs.resize(500);

}
OCRprocess::~OCRprocess()
{
    cap.release();
}
void OCRprocess::setDevice(int id)
{
    destroyAllWindows();
    cap.release();
    device = id;
    cap.open(device);
}
Mat OCRprocess::returnCurrent()
{
    cap >> frame;

    cvtColor(frame,grey,CV_BGR2GRAY);
    adaptiveThreshold(grey,mask,255,
                      cv::ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,481,0);
    return frame;
}
Mat OCRprocess::getImg(int Param)
{
    switch(Param)
    {
        case IMG:
        return frame;
        break;

        case GREY:
        return grey;
        break;

        case MASK:
        return mask;
        break;

        default:
        cout<<"Invalid Argument in funtion getImg()";

        break;
    }
}
Mat OCRprocess::addLine()
{

   Mat result;
   result = frame;
   cv::line(result,Point(0,line),Point(1000,line),CV_RGB(255,255,255),3);
   return result;
}
void OCRprocess::OCRprocessFrame()
{

    int cnt = 0;

   //noise filtering
    erode(mask,mask,Mat(),Point(-1,-1),3);
    dilate(mask,mask,Mat(),Point(-1,-1),0);
    //blur(mask,mask,Size(6,6));



    uchar *row = mask.ptr(line);
    for(int x =0;x<mask.size().width;x++)
    {
        if(row[x] > 128)
            {
                int area = floodFill(mask,Point(x,line),CV_RGB(0,0,100));
                if(area > 100)
                {
                    blobs[cnt++] = Point(x,line);
                }
            }

    }

    for(int y=0;y<mask.size().height;y++)
    {
        uchar* row = mask.ptr(y);
        for(int x=0;x<mask.size().width;x++)
        {
            if(row[x] > 128)
            {
                int area = floodFill(mask,Point(x,y),CV_RGB(0,0,64));

            }
        }
    }
    for(int i =0 ;i<cnt;i++)
    floodFill(mask,blobs[i],CV_RGB(255,255,255));
    for(int y=0;y<mask.size().height;y++)
	{
					uchar *row = mask.ptr(y);
					for(int x=0;x<mask.size().width;x++)
					{
						 if(row[x]==64 )
						 {
							  int area = cv::floodFill(mask, cv::Point(x,y), CV_RGB(0,0,0));

						 }
					}
	}


}

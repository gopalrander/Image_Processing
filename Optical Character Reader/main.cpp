#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "process.h"
#include <fstream>
#include "tesseract/baseapi.h"
#define MASK 3
int main()
{
    OCRprocess* ocr;
    ocr = OCRprocess::instance();
  //  ocr->setDevice(1);
    std::fstream file;
    char ch;
    system("ls");
    system("export LD_LIBRARY_PATH=$LD_LIBRARAY_PATH:/usr/local/lib");
    system("tesseract img2.tif testdd");



    while(1)
    {
        Mat img = ocr->returnCurrent();


        ocr->OCRprocessFrame();
        Mat mask = ocr->getImg(MASK);
        imshow("Read",ocr->addLine());

        imshow("HELLO",mask);
        imwrite("img.jpg",mask);

        system("convert img.jpg -monochrome -flatten img1.png");
        system("convert img1.png -monochrome -flatten img2.tif");
        system("tesseract img2.tif testdd");






        file.open("text.txt");
        file.seekg(0);
//        while(file)
//        {
//            file.get(ch);
//            cout<<ch;
//        }
//        cout<<endl;
        file.close();



        if(waitKey(25) == 27) break;

    }
    return 0;
}

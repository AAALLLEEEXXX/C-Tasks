#include <iostream>
#include <opencv2/opencv.hpp>

#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;

int threshold_value = 40;
int threshold_type = 1;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value= 255;

Mat src, src_gray,binary;
char* window_name = "Threshold Demo";

char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbar_value = "Value";

int r,g,b;
int sizeValue = 2, constValue = 11;

void Threshold_Demo(int, void*);
Mat brightnessEnch(Mat& greyScale);
Mat makeHistogram(Mat& image);
void adaptiveTreshold(int, void*);

int main()
{
    Mat image = imread("/Users/aleksej/Desktop/test_marker.jpg");
    //Mat image = imread("/Users/aleksej/Desktop/testbox.jpg");


    if(!image.data)
    {
        return -1;
    }

    imshow("Test", image);
    Mat greyScale;
    int i,j;
    int min_stolb,min_strok, max_stolb, max_strok;
    min_stolb=image.cols;
    min_strok=image.rows;
    max_stolb=0;
    max_strok=0;

    for (i=0;i<image.rows;i++)
    {
        for (j=0;j<image.cols;j++)
        {
            r = (image.at<cv::Vec3b>(i,j)[2]);
            g = (image.at<cv::Vec3b>(i,j)[1]);
            b = (image.at<cv::Vec3b>(i,j)[0]);
            //cout<<r<<"\t"<<g<<"\t"<<b<<"\t"<<endl;
            if ((r > b+40)&&(r > g+40)&&(r > 110)&&(b < 30))
            { if (j<min_stolb)
                min_stolb=j;
              if (i<min_strok)
                min_strok=i;
              if(j>max_stolb)
                max_stolb=j;
              if(i>max_strok)
                max_strok=i;
            }
        }
    }
    cout<<"min_stolb =  "<<min_stolb<<"   min_strok= "<<min_strok<<"  "<<"  max_stolb=  " <<  max_stolb<<"  max_strok  ="<<max_strok<<endl;
    Rect pr(min_stolb,min_strok,(max_stolb-min_stolb), (max_strok-min_strok));
    Mat image2;
    image(pr).copyTo(image2);
    imshow ("MiniSize", image2);
    waitKey();


    cvtColor(image2, src_gray, COLOR_BGR2GRAY);
    src = brightnessEnch(src_gray);
    GaussianBlur(src, src, Size(3,3),3);
    imshow ("GrayMiniSize", src);
    namedWindow(window_name, WINDOW_AUTOSIZE);



    Threshold_Demo(0,0);
    createTrackbar(trackbar_type,window_name,&threshold_type,1,Threshold_Demo);
    createTrackbar(trackbar_value,window_name,&threshold_value,50,Threshold_Demo);
    waitKey();


    Mat imagerec = imread("/Users/aleksej/Desktop/rec.png");
    Mat rgb;
    // downsample and use it for processing
    pyrDown(imagerec, rgb);
    Mat small;
    cvtColor(rgb, small, COLOR_BGR2GRAY);
    // morphological gradient
    Mat grad;
    Mat morphKernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
    morphologyEx(small, grad, MORPH_GRADIENT, morphKernel);
    // binarize
    Mat bw;
    threshold(grad, bw, 0.0, 255.0, THRESH_BINARY | THRESH_OTSU);
// connect horizontally oriented regions
    Mat connected;
    morphKernel = getStructuringElement(MORPH_RECT, Size(9, 1));
    morphologyEx(bw, connected, MORPH_CLOSE, morphKernel);
    // find contours
    Mat mask = Mat::zeros(bw.size(), CV_8UC1);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(connected, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));
    // filter contours
    for(int idx = 0; idx >= 0; idx = hierarchy[idx][0])
    {
        Rect rect = boundingRect(contours[idx]);
        Mat maskROI(mask, rect);
        maskROI = Scalar(0, 0, 0);
        // fill the contour
        drawContours(mask, contours, idx, Scalar(255, 255, 255), FILLED);
        // ratio of non-zero pixels in the filled region
        double r = (double)countNonZero(maskROI)/(rect.width*rect.height);

        if (r > .45 /* assume at least 45% of the area is filled if it contains text */
            &&
            (rect.height > 8 && rect.width > 8) /* constraints on region size */
            /* these two conditions alone are not very robust. better to use something
            like the number of significant peaks in a horizontal projection as a third condition */
            )
        {
            rectangle(rgb, rect, Scalar(0, 255, 200), 1);
        }
    }
    imshow ("Rac", rgb);
    waitKey();





    adaptiveThreshold(src, binary, 255, 0, THRESH_BINARY, 3*2+3, 15-11);

    imshow( "AdaptiveThreshold", binary );
    namedWindow("AdaptiveThreshold", WINDOW_AUTOSIZE);








    while (true) {
        int c;
        c = waitKey(20);
        if((char)c == 27){
            break;
        }
    }

    return 0;
}

//Mat makeHistogram(Mat& image)
//{
//    int histSize = 256;
//    float range[] = {0, 255};
//    const float* pRange = range;
//    int channels[] = {0};
//    Mat hist;

//    calcHist(&image, 1, (int*)channels,Mat(),hist,1,&histSize, &(pRange));
//    int hist_w = 512,hist_h = 400;
//    int bin_w = cvRound((double)hist_w/histSize);
//    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
//    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
//    for (int i=1;i<histSize;i++)
//    {
//        line(histImage, Point(bin_w*(i-1),hist_h-cvRound(hist.at<double>(i-1))), Point(bin_w*(i),hist_h-cvRound(hist.at<double>(i))), Scalar(255,255,255), 2,8,0);
//    }
//    return  histImage;
//}

void Threshold_Demo(int, void*)
{
    //THRESH_BINARY
    //THRESH_BINARY_INV;
    THRESH_TOZERO;
//GaussianBlur(src, src, Size(3,3),3);
    threshold(src,binary,threshold_value,max_BINARY_value,threshold_type);
    imshow(window_name, binary);
}

void adaptiveTreshold(int, void*)
{
    adaptiveThreshold(src_gray, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, sizeValue*2+3, constValue-11);

    erode(src_gray,binary, Mat());
    dilate(binary,binary, Mat());
    imshow(window_name, src_gray);
    imshow("Morph",binary);
}

Mat brightnessEnch(Mat& greyScale)
{
    double minValue, maxValue;
    minMaxLoc(greyScale, &minValue, &maxValue);
    double deltaStep = 255/(maxValue - minValue), value = 0;
    Mat lookUpTable(1,256,CV_8U);
    Mat newGreyScale;
    for (int i = 0; i<255;i++)
    {
        if(i<minValue)
        {
            lookUpTable.at<double>(i) = minValue;
        }
        if(i>=minValue && i<maxValue)
        {
            value +=deltaStep;
            lookUpTable.at<unsigned char>(i) = (unsigned char) value;
        }
        if(i>=maxValue)
        {
            lookUpTable.at<double>(i) = maxValue;
        }
    }
    LUT(greyScale, lookUpTable, newGreyScale);
    GaussianBlur(newGreyScale, newGreyScale, Size(5,5),3);
    return newGreyScale;
}

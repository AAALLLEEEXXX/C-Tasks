#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include<opencv2/features2d.hpp>
#include <unistd.h>

using namespace std;

int main()
{
    cv::Ptr<cv::FeatureDetector> detectorBrisk, detectorSurf, detectorSift;
    cv::Ptr<cv::DescriptorExtractor> extractorBrisk, extractorSurf, extractorSift;
    cv::BFMatcher matcher;
    std::vector<cv::KeyPoint> keys1, keys2;
    cv::Mat src, src2;
    cv::VideoCapture cap("/Users/aleksej/Desktop/video13.avi");
//    cv::VideoCapture cap2("/Users/aleksej/Desktop/video13.avi");
    if (!cap.isOpened()){
        return -1;
    }

    bool stop = false;
    // Определим частоту кадров на видео
    double rate = cap.get(cv::CAP_PROP_FPS);
    // Рассчитаем задержку в миллисекундах
    int delay = 1000 / rate;
    cout << "Frame rate of video is " << rate << endl;


        cap >> src;
        cap >> src2;

    while (!stop)
    {
        // Проверяем доступность кадра
        bool result = cap.grab(); // Если он готов, считываем if (result)
        if(result){
            src = src2;
            cap >> src2;
        } else{
            continue;
        }

        cv::imshow("Original1", src);
        cv::imshow("Original2", src2);
        // Ждём нажатия на кнопку
        cv::Mat descr1, descr2, img_matches;
        std::vector<cv::DMatch> matches;
        //=================BRISK=====================
        detectorBrisk = cv::BRISK::create();
        extractorBrisk = cv::BRISK::create();
        detectorBrisk->detect(src,keys1);
        detectorBrisk->detect(src2,keys2);

        extractorBrisk->compute(src, keys1, descr1);
        extractorBrisk->compute(src2, keys2, descr2);

        matcher.match(descr1, descr2, matches);
        cv::drawMatches(src, keys1, src2, keys2, matches, img_matches);
        cv::imshow("BRISK", img_matches);

        //=================SURF=======================
        detectorSurf = cv::xfeatures2d::SURF::create();
        extractorSurf = cv::xfeatures2d::SURF::create();
        detectorSurf->detect(src,keys1);
        detectorSurf->detect(src2,keys2);
        extractorSurf->compute(src, keys1, descr1);
        extractorSurf->compute(src2, keys2, descr2);
        matcher.match(descr1, descr2, matches);
        cv::drawMatches(src, keys1, src2, keys2, matches, img_matches);
        cv::imshow("SURF", img_matches);

        //=================SIFT=======================
        detectorSift = cv::xfeatures2d::SIFT::create();
        extractorSift = cv::xfeatures2d::SIFT::create();
        detectorSift->detect(src,keys1);
        detectorSift->detect(src2,keys2);
        extractorSift->compute(src, keys1, descr1);
        extractorSift->compute(src2, keys2, descr2);
        matcher.match(descr1, descr2, matches);
        cv::drawMatches(src, keys1, src2, keys2, matches, img_matches);
        cv::imshow("SIFT", img_matches);

        //===========================================

        int key = cv::waitKey(delay);
        if (key==27){
            stop=true;
        }
    }
    return 0;
}

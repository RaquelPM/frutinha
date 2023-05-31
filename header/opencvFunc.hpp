#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <vector>
#include "item.hpp"
#include "barrel.hpp"

using namespace std;
using namespace cv;

void drawTransparency(Mat frame, Mat transp, int xPos, int yPos)
{
    Mat mask;
    vector<Mat> layers;

    split(transp, layers);
    Mat rgb[3] = {layers[0], layers[1], layers[2]};
    mask = layers[3];
    merge(rgb, 3, transp);
    transp.copyTo(frame.rowRange(yPos, yPos + transp.rows).colRange(xPos, xPos + transp.cols), mask);
}

void drawTransRect(Mat frame, Scalar color, double alpha, Rect region)
{
    Mat roi = frame(region);
    Mat rectImg(roi.size(), CV_8UC3, color);
    addWeighted(rectImg, alpha, roi, 1.0 - alpha, 0, roi);
}

void detectAndDraw(Mat &img, CascadeClassifier &cascade, double scale, bool tryflip, vector<Item> items, Barrel barrel)
{
    double t = 0;
    vector<Rect> faces;
    Mat gray, smallImg;
    Scalar color = Scalar(255, 0, 0);

    if (tryflip)
    {
        flip(img, img, 1);
    }

    cvtColor(img, gray, COLOR_BGR2GRAY);
    double fx = 1 / scale;
    resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT);
    equalizeHist(smallImg, smallImg);

    t = (double)getTickCount();

    cascade.detectMultiScale(smallImg, faces,1.3, 2, 0| CASCADE_SCALE_IMAGE, Size(40, 40));
    t = (double)getTickCount() - t;
    //printf("detection time = %g ms\n", t * 1000 / getTickFrequency());
    
    Rect r;

    for(size_t i = 0; i < items.size(); i++){


        Mat fruit = cv::imread(items[i].getPNG(), IMREAD_UNCHANGED);
        drawTransparency(img, fruit, items[i].getX(), items[i].getY());

    }
    
    if(!(faces.empty())){
        r = faces[0];
        rectangle(img, Point(cvRound(r.x * scale), cvRound(r.y * scale)),
                    Point(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)),
                    color, 3);
        
        barrel.setX(r.x);
        barrel.setY(r.y);
        
        if(!(barrel.isOutOfBound(1280, 720))){
        
            Mat matBarrel = cv::imread(barrel.getPNG(), IMREAD_UNCHANGED);

            try{
                drawTransparency(img, matBarrel, r.x, r.y);
            }catch(cv::Exception e){};
        }
        
    }

    // Desenha um texto
    color = Scalar(0, 0, 255);
    putText(img, "Placar:", Point(300, 50), FONT_HERSHEY_PLAIN, 2, color); // fonte

    // Desenha o frame na tela
    imshow("result", img);
}

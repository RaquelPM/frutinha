#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/opencv.hpp"
#include <vector>
#include "game.hpp"
#include <iostream>

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

void drawGameOver(Mat &img, Game &game)
{
    flip(img, img, 1);
    Scalar black = Scalar(0, 0, 0);
    drawTransRect(img, black, 0.8, Rect( 0, 0, game.getWidth(), game.getHeight()));
    putText(img, "Game Over", Point(game.getWidth()/2 - 200, game.getHeight()/2), FONT_HERSHEY_PLAIN , 4, Scalar(0,0,255)); // fonte
    putText(img, "Placar: " + to_string(game.getScore()), Point(game.getWidth()/2 - 100, game.getHeight()/2 + 50), FONT_HERSHEY_PLAIN , 2, Scalar(255,255,255)); // fonte 
    putText(img, "Recorde: " + to_string(game.getMaxScore()), Point(game.getWidth()/2 - 100, game.getHeight()/2 + 100), FONT_HERSHEY_PLAIN , 2, Scalar(255,255,255)); // fonte
    putText(img, "Pressione R para reniciar", Point(game.getWidth() - 200, game.getHeight() - 50), FONT_HERSHEY_PLAIN , 0.8, Scalar(255,255,255)); // fonte
    imshow("result", img);
    waitKey(0);
}

void drawMenu(int height, int width)
{
    Mat background = imread("assets/background.jpg", IMREAD_UNCHANGED);
    resize(background, background, Size(width, height));

    drawTransRect(background, Scalar(0, 83, 144), 1, Rect( width/4 - 50, height/2 - 80, 400, 150));
    putText(background, "Frutinha", Point(width/2 - 180, height/2), FONT_HERSHEY_PLAIN, 5, Scalar(0,193,82), 3); // fonte
    putText(background, "Pressione barra de espaco para iniciar", Point(width/2 - 140, height/2+40), FONT_HERSHEY_PLAIN , 0.8, Scalar(255,255,255)); // fonte
    imshow("result", background);
    waitKey(0);
}


void detectAndDraw(Mat &img, CascadeClassifier &cascade, double scale, bool tryflip, Game &game)
{
    double t = 0;
    vector<Rect> faces;
    Mat gray, smallImg;
    Scalar color = Scalar(255, 0, 0);

    vector<Item*> items = game.getItems();

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
        Mat fruit = cv::imread(items[i]->getPNG(), IMREAD_UNCHANGED);
        drawTransparency(img, fruit, items[i]->getX(), items[i]->getY());
    }
    
    if(!(faces.empty())){
        r = faces[0];
       /*  rectangle(img, Point(cvRound(r.x * scale), cvRound(r.y * scale)),
                    Point(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)),
                    color, 3); */
        game.getBarrel().setX(r.x + r.width/2 - game.getBarrel().getSize().first/2);
        game.getBarrel().setY(r.y - game.getBarrel().getSize().second);
        
    }

    if(!(game.getBarrel().isOutOfBound(game.getWidth(), game.getHeight()))){
        
        Mat matBarrel = cv::imread(game.getBarrel().getPNG(), IMREAD_UNCHANGED);

        try{
            drawTransparency(img, matBarrel, game.getBarrel().getX(), game.getBarrel().getY());
        }catch(Exception e){};
    } 

    // Desenha um texto
    color = Scalar(0, 0, 0);
    putText(img, "Placar: " + to_string(game.getScore()), Point(50, 50), FONT_HERSHEY_PLAIN , 2, color); // fonte

    Mat matHeart = cv::imread("assets/heart.png", IMREAD_UNCHANGED);

    try{
        for(int i =0; i< game.getLives(); i++)
            drawTransparency(img, matHeart, game.getWidth() - 100 - (i*50), 25);
    }catch(string e){
        cout << e << endl;
    };
    // Desenha o frame na tela
    imshow("result", img);
}

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <vector>
#include "../header/item.hpp"
#include "../header/barrel.hpp"


using namespace std;
using namespace cv;

void detectAndDraw(Mat &img, CascadeClassifier &cascade, double scale, bool tryflip, vector<Item> items);

string cascadeName;

int main()
{
    VideoCapture capture;
    Barrel barrel(80, 0);
    vector<Item> frutas;
    Item laranja(210, 0, 0, "assets/orange.png");
    Item morango(200, 0, 1, "assets/watermelon.png");

    
    frutas.push_back(laranja);
    frutas.push_back(morango);
    
    Mat frame;
    bool tryflip;
    CascadeClassifier cascade;
    double scale;

    cascadeName = "./models/haarcascade_frontalface_default.xml";
    cascadeName = "./models/haarcascade_frontalface_alt2.xml";
    scale = 1;
    if (scale < 1)
        scale = 1;
    tryflip = true;

    if (!cascade.load(cascadeName))
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        return -1;
    }
    
    if (!capture.open(0))
    {
        cout << "Capture from camera #0 didn't work" << endl;
        return 1;
    }

    cout << "X: " << capture.get(CAP_PROP_FRAME_WIDTH) << endl;
    cout << "Y: " << capture.get(CAP_PROP_FRAME_HEIGHT) << endl; 


    if (capture.isOpened())
    {
        cout << "Video capturing has been started ..." << endl;

        int y = barrel.getY();
        int x = barrel.getX();
        
        while(1)
        {
            capture >> frame;
            if (frame.empty())
                break;

            for(int i = 0; i < frutas.size(); i++)
            {
                int vel = 5;
                if(!(frutas[i].getSize() + frutas[i].getY() + vel>= 720))
                    frutas[i].setY(frutas[i].getY() + vel);
                else if(!(frutas[i].getSize() + frutas[i].getY() + 1 >= 720)){
                    frutas[i].setY(frutas[i].getY() + 1);
                }

            // if(!(laranja.getSize() + x + vel>= 1280))
            //     x += vel;
            // else if(!(laranja.getSize() + x + 1 >= 1280)){
            //     x += 1;
            // }
            
            

            }
            detectAndDraw(frame, cascade, scale, tryflip, frutas);

            char c = (char)waitKey(10);
            if (c == 27 || c == 'q' || c == 'Q')
                break;
            
        }
    }

    return 0;
}
/**
 * @brief Draws a transparent image over a frame Mat.
 *
 * @param frame the frame where the transparent image will be drawn
 * @param transp the Mat image with transparency, read from a PNG image, with the IMREAD_UNCHANGED flag
 * @param xPos x position of the frame image where the image will start.
 * @param yPos y position of the frame image where the image will start.
 */
void drawTransparency(Mat frame, Mat transp, int xPos, int yPos)
{
    Mat mask;
    vector<Mat> layers;

    split(transp, layers); // seperate channels
    Mat rgb[3] = {layers[0], layers[1], layers[2]};
    mask = layers[3];      // png's alpha channel used as mask
    merge(rgb, 3, transp); // put together the RGB channels, now transp insn't transparent
    transp.copyTo(frame.rowRange(yPos, yPos + transp.rows).colRange(xPos, xPos + transp.cols), mask);
}

void drawTransRect(Mat frame, Scalar color, double alpha, Rect region)
{
    Mat roi = frame(region);
    Mat rectImg(roi.size(), CV_8UC3, color);
    addWeighted(rectImg, alpha, roi, 1.0 - alpha, 0, roi);
}

void detectAndDraw(Mat &img, CascadeClassifier &cascade, double scale, bool tryflip, vector<Item> items)
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

    cascade.detectMultiScale(smallImg, faces,
                             1.3, 2, 0
                                         //|CASCADE_FIND_BIGGEST_OBJECT
                                         //|CASCADE_DO_ROUGH_SEARCH
                                         | CASCADE_SCALE_IMAGE,
                             Size(40, 40));
    t = (double)getTickCount() - t;
    printf("detection time = %g ms\n", t * 1000 / getTickFrequency());
    // PERCORRE AS FACES ENCONTRADAS
    Rect r;

    for(int i = 0; i < items.size(); i++){


        Mat orange = cv::imread(items[i].getPNG(), IMREAD_UNCHANGED);
        drawTransparency(img, orange, items[i].getX(), items[i].getY());

    }
    
    try{

        
    
        if(!(faces.empty())){
            r = faces[0];
            rectangle(img, Point(cvRound(r.x * scale), cvRound(r.y * scale)),
                        Point(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)),
                        color, 3);
            // item.setX(r.x);
            // item.setY(r.y);
            
            
            // if(!(barrel.isOutOfBound(1280, 720))){
            //     drawTransparency(img, orange, r.x, r.y);
            // }
            // else{
            //     cout << "FORA\n";
            // }
            
        }
    }
    catch(cv::Exception e){
        cout << "ERRO\n";

    }
    

    // Desenha uma imagem
    

    // Desenha um texto
    color = Scalar(0, 0, 255);
    putText(img, "Placar:", Point(300, 50), FONT_HERSHEY_PLAIN, 2, color); // fonte

    // Desenha o frame na tela
    imshow("result", img);
}

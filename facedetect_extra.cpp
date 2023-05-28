#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void detectAndDraw( Mat& img, CascadeClassifier& cascade, double scale, bool tryflip, int x, int y);

string cascadeName;

int main( int argc, const char** argv )
{
    VideoCapture capture;
    Mat frame;
    bool tryflip;
    CascadeClassifier cascade;
    double scale;

    cascadeName = "haarcascade_frontalface_default.xml";
    cascadeName = "haarcascade_frontalface_alt2.xml";
    scale = 1;
    if (scale < 1)
        scale = 1;
    tryflip = true;

    if (!cascade.load(cascadeName)) {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        return -1;
    }

//    if(!capture.open("video.mp4")) // para testar com um video
    if(!capture.open(0))
    {
        cout << "Capture from camera #0 didn't work" << endl;
        return 1;
    }

    if( capture.isOpened() )
    {
        cout << "Video capturing has been started ..." << endl;
        
        int x = 1;

        for(;;)
        {
            x *= 2;
            capture >> frame;
            if( frame.empty() )
                break;

            detectAndDraw(frame, cascade, scale, tryflip, x, 250);

            char c = (char)waitKey(10);
            if( c == 27 || c == 'q' || c == 'Q' )
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
void drawTransparency(Mat frame, Mat transp, int xPos, int yPos) {
    Mat mask;
    vector<Mat> layers;

    split(transp, layers); // seperate channels
    Mat rgb[3] = { layers[0],layers[1],layers[2] };
    mask = layers[3]; // png's alpha channel used as mask
    merge(rgb, 3, transp);  // put together the RGB channels, now transp insn't transparent 
    transp.copyTo(frame.rowRange(yPos, yPos + transp.rows).colRange(xPos, xPos + transp.cols), mask);
}

void drawTransRect(Mat frame, Scalar color, double alpha, Rect region) {
    Mat roi = frame(region);
    Mat rectImg(roi.size(), CV_8UC3, color); 
    addWeighted(rectImg, alpha, roi, 1.0 - alpha , 0, roi); 
}

void detectAndDraw( Mat& img, CascadeClassifier& cascade, double scale, bool tryflip, int x, int y)
{
    double t = 0;
    vector<Rect> faces;
    Mat gray, smallImg;
    Scalar color = Scalar(255,0,0);

    if( tryflip ) {
        flip(img, img, 1);
    }

    cvtColor( img, gray, COLOR_BGR2GRAY );
    double fx = 1 / scale;
    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT );
    equalizeHist( smallImg, smallImg );

    t = (double)getTickCount();

    cascade.detectMultiScale( smallImg, faces,
        1.3, 2, 0
        //|CASCADE_FIND_BIGGEST_OBJECT
        //|CASCADE_DO_ROUGH_SEARCH
        |CASCADE_SCALE_IMAGE,
        Size(40, 40) );
    t = (double)getTickCount() - t;
    printf( "detection time = %g ms\n", t*1000/getTickFrequency());
    // PERCORRE AS FACES ENCONTRADAS
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Rect r = faces[i];
        rectangle( img, Point(cvRound(r.x*scale), cvRound(r.y*scale)),
                    Point(cvRound((r.x + r.width-1)*scale), cvRound((r.y + r.height-1)*scale)),
                    color, 3);
    }

    // Desenha uma imagem
    Mat overlay = cv::imread("orange.png", IMREAD_UNCHANGED);
    drawTransparency(img, overlay, x, y);

    // Desenha quadrados com transparencia
    double alpha = 0.3;
    drawTransRect(img, Scalar(0,255,0), alpha, Rect(  0, 0, 200, 200));
    drawTransRect(img, Scalar(255,0,0), alpha, Rect(200, 0, 200, 200));

    // Desenha um texto
    color = Scalar(0,0,255);
    putText	(img, "Placar:", Point(300, 50), FONT_HERSHEY_PLAIN, 2, color); // fonte

    // Desenha o frame na tela
    imshow( "result", img );
}

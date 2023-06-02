#include <iostream>
#include <../header/game.hpp>
#include "../header/opencvFunc.hpp"

using namespace std;

string cascadeName;

int main()
{
    srand(time(NULL));
  
    VideoCapture capture;
    
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

    if (capture.isOpened())
    {
        
        int width = capture.get(CAP_PROP_FRAME_WIDTH);
        int height = capture.get(CAP_PROP_FRAME_HEIGHT); 

        Game game(width, height);
        Barrel barrel(0, 0);
        cout << "Video capturing has been started ..." << endl;        
    
        while(true)
        {
            capture >> frame;
            if (frame.empty())
                break;

            try{
                game.frame();
            } catch(string msg){
                cout << msg << endl; // desenhar na tela
                break;
            } 

            detectAndDraw(frame, cascade, scale, tryflip, game.getItems(), game.getBarrel(), game.getScore());

            char c = (char)waitKey(10);
            if (c == 27 || c == 'q' || c == 'Q')
                break;
        }
    }

    return 0;
}
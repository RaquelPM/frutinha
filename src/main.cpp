#include <iostream>
#include <thread>
#include "opencvFunc.hpp"

using namespace std;

void func(){
    cout << "func" << endl;
}

string cascadeName;

int main()
{
    srand(time(NULL));
  
    VideoCapture capture;
    vector<thread> threads;
    
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
        cout << "Video capturing has been started ..." << endl;      
        int width = capture.get(CAP_PROP_FRAME_WIDTH);
        int height = capture.get(CAP_PROP_FRAME_HEIGHT);

        while(true){ 
            Game game(width, height);
            Barrel barrel(0, 0);
  
            bool alive = true;

            while(alive){
                capture >> frame;
                if (frame.empty())
                    break;

                try{
                    game.frame();
                    
                } catch(string msg){
                    drawGameOver(frame, game);

                    while (true){
                      
                        char c = (char)waitKey(1000);
                        
                        if(c == 'r' or c == 'R'){
                            alive = false;
                            break;
                        }
                        if(c == 'q' or c == 'Q'){
                            return 0;
                        }
                    }  
                } 

                if(!alive){
                    break;
                }

                detectAndDraw(frame, cascade, scale, tryflip, game);

                char c = (char)waitKey(10);
                if (c == 27 || c == 'q' || c == 'Q'){

                    return 0;
                }
            }
        }
       
    }

    return 0;
}
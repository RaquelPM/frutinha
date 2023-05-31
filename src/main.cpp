#include <iostream>
#include "../header/opencvFunc.hpp"

using namespace std;

string cascadeName;

int main()
{
    VideoCapture capture;
    Barrel barrel(0, 0);
    vector<Item> frutas;
    Item laranja(210, 0, 0);
    Item morango(200, 0, 1);
    cout << morango.getPNG() << endl;
    cout << barrel.getPNG() << endl;

    
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



    if (capture.isOpened())
    {
        cout << "Video capturing has been started ..." << endl;

        int width = capture.get(CAP_PROP_FRAME_WIDTH);
        int height = capture.get(CAP_PROP_FRAME_HEIGHT); 
    
        while(true)
        {
            capture >> frame;
            if (frame.empty())
                break;

            int vel = 5;
            
            for(size_t i = 0; i < frutas.size(); i++){

                frutas[i].setY(frutas[i].getY() + vel);
                
                if(frutas[i].isOutOfBound(height))
                    frutas.erase(frutas.begin() + i);
                
            }

            detectAndDraw(frame, cascade, scale, tryflip, frutas, barrel);

            char c = (char)waitKey(10);
            if (c == 27 || c == 'q' || c == 'Q')
                break;
        }
    }

    return 0;
}
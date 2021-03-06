#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

Mat detectAndDisplay(Mat frame) 
{
    static const String face_cascade_name = "haarcascade_frontalface_default.xml";
    static CascadeClassifier face_cascade;
	vector<Rect> faces;
	Mat frame_gray,out;
	cvtColor( frame, frame_gray, CV_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray );
	face_cascade.detectMultiScale(frame_gray, faces, 1.3, 4, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));
	/*for( int i = 0; i < faces.size(); i++) 
		{
	        Point pt1(faces[i].x+faces[i].width,faces[i].y+faces[i].height);
                Point pt2(faces[i].x,faces[i].y);
                rectangle(frame,pt1,pt2,cv::Scalar(0,0,225),2,4,0);
                out=frame(Rect(faces[i].x,faces[i].y,faces[i].width,faces[i].height));
		}*/ 
        Mat smallImg;
        if(faces.size() == 0) return smallImg;
	out=frame(Rect(faces[0].x,faces[0].y,faces[0].width,faces[0].height));
        resize(out, smallImg, Size(128,128));
        return smallImg;
}

void AttributeDetection(const Mat img, std::vector<float> &data_cp);

int main()
{
   //cv::Mat frame=cv::imread("test.jpg");
   cv::VideoCapture cap(0);
   if(!cap.isOpened())  
          return -1;
   Mat frame;
   std::string winname = "camera";
   cv::namedWindow(winname,WINDOW_NORMAL);
   cv::setWindowProperty(winname, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
   while(1){
      
  cap >> frame;
  
  Mat img = detectAndDisplay(frame);
 
  if(! img.empty()) continue;
  std::string attribute[] ={"5_o_Clock_Shadow","Arched_Eyebrows","Attractive","Bags_Under_Eyes","Bald", "Bangs","Big_Lips","Big_Nose","Black_Hair","Blond_Hair","Blurry","Brown_Hair","Bushy_Eyebrows","Chubby","Double_Chin","Eyeglasses","Goatee","Gray_Hair", "Heavy_Makeup","High_Cheekbones","Male","Mouth_Slightly_Open","Mustache","Narrow_Eyes","No_Beard","Oval_Face","Pale_Skin","Pointy_Nose","Receding_Hairline","Rosy_Cheeks","Sideburns","Smiling","Straight_Hair",
 "Wavy_Hair","Wearing_Earrings","Wearing_Hat","Wearing_Lipstick","Wearing_Necklace","Wearing_Necktie","Young"};

std::vector<float> data;
AttributeDetection(img, data);

  for(int it = 0;it < data.size();it++)
    {
     std::cout << data[it] << std::endl;
	if(data[it] > 0)
	{
        attribute[it] += " : yes";
        putText(frame, attribute[it], Point( frame.rows/16,frame.cols/25+11*it),CV_FONT_HERSHEY_COMPLEX, 0.3, Scalar(0, 0, 255) ); 
        
	}		 
	else
        {
	attribute[it] += " : no";
        putText(frame, attribute[it], Point( frame.rows/16,frame.cols/25+11*it),CV_FONT_HERSHEY_COMPLEX, 0.3, Scalar(255, 0, 255) );
	//std::cout << attribute[it] << " : no"<<std::endl;
        }
    }	  
cv::imshow(winname, frame);
cv::waitKey(1);
}
return 0;  
 
}







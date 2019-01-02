

#include <iostream>
#include <cstring>
#include "Leap.h"
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<bits/stdc++.h>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <string>
#include<sstream>
#define PORT 8105

using namespace Leap;

using namespace std;

void reverse(char *str, int len) 
{ 
    int i=0, j=len-1, temp; 
    while (i<j) 
    { 
        temp = str[i]; 
        str[i] = str[j]; 
        str[j] = temp; 
        i++; j--; 
    } 
} 



int intToStr(int x, char str[], int d) 
{ 
    int i = 0; 
    while (x) 
    { 
        str[i++] = (x%10) + '0'; 
        x = x/10; 
    } 
  
    // If number of digits required is more, then 
    // add 0s at the beginning 
    while (i < d) 
        str[i++] = '0'; 
  
    reverse(str, i); 
    str[i] = '\0'; 
    return i; 
} 


char* ftoa1(float n, int afterpoint=4) 
{ 
    // Extract integer part 
    int ipart = (int)n; 
   char *res;
    // Extract floating part 
    float fpart = n - (float)ipart; 
  
    // convert integer part to string 
    int i = intToStr(ipart, res, 0); 
  
    // check for display option after point 
    if (afterpoint != 0) 
    { 
        res[i] = '.';  // add dot 
  
        // Get the value of fraction part upto given no. 
        // of points after dot. The third parameter is needed 
        // to handle cases like 233.007 
        fpart = fpart * pow(10, afterpoint); 
  
        intToStr((int)fpart, res + i + 1, afterpoint); 
    } 
} 
         
  
  int server_fd, new_socket, valread; 

struct sockaddr_in address;


class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);

  private:
};

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

void SampleListener::onInit(const Controller& controller) 
{
  std::cout << "Initialized" << std::endl;
}



void SampleListener::onConnect(const Controller& controller) 
{
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
}



void SampleListener::onDisconnect(const Controller& controller) 
{
  // Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}



void SampleListener::onExit(const Controller& controller) 
{
  std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) 
{
  // Get the most recent frame and report some basic information
  //cout<<"in frame\n";
  const Frame frame = controller.frame();
  /*std::cout << "Frame id: " << frame.id()
            << ", timestamp: " << frame.timestamp()
            << ", hands: " << frame.hands().count()
            << ", extended fingers: " << frame.fingers().extended().count()
            << ", tools: " << frame.tools().count()
            << ", gestures: " << frame.gestures().count() << std::endl;*/

  HandList hands = frame.hands();
  for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
    // Get the first hand
    const Hand hand = *hl;
    std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
    /*std::cout << std::string(2, ' ') << handType << ", id: " << hand.id()
              << ", palm position: " << hand.palmPosition() << std::endl;*/
    // Get the hand's normal vector and direction
    const Vector normal = hand.palmNormal();
    const Vector direction = hand.direction();

    // Calculate the hand's pitch, roll, and yaw angles
    /*std::cout << std::string(2, ' ') <<  "pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
              << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
              << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;*/

    // Get the Arm bone
    Arm arm = hand.arm();
    /*std::cout << std::string(2, ' ') <<  "Arm direction: " << arm.direction()
              << " wrist position: " << arm.wristPosition()
              << " elbow position: " << arm.elbowPosition() << std::endl;*/

    // Get fingers
    const FingerList fingers = hand.fingers();
    for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
      const Finger finger = *fl;
      /*std::cout << std::string(4, ' ') <<  fingerNames[finger.type()]
                << " finger, id: " << finger.id()
                << ", length: " << finger.length()
                << "mm, width: " << finger.width() << std::endl;*/

      // Get finger bones
     /*FILE*fptr;
     fptr=fopen("test.txt","w");
    if(fptr==NULL)
    std::cout<<"file open failed\n";*/
    //fstream  file; 
    //file.open("test1.txt",ios::out);
     
      
      char buffer[1024] = {0};
      int addrlen = sizeof(address);
      
      printf("herererererererer========\n");
      
      while(1)
	{
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 	
		{ 
			perror("accept"); 
			exit(EXIT_FAILURE); 
		} 
		
		char *spare = "Hi";
		int count = 0;
		while(1) 
		{
		count++;
		//printf("herererererererer========>>   count = %d\n\n",count);
			//valread = read( new_socket , buffer, 1024);
			    
      			for (int b = 0; b < 4; ++b) 
       			{
        		Bone::Type boneType = static_cast<Bone::Type>(b);
        		Bone bone = finger.bone(boneType);
        		/*std::cout << std::string(6, ' ') <<  boneNames[boneType]
                  << " bone, start: " << bone.prevJoint()
                  << ", end: " << bone.nextJoint()
                  << ", direction: " << bone.direction() << std::endl;*/
           		
           		//printf("%d++++++++++\n",b);
           		if(b == 1){
           		//Vector a = bone.nextJoint();
           		/*temp=boost::lexical_cast<std::string>(a.x);
           		temp.append(boost::lexical_cast<std::string>(a.y));*/
           		std::cout<<bone.nextJoint()<<"\n";
           		
           		char brac1[] = "(";
           		char xarr[20], yarr[20], zarr[20]; 
           		
           		sprintf(xarr, "%f", bone.nextJoint().x);
			sprintf(yarr, "%f", bone.nextJoint().y);
		        sprintf(zarr, "%f", bone.nextJoint().z);
           		
           		char *temp = (char*)malloc(100);
           		
           		strcpy(temp, brac1);
           		strcat(temp,xarr);
           		strcat(temp,",");
           		std::cout<<"ibun"<<endl;
           		strcat(temp,yarr);
           		strcat(temp,",");
           		strcat(temp,zarr);
           		strcat(temp,")");
           		spare = temp;
           		/*
                        printf("%s\n",buffer ); 
                        //char* c=temp.c_str();
                        char stri[100];
                        cin>>stri;*/
                        cout<<"fin"<<spare<<endl;
                        int a;
                        //cin>>a;
			send(new_socket , spare , strlen(spare) , 0 ); 
			//printf("Hello message sent\n"); 
                        //memset(temp,0,sizeof(temp));
                        free(temp);
             }
      			}
			
		}
       }

   /*FILE*fptr;
    fptr=fopen("test.txt","w");
     Bone::Type boneType = static_cast<Bone::Type>(1);
     Bone bone = finger.bone(boneType);
     fprintf(fptr,"%d", bone.nextJoint());*/
     //fclose(fptr);






    }
  }

  // Get tools
  const ToolList tools = frame.tools();
  for (ToolList::const_iterator tl = tools.begin(); tl != tools.end(); ++tl) {
    const Tool tool = *tl;
    /*std::cout << std::string(2, ' ') <<  "Tool, id: " << tool.id()
              << ", position: " << tool.tipPosition()
              << ", direction: " << tool.direction() << std::endl;*/
  }

  // Get gestures
  const GestureList gestures = frame.gestures();
  for (int g = 0; g < gestures.count(); ++g) {
    Gesture gesture = gestures[g];

    switch (gesture.type()) {
      case Gesture::TYPE_CIRCLE:
      {
        CircleGesture circle = gesture;
        std::string clockwiseness;

        if (circle.pointable().direction().angleTo(circle.normal()) <= PI/2) {
          clockwiseness = "clockwise";
        } else {
          clockwiseness = "counterclockwise";
        }

        // Calculate angle swept since last frame
        float sweptAngle = 0;
        if (circle.state() != Gesture::STATE_START) {
          CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
          sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
        }
        /*std::cout << std::string(2, ' ')
                  << "Circle id: " << gesture.id()
                  << ", state: " << stateNames[gesture.state()]
                  << ", progress: " << circle.progress()
                  << ", radius: " << circle.radius()
                  << ", angle " << sweptAngle * RAD_TO_DEG
                  <<  ", " << clockwiseness << std::endl;*/
        break;
      }
      case Gesture::TYPE_SWIPE:
      {
        SwipeGesture swipe = gesture;
        /*std::cout << std::string(2, ' ')
          << "Swipe id: " << gesture.id()
          << ", state: " << stateNames[gesture.state()]
          << ", direction: " << swipe.direction()
          << ", speed: " << swipe.speed() << std::endl;*/
        break;
      }
      case Gesture::TYPE_KEY_TAP:
      {
        KeyTapGesture tap = gesture;
        /*std::cout << std::string(2, ' ')
          << "Key Tap id: " << gesture.id()
          << ", state: " << stateNames[gesture.state()]
          << ", position: " << tap.position()
          << ", direction: " << tap.direction()<< std::endl;*/
        break;
      }
      case Gesture::TYPE_SCREEN_TAP:
      {
        ScreenTapGesture screentap = gesture;
        /*std::cout << std::string(2, ' ')
          << "Screen Tap id: " << gesture.id()
          << ", state: " << stateNames[gesture.state()]
          << ", position: " << screentap.position()
          << ", direction: " << screentap.direction()<< std::endl;*/
        break;
      }
      default:
        //std::cout << std::string(2, ' ')  << "Unknown gesture type." << std::endl;
        break;
    }
  }

  if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
    std::cout << std::endl;
  }

}







void SampleListener::onFocusGained(const Controller& controller) 
{
  std::cout << "Focus Gained" << std::endl;
}





void SampleListener::onFocusLost(const Controller& controller) 
{
  std::cout << "Focus Lost" << std::endl;
}



void SampleListener::onDeviceChange(const Controller& controller) 
{
  std::cout << "Device Changed" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) 
  {
    std::cout << "id: " << devices[i].toString() << std::endl;
    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }
}






void SampleListener::onServiceConnect(const Controller& controller) 
{
  std::cout << "Service Connected" << std::endl;
}




void SampleListener::onServiceDisconnect(const Controller& controller) 
{
  std::cout << "Service Disconnected" << std::endl;
}





int main(int argc, char** argv) 
{
  // Create a sample listener and controller
  SampleListener listener;
  Controller controller;
  
        struct sockaddr_in address; 
	int opt = 1; 
	 
	 
	cout<<"here";
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	else
	cout<<"socket created\n";
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	else
	cout<<"binding done\n";
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	
	cout<<"listening\n";
  
   controller.addListener(listener);

  if (argc > 1 && strcmp(argv[1], "--bg") == 0)
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();

  // Remove the sample listener when done
  controller.removeListener(listener);

  return 0;
}

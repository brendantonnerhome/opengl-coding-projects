#include <GL/freeglut.h>
#include <pthread.h>
#include <iostream>
#include "../include/socketHelper.hpp"
#include "../include/definitions.hpp"
#include <vector>
#include "../include/objParser.hpp"

//#include "socketHelper.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <signal.h>

#include "../include/imageLoader.hpp"

using namespace std;

vector<parsingData*> modelList;
const float BOX_SIZE = 0.2f;
float _angle = 0;
GLuint _textureId;


void* threadClient(void* data) {
    bSocket tClient;
    sleep(5);
    cout << "open Client socket" << endl;
    int socketNo  = tClient.bSocketClient("2348","localhost",1024);
    //cout << "socket=="<< tClient.getSocketNo() << endl;
    coordData coordsTest;
    coordsTest.x = 10;
    coordsTest.y = 12;
    coordsTest.z = 5;

    int len = send(socketNo,&coordsTest,sizeof(coordData),0);
    cout << "sent len=" << len << endl;
    //
    return NULL;
}

void* threadServer(void* data) {
    cout << "open server socket" << endl;
    bSocket tServer;
    int socketNo = tServer.bSocketServer("2348","localhost",1024);
    unsigned char buff[1024];
    int len = recv(socketNo,buff,sizeof(coordData),0);
    cout << "recv len=" << len << endl;
    coordData* coordsTest = (coordData*)buff;
    cout << "coordsTest="<<coordsTest->x<<","<<coordsTest->y<<","<<coordsTest->z << endl;

    return NULL;
}


int cleanUpModels(vector<parsingData*>& models){
	vector<parsingData*>::iterator rIT;

	for(rIT = models.begin(); rIT !=models.end() ; rIT++){
		delete *rIT;
	}
	//delete parseFile1;
	return 0;
}

vector<parsingData*> loadModels(vector<parsingData*>& models){
	//vector<parsingData> modelList = new vector<parsingData>;
	//parsingData* parseFile1 = new parsingData("modelData/models/brick.obj");
	//parsingData* parseFile1 = new parsingData("modelData/models/boringBox.obj");
//	models.push_back(parseFile1);

	//parsingData* parseFile2 = new parsingData("modelData/models/boringBox.obj");
	parsingData* parseFile2 = new parsingData("modelData/models/simple.obj");
	//parsingData* parseFile2 = new parsingData("modelData/models/brick.obj");
	models.push_back(parseFile2);
	//return 0;
	return models;
}

void handleResize2(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
	//windowH=h;
	//windowW=w;
}

void onKeypress(unsigned char key, int x, int y){
	switch (key) {
		case 27: //Escape key
			{
				exit(0);
				break;
			}
	}
}


void DisplayBrick(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glTranslatef(0.0f, 0.0f, -20.0f);
	glTranslatef(0.0f, 0.0f, -4.0f);

	GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat lightPos[] = {-2 * BOX_SIZE, BOX_SIZE, 4 * BOX_SIZE, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glRotatef(-_angle, 1.0f, 1.0f, 0.0f);
	vector<parsingData*>::iterator modelListI;
	//cout << "# models " <<modelList.size() << endl;
	
	for(modelListI = modelList.begin(); modelListI != modelList.end(); modelListI++){
		dbgModel(*modelListI);
		
		renderModel(*modelListI);
	}
	glBegin(GL_QUADS);
	/*
	//Top face
	glColor3f(1.0f, 1.0f, 0.0f);
	glNormal3f(0.0, 1.0f, 0.0f);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);

	//Bottom face
	glColor3f(1.0f, 0.0f, 1.0f);
	glNormal3f(0.0, -1.0f, 0.0f);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

	//Left face
	glNormal3f(-1.0, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);

	//Right face
	glNormal3f(1.0, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
	*/
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	/*
	//Front face
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);

	//Back face
	glNormal3f(0.0, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(BOX_SIZE / 2 , BOX_SIZE / 2, -BOX_SIZE / 2);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
	*/
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();

	return;
}


void Display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -2.0f);

	GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat lightPos[] = {-2 * BOX_SIZE, BOX_SIZE, 4 * BOX_SIZE, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	//glRotatef(-_angle, 1.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
	glutSolidTeapot(1);
	//Top face
	glColor3f(1.0f, 1.0f, 0.0f);
	glNormal3f(0.0, 1.0f, 0.0f);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);

	//Bottom face
	glColor3f(1.0f, 0.0f, 1.0f);
	glNormal3f(0.0, -1.0f, 0.0f);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

	//Left face
	glNormal3f(-1.0, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);

	//Right face
	glNormal3f(1.0, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	//Front face
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);

	//Back face
	glNormal3f(0.0, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();

	return;
	// Clear Screen And Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset The Current Modelview Matrix
    glLoadIdentity();

//NEW//////////////////NEW//////////////////NEW//////////////////NEW/////////////

    glTranslatef(-1.5f,0.0f,-6.0f);	// Move 1.5 Left And 6.0 Into The Screen.
    glBegin(GL_TRIANGLES);		// Drawing Using Triangles
	glVertex3f( 0.0f, 1.0f, 0.0f);		// Top
	glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
	glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
    glEnd();					// Finished Drawing

    glTranslatef(3.0f,0.0f,0.0f);			// Move Right
    glBegin(GL_QUADS);				// Draw A Quad
	glVertex3f(-1.0f, 1.0f, 0.0f);		// Top Left
	glVertex3f( 1.0f, 1.0f, 0.0f);		// Top Right
	glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
	glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
    glEnd();
	return;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//glEnable(GL_TEXTURE_2D);
	//colorFunction(1000,frameCount);

	// set a 2D orthographic projection
	//gluOrtho2D(0, windowW, windowH, 0);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glLoadIdentity();
	//if(record)
	//	renderSpacedBitmapString(windowW-200,windowH-50,2,GLUT_BITMAP_TIMES_ROMAN_24,"Brendan Tonner.");
	//else
	//renderSpacedBitmapString(windowW-200,windowH-50,2,GLUT_BITMAP_TIMES_ROMAN_24,"Brendan Tonner");

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat ambientColor[] = {0.3f, 0.3f, 0.3f, 1.0f}; //Color (0.2, 0.2, 0.2)
	//GLfloat fogColor[] = {0.9f, 0.9f, 0.9f, 1.0f}; //Color (0.2, 0.2, 0.2)
	//GLfloat ambientColor[] = {0.1f, 0.1f, 0.1f, 1.0f}; //Color (0.2, 0.2, 0.2)

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	//glFogf(GL_FOG_MODE, GL_EXP);
	//glFogf(GL_FOG_DENSITY, fogDense);
	//glFogfv(GL_FOG, fogColor);

	//GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	//GLfloat lightPos1[] = {0f, 0f,0f, 0.0f};


	//GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};

	//GLfloat lightPos1[] = {-1.0f, 0.5f, _angle, 0.0f};
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);


	//glPushMatrix();
	//glTranslatef(Tx, Ty, Tz);
   // glScalef(Sx, Sy, Sz);
    //glRotatef(Rz, 0, 0, 1);
    //glRotatef(Ry, 0, 1, 0);
   // glRotatef(Rx, 1, 0, 0);
    //glTranslatef(Ox, Oy, Oz);
	//glPopMatrix();
	/*
	static bool countdir= false;
	if(sunStep > 100){
		countdir = true;
	}
	else if(sunStep < -100){
		countdir = false;
	}
	if(countdir){
		sunStep -= 5;
	}
	else{
		sunStep += 5;
	}
	*/
	//lightsZ = sunStep;

	//lightsX = sunStep;
	//lightsY = sunStep;
	//lightsZ =  lightsZ - sunStep;
	//lightsX  = sqrt(200*200 - lightsZ*lightsZ);// - 20;
	//lightsY  = sqrt(200*200 - lightsZ*lightsZ);// - 20;
	//lightsZ = 100;
	//cout << "X: "<< lightsX << " Y: "<< lightsY << " Z: " << lightsZ << std::endl;
	//1010 1020 -508.3
	//-1160 -1150 -508


	glPushMatrix();



		glPushMatrix();

			//GLfloat lightPos0[] = {lightsX, lightsY, lightsZ, 1.0f};
			//GL_POINTS(lightsX, lightsY, lightsZ);
			glutSolidTeapot(1);
			//GLfloat lightColor0[] = {0.7f, 0.7f, 0.7f, 1.0f};
			//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);

			glScalef(.02,.02,.02);
			/*vector<parsingData*>::iterator modelListI;
			for(modelListI = modelList.begin(); modelListI != modelList.end(); modelListI++){
				renderModel(*modelListI);
			}*/

			//renderModel();
			//glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

			//lLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
			//glTranslatef(0.0f + 4*oSetX, -1.0f + 4*oSetY, -7.0f + 4*oSetZ);

			//old default translate
			//glTranslatef(-0.5f + 4*oSetX, -9.5f + 4*oSetY,-85.0f + 4*oSetZ);
			//glTranslatef(-6.0f + 4*oSetX, -5.0f + 4*oSetY,-20.0f + 4*oSetZ);

			//old default rotations
			/*
			glRotatef(rotX+ -67.5, 1, 0, 0);//X
			glRotatef(rotZ+ -78.75, 0, 0, 1);//Z
			glRotatef(rotY+0, 0, 1, 0);//Y
			*/
			//glRotatef(rotX+ -67.5, 1, 0, 0);//X
			//glRotatef(rotZ+ 0, 0, 0, 1);//Z
			//glRotatef(rotY+0, 0, 1, 0);//Y
			//glTranslatef(-4*oSetX,-4*oSetY,-4*oSetZ);
			//newCity.renderCity();
			//newParse.myGlRenderHelper();
				//

		glPopMatrix();

		//newCity.renderCity();

	glPopMatrix();

	//sunStep++;

	//unsigned char* test;
	//movName = "movie/mov     ";
	//movName[9] = '1';
	//using std::stringstream;
	//std::stringstream str;
	// string "1";
	//int  i = 10;
	//char Filename[256] = "File";
	//frameCount++;
	/*if(record){

		sprintf_s(movName,"movie/File%0003d\i.ppm",frameCount);
		glReadPixels(0,0,1280,720,GL_RGB,GL_UNSIGNED_BYTE, imageptr);
		PPM::Write(movName,imageptr,1280,720);
	}
	glutSwapBuffers();*/

}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 image->width, image->height,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 image->pixels);
	return textureId;
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	Image* image = loadBMP("modelData/vtr.bmp");
	_textureId = loadTexture(image);
	delete image;
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void update(int value) {
	_angle += 1.0f;
	if (_angle > 360) {
		_angle -= 360;
	}
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}


void* glThreadMain(void* data) {
    cout << "launching the rendering thread" << endl;
    cout << "commenceing..." << endl;
	loadModels(modelList);
	int argc=2;
	char* tmpstr = "main";
	char** argv={&tmpstr};// = {"main","2"};
	//glutInit(&argc, argv);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);

	glutCreateWindow("Brendan Tonner - Brick Layer");
	initRendering();

	//glutDisplayFunc(Display);
	glutDisplayFunc(DisplayBrick);
	glutKeyboardFunc(onKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	glutMainLoop();
	cleanUpModels(modelList);
	return 0;


/*




	cout << "commenceing..." << endl;
	//vector<parsingData> modelList =
	loadModels(modelList);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Brendan Tonner - Brick Layer");

	initRendering();

	//Set handler functions
	glutDisplayFunc(Display);
	glutKeyboardFunc(onKeypress);
	glutReshapeFunc(handleResize);

	//glutTimerFunc(1000, update_vehicle, 0);

	glutMouseFunc(processMouse);

	glutMainLoop();

	cout << "program exiting..." << endl;
	cleanUpModels(modelList);
	return 0;*/
    return NULL;
}


    threadListObj::threadListObj() {
        this->threadInit();
    }
    threadListObj::~threadListObj() {
        this->threadCleanUp();
    }

    void threadListObj::threadInit(void) {
        this->threadList = new pthread_t[numPThreads];
        for(unsigned int i=0; i<numPThreads; i++) {
            switch(i) {
            case serverServer:
                 //pthread_create(&threadList[i],NULL,threadServer,NULL);
                break;
             case serverClient:
                 //pthread_create(&threadList[i],NULL,threadClient,NULL);
                break;
            case glThread:
                pthread_create(&threadList[i],NULL,glThreadMain,NULL);
                break;
            default:
                cout << "error thread creation attempted for undefined thread"<<endl;
                exit(0);

                break;
            }
        }
        return;
    }


    void threadListObj::threadCleanUp(void) {
        for(unsigned int i=0; i<numPThreads; i++) {
            pthread_join(this->threadList[i], NULL);
        }
    }

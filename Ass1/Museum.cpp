//  ========================================================================
//  Finn McCartney (98899086).
//  Skeleton from COSC363 Lab 2 UNiversity of Canterbury.
//
//  FILE NAME: Museum.cpp
//  ========================================================================
 
#include <iostream>
#include <fstream>
#include <cmath> 
#include <math.h>
#include <GL/freeglut.h>
#include "loadBMP.h"
using namespace std;
#define GL_CLAMP_TO_EDGE 0x812F

//--Globals ---------------------------------------------------------------
float angle=0, look_x, look_z=-1.5, eye_x, eye_z=30;  //Camera parameters
GLuint txId[7];   //Texture ids
GLUquadric *q; //allows round objects

// ------boat animatio variables ------------
float boatz = 0.0; //boat movement variable
int boatTheta = 0; //boat rotation variable
int boatDir = 1; // direction of boat travel
int boatFunc = 1; //rotate or translate
int boatx = 2; //side of course boat is on
int boatFace = 90; //direction boat is facing in

//--------------guard animation variables ----------------
int guardTheta = 0; // angle for gaurd arm movement
int movingIn = 1; //arm raising trigger

//------------------helicopter animation variables-------------------
int bladeTheta = 1; //angle for continuoes blade rotation
float heliPos = -30.5; //position of helicopter on z axis
int inLine = 0; //helicopter in line with player


//------Function to load a texture in bmp format  ------------------------
void loadTexture()
{
    glEnable(GL_TEXTURE_2D);
    glGenTextures(7, txId); 	// Create 6 texture ids

    // Create a Texture object
    glBindTexture(GL_TEXTURE_2D, txId[0]);		//Use this texture
    loadBMP("tropday_down.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Create a Texture object
    glBindTexture(GL_TEXTURE_2D, txId[1]);		//Use this texture
    loadBMP("tropday_up.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Create a Texture object
    glBindTexture(GL_TEXTURE_2D, txId[2]);		//Use this texture
    loadBMP("tropday_front.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Create a Texture object
    glBindTexture(GL_TEXTURE_2D, txId[3]);		//Use this texture
    loadBMP("tropday_right.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Create a Texture object
    glBindTexture(GL_TEXTURE_2D, txId[4]);		//Use this texture
    loadBMP("tropday_back.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Create a Texture object
    glBindTexture(GL_TEXTURE_2D, txId[5]);		//Use this texture
    loadBMP("tropday_left.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, txId[6]);		//Use this texture
    loadBMP("water.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


}

//--Draws 6 surfaces and attaches textures -------------------------------
void drawSkyBox()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[0]);

    glBegin(GL_QUADS);
        //---- floor ----
        glTexCoord2f(0., 0.); glVertex3f(-80, 0, -80);
        glTexCoord2f(0., 1.); glVertex3f(-80, 0, 80);
        glTexCoord2f(1., 1.); glVertex3f(80, 0, 80);
        glTexCoord2f(1., 0.); glVertex3f(80, 0, -80);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, txId[1]);

    glBegin(GL_QUADS);

        //---- cieling ----
        glTexCoord2f(0., 1.); glVertex3f(-80, 80, -80);
        glTexCoord2f(0., 0.); glVertex3f(-80, 80, 80);
        glTexCoord2f(1., 0.); glVertex3f(80, 80, 80);
        glTexCoord2f(1., 1.); glVertex3f(80, 80, -80);
   glEnd();

   glBindTexture(GL_TEXTURE_2D, txId[2]);

   glBegin(GL_QUADS);

        //---- north ----
        glTexCoord2f(1., 0.); glVertex3f(-80, 0, -80);
        glTexCoord2f(1., 1.); glVertex3f(-80, 80, -80);
        glTexCoord2f(0., 1.); glVertex3f(80, 80, -80);
        glTexCoord2f(0., 0.); glVertex3f(80, 0, -80);
   glEnd();

   glBindTexture(GL_TEXTURE_2D, txId[3]);

   glBegin(GL_QUADS);

        //---- east----
        glTexCoord2f(1., 0.); glVertex3f(80, 0, -80);
        glTexCoord2f(1., 1.); glVertex3f(80, 80, -80);
        glTexCoord2f(0., 1.); glVertex3f(80, 80, 80);
        glTexCoord2f(0., 0.); glVertex3f(80, 0, 80);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, txId[4]);

    glBegin(GL_QUADS);

        //---- south ----
        glTexCoord2f(0., 0.); glVertex3f(-80, 0, 80);
        glTexCoord2f(0., 1.); glVertex3f(-80, 80, 80);
        glTexCoord2f(1., 1.); glVertex3f(80, 80, 80);
        glTexCoord2f(1., 0.); glVertex3f(80, 0, 80);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, txId[5]);

    glBegin(GL_QUADS);

        //---- west ----
        glTexCoord2f(0., 0.); glVertex3f(-80, 0, -80);
        glTexCoord2f(0., 1.); glVertex3f(-80, 80, -80);
        glTexCoord2f(1., 1.); glVertex3f(-80, 80, 80);
        glTexCoord2f(1., 0.); glVertex3f(-80, 00, 80);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawPillars()
{
    glColor3ub(100, 100, 100);		//pillars
    glPushMatrix();
      glScalef(1, 5, 1);
      glTranslatef(-20, 0, 0);
      glutSolidSphere(3, 40, 40);
    glPopMatrix();

    glPushMatrix();
      glScalef(1, 5, 1);
      glTranslatef(-10, 0, 0);
      glutSolidSphere(3, 40, 40);
    glPopMatrix();

    glPushMatrix();
      glScalef(1, 5, 1);
      glTranslatef(10, 0, 0);
      glutSolidSphere(3, 40, 40);
    glPopMatrix();

    glPushMatrix();
      glScalef(1, 5, 1);
      glTranslatef(20, 0, 0);
      glutSolidSphere(3, 40, 40);
    glPopMatrix();
}

void drawWalls()
{


    glPushMatrix(); //left wall
        glTranslatef(-20, 6, -28);
        glScalef(1, 12, 40);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix(); //right wall
        glTranslatef(20, 6, -28);
        glScalef(1, 12, 40);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix(); //back wall
        glTranslatef(0, 6, -48);
        glScalef(40, 12, 1);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix(); //front wall (left)
        glTranslatef(-13, 6, -8);
        glScalef(15, 12, 1);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix(); //front wall (right)glVertex3f(0, 3.5, 0.5);
        glTranslatef(13, 6, -8);
        glScalef(15, 12, 1);
        glutSolidCube(1);
    glPopMatrix();

}

//--Draw interior walls and lights ----
void drawInterior()
{
    float lgt_pos_1[] = {-50.0f, 0.0f, 0.0f, 0.0f};

    glPushMatrix(); //left rail
        glTranslatef(-6, 0.5, -28);
        glScalef(1, 3, 40);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix(); //right rail
        glTranslatef(6, 0.5, -28);
        glScalef(1, 3, 40);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix(); //left wall
        glTranslatef(-13, 6, -28);
        glScalef(15, 12, 1);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix(); //right wall
        glTranslatef(13, 6, -28);
        glScalef(15, 12, 1);
        glutSolidCube(1);
    glPopMatrix();

   glPushMatrix(); //light left/top
        glTranslatef(-13, 11, -17.5);
        glRotatef(-90, 1, 0, 0);
        gluCylinder(q, 1, 0.5, 1, 30, 30);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0.01);
        glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos_1);
    glPopMatrix();

    glPushMatrix(); //light right/top
         glTranslatef(13, 11, -17.5);
         glRotatef(-90, 1, 0, 0);
         gluCylinder(q, 1, 0.5, 1, 30, 30);
         glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
         glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0.01);
         glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos_1);
     glPopMatrix();

     glPushMatrix(); //light left/bot
          glTranslatef(-13, 11, -38);
          glRotatef(-90, 1, 0, 0);
          gluCylinder(q, 1, 0.5, 1, 30, 30);
          glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
          glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0.01);
          glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos_1);
      glPopMatrix();

      glPushMatrix(); //light right/bot
           glTranslatef(13, 11, -38);
           glRotatef(-90, 1, 0, 0);
           gluCylinder(q, 1, 0.5, 1, 30, 30);
           glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
           glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0.01);
           glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos_1);
       glPopMatrix();


}

//--Draws the museum model for animations to be placeed in ------------------
void drawMuseum()
{ 
    drawPillars();

    drawWalls();

    drawInterior();

    glPushMatrix(); //floor
        glBegin(GL_QUADS);
        glVertex3f(-20, 0.5, -8);
        glVertex3f(-20, 0.5, -48);
        glVertex3f(20, 0.5, -48);
        glVertex3f(20, 0.5, -8);

        glVertex3f(-20, 0, -8);
        glVertex3f(-20, 0.5, -8);
        glVertex3f(20, 0.5, -8);
        glVertex3f(20, 0, -8);
        glEnd();
    glPopMatrix();

    glPushMatrix(); //roof
        glTranslatef(0, 12, 2);
        glPushMatrix();
            glBegin(GL_TRIANGLES);
                glVertex3f(-25, 0, 0);
                glVertex3f(0, 15, 0);
                glVertex3f(25, 0, 0);

                glVertex3f(-25, 0, -50);
                glVertex3f(0, 15, -50);
                glVertex3f(25, 0, -50);
            glEnd();

            glBegin(GL_QUADS);
                glVertex3f(-25, 0, 0);
                glVertex3f(0, 15, 0);
                glVertex3f(-25, 0, -50);
                glVertex3f(0, 15, -50);

                glVertex3f(-25, 0, 0);
                glVertex3f(-25, 0, -50);
                glVertex3f(25, 0, -50);
                glVertex3f(25, 0, 0);

                glVertex3f(25, 0, 0);
                glVertex3f(25, 0, -50);
                glVertex3f(0, 15, -50);
                glVertex3f(0, 15, 0);
            glEnd();

    glPopMatrix();

}

//----------animations-----------------------------
void drawBoat()
{
    //draw simple sail boat
    glPushMatrix();

        glColor3f(0.3, 0.15, 0.);

        //base
        glBegin(GL_QUADS);

            glVertex3f(-1.5, 1, 0); // top
            glVertex3f(1.5, 1, 0);
            glVertex3f(1.5, 1, 1);
            glVertex3f(-1.5, 1, 1);

            glVertex3f(-1.5, 1, 1); // side
            glVertex3f(1.5, 1, 1);
            glVertex3f(1, 0, 1);
            glVertex3f(-1, 0, 1);

            glVertex3f(-1.5, 1, 0); // side
            glVertex3f(1.5, 1, 0);
            glVertex3f(1, 0, 0);
            glVertex3f(-1, 0, 0);

            glVertex3f(1.5, 1, 1); // front
            glVertex3f(1.5, 1, 0);
            glVertex3f(1, 0, 0);
            glVertex3f(1, 0, 1);

            glVertex3f(-1.5, 1, 1); // back
            glVertex3f(-1.5, 1, 0);
            glVertex3f(-1, 0, 0);
            glVertex3f(-1, 0, 1);

            glVertex3f(-1, 0, 0);
            glVertex3f(1, 0, 0);
            glVertex3f(1, 0, 1);
            glVertex3f(-1, 0, 1);
        glEnd();

        //cabin
        glPushMatrix();
            glTranslatef(0, 1, 0.5);
            glScalef(1, 1, 0.9);
            glutSolidCube(1);
        glPopMatrix();

        //mast
        glPushMatrix();
            glTranslatef(0, 2, 0.5);
            glScalef(1, 15, 1);
            glutSolidCube(0.2);
        glPopMatrix();

        //sail
        glPushMatrix();
            glColor3d(250, 250, 250);
            glBegin(GL_TRIANGLES);
                glVertex3f(0, 1.7, 0.5);
                glVertex3f(2, 1.7, 0.5);
                glVertex3f(0, 3.5, 0.5);
            glEnd();
        glPopMatrix();


    glPopMatrix();


}

//water for boat animation
void drawWater()
{

    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, txId[6]);

    glPushMatrix();
        glColor3f(0, 0, 1);

        glBegin(GL_QUADS); // water
            glTexCoord2f(1., 0.); glVertex3f(-6.5, 0, 9.5);
            glTexCoord2f(1., 1.); glVertex3f(-6.5, 0, -9.5);
            glTexCoord2f(0., 1.); glVertex3f(6.5, 0, -9.5);
            glTexCoord2f(0., 0.); glVertex3f(6.5, 0, 9.5);

            glVertex3f(-6.5, 0, 9.5);
            glVertex3f(-6.5, -4, 9.5);
            glVertex3f(-6.5, -4, -9.5);
            glVertex3f(-6.5, 0, -9.5);


        glEnd();

        glPushMatrix();// boeys
             glColor3f(1, 0, 0);
             glTranslatef(0, 0, 5);
             glutSolidSphere(1, 30, 30);
        glPopMatrix();

        glPushMatrix();
            glColor3f(1, 0, 0);
            glTranslatef(0, 0, -5);
            glutSolidSphere(1, 30, 30);
        glPopMatrix();

    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
}

// sail boat that races around boeys
void boatAnimation()
{
    glTranslatef(13, -10, -40);
    glPushMatrix();
        glPushMatrix();
            glTranslatef(0, 0, boatz);
            glRotatef(-boatTheta, 0, 1, 0);
            glTranslatef(boatx, 0, 0);
            glRotated(boatFace, 0, 1, 0);
            drawBoat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, -boatz);
            glRotatef(-boatTheta, 0, 1, 0);
            glTranslatef(-boatx, 0, 0);
            glRotated(-boatFace, 0, 1, 0);
            drawBoat();
        glPopMatrix();

        drawWater();
     glPopMatrix();
}

//draw single guard hold stick
void drawGuard()
{
    glPushMatrix();

        glColor3f(1., 0.78, 0.06);		//Head
        glPushMatrix();
          glTranslatef(0, 7.7, 0);
          glutSolidCube(1.4);
        glPopMatrix();

        glColor3f(1., 0., 0.);			//Torso
        glPushMatrix();
          glTranslatef(0, 5.5, 0);
          glScalef(3, 3, 1.4);
          glutSolidCube(1);
        glPopMatrix();

        glColor3f(0., 0., 1.);			//Right leg
        glPushMatrix();
          glTranslatef(-0.8, 4, 0);
          glTranslatef(0.8, -4, 0);
          glTranslatef(-0.8, 2.2, 0);
          glScalef(1, 4.4, 1);
          glutSolidCube(1);
        glPopMatrix();

        glColor3f(0., 0., 1.);			//Left leg
        glPushMatrix();
        glTranslatef(0.8, 4, 0);
          glTranslatef(-0.8, -4, 0);
          glTranslatef(0.8, 2.2, 0);
          glScalef(1, 4.4, 1);
          glutSolidCube(1);
        glPopMatrix();

        glColor3f(1., 0.78, 0.06);		//Left arm
        glPushMatrix();
          glTranslatef(2, 6.5, 0);
          glTranslatef(-2, -6.5, 0);
          glTranslatef(2, 5, 0);
          glScalef(1, 4, 1);
          glutSolidCube(1);
        glPopMatrix();

        glTranslated(-2, 6.5, 0);
        glRotatef(-guardTheta, 1, 0, 0);
        glTranslatef(2, -6.5, 2);
        glPushMatrix(); //portion to rotate
            glColor3f(1., 0.78, 0.06);		//Right arm
            glPushMatrix();
              glTranslatef(-2, 6.5, 0);
              glRotatef(90, 1, 0, 0);
              glScalef(1, 4, 1);
              glutSolidCube(1);
            glPopMatrix();

            glColor3f(0.3, 0.15, 0.); //stick
            glPushMatrix();
                glTranslatef(-2, 6.5, 6);
                glScalef(0.25, 0.5, 12);
                glutSolidCube(1);
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();

}

//gaurds who raise sticks for you to enter museum
void guardAnimation()
{
    glPushMatrix();
        glTranslatef(13, 0, -17.5);
        glRotatef(-90, 0, 1, 0);
        drawGuard();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-13, 0, -17.5);
        glRotatef(90, 0, 1, 0);
        drawGuard();
    glPopMatrix();

}

//draw helicopter blade that will continously rotate
void drawBlade()
{
    glPushMatrix();

        glPushMatrix();
            glTranslatef(0, 0, 1.5);
            glScalef(0.5, 0.2, 3);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, -1.5);
            glScalef(0.5, 0.2, 3);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(1.5, 0, 0);
            glRotatef(90, 0, 1, 0);
            glScalef(0.5, 0.2, 3);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-1.5, 0, 0);
            glRotatef(90, 0, 1, 0);
            glScalef(0.5, 0.2, 3);
            glutSolidCube(1);
        glPopMatrix();

        glutSolidSphere(0.25, 30, 30);

    glPopMatrix();

}

//draw helicopter body
void drawHeli()
{
    glPushMatrix();

        glPushMatrix();//blade support sphere
            glTranslatef(-2.25, 0, 0);
            glutSolidSphere(0.2, 30, 30);
        glPopMatrix();

        glPushMatrix(); //blade support
            glTranslatef(-1, 0, 0);
            glRotatef(-90, 0, 1, 0);
            gluCylinder(q, 0.4, 0.2, 1.25, 30, 30);
        glPopMatrix();

        glPushMatrix(); //mast thing
            glColor3f(1, 0, 0);
            glTranslatef(0, 0.5, 0);
            glRotatef(-90, 1, 0, 0);
            gluCylinder(q, 0.3, 0.1, 0.75, 30, 30);
        glPopMatrix();

        glPushMatrix(); //cockpit
            glColor3f(0, 0, 1);
            glTranslatef(1, 0, 0);
            glScalef(1.5, 1, 1);
            glutSolidSphere(0.55, 30, 30);
        glPopMatrix();

        glPushMatrix(); //body
            glColor3f(1, 0, 0);
            glScalef(2, 1, 1);
            glutSolidCube(1);
        glPopMatrix();


    glPopMatrix();
}

//helicopter that follows user
void heliAnimation()
{
    glTranslatef(-13, 4, heliPos);
    glPushMatrix();
        drawHeli();

        glPushMatrix(); //side blade mechanics
            glTranslatef(-2.25, 0, 0.2);
            glRotatef(-8, 0, 1, 0);
            glRotatef(90, 1, 0, 0);
            glRotatef(-bladeTheta, 0, 1, 0);
            glScalef(0.25, 0.25, 0.25);
            drawBlade();
        glPopMatrix();

        glPushMatrix(); //top blade mechanics
            glTranslatef(0, 1.25, 0);
            glRotatef(-bladeTheta, 0, 1, 0);
            glScalef(0.75, 0.75, 0.75);
            drawBlade();
        glPopMatrix();

    glPopMatrix();
}

//--Display: ---------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display()  
{

	float lpos[4] = {10., 10., 10., 1.0};  //light's position

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye_x, 5, eye_z,  look_x, 5, look_z,   0, 1, 0);
	glLightfv(GL_LIGHT0,GL_POSITION, lpos);   //Set light position

    glRotatef(angle, 0.0, 1.0, 0.0);  //Rotate the scene about the y-axis

    glDisable(GL_LIGHTING);//Disable lighting when drawing floor.

    drawSkyBox();

	glEnable(GL_LIGHTING);	       //Enable lighting when drawing the model

    drawMuseum();

    boatAnimation();

    guardAnimation();

    heliAnimation();

	glFlush();
}

//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
    q = gluNewQuadric();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//Background colour

    loadTexture();

	glEnable(GL_LIGHTING);					//Enable OpenGL states
	glEnable(GL_LIGHT0);
 	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 1000.0);   //Camera Frustum
}

//------------ Special key event callback ---------------------------------
void special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT) angle -= 0.05;  //Change direction
    else if(key == GLUT_KEY_RIGHT) angle += 0.05;
    else if(key == GLUT_KEY_DOWN)
    {  //Move backward
        eye_x -= 2 * (0.1*sin(angle));
        eye_z += 2 * (0.1*cos(angle));
    }
    else if(key == GLUT_KEY_UP)
    { //Move forward
        eye_x += 2 * (0.1*sin(angle));
        eye_z -= 2 * (0.1*cos(angle));
    } else if(key == GLUT_KEY_PAGE_UP)
    { //move negatively along z axis
        eye_z -= 0.2;
    } else if(key == GLUT_KEY_PAGE_DOWN)
    { //move positively along z axis
        eye_z += 0.2;
    }

    look_x = eye_x + 100*sin(angle);
    look_z = eye_z - 100*cos(angle);
    glutPostRedisplay();
}

//update boat rotation around boey
void boatRotateTimer()
{
    if (boatTheta >= 180)
    {
        boatTheta = 0;
        if (boatz >= 5)
        {
            boatz = 4.8;
            boatx = -2;
            boatFace = -90;
        } else {
            boatz = -4.8;
            boatx = 2;
            boatFace = 90;
        }
        boatFunc = 1;
    } else {

        boatTheta += 3.5;
    }
}

//---update boat movement
void boatTimer()
{
    if (boatz >= 5 || boatz <= -5)
    {
        boatFunc = -1;

        if (boatz >= 5) {
            boatDir = -1;
        }
        if (boatz <= -5) {
            boatDir = 1;
        }
    } else {
        if (boatDir == 1) {
            boatz += 0.2;
        } else {
            boatz -= 0.2;
        }
    }

}

//----------------------guard arm movement ------------------
void raiseArm()
{
    if (guardTheta >= 20)
    {
        movingIn = 0;
    }
    if (movingIn == 1)
    {
        guardTheta += 2;
    }

}

void lowerArm()
{
    if (guardTheta <= 0)
    {
        movingIn = 1;
    }
    if (movingIn == 0)
    {
        guardTheta -= 2;
    }
}

//move heli inline with player
void moveHeli()
{

        if (eye_z > heliPos) {
                heliPos += 0.1;
        } else {
                heliPos -= 0.1;
        }

}

//select functions to run
void callFunctions(int value)
{
    if (boatFunc == 1) //if boat should be moving or rotating
    {
        boatTimer();
    } else {
        boatRotateTimer();
    }

    if (eye_z < -5 && eye_z > -30 && movingIn == 1) //if approaching entrance
    {
        raiseArm();
    }
    if (!(eye_z < -5 && eye_z > -30) && movingIn == 0) //if approaching entrance
    {
        lowerArm();
    }


    if (eye_z < -30.5 && eye_z > -45) {

        moveHeli();

    }

    bladeTheta += 20; //keep helicopter blades spinning

    glutPostRedisplay();
    glutTimerFunc(50, callFunctions, 0);
}

//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH);
   glutInitWindowSize (600, 600); 
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("Humanoid");
   initialize();
   glutTimerFunc(50, callFunctions, 0);
   glutDisplayFunc(display);
   glutSpecialFunc(special); 
   glutMainLoop();
   return 0;
}

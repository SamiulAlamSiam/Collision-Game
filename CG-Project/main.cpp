#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <math.h>
#include<string.h>
#include<windows.h>

#define PI 3.14159
#define GAME_SCREEN 0			//Constant to identify background color
#define MENU_SCREEN 4
#define MAX_STONES  100
#define MAX_STONE_TYPES 5
#define stoneRotationSpeed 5
#define SPACESHIP_SPEED 20
int stoneTranslationSpeed=2;

GLint m_viewport[4];
GLint CI=0;
int x,y;
int i;
int randomStoneIndices[100];
int index;
int Score=0;
int alienLife=100;
int GameLvl= 1;
float mouseX ,mouseY ;				//Cursor coordinates;
float LaserAngle=0 ,stoneAngle =0,lineWidth = 1;
float xOne=0,yOne=0;				//Spaceship coordinates
float xStone[MAX_STONES] ,yStone[MAX_STONES];//coordinates of stones
float xHealthBarStart = 750;				//Health bar starting coodinate
GLint stoneAlive[MAX_STONES];		//check to see if stone is killed

bool mButtonPressed= false,startGame=false,gameOver=false;		//boolean values to check state of the game
bool startScreen = true ,nextScreen=false,previousScreen=false;
bool gameQuit = false,instructionsGame = false, optionsGame = false;

//GLfloat a[][2]={0,-50, 70,-50, 70,70, -70,70};

int spaceshipX = 200, spaceshipY = 200;
char highScore[100],ch;
void display();
void StoneGenerate();
void displayRasterText(float x ,float y ,float z ,char *stringToDisplay) {
	int length;
	glRasterPos3f(x, y, z);
		length = strlen(stringToDisplay);

	for(int i=0 ;i<length ;i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,stringToDisplay[i]);
	}
}
void SetDisplayMode(int modeToDisplay) {
		switch(modeToDisplay){
		case GAME_SCREEN: glClearColor(0, 0, 0, 1);break;
		case MENU_SCREEN : glClearColor(0.3, 0 , 0.8, 1);break;
	}
}
void initializeStoneArray() {
	//random stones index

	for(int i = 0;i < MAX_STONES ;i++) {
		randomStoneIndices[i]=rand()%MAX_STONE_TYPES;
		stoneAlive[i]=true;
	}

	xStone[0] = -(200*MAX_STONES)-600;             //START LINE for stone appearance

	for(int i = 0;i<MAX_STONES ;i++) {				//ramdom appearance yIndex for each stone
		yStone[i]=rand()%600;
		if(int(yStone[i])%2)
			yStone[i]*=-1;
		xStone[i+1] = xStone[i] + 200;				//xIndex of stone aligned with 200 units gap
	}
}
void DrawSpaceshipBody()
{

    glPushMatrix();

    glColor3f(0.0,0.0,1.0);
    glScalef(25,50,1);
    glRotatef(90,0, 0, 1);
    glTranslated(0, 0, 0);
    glutSolidSphere(1,3,50);
    glPopMatrix();


	glPushMatrix();
	//glScalef(70,20,1);
    //glutSolidSphere(1,4,50);
	//glRotatef(90 ,0, 0, 1);
	glColor3f(0.39, 0.42, 0.67);
	//glPopMatrix();
    glScalef(70,25,1);
    glRotatef(90,0, 0, 1);
    glTranslated(0, 0, 0);
    glutSolidSphere(1,3,50);


    glPopMatrix();

    glPushMatrix();

    glColor3f(1.0,0.0,0.0);
    //glScalef(5,5,1);
    //glRotatef(90,0, 0, 1);

    glBegin(GL_QUADS);
        glVertex2f(35,-5);
        glVertex2f(45,-5);
        glVertex2f(45,-10);
        glVertex2f(35,-10);

        glEnd();


    glPopMatrix();


    glPushMatrix();

    glColor3f(1.0,0.0,0.0);
     glBegin(GL_QUADS);
        glVertex2f(35,5);
        glVertex2f(45,5);
        glVertex2f(45,0);
        glVertex2f(35,0);

        glEnd();


    glPopMatrix();
}

void DrawLazerBeam() {

	float xMid = -70;
    float yMid = 0;


	float mouseXEnd = -((- mouseX) + xOne);
	float mouseYEnd = -((- mouseY) + yOne);
	glLineWidth(5);   //----Laser beam width

	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
		glVertex2f(xMid ,yMid);
		glVertex2f(mouseXEnd ,mouseYEnd);
	glEnd();
	glLineWidth(1);
}
void DrawStone(int StoneIndex)
{
	glPushMatrix();
	glLoadIdentity();
	switch(StoneIndex)                           //CHANGE INDEX VALUE FOR DIFFERENT STONE VARIETY;
	{
	/*case 0:

		glTranslated(xStone[index] , yStone[index] ,0);
		glRotatef(stoneAngle ,0, 0, 1);
		glTranslated(0, 0, 0);
		glColor3f(0.0f, 1.0f, 0.3f);
		glScalef(35,35,1);
		glutSolidSphere(1,9,50);

        glLoadIdentity();
		glTranslated(xStone[index] , yStone[index] ,0);
		glRotatef(stoneAngle ,0, 0, 1);
		glTranslated(0, 0, 0);
		glScalef(60,10,1);
		glutSolidSphere(1,5,50);

		glLoadIdentity();
		glTranslated(xStone[index] , yStone[index] ,0);
		glRotatef(stoneAngle ,0, 0, 1);
		glTranslated(0, 0, 0);
		glScalef(10,60,1);
		glutSolidSphere(1,5,50);
		break;

	case 1:   //batman
		glColor3f(1.0f, 0.2f, 0.0f);
		glTranslated(xStone[index] , yStone[index] ,0);
		glRotatef(stoneAngle ,0, 0, 1);
		glTranslated(0, 0, 0);
		glScalef(30,30,1);
		glutSolidSphere(1,10,50);

		glLoadIdentity();
		glColor3f(0.8f, 0.8f, 0.1f);
		glTranslated(xStone[index] , yStone[index] ,0);
		glRotatef(stoneAngle ,0, 0, 1);
		glTranslated(0, 0, 0);
		glScalef(50,5,1);
		glutSolidSphere(1,20,50);
		break;*/

	case 2:    //space obj
		glColor3f(0.6f, 0.78f, 0.85f);
		glTranslated(xStone[index] , yStone[index] ,0);
		glRotatef(270,0, 0, 1);
		glTranslated(0, 0, 0);
		glScalef(60,25,1);
		glutSolidSphere(1,3,50);

		glLoadIdentity();
		glTranslated(xStone[index] , yStone[index] ,0);
		glRotatef(270,0, 0, 1);
		glTranslated(0, 0, 0);
		glScalef(25,60,1);
		glutSolidSphere(1,3,50);

		break;

	/*case 3://square shape
		glColor3f(0.8f, 0.8f, 0.1f);
		glTranslated(xStone[index] , yStone[index] ,0);
		glRotatef(stoneAngle ,0, 0, 1);
		glTranslated(0, 0, 0);
		glScalef(40,30,1);
		glutSolidSphere(1,3,7);


		glLoadIdentity();
		glTranslated(xStone[index] , yStone[index] ,0);
		glRotatef(stoneAngle ,0, 0, 1);
		glTranslated(0, 0, 0);
		glScalef(-40,-30,1);
		glutSolidSphere(1,3,7);
		break;
	case 4:
		glColor3f(1.0f, 0.85f, 0.3f);
		glTranslated(xStone[index] , yStone[index] ,0);
		glRotatef(stoneAngle ,0, 0, 1);
		glTranslated(0, 0, 0);
		glScalef(10,55,1);
		glutSolidSphere(1,9,50);

		glLoadIdentity();
		glTranslated(xStone[index] , yStone[index] ,0);
		glRotatef(stoneAngle ,0, 0, 0);
		glTranslated(0, 0, 0);
		glScalef(20,30,1);
		glutSolidSphere(1,6,50);
		glLoadIdentity();

		glTranslated(xStone[index] , yStone[index] ,0);
		glRotatef(stoneAngle+45 ,0, 0, 1);
		glTranslated(0, 0, 0);
		glScalef(25,40,1);
		glutSolidSphere(1,4,50);
		break;*/
	}
	glPopMatrix();
}
bool checkIfSpaceShipIsSafe() {
		for(int i = 0 ;i<MAX_STONES ;i++) {
		if(stoneAlive[i]&((xOne >= (xStone[i]/2 -70) && xOne <= (xStone[i]/2 + 70) && yOne >= (yStone[i]/2 -18 ) && yOne <= (yStone[i]/2 + 53)) || (yOne <= (yStone[i]/2 - 20) && yOne >= (yStone[i]/2 - 90) && xOne >= (xStone[i]/2 - 40) && xOne <= (xStone[i]/2 + 40))))
		{
			stoneAlive[i]=0;
			return false;
		}
	}
	return true;
}
void SpaceshipCreate(){
	glPushMatrix();
	glTranslated(xOne,yOne,0);
	if(!checkIfSpaceShipIsSafe() && alienLife ){
		alienLife-=10;
		xHealthBarStart -= 120;

		//PlaySound("E://cg codes/test/collision.wav", NULL, SND_ASYNC|SND_FILENAME);
	}
//	DrawSpaceshipDoom();
	glPushMatrix();
	glTranslated(4,19,0);
//	DrawAlien();
	glPopMatrix();
//	DrawSteeringWheel();
	DrawSpaceshipBody();
//	DrawSpaceShipLazer();
	if(mButtonPressed) {
		DrawLazerBeam();
	}
	glEnd();
	glPopMatrix();
}
void DisplayHealthBar() {

    glColor3f(0 ,1 ,0);
	glBegin(GL_POLYGON);
		glVertex2f(-(xHealthBarStart-800) ,630);
		glVertex2f(1100 ,630);
		glVertex2f(1100 ,600);
		glVertex2f(-(xHealthBarStart-800), 600);
glEnd();
	char temp[40];
	glColor3f(1 ,0 ,0);
	sprintf(temp,"SCORE : %d",Score);
	displayRasterText(-1100 ,600 ,0.4 ,temp);//<---display variable score ?
	sprintf(temp,"  LIFE : %d",alienLife);
	displayRasterText(-800 ,600 ,0.4 ,temp);
	sprintf(temp,"  LEVEL : %d",GameLvl);
	displayRasterText(-400 ,600 ,0.4 ,temp);
	//glColor3f(1 ,0 ,0);
}
void startScreenDisplay()
{
	glLineWidth(50);
	SetDisplayMode(MENU_SCREEN);


	glLineWidth(1);

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);				//START GAME PLOYGON
		glVertex3f(-200 ,300 ,0.5);
		glVertex3f(-200 ,400 ,0.5);
		glVertex3f(200 ,400 ,0.5);
		glVertex3f(200 ,300, 0.5);
	glEnd();

	glBegin(GL_POLYGON);				//INSTRUCTIONS POLYGON
		glVertex3f(-200, 50 ,0.5);
		glVertex3f(-200 ,150 ,0.5);
		glVertex3f(200 ,150 ,0.5);
		glVertex3f(200 ,50, 0.5);
	glEnd();



	if(mouseX>=-100 && mouseX<=100 && mouseY>=150 && mouseY<=200){
		glColor3f(0 ,0 ,1) ;
		if(mButtonPressed){
			startGame = true ;
			gameOver = false;
			mButtonPressed = false;
		}
	} else
		glColor3f(0 , 0, 0);

	displayRasterText(-100 ,340 ,0.4 ,"Start Game");

	if(mouseX>=-100 && mouseX<=100 && mouseY>=30 && mouseY<=80) {
		glColor3f(0 ,0 ,1);
		if(mButtonPressed){
			gameQuit = true ;
			mButtonPressed = false;
		}
	} else
		glColor3f(0 , 0, 0);
	displayRasterText(-100 ,80 ,0.4 ,"Quit");



}
void GameScreenDisplay()
{
	SetDisplayMode(GAME_SCREEN);
	DisplayHealthBar();
	glScalef(2, 2 ,0);
	if(alienLife){
		SpaceshipCreate();
	}
	else {
		gameOver=true;
		instructionsGame = false;
		startScreen = false;
	}								//<----------------------gameover screen

	StoneGenerate();

}
void readFromFile() {

	FILE *fp = fopen("HighScoreFile.txt" ,"r");
	int i=0;
	if(fp!= NULL){
		while(fread(&ch,sizeof(char),1 ,fp)){
			highScore[i++] = ch;
		}
		highScore[i] = '\0';
	}
	fclose(fp);
}
void writeIntoFile() {						//To write high score on to file
	FILE *fp = fopen("HighScoreFile.txt" ,"w");
	int i=0;
	char temp[40];
	if(fp!= NULL){
		int n= Score;
		while(n){
			ch = (n%10)+ '0';
			n/=10;
			temp[i++] = ch;
		}
		temp[i] = '\0';
		strrev(temp);
		puts(temp);
		if(temp[0] == '\0')
			temp[i++] = '0' ,temp[i++] = '\0';
		fwrite(temp ,sizeof(char)*i ,i ,fp);
	}
 fclose(fp);
}
void GameOverScreen()
{
	SetDisplayMode(MENU_SCREEN);
	glColor3f(0,0,0);
	glLineWidth(50);


	glLineWidth(1);
	stoneTranslationSpeed=5;
	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);				//GAME OVER
		glVertex3f(-550 ,810,0.5);
		glVertex3f(-550 ,610 ,0.5);
		glVertex3f(550 ,610 ,0.5);
		glVertex3f(550 ,810, 0.5);
	glEnd();

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);				//RESTART POLYGON
		glVertex3f(-200, 50 ,0.5);
		glVertex3f(-200 ,150 ,0.5);
		glVertex3f(200 ,150 ,0.5);
		glVertex3f(200 ,50, 0.5);
	glEnd();

	glBegin(GL_POLYGON);				//QUIT POLYGON
		glVertex3f(-200 ,-200 ,0.5);
		glVertex3f(-200 ,-100 ,0.5);
		glVertex3f(200, -100 ,0.5);
		glVertex3f(200, -200 ,0.5);
	glEnd();


	displayRasterText(-300 ,640 ,0.4 ,"G A M E    O V E R ! ! !");
	glColor3f(0 , 0, 0);
	char temp[40];

	sprintf(temp,"Score : %d",Score);
	displayRasterText(-100 ,340 ,0.4 ,temp);
	readFromFile();
	char temp2[40];
	if(atoi(highScore) < Score){
		writeIntoFile();
		sprintf(temp2 ,"Highest Score :%d" ,Score);
	} else
		sprintf(temp2 ,"Highest Score :%s" ,highScore);

	displayRasterText(-250 ,400 ,0.4 ,temp2);

	if(mouseX>=-100 && mouseX<=100 && mouseY>=25 && mouseY<=75){
		glColor3f(0 ,0 ,1);
		if(mButtonPressed){                                                       //Reset game default values
			startGame = true ;
			gameOver=false;
			mButtonPressed = false;
			initializeStoneArray();
			alienLife=100;
			xHealthBarStart=1200;
			Score=0;
			GameLvl=1;
			GameScreenDisplay();
		}
	} else
		glColor3f(0 , 0, 0);
	displayRasterText(-70 ,80 ,0.4 ,"Restart");

	if(mouseX>=-100 && mouseX<=100 && mouseY>=-100 && mouseY<=-50){
		glColor3f(0 ,0 ,1);
		if(mButtonPressed){
			exit(0);
			mButtonPressed = false;
		}
	}
	else
		glColor3f(0 , 0, 0);
	displayRasterText(-100 ,-170 ,0.4 ,"    Quit");

}
void StoneGenerate(){

		if(xStone[0]>=1200){      //If the last screen hits the end of screen then go to Nxt lvl
			GameLvl++;
			stoneTranslationSpeed+=1;
			Score+=50;
			initializeStoneArray();
			GameScreenDisplay();
		}

	for(int i=0; i<MAX_STONES ;i++){
		index = i;

		if(mouseX <= (xStone[i]/2+20) && mouseX >=(xStone[i]/2-20) && mouseY >= (yStone[i]/2-20) && mouseY <= (yStone[i]/2+20) && mButtonPressed){
			if(stoneAlive[i]){   // IF ALIVE KILL STONE
				stoneAlive[i]=0;
				Score++;
				if(Score%1==0) {
					stoneTranslationSpeed+=0.75;			//<--------------Rate of increase of game speed
				}
			}
		}
		xStone[i] += stoneTranslationSpeed;
		if(stoneAlive[i] )             //stone alive
			DrawStone(randomStoneIndices[i]);
	}
	stoneAngle+=stoneRotationSpeed;
	if(stoneAngle > 360) stoneAngle = 0;
}
void backButton() {
	if(mouseX <= -450 && mouseX >= -500 && mouseY >= -275 && mouseY <= -250){
			glColor3f(0, 0, 1);
			if(mButtonPressed){
				mButtonPressed = false;
				instructionsGame = false;
				startScreenDisplay();
			}
	}
	else glColor3f(0, 0, 0);
	displayRasterText(-1000 ,-550 ,0, "Back");
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0,0,1200,700);

	if(startGame && !gameOver)
		GameScreenDisplay();



	else if(gameOver)
    {


        GameOverScreen();
    }


	//Make spaceship bigger
	else if(startScreen){

			startScreenDisplay();
			if(gameQuit || startGame || optionsGame || instructionsGame){
				//startScreen = false;

				if(startGame){
					SetDisplayMode(GAME_SCREEN);
					startScreen = false;

				} else if(gameQuit)
					exit(0);

				}
		}

	//Reset Scaling values
	glScalef(1/2 ,1/2 ,0);
	glFlush();
	glLoadIdentity();
	glutSwapBuffers();
}
void somethingMovedRecalculateLaserAngle() {

	float mouseXForTan = (-50 - mouseX) + xOne;
	float mouseYForTan = (35 - mouseY) + yOne;
	float LaserAngleInRadian = atan(mouseYForTan/mouseXForTan);
	LaserAngle = (180/PI) * LaserAngleInRadian;
}
void keys(unsigned char key, int x, int y)
{
	//if(key=='w' && key=='d' ){xOne+=0.5;yOne+=0.5;}
	if(key == 'd') xOne+=SPACESHIP_SPEED;
	if(key == 'a') xOne-=SPACESHIP_SPEED;
	if(key == 'w') {yOne+=SPACESHIP_SPEED;}
	if(key == 's') {yOne-=SPACESHIP_SPEED;}
	if(key == 'd' || key == 'a' || key == 'w' || key == 's')
		somethingMovedRecalculateLaserAngle();

	display();

}
void myinit()
{
	glClearColor(0.5,0.5,0.5,0);
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    gluOrtho2D(-1200,1200,-700,700);                   //<-----CHANGE THIS TO GET EXTRA SPACE
//  gluOrtho2D(-200,200,-200,200);
	glMatrixMode(GL_MODELVIEW);
}
void passiveMotionFunc(int x,int y) {

	//when mouse not clicked
	mouseX = float(x)/(m_viewport[2]/1200.0)-600.0;  //converting screen resolution to ortho 2d spec
	mouseY = -(float(y)/(m_viewport[3]/700.0)-350.0);

	//Do calculations to find value of LaserAngle
	somethingMovedRecalculateLaserAngle();
	display();
}
 void mouseClick(int buttonPressed ,int state ,int x, int y) {

	if(buttonPressed == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        mButtonPressed = true;
		//PlaySound("E://cg codes/test/laser.wav", NULL, SND_ASYNC|SND_FILENAME);
	}

	else
		mButtonPressed = false;
	display();
}
 void UpdateColorIndexForSpaceshipLights(int value)
{
	 CI=(CI+1)%3;			//Color Index swapping to have rotation effect
	 display();
 	 glutTimerFunc(250,UpdateColorIndexForSpaceshipLights,0);
}
 void idleCallBack() {			//when no mouse or keybord pressed
	 display();
 }
 int main(int argc, char** argv) {

	 FILE *fp = fopen("HighScoreFile.txt" ,"r") ;      //check if HighScoreFile.txt exist if not create
	 if(fp!=NULL)
		fclose(fp);
	 else
		 writeIntoFile();

	glutInit(&argc, argv);
	glutInitWindowSize(1200,700);
	glutInitWindowPosition(90 ,0);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutTimerFunc(50,UpdateColorIndexForSpaceshipLights,0);
	glutCreateWindow("SPACE ADVENTURE GAME");
	glutDisplayFunc(display);
	glutKeyboardFunc(keys);
	glutPassiveMotionFunc(passiveMotionFunc);
	glBlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA);
	glutIdleFunc(idleCallBack);
	glutMouseFunc(mouseClick);
	glGetIntegerv(GL_VIEWPORT ,m_viewport);
	myinit();
	SetDisplayMode(GAME_SCREEN);
	initializeStoneArray();
	glutMainLoop();
	//void glutFullScreen(void);
}

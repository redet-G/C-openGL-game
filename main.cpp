#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<string>

using namespace std;

char title[]= "computer graphics";//16
char option1[]="press f for flag of namibiya";//30
char option2[]="press L for the sign";//20
char option3[]="press g for bonous surprise";//28
char developedBy[]="Developed by: Redet Getachew(3928/08)";//38
int score = 0;
const int MAX_NUM_SHIP= 30;
struct sh{
	int id;
	float x;
	float y;
	float ySpeed;
	float color[3];
	sh(){
	}
	 sh(float xPos, float yPos, float speed, float scolor[3]){
		x=xPos;
		y=yPos;
		ySpeed = speed;
		color[0]=scolor[0];
		color[1]=scolor[1];
		color[2]=scolor[2];
	}
	void draw(){
		if(y<-660){
			y=600;
			score+=10;
			ySpeed+=0.03;
			return;
		}
		glColor3f(color[0],color[1],color[2]);
		glBegin(GL_TRIANGLES);
			glVertex2f( 0.0+x, 60.0+y );
			glVertex2f( 60.0+x, 60.0+y );			
			glVertex2f( 30.0+x, 0.0+y );
		glEnd();
		y-=ySpeed;
	}
	
	bool collied(float wx,float wy){
		float dx = x-wx;
		float dy = y-wy;
		return  sqrt(dx*dx+dy*dy) < 40.0;
	}
} ships[MAX_NUM_SHIP];

void printScore(int score);
float mx = 0;// x position
float my = 0;// y position
float acx = 0.0; // acc x
float acy = 0.0;// acc y
float delta = 0.05;// change
//player ship
void ship(float,float);
// used for drawing rouned corners
void midpointAlgorithm( int r ,int cx, int cy,int corner);
// drawing the star
void drawCirclePolar(int cx,int cy,int r){
	
	glColor3f(1,0.8078434375,0);
	double increament = 0.523599;
	GLint basePoints[30][2];
	GLint topPoints[30][2];
	int counter=0;
	glBegin(GL_POINTS);
	for(double i=0.2617995;i<=6.5449845;i+=increament){
		//glVertex2i(round(cx+r*cos(i)),round(cy+r*sin(i)));
		basePoints[counter][0]=round(cx+r*cos(i));
		basePoints[counter][1]=round(cy+r*sin(i));
		counter++;
	}
	
	basePoints[counter][0]=basePoints[0][0];
	basePoints[counter][1]=basePoints[0][1];
	
	r+=50;
	int counterTop=0;
	for(double i=0;i<6.283185;i+=increament){
//		glVertex2i(round(cx+r*cos(i)),round(cy+r*sin(i)));
		topPoints[counterTop][0]=round(cx+r*cos(i));
		topPoints[counterTop][1]=round(cy+r*sin(i));
		counterTop++;
	}
	
		topPoints[counterTop][0]=	topPoints[0][0];
		topPoints[counterTop][1]=	topPoints[0][1];
	glEnd();
		glBegin(GL_TRIANGLES);
	int i2;
	for(int i=0;i<counterTop;i++){
		
			glVertex2iv(basePoints[i]);
			i2 = i+1;
			glVertex2iv(basePoints[i2]);
			glVertex2iv(topPoints[i2]);
		}
	glEnd();
}
bool showFlag = false;
bool showIntro = true;
bool showSign = false;
bool showGame = false;
bool gameOver= false;
void keyPressed(unsigned char key,int,int){
	cout<<key<<endl;
	switch(key){
		case 'f':
		case 'F':
			showFlag = true;
			showIntro = false;
			showSign = false;
			showGame = false;
			break;
		case 'I':
		case 'i':
			showIntro = true;
			showFlag = false;
			showSign = false;
			showGame = false;
			break;
		case 'l':
		case 'L':
			showIntro = false;
			showFlag = false;
			showSign = true;
			showGame = false;
			break;
		case 'G':
		case 'g':
			showIntro = false;
			showFlag = false;
			showSign = false;
			showGame = true;
			gameOver = false;
			score=0;
			// start all ships
				float color[3];
				cout<<rand();
				for(int x=0;x<MAX_NUM_SHIP;x++){
					color[0]=(rand()%10)/10.0;
					color[1]=(rand()%10)/10.0;
					color[2]=(rand()%10)/10.0;
					int xpos = (rand()%600);
					if(x%2==0)
					  xpos*=-1;
					ships[x]=sh(xpos,600.0+rand()%600,(rand()%10+2)/100.0,color);
				}
			break;
	}
	glutPostRedisplay();
}

void midpoint(int cx,int cy,int r){
	int pp = 1-r;
	glBegin(GL_LINE_LOOP);
	int x= 0;
	int y=r;
	glVertex2i(cx+x,cy+y);
	double a = 1; 
	while(x<y){
		if(pp<0){
			pp=pp+2*(++x)+1;
		
		}else{
			pp=pp+2*(++x)+1-2*(--y);
		}
		glVertex2i(cx+x,(cy+y)*a);
		glVertex2i(cx-x,(cy+y)*a);
		glVertex2i(cx+x,(cy-y)*a);
		glVertex2i(cx-x,(cy-y)*a);
		glVertex2i(cx+y,(cy+x)*a);
		glVertex2i(cx-y,(cy+x)*a);
		glVertex2i(cx+y,(cy-x)*a);
		glVertex2i(cx-y,(cy-x)*a);
		
	}
	
	
	glEnd();
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	if(showFlag){
		glPopMatrix();
   		glPushMatrix();
		//left blue
		glColor3f(0,0.235556,0.56888889);
		glBegin(GL_POLYGON);
		    glVertex2i(300,300);		    
//			glVertex2i(-400,300);
			glVertex2i(-320,300);
			midpointAlgorithm(80,-320,220,64);
			midpointAlgorithm(80,-320,220,32);
			glVertex2i(-400,220);
			glVertex2i(-400,-200);
				
		glEnd();
		
		// left weight stroke
		glColor3f(1,1,1);
		glBegin(GL_POLYGON);
			glVertex2i(-400,-200);
			glVertex2i(-400,-220);
			glVertex2i(320,300);
			glVertex2i(300,300);
		glEnd();
		
		// right weight stroke
		glColor3f(1,1,1);
		glBegin(GL_POLYGON);
			glVertex2i(400,200);
			glVertex2i(400,220);
			glVertex2i(-320,-300);
			glVertex2i(-300,-300);
		glEnd();
		
		//center red
		glColor3f(0.823529,0.0627451,0.203922);
		
		glBegin(GL_POLYGON);
			glVertex2i(-400,-220);
//			glVertex2i(-400,-300);
			midpointAlgorithm(80,-320,-220,16);
			midpointAlgorithm(80,-320,-220,8);
			
			glVertex2i(-320,-300);
			glVertex2i(400,220);
//			glVertex2i(400,300);
			midpointAlgorithm(80,320,220,1);
			midpointAlgorithm(80,320,220,128);
			
			glVertex2i(320,300);
		glEnd();
		
		// right green
		glColor3f(0,0.584344,0.26274509804);
		glBegin(GL_POLYGON);
			glVertex2i(400,200);
			glVertex2i(-300,-300);
//			glVertex2i(400,-300);
			glVertex2i(320,-300);
			midpointAlgorithm(80,320,-220,4);
			midpointAlgorithm(80,320,-220,2);
			glVertex2i(400,-220);		
		glEnd();
	
		// logo
		int cx=-205,cy=155;
		drawCirclePolar(cx,cy,60);
		glColor3f(0,0.235556,0.56888889);
		midpoint(cx,cy,61);
		glColor3f(1,0.8078434375,0);
		midpoint(cx,cy,50);
   }
   if(showIntro){
   		//reset line width and color
   		glLineWidth(1);
   		glColor3f(0.0,0.0,0.0);
   		glPopMatrix();
   		glPushMatrix();
   		glTranslated(-580,0,0);
   		//title
		for(int i=0;i<17;i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN,title[i]);
		//options
		glScaled(0.3,0.3,1);
		
		glTranslated(-3000,-300,0);
		for(int j=0;j<29;j++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN,option1[j]);
		
  		glTranslated(-1870,-200,0);
		for(int j=0;j<20;j++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN,option2[j]);	
  	    glTranslated(-1370,-200,0);
		for(int j=0;j<28;j++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN,option3[j]);
		glScaled(0.8,0.8,1);
		glTranslated(-1370,-400,0);
		for(int j=0;j<38;j++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN,developedBy[j]);
   }
   
   if(showSign){
		glPopMatrix();
		glPushMatrix();
   		// inner color
		glColor3f(0.984375,0.7578125,0.0859375);
		glBegin(GL_POLYGON);
			glVertex2i(20,-280);
			glVertex2i(280,-20);
				//right rounded corner			
				midpointAlgorithm(27,260,0,2);
				midpointAlgorithm(27,260,0,1);
			glVertex2i(280,20);
				//top rounded corner
			  		midpointAlgorithm(27,0,260,128);
					midpointAlgorithm(27,0,260,64);
			glVertex2i(-20,280);
				//left rouned corner
				midpointAlgorithm(27,-260,0,32);
		    	midpointAlgorithm(27,-260,0,16);
			glVertex2i(-280,-20);
				//bottom rouned corner
				midpointAlgorithm(27,0,-260,8);
			    midpointAlgorithm(27,0,-260,4);
		glEnd();
		
		//outer border
		glColor3f(0,0,0);
	  	glLineWidth(6);
	  	glPointSize(3.5);
	
		// right rounded corner
		glBegin(GL_POINTS);
			midpointAlgorithm(27,260,0,2);
			midpointAlgorithm(27,260,0,1);
		glEnd();
		// bottom right line
		glBegin(GL_LINES);
	  		glVertex2i(20,-280);  	
			glVertex2i(280,-20);
		glEnd();
		// bottom rounded corner
		glBegin(GL_POINTS);
			midpointAlgorithm(27,0,-260,8);
			midpointAlgorithm(27,0,-260,4);
		glEnd();
		//bttom right line
		glBegin(GL_LINES); 	
			glVertex2i(-280,-20);
			glVertex2i(-20,-280);		
		glEnd();
		// left rounded corner
		glBegin(GL_POINTS);
			midpointAlgorithm(27,-260,0,32);
			midpointAlgorithm(27,-260,0,16);
		glEnd();
		// left upper line
		glBegin(GL_LINES);
			glVertex2i(-20,280);
			glVertex2i(-280,20);
	  	glEnd();
	  	//top rounded corner
	  	glBegin(GL_POINTS);
			midpointAlgorithm(27,0,260,128);
			midpointAlgorithm(27,0,260,64);
		glEnd();
	  	//top right line
		glBegin(GL_LINES);			
			glVertex2i(280,20);
			glVertex2i(20,280);
		glEnd;
			
		// middle lines
	  	glBegin(GL_LINES);
	  		glVertex2i(0,220);
	  		glVertex2i(0,130);
	  		glVertex2i(0,50);
	  		glVertex2i(0,-50);	
	  		glVertex2i(0,-130);
	  		glVertex2i(0,-200);
	  	glEnd();
	  	
	  	// right arrow
	  	glBegin(GL_POLYGON);
	  		glVertex2i(100,115);
	  		glVertex2i(50,40);
	  		glVertex2i(80,40);
	  		glVertex2i(80,-115);
	  		glVertex2i(120,-115);
	  		glVertex2i(120,40);
	  		glVertex2i(150,40);
	  	glEnd();
	  	
	  	// left arrow
	  	
	  	glBegin(GL_POLYGON);
	  		glVertex2i(-100,-115);
	  		glVertex2i(-50,-40);
	  		glVertex2i(-80,-40);
	  		glVertex2i(-80,115);
	  		glVertex2i(-120,115);
	  		glVertex2i(-120,-40);
	  		glVertex2i(-150,-40);
	  	glEnd();
   }
	if(showGame){
		glLineWidth(1);
   		glPopMatrix();
   		glPushMatrix();
	  	for(int i=0;i<MAX_NUM_SHIP&&!gameOver;i++){
	  		ships[i].draw();
			if(ships[i].collied(mx,my)){
				gameOver=true;
			}
	  	}
	  	if(gameOver){
			//game over
			glLineWidth(5);
			char gameOver[]="Game Over";
	  		glTranslated(-350,0,0);
   			for(int i=0;i<9;i++)
				glutStrokeCharacter(GLUT_STROKE_ROMAN,gameOver[i]);
			glLineWidth(3);
			glScaled(0.5,0.5,1);
			glTranslated(-1000,-300,0);
			char ScoreText[] = "score: ";
			for(int i=0;i<7;i++)
				glutStrokeCharacter(GLUT_STROKE_ROMAN,ScoreText[i]);
			printScore(score);
	  	}else{
		  	//move the main ship
		  	mx+=delta*acx;
			my+=delta*acy;
		  	ship(mx,my);
		  	if(acx>0.2 || acx<-0.2)
		  		acx=acx/1.02;
		  	else
		  		acx = 0.0;
		  	if(acy>0.2 || acy<-0.2)
		  		acy=acy/1.008;
		  	else
		  		acy = 0.0;
		  	glutPostRedisplay();
	  }
	}

	glFlush();
//	glutSwapBuffers();
}

void myint(){
	glClearColor(1,1,1,0.0);
	glColor3f(0.0,0.0,0.0);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-600.0,600.0,-600.0,600.0);
}
void gamekeypressed(int key, int x , int y){ 
 
	switch(key){
		case 27: break;
		case 100://left
			acx-=10.0;
			break;
		case 101://up
			acy+=10.0;
			break;
		case 102://right
			acx+=10;
			break;
		case 103://down
			acy-=10.0;
			break;
	}
}

int main(int a, char *v[]){
	glutInit(&a,v);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(50,0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("firt opengl");
	myint();
	glutDisplayFunc(display);
//	 glutSwapBuffers();
//	glutSpecialFunc(keyPressed);	
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(gamekeypressed);
	glutMainLoop();
	return 0;
}

/*
  	corner can be the following values
  		1 for right side of the upper section
  		2 for right side of th lower section
  		4 for bottom side of the right section
  		8 for bottom side of the left section
  		16 for left side of the lower section
  		32 for left side of the upper section
  		64 for top side of the left section
  		128 for top side of the right section
  		
  */

void midpointAlgorithm( int r ,int cx, int cy,int corner){
	
	int x = 0;
	int y = r;
	int p = 1 - r;
	
	int count=0;
	int points[r*2][2];
	while ( x <= y ){
		switch(corner){
			case 1:
//				glVertex2i(y+cx,x+cy);
				points[count][0]=y+cx;
				points[count][1]=x+cy;
				count++;
				break;
			case 2:
//				glVertex2i(y+cx,-x+cy);
				points[count][0]=y+cx;
				points[count][1]=-x+cy;
				count++;
				break;
			case 4:
//				glVertex2i(x+cx,-y+cy);
				points[count][0]=x+cx;
				points[count][1]=-y+cy;
				count++;
				break;
			case 8:
//				glVertex2i(-x+cx,-y+cy);
				points[count][0]=-x+cx;
				points[count][1]=-y+cy;
				count++;
				break;
			case 16:
//				glVertex2i(-y+cx,-x+cy);
				points[count][0]=-y+cx;
				points[count][1]=-x+cy;
				count++;
				break;
			case 32:
//				glVertex2i(-y+cx,x+cy);
				points[count][0]=-y+cx;
				points[count][1]=x+cy;
				count++;
				break;
			case 64:
//				glVertex2i(-x+cx,y+cy);
				points[count][0]=-x+cx;
				points[count][1]=y+cy;
				count++;
				break;
			case 128:
//				glVertex2i(x+cx,y+cy);
				points[count][0]=x+cx;
				points[count][1]=y+cy;
				count++;
				break;				
		}			
		if ( p < 0 ){
			x = x + 1;
			y = y;
			p = p + ( 2 * x ) + 1;
		}else{//p > = 0
			x = x + 1;
			y = y - 1;
			p = p + ( 2 * x ) + 1 - ( 2 * y );
		}
	}
	
	//sort the in to counter colckwise
	int pointsR[count][2];
	for(int i=0,j=count-1;i<count;i++,j--){
		pointsR[j][0]=points[i][0];	
	    pointsR[j][1]=points[i][1];	
	}
//print points
	switch(corner){
			case 1:
			case 4:
			case 16:
			case 64:{
				for(int i=0;i<count;i++){
					glVertex2i(points[i][0],points[i][1]);
			    }
			}
				break;
			case 2:
			case 8:
			case 32:
			case 128:{
				for(int i=0;i<count;i++){
					glVertex2i(pointsR[i][0],pointsR[i][1]);
			    }
			}
				break;				
		}			

}
// draw main ship
void ship(float x, float y){
	glBegin(GL_TRIANGLES);
			glVertex2f( 0.0+x, 0.0+y );
			glVertex2f( 60.0+x, 0.0+y );			
			glVertex2f( 30.0+x, 60.0+y );
	glEnd();
}

void printScore(int score){
	if(score<10)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,(char)(48+score));
	else{
		int number = score % 10;
		score /=10;
		printScore(score);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,(char)(48+number));
	}
		
}

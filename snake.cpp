//#include<windows.h>
#include <glut.h>
#include <time.h>
#include <iostream>
#include <algorithm> 
#include <string.h>
#include <conio.h>

using namespace std;

int GAME_OVER=-1;
int SCORE=0;

int pom = 25;

int foodx, foody;
int food = 1;

int c = 0;
int b = 0;

int length = 5;
int posSnake[200][2] = {{11,14},{11,13},{11,12},{11,11},{11,10},{11,9}};
					//{{11,9}, {11,10}, {11,11}, {11,12}, {11,13}, {11,14}};
int xr=0, yr=0;

char pass;

void init()
{
    // For displaying the window color
    glClearColor(0, 1, 1, 0);
    // Choosing the type of projection
    glMatrixMode(GL_PROJECTION);
    // for setting the transformation which here is 2D
    gluOrtho2D(0, 600, 0, 600);
}



void partSnake(int x, int y)
{
	glBegin(GL_QUADS);
	
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(x + pom, y +  pom);
    glColor3f(0.5f, 0.5f, 0.0f);
    glVertex2i(x + pom, y);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(x, y);
    glColor3f(0.0f, 0.5f, 0.5f);
    glVertex2i(x, y + pom);

    glEnd();
}

void specialkey(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
		{
			if(yr!=-1)
			{
				yr=1;
				xr=0;	
			}
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_DOWN:
		{
			if(yr!=1)
			{
				yr=-1;
				xr=0;
			}
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_LEFT:
		{
			if(xr!=2)
			{
				xr=-2;
				yr=0;	
			}	
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_RIGHT:
		{
			if(xr!=-2)
			{
				xr=2;
				yr=0;	
			}
			glutPostRedisplay();
			break;
		}
		defoult:
			break;
	}
}

void drawSnake()
{
	for(int i = 0 ; i<length; i++)
    {
    	partSnake(posSnake[i][0]*25, posSnake[i][1]*25);
	}
}

void moveSnake()
{	

	for (int i = length - 1; i > 0; i--)
    {
    	posSnake[i][0] = posSnake[i - 1][0];
        posSnake[i][1] = posSnake[i - 1][1];
	}
	
	for (int i = 0; i < length; i++)
    {  
        if (i == 0)
        {
		    if(yr!=0)
			{
				if(yr>0)
				{
					posSnake[0][1]++;
				}
				else
				{
					posSnake[0][1]--;	
				}	
			}
			else
			{
				if(xr>0)
				{
					posSnake[0][0]++;
				}
				else
				{
					posSnake[0][0]--;	
				}		
			}
			if (posSnake[0][0] < 1 || posSnake[0][0] > 22 || posSnake[0][1] < 1 || posSnake[0][1] > 22)
			{
			 	GAME_OVER=1;
			 	cout<<8;
			 	//exit(0);
			}
            else
			{
				if(posSnake[0][0] == foodx &&  posSnake[0][1] == foody)
				{
					SCORE++;
					food = 1;
					posSnake[length+1][0] = posSnake[length][0];
        			posSnake[length+1][1] = posSnake[length][1];
					
					length++;
				}
			}
			for (int j = 1; j < length; j++)
            {
                if (posSnake[0][0] == posSnake[j][0] &&  posSnake[0][1] == posSnake[j][1])
                {
                	GAME_OVER = 1;
                	cout<<9;
                	//exit(0);
				}
            }   
		}
	}
	
    
//    void drawSnake();
}

void drawFood()
{
    if (food)
    {
        foodx = 1 + rand() % 22;
        foody = 1 + rand() % 22;

        
        for (int j = 1; j < length; j++)
	    {
	    	if (posSnake[j][0] == foodx && posSnake[j][1] == foody)
	    	{
				food = 1;
				break;
			}
			else
			{
				food = 0;	
			}
	    }   
    }
    

    
    glBegin(GL_QUADS);
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(25 * foodx + pom, 25 * foody +  pom);
    glColor3f(1.0f, 0.2f, 0.2f);
    glVertex2i(25 * foodx + pom, 25 * foody);
    glColor3f(1.0f, 0.1f, 0.1f);
    glVertex2i(25 * foodx, 25 * foody);
    glColor3f(1.0f, 0.3f, 0.3f);
    glVertex2i(25 * foodx, 25 * foody + pom);

    glEnd();
}



void drawSquare(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLint x4, GLint y4)
{
    // if color is 0 then draw white box and change value of color = 1
    if (c == 0)
    {
        glColor3f(0.0f, 0.4f, 0.0f); // green color value
        c = 1;
    }
    else
    {
        glColor3f(0.6f, 0.6f, 0.0f); // yellow color value
        c = 0;
    }

    if (b == 1)
    {
        glColor3f(0.1f, 0.1f, 0.1f);
        b = 0;
    }

    // Draw Square
    glBegin(GL_POLYGON);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glVertex2i(x3, y3);
    glVertex2i(x4, y4);
    glEnd();
}

void board()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window

    for (GLint x = 0; x <= 625; x += 25)
    {
        for (GLint y = 0; y <= 600; y += 25)
        {
            if (x == 0 || y == 0 || x == 575 || y == 575)
            {
                b = 1;
            }
            drawSquare(x, y + 25, x + 25, y + 25, x + 25, y, x, y);
        }
    }

}


void gameSnake()
{
	board();
	drawFood();
    moveSnake();
    drawSnake();
    glFlush();
    cout<<2;
}

void beginSnake()
{
	board();
    
    drawSnake();
    
    glFlush();
	
	cout<<1;
	
	if(yr > 0 || xr !=0)
	{
		//moveSnake();
		GAME_OVER=0;
	}
	Sleep(1);
}

void endSnake()
{
	board();
    
    drawSnake();
    
    glFlush();
    
    cout<<3;
}

void bildSnake()
{
	if(GAME_OVER==-1)
	{
		beginSnake();
	}
	else
	{
		if(GAME_OVER==0)
		{
			gameSnake();
		}
		else
		{
			endSnake();
		}
	}
}

void timer_callback(int)
{
    glutPostRedisplay();
    glutTimerFunc(100,timer_callback,0);
}

int main(int agrc, char **argv)
{
    srand(time(NULL));
    // Initialize GLUT
    glutInit(&agrc, argv);
    // Set display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Set top - left display window position.
    glutInitWindowPosition(150, 150);
    // Set display window width and height
    glutInitWindowSize(600, 600);
    // Create display window with the given title
    glutCreateWindow("SNAKE-0.4");
    // Execute initialization procedure
    
    // Send graphics to display window
    glutDisplayFunc(bildSnake);
    glutSpecialFunc(specialkey);
    
    glutTimerFunc(1,timer_callback,2);
	init();
    // Display everything and wait.
    glutMainLoop();
}

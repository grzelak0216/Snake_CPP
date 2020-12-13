//#include<windows.h>
#include<glut.h>
#include<time.h>

float pom = 12.5;

int foodx, foody;
int food = 1;

int c = 0;
int b = 0;



void init()
{
// For displaying the window color
glClearColor(0, 1, 1, 0);
// Choosing the type of projection
glMatrixMode(GL_PROJECTION);
// for setting the transformation which here is 2D
gluOrtho2D(0, 600, 0,600);
}

void drawSnake()
{
	
}

//void moveSnake()
//{
//	
//}

void drawFood()
{
	if(food)
	{
		foodx=1+rand()%16;
		foody=1+rand()%22;
		
		
		
		glBegin(GL_QUADS);
		
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2i(25*foodx+2*pom, 25*foody+2*pom);
		glColor3f(1.0f, 0.2f, 0.2f);
		glVertex2i(25*foodx+2*pom, 25*foody);
		glColor3f(1.0f, 0.1f, 0.1f);
		glVertex2i(25*foodx, 25*foody);
		glColor3f(1.0f, 0.3f, 0.3f);
		glVertex2i(25*foodx, 25*foody+2*pom);
		
		glEnd();
		
	}
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
	b=0;
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
GLint x, y;

for (x = 0; x <= 600; x += 25)
{
for (y = 0; y <= 600; y += 25)
{
	if(x==0 || y==0 || x > 400 || y == 575)
	{
		b=1;
	}
	drawSquare(x, y + 25, x + 25, y + 25, x +25, y, x, y);
}
}

drawFood();

// Process all OpenGL routine s as quickly as possible
glFlush();
}

int main(int agrc, char ** argv)
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
glutCreateWindow("Chess Board using OpenGL in C++");
// Execute initialization procedure
init();
// Send graphics to display window
glutDisplayFunc(board);
// Display everything and wait.
glutMainLoop();
}

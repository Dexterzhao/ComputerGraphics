#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>



// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f,ly=0.0f;
// XZ position of the camera
float x=0.0f,z=5.0f,y=0.0f;


void renderScene(void)
{

    // Clear Color and Depth Buffers

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    // Set the camera
    gluLookAt(    x, 1.0f, z,
                  x+lx, y+ly,  z+lz,
                  0.0f, 1.0f,  0.0f);

    // Draw ground
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();

    // Draw 36 teapot
    for(int i = -3; i < 3; i++)
        for(int j=-3; j < 3; j++)
        {
            glPushMatrix();
            glTranslatef(i*10.0,0,j * 10.0);

            glutSolidTeapot(1.0);
            glPopMatrix();
        }

    glutSwapBuffers();
}



void processSpecialKeys(int key, int xx, int yy)
{

    float fraction = 0.1f;

    switch (key)
    {                               //Define specialkeys and the fluctuations from the key
    case GLUT_KEY_LEFT :        //key left
        angle -= 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_RIGHT :       //key right
        angle += 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_UP :          //key up
        angle += 0.01f;
        ly = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_DOWN :        //key down
        angle -= 0.01f;
        ly = sin(angle);
        lz = -cos(angle);
        //x -= lx * fraction;
        //z -= lz * fraction;
        break;
    }
}



void init(void)

{
    // Initialize material property, light source, lighting model, * and depth buffer.
    GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};

    GLfloat mat_diffuse[] = {0.8, 0.8, 0.8, 1.0} ;

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat mat_shininess[] = { 50.0 };

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat Light_Model_Ambient[] = { 0.2 , 0.2 , 0.2 , 1.0 };

    glClearColor (0.0, 0.0, 0.0, 0.0);

    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);

    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

    glLightModelfv( GL_LIGHT_MODEL_AMBIENT , Light_Model_Ambient ); //

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);

}

void changeSize(GLsizei w,GLsizei h)
{
    if(h==0) h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
        glOrtho(-5.5,5.5,-5.5*h/w,5.5*h/w,-10.0,10.0);
    else
        glOrtho(-5.5*w/h,5.5*w/h,-5.5,5.5,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}


int main(int argc, char** argv)

{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize (500, 500);

    glutInitWindowPosition (100, 100);

    glutCreateWindow (argv[0]);

    init ();
    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutSpecialFunc(processSpecialKeys);

    glEnable(GL_DEPTH_TEST);

    return 0;

}

#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
GLfloat cameraX = 0;
GLfloat cameraY = 0;
GLfloat cameraZ = 5;
GLfloat cameraRX = 0;
GLfloat cameraRY = 0;
GLfloat cameraRZ = 0;

int x=0;
int y=0;
int z=0;


int id2 = 0;
int reading =0;
unsigned char buffer[1024];
FILE *file;
size_t bytes_read;
float renderlist[1024][10];
int background[3];

void display() {
    glLineWidth(2);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // カメラの設定
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, cameraRX, cameraRY, cameraRZ, 0.0, 1.0, 0.0);
    size_t bytes_read;
    for(int i=0; i<200; i++){
        if(renderlist[i][0] == 1){
            glTranslated(renderlist[i][1], renderlist[i][2], renderlist[i][3]);
            x += renderlist[i][1];
            y += renderlist[i][2];
            z += renderlist[i][3];
            glRotated(1, renderlist[i][4], renderlist[i][5], renderlist[i][6]);
            glScaled(renderlist[i][7], renderlist[i][8], renderlist[i][9]);
            glutWireCube(1);
            
        }
        if(renderlist[i][0] == 2){
            glTranslated(renderlist[i][1], renderlist[i][2], renderlist[i][3]);
            x += renderlist[i][1];
            y += renderlist[i][2];
            z += renderlist[i][3];
            glRotated(1, renderlist[i][4], renderlist[i][5], renderlist[i][6]);
            glScaled(renderlist[i][7], renderlist[i][8], renderlist[i][9]);
            glutWireSphere(1,64,64); 
        }
        if(renderlist[i][0] == 3){
            glTranslated(renderlist[i][1], renderlist[i][2], renderlist[i][3]);
            x += renderlist[i][1];
            y += renderlist[i][2];
            z += renderlist[i][3];
            glRotated(1, renderlist[i][4], renderlist[i][5], renderlist[i][6]);
            glScaled(renderlist[i][7], renderlist[i][8], renderlist[i][9]);
            glutWireTeapot(1);
        }    
        if(renderlist[i][0] == 4){
            glClearColor(renderlist[i][1]/255, renderlist[i][2]/255, renderlist[i][3]/255,1);
        }
        if(renderlist[i][0] == 5){
            glColor3f(renderlist[i][1]/255, renderlist[i][2]/255, renderlist[i][3]/255);
        }
        if(renderlist[i][0] == 6){
            float subx = -x;
            float suby = -y;
            float subz = -z;
            float addx = renderlist[i][1];
            float addy = renderlist[i][2];
            float addz = renderlist[i][3];
            if(renderlist[i][4]==0x01){
                addx = -addx;
            }
            if(renderlist[i][5]==0x01){
                addy = -addy;
            }
            if(renderlist[i][6]==0x01){
                addz = -addz;
            }
            
            
            glTranslated(subx+addx,suby+addy,subz+addz);
            x = 0;
            y = 0;
            z = 0;
        }
        if(renderlist[i][0] == 7){
            cameraX = renderlist[i][1];
            cameraY = renderlist[i][2];
            cameraZ = renderlist[i][3];
            cameraRX = renderlist[i][4];
            cameraRY = renderlist[i][5];
            cameraRZ = renderlist[i][6];
        }
        
    }
    glPushMatrix();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (double)width / (double)height, 0.1, 100.0);
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    int f1;
    char *str;
    file = fopen("Map", "rb");
    while ((bytes_read = fread(buffer, 1, 1024, file)) > 0) {}
    if (file == NULL) {
        perror("GSource2.1");
        return 1;
    }
    for(int id = 0; id<1024; id++){
        if(buffer[id]==0x01){
            renderlist[id2][0] = 1;
            renderlist[id2][1] = buffer[id+1];
            renderlist[id2][2] = buffer[id+2];
            renderlist[id2][3] = buffer[id+3];
            renderlist[id2][4] = buffer[id+4];
            renderlist[id2][5] = buffer[id+5];
            renderlist[id2][6] = buffer[id+6];
            renderlist[id2][7] = buffer[id+7];
            renderlist[id2][8] = buffer[id+8];
            renderlist[id2][9] = buffer[id+9];
            id+=9;
        }
        if(buffer[id]==0x02){
            renderlist[id2][0] = 2;
            renderlist[id2][1] = buffer[id+1];
            renderlist[id2][2] = buffer[id+2];
            renderlist[id2][3] = buffer[id+3];
            renderlist[id2][4] = buffer[id+4];
            renderlist[id2][5] = buffer[id+5];
            renderlist[id2][6] = buffer[id+6];
            renderlist[id2][7] = buffer[id+7];
            renderlist[id2][8] = buffer[id+8];
            renderlist[id2][9] = buffer[id+9];
            id+=9;
        }
        if(buffer[id]==0x03){
            renderlist[id2][0] = 3;
            renderlist[id2][1] = buffer[id+1];
            renderlist[id2][2] = buffer[id+2];
            renderlist[id2][3] = buffer[id+3];
            renderlist[id2][4] = buffer[id+4];
            renderlist[id2][5] = buffer[id+5];
            renderlist[id2][6] = buffer[id+6];
            renderlist[id2][7] = buffer[id+7];
            renderlist[id2][8] = buffer[id+8];
            renderlist[id2][9] = buffer[id+9];
            id+=9;
        }
        if(buffer[id]==0x04){
            renderlist[id2][0] = 4;
            renderlist[id2][1] = buffer[id+1];
            renderlist[id2][2] = buffer[id+2];
            renderlist[id2][3] = buffer[id+3];
            id+=3;
        }
        if(buffer[id]==0x05){
            renderlist[id2][0] = 5;
            renderlist[id2][1] = buffer[id+1];
            renderlist[id2][2] = buffer[id+2];
            renderlist[id2][3] = buffer[id+3];

            id+=3;
        }
        if(buffer[id]==0x06){
            renderlist[id2][0] = 6;
            renderlist[id2][1] = buffer[id+1];
            renderlist[id2][2] = buffer[id+2];
            renderlist[id2][3] = buffer[id+3];
            renderlist[id2][4] = buffer[id+4];
            renderlist[id2][5] = buffer[id+5];
            renderlist[id2][6] = buffer[id+6];
            id+=6;
        }
        if(buffer[id]==0x07){
            renderlist[id2][0] = 7;
            renderlist[id2][1] = buffer[id+1];
            renderlist[id2][2] = buffer[id+2];
            renderlist[id2][3] = buffer[id+3];
            renderlist[id2][4] = buffer[id+4];
            renderlist[id2][5] = buffer[id+5];
            renderlist[id2][6] = buffer[id+6];
            id+=6;
        }
        
        id2++;
    }
        
    fclose(file);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("GSource2.1 - Player");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}

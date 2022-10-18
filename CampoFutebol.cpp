#include <bits/stdc++.h>
#include <GL/glut.h>
#include <stdlib.h>

using namespace std;

int AngVisao = 40, golsEsq = 0, golsDir = 0;

double ObsX = 0, ObsY = 0.0, ObsZ = 500.0;

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
void linhaVertical(int x1, int x2, int y1, int y2, int z);
void linhaHorizontal(int x1, int x2, int y1, int y2);
void linhaZ(int x1, int z1, int x2, int z2, int y);
void desenhaCirculo(int r, int x1, int y1, int op);
void criarBola();

#define WHITE 1.0, 1.0, 1.0
#define GREEN 0.0, 1.0, 0.0
#define YELLOW 1.0, 1.0, 0.0

static GLfloat vertices[16] = {
    -140.0, 120.0, 0.0,  /* 0 */
    -140.0, -120.0, 0.0, /* 1 */
    140.0, -120.0, 0.0,  /* 2 */
    140.0, 120.0, 0.0,   /* 3 */
};

static GLubyte gramadoIndices[] = {0, 1, 2, 3};

static int eixoy, eixox;
int largura, altura;
float anguloCameraX = 0.0, anguloCameraY = 0.0, velocidadeCamera = 200.0;

/*Dados da bola*/

float raioBola = 2.0;
float xBola = 0.0;
float yBola = 0.0;
float zBola = 2.0;
float velocidadeBola = 200.0;

int main(int argc, char **argv)
{
    int i;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1050, 650);
    glutInitWindowPosition(200, 25);
    glutCreateWindow(argv[0]);
    // init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

// void init(void)
// {

//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluPerspective(AngVisao, 1, 1, 1000);
//     gluLookAt(ObsX, ObsY, ObsZ, 0, 0, 0, 0, 1, 0);
//     glMatrixMode(GL_MODELVIEW);

//     glClearColor(0.0, 0.0, 0.0, 0.0);
//     glEnable(GL_DEPTH_TEST);
// }

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    largura = w;
    altura = h;
}

void display(void)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(AngVisao, 1, 1, 1000);
    gluLookAt(ObsX, ObsY, ObsZ, 0, 0, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
    glRotatef((GLfloat)eixoy, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)eixox, 1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    /*Gramado*/
    glColor3f(GREEN);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, gramadoIndices);

    glDisableClientState(GL_VERTEX_ARRAY);

    /*Bola*/
    criarBola();

    /*Retangulo Maior*/
    linhaHorizontal(-120, 90, 120, 90);
    linhaHorizontal(-120, -90, 120, -90);
    linhaVertical(-120, -90, -120, 90, 0);
    linhaVertical(120, -90, 120, 90, 0);

    /*Grande Área Esquerda*/
    linhaHorizontal(-120, 40.3, -87, 40.3);
    linhaHorizontal(-120, -40.3, -87, -40.3);
    linhaVertical(-87, -40.3, -87, 40.3, 0);

    /*Grande Área Direita*/
    linhaHorizontal(87, 40.3, 120, 40.3);
    linhaHorizontal(87, -40.3, 120, -40.3);
    linhaVertical(87, -40.3, 87, 40.3, 0);

    /*Pequena Área Esquerda*/
    linhaHorizontal(-120, 18.3, -109, 18.3);
    linhaHorizontal(-120, -18.3, -109, -18.3);
    linhaVertical(-109, -18.3, -109, 18.3, 0);

    /*Pequena Área Direita*/
    linhaHorizontal(109, 18.3, 120, 18.3);
    linhaHorizontal(109, -18.3, 120, -18.3);
    linhaVertical(109, -18.3, 109, 18.3, 0);

    /*Gol Esquerdo*/
    linhaHorizontal(-124.8, 7.3, -120.0, 7.3);
    linhaHorizontal(-124.8, -7.3, -120.0, -7.3);
    linhaVertical(-124.8, -7.3, -124.8, 7.3, 0);

    /*Gol Direito*/
    linhaHorizontal(120.0, 7.3, 124.8, 7.3);
    linhaHorizontal(120.0, -7.3, 124.8, -7.3);
    linhaVertical(124.8, -7.3, 124.8, 7.3, 0);

    /*Trave Esquerda*/
    linhaZ(-120.0, 0.0, -120.0, 5.0, 7.3);
    linhaZ(-120.0, 0.0, -120.0, 5.0, -7.3);
    linhaVertical(-120.0, -7.3, -120.0, 7.3, 5);

    /*Trave Direita*/
    linhaZ(120.0, 0.0, 120.0, 5.0, 7.3);
    linhaZ(120.0, 0.0, 120.0, 5.0, -7.3);
    linhaVertical(120.0, -7.3, 120.0, 7.3, 5);

    /*Linha do Meio*/
    linhaVertical(0, -90, 0, 90, 0);

    /*Área Central*/
    desenhaCirculo(20, 0, 0, 0);

    /*Canto 1*/
    desenhaCirculo(6, -120, 90, 1);

    /*Canto 2*/
    desenhaCirculo(6, -120, -90, 2);

    /*Canto 3*/
    desenhaCirculo(6, 120, -90, 3);

    /*Canto 4*/
    desenhaCirculo(6, 120, 90, 4);

    /*Ponto Central*/
    desenhaCirculo(1, 0, 0, 0);

    /*Ponto Pênalti Esquerdo*/
    desenhaCirculo(1, 98, 0, 0);

    /*Ponto Pênalti Direito*/
    desenhaCirculo(1, -98, 0, 0);

    glPopMatrix();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    /*Movimentação da Bola*/
    /*Cima*/
    case 'w':
        /*Dentro da Trave*/
        if ((xBola <= -118 or xBola >= 118) and yBola < 5)
        {
            yBola += 1.0;
        }
        /*Fora*/
        if (yBola < 88 and (xBola >= -118 and xBola <= 118))
            yBola += 1.0;
        glutPostRedisplay();
        break;
    /*Baixo*/
    case 's':
        /*Dentro da Trave*/
        if ((xBola <= -118 or xBola >= 118) and yBola > -5)
        {
            yBola -= 1.0;
        }
        /*Fora*/
        if (yBola > -88 and (xBola >= -118 and xBola <= 118))
            yBola -= 1.0;
        glutPostRedisplay();
        break;
    /*Esquerda*/
    case 'a':
        /*Parcialmente dentro da Trave ou Fora*/
        if (xBola > -118 or (yBola <= 5 and yBola >= -5))
            xBola -= 1.0;
        /*Gol*/
        if (xBola <= -121)
        {
            xBola = 0.0;
            yBola = 0.0;
            golsDir += 1;
            cout << golsEsq << " x " << golsDir << endl;
        }
        glutPostRedisplay();
        break;
    /*Direita*/
    case 'd':
        /*Parcialmente dentro da Trave ou Fora*/
        if (xBola < 118 or (yBola <= 5 and yBola >= -5))
            xBola += 1.0;
        /*Gol*/
        if (xBola >= 121)
        {
            xBola = 0.0;
            yBola = 0.0;
            golsEsq += 1;
            cout << golsEsq << " x " << golsDir << endl;
        }
        glutPostRedisplay();
        break;
    /*Movimentação da Câmera*/
    /*"Cima"*/
    case 'W':
        anguloCameraY += velocidadeCamera / 10000;
        if (500.0 * cos(anguloCameraY) >= 0)
        {
            ObsY = 500.0 * sin(anguloCameraY);
            ObsZ = 500.0 * cos(anguloCameraY);
        }
        glutPostRedisplay();
        break;
    /*Baixo*/
    case 'S':
        anguloCameraY -= velocidadeCamera / 10000;
        if (500.0 * cos(anguloCameraY) >= 0)
        {
            ObsY = 500.0 * sin(anguloCameraY);
            ObsZ = 500.0 * cos(anguloCameraY);
        }
        glutPostRedisplay();
        break;
    case 'A':
        anguloCameraX -= velocidadeCamera / 10000;
        if (500.0 * cos(anguloCameraX) >= 0)
        {
            ObsX = 500.0 * sin(anguloCameraX);
            ObsZ = 500.0 * cos(anguloCameraX);
        }
        glutPostRedisplay();
        break;
    case 'D':
        anguloCameraX += velocidadeCamera / 10000;
        if (500.0 * cos(anguloCameraX) >= 0)
        {
            ObsX = 500.0 * sin(anguloCameraX);
            ObsZ = 500.0 * cos(anguloCameraX);
        }
        glutPostRedisplay();
        break;
    }
}

void linhaVertical(int x1, int y1, int x2, int y2, int z)
{

    int dx, dy, incE, incNE, d, x, y;
    dx = x2 - x1;
    dy = y2 - y1;
    d = 2 * dy - dx;       // Valor inicial do d
    incE = 2 * dy;         // Incremento do E
    incNE = 2 * (dy - dx); // Incremento do NE
    x = x1;
    y = y1;

    glColor3f(WHITE);
    glPointSize(4.0f);
    glBegin(GL_POINTS);
    glVertex3d(x, y, z);

    while (y < y2)
    {

        if (d <= 0)
        {
            d = d + incE;
            x = x + 1;
            y = y + 1;
        }
        else
        {
            d = d + incNE;
            y = y + 1;
        }
        glVertex3d(x, y, z);
    }
    glEnd();
}

void linhaHorizontal(int x1, int y1, int x2, int y2)
{

    int dx, dy, incE, incNE, d, x, y, xFim, slope;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    d = 2 * dy - dx;       // Valor inicial do d
    incE = 2 * dy;         // Incremento do E
    incNE = 2 * (dy - dx); // Incremento do NE
    x = x1;
    y = y1;
    xFim = x2;

    glColor3f(WHITE);
    glPointSize(4.0f);
    glBegin(GL_POINTS);
    glVertex3d(x, y, 0.0);

    while (x < xFim)
    {

        x++;
        if (d < 0)
        {
            d += incE;
        }
        else
        {
            y++;
            d += incNE;
        }
        glVertex3d(x, y, 0.0);
    }
    glEnd();
}

void linhaZ(int x1, int z1, int x2, int z2, int y)
{

    int dx, dz, incE, incNE, d, x, z;
    dx = x2 - x1;
    dz = z2 - z1;
    d = 2 * dz - dx;       // Valor inicial do d
    incE = 2 * dz;         // Incremento do E
    incNE = 2 * (dz - dx); // Incremento do NE
    x = x1;
    z = z1;

    glColor3f(WHITE);
    glPointSize(4.0f);
    glBegin(GL_POINTS);
    glVertex3d(x, z, z);

    while (z < z2)
    {

        if (d <= 0)
        {
            d = d + incE;
            x = x + 1;
            z = z + 1;
        }
        else
        {
            d = d + incNE;
            z = z + 1;
        }
        glVertex3d(x, y, z);
    }
    glEnd();
}

void desenhaCirculo(int r, int x1, int y1, int op)
{

    int x = 0;
    int y = r;
    int d = 1 - r;

    void desenhaPontosDoCirculo(int, int, int, int, int);

    desenhaPontosDoCirculo(x1, y1, x, y, op);

    while (x < y)
    {
        x++;
        if (d < 0)
        {
            d += 2 * x + 1;
        }
        else
        {
            y--;
            d += 2 * (x - y) + 1;
        }
        desenhaPontosDoCirculo(x1, y1, x, y, op);
    }
}

void desenhaPontosDoCirculo(int x1, int y1, int x, int y, int op)
{

    glColor3f(WHITE);
    glBegin(GL_POINTS);

    if (op == 0 or op == 1)
    {
        glVertex3d(x1 + x, y1 - y, 0.0);
        glVertex3d(x1 + y, y1 - x, 0.0);
    }

    if (op == 0 or op == 2)
    {
        glVertex3d(x1 + x, y1 + y, 0.0);
        glVertex3d(x1 + y, y1 + x, 0.0);
    }

    if (op == 0 or op == 3)
    {
        glVertex3d(x1 - x, y1 + y, 0.0);
        glVertex3d(x1 - y, y1 + x, 0.0);
    }

    if (op == 0 or op == 4)
    {
        glVertex3d(x1 - x, y1 - y, 0.0);
        glVertex3d(x1 - y, y1 - x, 0.0);
    }

    glEnd();
}

void criarBola()
{
    GLUquadricObj *bola = gluNewQuadric();
    glPushMatrix();
    glTranslatef(xBola, yBola, zBola);
    glColor3f(YELLOW);
    gluSphere(bola, raioBola, 40, 40);
    glPopMatrix();
}
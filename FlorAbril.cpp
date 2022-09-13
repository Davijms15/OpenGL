#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <unistd.h>

using namespace std;

vector<vector<int>> colors;
int aux = 1;

void init(void)
{
   /* selecionar cor de fundo (preto) */
   glClearColor(0.0, 0.0, 0.0, 0.0);

   glMatrixMode(GL_PROJECTION); // Projecao 2D

   glOrtho(0.0, 500.0, 0.0, 400.0, -1.0, 1.0); // Definindo os limites da Porta de Visao (ViewPort)
}

void displayFcn(void)
{
   /* Limpar todos os pixels  */
   glClear(GL_COLOR_BUFFER_BIT);

   glColor3f(1.0, 1.0, .0);
   glBegin(GL_POLYGON);
   glVertex3f(249.0f, 250.0f, -1.0f);
   glVertex3f(251.0f, 250.0f, -1.0f);
   glVertex3f(249.0f, 100.0f, -1.0f);
   glVertex3f(251.0f, 100.0f, -1.0f);
   glEnd();

   /* Desenhar um polígono branco  */
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_TRIANGLES);
   glVertex2f(250.0f, 250.0f);
   glVertex2f(230.0f, 200.0f);
   glVertex2f(270.0f, 200.0f);
   glEnd();

   /* Desenhar um polígono vermelho */
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_TRIANGLES);
   glVertex2f(250.0f, 250.0f);
   glVertex2f(300.0f, 230.0f);
   glVertex2f(300.0f, 270.0f);
   glEnd();

   /* Desenhar um polígono verde */
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_TRIANGLES);
   glVertex2f(250.0f, 250.0f);
   glVertex2f(230.0f, 300.0f);
   glVertex2f(270.0f, 300.0f);
   glEnd();

   /* Desenhar um polígono vermelho */
   glColor3f(0.0, 0.0, 1.0);
   glBegin(GL_TRIANGLES);
   glVertex2f(250.0f, 250.0f);
   glVertex2f(200.0f, 270.0f);
   glVertex2f(200.0f, 230.0f);
   glEnd();

   /* Não esperar! */
   glFlush();
}

void controlRotation(unsigned char key, int a, int b)
{
   if (key)
   {
      glColor3f(colors[aux][0], colors[aux][1], colors[aux][2]);
      glBegin(GL_TRIANGLES);
      glVertex2f(250.0f, 250.0f);
      glVertex2f(230.0f, 200.0f);
      glVertex2f(270.0f, 200.0f);
      glEnd();

      glColor3f(colors[(aux + 1) % 4][0], colors[(aux + 1) % 4][1], colors[(aux + 1) % 4][2]);
      glBegin(GL_TRIANGLES);
      glVertex2f(250.0f, 250.0f);
      glVertex2f(300.0f, 230.0f);
      glVertex2f(300.0f, 270.0f);
      glEnd();

      glColor3f(colors[(aux + 2) % 4][0], colors[(aux + 2) % 4][1], colors[(aux + 2) % 4][2]);
      glBegin(GL_TRIANGLES);
      glVertex2f(250.0f, 250.0f);
      glVertex2f(230.0f, 300.0f);
      glVertex2f(270.0f, 300.0f);
      glEnd();

      glColor3f(colors[(aux + 3) % 4][0], colors[(aux + 3) % 4][1], colors[(aux + 3) % 4][2]);
      glBegin(GL_TRIANGLES);
      glVertex2f(250.0f, 250.0f);
      glVertex2f(200.0f, 270.0f);
      glVertex2f(200.0f, 230.0f);
      glEnd();

      aux = (aux + 1) % 4;
      sleep(1);
   }
   glFlush();
}

void createColors()
{
   colors.resize(4);
   for (int i = 0; i < 4; ++i)
   {
      colors[i].resize(3);
   }
   colors[0][0] = 1.0;
   colors[0][1] = 1.0;
   colors[0][2] = 1.0;

   colors[1][0] = 1.0;
   colors[1][1] = 0.0;
   colors[1][2] = 0.0;

   colors[2][0] = 0.0;
   colors[2][1] = 1.0;
   colors[2][2] = 0.0;

   colors[3][0] = 0.0;
   colors[3][1] = 0.0;
   colors[3][2] = 1.0;
}

int main(int argc, char **argv)
{
   createColors();

   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(500, 400);
   glutInitWindowPosition(200, 200);
   glutCreateWindow("Flor de Abril");

   init();

   glutDisplayFunc(displayFcn);
   glutKeyboardFunc(controlRotation);

   glutMainLoop();

   return 0;
}

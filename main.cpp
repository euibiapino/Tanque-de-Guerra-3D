#include <GL/glut.h>
#include <GL/glu.h>
#include <SOIL/SOIL.h>
#include <cmath>
#include <stdio.h>

enum ModoVisao { Tpessoa, Ppessoa };
ModoVisao modoVisao = Tpessoa;
float cameraDirecao = 1.5;

float cameraOffsetX = 0;
float cameraOffsetZ = 10;  
float cameraAltura = 5.0;


float anguloTanque = 0.0;
float anguloTorreta = 0.0;  

bool teclaW = false;
bool teclaA = false;
bool teclaS = false;
bool teclaD = false;

float posicaoTanqueX = 0.0, posicaoTanqueZ = 0.0, posicaoTanqueY = 0.0;

GLuint texturaCorpo, texturaTorreta, texturaCano, texturaTerreno, texturaEsteira; 

GLuint carregarTextura(const char* caminho) {
    GLuint texturaID;
    int largura, altura, canais;
    unsigned char* imagem = SOIL_load_image(caminho, &largura, &altura, &canais, SOIL_LOAD_AUTO);
    
    if (!imagem) {
        printf("Erro ao carregar a imagem: %s\n", SOIL_last_result());
        return 0;
    }

    glGenTextures(1, &texturaID);
    glBindTexture(GL_TEXTURE_2D, texturaID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    GLenum formato = (canais == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, formato, largura, altura, 0, formato, GL_UNSIGNED_BYTE, imagem);
    
    SOIL_free_image_data(imagem);
    return texturaID;
}


void desenharCorpo(float x, float y, float z) {

    glBindTexture(GL_TEXTURE_2D, texturaCorpo);
    glPushMatrix();
    glTranslatef(x, y, z); 
    glColor3f(1.0, 1.0, 1.0); 
    glScalef(2.9, 2.4, 3.9); 


    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -0.5, -1.25);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -0.5, -1.25);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 0.5, -1.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 0.5, -1.25);
    
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -0.5, 1.25);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -0.5, 1.25);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 0.5, 1.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 0.5, 1.25);
    
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -0.5, -1.25);
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -0.5, 1.25);
    glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, 0.5, 1.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 0.5, -1.25);
    
    glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -0.5, -1.25);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -0.5, 1.25);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 0.5, 1.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 0.5, -1.25);
    
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 0.5, -1.25);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 0.5, -1.25);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 0.5, 1.25);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 0.5, 1.25);
    glEnd();
    glPopMatrix();

}

void desenharEsteira(float x, float y, float z) {
    glBindTexture(GL_TEXTURE_2D, texturaEsteira);
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(1.9, 3, 11);

    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);

    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);

    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);

    glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, 0.5);

    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);

    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, -0.5, -0.5);

    glEnd();
    glPopMatrix();
}


void desenharTorreta(float x, float y, float z) {
    
    glPushMatrix();

    glTranslatef(x, y, z); 
    glRotatef(anguloTorreta, 0.0, 1.0, 0.0); 
    glBindTexture(GL_TEXTURE_2D, texturaTorreta);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(1.9, 14, 14);

    glBindTexture(GL_TEXTURE_2D, texturaCano);
    glPushMatrix();
    glTranslatef(0.0, 0.0, 5.0);
    glScalef(0.4, 0.4, 8.0);
    glutSolidCube(1.0); 
    glPopMatrix();

    glPopMatrix();

}

void desenharTanque() {
    
desenharCorpo(0, 1.2, 0);
desenharTorreta(0, 3, 0);
desenharEsteira(3.7, 1, 0.3);
desenharEsteira(-3.7, 1, 0.3);
}

void desenharTerreno() {
    glBindTexture(GL_TEXTURE_2D, texturaTerreno); 
    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, -0.5, -50.0);
    glTexCoord2f(50.0, 0.0); glVertex3f(50.0, -0.5, -50.0);
    glTexCoord2f(50.0, 50.0); glVertex3f(50.0, -0.5, 50.0);
    glTexCoord2f(0.0, 50.0); glVertex3f(-50.0, -0.5, 50.0);
    
    glEnd();
}


void exibir() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float cameraDistancia = 35.0;
    float cameraDesloAltura = 5.0;

    float cameraPosX = posicaoTanqueX;
    float cameraPosY = (modoVisao == Ppessoa) ? cameraAltura : 20;  
    float cameraPosZ = posicaoTanqueZ;
    
    float radianoTorreta = anguloTorreta * M_PI / 180.0;
    float cameraDirX = sin(radianoTorreta);
    float cameraDirZ = cos(radianoTorreta);

    if (modoVisao == Ppessoa) {
    gluLookAt(cameraPosX, cameraPosY, cameraPosZ,  
              cameraPosX + cameraDirX, cameraPosY, cameraPosZ + cameraDirZ,
              0.0, 1.0, 0.0);  
    } else {
        gluLookAt(cameraPosX - cameraDirX * cameraDistancia, 
                  cameraDesloAltura + 20, 
                  cameraPosZ - cameraDirZ * cameraDistancia, 
                  posicaoTanqueX, 
                  posicaoTanqueY, 
                  posicaoTanqueZ, 
                  0.0, 1.0, 0.0);
    }              

    float velocidade = 0.3;
    float radiano = anguloTanque * M_PI / 180.0;
    float dx = velocidade * sin(radiano);
    float dz = velocidade * cos(radiano);

    if (teclaA) {
        anguloTanque += 5.0;
    }
    if (teclaD) {
        anguloTanque -= 5.0;
    }
    if (teclaW) {
        posicaoTanqueX += dx;
        posicaoTanqueZ += dz;
    }
    if (teclaS) {
        posicaoTanqueX -= dx;
        posicaoTanqueZ -= dz;
    }

    desenharTerreno();

    glPushMatrix();
    glTranslatef(posicaoTanqueX, 0.0, posicaoTanqueZ); 
    glRotatef(anguloTanque, 0.0, 1.0, 0.0);
    desenharTanque();
    glPopMatrix();

    glutSwapBuffers();
}



void configurarIluminacao() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat luzAmbiente[] = { 0.8, 0.8, 0.8, 1.0 }; 
    GLfloat luzDifusa[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat luzSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat posicaoLuz[] = { 10.0, 10.0, 10.0, 1.0 }; 

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    
    GLfloat ambienteMaterial[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat difusoMaterial[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat especularMaterial[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat brilhoMaterial[] = { 80.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambienteMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difusoMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularMaterial);
    glMaterialfv(GL_FRONT, GL_SHININESS, brilhoMaterial);

    glShadeModel(GL_SMOOTH);
}

void inicializar() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    configurarIluminacao();
    texturaCorpo = carregarTextura("militar.jpg");
    texturaTorreta = carregarTextura("militar.jpg");
    texturaCano = carregarTextura("militar.jpg");
    texturaTerreno = carregarTextura("grama.jpg");
    texturaEsteira = carregarTextura("esteira.jpg");

    glClearColor(0.68f, 0.85f, 0.9f, 1.0f);   //68 85 90
}


void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 'w': case 'W':
            teclaW = true;
            break;
        case 's': case 'S':
            teclaS = true;
            break;
        case 'a': case 'A':
            teclaA = true;
            break;
        case 'd': case 'D':
            teclaD = true;
            break;
        case 'v': case 'V':
            modoVisao = (modoVisao == Tpessoa) ? Ppessoa : Tpessoa;
            break;    
    }
    glutPostRedisplay();
}

void tecladoSolto(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 'w':
            teclaW = false;
            break;
        case 's':
            teclaS = false;
            break;
        case 'a':
            teclaA = false;
            break;
        case 'd':
            teclaD = false;
            break;
    }
    glutPostRedisplay();
}


void teclasEspeciais(int tecla, int x, int y) {
    switch (tecla) {
        case GLUT_KEY_LEFT:
            anguloTorreta += 5.0;  
            break;
        case GLUT_KEY_RIGHT:
            anguloTorreta -= 5.0; 
            break;    
    }
    glutPostRedisplay(); 
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tanque 3D");
    inicializar();
    glutDisplayFunc(exibir);
    glutKeyboardFunc(teclado);
    glutKeyboardUpFunc(tecladoSolto);
    glutSpecialFunc(teclasEspeciais);
    glutMainLoop();
    return 0;
}
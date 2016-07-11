#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "Constants.h"
#include "Cube.h"
#include "lodepng.h"
#include "Shaderprogram.h"
#include "Piece.h"
#include "Declarations.h"
#include "Game.h"

using namespace glm;

Game* game;

//Uchwyty na shadery
ShaderProgram *shaderProgramWithTexture;
ShaderProgram *shaderProgramWithoutTexture;



//Wskaźnik na obiekt reprezentujący program cieniujący.

//Uchwyty na VAO i bufory wierzchołków
GLuint boardVao;
GLuint boardVerticesBuffer; //Uchwyt na bufor VBO przechowujący tablicę współrzędnych wierzchołków
GLuint boardColorsBuffer;  //Uchwyt na bufor VBO przechowujący tablicę kolorów
GLuint boardNormalsBuffer; //Uchwyt na bufor VBO przechowujący tablickę wektorów normalnych
GLuint boardCoordsBuffer;

//Kostka
float* vertices=Models::CubeInternal::vertices;
float* colors=Models::CubeInternal::colors;
float* normals=Models::CubeInternal::normals;
float* texCoords=Models::CubeInternal::texCoords;
int vertexCount=Models::CubeInternal::vertexCount;

//Zmienne i stale kamery
GLfloat cameraHorizontalAngle=0.0f;
GLfloat cameraVerticalAngle=PI/2.1; //Patrzenie z góry przy inicie

GLfloat cameraHorizontalAdd=0.05f;
GLfloat cameraVerticalAdd=0.05f;

glm::vec3 targetPosition=glm::vec3(0.0f, 0.0f, 0.0f);
GLfloat distanceFromTarget=20.0f;

GLfloat FieldOfView = 100.0f;

GLfloat FieldOfViewMin= 1.0f;
GLfloat FieldOfViewMax=1000.0f;


//ZMIENNE I STALE SWIATLA

float ambient[]={
        0,0,0,1
};

float diffuse[]={
        0.7,0.5,0.5,1,
};

float specular[]={
        0.5,0.5,0.5,1
};


float lightPos[]={
        0,-1,-1,0
};

const int shininess=50;

//ZMIENNE GLOBALNE

GLuint boardTexture;


//Procedura obsługi błędów
void error_callback(int error, const char* description) {
    fputs(description, stderr);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_W)
        cameraVerticalAngle+=cameraVerticalAdd;
    if(key == GLFW_KEY_S)
        cameraVerticalAngle-=cameraVerticalAdd;
    if(key == GLFW_KEY_A)
        cameraHorizontalAngle-=cameraHorizontalAdd;
    if(key == GLFW_KEY_D)
        cameraHorizontalAngle+=cameraHorizontalAdd;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(FieldOfView >= FieldOfViewMin && FieldOfView <= FieldOfViewMax)
        FieldOfView -= yoffset;
    if(FieldOfView <= FieldOfViewMin)
        FieldOfView = FieldOfViewMin;
    if(FieldOfView >= FieldOfViewMax)
        FieldOfView = FieldOfViewMax;
}

//Tworzy bufor VBO z tablicy
GLuint makeBuffer(void *data, int vertexCount, int vertexSize) {
    GLuint handle;

    glGenBuffers(1,&handle);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), który będzie zawierał tablicę danych
    glBindBuffer(GL_ARRAY_BUFFER,handle);  //Uaktywnij wygenerowany uchwyt VBO
    glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);//Wgraj tablicę do VBO

    return handle;
}

//Przypisuje bufor VBO do atrybutu
void assignVBOtoAttribute(ShaderProgram *shaderProgram,char* attributeName, GLuint bufVBO, int vertexSize) {
    GLuint location=shaderProgram->getAttribLocation(attributeName); //Pobierz numery slotów dla atrybutu
    glBindBuffer(GL_ARRAY_BUFFER,bufVBO);  //Uaktywnij uchwyt VBO
    glEnableVertexAttribArray(location); //Włącz używanie atrybutu o numerze slotu zapisanym w zmiennej location
    glVertexAttribPointer(location,vertexSize,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu location mają być brane z aktywnego VBO
}

void texturesInput(){

    //Wczytanie do pamięci komputera
    std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
    unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
//Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, "/home/piotrek/Dokumenty/3dChess/textures/marbleBoard.png");

//Import do pamięci karty graficznej
    glGenTextures(1,&boardTexture); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, boardTexture); //Uaktywnij uchwyt
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());


}


//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
    //************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
    //glClearColor(0, 0, 0, 1); //Czyść ekran na czarno
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Czyść ekran na niebieskawo
    glEnable(GL_DEPTH_TEST); //Włącz używanie Z-Bufora

    //glEnable(GL_LIGHTING); //Włącz tryb cieniowania
    //glEnable(GL_LIGHT0); //Włącz domyslne światło

    //SWIATLO

    //float lightPos[]={100,100,100,0};
    //glLightfv(GL_LIGHT0,GL_POSITION,lightPos);


    //WCZYTYWANIE TEKSTUR
    texturesInput();


    glfwSetKeyCallback(window, key_callback); //Zarejestruj procedurę obsługi klawiatury
    glfwSetScrollCallback(window, scroll_callback); //Zarejestruj procedure obslugi scrolla


    shaderProgramWithTexture =new ShaderProgram("/home/piotrek/Dokumenty/3dChess/shaders/vshaderWithTexture.txt", NULL, "/home/piotrek/Dokumenty/3dChess/shaders/fshaderWithTexture.txt"); //Wczytaj program cieniujący
    shaderProgramWithoutTexture=new ShaderProgram("/home/piotrek/Dokumenty/3dChess/shaders/vshaderWithoutTexture.txt",NULL,"/home/piotrek/Dokumenty/3dChess/shaders/fshaderWithoutTexture.txt"); //Wczytaj program cieniujący


    //*****Przygotowanie do rysowania pojedynczego obiektu*******
    //Zbuduj VBO z danymi obiektu do narysowania
    boardVerticesBuffer =makeBuffer(vertices, vertexCount, sizeof(float) * 4); //VBO ze współrzędnymi wierzchołków
    boardColorsBuffer =makeBuffer(colors, vertexCount, sizeof(float) * 4);//VBO z kolorami wierzchołków
    boardNormalsBuffer =makeBuffer(normals, vertexCount, sizeof(float) * 4);//VBO z wektorami normalnymi wierzchołków
    boardCoordsBuffer =makeBuffer(texCoords, vertexCount, sizeof(float) * 2);//VBO z wektorami normalnymi wierzchołków

    //Zbuduj VAO wiążący atrybuty z konkretnymi VBO
    glGenVertexArrays(1,&boardVao); //Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej

    glBindVertexArray(boardVao); //Uaktywnij nowo utworzony VAO

    assignVBOtoAttribute(shaderProgramWithTexture, "vertex", boardVerticesBuffer, 4); //"vertex" odnosi się do deklaracji "in vec4 vertex;" w vertex shaderze
    assignVBOtoAttribute(shaderProgramWithTexture, "color", boardColorsBuffer, 4); //"color" odnosi się do deklaracji "in vec4 color;" w vertex shaderze
    assignVBOtoAttribute(shaderProgramWithTexture, "normal", boardNormalsBuffer, 4); //"normal" odnosi się do deklaracji "in vec4 normal;" w vertex shaderze
    assignVBOtoAttribute(shaderProgramWithTexture, "texcoord", boardCoordsBuffer, 2); //"normal" odnosi się do deklaracji "in vec4 normal;" w vertex shaderze

    assignVBOtoAttribute(shaderProgramWithoutTexture, "vertex", boardVerticesBuffer, 4); //"vertex" odnosi się do deklaracji "in vec4 vertex;" w vertex shaderze
    assignVBOtoAttribute(shaderProgramWithoutTexture, "color", boardColorsBuffer, 4); //"color" odnosi się do deklaracji "in vec4 color;" w vertex shaderze
    assignVBOtoAttribute(shaderProgramWithoutTexture, "normal", boardNormalsBuffer, 4); //"normal" odnosi się do deklaracji "in vec4 normal;" w vertex shaderze

    glBindVertexArray(0); //Dezaktywuj VAO
    //******Koniec przygotowania obiektu************

    glEnable(GL_NORMALIZE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);

    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shininess);


}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram() {
    delete shaderProgramWithTexture; //Usunięcie programu cieniującego

    glDeleteVertexArrays(1,&boardVao); //Usunięcie vao
    glDeleteBuffers(1,&boardVerticesBuffer); //Usunięcie VBO z wierzchołkami
    glDeleteBuffers(1,&boardColorsBuffer); //Usunięcie VBO z kolorami
    glDeleteBuffers(1,&boardNormalsBuffer); //Usunięcie VBO z wektorami normalnymi

    glDeleteTextures(1,&boardTexture);


}




void drawObjectWithTexture(GLuint vao, ShaderProgram *shaderProgram, mat4 mP, mat4 mV, mat4 mM){

    //Włączenie programu cieniującego, który ma zostać użyty do rysowania
    //W tym programie wystarczyłoby wywołać to raz, w setupShaders, ale chodzi o pokazanie,
    //że mozna zmieniać program cieniujący podczas rysowania jednej sceny
    shaderProgram->use();

    //Przekaż do shadera macierze P,V i M.
    //W linijkach poniżej, polecenie:
    //  shaderProgramWithTexture->getUniformLocation("P")
    //pobiera numer slotu odpowiadającego zmiennej jednorodnej o podanej nazwie
    //UWAGA! "P" w powyższym poleceniu odpowiada deklaracji "uniform mat4 P;" w vertex shaderze,
    //a mP w glm::value_ptr(mP) odpowiada argumentowi  "mat4 mP;" TYM pliku.
    //Cała poniższa linijka przekazuje do zmiennej jednorodnej P w vertex shaderze dane z argumentu mP niniejszej funkcji
    //Pozostałe polecenia działają podobnie.
    glUniformMatrix4fv(shaderProgram->getUniformLocation("P"),1, false, glm::value_ptr(mP));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("V"),1, false, glm::value_ptr(mV));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(mM));

    glUniform4f(shaderProgram->getUniformLocation("lpos"),0,0,-5,1);


    //Uaktywnienie tekstury
    glBindTexture(GL_TEXTURE_2D,boardTexture);



    //Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powiązań slotów atrybutów z tablicami z danymi
    glBindVertexArray(vao);

    //Narysowanie obiektu

    glDrawArrays(GL_TRIANGLES,0,vertexCount);

    //Posprzątanie po sobie (niekonieczne w sumie jeżeli korzystamy z VAO dla każdego rysowanego obiektu)
    glBindVertexArray(0);
}

void drawObject(GLuint vao, ShaderProgram *shaderProgram, mat4 mP, mat4 mV, mat4 mM) {
    //Włączenie programu cieniującego, który ma zostać użyty do rysowania
    //W tym programie wystarczyłoby wywołać to raz, w setupShaders, ale chodzi o pokazanie,
    //że mozna zmieniać program cieniujący podczas rysowania jednej sceny
    shaderProgram->use();

    //Przekaż do shadera macierze P,V i M.
    //W linijkach poniżej, polecenie:
    //  shaderProgramWithTexture->getUniformLocation("P")
    //pobiera numer slotu odpowiadającego zmiennej jednorodnej o podanej nazwie
    //UWAGA! "P" w powyższym poleceniu odpowiada deklaracji "uniform mat4 P;" w vertex shaderze,
    //a mP w glm::value_ptr(mP) odpowiada argumentowi  "mat4 mP;" TYM pliku.
    //Cała poniższa linijka przekazuje do zmiennej jednorodnej P w vertex shaderze dane z argumentu mP niniejszej funkcji
    //Pozostałe polecenia działają podobnie.
    glUniformMatrix4fv(shaderProgram->getUniformLocation("P"),1, false, glm::value_ptr(mP));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("V"),1, false, glm::value_ptr(mV));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(mM));

    glUniform4f(shaderProgram->getUniformLocation("lpos"),0,0,-5,1);

    //Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powiązań slotów atrybutów z tablicami z danymi
    glBindVertexArray(vao);

    //Narysowanie obiektu

    glDrawArrays(GL_TRIANGLES,0,vertexCount);

    //Posprzątanie po sobie (niekonieczne w sumie jeżeli korzystamy z VAO dla każdego rysowanego obiektu)
    glBindVertexArray(0);
}

void drawBoard(GLuint boardvao, ShaderProgram *shaderProgram,glm::mat4 P,glm::mat4 V){

    //Wylicz macierz modelu rysowanego obiektu
    glm::mat4 M = glm::mat4(1.0f);

    M = glm::translate(M, glm::vec3(0.0f, -0.5f*BOARDSIDESIZE*BOARDHEIGHTRATIO, 0.0f));
    M = glm::scale(M, glm::vec3(0.5f*BOARDSIDESIZE, 0.5f*BOARDSIDESIZE*BOARDHEIGHTRATIO, 0.5f*BOARDSIDESIZE));



    //Narysuj plansze
    drawObjectWithTexture(boardVao, shaderProgramWithTexture, P, V, M);
}

void drawPiece(Tile piece,int horizontalIndex,int verticalIndex, GLuint piecevao,ShaderProgram *shaderProgram,glm::mat4 P,glm::mat4 V){

    //Wylicz macierz modelu rysowanego obiektu
    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, glm::vec3(float(horizontalIndex)-PIECEMOVINGCONSTANT, 0.5f*PIECESIZE, float(verticalIndex)-PIECEMOVINGCONSTANT));

    if(piece.type!=None){
        //Narysuj bierke
        drawObject(piecevao, shaderProgram, P, V, M);
    }



}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {
    //************Tutaj umieszczaj kod rysujący obraz******************l

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolorów

   /* glLineWidth(2.5);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(16.0, 0, 0);
    glEnd();
    */

    glm::mat4 P = glm::perspective(FieldOfView * PI / 180, (GLfloat)WINDOWWIDTH/(GLfloat)WINDOWHEIGHT, 1.0f, 50.0f); //Wylicz macierz rzutowania

    GLfloat camX = sin(cameraHorizontalAngle) * distanceFromTarget *cos(cameraVerticalAngle);
    GLfloat camZ = cos(cameraHorizontalAngle) * distanceFromTarget *cos(cameraVerticalAngle);
    GLfloat camY=sin(cameraVerticalAngle) * distanceFromTarget ;

    glm::mat4 V = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

    //Narysuj plansze
    drawBoard(boardVao,shaderProgramWithTexture,P,V);

    //TRANSLATE BOARD
    Tile** boardsnapshot=game->getBoardSnapshot();

    for(int j=0;j<TILECOUNT;j++){
        for (int i=0;i<TILECOUNT;i++){

            drawPiece(boardsnapshot[j][i],2*i,2*j,boardVao,shaderProgramWithoutTexture,P,V);
        }
    }





    //Przerzuć tylny bufor na przedni
    glfwSwapBuffers(window);

}

int main(void)
{

    game = new Game("/home/piotrek/Dokumenty/3dChess/games/1");

    //game->Move();


    GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

    glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

    if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
        fprintf(stderr, "Nie można zainicjować GLFW.\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(WINDOWWIDTH, WINDOWHEIGHT, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

    if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
    {
        fprintf(stderr, "Nie można utworzyć okna.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
    glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

    if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
        fprintf(stderr, "Nie można zainicjować GLEW.\n");
        exit(EXIT_FAILURE);
    }

    initOpenGLProgram(window); //Operacje inicjujące

    glfwSetTime(0); //Wyzeruj licznik czasu

    //Główna pętla
    while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
    {
        if(glfwGetTime()>=BREAKBETWEENMOVES){
            if(game->Move()) glfwSetTime(0);
            else break;
        }


        drawScene(window); //Wykonaj procedurę rysującą
        glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
    }

    freeOpenGLProgram();

    glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
    glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
    exit(EXIT_SUCCESS);
}
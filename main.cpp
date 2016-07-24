#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include "Constants.h"
#include "lodepng.h"
#include "Shaderprogram.h"
#include "Piece.h"
#include "Declarations.h"
#include "Game.h"
#include "models.h"
#include <string>
#include <string.h>

using namespace glm;


//Structy nie mogace byc w Declarations.h

struct VBOstruct{
    GLuint verticesBuffer;
    GLuint normalsBuffer;
    GLuint texCoordsBuffer;
    int vertexCount;
};

struct light_t{
    glm::vec3 position;
    glm::vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct spotlight_t {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct material_t {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};


//Uchwyty na shadery

//Wskaźnik na obiekt reprezentujący program cieniujący.
ShaderProgram *shaderProgram;

//Uchwyty na VAO i bufory wierzchołków
GLuint boardVao;
GLuint boardVerticesBuffer; //Uchwyt na bufor VBO przechowujący tablicę współrzędnych wierzchołków
GLuint boardNormalsBuffer; //Uchwyt na bufor VBO przechowujący tablickę wektorów normalnych
GLuint boardCoordsBuffer;

GLuint  PiecesVAO[PIECESAMOUNT];
VBOstruct PiecesVBO[PIECESAMOUNT];


//Zmienne i stale kamery
GLfloat cameraHorizontalAngle=0.0f;
GLfloat cameraVerticalAngle=PI/1.4; //Patrzenie z góry przy inicie

GLfloat cameraHorizontalAdd=0.05f;
GLfloat cameraVerticalAdd=0.05f;

glm::vec3 targetPosition=glm::vec3(0.0f, 0.0f, 0.0f);
GLfloat distanceFromTarget=15.0f;

GLfloat FieldOfView = 100.0f;

GLfloat FieldOfViewMin= 1.0f;
GLfloat FieldOfViewMax=1000.0f;

glm::vec3 camera;

//ZMIENNE GLOBALNE

Game* game;
OBJModel OBJModels[PIECESAMOUNT];
GLuint textures[TEXTURESAMOUNT];

light_t lights[2];
spotlight_t spotLight;

material_t boardMaterial;
material_t pieceMaterial;

Pole currentTile, previousTile;
bool newMove = true;
bool endFlag = false;

std::string wdpath = "/home/piotrek/Dokumenty/";
std::string gamefilename="1.pgn";
std::string gamepath=wdpath + "3dChess/games/" + gamefilename;

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_W)
        cameraVerticalAngle-=cameraVerticalAdd;
    if(key == GLFW_KEY_S)
        cameraVerticalAngle+=cameraVerticalAdd;
    if(key == GLFW_KEY_A)
        cameraHorizontalAngle-=cameraHorizontalAdd;
    if(key == GLFW_KEY_D)
        cameraHorizontalAngle+=cameraHorizontalAdd;
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        newMove = true;
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

void texturesInput(GLuint &textureHandler, string path){
    //Wczytanie do pamięci komputera
    std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
    unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
//Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, path);
//Import do pamięci karty graficznej
    glGenTextures(1,&textureHandler); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, textureHandler); //Uaktywnij uchwyt
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());

}

void modelsinit(){

    OBJModels[Pawn].vertices=pawnVertices;
    OBJModels[Pawn].normals=pawnNormals;
    OBJModels[Pawn].texcoords=pawnTexCoords;
    OBJModels[Pawn].vertexCount=pawnVertexCount;

    OBJModels[Rook].vertices=rookVertices;
    OBJModels[Rook].normals=rookNormals;
    OBJModels[Rook].texcoords=rookTexCoords;
    OBJModels[Rook].vertexCount=rookVertexCount;

    OBJModels[Knight].vertices=knightVertices;
    OBJModels[Knight].normals=knightNormals;
    OBJModels[Knight].texcoords=knightTexCoords;
    OBJModels[Knight].vertexCount=knightVertexCount;

    OBJModels[Bishop].vertices=bishopVertices;
    OBJModels[Bishop].normals=bishopNormals;
    OBJModels[Bishop].texcoords=bishopTexCoords;
    OBJModels[Bishop].vertexCount=bishopVertexCount;

    OBJModels[Queen].vertices=queenVertices;
    OBJModels[Queen].normals=queenNormals;
    OBJModels[Queen].texcoords=queenTexCoords;
    OBJModels[Queen].vertexCount=queenVertexCount;

    OBJModels[King].vertices=kingVertices;
    OBJModels[King].normals=kingNormals;
    OBJModels[King].texcoords=kingTexCoords;
    OBJModels[King].vertexCount=kingVertexCount;
}


void lightsinit(){

    lights[0].position=glm::vec3(0.0,10.0f,0.0f);
    lights[0].ambient=glm::vec3(0.2f, 0.2f, 0.2f);
    lights[0].diffuse=glm::vec3(0.5f, 0.5f, 0.5f);
    lights[0].specular=glm::vec3(0.2f, 0.2f, 0.2f);

    spotLight.position=glm::vec3(0.0f,-10.0f,0.0f);
    spotLight.direction=glm::vec3(0.0f,-1.0f,0.0f);
    spotLight.direction=glm::normalize(spotLight.direction);


    spotLight.cutOff=glm::cos(glm::radians(9.5f));
    spotLight.outerCutOff=glm::cos(glm::radians(10.0f));
    spotLight.constant=1.0f;
    spotLight.linear=0.09;
    spotLight.quadratic=0.032;
    spotLight.ambient=glm::vec3(1.0f, 1.0f, 1.0f);
    spotLight.diffuse=glm::vec3(0.0f, 1.0f, 0.0f);
    spotLight.specular=glm::vec3(0.0f, 1.0f, 0.0f);

}

void materialsinit(){

    boardMaterial.ambient=glm::vec3(1.0f, 0.5f, 0.31f);
    boardMaterial.diffuse=glm::vec3(1.0f, 0.5f, 0.31f);
    boardMaterial.specular=glm::vec3(0.508273,	0.508273,	0.508273);
    boardMaterial.shininess=32.0f;

    pieceMaterial.ambient=glm::vec3(1.0f, 0.5f, 0.31f);
    pieceMaterial.diffuse=glm::vec3(1.0f, 0.5f, 0.31f);
    pieceMaterial.specular=glm::vec3(0.5f, 0.5f, 0.5f);
    pieceMaterial.shininess=2.0f;

}


void texturesinit(){

    //WCZYTYWANIE TEKSTUR
    texturesInput(textures[board],wdpath + "3dChess/textures/marbleBoard.png");
    texturesInput(textures[white],wdpath + "3dChess/textures/white.png");
    texturesInput(textures[black],wdpath + "3dChess/textures/black.png");

}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {

    //************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
    glClearColor(0, 0, 0, 1); //Czyść ekran na czarno
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Czyść ekran na niebieskawo
    glEnable(GL_DEPTH_TEST); //Włącz używanie Z-Bufora

    modelsinit();
    lightsinit();
    materialsinit();
    texturesinit();

    glfwSetKeyCallback(window, key_callback); //Zarejestruj procedurę obsługi klawiatury
    glfwSetScrollCallback(window, scroll_callback); //Zarejestruj procedure obslugi scrolla

    shaderProgram =new ShaderProgram("/home/piotrek/Dokumenty/3dChess/shaders/vshaderWithTexture.txt", NULL, "/home/piotrek/Dokumenty/3dChess/shaders/fshaderWithTexture.txt"); //Wczytaj program cieniujący

    //*****Przygotowanie do rysowania pojedynczego obiektu*******
    //Zbuduj VBO z danymi obiektu do narysowania
    boardVerticesBuffer =makeBuffer(boardVertices, boardVertexCount, sizeof(float) * 4); //VBO ze współrzędnymi wierzchołków
    boardNormalsBuffer =makeBuffer(boardNormals, boardVertexCount, sizeof(float) * 4);//VBO z wektorami normalnymi wierzchołków
    boardCoordsBuffer =makeBuffer(boardTexCoords, boardVertexCount, sizeof(float) * 2);//VBO z wektorami normalnymi wierzchołków

    //Zbuduj VAO wiążący atrybuty z konkretnymi VBO
    glGenVertexArrays(1,&boardVao); //Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej

    glBindVertexArray(boardVao); //Uaktywnij nowo utworzony VAO

    assignVBOtoAttribute(shaderProgram, "vertex", boardVerticesBuffer, 4); //"vertex" odnosi się do deklaracji "in vec4 vertex;" w vertex shaderze
    assignVBOtoAttribute(shaderProgram, "normal", boardNormalsBuffer, 4); //"normal" odnosi się do deklaracji "in vec4 normal;" w vertex shaderze
    assignVBOtoAttribute(shaderProgram, "texcoord", boardCoordsBuffer, 2); //"normal" odnosi się do deklaracji "in vec4 normal;" w vertex shaderze

    /* INDEKSY W TABLICY PIECESVBO NA PODSTAWIE WARTOSCI PIECETYPE ENUM */

    for(int pieceIndex=0;pieceIndex<PIECESAMOUNT;pieceIndex++){

        PiecesVBO[pieceIndex].verticesBuffer =makeBuffer(OBJModels[pieceIndex].vertices, OBJModels[pieceIndex].vertexCount, sizeof(float) * 3); //VBO ze współrzędnymi wierzchołków
        PiecesVBO[pieceIndex].normalsBuffer =makeBuffer(OBJModels[pieceIndex].normals, OBJModels[pieceIndex].vertexCount, sizeof(float) * 3);//VBO z wektorami normalnymi wierzchołków
        PiecesVBO[pieceIndex].texCoordsBuffer =makeBuffer(OBJModels[pieceIndex].texcoords, OBJModels[pieceIndex].vertexCount, sizeof(float) * 2);//VBO z wektorami normalnymi wierzchołków
        PiecesVBO[pieceIndex].vertexCount= OBJModels[pieceIndex].vertexCount;

        //Zbuduj VAO wiążący atrybuty z konkretnymi VBO
        glGenVertexArrays(1,&PiecesVAO[pieceIndex]); //Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej

        glBindVertexArray(PiecesVAO[pieceIndex]); //Uaktywnij nowo utworzony VAO

        assignVBOtoAttribute(shaderProgram, "vertex", PiecesVBO[pieceIndex].verticesBuffer, 3); //"vertex" odnosi się do deklaracji "in vec4 vertex;" w vertex shaderze
        assignVBOtoAttribute(shaderProgram, "normal", PiecesVBO[pieceIndex].normalsBuffer, 3); //"normal" odnosi się do deklaracji "in vec4 normal;" w vertex shaderze
        assignVBOtoAttribute(shaderProgram, "texcoord", PiecesVBO[pieceIndex].texCoordsBuffer, 2); //"normal" odnosi się do deklaracji "in vec4 normal;" w vertex shaderze

        glBindVertexArray(0); //Dezaktywuj VAO

    }

    glEnable(GL_NORMALIZE);

}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram() {
    delete shaderProgram; //Usunięcie programu cieniującego

    glDeleteVertexArrays(1,&boardVao); //Usunięcie vao
    glDeleteBuffers(1,&boardVerticesBuffer); //Usunięcie VBO z wierzchołkami
    glDeleteBuffers(1,&boardNormalsBuffer); //Usunięcie VBO z wektorami normalnymi


    for(int i=0;i<TEXTURESAMOUNT;i++){
        glDeleteTextures(1,&textures[i]);
    }

}

void drawObject(GLuint vao, int vertexCount, ShaderProgram *shaderProgram, GLuint texture, mat4 mP, mat4 mV, mat4 mM,material_t material){

    //Włączenie programu cieniującego, który ma zostać użyty do rysowania
    //W tym programie wystarczyłoby wywołać to raz, w setupShaders, ale chodzi o pokazanie,
    //że mozna zmieniać program cieniujący podczas rysowania jednej sceny
    shaderProgram->use();

    //Przekaż do shadera macierze P,V i M.
    //W linijkach poniżej, polecenie:
    //  shaderProgram->getUniformLocation("P")
    //pobiera numer slotu odpowiadającego zmiennej jednorodnej o podanej nazwie
    //UWAGA! "P" w powyższym poleceniu odpowiada deklaracji "uniform mat4 P;" w vertex shaderze,
    //a mP w glm::value_ptr(mP) odpowiada argumentowi  "mat4 mP;" TYM pliku.
    //Cała poniższa linijka przekazuje do zmiennej jednorodnej P w vertex shaderze dane z argumentu mP niniejszej funkcji
    //Pozostałe polecenia działają podobnie.
    glUniformMatrix4fv(shaderProgram->getUniformLocation("P"),1, false, glm::value_ptr(mP));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("V"),1, false, glm::value_ptr(mV));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(mM));

    glUniform3f(shaderProgram->getUniformLocation("material.ambient"),material.ambient.r,material.ambient.g,material.ambient.b);
    glUniform3f(shaderProgram->getUniformLocation("material.diffuse"),material.diffuse.r,material.diffuse.g,material.diffuse.b);
    glUniform3f(shaderProgram->getUniformLocation("material.specular"),material.specular.r,material.specular.g,material.specular.b);
    glUniform1f(shaderProgram->getUniformLocation("material.shininess"),material.shininess);

    glUniform3f(shaderProgram->getUniformLocation("light1.position"),lights[0].position.x,lights[0].position.y,lights[0].position.z);
    glUniform3f(shaderProgram->getUniformLocation("light1.ambient"),lights[0].ambient.r,lights[0].ambient.g,lights[0].ambient.b);
    glUniform3f(shaderProgram->getUniformLocation("light1.diffuse"),lights[0].diffuse.r,lights[0].diffuse.g,lights[0].diffuse.b);
    glUniform3f(shaderProgram->getUniformLocation("light1.specular"),lights[0].specular.r,lights[0].specular.g,lights[0].specular.b);

    glUniform3f(shaderProgram->getUniformLocation("cameraPosition"), camera.x, camera.y, camera.z);

    glUniform3f(shaderProgram->getUniformLocation("spotLight.position"), spotLight.position.x, spotLight.position.y, spotLight.position.z);
    glUniform3f(shaderProgram->getUniformLocation("spotLight.direction"), spotLight.direction.x, spotLight.direction.y, spotLight.direction.z);
    glUniform3f(shaderProgram->getUniformLocation("spotLight.ambient"), spotLight.ambient.r, spotLight.ambient.g, spotLight.ambient.b);
    glUniform3f(shaderProgram->getUniformLocation("spotLight.diffuse"), spotLight.diffuse.r, spotLight.diffuse.g, spotLight.diffuse.b);
    glUniform3f(shaderProgram->getUniformLocation("spotLight.specular"), spotLight.specular.r, spotLight.specular.g, spotLight.specular.b);
    glUniform1f(shaderProgram->getUniformLocation("spotLight.constant"), spotLight.constant);
    glUniform1f(shaderProgram->getUniformLocation("spotLight.linear"), spotLight.linear);
    glUniform1f(shaderProgram->getUniformLocation("spotLight.quadratic"), spotLight.quadratic);
    glUniform1f(shaderProgram->getUniformLocation("spotLight.cutOff"), spotLight.cutOff);
    glUniform1f(shaderProgram->getUniformLocation("spotLight.outerCutOff"), spotLight.outerCutOff);

    //Uaktywnienie tekstury
    glBindTexture(GL_TEXTURE_2D,texture);

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
    drawObject(boardVao, boardVertexCount, shaderProgram, textures[board], P, V, M,boardMaterial);
}

void drawPiece(Tile piece,int horizontalIndex,int verticalIndex,ShaderProgram *shaderProgram,glm::mat4 P,glm::mat4 V){

    //Wylicz macierz modelu rysowanego obiektu
    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, glm::vec3(float(horizontalIndex)-PIECEMOVINGCONSTANT,0, float(verticalIndex)-PIECEMOVINGCONSTANT));

    if(piece.type!=None) {
        //Narysuj bierke
        drawObject(PiecesVAO[piece.type], PiecesVBO[piece.type].vertexCount, shaderProgram, textures[piece.colour], P, V, M, pieceMaterial);
    }

}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {
    //************Tutaj umieszczaj kod rysujący obraz******************l

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolorów

    glm::mat4 P = glm::perspective(FieldOfView * PI / 180, (GLfloat)WINDOWWIDTH/(GLfloat)WINDOWHEIGHT, 1.0f, 50.0f); //Wylicz macierz rzutowania

    camera.x=sin(cameraHorizontalAngle) * distanceFromTarget *cos(cameraVerticalAngle);
    camera.y=sin(cameraVerticalAngle) * distanceFromTarget;
    camera.z=cos(cameraHorizontalAngle) * distanceFromTarget *cos(cameraVerticalAngle);

    glm::mat4 V = glm::lookAt(glm::vec3(camera.x, camera.y, camera.z), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

    //Narysuj plansze
    drawBoard(boardVao, shaderProgram, P, V);

    //TRANSLATE BOARD
    Tile** boardsnapshot=game->getBoardSnapshot();


    for(int j=0;j<TILECOUNT;j++){
        for (int i=0;i<TILECOUNT;i++){
            drawPiece(boardsnapshot[j][i],2*(TILECOUNT-1-i),2*j, shaderProgram, P, V);
        }
    }

    //Przerzuć tylny bufor na przedni
    glfwSwapBuffers(window);

}

int main(void)
{
    currentTile.Row = -1;
    currentTile.Column = 1;
    previousTile.Row = -1;
    previousTile.Column = 1;

    //game = new Game(wdpath + "3dChess/games/1.pgn");
    game= new Game(gamepath);

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
        //if(glfwGetTime()>=BREAKBETWEENMOVES){
        if(!endFlag && newMove){
            game->Print();
            previousTile = currentTile;
            currentTile = game->Move();
            if(currentTile.Row * currentTile.Column >= 0){
                newMove = false;
                if(previousTile.Column * previousTile.Row >= 0) {
                    spotLight.position.x = (TILECOUNT-1-previousTile.Column) * BOARDSIDESIZE / TILECOUNT - PIECEMOVINGCONSTANT;
                    spotLight.position.y = 10.0f;
                    spotLight.position.z = previousTile.Row * BOARDSIDESIZE / TILECOUNT - PIECEMOVINGCONSTANT;
                }
            }
            else
            {
                endFlag = true;
                newMove = false;
            }
        }

        if(endFlag)
        {
            spotLight.specular=glm::vec3(1.0f, 0.0f, 0.0f);
            spotLight.ambient=glm::vec3(1.0f, 0.0f, 0.0f);
            spotLight.diffuse=glm::vec3(1.0f, 0.0f, 0.0f);
            spotLight.position.x = (TILECOUNT-1-previousTile.Column) * BOARDSIDESIZE / TILECOUNT - PIECEMOVINGCONSTANT;
            spotLight.position.y = 10.0f;
            spotLight.position.z = previousTile.Row * BOARDSIDESIZE / TILECOUNT - PIECEMOVINGCONSTANT;

            if(newMove)break;
        }

        drawScene(window); //Wykonaj procedurę rysującą
        glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
    }


    freeOpenGLProgram();

    glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
    glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
    exit(EXIT_SUCCESS);
}
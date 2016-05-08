#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Game.h"
#include "myCube.h"

using namespace std;

const float PI = 3.141592653589793f;

Game* game;
float speed = 0; // [radiany/s]


void key_callback(GLFWwindow* window, int key,
                  int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_LEFT) speed = -3.14;
        if (key == GLFW_KEY_RIGHT) speed = 3.14;
    }

    if (action == GLFW_RELEASE) {
        speed = 0;
    }
}

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
    //************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
    glClearColor(0, 0, 0, 1); //Czyść ekran na czarno
    //glEnable(GL_LIGHTING); //Włącz tryb cieniowania
    glEnable(GL_LIGHT0); //Włącz domyslne światło
    glEnable(GL_DEPTH_TEST); //Włącz używanie Z-Bufora
    glEnable(GL_COLOR_MATERIAL); //glColor3d ma modyfikować własności materiału

    glfwSetKeyCallback(window, key_callback);

}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float angle) {
    //************Tutaj umieszczaj kod rysujący obraz******************l

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolorów


    glm::mat4 V = glm::lookAt( //Wylicz macierz widoku
            glm::vec3(0.0f, 0.0f, -5.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 P = glm::perspective(50 * PI / 180, 1.0f, 1.0f, 50.0f); //Wylicz macierz rzutowania

    //Załaduj macierz rzutowania do OpenGL
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(P));

    //Przejdź w tryb pracy z macierzą Model-Widok
    glMatrixMode(GL_MODELVIEW);

    //Wylicz macierz obrotu o kąt angle wokół osi (0,1,1)
    glm::mat4 M = glm::mat4(1.0f);
    M = glm::rotate(M, angle, glm::vec3(0, 1, 1));
    glLoadMatrixf(glm::value_ptr(V*M)); //Załaduj wyliczoną macierz do OpenGL


    //Narysuj model
    glEnableClientState(GL_VERTEX_ARRAY); //Włącz używanie tablicy wierzchołków
    glEnableClientState(GL_COLOR_ARRAY); //Włącz używanie tablicy kolorów

    glVertexPointer(3, GL_FLOAT, 0, myCubeVertices); //Wskaż tablicę wierzchołków
    glColorPointer(3, GL_FLOAT, 0, myCubeColors); //Wskaż tablicę kolorów

    glDrawArrays(GL_QUADS, 0, myCubeVertexCount); //Wykonaj rysowanie

    glDisableClientState(GL_VERTEX_ARRAY); //Wyłącz używanie tablicy wierzchołków
    glDisableClientState(GL_COLOR_ARRAY); //Wyłącz używanie tablicy kolorów

    //Przerzuć tylny bufor na przedni
    glfwSwapBuffers(window);

}


int main(int argc, char** argv)
{
    //wczytanie gry
    game = new Game("C:\\Users\\Jan\\Desktop\\semestr4\\grafika\\fischer_petrosian_1959.pgn");

    GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

    glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

    if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
        fprintf(stderr, "Nie można zainicjować GLFW.\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

    if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
    {
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

    float angle = 0; //Kąt obrotu torusa
    glfwSetTime(0); //Wyzeruj licznik czasu

    //koniec programu Witka


    game->Print();
    //game->printGameInfo();
    cout<<endl;

    while(game->Move());

    /*int i = 1;
    while(true)
    {
        cout<<i++<<". ";
        if(!game->Move())break;
        game->Print();
        if(!game->Move())break;
        game->Print();
    }*/

    game->Print();

    //Główna pętla
    while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
    {
        angle += speed*glfwGetTime(); //Zwiększ kąt o prędkość kątową razy czas jaki upłynął od poprzedniej klatki
        glfwSetTime(0); //Wyzeruj licznik czasu
        drawScene(window,angle); //Wykonaj procedurę rysującą
        glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
    }

    glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
    glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
    exit(EXIT_SUCCESS);


    delete game;

    return 0;
}
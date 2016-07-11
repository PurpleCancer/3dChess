//
// Created by piotrek on 05.07.16.
//

#ifndef INC_3DCHESS_DRAWING_H
#define INC_3DCHESS_DRAWING_H

namespace Drawing{
    //void drawTile(float x,float y, float z,float r);

    void drawTile(float x,float y, float z,float r) {

        glBegin(GL_QUADS);
        // glTranslatef(x, y, z);
        //   glColor3f(1.0f, 1.0f, 1.0f);

        // front
        // glNormal3f(0.0f, 0.0f, 1.0f);
        glNormal3f(0.0f, -1.0f, 1.0f);
        glVertex3f(x - 0.5f, y - 0.2f, z + 0.5f);
        glNormal3f(0.0f, 1.0f, 1.0f);
        glVertex3f(x - 0.5f, y + 0.2f, z + 0.5f);
        glNormal3f(0.0f, 1.0f, 1.0f);
        glVertex3f(x + 0.5f, y + 0.2f, z + 0.5f);
        glNormal3f(0.0f, -1.0f, 1.0f);
        glVertex3f(x + 0.5f, y - 0.2f, z + 0.5f);
        //  glColor3f(0.0f, 1.0f, 1.0f);
        // right
        //    glNormal3f(1.0f, 0.0f, 0.0f);
        glNormal3f(1.0f, -1.0f, 0.0f);
        glVertex3f(x + 0.5f, y - 0.2f, z - 0.5f);
        glNormal3f(1.0f, 1.0f, 0.0f);
        glVertex3f(x + 0.5f, y + 0.2f, z - 0.5f);
        glNormal3f(1.0f, 1.0f, 0.0f);
        glVertex3f(x + 0.5f, y + 0.2f, z + 0.5f);
        glNormal3f(1.0f, -1.0f, 0.0f);
        glVertex3f(x + 0.5f, y - 0.2f, z + 0.5f);
        // glColor3f(1.0f, 0.0f, 1.0f);

        // left
        //    glNormal3f(-1.0f, 0.0f, 0.0f);
        glNormal3f(-1.0f, -1.0f, 0.0f);
        glVertex3f(x - 0.5f, y - 0.2f, z - 0.5f);
        glNormal3f(-1.0f, -1.0f, 0.0f);
        glVertex3f(x - 0.5f, y - 0.2f, z + 0.5f);
        glNormal3f(-1.0f, 1.0f, 0.0f);
        glVertex3f(x - 0.5f, y + 0.2f, z + 0.5f);
        glNormal3f(-1.0f, 1.0f, 0.0f);
        glVertex3f(x - 0.5f, y + 0.2f, z - 0.5f);

        //  glColor3f(1.0f, 1.0f, 0.0f);

        // back
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(x - 0.5f, y - 0.2f, z - 0.5f);
        glVertex3f(x - 0.5f, y + 0.2f, z - 0.5f);
        glVertex3f(x + 0.5f, y + 0.2f, z - 0.5f);
        glVertex3f(x + 0.5f, y - 0.2f, z - 0.5f);

        //glColor3f(1.0f, 0.0f, 0.0f);

        // top
        //    glNormal3f(0.0f, 0.0f, -1.0f);
        glNormal3f(0.0f, -1.0f, -1.0f);
        glVertex3f(x - 0.5f, y + 0.2f, z - 0.5f);
        glNormal3f(-0.0f, 1.0f, -1.0f);
        glVertex3f(x - 0.5f, y + 0.2f, z + 0.5f);
        glNormal3f(0.0f, 1.0f, -1.0f);
        glVertex3f(x + 0.5f, y + 0.2f, z + 0.5f);
        glNormal3f(0.0f, 1.0f, -1.0f);
        glVertex3f(x + 0.5f, y + 0.2f, z - 0.5f);

        glEnd();
    }

    void draw_BlackArea()
    {
            glBegin(GL_QUADS);
            glColor3f(0.05f,0.05f,0.05f);
            glTranslatef(0.0f,0.0f,0.0f);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(1.50f,0.0f,0.0f);
            glVertex3f(1.5f,0.3f,0.0f);
            glVertex3f(0.0f,0.3f,0.0f);
            glEnd();
            glBegin(GL_QUADS);
            glColor3f(0.05f,0.05f,0.05f);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(0.0f,0.0f,-1.5f);
            glVertex3f(0.0f,0.3f,-1.5f);
            glVertex3f(0.0f,0.3f,0.0f);
            glEnd();
            glBegin(GL_QUADS);
            glColor3f(0.05f,0.05f,0.05f);
            glVertex3f(1.5f,0.0f,0.0f);
            glVertex3f(1.5f,0.0f,-1.5f);
            glVertex3f(1.5f,0.3f,-1.5f);
            glVertex3f(1.5f,0.3f,0.0f);
            glEnd();
            glBegin(GL_QUADS);
            glColor3f(0.05f,0.05f,0.05f);
            glVertex3f(0.0f,0.0f,-1.5f);
            glVertex3f(1.50f,0.0f,-1.5f);
            glVertex3f(1.5f,0.3f,-1.5f);
            glVertex3f(0.0f,0.3f,-1.5f);
            glEnd();
            glBegin(GL_QUADS);
            glColor3f(0.05f,0.05f,0.05f);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(1.50f,0.0f,0.0f);
            glVertex3f(1.5f,0.0f,-1.5f);
            glVertex3f(0.0f,0.0f,-1.5f);
            glEnd();
            glBegin(GL_QUADS);
            glColor3f(0.0f,0.0f,0.0f);
            glVertex3f(0.0f,0.3f,0.0f);
            glVertex3f(1.50f,0.3f,0.0f);
            glVertex3f(1.5f,0.3f,-1.5f);
            glVertex3f(0.0f,0.3f,-1.5f);
            glEnd();
    }

    void draw_WhiteArea()
    {
            glBegin(GL_QUADS);
            glColor3f(0.05f,0.05f,0.05f);
            glTranslatef(0.0f,0.0f,0.0f);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(1.50f,0.0f,0.0f);
            glVertex3f(1.5f,0.3f,0.0f);
            glVertex3f(0.0f,0.3f,0.0f);
            glEnd();
            glBegin(GL_QUADS);
            glColor3f(0.05f,0.05f,0.05f);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(0.0f,0.0f,-1.5f);
            glVertex3f(0.0f,0.3f,-1.5f);
            glVertex3f(0.0f,0.3f,0.0f);
            glEnd();
            glBegin(GL_QUADS);
            glColor3f(0.05f,0.05f,0.05f);
            glVertex3f(1.5f,0.0f,0.0f);
            glVertex3f(1.5f,0.0f,-1.5f);
            glVertex3f(1.5f,0.3f,-1.5f);
            glVertex3f(1.5f,0.3f,0.0f);
            glEnd();
            glBegin(GL_QUADS);
            glColor3f(0.05f,0.05f,0.05f);
            glVertex3f(0.0f,0.0f,-1.5f);
            glVertex3f(1.50f,0.0f,-1.5f);
            glVertex3f(1.5f,0.3f,-1.5f);
            glVertex3f(0.0f,0.3f,-1.5f);
            glEnd();
            glBegin(GL_QUADS);
            glColor3f(0.05f,0.05f,0.05f);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(1.50f,0.0f,0.0f);
            glVertex3f(1.5f,0.0f,-1.5f);
            glVertex3f(0.0f,0.0f,-1.5f);
            glEnd();
            glBegin(GL_QUADS);
            glColor3f(0.52f,0.37f,0.26f);
            glVertex3f(0.0f,0.3f,0.0f);
            glVertex3f(1.50f,0.3f,0.0f);
            glVertex3f(1.5f,0.3f,-1.5f);
            glVertex3f(0.0f,0.3f,-1.5f);
            glEnd();
    }



    }

#endif //INC_3DCHESS_DRAWING_H


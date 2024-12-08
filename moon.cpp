#include "moon.h"
#include <cmath>

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include "globals.h"

Moon::Moon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
    this->distanceFromPlanet = distanceFromPlanet;
    this->orbitTime = orbitTime;
    this->rotationTime = rotationTime;
    this->radius = radius;
    this->textureHandle = textureHandle;
}

void Moon::calculatePosition(float time)
{
    // menemukan sudut orientasi orbit di sekitar planet
    float angle = time * 3.1419f / orbitTime;

    // menggunakan trigonometri untuk menemukan posisi di ruang
    position[0] = sin(angle) * distanceFromPlanet;
    position[1] = cos(angle) * distanceFromPlanet;
    position[2] = 0;

    // menemukan rotasi planet di sekitar porosnya
    rotation = time * 360 / rotationTime;
}

void Moon::render(void)
{
    // menerjemahkan ke posisi yang benar
    glPushMatrix();

    // memutar untuk putaran planet
    glBindTexture(GL_TEXTURE_2D, textureHandle);

    // merender sebagai objek quadric bola GLU
    glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);
    glRotatef(-rotation, 0.0f, 0.0f, 1.0f);

    // mengikat tekstur planet
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, true);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    // merender sebagai objek quadric bola GLU
    gluSphere(quadric, radius * planetSizeScale, 30, 30);

    // menggambar orbit
    glPopMatrix();
}

void Moon::renderOrbit(void)
{
    // menggambar orbit
    glBegin(GL_LINE_STRIP);

    // loop melalui 0 hingga 2pi dengan peningkatan sudut 0.1
    for (float angle = 0.0f; angle < 6.283185307f; angle += 0.1f)
    {
        glVertex3f(sin(angle) * distanceFromPlanet * distanceScale, cos(angle) * distanceFromPlanet * distanceScale, 0.0f);
    }
    glVertex3f(0.0f, distanceFromPlanet * distanceScale, 0.0f);

    glEnd();
}
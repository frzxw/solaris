#include "planet.h"
#include <cmath>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include "globals.h"

float planetSizeScale = 0.000005f;

Planet::Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	this->distanceFromSun = distanceFromSun;
	this->orbitTime = orbitTime;
	this->rotationTime = rotationTime;
	this->radius = radius;
	this->textureHandle = textureHandle;
}

// Menghitung posisinya di ruang 3D dalam orbit menggunakan nilai waktu yang diberikan
void Planet::calculatePosition(float time)
{
	// menemukan sudut orientasi orbit di sekitar matahari
	float angle = time * 3.1419f / orbitTime;

	// menggunakan trigonometri untuk menemukan posisi di ruang
	position[0] = sin(angle) * distanceFromSun;
	position[1] = cos(angle) * distanceFromSun;
	position[2] = 0;

	// menemukan rotasi planet di sekitar porosnya
	rotation = time * 360 / rotationTime;

	// menghitung posisi bulan
	for (int i = 0; i < moons.size(); i++)
	{
		moons[i].calculatePosition(time);
	}
}

// Merender ke layar
void Planet::render(void)
{
	glPushMatrix();

	// menerjemahkan ke posisi yang benar
	glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);

	// memutar untuk putaran planet
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);

	// mengikat tekstur planet
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	// merender sebagai objek quadric bola GLU
	GLUquadricObj *quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	if (distanceFromSun < 0.001f) // jika ini adalah matahari, jangan merender terlalu besar, dan nonaktifkan pencahayaan
	{
		float radiusScaled = radius * planetSizeScale;
		if (radiusScaled > 0.5f)
			radiusScaled = 0.5f;

		glDisable(GL_LIGHTING);
		gluSphere(quadric, radiusScaled, 30, 30);
		glEnable(GL_LIGHTING);
	}
	else
	{
		gluSphere(quadric, radius * planetSizeScale, 30, 30);
	}

	glPopMatrix();
}

// merender lingkaran orbit planet ini
void Planet::renderOrbit(void)
{
	// menggambar garis strip
	glBegin(GL_LINE_STRIP);

	// loop dari 0 hingga 2*PI dan menggambar di sekitar radius orbit menggunakan trigonometri
	for (float angle = 0.0f; angle < 6.283185307f; angle += 0.05f)
	{
		glVertex3f(sin(angle) * distanceFromSun * distanceScale, cos(angle) * distanceFromSun * distanceScale, 0.0f);
	}
	glVertex3f(0.0f, distanceFromSun * distanceScale, 0.0f);

	glEnd();

	// merender orbit bulan
	glPushMatrix();
	// menerjemahkan ke pusat planet ini untuk menggambar orbit bulan di sekitarnya
	glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);
	// menggambar orbit bulan
	for (int i = 0; i < moons.size(); i++)
	{
		moons[i].renderOrbit();
	}
	glPopMatrix();
}

// Mendapatkan posisinya dalam satuan ruang 3D dunia (setelah penskalaan) dan menempatkannya ke dalam vektor 3D
void Planet::getPosition(float *vec)
{
	vec[0] = position[0] * distanceScale;
	vec[1] = position[1] * distanceScale;
	vec[2] = position[2] * distanceScale;
}

// mendapatkan radius planet ini
float Planet::getRadius(void)
{
	return radius;
}

void Planet::addMoon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	moons.push_back(Moon(distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle));
}
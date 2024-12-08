#ifndef PLANET_H
#define PLANET_H

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>
#include <vector>
#include "moon.h"

class Planet
{
private:
	// jarak dari matahari
	float distanceFromSun;

	// waktu yang dibutuhkan untuk menyelesaikan 1 orbit
	float orbitTime;

	// waktu yang dibutuhkan untuk berputar 360 derajat
	float rotationTime;

	// radius planet itu sendiri
	float radius;

	// tekstur yang digunakan untuk rendering
	GLuint textureHandle;

	// posisinya dalam ruang 3d
	float position[3];
	// rotasinya di sekitar porosnya
	float rotation;

	// daftar bulan yang dimiliki planet ini
	std::vector<Moon> moons;

public:
	// Jarak dalam satuan km (kilometer) dan waktu dalam satuan hari bumi (365,25 waktu orbit untuk bumi)
	Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	// Hitung posisinya dalam ruang 3d di orbit menggunakan nilai waktu yang diberikan
	void calculatePosition(float time);

	// Render ke layar
	void render(void);

	// render lingkaran orbit planet ini
	void renderOrbit(void);

	// Dapatkan posisinya dalam satuan ruang dunia 3d (setelah penskalaan) dan masukkan ke dalam vektor 3d
	void getPosition(float *vec);

	// dapatkan radius planet ini
	float getRadius(void);

	// tambahkan bulan ke planet ini
	void addMoon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);
};

#endif
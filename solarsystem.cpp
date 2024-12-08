#include "solarsystem.h"

SolarSystem::SolarSystem()
{
	
}

// menghitung posisi dan logika semua planet
void SolarSystem::calculatePositions(float time)
{
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].calculatePosition(time);
	}
}

// menambahkan planet dengan data yang diberikan
void SolarSystem::addPlanet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	planets.push_back(Planet(distanceFromSun, orbitTime, rotationTime, radius, textureHandle));
}

// merender planet dengan opengl
void SolarSystem::render()
{
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].render();
	}
}

// merender gambar orbit
void SolarSystem::renderOrbits()
{
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].renderOrbit();
	}
}

// mendapatkan posisi dalam satuan ruang 3d dari planet yang diberikan (ditentukan oleh indeksnya dalam daftar) dan menempatkannya ke dalam vektor 3d vec
void SolarSystem::getPlanetPosition(int index, float* vec)
{
	planets[index].getPosition(vec);
}

// mendapatkan radius planet pada indeks yang diberikan dalam daftar planet
float SolarSystem::getRadiusOfPlanet(int index)
{
	return planets[index].getRadius();
}

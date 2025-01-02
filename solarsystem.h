#include <Windows.h>
#include <gl\GL.h>
#include <vector>

#include "planet.h"

class SolarSystem	
{
private:
	std::vector<Planet> planets;

public:
	SolarSystem();

	// menghitung posisi dan logika semua planet
	void calculatePositions(float time);

	// Tambahkan planet dengan data yang diberikan
	void addPlanet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	// Tambahkan bulan ke planet dengan indeks yang diberikan
	void addMoon(int planetIndex, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	// render planet dengan opengl
	void render();

	// render gambar orbit
	void renderOrbits();

	// dapatkan posisi dalam satuan ruang 3d dari planet yang diberikan (ditentukan oleh indeksnya dalam daftar) dan masukkan ke dalam vektor 3d vec
	void getPlanetPosition(int index, float *vec);

	// dapatkan radius planet pada indeks yang diberikan dalam daftar planet
	float getRadiusOfPlanet(int index);

	void showHelp();
};
#include <Windows.h>
#include <gl\GL.h>
#include <vector>

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
	void getPosition(float* vec);

	// dapatkan radius planet ini
	float getRadius(void);
};
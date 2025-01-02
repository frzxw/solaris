#include <cmath>
#include <cstdlib>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\gl.h>
#include <gl\glut.h>
#include <gl\glu.h>
#include <mmsystem.h>
#include "tga.h"
#include "solarsystem.h"
#include "camera.h"
#include "globals.h"

// ukuran layar
int screenWidth, screenHeight;

// Tekstur TGA yang berisi dialog bantuan, bintang, dan bulan
TGA *help, *stars, *moon;
// toggle jika dialog bantuan diaktifkan
bool helpDialogue = true;
// toggle jika orbit ditampilkan
bool showOrbits = true;
// menyimpan indeks planet terakhir yang dipilih dengan tombol angka 1 hingga 9
int planetSelected = 1;

// Instance utama dari tata surya
SolarSystem solarSystem;

// Instance dari kamera
Camera camera;

// Ini mengontrol simulasi waktu
double time;
double timeSpeed;

// menyimpan status kontrol untuk kamera - jika true, tombol untuk kontrol tersebut sedang ditekan
struct ControlStates
{
	bool forward, backward, left, right, yawLeft, yawRight, pitchUp,
		pitchDown, rollLeft, rollRight;
} controls;

// fungsi timer yang dipanggil setiap 10ms atau lebih
void timer(int)
{
	glutPostRedisplay();		 // post untuk fungsi display
	glutTimerFunc(10, timer, 0); // batasi gambar frame hingga 100fps
}

// membuat angka acak hingga maksimum yang ditentukan
float random(float max)
{
	return (float)(std::rand() % 1000) * max * 0.001;
}

void addMoon()
{
	// menambahkan bulan ke planet yang dipilih dengan jarak acak dari planet dan ukuran acak
	solarSystem.addMoon(planetSelected,
						(500 + random(1500)) * solarSystem.getRadiusOfPlanet(planetSelected),
						10 + random(100), 0.5 + random(20),
						solarSystem.getRadiusOfPlanet(planetSelected) * (0.05f + random(0.2f)), moon->getTextureHandle());
}

void backsound()
{
	PlaySound(TEXT("sounds/background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	// Mengurangi volume backsound
	waveOutSetVolume(0, 0x50005000); // Volume 50%
}

void info()
{
	PlaySound(TEXT("sounds/info.wav"), NULL, SND_FILENAME | SND_ASYNC);
	// Menambahkan volume info
	waveOutSetVolume(0, 0xFFFF0000); // Volume 100%
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // warna background hitam
	glShadeModel(GL_SMOOTH);		  // shading model
	glEnable(GL_TEXTURE_2D);		  // mengaktifkan tekstur

	// mengatur pencahayaan
	glEnable(GL_LIGHTING);						  // mengaktifkan pencahayaan
	glMatrixMode(GL_MODELVIEW);					  // mengatur matriks modelview
	glLoadIdentity();							  // mengatur matriks identitas
	GLfloat matSpecular[] = {1.0, 1.0, 1.0, 1.0}; // warna specular
	GLfloat matAmbience[] = {0.3, 0.3, 0.3, 1.0}; // warna ambience
	GLfloat matShininess[] = {20.0};			  // shininess
	glClearColor(0.0, 0.0, 0.0, 0.0);			  // warna background hitam
	glShadeModel(GL_SMOOTH);					  // shading model
	backsound();								  // memainkan musik latar belakang
	info();										  // memainkan informasi

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);	// mengatur warna specular
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess); // mengatur shininess
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbience);	// mengatur warna ambience

	GLfloat lightAmbient[] = {0.3, 0.3, 0.3, 1.0};	// warna ambient
	GLfloat lightDiffuse[] = {1.0, 1.0, 1.0, 1.0};	// warna diffuse
	GLfloat lightSpecular[] = {1.0, 1.0, 1.0, 1.0}; // warna specular

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);	  // mengatur warna ambient
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);	  // mengatur warna diffuse
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular); // mengatur warna specular

	glEnable(GL_LIGHTING);	// mengaktifkan pencahayaan
	glEnable(GL_LIGHT0);	// mengaktifkan lampu 0
	glDisable(GL_LIGHTING); // menonaktifkan pencahayaan

	// Memuat semua data gambar
	help = new TGA("images/help.tga");
	stars = new TGA("images/stars2.tga");
	moon = new TGA("images/moon.tga");

	TGA *sun = new TGA("images/sun.tga");
	TGA *mercury = new TGA("images/mercury.tga");
	TGA *venus = new TGA("images/venus.tga");
	TGA *earth = new TGA("images/earth.tga");
	TGA *mars = new TGA("images/mars.tga");
	TGA *jupiter = new TGA("images/jupiter.tga");
	TGA *saturn = new TGA("images/saturn.tga");
	TGA *uranus = new TGA("images/uranus.tga");
	TGA *neptune = new TGA("images/neptune.tga");

	// Menambahkan semua planet dengan data yang akurat. Jarak diukur dalam km, waktu diukur dalam hari bumi.
	solarSystem.addPlanet(0, 1, 500, 695500, sun->getTextureHandle());					   // matahari
	solarSystem.addPlanet(57910000, 88, 58.6, 2440, mercury->getTextureHandle());		   // mercury
	solarSystem.addPlanet(108200000, 224.65, 243, 6052, venus->getTextureHandle());		   // venus
	solarSystem.addPlanet(149600000, 365, 1, 6371, earth->getTextureHandle());			   // earth
	solarSystem.addPlanet(227939100, 686, 1.03f, 3389, mars->getTextureHandle());		   // mars
	solarSystem.addPlanet(778500000, 4332, 0.4139, 69911, jupiter->getTextureHandle());	   // jupiter
	solarSystem.addPlanet(1433000000, 10759, 0.44375, 58232, saturn->getTextureHandle());  // saturn
	solarSystem.addPlanet(2877000000, 30685, 0.718056, 25362, uranus->getTextureHandle()); // uranus
	solarSystem.addPlanet(4503000000, 60188, 0.6713, 24622, neptune->getTextureHandle());  // neptune

	solarSystem.addMoon(3, 7000000, 27.3, 27.3, 1738, moon->getTextureHandle()); // test moon for the earth

	// mengatur waktu
	time = 2.552f;
	timeSpeed = 0.1f;

	// reset kontrol
	controls.forward = false;
	controls.backward = false;
	controls.left = false;
	controls.right = false;
	controls.rollRight = false;
	controls.rollLeft = false;
	controls.pitchDown = false;
	controls.pitchUp = false;
	controls.yawLeft = false;
	controls.yawRight = false;

	timer(0);
}

void drawCube(void);

void display(void)
{
	// memperbarui logika dan simulasi
	time += timeSpeed;
	solarSystem.calculatePositions(time);

	if (controls.forward)
		camera.forward();
	if (controls.backward)
		camera.backward();
	if (controls.left)
		camera.left();
	if (controls.right)
		camera.right();
	if (controls.yawLeft)
		camera.yawLeft();
	if (controls.yawRight)
		camera.yawRight();
	if (controls.rollLeft)
		camera.rollLeft();
	if (controls.rollRight)
		camera.rollRight();
	if (controls.pitchUp)
		camera.pitchUp();
	if (controls.pitchDown)
		camera.pitchDown();

	// membersihkan buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	// mengatur matriks perspektif untuk merender dunia 3D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0f, (float)screenWidth / (float)screenHeight, 0.001f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// melakukan transformasi orientasi kamera
	camera.transformOrientation();

	// menggambar skybox
	glBindTexture(GL_TEXTURE_2D, stars->getTextureHandle());
	drawCube();

	// melakukan transformasi translasi kamera
	camera.transformTranslation();

	GLfloat lightPosition[] = {0.0, 0.0, 0.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	// merender tata surya
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	solarSystem.render();
	glDisable(GL_LIGHTING);

	// mungkin merender orbit
	if (showOrbits)
		solarSystem.renderOrbits();

	glDisable(GL_DEPTH_TEST);

	// mengatur matriks ortho untuk menampilkan UI (dialog bantuan)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, (GLdouble)screenHeight, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glFlush();
	glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y)
{
	// memeriksa tombol angka
	if (key > '0' && key <= '9')
	{
		// menunjuk pada planet yang ditentukan
		float vec[3];
		solarSystem.getPlanetPosition(key - '0', vec);
		camera.pointAt(vec);

		// memilih planet tersebut
		planetSelected = key - '0';
	}
	switch (key)
	{
	case '-':
		timeSpeed /= 2.0f; // mengurangi laju waktu
		break;
	case '=':
		timeSpeed *= 2.0f; // menggandakan laju waktu
		break;
	case 'h':
		helpDialogue = !helpDialogue; // toggle dialog bantuan
		break;
	case '[':
		planetSizeScale /= 1.2; // memperkecil skala planet
		break;
	case ']':
		planetSizeScale *= 1.2; // memperbesar skala planet
		break;
	case 'o':
		showOrbits = !showOrbits; // toggle tampilkan orbit
		break;
	case 'm':
		addMoon(); // menambahkan bulan ke planet yang dipilih
		break;
	case 'r':
		planetSizeScale = distanceScale;
		break;
	case ',':
		camera.slowDown(); // memperlambat kamera
		break;
	case '.':
		camera.speedUp(); // mempercepat kamera
		break;
		// ini semua adalah kontrol kamera
	case 'w':
		controls.forward = true;
		break;
	case 's':
		controls.backward = true;
		break;
	case 'a':
		controls.left = true;
		break;
	case 'd':
		controls.right = true;
		break;
	case 'e':
		controls.rollRight = true;
		break;
	case 'q':
		controls.rollLeft = true;
		break;
	case 'i':
		controls.pitchDown = true;
		break;
	case 'k':
		controls.pitchUp = true;
		break;
	case 'j':
		controls.yawLeft = true;
		break;
	case 'l':
		controls.yawRight = true;
		break;
	}
}

void keyUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		controls.forward = false;
		break;
	case 's':
		controls.backward = false;
		break;
	case 'a':
		controls.left = false;
		break;
	case 'd':
		controls.right = false;
		break;
	case 'e':
		controls.rollRight = false;
		break;
	case 'q':
		controls.rollLeft = false;
		break;
	case 'i':
		controls.pitchDown = false;
		break;
	case 'k':
		controls.pitchUp = false;
		break;
	case 'j':
		controls.yawLeft = false;
		break;
	case 'l':
		controls.yawRight = false;
		break;
	}
}

void reshape(int w, int h)
{
	screenWidth = w;
	screenHeight = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

int main(int argc, char **argv)
{
	// inisialisasi GLUT
	glutInit(&argc, argv);
	// inisialisasi layar
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// membuat window
	glutInitWindowSize(1200, 700);
	// mengatur posisi window
	glutInitWindowPosition(100, 100);
	// memberi nama window
	glutCreateWindow("Solaris");
	// inisialisasi
	init();
	// menampilkan window
	glutDisplayFunc(display);
	// menampilkan reshape
	glutReshapeFunc(reshape);
	// mengatur keyboard
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	// menjalankan loop
	glutMainLoop();
	return 0;
}

void drawCube(void)
{
	glBegin(GL_QUADS);
	// sisi baru
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	// sisi baru
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	// sisi baru
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	// sisi baru
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	// sisi baru
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	// sisi baru
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();
}
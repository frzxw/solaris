#include <Windows.h>
#include <gl\GL.h>

// Ini adalah kelas yang memuat file TGA ke dalam tekstur opengl
class TGA
{
private:
	// handle untuk tekstur di opengl
	GLuint textureHandle;
public:
	// Membangun dan memuat TGA ke dalam opengl dari jalur file gambar yang diberikan
	TGA(const char* imagePath);

	// Mengembalikan handle ke tekstur yang dibuat dari gambar, untuk mengikat ke opengl
	GLuint getTextureHandle(void);
};
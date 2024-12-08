class Camera
{
private:
	float forwardVec[3]; // vektor menghadap ke depan untuk orientasi kamera
	float rightVec[3];	 // vektor kanan untuk orientasi kamera
	float upVec[3];		 // vektor atas untuk orientasi kamera
	float position[3];	 // vektor posisi untuk translasi kamera

	float cameraSpeed;	   // kecepatan gerak kamera
	float cameraTurnSpeed; // kecepatan rotasi kamera

public:
	Camera(void); // konstruktor untuk menginisialisasi kamera

	void transformOrientation(void); // mengubah orientasi kamera berdasarkan vektor orientasi

	void transformTranslation(void); // mengubah translasi kamera berdasarkan vektor posisi

	void pointAt(float *targetVec); // mengarahkan kamera ke suatu titik tertentu di ruang 3d

	void speedUp(void); // meningkatkan kecepatan kamera

	void slowDown(void); // mengurangi kecepatan kamera

	void forward(void); // menggerakkan kamera ke depan

	void left(void); // menggerakkan kamera ke kiri

	void right(void); // menggerakkan kamera ke kanan

	void backward(void); // menggerakkan kamera ke belakang

	void rollRight(void); // memutar kamera ke kanan di sekitar sumbu forward

	void rollLeft(void); // memutar kamera ke kiri di sekitar sumbu forward

	void pitchUp(void); // memiringkan kamera ke atas di sekitar sumbu right

	void pitchDown(void); // memiringkan kamera ke bawah di sekitar sumbu right

	void yawLeft(void); // memutar kamera ke kiri di sekitar sumbu up

	void yawRight(void); // memutar kamera ke kanan di sekitar sumbu up
};

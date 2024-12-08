#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <cmath>
#include "camera.h"

// sistem kamera yang kami kerjakan dikendalikan seperti pesawat luar angkasa
// sehingga keyboard akan mengatur roll, arah, dan gerakan
// kami merepresentasikannya dengan 4 vektor
// vektor up, forward, dan right untuk orientasi di semua sumbu
// serta vektor position untuk translasi

// berikut adalah beberapa fungsi vektor yang kami buat untuk mempermudah penggunaan vektor

// mengatur vec ke (x, y, z)
void vectorSet(float *vec, float x, float y, float z)
{
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
}

// menambahkan v2 ke v1
void vectorAdd(float *v1, float *v2)
{
    v1[0] += v2[0];
    v1[1] += v2[1];
    v1[2] += v2[2];
}

// menyalin v2 ke v1
void vectorCopy(float *v1, float *v2)
{
    v1[0] = v2[0];
    v1[1] = v2[1];
    v1[2] = v2[2];
}

// mengalikan vec dengan skalar
void vectorMul(float *vec, float scalar)
{
    vec[0] *= scalar;
    vec[1] *= scalar;
    vec[2] *= scalar;
}

// menemukan panjang vektor menggunakan pythagoras
float lengthOfVec(float *vec)
{
    return sqrtf(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

// menormalisasi vektor agar panjangnya menjadi 1
void normaliseVec(float *vec)
{
    vectorMul(vec, 1 / lengthOfVec(vec));
}

// membuat matriks rotasi 3x3 dari sudut dan sumbu yang diberikan serta pointer ke matriks 3x3
void rotationMatrix(float *matrix, float *axis, float angle)
{
    // menggunakan http://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
    float cos1 = cos(angle);
    float cos2 = 1 - cos1;
    float sin1 = sin(angle);

    matrix[0] = cos1 + axis[0] * axis[0] * cos2;
    matrix[1] = axis[0] * axis[1] * cos2 - axis[2] * sin1;
    matrix[2] = axis[0] * axis[2] * cos2 + axis[1] * sin1;

    matrix[3] = axis[1] * axis[0] * cos2 + axis[2] * sin1;
    matrix[4] = cos1 + axis[1] * axis[1] * cos2;
    matrix[5] = axis[1] * axis[2] * cos2 - axis[0] * sin1;

    matrix[6] = axis[2] * axis[0] * cos2 - axis[1] * sin1;
    matrix[7] = axis[2] * axis[1] * cos2 + axis[0] * sin1;
    matrix[8] = cos1 + axis[2] * axis[2] * cos2;
}

// mengalikan vektor v1 dengan matriks dan menyimpan hasilnya ke vektor v2
void mulVecBy(float *v1, float *matrix, float *v2)
{
    v2[0] = v1[0] * matrix[0] + v1[1] * matrix[1] + v1[2] * matrix[2];
    v2[1] = v1[0] * matrix[3] + v1[1] * matrix[4] + v1[2] * matrix[5];
    v2[2] = v1[0] * matrix[6] + v1[1] * matrix[7] + v1[2] * matrix[8];
}

// memutar vektor v1 di sekitar sumbu v2 dengan sudut tertentu dan menyimpan hasilnya ke v3
void rotateAroundVec(float *v1, float *v2, float angle, float *v3)
{
    // membuat matriks rotasi
    float matrix[16];
    rotationMatrix(matrix, v2, angle);

    // mengalikan dengan matriks
    mulVecBy(v1, matrix, v3);
}

Camera::Camera(void)
{
    cameraSpeed = 0.005f;
    cameraTurnSpeed = 0.01f;
    // mengatur nilai default untuk vektor - diperoleh sudut pandang yang baik terhadap planet, nilainya didapatkan menggunakan debugger
    /*      forwardVec  0x00ab354c {-0.398769796, 0.763009906, -0.508720219}  float[3]
+       upVec       0x00ab3564 {-0.235630989, 0.450859368, 0.860931039}   float[3]
+       rightVec    0x00ab3558 {0.886262059, 0.463184059, 0.000000000}    float[3]
+       position    0x00ab3570 {0.764331460, -1.66760659, 0.642456770}    float[3] */
    vectorSet(position, 0.764331460f, -1.66760659f, 0.642456770);
    vectorSet(forwardVec, -0.398769796f, 0.763009906f, -0.508720219f);
    vectorSet(rightVec, 0.886262059f, 0.463184059f, 0.000000000f);
    vectorSet(upVec, -0.235630989f, 0.450859368f, 0.860931039f);
}

// mentransformasi matriks pandangan OpenGL untuk kamera
void Camera::transformOrientation(void)
{
    // melihat ke arah vektor orientasi
    gluLookAt(0, 0, 0, forwardVec[0], forwardVec[1], forwardVec[2], upVec[0], upVec[1], upVec[2]);
}

// mentransformasi matriks pandangan OpenGL untuk translasi
void Camera::transformTranslation(void)
{
    // menerjemahkan untuk meniru posisi kamera
    glTranslatef(-position[0], -position[1], -position[2]);
}

// mengarahkan kamera ke titik tertentu di ruang 3D
void Camera::pointAt(float *targetVec)
{
    float tempVec[3];
    float up[3] = {0.0f, 0.0f, 1.0f};

    // pertama, menghitung vektor maju baru dengan mengurangi posisi target dari posisi kamera
    forwardVec[0] = targetVec[0] - position[0];
    forwardVec[1] = targetVec[1] - position[1];
    forwardVec[2] = targetVec[2] - position[2];
    // kemudian, menormalkan panjangnya menjadi 1
    normaliseVec(forwardVec);

    // sekarang, untuk mendapatkan vektor kanan, putar vektor maju -pi/2 di sekitar sumbu z
    rotateAroundVec(forwardVec, up, -1.57079632679f, tempVec);
    // dan hilangkan komponen y untuk membuatnya datar
    tempVec[2] = 0;
    // kemudian normalkan
    normaliseVec(tempVec);
    // dan tetapkan ke rightVec
    vectorCopy(rightVec, tempVec);

    // sekarang, hitung vektor atas dengan memutar vektor maju pi/2 di sekitar vektor kanan
    rotateAroundVec(forwardVec, rightVec, 1.57079632679f, tempVec);
    vectorCopy(upVec, tempVec);
}

// mempercepat kamera
void Camera::speedUp(void)
{
    if (cameraSpeed < 1.0f)
        cameraSpeed *= 2;
}

// memperlambat kamera
void Camera::slowDown(void)
{
    if (cameraSpeed > 0.000001f)
        cameraSpeed /= 2;
}

// menggerakkan kamera ke depan
void Camera::forward(void)
{
    // membuat vektor gerakan dengan kecepatan yang sesuai menghadap arah maju
    float vec[3];
    vectorCopy(vec, forwardVec);
    vectorMul(vec, cameraSpeed);

    // menambahkan vektor gerakan ke vektor posisi
    vectorAdd(position, vec);
}

// menggerakkan kamera ke belakang
void Camera::backward(void)
{
    // membuat vektor gerakan dengan kecepatan yang sesuai menghadap arah belakang
    float vec[3];
    vectorCopy(vec, forwardVec);
    vectorMul(vec, -cameraSpeed); // -cameraSpeed untuk mundur

    // menambahkan vektor gerakan ke vektor posisi
    vectorAdd(position, vec);
}

// bergerak ke kiri
void Camera::left(void)
{
    // membuat vektor gerakan dengan kecepatan yang sesuai menghadap ke kiri
    float vec[3];
    vectorCopy(vec, rightVec);
    vectorMul(vec, -cameraSpeed); // -cameraSpeed untuk kiri

    // menambahkan vektor gerakan ke vektor posisi
    vectorAdd(position, vec);
}

// bergerak ke kanan
void Camera::right(void)
{
    // membuat vektor gerakan dengan kecepatan yang sesuai menghadap ke kanan
    float vec[3];
    vectorCopy(vec, rightVec);
    vectorMul(vec, cameraSpeed);

    // menambahkan vektor gerakan ke vektor posisi
    vectorAdd(position, vec);
}

// menggulung kamera ke kanan
void Camera::rollRight(void)
{
    float tempVec[3];
    // memutar vektor atas dan kanan di sekitar sumbu vektor maju untuk menggulung
    rotateAroundVec(upVec, forwardVec, cameraTurnSpeed, tempVec);
    vectorCopy(upVec, tempVec);

    rotateAroundVec(rightVec, forwardVec, cameraTurnSpeed, tempVec);
    vectorCopy(rightVec, tempVec);
}

// menggulung kamera ke kiri
void Camera::rollLeft(void)
{
    float tempVec[3];
    // memutar vektor atas dan kanan di sekitar sumbu vektor maju untuk menggulung
    rotateAroundVec(upVec, forwardVec, -cameraTurnSpeed, tempVec);
    vectorCopy(upVec, tempVec);

    rotateAroundVec(rightVec, forwardVec, -cameraTurnSpeed, tempVec);
    vectorCopy(rightVec, tempVec);
}

// memiringkan kamera ke atas
void Camera::pitchUp(void)
{
    float tempVec[3];
    // memutar vektor maju dan atas di sekitar sumbu vektor kanan untuk memiringkan
    rotateAroundVec(forwardVec, rightVec, cameraTurnSpeed, tempVec);
    vectorCopy(forwardVec, tempVec);

    rotateAroundVec(upVec, rightVec, cameraTurnSpeed, tempVec);
    vectorCopy(upVec, tempVec);
}

// memiringkan kamera ke bawah
void Camera::pitchDown(void)
{
    float tempVec[3];
    // memutar vektor maju dan atas di sekitar sumbu vektor kanan untuk memiringkan
    rotateAroundVec(forwardVec, rightVec, -cameraTurnSpeed, tempVec);
    vectorCopy(forwardVec, tempVec);

    rotateAroundVec(upVec, rightVec, -cameraTurnSpeed, tempVec);
    vectorCopy(upVec, tempVec);
}

// memutar kamera ke kiri
void Camera::yawLeft(void)
{
    float tempVec[3];
    // memutar vektor maju dan kanan di sekitar sumbu vektor atas untuk memutar
    rotateAroundVec(forwardVec, upVec, cameraTurnSpeed, tempVec);
    vectorCopy(forwardVec, tempVec);

    rotateAroundVec(rightVec, upVec, cameraTurnSpeed, tempVec);
    vectorCopy(rightVec, tempVec);
}

// memutar kamera ke kanan
void Camera::yawRight(void)
{
    float tempVec[3];
    // memutar vektor maju dan kanan di sekitar sumbu vektor atas untuk memutar
    rotateAroundVec(forwardVec, upVec, -cameraTurnSpeed, tempVec);
    vectorCopy(forwardVec, tempVec);

    rotateAroundVec(rightVec, upVec, -cameraTurnSpeed, tempVec);
    vectorCopy(rightVec, tempVec);
}

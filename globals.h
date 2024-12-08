// Ini mengurangi skala jarak planet dalam simulasi. Misalnya, jika skalanya adalah 0.00000001
// dan sebuah planet berjarak 149600000km dari matahari, maka akan digambar pada jarak 1.496 unit
// dalam ruang 3d dari matahari
const float distanceScale = 0.00000001f;

// Ini mengurangi skala ukuran planet dalam simulasi. Misalnya, jika radius sebuah planet
// adalah 6,371km dan skalanya adalah 0.0001f, maka akan digambar dengan radius 0.6371 unit
extern float planetSizeScale;

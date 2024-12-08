# Dokumentasi Proyek

Selamat datang di Proyek Solaris! Proyek ini mensimulasikan tata surya dengan planet dan bulan, memungkinkan Anda untuk menavigasi dan berinteraksi dengan benda-benda langit. Proyek ini dibangun menggunakan OpenGL dan GLUT untuk rendering dan interaksi.

## Struktur File

- `main.cpp`: Titik masuk utama aplikasi. Menangani inisialisasi, rendering, dan input pengguna.
- `solarsystem.cpp`: Mengelola tata surya, termasuk planet dan posisinya.
- `planet.cpp`: Mendefinisikan kelas `Planet` dan logika renderingnya.
- `moon.cpp`: Mendefinisikan kelas `Moon` dan logika renderingnya.
- `tga.cpp`: Menangani pemuatan file gambar TGA untuk tekstur.
- `camera.cpp`: Mengelola sistem kamera untuk navigasi dan tampilan.
- `camera.h`, `planet.h`, `moon.h`, `solarsystem.h`: File header untuk kelas masing-masing.

## Kompilasi

Untuk mengompilasi proyek, gunakan perintah berikut:

```sh
g++ [main.cpp](http://_vscodecontentref_/0) [solarsystem.cpp](http://_vscodecontentref_/1) [planet.cpp](http://_vscodecontentref_/2) [moon.cpp](http://_vscodecontentref_/3) [tga.cpp](http://_vscodecontentref_/4) [camera.cpp](http://_vscodecontentref_/5) -o [solaris.exe](http://_vscodecontentref_/6) -lopengl32 -lglu32 -lfreeglut -lwinmm
```

### Kontrol

- **Gerakan**: Gunakan `W`, `A`, `S`, `D` untuk bergerak maju, kiri, mundur, dan kanan.
- **Rotasi**: Gunakan `I`, `K` untuk pitch atas dan bawah, `J`, `L` untuk roll kiri dan kanan, dan `Q`, `E` untuk yaw kiri dan kanan.
- **Kontrol Kecepatan**: Gunakan `<` dan `>` untuk mengubah kecepatan gerakan, `-` dan `=`/`+` untuk menyesuaikan kecepatan waktu.
- **Pemilihan Planet**: Gunakan `1-9` untuk memilih planet yang berbeda.
- **Penyesuaian Skala**: Gunakan `[` dan `]` untuk mengubah skala planet, `R` untuk mengatur ulang ke skala realistis.
- **Visualisasi Orbit**: Gunakan `O` untuk mengaktifkan/nonaktifkan jalur orbit.
- **Menambahkan Bulan**: Gunakan `M` untuk menambahkan bulan ke planet yang dipilih.

### Daftar Planet

1. **Merkurius**
2. **Venus**
3. **Bumi**
4. **Mars**
5. **Yupiter**
6. **Saturnus**
7. **Uranus**
8. **Neptunus**

### Fitur

- **Gerakan Planet yang Realistis**: Planet dan bulan bergerak dalam orbit mereka berdasarkan data astronomi nyata.
- **Kamera Interaktif**: Navigasi melalui tata surya dengan kamera yang meniru kontrol pesawat luar angkasa.
- **Skala Dinamis**: Sesuaikan skala planet untuk visibilitas yang lebih baik atau proporsi yang realistis.
- **Jalur Orbit**: Visualisasikan orbit planet dan bulan.

### Nikmati Perjalanan Anda!

Jelajahi keajaiban tata surya dengan Proyek Solaris. Navigasi melalui ruang angkasa, amati gerakan planet, dan nikmati keindahan kosmos. Selamat menjelajah!

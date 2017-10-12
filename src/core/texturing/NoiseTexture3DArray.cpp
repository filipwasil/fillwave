// The MIT License (MIT)
//
// Copyright (c) 2013 Dan Ginsburg, Budirijanto Purnomo
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

//
// Book:      OpenGL(R) ES 3.0 Programming Guide, 2nd Edition
// Authors:   Dan Ginsburg, Budirijanto Purnomo, Dave Shreiner, Aaftab Munshi
// ISBN-10:   0-321-93388-5
// ISBN-13:   978-0-321-93388-1
// Publisher: Addison-Wesley Professional
// URLs:      http://www.opengles-book.com
//            http://my.safaribooksonline.com/book/animation-and-3d/9780133440133
//
// Noise3D.c
//
//    This is an example that demonstrates generating and using
//    a 3D noise texture.
//
// #define _USE_MATH_DEFINES

#include <fillwave/Fillwave.h>

#define NOISE_TABLE_MASK   255

#define FLOOR(x)           ((int)(x) - ((x) < 0 && (x) != (int)(x)))
#define smoothstep(t)      ( t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f ) )
#define lerp(t, a, b)      ( a + t * (b - a) )
#ifdef _WIN32
#define srandom srand
#define random rand
#endif

// lattice gradients 3D noise
static float gradientTable[256 * 3];

// permTable describes a random permutatin of 8-bit values from 0 to 255.
static unsigned char permTable[256] = {
    0xE1,
    0x9B,
    0xD2,
    0x6C,
    0xAF,
    0xC7,
    0xDD,
    0x90,
    0xCB,
    0x74,
    0x46,
    0xD5,
    0x45,
    0x9E,
    0x21,
    0xFC,
    0x05,
    0x52,
    0xAD,
    0x85,
    0xDE,
    0x8B,
    0xAE,
    0x1B,
    0x09,
    0x47,
    0x5A,
    0xF6,
    0x4B,
    0x82,
    0x5B,
    0xBF,
    0xA9,
    0x8A,
    0x02,
    0x97,
    0xC2,
    0xEB,
    0x51,
    0x07,
    0x19,
    0x71,
    0xE4,
    0x9F,
    0xCD,
    0xFD,
    0x86,
    0x8E,
    0xF8,
    0x41,
    0xE0,
    0xD9,
    0x16,
    0x79,
    0xE5,
    0x3F,
    0x59,
    0x67,
    0x60,
    0x68,
    0x9C,
    0x11,
    0xC9,
    0x81,
    0x24,
    0x08,
    0xA5,
    0x6E,
    0xED,
    0x75,
    0xE7,
    0x38,
    0x84,
    0xD3,
    0x98,
    0x14,
    0xB5,
    0x6F,
    0xEF,
    0xDA,
    0xAA,
    0xA3,
    0x33,
    0xAC,
    0x9D,
    0x2F,
    0x50,
    0xD4,
    0xB0,
    0xFA,
    0x57,
    0x31,
    0x63,
    0xF2,
    0x88,
    0xBD,
    0xA2,
    0x73,
    0x2C,
    0x2B,
    0x7C,
    0x5E,
    0x96,
    0x10,
    0x8D,
    0xF7,
    0x20,
    0x0A,
    0xC6,
    0xDF,
    0xFF,
    0x48,
    0x35,
    0x83,
    0x54,
    0x39,
    0xDC,
    0xC5,
    0x3A,
    0x32,
    0xD0,
    0x0B,
    0xF1,
    0x1C,
    0x03,
    0xC0,
    0x3E,
    0xCA,
    0x12,
    0xD7,
    0x99,
    0x18,
    0x4C,
    0x29,
    0x0F,
    0xB3,
    0x27,
    0x2E,
    0x37,
    0x06,
    0x80,
    0xA7,
    0x17,
    0xBC,
    0x6A,
    0x22,
    0xBB,
    0x8C,
    0xA4,
    0x49,
    0x70,
    0xB6,
    0xF4,
    0xC3,
    0xE3,
    0x0D,
    0x23,
    0x4D,
    0xC4,
    0xB9,
    0x1A,
    0xC8,
    0xE2,
    0x77,
    0x1F,
    0x7B,
    0xA8,
    0x7D,
    0xF9,
    0x44,
    0xB7,
    0xE6,
    0xB1,
    0x87,
    0xA0,
    0xB4,
    0x0C,
    0x01,
    0xF3,
    0x94,
    0x66,
    0xA6,
    0x26,
    0xEE,
    0xFB,
    0x25,
    0xF0,
    0x7E,
    0x40,
    0x4A,
    0xA1,
    0x28,
    0xB8,
    0x95,
    0xAB,
    0xB2,
    0x65,
    0x42,
    0x1D,
    0x3B,
    0x92,
    0x3D,
    0xFE,
    0x6B,
    0x2A,
    0x56,
    0x9A,
    0x04,
    0xEC,
    0xE8,
    0x78,
    0x15,
    0xE9,
    0xD1,
    0x2D,
    0x62,
    0xC1,
    0x72,
    0x4E,
    0x13,
    0xCE,
    0x0E,
    0x76,
    0x7F,
    0x30,
    0x4F,
    0x93,
    0x55,
    0x1E,
    0xCF,
    0xDB,
    0x36,
    0x58,
    0xEA,
    0xBE,
    0x7A,
    0x5F,
    0x43,
    0x8F,
    0x6D,
    0x89,
    0xD6,
    0x91,
    0x5D,
    0x5C,
    0x64,
    0xF5,
    0x00,
    0xD8,
    0xBA,
    0x3C,
    0x53,
    0x69,
    0x61,
    0xCC,
    0x34,
};

void initNoiseTable() {
  int i;
  float a;
  float x, y, z, r/*, theta*/;
  float gradients[256 * 3];
  unsigned int *p, *psrc;

  srandom(0);

  // build gradient table for 3D noise
  for (i = 0; i < 256; i++) {
    /*
     * calculate 1 - 2 * random number
     */
    a = (random() % 32768) / 32768.0f;
    z = (1.0f - 2.0f * a);

    r = sqrtf(1.0f - z * z); // r is radius of circle

    a = (random() % 32768) / 32768.0f;
    /*theta = (2.0f * (float) M_PI * a);*/
    x = (r * cosf(a));
    y = (r * sinf(a));

    gradients[i * 3] = x;
    gradients[i * 3 + 1] = y;
    gradients[i * 3 + 2] = z;
  }

  // use the index in the permutation table to load the
  // gradient values from gradients to gradientTable
  p = (unsigned int *) gradientTable;
  psrc = (unsigned int *) gradients;

  for (i = 0; i < 256; i++) {
    int indx = permTable[i];
    p[i * 3] = psrc[indx * 3];
    p[i * 3 + 1] = psrc[indx * 3 + 1];
    p[i * 3 + 2] = psrc[indx * 3 + 2];
  }
}

//
// generate the value of gradient noise for a given lattice point
//
// (ix, iy, iz) specifies the 3D lattice position
// (fx, fy, fz) specifies the fractional part
//
static float glattice3D(int ix, int iy, int iz, float fx, float fy, float fz) {
  float *g;
  int indx, y, z;

  z = permTable[iz & NOISE_TABLE_MASK];
  y = permTable[(iy + z) & NOISE_TABLE_MASK];
  indx = (ix + y) & NOISE_TABLE_MASK;
  g = &gradientTable[indx * 3];

  return (g[0] * fx + g[1] * fy + g[2] * fz);
}

//
// generate the 3D noise value
// f describes the input (x, y, z) position for which the noise value needs to be computed
// noise3D returns the scalar noise value
//
float noise3D(float *f) {
  int ix, iy, iz;
  float fx0, fx1, fy0, fy1, fz0, fz1;
  float wx, wy, wz;
  float vx0, vx1, vy0, vy1, vz0, vz1;

  ix = FLOOR(f[0]);
  fx0 = f[0] - ix;
  fx1 = fx0 - 1;
  wx = smoothstep(fx0);

  iy = FLOOR(f[1]);
  fy0 = f[1] - iy;
  fy1 = fy0 - 1;
  wy = smoothstep(fy0);

  iz = FLOOR(f[2]);
  fz0 = f[2] - iz;
  fz1 = fz0 - 1;
  wz = smoothstep(fz0);

  vx0 = glattice3D(ix, iy, iz, fx0, fy0, fz0);
  vx1 = glattice3D(ix + 1, iy, iz, fx1, fy0, fz0);
  vy0 = lerp(wx, vx0, vx1);
  vx0 = glattice3D(ix, iy + 1, iz, fx0, fy1, fz0);
  vx1 = glattice3D(ix + 1, iy + 1, iz, fx1, fy1, fz0);
  vy1 = lerp(wx, vx0, vx1);
  vz0 = lerp(wy, vy0, vy1);

  vx0 = glattice3D(ix, iy, iz + 1, fx0, fy0, fz1);
  vx1 = glattice3D(ix + 1, iy, iz + 1, fx1, fy0, fz1);
  vy0 = lerp(wx, vx0, vx1);
  vx0 = glattice3D(ix, iy + 1, iz + 1, fx0, fy1, fz1);
  vx1 = glattice3D(ix + 1, iy + 1, iz + 1, fx1, fy1, fz1);
  vy1 = lerp(wx, vx0, vx1);
  vz1 = lerp(wy, vy0, vy1);

  return lerp(wz, vz0, vz1);;
}

GLuint Create3DNoiseTexture(int textureSize, float frequency) {
  GLuint textureId;
  GLfloat *texBuf = (GLfloat *) malloc(sizeof(GLfloat) * textureSize * textureSize * textureSize);
  GLubyte *uploadBuf = (GLubyte *) malloc(sizeof(GLubyte) * textureSize * textureSize * textureSize);
  int x, y, z;
  int index = 0;
  float min = 1000;
  float max = -1000;
  float range;

  initNoiseTable();

  for (z = 0; z < textureSize; z++) {
    for (y = 0; y < textureSize; y++) {
      for (x = 0; x < textureSize; x++) {
        float noiseVal;
        float pos[3] = {
            (float) x / (float) textureSize,
            (float) y / (float) textureSize,
            (float) z / (float) textureSize
        };
        pos[0] *= frequency;
        pos[1] *= frequency;
        pos[2] *= frequency;
        noiseVal = noise3D(pos);

        if (noiseVal < min) {
          min = noiseVal;
        }

        if (noiseVal > max) {
          max = noiseVal;
        }

        texBuf[index++] = noiseVal;
      }
    }
  }

  // Normalize to the [0, 1] range
  range = (max - min);
  index = 0;

  for (z = 0; z < textureSize; z++) {
    for (y = 0; y < textureSize; y++) {
      for (x = 0; x < textureSize; x++) {
        float noiseVal = texBuf[index];
        noiseVal = (noiseVal - min) / range;
        uploadBuf[index++] = (GLubyte) (noiseVal * 255.0f);
      }
    }
  }

  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_3D, textureId);
  glTexImage3D(GL_TEXTURE_3D, 0, GL_R8, textureSize, textureSize, textureSize, 0, GL_RED, GL_UNSIGNED_BYTE, uploadBuf);

  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);

  glBindTexture(GL_TEXTURE_3D, 0);

  free(texBuf);
  free(uploadBuf);

  return textureId;
}

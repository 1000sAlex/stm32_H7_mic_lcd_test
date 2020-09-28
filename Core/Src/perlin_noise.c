/*
 * perlin_noise.c
 *
 *  Created on: 28 сент. 2020 г.
 *      Author: u
 */

#include "perlin_noise.h"

typedef struct FLOAT2
    {
	float a;
	float b;
    } float2;

// @formatter:off
const u8 permutation[] =
{ 151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36,
  103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0,
  26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56,
  87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
  77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55,
  46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132,
  187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109,
  198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126,
  255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183,
  170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43,
  172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112,
  104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162,
  241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106,
  157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205,
  93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180 };
// @formatter:on
float Dot(float2 a, float2 b)
    {
    return a.a * b.a + a.b * b.b;
    }

float2 GetPseudoRandomGradientVector(int x, int y)
    {
    int v = permutation[((x * 183903) ^ (y * 297073)) & 0xFF] & 3;
    // int v = // псевдо-случайное число от 0 до 3 которое всегда неизменно при данных x и y
    float2 val;
    // @formatter:off
    switch (v)
	{
    case 0: val.a = 1; val.b = 0;
	break;
    case 1: val.a = -1; val.b = 0;
	break;
    case 2: val.a = 0; val.b = 1;
	break;
    default: val.a = 0; val.b = -1;
	break;
	}
    // @formatter:on
    return val;
    }

float QunticCurve(float t)
    {
    return t * t * t * (t * (t * 6 - 15) + 10);
    }

float Lerp(float a, float b, float t)
    {
    return a + (b - a) * t;
    }

float Noise(float fx, float fy)
    {
    // сразу находим координаты левой верхней вершины квадрата
    int left = (int) fx;
    int top = (int) fy;

    // а теперь локальные координаты точки внутри квадрата
    float pointInQuadX = fx - left;
    float pointInQuadY = fy - top;

    // извлекаем градиентные векторы для всех вершин квадрата:
    float2 topLeftGradient = GetPseudoRandomGradientVector(left, top);
    float2 topRightGradient = GetPseudoRandomGradientVector(left + 1, top);
    float2 bottomLeftGradient = GetPseudoRandomGradientVector(left, top + 1);
    float2 bottomRightGradient = GetPseudoRandomGradientVector(left + 1,
	    top + 1);

    // вектора от вершин квадрата до точки внутри квадрата:
    float2 distanceToTopLeft;
    distanceToTopLeft.a = pointInQuadX;
    distanceToTopLeft.b = pointInQuadY;

    float2 distanceToTopRight;
    distanceToTopRight.a = pointInQuadX - 1;
    distanceToTopRight.b = pointInQuadY;

    float2 distanceToBottomLeft;
    distanceToBottomLeft.a = pointInQuadX;
    distanceToBottomLeft.b = pointInQuadY - 1;

    float2 distanceToBottomRight;
    distanceToBottomRight.a = pointInQuadX - 1;
    distanceToBottomRight.b = pointInQuadY - 1;

    // считаем скалярные произведения между которыми будем интерполировать
    /*
     tx1--tx2
     |    |
     bx1--bx2
     */
    float tx1 = Dot(distanceToTopLeft, topLeftGradient);
    float tx2 = Dot(distanceToTopRight, topRightGradient);
    float bx1 = Dot(distanceToBottomLeft, bottomLeftGradient);
    float bx2 = Dot(distanceToBottomRight, bottomRightGradient);

    // готовим параметры интерполяции, чтобы она не была линейной:
    pointInQuadX = QunticCurve(pointInQuadX);
    pointInQuadY = QunticCurve(pointInQuadY);

    // собственно, интерполяция:
    float tx = Lerp(tx1, tx2, pointInQuadX);
    float bx = Lerp(bx1, bx2, pointInQuadX);
    float tb = Lerp(tx, bx, pointInQuadY);

    // возвращаем результат:
    return tb;
    }

u16 Noise_combine(float a, float ak, float b, float bk, float c, float ck,
	u16 map, u16 x, u16 y)
    {
    float a_val = Noise(x * a, y * a) + 0.5;
    float b_val = Noise(x * b, y * b) + 0.5;
    float c_val = Noise(x * c, y * c) + 0.5;

    return (u16) (((a_val * ak) + (b_val * bk) + (c_val * ck)) * (float) map);
    }

u16 Noise_treshold(float in, float min, float max, float map, float bias)
    {
    if ((in >= min) && (in < max))
	{
	float d = max - min;
	return (u16) ((in - min) * (map / d) + bias);
	}
    return 0;
    }

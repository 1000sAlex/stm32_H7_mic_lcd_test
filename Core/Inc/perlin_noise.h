/*
 * perlin_noise.h
 *
 *  Created on: 28 сент. 2020 г.
 *      Author: u
 */

#ifndef INC_PERLIN_NOISE_H_
#define INC_PERLIN_NOISE_H_

#include "main.h"
float Noise(float fx, float fy);
u16 Noise_combine(float a, float ak, float b, float bk, float c, float ck,
	u16 map, u16 x, u16 y);
u16 Noise_treshold(float in, float min, float max, float map, float bias);
float Noise_simple(float k, u16 x, u16 y);
void Generate_NoiseLine(float x, float y, u16 *buf);
#endif /* INC_PERLIN_NOISE_H_ */

#include "area.h" 

float get_area_of_rectangle(float l,float w)
{
	return l * w;
}


float get_area_of_triangle(float w,float h)
{
	return w * h / 2;
}

float get_area_of_ellipse(float lr,float sr)
{
	return PI * lr * sr;
}

#include "Color.h"

Color::Color()
{
	SetColor(0, 0, 0);
}

Color::Color(unsigned int R, unsigned int G, unsigned int B)
{
	SetColor(R, G, B);
}

void Color::SetColor(unsigned int R, unsigned int G, unsigned int B)
{
	if (R > 255) mR = 255;
	else mR = R;
	if (G > 255) mG = 255;
	else mG = G;
	if (B > 255) mB = 255;
	else mB = B;
}

unsigned int Color::GetRComponent()
{
	return mR;
}

unsigned int Color::GetGComponent()
{
	return mG;
}

unsigned int Color::GetBComponent()
{
	return mB;
}
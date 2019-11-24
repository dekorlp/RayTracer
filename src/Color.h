#pragma once

class Color
{
	public:
		Color(unsigned int R, unsigned int G, unsigned int B);
		void SetColor(unsigned int R, unsigned int G, unsigned int B);
		unsigned int GetRComponent();
		unsigned int GetGComponent();
		unsigned int GetBComponent();

	private:
		unsigned int mR;
		unsigned int mG;
		unsigned int mB;
};
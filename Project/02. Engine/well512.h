#pragma once

#include <ctime>

class CWell512
{
	enum
	{
		DIFFER_VALUE = 100,
	};

public:

	explicit CWell512()
	{
		index = 0;
		unsigned int s = static_cast<unsigned int>(time(NULL));

		for (int i = 0; i < 16; i++)
		{
			state[i] = s;
			s += s + DIFFER_VALUE;
		}
	}

	~CWell512() {}

	unsigned int GetValue()
	{
		unsigned int a, b, c, d;

		a = state[index];
		c = state[(index + 13) & 15];
		b = a ^ c ^ (a << 16) ^ (c << 15);
		c = state[(index + 9) & 15];
		c ^= (c >> 11);
		a = state[index] = b ^ c;
		d = a ^ ((a << 5) & 0xda442d24U);
		index = (index + 15) & 15;
		a = state[index];
		state[index] = a ^ b^d ^ (a << 2) ^ (b << 18) ^ (c << 28);

		return state[index];
	}

	unsigned int GetValue(unsigned int nMinValue, unsigned int nMaxValue)
	{
		return nMinValue + (GetValue() % (nMaxValue - nMinValue));
	}

	unsigned int GetValue(unsigned int nMaxValue)
	{
		return GetValue() % nMaxValue;
	}

	float GetFloatValue()
	{
		unsigned int nRandValue = GetValue();

		union { unsigned long ul; float f; }p;
		p.ul = (((nRandValue *= 16807) & 0x007fffff) - 1) | 0x3f800000;

		return p.f - 1.f;
	}

	float GetFloatValue(float fMinValue, float fMaxValue)
	{
		return fMinValue + GetFloatValue()* (fMaxValue - fMinValue);
	}

	float GetFloatValue(float fMaxValue)
	{
		return GetFloatValue() * fMaxValue;
	}

protected:
	unsigned long state[16];
	unsigned int index;
};
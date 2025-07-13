#include "MD_Math.h"

#include <math.h>

void MD_Math_PrintMatrix(const char* name, MD_MATH_MATRIX m)
{
    printf("%s:\n", name);
    printf("[%8.4f, %8.4f, %8.4f, %8.4f]\n", m._11, m._12, m._13, m._14);
    printf("[%8.4f, %8.4f, %8.4f, %8.4f]\n", m._21, m._22, m._23, m._24);
    printf("[%8.4f, %8.4f, %8.4f, %8.4f]\n", m._31, m._32, m._33, m._34);
    printf("[%8.4f, %8.4f, %8.4f, %8.4f]\n", m._41, m._42, m._43, m._44);
}

void PrintMatix(float* v)
{
	printf("[%8.4f, %8.4f, %8.4f, %8.4f]\n", v[0], v[1], v[2], v[3]);
    printf("[%8.4f, %8.4f, %8.4f, %8.4f]\n", v[4], v[5], v[6], v[7]);
    printf("[%8.4f, %8.4f, %8.4f, %8.4f]\n", v[8], v[9], v[10], v[11]);
    printf("[%8.4f, %8.4f, %8.4f, %8.4f]\n", v[12], v[13], v[14], v[15]);
}

int main()
{
	
	printf("%f\n",MD_Math_log2(2.0f));
    printf("%f\n",MD_MATH_PI / 4.0f);

    printf("%f\n",log10(10.0f));

    system("pause");
    return 0;
}
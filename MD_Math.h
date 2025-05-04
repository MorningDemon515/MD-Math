#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

const float MD_MATH_PI = 3.14159265358979323846f;//26433832795028841971693993751058209749445923078164062862089986280348253421170679f;
//Take 100 decimal places for pi

const float MD_MATH_E = 2.71828182845904523536f;//02874713526624977572470936999595749669676277240766303535475945713821785251664274f;

const float MD_MATH_PIReciprocal = 0.31830988618379067153f;//7767526745028724068919291480912897495334688117793595268453070180227605532506171912f;

const float MD_MATH_THIRD = 0.33333333333333333333f;//33333333333333333333333333333333333333333333333333333333333333333333333333333333;

//The value of root number 2 must be 100 digits
const float MD_MATH_SQRT2 = 1.41421356237309504880f;//1688724209698078569671875376948073176679737990732478462107038850387534327641573f;
//The value of root number 3 must be 100 digits
const float MD_MATH_SQRT3 = 1.73205080756887729352f;//7446341505872366942805253810380628055806979451933016908800037081146186757248576f;

const float MD_MATH_OneHundredAndEighty = 0.005555555555555556f;

const float MD_MATH_1Degree = 0.017453f;
const float MD_MATH_1Radian = 57.30f; 

const float MD_MATH_EPSILON = 1.192092896e-07f;

//Special trigonometric values
#define MD_MATH_SIN0  0.0f, 
#define MD_MATH_SIN30  0.5f,
#define MD_MATH_SIN45  MD_MATH_SQRT2 * 0.5f,
#define MD_MATH_SIN60  MD_MATH_SQRT3 * 0.5f,
#define MD_MATH_SIN90  1.0f,
#define MD_MATH_SIN120  MD_MATH_SQRT3 * 0.5f,
#define MD_MATH_SIN150  0.5f,
#define MD_MATH_SIN180  0.0f,
#define MD_MATH_SIN270  -1.0f;

#define MD_MATH_COS0  1.0f, 
#define MD_MATH_COS30  MD_MATH_SQRT3 * 0.5f,
#define MD_MATH_COS45  MD_MATH_SQRT2 * 0.5f,
#define MD_MATH_COS60  0.5f,
#define MD_MATH_COS90  0.0f,
#define MD_MATH_COS120  -1.0f * 0.5f,
#define MD_MATH_COS150  -1.0f * MD_MATH_SQRT3 *0.5f,
#define MD_MATH_COS180  -1.0f,
#define MD_MATH_COS270  0.0f;   

#define MD_MATH_TAN0  0.0f, 
#define MD_MATH_TAN30 MD_MATH_SQRT3 * MD_MATH_THIRD,
#define MD_MATH_TAN45  1.0f,
#define MD_MATH_TAN60  MD_MATH_SQRT3,
#define MD_MATH_TAN120  -1.0f * MD_MATH_SQRT3,
#define MD_MATH_TAN150  -1.0f * MD_MATH_SQRT3 * MD_MATH_THIRD,
#define MD_MATH_TAN180  0.0f;                      

float MD_Math_Abs(float number)
{
    if(number > 0.0f)
    {
        return number;
    }
    else if (number == 0.0f)
    {
        return 0.0f;
    }
    else if (number < 0.0f)
    {
        return -1.0f * number;
    }
    else
    {
        return 0.0f;
    }
    
}

float MD_Math_Mod(float number1, float number2)
{
    if(number2 == 0.0f)
        return 0.0f;
    
    int y = (int)(number1 / number2);
    return number1 - (float)y * number2;
}


float MD_Math_Max(float number1, float number2)
{
    if(number1 > number2)
    {
        return number1;
    }
    else
    {
        return number2;
    }
    
}

float MD_Math_Min(float number1, float number2)
{
    if(number1 < number2)
    {
        return number1;
    }
    else
    {
        return number2;
    }
    
}

float MD_Math_Sqrt(float number)
{
    long i;
	float y;

	y  = number;
	i  = * ( long * ) &y;						// evil floating point bit level hacking
	i  = ( i >> 1 ) + 0x1fc00000;               // new magic number
	y  = * ( float * ) &i;
    y = 0.5f * ( y + number / y);// 1st iteration
    y = 0.5f * ( y + number / y);// 2nd iteration
    //y = 0.5f * ( y + number / y);// 3rd iteration

	return y;
}

float MD_Math_Cbrt(float number)
{
    long i;
	float y;

	y  = number;
	i  = * ( long * ) &y;					 // evil floating point bit level hacking
	i  = ( i / 3 ) + 0x2a9f84fe;               // new magic number
	y  = * ( float * ) &i;
    y = MD_MATH_THIRD * (2.0f * y + number / (y*y));// 1st iteration
    y = MD_MATH_THIRD * (2.0f * y + number / (y*y));// 2nd iteration
    y = MD_MATH_THIRD * (2.0f * y + number / (y*y));// 3rd iteration
    y = MD_MATH_THIRD * (2.0f * y + number / (y*y));// 4th iteration

	return y;
}

//From https://github.com/id-Software/Quake-III-Arena/blob/master/code/game/q_math.c#L552
float MD_Math_Rsqrt(float number)
{
    long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;						// evil floating point bit level hacking
	i  = 0x5f375a86 - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

int MD_Math_Pow(int x,int y)
{
    int xx = 1;
    
    for (int i = 0; i < y ; i++)
    {
        xx = x * xx;
    }

    return xx;
    
}

float MD_Math_Hypot(float x,float y)
{
    return MD_Math_Sqrt((x*x + y*y));
}

float MD_Math_Factorial(float number)
{
    return number * (number - 1);
}

float MD_Math_Sin(float x)
{
    return x - ((x*x*x)/MD_Math_Factorial(3.0f)) + 
        ((x*x*x*x*x)/MD_Math_Factorial(5.0f))-
        ((x*x*x*x*x*x*x)/MD_Math_Factorial(7.0f))+
        ((x*x*x*x*x*x*x*x*x)/MD_Math_Factorial(9.0f));
}

float MD_Math_Cos(float x)
{
    return 1 - ((x*x)/MD_Math_Factorial(2.0f)) + 
        ((x*x*x*x)/MD_Math_Factorial(4.0f))-
        ((x*x*x*x*x*x)/MD_Math_Factorial(6.0f))+
        ((x*x*x*x*x*x*x*x)/MD_Math_Factorial(8.0f));//-
        //((x*x*x*x*x*x*x*x*x*x)/MD_Math_Factorial(10.0f))+
        //((x*x*x*x*x*x*x*x*x*x*x*x)/MD_Math_Factorial(12.0f))-
        //((x*x*x*x*x*x*x*x*x*x*x*x*x*x)/MD_Math_Factorial(14.0f));
}

float MD_Math_Tan(float x )
{
    return x + ((x*x*x)/3) - ((2*x*x*x*x*x)/15);
}

float MD_Math_Cot(float x)
{
    return MD_Math_Cos(x)/MD_Math_Sin(x);
}

bool MD_Math_Equal(float a,float b, float epsilon)
{
    if(MD_Math_Abs(a - b) < epsilon)
    {
        return true;
    }
    else
    {
        return false;
    }
}

float MD_Math_EtoXPower(float x)
{
    return 1 + x + (x*x)/MD_Math_Factorial(2.0f)+
    (x*x*x)/MD_Math_Factorial(3.0f)+
    (x*x*x*x)/MD_Math_Factorial(4.0f)+
    (x*x*x*x*x)/MD_Math_Factorial(5.0f)+
    (x*x*x*x*x*x)/MD_Math_Factorial(6.0f);
}

float MD_Math_ln1andx(float x)
{
    return 1 +- x + (x*x)/MD_Math_Factorial(2.0f)-
    (x*x*x)/MD_Math_Factorial(3.0f)+
    (x*x*x*x)/MD_Math_Factorial(4.0f)-
    (x*x*x*x*x)/MD_Math_Factorial(5.0f);
}

void MD_Math_Frexp(double x, double *m, int *e) {
    
    // Extract the binary representation of the double
    uint64_t bits;
    memcpy(&bits, &x, sizeof(double));
    
    // Decompose symbols, exponents, and mantissas
    int sign = (bits >> 63) & 0x1;
    int exponent = (bits >> 52) & 0x7FF;
    uint64_t mantissa = bits & 0x000FFFFFFFFFFFFFULL;

    // Handling Non-normalized Numbers (Exponential All 0)
    if (exponent == 0) {
        // Find the position of the highest 1 in the mantissa number
        int shift = 0;
        while ((mantissa & (1ULL << 51)) == 0 && shift < 53) {
            mantissa <<= 1;
            shift++;
        }
        // Adjust the exponent and mantissa number
        exponent = -1022 - shift;
        mantissa &= 0x000FFFFFFFFFFFFFULL; // Clear the implicit 1
        exponent += 1; // Mantissa adjusted to [0.5, 1]
    } else {
        // Normalize number: Adjusts the exponent and adds an implied 1
        exponent -= 1023;
        mantissa |= (1ULL << 52); // Add an implicit 1
    }

    // Construct a new mantissa mantissa number
    uint64_t new_bits = (uint64_t)(sign) << 63;
    new_bits |= (uint64_t)(exponent + 1023) << 52;
    new_bits |= mantissa & 0x000FFFFFFFFFFFFFULL;
    memcpy(m, &new_bits, sizeof(double));

    *e = exponent;
}

float MD_Math_lnx(float a)
{
    int k;
    double b;
    MD_Math_Frexp(a,&b ,&k);
    b *= 2.0;
    k -= 1;
    
    double x = 0.0; 
    for (int i = 0; i < 20; i++) {
        double exp_x = MD_Math_EtoXPower(x);
        double delta = (exp_x - b) / exp_x;
        x -= delta;
        if (MD_Math_Abs(delta) < 1e-10) break;
    }
    return x + k * 0.6931471805599453;
}

float MD_Math_lgx(float x)
{
    return MD_Math_lnx(x) * 0.43429448190325176f;
}

float MD_Math_log2(float x)
{
    return MD_Math_lnx(x) * 1.4426950408889634f;
}

float MD_Math_AngularToRadian(float angle)
{
    return angle * MD_MATH_PI * MD_MATH_OneHundredAndEighty;
}

float MD_Math_RadianToangle(float Radian)
{
    return Radian * 180.0f * MD_MATH_PIReciprocal;
}

float MD_Math_ComputeRectanglePerimeter(float Length, float Width)
{
    return (Length + Width) * 2;
}

float MD_Math_ComputeSquarePerimeter(float Length)
{
    return Length * 4;
}

float MD_Math_ComputeRectangleArea(float Length, float Width)
{
    return Length * Width;
}

float MD_Math_ComputeSquareArea(float Length)
{
    return Length * Length;
}

float MD_Math_ComputeTriangleArea(float Bottom, float Height)
{
    return Bottom * Height * 0.5f; 
}

float MD_Math_ComputeParallelogramArea(float Bottom, float Height)
{
    return Bottom * Height;
}

float MD_Math_ComputeTrapezoidArea(float Top, float Bottom,float Height)
{
    return (Top + Bottom) * Height * 0.5f;
}

float MD_Math_ComputeCirclePerimeter(float radius)
{
    return 2.0f * MD_MATH_PI * radius;
}

float MD_Math_ComputeCircleArea(float radius)
{
    return MD_MATH_PI * radius * radius;
}

float MD_Math_ComputeCuboidVolume(float Length, float Width, float Height)
{
    return Length * Width * Height;
}

float MD_Math_ComputeCubeVolume(float Length)
{
    return Length * Length;
}

float MD_Math_ComputeCylinderSideArea(float radius, float height)
{
    return 2.0f * MD_MATH_PI * radius * height;
}

float MD_Math_ComputeConeSideArea(float radius, float busbar)
{
    return 2.0f * MD_MATH_PI * radius * busbar;
}

float MD_Math_ComputeRoundTableSideArea(float radius1,float radius2,float busbar)
{
    return MD_MATH_PI * (radius1 + radius2) * busbar;
}

float MD_Math_ComputeCylinderSurfaceArea(float radius, float height)
{
    return MD_Math_ComputeCylinderSideArea(radius,height) + MD_Math_ComputeCircleArea(radius);
}

float MD_Math_ComputeConeSurfaceArea(float radius, float busbar)
{
    return MD_Math_ComputeCircleArea(radius) + MD_MATH_PI * radius * busbar;
}

float MD_Math_ComputeRoundTableSurfaceArea(float radius1,float radius2, float busbar)
{
    return MD_Math_ComputeCircleArea(radius1) + MD_Math_ComputeCircleArea(radius2) + MD_MATH_PI * radius1 * busbar + MD_MATH_PI * radius2 * busbar;
}

float MD_Math_ComputeBallSurfaceArea(float radius)
{
    return 4.0f * MD_MATH_PI * radius;
}

float MD_Math_ComputeCylinderVolume(float radius, float height)
{
    return MD_Math_ComputeCircleArea(radius) * height;
}

float MD_Math_ComputeConeVolume(float radius, float height)
{
    return MD_MATH_THIRD * MD_Math_ComputeCylinderVolume(radius,height);
}

float MD_Math_ComputeRoundTableVolume(float radius1, float radius2, float height)
{
    return MD_MATH_THIRD * height * (MD_Math_ComputeCircleArea(radius1) + MD_Math_ComputeCircleArea(radius2) + MD_MATH_PI * (radius1 + radius2));
}

float MD_Math_ComputeBallVolume(float radius)
{
    return 4.0f * MD_MATH_THIRD * MD_MATH_PI * radius * radius * radius;
}

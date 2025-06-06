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

const float MD_MATH_LN2 = 0.69314718055994530942f;

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

float MD_Math_Hypot(float x,float y)
{
    return MD_Math_Sqrt((x*x + y*y));
}

float MD_Math_Factorial(float number)
{
    unsigned long long factorial = 1;
 
    for(int i = 1; i <=number; ++i)
    {
        factorial *= i;
    }

    return factorial;
    
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

float MD_Math_ArcSin(float x)
{
    return x + 
            0.1666666667f * x * x * x +
            0.075f * x * x * x * x * x +
            0.04464285714 * x * x * x * x * x * x * x +
            0.03038194444 * x * x * x * x * x * x * x * x * x +
            0.02237215909 * x * x * x * x * x * x * x * x * x * x * x +
            0.01735276442 * x * x * x * x * x * x * x * x * x * x * x * x * x;
}

float MD_Math_ArcCos(float x)
{
    return MD_MATH_PI * 0.5f - MD_Math_ArcSin(x);
}

float MD_Math_ArcTan(float x)
{
    return x - 
            x * x * x * MD_MATH_THIRD +
            x * x * x * x * x * 0.2f -
            x * x * x * x * x * x * x * 0.1428571429f +
            x * x * x * x * x * x * x * x * x * 0.1111111111f -
            x * x * x * x * x * x * x * x * x * x * x * 0.09090909091f +
            x * x * x * x * x * x * x * x * x * x * x * x * x * 0.07692307692f;
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

float MD_Math_lnx(float x)
{
    if (x <= 0.0) {
        return 0.0 / 0.0;  // 返回 NaN
    }

    int k = 0;
    while (x > 2.0) {
        x /= 2.0;
        k++;
    }

    float t = x - 1.0;  
    float result = 0.0;
    float term = t;     
    float sign = 1.0;  
    int n = 1;           

    while (n <= 12) {
        double current = sign * term / n;
        result += current;

        term *= t;      
        sign = -sign; 
        n++;           
    }

    result += k * MD_MATH_LN2;

    return result;
    
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

typedef float MD_MATH_VECTOR2[2];
typedef float MD_MATH_VECTOR3[3];
typedef float MD_MATH_VECTOR4[4];

/*
typedef float MD_MATH_MATRIX2x2[4];
typedef float MD_MATH_MATRIX2x3[6];
typedef float MD_MATH_MATRIX2x4[8];

typedef float MD_MATH_MATRIX3x2[6];
typedef float MD_MATH_MATRIX3x3[9];
typedef float MD_MATH_MATRIX3x4[12];

typedef float MD_MATH_MATRIX4x2[8];
typedef float MD_MATH_MATRIX4x3[12];
*/

typedef float MD_MATH_MATRIX[16];//4x4

MD_MATH_VECTOR2 BasisVector2I = {1.0f,0.0f};
MD_MATH_VECTOR2 BasisVector2J = {0.0f,1.0f};

MD_MATH_VECTOR3 BasisVector3I = {1.0f,0.0f,0.0f};
MD_MATH_VECTOR3 BasisVector3J = {0.0f,1.0f,0.0f};

MD_MATH_VECTOR4 BasisVector4I = {1.0f,0.0f,0.0f,0.0f};
MD_MATH_VECTOR4 BasisVector4J = {0.0f,1.0f,0.0f,0.0f};

MD_MATH_VECTOR3 BasisVector3K = {0.0f,0.0f,1.0f};
MD_MATH_VECTOR4 BasisVector4K = {0.0f,0.0f,1.0f,0.0f};

MD_MATH_VECTOR4 BasisVector4W = {0.0f,0.0f,0.0f,1.0f};


// About Vector--------------------------------------------------------------------------------
bool MD_Math_Vector2Equal(MD_MATH_VECTOR2 v1,MD_MATH_VECTOR2 v2)
{
    if(
        MD_Math_Equal(v1[0],v2[0],MD_MATH_EPSILON) &&
        MD_Math_Equal(v1[1],v2[1],MD_MATH_EPSILON)
    )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MD_Math_Vector3Equal(MD_MATH_VECTOR3 v1,MD_MATH_VECTOR3 v2)
{
    if(
        MD_Math_Equal(v1[0],v2[0],MD_MATH_EPSILON) &&
        MD_Math_Equal(v1[1],v2[1],MD_MATH_EPSILON) &&
        MD_Math_Equal(v1[2],v2[2],MD_MATH_EPSILON) 
    )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MD_Math_Vector4Equal(MD_MATH_VECTOR4 v1,MD_MATH_VECTOR4 v2)
{
    if(
        MD_Math_Equal(v1[0],v2[0],MD_MATH_EPSILON) &&
        MD_Math_Equal(v1[1],v2[1],MD_MATH_EPSILON) &&
        MD_Math_Equal(v1[2],v2[2],MD_MATH_EPSILON) &&
        MD_Math_Equal(v1[3],v2[3],MD_MATH_EPSILON)
    )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void MD_Math_Vector2Addition(MD_MATH_VECTOR2 v1, MD_MATH_VECTOR2 v2,MD_MATH_VECTOR2 result)
{
    result[0] = v1[0] + v2[0];
    result[1] = v1[1] + v2[1];
}

void MD_Math_Vector3Addition(MD_MATH_VECTOR3 v1, MD_MATH_VECTOR3 v2,MD_MATH_VECTOR3 result)
{
    result[0] = v1[0] + v2[0];
    result[1] = v1[1] + v2[1];
    result[2] = v1[2] + v2[2];
}

void MD_Math_Vector4Addition(MD_MATH_VECTOR4 v1, MD_MATH_VECTOR4 v2,MD_MATH_VECTOR4 result)
{
    result[0] = v1[0] + v2[0];
    result[1] = v1[1] + v2[1];
    result[2] = v1[2] + v2[2];
    result[3] = v1[3] + v2[3];
}

void MD_Math_Vector2Multiplication(MD_MATH_VECTOR2 v,float x)
{
    v[0] = x * v[0];
    v[1] = x * v[1];
}

void MD_Math_Vector3Multiplication(MD_MATH_VECTOR3 v,float x)
{
    v[0] = x * v[0];
    v[1] = x * v[1];
    v[2] = x * v[2];
}

void MD_Math_Vector4Multiplication(MD_MATH_VECTOR4 v,float x)
{
    v[0] = x * v[0];
    v[1] = x * v[1];
    v[2] = x * v[2];
    v[3] = x * v[3];
}

float MD_Math_ComputeVector2Length(MD_MATH_VECTOR2 v)
{
    return MD_Math_Hypot(v[0],v[1]);
}

float MD_Math_ComputeVector3Length(MD_MATH_VECTOR3 v)
{
    return MD_Math_Sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

float MD_Math_ComputeVector4Length(MD_MATH_VECTOR4 v)
{
    return MD_Math_Sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
}

void MD_Math_Vector2Normalized(MD_MATH_VECTOR2 v)
{
    v[0] = v[0] * MD_Math_Rsqrt(v[0]*v[0] + v[1] * v[1]); 
    v[1] = v[1] * MD_Math_Rsqrt(v[0]*v[0] + v[1] * v[1]); 
}

void MD_Math_Vector3Normalized(MD_MATH_VECTOR3 v)
{
    v[0] = v[0] * MD_Math_Rsqrt(v[0]*v[0] + v[1] * v[1] + v[2] * v[2]); 
    v[1] = v[1] * MD_Math_Rsqrt(v[0]*v[0] + v[1] * v[1] + v[2] * v[2]); 
    v[2] = v[2] * MD_Math_Rsqrt(v[0]*v[0] + v[1] * v[1] + v[2] * v[2]); 
}

void MD_Math_Vector4Normalized(MD_MATH_VECTOR4 v)
{
    v[0] = v[0] * MD_Math_Rsqrt(v[0]*v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]); 
    v[1] = v[1] * MD_Math_Rsqrt(v[0]*v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
    v[2] = v[2] * MD_Math_Rsqrt(v[0]*v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]); 
    v[3] = v[3] * MD_Math_Rsqrt(v[0]*v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);  
}

float MD_Math_Vector2Dot(MD_MATH_VECTOR2 v1,MD_MATH_VECTOR2 v2)
{
    return 
       v1[0] * v2[0] +
       v1[1] * v2[1]
    ;
}

float MD_Math_Vector3Dot(MD_MATH_VECTOR3 v1,MD_MATH_VECTOR3 v2)
{
    return 
       v1[0] * v2[0] +
       v1[1] * v2[1] +
       v1[2] * v2[2]
    ;
}

float MD_Math_Vector4Dot(MD_MATH_VECTOR4 v1,MD_MATH_VECTOR4 v2)
{
    return 
       v1[0] * v2[0] +
       v1[1] * v2[1] +
       v1[2] * v2[2] +
       v1[3] * v2[3]
    ;
}

void MD_Math_VectorCross(MD_MATH_VECTOR3 v1, MD_MATH_VECTOR3 v2, MD_MATH_VECTOR3 r)
{
    r[0] = v1[1] * v2[2] - v2[1] * v1[2];
    r[1] = v1[2] * v2[0] - v2[2] * v1[0];
    r[2] = v1[0] * v2[1] - v2[0] * v1[1];
}

float MD_Math_ProjectionOfVector2(MD_MATH_VECTOR2 v1, MD_MATH_VECTOR2 v2)
{
    return 
        MD_Math_ComputeVector2Length(v1) * 
        MD_Math_Cos(MD_Math_ArcCos(MD_Math_Vector2Dot(v1,v2) * MD_Math_Rsqrt(v1[0] * v1[0] + v1[1] * v1[1])*
                                                                MD_Math_Rsqrt(v2[0]* v2[0] + v2[1]*v2[1] )))
    ;
}

float MD_Math_ProjectionOfVector3(MD_MATH_VECTOR3 v1, MD_MATH_VECTOR3 v2)
{
    return 
        MD_Math_ComputeVector3Length(v1) * 
        MD_Math_Cos(MD_Math_ArcCos(MD_Math_Vector3Dot(v1,v2) * MD_Math_Rsqrt(v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2])*
                                                                MD_Math_Rsqrt(v2[0]* v2[0] + v2[1]*v2[1] + v2[2] * v2[2])))
    ;
}

float MD_Math_ProjectionOfVector4(MD_MATH_VECTOR4 v1, MD_MATH_VECTOR4 v2)
{
    return 
        MD_Math_ComputeVector4Length(v1) * 
        MD_Math_Cos(MD_Math_ArcCos(MD_Math_Vector4Dot(v1,v2) * MD_Math_Rsqrt(v1[0] * v1[0] + v1[1] * v1[1]+ v1[2] * v1[2]+ v1[3] * v1[3])*
                                                                MD_Math_Rsqrt(v2[0]* v2[0] + v2[1]*v2[1] + v1[2] * v1[2]+ v1[3] * v1[3])))
    ;
}

void MD_Math_ProjectionVector2(MD_MATH_VECTOR2 v1, MD_MATH_VECTOR2 v2, MD_MATH_VECTOR2 r)
{
    MD_Math_Vector2Normalized(r);
    r[0] = MD_Math_ProjectionOfVector2(v1,v2) * r[0];
    r[1] = MD_Math_ProjectionOfVector2(v1,v2) * r[1];
}

void MD_Math_ProjectionVector3(MD_MATH_VECTOR3 v1, MD_MATH_VECTOR3 v2, MD_MATH_VECTOR3 r)
{
    MD_Math_Vector3Normalized(r);
    r[0] = MD_Math_ProjectionOfVector3(v1,v2) * r[0];
    r[1] = MD_Math_ProjectionOfVector3(v1,v2) * r[1];
    r[2] = MD_Math_ProjectionOfVector3(v1,v2) * r[2];
}

void MD_Math_ProjectionVector4(MD_MATH_VECTOR4 v1, MD_MATH_VECTOR4 v2, MD_MATH_VECTOR4 r)
{
    MD_Math_Vector4Normalized(r);
    r[0] = MD_Math_ProjectionOfVector4(v1,v2) * r[0];
    r[1] = MD_Math_ProjectionOfVector4(v1,v2) * r[1];
    r[2] = MD_Math_ProjectionOfVector4(v1,v2) * r[2];
    r[3] = MD_Math_ProjectionOfVector4(v1,v2) * r[3];
}
//---------------------------------------------------------------------------------------------------------
//About Matrix --------------------------------------------------------------------------------------------

void MD_Math_VectorMulMatrix(MD_MATH_MATRIX m, MD_MATH_VECTOR4 v, MD_MATH_VECTOR4 r)
{
   r[0] = v[0] * m[0] + v[1] * m[4] + v[2] * m[8] + v[3]*m[12];
   r[1] = v[0] * m[1] + v[1] * m[5] + v[2] * m[9] + v[3]*m[13];
   r[2] = v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + v[3]*m[14];
   r[3] = v[0] * m[3] + v[1] * m[7] + v[2] * m[11] + v[3]*m[15];
}

void MD_Math_MatrixMulMatrix(MD_MATH_MATRIX m1,MD_MATH_MATRIX m2, MD_MATH_MATRIX r)
{
    r[0] = m2[0] * m1[0] + m2[1] * m1[4] + m2[2] * m1[8] + m2[3] * m1[12] ;
    r[1] = m2[0] * m1[1] + m2[1] * m1[5] + m2[2] * m1[9] + m2[3] * m1[13] ;
    r[2] = m2[0] * m1[2] + m2[1] * m1[6] + m2[2] * m1[10] + m2[3] * m1[14] ;
    r[3] = m2[0] * m1[3] + m2[1] * m1[7] + m2[2] * m1[11] + m2[3] * m1[15] ;

    r[4] = m2[4] * m1[0] + m2[5] * m1[4] + m2[6] * m1[8] + m2[7] * m1[12] ;
    r[5] = m2[4] * m1[1] + m2[5] * m1[5] + m2[6] * m1[9] + m2[7] * m1[13] ;
    r[6] = m2[4] * m1[2] + m2[5] * m1[6] + m2[6] * m1[10] + m2[7] * m1[14] ;
    r[7] = m2[4] * m1[3] + m2[5] * m1[7] + m2[6] * m1[11] + m2[7] * m1[15] ;

    r[8] = m2[8] * m1[0] + m2[9] * m1[4] + m2[10] * m1[8] + m2[11] * m1[12] ;
    r[9] = m2[8] * m1[1] + m2[9] * m1[5] + m2[10] * m1[9] + m2[11] * m1[13] ;
    r[10] = m2[8] * m1[2] + m2[9] * m1[6] + m2[10] * m1[10] + m2[11] * m1[14] ;
    r[11] = m2[8] * m1[3] + m2[9] * m1[7] + m2[10] * m1[11] + m2[11] * m1[15] ;

    r[12] = m2[12] * m1[0] + m2[13] * m1[4] + m2[14] * m1[8] + m2[15] * m1[12] ;
    r[13] = m2[12] * m1[1] + m2[13] * m1[5] + m2[14] * m1[9] + m2[15] * m1[13] ;
    r[14] = m2[12] * m1[2] + m2[13] * m1[6] + m2[14] * m1[10] + m2[15] * m1[14] ;
    r[15] = m2[12] * m1[3] + m2[13] * m1[7] + m2[14] * m1[11] + m2[15] * m1[15] ;
}


void MD_Math_MatrixAddMatrix(MD_MATH_MATRIX m1,MD_MATH_MATRIX m2, MD_MATH_MATRIX r)
{
    r[0] = m1[0] + m2[0];
    r[1] = m1[1] + m2[1];
    r[2] = m1[2] + m2[2];
    r[3] = m1[3] + m2[3];

    r[4] = m1[4] + m2[4];
    r[5] = m1[5] + m2[5];
    r[6] = m1[6] + m2[6];
    r[7] = m1[7] + m2[7];

    r[8] = m1[8] + m2[8];
    r[9] = m1[9] + m2[9];
    r[10] = m1[10] + m2[10];
    r[11] = m1[11] + m2[11];

    r[12] = m1[12] + m2[12];
    r[13] = m1[13] + m2[13];
    r[14] = m1[14] + m2[14];
    r[15] = m1[15] + m2[15];

}

void MD_Math_MatrixMultiplication(MD_MATH_MATRIX m,float x)
{
    m[0] = x * m[0];
    m[1] = x * m[1];
    m[2] = x * m[2];
    m[3] = x * m[3];

    m[4] = x * m[4];
    m[5] = x * m[5];
    m[6] = x * m[6];
    m[7] = x * m[7];

    m[8] = x * m[8];
    m[9] = x * m[9];
    m[10] = x * m[10];
    m[11] = x * m[11];

    m[12] = x * m[12];
    m[13] = x * m[13];
    m[14] = x * m[14];
    m[15] = x * m[15];
}

void MD_Math_MatrixTranspose(MD_MATH_MATRIX m)
{
    m[1] = m[4];
    m[2] = m[8];
    m[3] = m[12];

    m[7] = m[13];
    m[11] = m[14];

    m[6] = m[9];
}

void MD_Math_AdjointMatrix(MD_MATH_MATRIX m)
{
    float t[16];
    for (int i = 0; i < 16; i++) {
        t[i] = m[i];
    }

    #define DET3(a0,a1,a2, b0,b1,b2, c0,c1,c2) ( \
        a0*(b1*c2 - b2*c1) - \
        a1*(b0*c2 - b2*c0) + \
        a2*(b0*c1 - b1*c0) )

    m[0]  = DET3(t[5], t[6], t[7],  t[9], t[10], t[11],  t[13], t[14], t[15]);
    m[4]  = -DET3(t[4], t[6], t[7],  t[8], t[10], t[11],  t[12], t[14], t[15]);
    m[8]  = DET3(t[4], t[5], t[7],  t[8], t[9], t[11],  t[12], t[13], t[15]);
    m[12] = -DET3(t[4], t[5], t[6],  t[8], t[9], t[10],  t[12], t[13], t[14]);
    m[1]  = -DET3(t[1], t[2], t[3],  t[9], t[10], t[11],  t[13], t[14], t[15]);
    m[5]  = DET3(t[0], t[2], t[3],  t[8], t[10], t[11],  t[12], t[14], t[15]);
    m[9]  = -DET3(t[0], t[1], t[3],  t[8], t[9], t[11],  t[12], t[13], t[15]);
    m[13] = DET3(t[0], t[1], t[2],  t[8], t[9], t[10],  t[12], t[13], t[14]);
    m[2]  = DET3(t[1], t[2], t[3],  t[5], t[6], t[7],  t[13], t[14], t[15]);
    m[6]  = -DET3(t[0], t[2], t[3],  t[4], t[6], t[7],  t[12], t[14], t[15]);
    m[10] = DET3(t[0], t[1], t[3],  t[4], t[5], t[7],  t[12], t[13], t[15]);
    m[14] = -DET3(t[0], t[1], t[2],  t[4], t[5], t[6],  t[12], t[13], t[14]);
    m[3]  = -DET3(t[1], t[2], t[3],  t[5], t[6], t[7],  t[9], t[10], t[11]);
    m[7]  = DET3(t[0], t[2], t[3],  t[4], t[6], t[7],  t[8], t[10], t[11]);
    m[11] = -DET3(t[0], t[1], t[3],  t[4], t[5], t[7],  t[8], t[9], t[11]);
    m[15] = DET3(t[0], t[1], t[2],  t[4], t[5], t[6],  t[8], t[9], t[10]);

    #undef DET3
}

float MD_Math_DetMatrix(MD_MATH_MATRIX m)
{

    float m00 = m[0],  m01 = m[1],  m02 = m[2],  m03 = m[3];
    float m10 = m[4],  m11 = m[5],  m12 = m[6],  m13 = m[7];
    float m20 = m[8],  m21 = m[9],  m22 = m[10], m23 = m[11];
    float m30 = m[12], m31 = m[13], m32 = m[14], m33 = m[15];

    float det00 = m11 * (m22 * m33 - m23 * m32) 
                - m12 * (m21 * m33 - m23 * m31) 
                + m13 * (m21 * m32 - m22 * m31);

    float det01 = m10 * (m22 * m33 - m23 * m32) 
                - m12 * (m20 * m33 - m23 * m30) 
                + m13 * (m20 * m32 - m22 * m30);

    float det02 = m10 * (m21 * m33 - m23 * m31) 
                - m11 * (m20 * m33 - m23 * m30) 
                + m13 * (m20 * m31 - m21 * m30);

    float det03 = m10 * (m21 * m32 - m22 * m31) 
                - m11 * (m20 * m32 - m22 * m30) 
                + m12 * (m20 * m31 - m21 * m30);

    return m00 * det00 
           - m01 * det01 
           + m02 * det02 
           - m03 * det03;
}


void MD_Math_InvMatrix(MD_MATH_MATRIX m)
{
    float m1[16];
    for (int i = 0; i < 16; i++) {
        m1[i] = m[i];
    }

    MD_Math_AdjointMatrix(m);
    MD_Math_MatrixMultiplication(m , (1/MD_Math_DetMatrix(m1)));
    MD_Math_MatrixTranspose(m);
}
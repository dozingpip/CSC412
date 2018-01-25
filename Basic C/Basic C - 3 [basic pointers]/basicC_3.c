/*--------------------------------------------------------------+
|		A simple C program to demonstrate some basic elements	|
|	of the language to Java programmers.						|
|																|
|	Jean-Yves Hervé, 3DG URI									|
|	2016-09-29													|
|	rev. 2018-01-23												|
+--------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>


#if 0
#pragma mark -
//--------------------------------------------------------------------------
#pragma mark Data type definitions
//--------------------------------------------------------------------------
#endif

//	We saw all of that in Sample 2.  Moving on...
// You can also use the default increment by one to associate ranges
//	of values to different categories
typedef enum TerrainType {
	UNKNOWN = -1,
	//
	SEA = 0,
	//
	FORREST = 100,			//	the way I write it, all the terrain types
	TROPICAL_FORREST,		//	in the range 100-199 will be some kind of
	TEMPERATE_FORREST,		//	forest
	//
	DESERT = 200,
	//
	FIELD = 300,
	WHEAT_FIELD,
	RICE_FIELD,
	POLDER,
	//
	PRAIRIE = 400,
	//
	HELL = 10000
} TerrainType;


#ifndef TRUE
	#define TRUE  1
	#define FALSE 0
#endif

typedef struct SurveyData {
	int x, y;	//	coordinates of a survey point on a grid
	float elev;	//	elevation at that point
	TerrainType type;
} SurveyData;

#if 0
#pragma mark -
//--------------------------------------------------------------------------
#pragma mark Function headers
//--------------------------------------------------------------------------
#endif

// Headers for three illustrative functions
int simpleFunc1(int x, int* y);
int simpleFunc2(int x, int* y);
SurveyData northmost(SurveyData pt1, SurveyData* pt2);

#if 0
#pragma mark -
//--------------------------------------------------------------------------
#pragma mark Source code
//--------------------------------------------------------------------------
#endif

int main(int argc, const char * argv[]) {
	//---------------------------------------------
	//	Part 1: Basic pointer declaration and usage
	//---------------------------------------------
	printf("Part 1\n------\n");
	
	//	a and b are variables of type int
	//	p is a pointer to a, so its type is int* ---> pointer to int
	int a = 56;
	int* p = &a;
	printf("\tPoint 1.1: a = %3d             *p = %3d   p = %p\n", a, (*p), p);
	
	// we write *p to "dereference" the pointer.
	// As an rvalue, it refers to the value at the location pointed to by ap
	int b = *p + 2;
	printf("\tPoint 1.2: a = %3d   b = %3d   *p = %3d   p = %p\n", a, b, (*p), p);
	
	// As an lvalue, we use it to assign a value at the location pointed at by ap
	*p = 123;
	printf("\tPoint 1.3: a = %3d   b = %3d   *p = %3d   p = %p\n", a, b, (*p), p);
	
	//	Note: lvalue and rvalue are actual classical technical terms.  You can do a search
	//	C pointer rvalue lvalue
	///	to read more on the topic
	
	// of course, we can change the value of p, what it points to
	p = &b;
	(*p)++;
	printf("\tPoint 1.4: a = %3d   b = %3d   *p = %3d   p = %p\n", a, b, (*p), p);
	
	//--------------------------------------------------------------
	//	Part 2: Of course, we could do this with any other data type
	//--------------------------------------------------------------
	printf("\nPart 2\n------\n");
	float fa = 12.3456789f;
	float* fp = &fa;
	printf("\tPoint 2.1: fa = %7.3f                  *fp = %7.3f   fp = %p\n", fa, (*fp), fp);
	
	// we write *fp to "dereference" the pointer.
	// As an rvalue, it refers to the value at the location pointed to by fp
	float fb = *fp + 6.2f;
	printf("\tPoint 2.2: fa = %7.3f   fb = %7.3f   *fp = %7.3f   fp = %p\n", fa, fb, (*fp), fp);
	
	// As an lvalue, we use it to assign a value at the location pointed at by fp
	*fp = 987.56;
	printf("\tPoint 2.3: fa = %7.3f   fb = %7.3f   *fp = %7.3f   fp = %p\n", fa, fb, (*fp), fp);
	
	// of course, we can change the value of fp, what it points to
	fp = &fb;
	(*fp)++;
	printf("\tPoint 2.4: fa = %7.3f   fb = %7.3f   *fp = %7.3f   fp = %p\n", fa, fb, (*fp), fp);
	
	//--------------------------------------------------------------
	//	Part 3: Including custom types
	//--------------------------------------------------------------
	printf("\nPart 3\n------\n");

	SurveyData pt1 = {45, 120, 123.25, FORREST}; // declaration-initialization is ok;
	//pt1 = {45, 120, 123.25, FORREST};	this is not ok
	SurveyData pt2;
	pt2 = pt1;	//	copy is fine (but beware if struct members are pointers!)
	pt2.x = 100;
	pt2.elev = -20.35f;
	
	SurveyData* fpt = &pt2;
	fpt->type = POLDER;		//	shortcut for (*fpt).type
	
	// Note that the type comes out as an integer
	printf("\tPoint 3: pt1: {x = %3d   y = %3d  elev = %6.2f  type: %d\n",
			pt1.x, pt1.y, pt1.elev, pt1.type);
	printf("\t         pt2: {x = %3d   y = %3d  elev = %6.2f  type: %d\n",
			pt2.x, pt2.y, pt2.elev, pt2.type);
	
	
	SurveyData pt3 = northmost(pt2, &pt1);
	printf("\tPoint 4: pt1: {x = %3d   y = %3d  elev = %6.2f  type: %d\n",
			pt1.x, pt1.y, pt1.elev, pt1.type);
	printf("\t         pt2: {x = %3d   y = %3d  elev = %6.2f  type: %d\n",
			pt2.x, pt2.y, pt2.elev, pt2.type);
	printf("\t         pt3: {x = %3d   y = %3d  elev = %6.2f  type: %d\n",
			pt3.x, pt3.y, pt3.elev, pt3.type);

	//--------------------------------------------------------------
	//	Part 4: Passing of "output" parameters
	//--------------------------------------------------------------
	printf("\nPart 4\n------\n");
	
	// Just like in Java, in standard C function paramters are only passed by value
	//	The value of the parameter cannot be changed.  But if the value passed is
	//	a pointer, then the value of what the pointer points to may be changed.
	int m = 10, n = 25;
	printf("\tPoint 4.1: m = %4d   n = %4d\n", m, n);
	int k = simpleFunc1(m, &n);
	printf("\tPoint 4.2: m = %4d   n = %4d   k = %4d\n", m, n, k);

	m = 10; n = 25;
	printf("\tPoint 4.3: m = %4d   n = %4d\n", m, n);
	k = simpleFunc2(m, &n);
	printf("\tPoint 4.4: m = %4d   n = %4d   k = %4d\n", m, n, k);
	
	
	//--------------------------------------------------------------
	//	Part 5: Pointer to a function
	//--------------------------------------------------------------
	printf("\nPart 5\n------\n");

	//	What funcPt points to is a function that takes an in and a pointer to int as parameters
	//	and returns an int
	int (*funcPt)(int, int*) = NULL;
	int keepAsking = TRUE;
	
	while (keepAsking)
	{
		printf("\tDo you want to use function 1 or 2? ");
		int choice;
		scanf("%d", &choice);
		switch (choice)
		{
			case 1:
				printf("\t\tOK, you selected function 1\n");
				funcPt = simpleFunc1;
				keepAsking = FALSE;
				break;
			case 2:
				printf("\t\tOK, you selected function 2\n");
				funcPt = simpleFunc2;
				keepAsking = FALSE;
				break;
			default:
				printf("\t\tType either 1 or 2, you knucklehead!\n");
				break;
		}
	}
	m = 10; n = 25;
	printf("\tPoint 5.1: m = %4d   n = %4d\n", m, n);
	k = funcPt(m, &n);
	printf("\tPoint 5.2: m = %4d   n = %4d   k = %4d\n", m, n, k);
	
	
	
    return 0;
}

// This is a simple function with two parameters:
//		one is an input parameter
//		the other implements an input/output parameter by using a pointer
//	Of course, because C uses value passing, neither parameter's value is changed, it's
//	the value of what the second parameter points to that is modified.
//	If you want to "return" multiple values without encapsulating them in a struct,
//	your only choice is to pass a series of pointers as arguments).
//	For the purists:  This function has a return value, and also a "side effect," since
//	the value of what the second parameter points to is modified.
int simpleFunc1(int x, int* y)
{
	//	silly code
	*y += x*2;
	x++;
	
	return x * *y;
}

//	Note that this function, like the previous one doesn't do anything meaningful
//	I am just trying to illustrate basic stuff that you can do with pointers
//	Here again, this function has a return value and a side effect
int simpleFunc2(int x, int* y)
{
	//	silly code
	(*y)--;		//	decrements the value at the location that y points to
	x++;
	
	return x - *y;
}

//	This is not Java.  So pt1 is not simply a reference to a SurveyData object.
//	pt1 is a **copy** of the struct that was defined in the caller function.
//	The same thing is happening with the return value:  We are returning a copy of the
//	struct created inside this function.
//	Keep this in mind:
//		1. Passing by value can be quite costly in terms of performance if
//			you end up doing a lot of copying.
//		2. If one of the fields of the structs is a pointer (pointing to an array), then
//			you simply make a copy of the pointer, not of the entire array.  There is only
//			one array and both structs point to it.
SurveyData northmost(SurveyData pt1, SurveyData* pt2)
{
	SurveyData newPt;
	newPt.x = pt1.x + pt2->x;   // (*pt2).x
	newPt.y = 23;
	
//	This is just to belabor a point that I already made:  In C/C++ there is no
//	default initialization.
//	Run the program first and look at the out put, then enable the lines below
//	again, and compare.
//	Your variable (here, the struct and its fields) get
//	a memory slot to occupy, and gets initialized to whatever junk was already
//	there in memory.  Be very careful about that!  This is a *very* common source
//	of hard-to-track bugs (and particularly common for people coming from Java).

//	newPt.elev = 0.5f * (pt1.elev + pt2->elev);
//	newPt.type = pt1.type;
	return newPt;
}


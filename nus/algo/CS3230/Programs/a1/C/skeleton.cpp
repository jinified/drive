/**
     *======================================================================
     * Course:    CS3230 Design and Analysis of Algorithms
     *            Fall 2014, School of Computing, NUS
     *            Skeleton Code provided by Jonathan
     *
     * Student:   [student's name]
     * Tutorial:  G2 (for example) 
     * Program:   Name of Program, 
     * Language:  C++
     * Purpose:   Skeleton code for Programming Assignment 1.
     *            Student MUST use the skeleton code and fill
     *            in the implementation code necessary to make
     *            it work.
     *      
     *            NOTE: The method findStableMarriage()  
     *                  MUST NOT be modified.
     *
     *========================================================================
*/

#include <cstdio>
#include <vector>
using namespace std;

void initializeEachPersonFree()
{

}

//return true iff there is a man who is free and has not proposed anyone
bool someManIsFreeAndHasNotProposed()
{
	return true;
}

//return the index of the man who is free and has not proposed anyone
int chooseThatMan()
{
	return 1;
}

//return the index of the first woman on Man #manIndex's list whom he has not yet proposed
int firstWomanOnManList(int manIndex)
{
	return 1;
}

//return true iff woman #womanIndex is free
bool isFree(int womanIndex)
{
	return true;
}

//assign Man #manIndex and Woman #womanIndex to be engaged
void assign(int manIndex,int womanIndex)
{

}

//return true iff Woman #womanIndex prefers Man #firstManIndex to Man #secondManIndex
bool prefers(int womanIndex,int firstManIndex,int secondManIndex)
{
	return true;
}

//set Man #manIndex to be free
void setFree(int manIndex)
{

}

//Man #manIndex get rejected by Woman #womanIndex
void rejected(int manIndex,int womanIndex)
{

}

//return the index of man who is the fiance of Woman #womanIndex
int fiance(int womanIndex)
{
	return 1;
}

void findStableMarriage()
{
	//Initialize each person to be free.
	initializeEachPersonFree(); 
	//while (some man is free and hasn't proposed to every woman)
	while (someManIsFreeAndHasNotProposed())
	{
		//Choose such a man m
		int freeMan = chooseThatMan();
		//w = 1st woman on m's list to whom m has not yet proposed
		int firstWoman = firstWomanOnManList(freeMan);
		//if (w is free)
		if (isFree(firstWoman)) 
		{
			//assign m and w to be engaged
			assign(freeMan,firstWoman);
		}
		//else if (w prefers m to her fiancé m')
		else if (prefers(firstWoman,freeMan,fiance(firstWoman)))
		{
			//assign m and w to be engaged, and m' to be free
			setFree(fiance(firstWoman)); assign(freeMan,firstWoman);
		//else
		} else
		{
			//w rejects m
			rejected(freeMan,firstWoman);
		}
	}
}

int main()
{	
	
	return 0;
}


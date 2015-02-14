/**
 *======================================================================
 * Course:    CS3230 Design and Analysis of Algorithms
 *            Fall 2014, School of Computing, NUS
 *            Skeleton Code provided by Jonathan
 *
 * Student:   NGUYEN DUC THIEN
 * Tutorial:  3
 * Program:   main.cpp
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

#define MAX_MEN 501

using namespace std;

struct Man {
    vector<int> prefList;
    // int iPrefList[MAX_MEN]; // Tobe removed
    int curIndex; // curIndex always point to the next prefered woman
};

struct Woman {
    int iPrefList[MAX_MEN]; // man -> rank
    int curPartner;
};

int m, n; // Number of men and women respectively

/* Men and Women are indexed from 0 */
vector<int> freeMen;
vector<Man> men;
vector<Woman> women;
int H[MAX_MEN];

void initializeEachPersonFree()
{
    for (int i = 0; i < (int) men.size(); i++) {
        freeMen.push_back(i);
        men[i].curIndex = 0;
    }
    for (int i = 0; i < n; i++) {
        women[i].curPartner = -1;
    }
}

//return true iff there is a man who is free and has not proposed anyone
bool someManIsFreeAndHasNotProposed()
{
    return freeMen.size() > 0;
}

//return the index of the man who is free and has not proposed anyone
int chooseThatMan()
{
    int chosenMan = freeMen.back();
    freeMen.pop_back();
    return chosenMan;
}

//return the index of the first woman on Man #manIndex's list whom he has not yet proposed
int firstWomanOnManList(int manIndex)
{
    return men[manIndex].prefList[men[manIndex].curIndex];
}

//return true iff woman #womanIndex is free
bool isFree(int womanIndex)
{
    return women[womanIndex].curPartner == -1;
}

//assign Man #manIndex and Woman #womanIndex to be engaged
void assign(int manIndex,int womanIndex)
{
    women[womanIndex].curPartner = manIndex;
    men[manIndex].curIndex++;
}

//return true iff Woman #womanIndex prefers Man #firstManIndex to Man #secondManIndex
bool prefers(int womanIndex,int firstManIndex,int secondManIndex)
{
    return women[womanIndex].iPrefList[firstManIndex] <
        women[womanIndex].iPrefList[secondManIndex];
}

//set Man #manIndex to be free
void setFree(int manIndex)
{
    freeMen.push_back(manIndex);
}

//Man #manIndex get rejected by Woman #womanIndex
void rejected(int manIndex,int womanIndex)
{
    men[manIndex].curIndex++;
    freeMen.push_back(manIndex);
}

//return the index of man who is the fiance of Woman #womanIndex
int fiance(int womanIndex)
{
    return women[womanIndex].curPartner;
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

/*
bool isStable() {
    for (int i = 0; i < (int) men.size(); i++) {
        for (int j = 0; j < n; j++) {
            if (women[j].iPrefList[i] < women[j].iPrefList[women[j].curPartner] &&
                men[i].iPrefList[j] < men[i].iPrefList[men[i].prefList[men[i].curIndex-1]]) {
                printf("branch: %d, intern: %d\n", i, j);
                return false;
            }
        }
    }
    return true;
}
*/

int main()
{
    int t; // number of test cases;
    scanf("%d", &t);
    while (t--) {
        freeMen.clear();
        men.clear();
        women.clear();

        scanf("%d %d", &m, &n);
        /* Index H from 1 for easy cumulative calculation later */
        H[0] = 0;
        for (int i = 1; i <= m; i++) {
            scanf("%d", &H[i]);
        }

        int tmp;
        for (int i = 0; i < m; i++) {
            Man newMan;
            for (int j = 0; j < n; j++) {
                scanf("%d", &tmp);
                tmp--;
                newMan.prefList.push_back(tmp);
                // newMan.iPrefList[tmp] = j; // Tobe removed
            }
            for (int j = 0; j < H[i+1]; j++) {
                men.push_back(newMan);
            }
        }

        for (int i = 1; i <= m; i++) {
            H[i] = H[i-1] + H[i];
        }

        for (int i = 0; i < n; i++) {
            Woman newWoman;
            for (int j = 0; j < m; j++) {
                scanf("%d", &tmp);
                tmp--;
                for (int k = H[tmp]; k < H[tmp+1]; k++) {
                    newWoman.iPrefList[k] = j;
                }
            }
            women.push_back(newWoman);
        }

        findStableMarriage();
        // printf("--%d--\n", isStable()); // Tobe removed

        for (int i = 0; i < m; i++) {
            for (int j = H[i]; j < H[i+1]; j++) {
                printf("%d %d\n", i + 1,
                       men[j].prefList[men[j].curIndex - 1] + 1);
            }
        }
    }
    return 0;
}


#include <stdio.h>
#include <string.h>

#define MAX_NUM_VARS 15
#define MAX_NUM_CLAUSES 100
#define MAX_NUM_GATES 1000

#define AND 0
#define OR 1
#define NOT 2

void updateGates(int gates[][3], int n, int gateIndex,
                 int gateType, int input1, int input2) {
    int index = gateIndex - n - 1;
    gates[index][0] = gateType;
    gates[index][1] = input1;
    gates[index][2]= input2;
}

void printGates(int gates[][3], int numGates) {
    printf("%d\n", numGates);
    for (int i = 0; i < numGates; i++) {
        switch (gates[i][0]) {
            case AND:
                printf("AND %d %d\n", gates[i][1], gates[i][2]);
                break;
            case OR:
                printf("OR %d %d\n", gates[i][1], gates[i][2]);
                break;
            case NOT:
                printf("NOT %d \n", gates[i][1]);
                break;
            default:
                printf("Something when wrong: %d\n", gates[i][0]);
        }
    }
}

int main() {
    int t;
    int c, n; // Number of clauses and variables respectively
    int negated[MAX_NUM_VARS + 1]; // Gate number of a variable's complement
    int gates[MAX_NUM_GATES][3];
    int curGate;

    scanf("%d", &t);

    while (t--) {
        /* Initialize variables for this test case */
        scanf("%d %d", &c, &n);
        memset(negated, 0, sizeof(negated));
        curGate = n + 1;

        int numVars, tobeOred = 0, tobeAnded = 0, curVar;
        for (int i = 0; i < c; i++) {
            scanf("%d %d", &numVars, &tobeOred);

            if (tobeOred < 0) {
                if (negated[-tobeOred] == 0) {
                    /* Create new NOT gate */
                    updateGates(gates, n, curGate, NOT, -tobeOred, 0);
                    negated[-tobeOred] = curGate;
                    tobeOred = curGate;
                    curGate++;
                } else {
                    tobeOred = negated[-tobeOred];
                }
            }

            for (int j = 1; j < numVars; j++) {
                scanf("%d", &curVar);
                if (curVar < 0) {
                    if (negated[-curVar] == 0) {
                        /* Create new NOT gate */
                        updateGates(gates, n, curGate, NOT, -curVar, 0);
                        negated[-curVar] = curGate;
                        curGate++;

                        /* OR the new NOT gate with tobeOred */
                        updateGates(gates, n,
                                    curGate, OR, tobeOred, curGate - 1);
                        tobeOred = curGate;
                        curGate++;
                    } else {
                        /* OR the existing complement of curVar with tobeOred */
                        updateGates(gates, n,
                                    curGate, OR, tobeOred, negated[-curVar]);
                        tobeOred = curGate;
                        curGate++;
                    }
                } else {
                    /* OR curVar with tobeOred */
                    updateGates(gates, n, curGate, OR, tobeOred, curVar);
                    tobeOred = curGate;
                    curGate++;
                }
            }

            if (tobeAnded == 0) {
                tobeAnded = curGate - 1;
            } else {
                updateGates(gates, n, curGate, AND, tobeAnded, curGate - 1);
                tobeAnded = curGate;
                curGate++;
            }
        }

        printGates(gates, curGate - n - 1);
    }

    return 0;
}

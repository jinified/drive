#include <stdio.h>
#include <string.h>

#define MAX_NUM_GATES 100
#define MAX_NUM_VAR 15

#define GET_VAR(vars, numVars, varIndex) \
    ((vars) & (mask[(numVars) - (varIndex)]))

#define GET_OPERAND(op, vars, n, gOut) \
    (((op) <= (n)) ? (GET_VAR((vars), (n), (op))) : ((gOut)[(op)- n- 1]))

#define AND 0
#define OR 1
#define NOT 2

int mask[MAX_NUM_VAR];

bool runCircuit(int& vars, int& numVars,
                int gates[][3], int& numGates, bool gatesOutput[]) {
    memset(gatesOutput, 0, numGates * sizeof(bool));
    for (int i = 0; i < numGates; i++) {
        switch (gates[i][0]) {
            case AND:
               gatesOutput[i] = GET_OPERAND(gates[i][1],
                                            vars, numVars, gatesOutput) &&
                                GET_OPERAND(gates[i][2],
                                            vars, numVars, gatesOutput); 
               break;
            case OR:
               gatesOutput[i] = GET_OPERAND(gates[i][1],
                                            vars, numVars, gatesOutput) ||
                                GET_OPERAND(gates[i][2],
                                            vars, numVars, gatesOutput); 
               break;
            case NOT:
               gatesOutput[i] = !GET_OPERAND(gates[i][1],
                                             vars, numVars, gatesOutput);
        }
    } 

    return gatesOutput[numGates - 1];
}

int main() {
    for (int i = 0; i < MAX_NUM_VAR; i++) {
        mask[i] = 1 << i;
    }

    int t;
    int g, n; // Number of gates and variables respectively
    int gates[MAX_NUM_GATES][3];
    bool gatesOutput[MAX_NUM_GATES];
    char s[5];

    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &g, &n);

        for (int i = 0; i < g; i++) {
            scanf("%3s", s); 
            if (strcmp(s, "AND") == 0) {
                gates[i][0] = AND;
                scanf("%d %d", &gates[i][1], &gates[i][2]);
            } else if (strcmp(s, "OR") == 0) {
                gates[i][0] = OR;
                scanf("%d %d", &gates[i][1], &gates[i][2]);
            } else if (strcmp(s, "NOT") == 0) {
                gates[i][0] = NOT;
                scanf("%d", &gates[i][1]);
            } else {
                printf("Something went wrong: %s\n", s);
                return 1;
            }
        }

        int last = (1 << n) - 1;
        for (int i = 0; i <= last; i++) {
            printf("%d\n", runCircuit(i, n, gates, g, gatesOutput));
        }
    }

    return 0;
}

#include <stdio.h>

#define MAX_NUM_CLAUSES 100
#define MAX_NUM_VAR 15

#define GET_VAR(vars, numVars, varIndex) \
    ((vars) & (mask[(numVars) - (varIndex)]))

struct Clause {
    int numVars;
    int vars[MAX_NUM_VAR];
};

int mask[MAX_NUM_VAR];

bool truthValue(int& vars, int& numVars, Clause clauses[], int& numClauses) {
    bool rval = true;

    for (int i = 0; i < numClauses; i++) {
        bool clauseVal = false;
        for (int j = 0; j < clauses[i].numVars; j++) {
            if (clauses[i].vars[j] < 0) {
                clauseVal = clauseVal ||
                    !GET_VAR(vars, numVars, -clauses[i].vars[j]);
            } else {
                clauseVal = clauseVal ||
                    GET_VAR(vars, numVars, clauses[i].vars[j]);
            }
        }

        rval = rval && clauseVal;
    }

    return rval;
}

int main() {
    for (int i = 0; i < MAX_NUM_VAR; i++) {
        mask[i] = 1 << i;
    }

    int t;
    int c, n;
    Clause clauses[MAX_NUM_CLAUSES];

    scanf("%d", &t);
    while (t--) {
        /* Getting all input */
        scanf("%d %d", &c, &n);
        for (int i = 0; i < c; i++) {
            scanf("%d", &clauses[i].numVars);
            for (int j = 0; j < clauses[i].numVars; j++) {
                scanf("%d", &clauses[i].vars[j]);
            }
        }

        /* Find truth values */
        int last = (1 << n) - 1;
        for (int i = 0; i <= last; i++) {
            printf("%d\n",truthValue(i, n, clauses, c));
        }
    }

    return 0;
}

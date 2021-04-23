#include <cstdlib>
#include <cstring>

struct Expression {
    char data[100];
    Expression *left, *right;
} typedef *pExpression;

void arithExpression();
pExpression createTree(char expression[], int first, int last);
int priority(char sign);
int calc(pExpression tree);
void freeMemory(pExpression tree);
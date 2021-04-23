#include "func.h"
#include <iostream>
#include <string>

using namespace std;

void arithExpression() {
    char str[150];
    pExpression tree;

    cout << "\nInput: ";
    cin >> str;

    tree = createTree(str, 0, strlen(str) - 1);

    cout << "\nResult: " << calc(tree);

    freeMemory(tree);
}

pExpression createTree(char expression[], int first, int last) {
    int k, prt;
    int minPrt = 100;
    int countBKT = 0;

    auto tree = new Expression;

    for(int i = first; i <= last; i++) {
        if (expression[i] == '(') {
            countBKT++;
            continue;
        }

        if (expression[i] == ')') {
            countBKT--;
            continue;
        }

        if (countBKT > 0)
            continue;

        prt = priority(expression[i]);
        if (prt <= minPrt) {
            minPrt = prt;
            k = i;
        }
    }

    if (minPrt == 100) {
        if (expression[first] == '(' && expression[last] == ')') {
            delete tree;
            return createTree(expression, first + 1, last - 1);
        } else {
            k = last - first + 1;
            strncpy(tree->data, expression + first, k);
            tree->data[k] = '\0';
            tree->left = nullptr;
            tree->right = nullptr;
            return tree;
        }
    }

    tree->data[0] = expression[k];
    tree->data[1] = '\0';
    tree->left = createTree(expression, first, k - 1);
    tree->right = createTree(expression, k + 1, last);

    return tree;
}

int priority(char sign) {
    if (sign=='+' || sign=='-') {
        return 1;
    } else if (sign=='*' || sign=='/') {
        return 2;
    } else {
        return 300;
    }
}

int calc(pExpression tree) {
    int one, two;
    if(!tree->left)
        return stoi(tree->data);

    one = calc(tree->left);
    two = calc(tree->right);

    switch(tree->data[0])
    {
        case '+':
            return one+two;
        case '-':
            return one-two;
        case '*':
            return one*two;
        case '/':
            return one/two;
    }
    return 666;
}

void freeMemory(pExpression tree) {
    if(tree != nullptr) {
        freeMemory(tree->left);
        freeMemory(tree->right);
        delete tree;
    }
}
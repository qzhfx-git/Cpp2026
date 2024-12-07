//
// Created by ASUS on 24-12-7.
//

#ifndef TREENODE_H
#define TREENODE_H
#include "Token.h"
#include <stack>

inline std::map<std::string, Val> mp;

class TreeNode {
public:
    Val x;
    char op;
    std::string var;
    int type;
    TreeNode *L;
    TreeNode *R;

    TreeNode() {
    }

    TreeNode(TreeNode *_L, char _op, TreeNode *_R) {
        type = OP;
        L = _L;
        op = _op;
        R = _R;
    }

    TreeNode(Val _x) {
        type = NUM;
        x = _x;
    }

    TreeNode(std::string _s) {
        type = VAR;
        var = _s;
    }


    Val eval() {
        if (type == NUM)return x;
        if (type == VAR)return mp[var];
        switch (op) {
            case '+': return L->eval() + R->eval();
            case '-': return L->eval() - R->eval();
            case '*': return L->eval() * R->eval();
            case '/': return L->eval() / R->eval();
            case '=':
                mp[L->var] = R->eval();
                return mp[L->var];
            case 'a': return L->eval() == R->eval();
            case 'b':
                if (L->eval() == 1 && R->eval() == 0)return 0;
                else return 1;
            case '|': return L->eval() || R->eval();
            case '&': return L->eval() && R->eval();
            case '!': return !((R->eval() == 1));
        }
    }
};

void addNode();

Val Expression(std::string s);

#endif //TREENODE_H

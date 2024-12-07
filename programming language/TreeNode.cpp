//
// Created by ASUS on 24-12-7.
//

#include "TreeNode.h"
std::stack<TreeNode *> num_stk;
std::stack<char> op_stk;

void addNode() {
    TreeNode *R = num_stk.top();
    num_stk.pop();
    TreeNode *L = new TreeNode(Val(0));
    char op = op_stk.top();
    op_stk.pop();
    if (op == '!') {
        num_stk.push(new TreeNode(L, op, R));
    } else {
        if (num_stk.size())L = num_stk.top(), num_stk.pop();
        num_stk.push(new TreeNode(L, op, R));
    }
}

int level[128]; //优先级;
Val Expression(std::string s) {
    level['!'] = 5;
    level['*'] = level['/'] = 2;
    level['+'] = level['-'] = 1;
    level['='] = -5;
    level['a'] = level['b'] = -4;
    level['|'] = -3, level['&'] = -2;
    level['('] = level[')'] = -100;
    while (num_stk.size())num_stk.pop();
    while (op_stk.size())op_stk.pop();
    for (auto t: Lexer(s)) {
        // std::cerr << t << std::endl;
        if (t.type == NUM) {
            num_stk.push(new TreeNode(t.num));
        } else if (t.type == VAR) {
            num_stk.push(new TreeNode(t.var));
        } else if (t.type == OP) {
            switch (t.op) {
                case '(':
                    op_stk.push(t.op);
                    break;
                case ')':
                    while (op_stk.size() && op_stk.top() != '(') {
                        addNode();
                    }
                    op_stk.pop();
                    break;
                default:
                    while (op_stk.size() && level[op_stk.top()] >= level[t.op]) {
                        addNode();
                    }
                    op_stk.push(t.op);
            }
        } else {
            return Val();
        }
    }
    while (op_stk.size()) {
        addNode();
    }
    if (num_stk.empty())return Val();
    return num_stk.top()->eval();
}

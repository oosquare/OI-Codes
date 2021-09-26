#include <bits/stdc++.h>
using namespace std;

enum ElementType {Number, Operator, End};
enum OperatorType {Plus, Sub, Multiply, Divide, Power, LeftBracket, RightBracket};

struct Element {
    ElementType type;
    OperatorType op;
    int num;

    Element() {}

    Element(ElementType et, OperatorType ot, int n) : type(et), op(ot), num(n) {}

    string toString() {
        if (type == ElementType::Number) {
            return to_string(num);
        } else if (type == ElementType::Operator) {
            if (op == OperatorType::Plus) {
                return "+";
            } else if (op == OperatorType::Sub) {
                return "-";
            } else if (op == OperatorType::Multiply) {
                return "*";
            } else if (op == OperatorType::Divide) {
                return "/";
            } else if (op == OperatorType::Power) {
                return "^";
            }
        }
        return "";
    }
};

string expr;
vector<Element> midexpr, sufexpr;
int priority[10];

void init() {
    priority[OperatorType::Plus] = priority[OperatorType::Sub] = 1;
    priority[OperatorType::Multiply] = priority[OperatorType::Divide] = 2;
    priority[OperatorType::Power] = 3;
    priority[OperatorType::LeftBracket] = priority[OperatorType::RightBracket] = 4;
}

void parse() {
    bool ax = false;
    stack<int> op;
    for (int e = 0; e < (int)midexpr.size(); ++e) {
        auto i = midexpr[e];
        if (i.type == ElementType::End) {
            while (!op.empty()) {
                sufexpr.push_back(Element(ElementType::Operator, (OperatorType)op.top(), 0));
                op.pop();
            }
            break;
        }
        if (i.type == ElementType::Number) {
            sufexpr.push_back(Element(ElementType::Number, (OperatorType)0, i.num));
            if (!op.empty() && priority[op.top()] == 2) {
                if (midexpr[e + 1].op != OperatorType::Power) {
                    sufexpr.push_back(Element(ElementType::Operator, (OperatorType)op.top(), 0));
                    op.pop();
                }
            }
        }
        if (i.type == ElementType::Operator) {
            if (i.op == OperatorType::LeftBracket) {
                op.push(OperatorType::LeftBracket);
            } else if (i.op == OperatorType::RightBracket) {
                while (op.top() != OperatorType::LeftBracket) {
                    sufexpr.push_back(Element(ElementType::Operator, (OperatorType)op.top(), 0));
                    op.pop();
                }
                op.pop();
            } else if (i.op == OperatorType::Power) {
                ax = true;
                op.push(i.op);
            } else if (priority[i.op] == 2) {
                if (ax == true) {
                    while (!op.empty() && op.top() == OperatorType::Power) {
                        sufexpr.push_back(Element(ElementType::Operator, (OperatorType)op.top(), 0));
                        op.pop();
                    }
                    ax = false;
                }
                while (!op.empty() && priority[op.top()] == 2) {
                    sufexpr.push_back(Element(ElementType::Operator, (OperatorType)op.top(), 0));
                    op.pop();
                }
                op.push(i.op);
            } else if (priority[i.op] == 1) {
                if (ax == true) {
                    while (!op.empty() && op.top() == OperatorType::Power) {
                        sufexpr.push_back(Element(ElementType::Operator, (OperatorType)op.top(), 0));
                        op.pop();
                    }
                    ax = false;
                }
                while (!op.empty() && priority[op.top()] <= 2) {
                    sufexpr.push_back(Element(ElementType::Operator, (OperatorType)op.top(), 0));
                    op.pop();
                }
                op.push(i.op);
            }
        }
    }
}

void calculate() {
    int num[200], top = 0;
    for (auto i : sufexpr)
        cout << i.toString() << " ";
    cout << endl;
    for (int e = 0; e < (int)sufexpr.size(); ++e) {
        auto i = sufexpr[e];
        if (i.type == ElementType::Number) {
            num[++top] = i.num;
        } else if (i.type == ElementType::Operator) {
            int y = num[top--], x = num[top--], res;
            if (i.op == OperatorType::Plus) {
                res = x + y;
            } else if (i.op == OperatorType::Sub) {
                res = x - y;
            } else if (i.op == OperatorType::Multiply) {
                res = x * y;
            } else if (i.op == OperatorType::Divide) {
                res = x / y;
            } else if (i.op == OperatorType::Power) {
                res = pow(x, y);
            }
            num[++top] = res;
            for (int j = 1; j <= top; ++j)
                cout << num[j] << " ";
            for (int j = e + 1; j < (int)sufexpr.size(); ++j)
                cout << sufexpr[j].toString() << " ";
            cout << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    init();
    cin >> expr;
    for (auto i : expr) {
        if (isdigit(i)) {
            midexpr.push_back(Element(ElementType::Number, (OperatorType)0, i - '0'));
        } else if (i == '+') {
            midexpr.push_back(Element(ElementType::Operator, OperatorType::Plus, 0));
        } else if (i == '-') {
            midexpr.push_back(Element(ElementType::Operator, OperatorType::Sub, 0));
        } else if (i == '*') {
            midexpr.push_back(Element(ElementType::Operator, OperatorType::Multiply, 0));
        } else if (i == '/') {
            midexpr.push_back(Element(ElementType::Operator, OperatorType::Divide, 0));
        } else if (i == '^') {
            midexpr.push_back(Element(ElementType::Operator, OperatorType::Power, 0));
        } else if (i == '(') {
            midexpr.push_back(Element(ElementType::Operator, OperatorType::LeftBracket, 0));
        } else if (i == ')') {
            midexpr.push_back(Element(ElementType::Operator, OperatorType::RightBracket, 0));
        }
    }
    midexpr.push_back(Element(ElementType::End, (OperatorType)0, 0));
    parse();
    calculate();
    return 0;
}
#include <iostream>
#include <stack>
#include <string>

int priority(char op) {
  if (op == '+' || op == '-')
    return 1;
  if (op == '*' || op == '/')
    return 2;
  return 0;
}

float applyOp(float a, float b, char op) {
  switch (op) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    return a / b;
  }
  return 0;
}

float evaluate(std::string expression) {
  std::stack<float> numberStack;
  std::stack<char> operatorStack;
  for (int i = 0; i < expression.length(); i++) {
    if (expression[i] == ' ')
      continue;
    else if (expression[i] == '(') {
      operatorStack.push(expression[i]);
    } else if (isdigit(expression[i]) || expression[i] == '-' ||
               expression[i] == '.') {
      float val = 0;
      int sign = 1;
      if (expression[i] == '-') {
        if (i > 0 && (isdigit(expression[i - 1]) || expression[i - 1] == ')')) {
          operatorStack.push(expression[i]);
          continue;
        }
        sign = -1;
        i++;
      }
      while (i < expression.length() &&
             (isdigit(expression[i]) || expression[i] == '.')) {
        if (expression[i] == '.') {
          float decimalPlace = 10;
          i++;
          while (i < expression.length() && isdigit(expression[i])) {
            val += (expression[i] - '0') / decimalPlace;
            decimalPlace *= 10;
            i++;
          }
        } else {
          val = (val * 10) + (expression[i] - '0');
          i++;
        }
      }
      numberStack.push(sign * val);
      i--;
    } else if (expression[i] == ')') {
      while (!operatorStack.empty() && operatorStack.top() != '(') {
        float val2 = numberStack.top();
        numberStack.pop();
        float val1 = numberStack.top();
        numberStack.pop();
        char op = operatorStack.top();
        operatorStack.pop();
        numberStack.push(applyOp(val1, val2, op));
      }
      if (!operatorStack.empty())
        operatorStack.pop();
    } else {
      while (!operatorStack.empty() &&
             priority(operatorStack.top()) >= priority(expression[i])) {
        float val2 = numberStack.top();
        numberStack.pop();
        float val1 = numberStack.top();
        numberStack.pop();
        char op = operatorStack.top();
        operatorStack.pop();
        numberStack.push(applyOp(val1, val2, op));
      }
      operatorStack.push(expression[i]);
    }
  }
  while (!operatorStack.empty()) {
    float val2 = numberStack.top();
    numberStack.pop();
    float val1 = numberStack.top();
    numberStack.pop();
    char op = operatorStack.top();
    operatorStack.pop();
    numberStack.push(applyOp(val1, val2, op));
  }
  return numberStack.top();
}

int main() {
  std::string expression;
  std::cout << "Enter a mathematical expression: " << std::endl;
  std::getline(std::cin, expression);
  std::cout << expression << " = " << evaluate(expression) << std::endl;
  return 0;
}

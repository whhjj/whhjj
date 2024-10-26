#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <cctype>
#include"Stack.cpp"



class Calculator {
public:
    int calculate(const std::string& expression) {
        std::istringstream tokens(expression);
        Stack<int> values;      
        Stack<char> operators;  
        
        char token;
        while (tokens >> token) {
            if (std::isdigit(token)) {
                tokens.putback(token);
                int value;
                tokens >> value;
                values.push(value);
            } else if (isOperator(token)) {
                while (!operators.isEmpty() && precedence(operators.top()) >= precedence(token)) {
                    performOperation(values, operators.top());
                    operators.pop();
                }
                operators.push(token);
            } else {
                throw std::runtime_error("Invalid character in expression.");
            }
        }

        while (!operators.isEmpty()) {
            performOperation(values, operators.top());
            operators.pop();
        }

        return values.top();
    }

private:
    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    void performOperation(Stack<int>& values, char op) {
        int right = values.top(); values.pop();
        int left = values.top(); values.pop();
        switch (op) {
            case '+': values.push(left + right); break;
            case '-': values.push(left - right); break;
            case '*': values.push(left * right); break;
            case '/': 
                if (right == 0) {
                    throw std::runtime_error("Division by zero.");
                }
                values.push(left / right); 
                break;
        }
    }
};

int main() {
    Calculator calc;

    std::string expression;
    std::cout << "请输入一个数学表达式：";
    std::getline(std::cin, expression);

    try {
        int result = calc.calculate(expression);
        std::cout << "结果: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }

    return 0;
}


#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class Stack {
public:
    void push(const T& value) {
        data.push_back(value);
    }

    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty.");
        }
        data.pop_back();
    }

    T top() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty.");
        }
        return data.back();
    }

    bool isEmpty() const {
        return data.empty();
    }

private:
    std::vector<T> data;
};


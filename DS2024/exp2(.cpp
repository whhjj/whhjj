#include <iostream>
#include<vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int largestRectangleArea(const std::vector<int>& heights) {
    std::stack<int> indices;
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i <= n; ++i) {
        int currentHeight = (i == n) ? 0 : heights[i];

        while (!indices.empty() && heights[indices.top()] > currentHeight) {
            int height = heights[indices.top()];
            indices.pop();
            int width = indices.empty() ? i : i - indices.top() - 1;
            maxArea = std::max(maxArea, height * width);
        }
        indices.push(i);
    }

    return maxArea;
}

void generateTestCases() {
    std::srand(std::time(0));  

    for (int i = 0; i < 10; ++i) {
        int size = std::rand() % 125 + 1; 
        std::vector<int> heights(size);
        for (int j = 0; j < size; ++j) {
            heights[j] = std::rand() % 125; 
        }

        int maxArea = largestRectangleArea(heights);
        std::cout << "Test Case " << (i + 1) << ": Max Rectangle Area = " << maxArea << std::endl;
    }
}

int main() {
    generateTestCases();
    return 0;
}


#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cstring>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

// 1. 定义二叉树节点类
class BinTreeNode {
public:
    char data;  // 存储字符
    int weight; // 存储字符的频率
    BinTreeNode *left, *right;

    BinTreeNode(char d, int w) : data(d), weight(w), left(NULL), right(NULL) {}

    bool operator>(const BinTreeNode &other) const {
        return weight > other.weight;
    }
};

// 2. 定义二叉树类
class BinTree {
public:
    BinTreeNode *root;

    BinTree() : root(NULL) {}
    BinTree(BinTreeNode *r) : root(r) {}

    void postOrderPrint(BinTreeNode* node) {
        if (node) {
            postOrderPrint(node->left);
            postOrderPrint(node->right);
            cout << node->data << ": " << node->weight << endl;
        }
    }

    void postOrderPrint() {
        postOrderPrint(root);
    }
};

// 3. 定义位图类 Bitmap
class Bitmap {
private:
    unsigned char* M; // 位图数据
    int N, _sz; // 位图空间N*sizeof(char)*8个比特中含_sz个有效位

protected:
    void init(int n) {
        M = new unsigned char[N = (n + 7) / 8]; // 创建位图，确保空间足够
        memset(M, 0, N); // 初始化位图为0
        _sz = 0;
    }

public:
    Bitmap(int n = 8) { init(n); }  // 默认初始化8个比特位
    ~Bitmap() {
        delete[] M;
        M = NULL;
        _sz = 0;
    }

    int size() { return _sz; } // 返回有效位的数量

    void set(int k) {
        expand(k);
        _sz++;
        M[k >> 3] |= (0x80 >> (k & 0x07)); // 设置第k位为1
    }

    void clear(int k) {
        expand(k);
        _sz--;
        M[k >> 3] &= ~(0x80 >> (k & 0x07)); // 清除第k位
    }

    bool test(int k) {
        expand(k);
        return M[k >> 3] & (0x80 >> (k & 0x07)); // 测试第k位是否为1
    }

    void dump(const char* file) { // 将位图整体导出至指定的文件
        FILE* fp = fopen(file, "w");
        fwrite(M, sizeof(char), N, fp);
        fclose(fp);
    }

    char* bits2string(int n) {
        expand(n - 1); // 扩容
        char* s = new char[n + 1];
        s[n] = '\0';
        for (int i = 0; i < n; i++)
            s[i] = test(i) ? '1' : '0';
        return s;
    }

    void expand(int k) {
        if (k < 8 * N) return;
        int oldN = N;
        unsigned char* oldM = M;
        init(2 * k);  // 扩容
        memcpy(M, oldM, oldN); // 将原数据复制到新空间
        delete[] oldM;
    }
};

// 4. 定义 Huffman 树类
class HuffmanTree {
public:
    BinTree *tree;

    HuffmanTree(const string &text) {
        map<char, int> freq_map;
        for (char c : text) {
            if (isalpha(c)) {
                c = tolower(c);
                freq_map[c]++;
            }
        }

        priority_queue<BinTreeNode*, vector<BinTreeNode*>, greater<BinTreeNode*>> pq;
        for (auto &entry : freq_map) {
            pq.push(new BinTreeNode(entry.first, entry.second));
        }

        while (pq.size() > 1) {
            BinTreeNode* left = pq.top();
            pq.pop();
            BinTreeNode* right = pq.top();
            pq.pop();

            BinTreeNode* parent = new BinTreeNode('\0', left->weight + right->weight);
            parent->left = left;
            parent->right = right;

            pq.push(parent);
        }

        tree = new BinTree(pq.top()); // 最终的 Huffman 树
    }
};

// 5. 定义 Huffman 编码类 HuffCode
class HuffCode {
public:
    map<char, string> huffCodeMap;

    void generateHuffCode(BinTreeNode* node, const string &code) {
        if (node == NULL) return;
        if (node->data != '\0') {
            huffCodeMap[node->data] = code;
        }
        generateHuffCode(node->left, code + "0");
        generateHuffCode(node->right, code + "1");
    }

    void printHuffCode() const {
        for (const auto &entry : huffCodeMap) {
            cout << entry.first << ": " << entry.second << endl;
        }
    }
};

// 6. 定义 Huffman 编码器类
class HuffmanEncoder {
public:
    HuffmanTree huffTree;
    HuffCode huffCode;

    HuffmanEncoder(const string &text) : huffTree(text) {
        huffCode.generateHuffCode(huffTree.tree->root, "");
    }

    string encode(const string &text) {
        string encodedText = "";
        for (char c : text) {
            c = tolower(c);
            if (huffCode.huffCodeMap.find(c) != huffCode.huffCodeMap.end()) {
                encodedText += huffCode.huffCodeMap[c];
            }
        }
        return encodedText;
    }
};

// 7. 从文件中读取文本内容
string readFile(const string &filename) {
    ifstream file(filename);
    string content;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            content += line + " ";
        }
        file.close();
    } else {
        cerr << "Failed to open file: " << filename << endl;
    }
    return content;
}

int main() {
    // 读取文件内容
    string filename = "i have a dream.txt";
    string text = readFile(filename);

    if (text.empty()) {
        cerr << "File is empty or couldn't be read." << endl;
        return 1;
    }

    // 使用 Huffman 编码器进行编码
    HuffmanEncoder encoder(text);

    // 打印 Huffman 编码
    cout << "Huffman Encoding for the Text:" << endl;
    encoder.huffCode.printHuffCode();

    // 对 "dream" 进行编码
    string encodedDream = encoder.encode("dream");
    cout << "\nEncoded 'dream': " << encodedDream << endl;
    // 对 "have" 进行编码
    string encodedHave = encoder.encode("have");
    cout << "\nEncoded 'have': " << encodedHave << endl;
    
    return 0;
}


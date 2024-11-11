#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cstring>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

// 1. ����������ڵ���
class BinTreeNode {
public:
    char data;  // �洢�ַ�
    int weight; // �洢�ַ���Ƶ��
    BinTreeNode *left, *right;

    BinTreeNode(char d, int w) : data(d), weight(w), left(NULL), right(NULL) {}

    bool operator>(const BinTreeNode &other) const {
        return weight > other.weight;
    }
};

// 2. �����������
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

// 3. ����λͼ�� Bitmap
class Bitmap {
private:
    unsigned char* M; // λͼ����
    int N, _sz; // λͼ�ռ�N*sizeof(char)*8�������к�_sz����Чλ

protected:
    void init(int n) {
        M = new unsigned char[N = (n + 7) / 8]; // ����λͼ��ȷ���ռ��㹻
        memset(M, 0, N); // ��ʼ��λͼΪ0
        _sz = 0;
    }

public:
    Bitmap(int n = 8) { init(n); }  // Ĭ�ϳ�ʼ��8������λ
    ~Bitmap() {
        delete[] M;
        M = NULL;
        _sz = 0;
    }

    int size() { return _sz; } // ������Чλ������

    void set(int k) {
        expand(k);
        _sz++;
        M[k >> 3] |= (0x80 >> (k & 0x07)); // ���õ�kλΪ1
    }

    void clear(int k) {
        expand(k);
        _sz--;
        M[k >> 3] &= ~(0x80 >> (k & 0x07)); // �����kλ
    }

    bool test(int k) {
        expand(k);
        return M[k >> 3] & (0x80 >> (k & 0x07)); // ���Ե�kλ�Ƿ�Ϊ1
    }

    void dump(const char* file) { // ��λͼ���嵼����ָ�����ļ�
        FILE* fp = fopen(file, "w");
        fwrite(M, sizeof(char), N, fp);
        fclose(fp);
    }

    char* bits2string(int n) {
        expand(n - 1); // ����
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
        init(2 * k);  // ����
        memcpy(M, oldM, oldN); // ��ԭ���ݸ��Ƶ��¿ռ�
        delete[] oldM;
    }
};

// 4. ���� Huffman ����
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

        tree = new BinTree(pq.top()); // ���յ� Huffman ��
    }
};

// 5. ���� Huffman ������ HuffCode
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

// 6. ���� Huffman ��������
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

// 7. ���ļ��ж�ȡ�ı�����
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
    // ��ȡ�ļ�����
    string filename = "i have a dream.txt";
    string text = readFile(filename);

    if (text.empty()) {
        cerr << "File is empty or couldn't be read." << endl;
        return 1;
    }

    // ʹ�� Huffman ���������б���
    HuffmanEncoder encoder(text);

    // ��ӡ Huffman ����
    cout << "Huffman Encoding for the Text:" << endl;
    encoder.huffCode.printHuffCode();

    // �� "dream" ���б���
    string encodedDream = encoder.encode("dream");
    cout << "\nEncoded 'dream': " << encodedDream << endl;
    // �� "have" ���б���
    string encodedHave = encoder.encode("have");
    cout << "\nEncoded 'have': " << encodedHave << endl;
    
    return 0;
}


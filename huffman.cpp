#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

class Node {
public:
    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char c = 0, int f = 0) : data(c), freq(f), left(nullptr), right(nullptr) {}

    bool operator>(const Node& other) const {
        return freq > other.freq;
    }
};

Node* buildHuffmanTree(const string& data) {
    unordered_map<char, int> freqMap;

    for (char ch : data) {
        freqMap[ch]++;
    }

    priority_queue<Node*, vector<Node*>, greater<Node*>> minHeap;

    for (const auto& pair : freqMap) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        Node* merged = new Node(0, left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        minHeap.push(merged);
    }

    return minHeap.top();
}

void buildHuffmanCodes(Node* node, string currentCode, unordered_map<char, string>& codes) {
    if (node != nullptr) {
        if (node->data != 0) {
            codes[node->data] = currentCode;
        }
        buildHuffmanCodes(node->left, currentCode + "0", codes);
        buildHuffmanCodes(node->right, currentCode + "1", codes);
    }
}

string huffmanEncode(const string& data) {
    Node* root = buildHuffmanTree(data);
    unordered_map<char, string> codes;
    buildHuffmanCodes(root, "", codes);

    string encodedData;
    for (char ch : data) {
        encodedData += codes[ch];
    }

    return encodedData;
}

string huffmanDecode(const string& encodedData, unordered_map<char, string>& codes) {
    unordered_map<string, char> reversedCodes;
    for (const auto& pair : codes) {
        reversedCodes[pair.second] = pair.first;
    }

    string currentCode;
    string decodedData;

    for (char bit : encodedData) {
        currentCode += bit;
        if (reversedCodes.find(currentCode) != reversedCodes.end()) {
            decodedData += reversedCodes[currentCode];
            currentCode = "";
        }
    }

    return decodedData;
}

int main() {
    // Example usage
    string data = "hello world";
    string encodedData = huffmanEncode(data);

    unordered_map<char, string> huffmanCodes;
    buildHuffmanCodes(buildHuffmanTree(data), "", huffmanCodes);

    string decodedData = huffmanDecode(encodedData, huffmanCodes);

    cout << "Original data: " << data << endl;
    cout << "Encoded data: " << encodedData << endl;
    cout << "Decoded data: " << decodedData << endl;

    return 0;
}

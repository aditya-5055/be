#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

// Node of Huffman Tree
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = NULL;
    }
};

// Comparator for Min Heap
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Function to print Huffman Codes
void printCodes(Node* root, string code) {

    if (root == NULL)
        return;

    // If it is a leaf node, print the character and code
    if (root->left == NULL && root->right == NULL) {
        cout << root->ch << " : " << code << endl;
    }

    // Left = 0, Right = 1
    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

int main() {
    string text;

    cout << "Enter text: ";
    getline(cin, text);

    // Count frequency of each character
    unordered_map<char, int> freq;

    for (char ch : text) {
        freq[ch]++;
    }

    // Create Min Heap
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Insert each character into Min Heap
    for (auto x : freq) {
        pq.push(new Node(x.first, x.second));
    }

    // Build Huffman Tree
    while (pq.size() > 1) {

        // Get two nodes with minimum frequency
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        // Create a new node
        Node* newNode = new Node('$', left->freq + right->freq);

        newNode->left = left;
        newNode->right = right;

        // Insert new node back into heap
        pq.push(newNode);
    }

    // Get root of Huffman Tree
    Node* root = pq.top();

    cout << "\nHuffman Codes:\n";

    // Print codes
    printCodes(root, "");

    return 0;
}

// tc=n log n
// sc=n




/*
. What is Huffman Coding?
Huffman Coding is a Greedy Algorithm used for lossless data compression.

It assigns:
- Shorter binary codes to characters that appear more frequently.
- Longer binary codes to characters that appear less frequently.
Example:

If the character A appears 10 times and B appears 2 times, A should generally get a shorter code than B.

The main aim is to reduce the total number of bits required to store data.
2. Understand your code step by step
Step 1: Header files
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;


- iostream: For input and output.
- queue: For implementing the priority queue (Min Heap).
- unordered_map: For storing the frequency of each character.
Step 2: Create a Node
struct Node {
    char ch;
    int freq;
    Node *left, *right;


Each node of the Huffman Tree contains:
- ch: Character.
- freq: Frequency of that character.
- left: Pointer to the left child.
- right: Pointer to the right child.
Node(char c, int f) {
    ch = c;
    freq = f;
    left = right = NULL;
}


This is a constructor. It initializes the character and frequency, and sets both child pointers to NULL.
Step 3: Comparator for Min Heap
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};


This comparator makes the priority queue work as a Min Heap.

The node with the smallest frequency gets the highest priority and comes out first.
Step 4: Print Huffman Codes
void printCodes(Node* root, string code) {


This function traverses the Huffman Tree and prints the binary code of each character.
if (root == NULL)
    return;


If the current node is NULL, stop recursion.
if (root->left == NULL && root->right == NULL) {
    cout << root->ch << " : " << code << endl;
}


This checks whether the current node is a leaf node.

A leaf node contains the actual character, so we print its Huffman code.
printCodes(root->left, code + "0");
printCodes(root->right, code + "1");


- Moving left adds 0.
- Moving right adds 1.
Step 5: Take input
string text;
cout << "Enter text: ";
getline(cin, text);


Takes a complete line of text from the user, including spaces.
Step 6: Count character frequency
unordered_map<char, int> freq;

for (char ch : text) {
    freq[ch]++;
}


This counts how many times each character appears.

Example:

Input:
banana


Frequency:
Character	Frequency
b	1
a	3
n	2

Step 7: Create Min Heap
priority_queue<Node*, vector<Node*>, Compare> pq;


Creates a priority queue that stores Node pointers and uses our Compare function to arrange them by frequency.
for (auto x : freq) {
    pq.push(new Node(x.first, x.second));
}


Creates a new node for each character and inserts it into the Min Heap.
- x.first = Character.
- x.second = Frequency.
Step 8: Build Huffman Tree
while (pq.size() > 1) {


Continue until only one node remains in the priority queue.
Node* left = pq.top();
pq.pop();

Node* right = pq.top();
pq.pop();


Remove the two nodes with the smallest frequencies.
Node* newNode = new Node('$', left->freq + right->freq);


Create a new internal node.
- $ represents an internal node, not an actual input character.
- Its frequency is the sum of both child frequencies.
newNode->left = left;
newNode->right = right;


Connect the two removed nodes as left and right children.
pq.push(newNode);


Insert the new combined node back into the Min Heap.

Repeat this process until one node remains.
Step 9: Get root and print codes
Node* root = pq.top();
printCodes(root, "");


The remaining node is the root of the Huffman Tree.

We start traversal with an empty string. The function builds the code by adding 0 and 1 while traversing.
3. Example of Huffman Tree
Suppose input is:
banana


Frequencies:
b = 1
a = 3
n = 2


The algorithm combines the two smallest frequencies:
1. Combine b(1) and n(2) → New node (3).
2. Combine a(3) and new node (3) → Root (6).
One possible tree:
          (6)
         /   \
      a(3)   (3)
             / \
          b(1) n(2)


Codes:
Character	Huffman Code
a	0
b	10
n	11

Note: Different valid codes may be generated when frequencies are equal because the priority queue does not guarantee a fixed order for ties.
4. Time and Space Complexity
Time Complexity:

Let:
- L = Length of input text.
- K = Number of distinct characters.
Operation	Complexity
Count frequencies	O(L) average
Insert nodes into Min Heap	O(K log K)
Build Huffman Tree	O(K log K)
Print codes	O(K)

Total:
\[
O(L+K\log K)
\]

If we consider only K distinct characters, the tree-building complexity is O(K log K).

Space Complexity:
\[
O(K)
\]

For the frequency map, Min Heap and Huffman Tree. The recursion stack can also take O(K) space in the worst case.

5. Important Huffman Coding Viva Questions
Q1. What is Huffman Coding?

It is a greedy algorithm used for lossless data compression.

Q2. Which algorithm technique does Huffman Coding use?

Greedy Algorithm.

Q3. Why is it called a Greedy Algorithm?

Because it always selects the two nodes with the smallest frequencies.

Q4. What is lossless compression?

It reduces data size without losing the original information.

Q5. What is a Huffman Tree?

It is a binary tree used to generate Huffman codes.

Q6. What is a leaf node?

A node that does not have any left or right child.

Q7. What is an internal node?

A node that has child nodes.

Q8. Why do we use Min Heap?

To quickly get the two nodes with the smallest frequencies.

Q9. What is a priority queue?

It is a data structure that gives priority to elements based on their priority values.

Q10. Why do we use a comparator?

To arrange nodes according to their frequencies in Min Heap order.

Q11. Why do we assign 0 to the left and 1 to the right?

To generate binary codes while traversing the tree. These choices can also be reversed.

Q12. What does $ represent in your code?

It represents an internal node that combines two frequencies. It is not an actual input character.

Q13. Why do we use recursion in printCodes()?

To traverse the left and right subtrees and generate codes.

Q14. What is a prefix-free code?

A code in which no character's code is the prefix of another character's code.

Q15. Why is prefix-free coding important?

It allows us to decode compressed data without confusion.

Q16. What happens when two characters have the same frequency?

Either can be selected first. Both choices can produce valid Huffman codes.

Q17. What is the time complexity?

O(L + K log K), where L is input length and K is the number of distinct characters.

Q18. What is the space complexity?

O(K), excluding the input string.

Q19. What happens if the input contains only one unique character?

The tree contains only one node, and this code prints an empty Huffman code. In practical implementations, we usually assign it code 0.

Q20. What are the applications of Huffman Coding?
- File compression
- ZIP compression
- JPEG encoding
- Data transmission

6. Most Important 10 Questions to Remember
1. What is Huffman Coding?
2. Why is it a Greedy Algorithm?
3. Why do we use Min Heap?
4. What is a Huffman Tree?
5. What is a leaf node?
6. What is prefix-free coding?
7. Why do we assign 0 to left and 1 to right?
8. What is the purpose of the comparator?
9. Explain how the two minimum-frequency nodes are combined.
10. What are the time and space complexities?
Most important thing: In your viva, be ready to explain how you select the two minimum-frequency nodes, combine them, and repeat until the Huffman Tree is built.
*/
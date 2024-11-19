#include <iostream>
#include <queue>

using namespace std;

struct Node
{
    int key;
    Node *pLeft;
    Node *pRight;
};

Node *createNode(int data)
{
    Node *newNode = new Node;
    newNode->key = data;
    newNode->pLeft = nullptr;
    newNode->pRight = nullptr;

    return newNode;
}

void Insert(Node *&pRoot, int x)
{
    if (pRoot == nullptr)
    {
        pRoot = createNode(x);
        return;
    }

    if (x < pRoot->key)
        Insert(pRoot->pLeft, x);
    else
        Insert(pRoot->pRight, x);
}

void NLR(Node *pRoot) 
{
    if (pRoot == nullptr)
        return;
    
    cout << pRoot->key << " ";
    NLR(pRoot->pLeft);
    NLR(pRoot->pRight);
}

void LNR(Node *pRoot)
{
    if (pRoot == nullptr)
        return;

    LNR(pRoot->pLeft);
    cout << pRoot->key << " ";
    LNR(pRoot->pRight);
}

void LRN(Node *pRoot)
{
    if (pRoot == nullptr)
        return;

    LRN(pRoot->pRight);
    LRN(pRoot->pLeft);
    cout << pRoot->key << " ";
}

void levelOrder(Node *pRoot)
{
    if (pRoot == nullptr)
        return;

    queue<Node*> q;
    q.push(pRoot);

    while (!q.empty())
    {
        Node *tmp = q.front();
        cout << tmp->key << " ";

        if (tmp->pLeft != nullptr)
            q.push(tmp->pLeft);

        if (tmp->pRight != nullptr)
            q.push(tmp->pRight);

        q.pop();
    }
}

int Height(Node *pRoot)
{
    if (pRoot == nullptr)
        return 0;

    return 1 + max(Height(pRoot->pLeft), Height(pRoot->pRight));
}

int countNode(Node *pRoot)
{
    if (pRoot == nullptr)
        return 0;
    
    return 1 + countNode(pRoot->pLeft) + countNode(pRoot->pRight);
}

int sumNode(Node *pRoot)
{
    if (pRoot == nullptr)
        return 0;
    
    return pRoot->key + sumNode(pRoot->pLeft) + sumNode(pRoot->pRight);
}

Node *Search(Node *pRoot, int x)
{
    if (pRoot == nullptr)
        return nullptr;

    if (pRoot->key == x)
        return pRoot;
    
    if (x < pRoot->key)
        return Search(pRoot->pLeft, x);
    else
        return Search(pRoot->pRight, x);
}

void Remove(Node *&pRoot, int x)
{
    if (pRoot == nullptr)
        return;

    if (x < pRoot->key)
        Remove(pRoot->pLeft, x);
    else if (x > pRoot->key)
        Remove(pRoot->pRight, x);
    else
    {
        if (pRoot->pLeft == nullptr && pRoot->pRight == nullptr)
        {
            delete pRoot;
            pRoot = nullptr;
            return;
        }

        if (pRoot->pLeft != nullptr && pRoot->pRight == nullptr)
        {
            Node *del = pRoot;
            pRoot = pRoot->pLeft;
            delete del;
            return;
        }

        if (pRoot->pLeft == nullptr && pRoot->pRight != nullptr)
        {
            Node *del = pRoot;
            pRoot = pRoot->pRight;
            delete del;
            return;
        }

        Node *temp = pRoot->pRight;
        while (temp->pLeft != nullptr)
            temp = temp->pLeft;
        
        pRoot->key = temp->key;
        Remove(pRoot->pRight, temp->key);
    }
}

Node *createBST(int a[], int n)
{
    Node *newBST = createNode(a[0]);

    for (int i = 1; i < n; i++)
        Insert(newBST, a[i]);

    return newBST;
}

void removeBST(Node *&pRoot)
{
    if (pRoot == nullptr)
        return;

    removeBST(pRoot->pLeft);
    removeBST(pRoot->pRight);

    delete pRoot;
    pRoot = nullptr;
}

int nodeHeight(Node *pRoot, int x)
{
    if (pRoot == nullptr)
        return 0;

    if (pRoot->key == x)
        return Height(pRoot);

    if (x < pRoot->key)
        return nodeHeight(pRoot->pLeft, x);
    else
        return nodeHeight(pRoot->pRight, x);
}

int nodeLevel(Node *pRoot, Node *pNode, int level = 1)
{
    if (pRoot == nullptr)
        return -1;
    
    if (pRoot->key == pNode->key)
        return level;
    
    if (pNode->key < pRoot->key)
        return nodeLevel(pRoot->pLeft, pNode, level + 1);
    
    return nodeLevel(pRoot->pRight, pNode, level + 1);
}

int countLeaf(Node *pRoot)
{
    if (pRoot == nullptr)
        return 0;

    if (pRoot->pLeft == nullptr && pRoot->pRight == nullptr)
        return 1;
    
    return countLeaf(pRoot->pLeft) + countLeaf(pRoot->pRight);
}

int countLess(Node *pRoot, int x)
{
    if (pRoot == nullptr)
        return 0;
    
    if (x > pRoot->key)
        return 1 + countLess(pRoot->pLeft, x) + countLess(pRoot->pRight, x);
    else
        return countLess(pRoot->pLeft, x) + countLess(pRoot->pRight, x);
}

int countGreater(Node *pRoot, int x)
{
    if (pRoot == nullptr)
        return 0;
    
    if (x < pRoot->key)
        return 1 + countGreater(pRoot->pLeft, x) + countGreater(pRoot->pRight, x);
    else
        return countGreater(pRoot->pLeft, x) + countGreater(pRoot->pRight, x);
}

int findMax(Node *pRoot)
{
    if (pRoot == nullptr)
        return INT_MIN;
    
    return max(pRoot->key, max(findMax(pRoot->pLeft), findMax(pRoot->pRight)));
}

int findMin(Node *pRoot)
{
    if (pRoot == nullptr)
        return INT_MAX;
    
    return min(pRoot->key, min(findMin(pRoot->pLeft), findMin(pRoot->pRight)));
}

bool isBST(Node *pRoot)
{
    if (pRoot == nullptr)
        return true;
    
    if (pRoot->pLeft != nullptr && findMax(pRoot->pLeft) > pRoot->key)
        return false;
    
    if (pRoot->pRight != nullptr && findMin(pRoot->pRight) < pRoot->key)
        return false;

    return isBST(pRoot->pLeft) && isBST(pRoot->pRight);

}


bool isFullBST(Node *pRoot)
{
    if (pRoot == nullptr)
        return true;

    if ((pRoot->pLeft == nullptr && pRoot->pRight != nullptr) || (pRoot->pLeft != nullptr && pRoot->pRight == nullptr))
        return false;
    
    if (isBST(pRoot) == false)
        return false;

    return isFullBST(pRoot->pLeft) && isFullBST(pRoot->pRight);
    
}

void inorderTraversal(Node* pRoot, vector<int>& inorderArr) {
    if (pRoot == nullptr) {
        return;
    }
  
    inorderTraversal(pRoot->pLeft, inorderArr);  
    inorderArr.push_back(pRoot->key);          
    inorderTraversal(pRoot->pRight, inorderArr); 
}

void preorderFill(Node* pRoot, vector<int>& inorderArr, int& index) {
    if (pRoot == nullptr) {
        return;
    }

    // Copy the next element from the inorder array
    pRoot->key = inorderArr[index++];

    // Fill pLeft and pRight subtree
    preorderFill(pRoot->pLeft, inorderArr, index);  
    preorderFill(pRoot->pRight, inorderArr, index);
}

// Function to convert BST to Min Heap
void convertBSTtoMinHeap(Node* pRoot) {
  
    vector<int> inorderArr;

    inorderTraversal(pRoot, inorderArr);

    int index = 0;

    preorderFill(pRoot, inorderArr, index);
}

int main()
{
    int a[] = {50, 30, 70, 20, 40, 60, 80};
    Node *BST = createBST(a, sizeof(a) / sizeof(a[0]));
    // Node *BST = createNode(5);
    // Insert(BST, 3);
    // Insert(BST, 1);
    // Insert(BST, 10);
    // Insert(BST, 6);
    // Insert(BST, 30);
    // Insert(BST, 9);
    // Insert(BST, -10);

    LNR(BST);
    cout << endl;
    levelOrder(BST);

    cout << "\nHeight: " << Height(BST) << endl;

    cout << "Number of Node: " << countNode(BST) << endl;

    cout << "Sum of key Node: " << sumNode(BST) << endl;

    cout << "Search: " << Search(BST, 9) << endl;

    // Remove(BST, 5);

    // levelOrder(BST);

    // removeBST(BST);

    // cout << endl << "After destroy tree: " << endl;

    // levelOrder(BST);
    Node *t = createNode(40);

    cout << "\n height of 40: " << nodeHeight(BST, 40) << endl;
    cout << "\n level of 40: " << nodeLevel(BST, t) << endl;

    cout << "Leaf: " << countLeaf(BST) << endl;

    cout << "Count less: " << countLess(BST, 10) << endl;

    cout << "Count greater: " << countGreater(BST, 10) << endl;

    cout << "is BST: " << isBST(BST) << endl;

    return 0;
}
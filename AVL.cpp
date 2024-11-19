//
// Template cho Homework 2 - AVL
//
// Miêu tả homework:
// Trong Homework 2, sinh viên sẽ cài đặt lại cây AVL cùng một số thao tác cơ bản trên cây AVL
// i.e. chèn node, xóa node, duyệt cây, ..etc.
//
// Cách thức chấm điểm:
// Bài làm sẽ được chấm trên nhiều testcase, mỗi testcase là một tập tin .txt gồm 3 dòng: 
//
// Ví dụ:
//
// 10 3
// 3 4 2 7 6 8 19 22 1 9
// 2 19 1
//
// Trong đó
// - Dòng đầu tiên gồm 2 số nguyên dương n and k:
//    - n: tổng số node của cây
//    - k: tổng số node sẽ bị xóa khỏi cây.
//
// - Dòng thứ 2 gồm n số nguyên dương phân biệt bởi dấu khoảng trắng -- giá trị các node chèn vào cây.
// - Dòng thứ 3 gồm k số nguyên dương phân biệt bởi dấu khoảng trắng -- giá trị các node được xóa khỏi cây.
//
// Ví dụ: input_sample.txt
//
// Hướng dẫn:
// 1. Điền code vào các mục <// TODO: YOUR CODE HERE>.
// 2. Không nên chỉnh sửa các đoạn code trong mục <// DO NOT MODIFY CODE INSIDE THIS ZONE>
//    để tránh trường hợp gây bug cho trình chấm.
// 3. Sinh viên có thể viết thêm hàm, nhưng không được chỉnh sửa các nguyên mẫu hàm/struct đã có.
// 4. Sinh viên có thể chỉnh sửa hàm main() để test, nhưng lưu ý phải restore lại hàm main() ban đầu
//    trước khi nộp bài. 
//
// Have fun!
// Last updated: Jul 24, 2024.
// 

#include<iostream>
#include<cassert>
#include<vector>
#include<queue>

using namespace std;

// ---------------------------------------------------
// DO NOT MODIFY CODE INSIDE THIS ZONE

struct NODE {
    int key;
    NODE* pLeft;
    NODE* pRight;
    int height;
};

// Destroy a tree.
void demolishTree(NODE*& pRoot) {
    if (pRoot == NULL) {
        return;
    }

    demolishTree(pRoot->pLeft);
    demolishTree(pRoot->pRight);
    delete pRoot; pRoot = NULL;
}

// ---------------------------------------------------
// YOUR WORK

NODE* createNode(int data) {
    NODE *newNode = new NODE;

    newNode->key = data;
    newNode->height = 1;
    newNode->pLeft = NULL;
    newNode->pRight = NULL;

    return newNode;
}

int height(NODE* pRoot) {
    if (pRoot == NULL)
        return 0;

    return pRoot->height;
}

int getBalance(NODE *pRoot)
{
    if (pRoot == NULL)
        return 0;
        
    return height(pRoot->pLeft) - height(pRoot->pRight);
}

void rotateLeft(NODE *&pRoot)
{
    NODE *temp = pRoot->pRight;
    pRoot->pRight = temp->pLeft;
    temp->pLeft = pRoot;

    pRoot->height = 1 + max(height(pRoot->pLeft), height(pRoot->pRight));
    temp->height = 1 + max(height(temp->pLeft), height(temp->pRight));

    pRoot = temp;
}

void rotateRight(NODE *&pRoot)
{
    NODE *temp = pRoot->pLeft;
    pRoot->pLeft = temp->pRight;
    temp->pRight = pRoot;

    pRoot->height = 1 + max(height(pRoot->pLeft), height(pRoot->pRight));
    temp->height = 1 + max(height(temp->pLeft), height(temp->pRight));
    
    pRoot = temp;
}

void Insert(NODE*& pRoot, int x) {
    if (pRoot == NULL)
    {
        pRoot = createNode(x);
        return;
    }    

    if (x < pRoot->key)
        Insert(pRoot->pLeft, x);
    else if (x > pRoot->key)
        Insert(pRoot->pRight, x);
    else
        return;
    
    pRoot->height = 1 + max(height(pRoot->pLeft), height(pRoot->pRight));
    int balance = getBalance(pRoot);

    if (balance > 1 && getBalance(pRoot->pLeft) >= 0)
        rotateRight(pRoot);

    if (balance > 1 && getBalance(pRoot->pLeft) < 0)
    {
        rotateLeft(pRoot->pLeft);
        rotateRight(pRoot);
    }

    if (balance < -1 && getBalance(pRoot->pRight) <= 0)
        rotateLeft(pRoot);

    if (balance < -1 && getBalance(pRoot->pRight) > 0)
    {
        rotateRight(pRoot->pRight);
        rotateLeft(pRoot);
    }
    
    return;
}

//
// Trong trường hợp xóa node có đủ 2 con, node thay thế sẽ là NODE CON LỚN NHẤT CỦA CÂY CON BÊN TRÁI.
//

void Remove(NODE*& pRoot, int x) {
    if (pRoot == NULL)
        return;

    if (x < pRoot->key)
        Remove(pRoot->pLeft, x);
    else if (x > pRoot->key)
        Remove(pRoot->pRight, x);
    else
    {
        if (pRoot->pLeft == NULL && pRoot->pRight == NULL)
        {
            delete pRoot;
            pRoot = NULL;
            return;
        }

        if (pRoot->pLeft == NULL && pRoot->pRight != NULL)
        {
            NODE *del = pRoot;
            pRoot = pRoot->pRight;
            delete del;
            del = NULL;
            return;
        }

        if (pRoot->pLeft != NULL && pRoot->pRight == NULL)
        {
            NODE *del = pRoot;
            pRoot = pRoot->pLeft;
            delete del;
            del = NULL;
            return;
        }

        NODE *temp = pRoot->pLeft;
        while (temp->pRight != NULL)
            temp = temp->pRight;

        pRoot->key = temp->key;
        Remove(pRoot->pLeft, temp->key);
    }

    // rebalance
    if (pRoot == NULL)
        return;

    pRoot->height = 1 + max(height(pRoot->pLeft), height(pRoot->pRight));
    int balance = getBalance(pRoot);

    if (balance > 1 && getBalance(pRoot->pLeft) >= 0)
        rotateRight(pRoot);

    if (balance > 1 && getBalance(pRoot->pLeft) < 0)
    {
        rotateLeft(pRoot->pLeft);
        rotateRight(pRoot);
    }

    if (balance < -1 && getBalance(pRoot->pRight) <= 0)
        rotateLeft(pRoot);

    if (balance < -1 && getBalance(pRoot->pRight) > 0)
    {
        rotateRight(pRoot->pRight);
        rotateLeft(pRoot);
    }
}

bool isAVL(NODE* pRoot) {
    if (pRoot == NULL)
        return true;
    
    int balance = getBalance(pRoot);

    if (balance < -1 || balance > 1)
        return false;

    return isAVL(pRoot->pLeft) && isAVL(pRoot->pRight);
}

//
// Với các hàm duyệt cây, sinh viên in giá trị các node cách nhau bởi dấu khoảng trắng,
// không in thêm dấu xuống dòng.
//
// VD: 1 2 3 4 5 6

void LRN(NODE* pRoot) {
    if (pRoot == NULL)
        return;
    
    LRN(pRoot->pLeft);
    LRN(pRoot->pRight);
    cout << pRoot->key << " ";
}

void NLR(NODE* pRoot) {
    if (pRoot == NULL)
        return;

    cout << pRoot->key << " ";
    NLR(pRoot->pLeft);
    NLR(pRoot->pRight);
}

void LNR(NODE* pRoot) {
    if (pRoot == NULL)
        return;

    LNR(pRoot->pLeft);
    cout << pRoot->key << " ";
    LNR(pRoot->pRight);
}

void LevelOrder(NODE* pRoot) {
    if (pRoot == NULL)
        return;

    queue <NODE *> q;
    q.push(pRoot);

    while (q.empty() == false)
    {
        NODE *temp = q.front();
        q.pop();
        cout << temp->key << " ";

        if (temp->pLeft != NULL)
            q.push(temp->pLeft);
            
        if (temp->pRight != NULL)
            q.push(temp->pRight);
    }
}

// ---------------------------------------------------
// DO NOT MODIFY CODE INSIDE THIS ZONE

// Create the tree from a given array (std::vector)
NODE* createTreeFromArray(const vector<int>& arr) {
    NODE* pRoot = NULL;
    for (int i = 0; i < arr.size(); ++i) {
        Insert(pRoot, arr[i]);
    }
    return pRoot;
}

// ---------------------------------------------------

int main() {
    // All testcases will be load from files and printed into file.
    freopen("input.txt", "r+", stdin);
    freopen("output.txt", "w+", stdout);

    int n, k; cin >> n >> k;
    vector<int> arr(n); for (auto& i : arr) cin >> i;
    vector<int> del(k); for (auto& i : del) cin >> i;

    NODE* pRoot = createTreeFromArray(arr);

    assert(isAVL(pRoot));

    // LRN order
    LRN(pRoot); cout << "\n";
    LNR(pRoot); cout << "\n";
    NLR(pRoot); cout << "\n"; 

    // Print the tree height
    cout << height(pRoot) << "\n";

    // Removing nodes 
    for (const auto i : del) {
        Remove(pRoot, i);
    }

    // Print the tree after removal
    LRN(pRoot); cout << "\n";
    LNR(pRoot); cout << "\n";
    NLR(pRoot); cout << "\n";	

    // Print the tree height after removal
    cout << height(pRoot) << "\n";
    

    demolishTree(pRoot);
    assert(pRoot == NULL);

    return 0;
}
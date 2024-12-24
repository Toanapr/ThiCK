#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <stack>

using namespace std;

const string fileName1 = "graph1.txt";
const string fileName2 = "graph2.txt";

vector<vector<int>> printAdjacencyList(const string &fileName)
{
    int n = 0;
    fstream input;
    input.open(fileName, ios::in);

    input >> n;
    vector<vector<int>> matrix(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int x;
            input >> x;

            matrix[i].push_back(x);
        }

    input.close();

    return matrix;
}

void printAdjacenyMatrix(const string &fileName)
{
    fstream input;
    int n = 0;
    string line = "";

    input.open(fileName, ios::in);

    input >> n;
    cout << n << endl;
    getline(input, line);

    int **matrix = new int *[n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        getline(input, line);

        if (line != "")
            for (int j = 0; j < line.size(); j++)
                if (line[j] != ' ')
                    matrix[i][line[j] - '0'] = 1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }

    for (int i = 0; i < n; i++)
        delete[] matrix[i];

    input.close();
}

bool isUndirectedGraph(vector<vector<int>> matrix)
{
    int n = matrix.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
            if ((matrix[i][j] != matrix[j][i]))
                return false;
    }

    return true;
}

int countEdge(vector<vector<int>> matrix)
{
    int n = matrix.size();
    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] == 1)
                count++;

    if (isUndirectedGraph(matrix))
        return count / 2;
    else
        return count;
}

int deg(vector<vector<int>> matrix, bool isUndirectedGraph, int vertex)
{
    int n = matrix.size();

    if (isUndirectedGraph)
    {
        int deg = 0;
        for (auto x : matrix[vertex])
        {
            if (x != 0)
                deg++;
        }

        return deg;
    }
    else
    {
        int inDeg = 0;
        int outDeg = 0;

        for (auto x : matrix[vertex])
            if (x != 0)
                outDeg++;

        for (auto x : matrix)
            if (x[vertex] != 0)
                inDeg++;

        return inDeg - outDeg;
    }
}

vector<int> isolatedVertex(vector<vector<int>> matrix)
{
    vector<int> res;
    for (int i = 0; i < matrix.size(); i++)
        if (deg(matrix, true, i) == 0)
            res.push_back(i);

    return res;
}

vector<int> leafVertex(vector<vector<int>> matrix)
{
    vector<int> res;
    for (int i = 0; i < matrix.size(); i++)
        if (deg(matrix, true, i) == 1)
            res.push_back(i);

    return res;
}

bool isCompleteGraph(vector<vector<int>> matrix) // đồ thị đủ
{
    int n = matrix.size();

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && matrix[i][j] == 0)
                return false;

    return true;
}

bool isCercularGraph(vector<vector<int>> matrix) // đồ thị vòng
{

    return true;
}

bool isBipartiteGraph(vector<vector<int>> matrix) // đồ thị hai phía
{

    return true;
}

bool isCompleteBipartiteGraph(vector<vector<int>> matrix) // đồ thị hai phía đầy đủ
{

    return true;
}

void DFS(vector<vector<int>> matrix, int startVertex, vector<bool> &visit, vector<pair<int, int>> &spanningTree)
{
    cout << startVertex << " ";
    visit[startVertex] = true;

    for (int i = 0; i < matrix.size(); i++)
    {
        if (visit[i] == false && matrix[startVertex][i] == 1)
        {
            spanningTree.push_back({startVertex, i});
            DFS(matrix, i, visit, spanningTree);
        }
    }
}

void DFS(vector<vector<int>> matrix, int startVertex, vector<bool> &visit, int &vertices, int &egdes)
{
    visit[startVertex] = true;
    vertices++;

    for (int i = 0; i < matrix.size(); i++)
    {
        if (matrix[startVertex][i] == 1)
        {
            egdes++;
            if (visit[i] == false)
            {
                DFS(matrix, i, visit, vertices, egdes);
            }
        }
    }
}
void countComponent(vector<vector<int>> matrix)
{
    vector<bool> visit(matrix.size(), false);
    int numComponent = 0;
    int numTree = 0;

    for (int i = 0; i < matrix.size(); i++)
        if (visit[i] == false)
        {
            numComponent++;

            int vertices = 0;
            int edges = 0;
            DFS(matrix, i, visit, vertices, edges);

            if (vertices - 1 == edges / 2)
                numTree++;
        }

    cout << numTree << " " << numComponent;
}
void BFS(const vector<vector<int>> &matrix, int startVertex, vector<bool> &visit, vector<pair<int, int>> &spanningTree)
{
    queue<int> q;

    visit[startVertex] = true;
    q.push(startVertex);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        cout << u << " ";

        for (int v = 0; v < matrix.size(); v++)
        {
            if (matrix[u][v] == 1 && visit[v] == false)
            {
                visit[v] = true;
                q.push(v);
                spanningTree.push_back({u, v});
            }
        }
    }
}

void findEulerCycle(const vector<vector<int>> &matrix, int startVertex, vector<int> &eulerCycle)
{
    vector<vector<int>> adjMatrix = matrix; // Sao chép ma trận kề
    stack<int> currentPath;
    currentPath.push(startVertex);

    while (!currentPath.empty())
    {
        int u = currentPath.top();
        bool hasEdge = false;

        // Tìm cạnh từ đỉnh u
        for (int v = 0; v < adjMatrix.size(); v++)
        {
            if (adjMatrix[u][v] > 0)
            {
                currentPath.push(v); // Đẩy đỉnh v vào stack
                adjMatrix[u][v]--;   // Loại bỏ cạnh u-v
                adjMatrix[v][u]--;   // Loại bỏ cạnh v-u (vì đồ thị vô hướng)
                hasEdge = true;
                break;
            }
        }

        if (!hasEdge)
        {
            eulerCycle.push_back(u); // Đưa đỉnh vào chu trình Euler
            currentPath.pop();
        }
    }
}

bool hasEulerCycle(const vector<vector<int>> &matrix)
{
    // Kiểm tra bậc của mỗi đỉnh
    for (int i = 0; i < matrix.size(); i++)
    {
        int degree = 0;
        for (int j = 0; j < matrix[i].size(); j++)
        {
            degree += matrix[i][j];
        }
        if (degree % 2 != 0)
        {
            return false; // Nếu có đỉnh bậc lẻ, không có chu trình Euler
        }
    }
    return true;
}

vector<vector<int>> getUndirectedFromDirectedGraph(vector<vector<int>> undirectedGraph)
{
    vector<vector<int>> directedGraph(undirectedGraph.size(), vector<int>(undirectedGraph.size(), 0));

    for (int i = 0; i < undirectedGraph.size(); i++)
    {
        for (int j = 0; j < undirectedGraph.size(); j++)
        {
            if (undirectedGraph[i][j] == 1 || undirectedGraph[j][i] == 1)
            {
                directedGraph[i][j] = 1;
                directedGraph[j][i] = 1;
            }
        }
    }

    return directedGraph;
}

vector<vector<int>> getComplementGraph(vector<vector<int>> graph) // đồ thị bù
{
    vector<vector<int>> complementGraph;

    for (int i = 0; i < graph.size(); i++)
    {
        for (int j = 0; j < graph.size(); j++)
        {
            complementGraph[i].push_back(0);
        }
    }

    for (int i = 0; i < graph.size(); i++)
    {
        for (int j = 0; j < graph.size(); j++)
        {
            if (i != j)
                complementGraph[i][j] = 1 - graph[i][j];
        }
    }

    return complementGraph;
}

vector<vector<int>> getTransposeGraph(vector<vector<int>> graph) // đồ thị bù
{
    vector<vector<int>> transposeGraph;

    for (int i = 0; i < graph.size(); i++)
    {
        for (int j = 0; j < graph.size(); j++)
        {
            transposeGraph[i].push_back(0);
        }
    }

    for (int i = 0; i < graph.size(); i++)
    {
        for (int j = 0; j < graph.size(); j++)
        {
            transposeGraph[j][i] = graph[i][j];
        }
    }

    return transposeGraph;
}


//Prim
int minKey(vector<int> key, vector<bool> visit, int n)
{
    int min_index = -1;
    int min = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        if (!visit[i] && key[i] < min)
        {
            min = key[i];
            min_index = i;
        }
    }

    return min_index;
}
#define EDGES_LIST map<pair<int, int>, int>
#define ADJ_MATRIX vector<vector<int>>
EDGES_LIST Prim(const ADJ_MATRIX &graph, int startVertex)
{
    EDGES_LIST res;

    int n = graph.size();
    vector<int> key(n, INT_MAX);
    vector<bool> visit(n, false);

    key[startVertex] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int u = minKey(key, visit, n);

        visit[u] = true;

        for (int v = 0; v < n; v++)
        {
            if (!visit[v] && graph[u][v] != 0 && graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
                res[{u, v}] = graph[u][v];
            }
        }
    }

    return res;
}

// Dijkstra
void printTrace(int end, const vector<int> &trace)
{
    stack<int> s;
    s.push(end);

    int current = end;
    while (trace[current] != -1)
    {
        s.push(trace[current]);
        current = trace[current];
    }

    while (s.size() > 1)
    {
        cout << s.top() << " -> ";
        s.pop();
    }

    cout << s.top();
}

int minDistance(vector<int> dist, vector<bool> visit, int n)
{
    int min = INT_MAX;
    int min_index = -1;

    for (int i = 0; i < n; i++)
        if (!visit[i] && dist[i] < min)
        {
            min = dist[i];
            min_index = i;
        }

    return min_index;
}

int Dijkstra(const ADJ_MATRIX &matrix, int start, int end, vector<int> &trace)
{
    int n = matrix.size();
    vector<int> dist(n, INT_MAX);
    vector<bool> visit(n, false);

    dist[start] = 0;
    trace[start] = -1;

    for (int i = 0; i < n - 1; i++)
    {
        int u = minDistance(dist, visit, n);

        if (u == end)
            break;

        visit[u] = true;

        for (int v = 0; v < n; v++)
        {
            if (!visit[v] && dist[u] != INT_MAX && matrix[u][v] != 0 && dist[u] + matrix[u][v] < dist[v])
            {
                dist[v] = dist[u] + matrix[u][v];
                trace[v] = u;
            }
        }
    }

    return dist[end] == INT_MAX ? -1 : dist[end];
}

// kiểm tra đồ thị hai phía
bool isBipartiteDFS(const vector<vector<int>> &matrix, vector<int> &colors, int vertex, int color)
{
    colors[vertex] = color;

    for (int i = 0; i < matrix.size(); i++)
    {
        if (matrix[vertex][i])
        {
            if (colors[i] == 0)
            {
                if (!isBipartiteDFS(matrix, colors, i, -color))
                    return false;
            }
            else if (colors[i] == color)
                return false;
        }
    }
    return true;
}

bool isBipartite(const vector<vector<int>> &matrix)
{ // kiểm tra đồ thị hai phía
    if (matrix.empty())
        return true;

    int n = matrix.size();
    vector<int> colors(n, 0); // 0: uncolored, 1: color1, -1: color2

    for (int i = 0; i < n; i++)
    {
        if (colors[i] == 0)
        {
            if (!isBipartiteDFS(matrix, colors, i, 1))
                return false;
        }
    }
    return true;
}

// kiểm tra 2 đỉnh có thuộc cùng một thành phần liên thông
void DFSComponent(const vector<vector<int>> &matrix, vector<int> &components, int vertex, int componentId)
{
    components[vertex] = componentId;

    for (int i = 0; i < matrix.size(); i++)
    {
        if (matrix[vertex][i] && components[i] == -1)
        {
            DFSComponent(matrix, components, i, componentId);
        }
    }
}

bool isInSameComponent(const vector<vector<int>> &matrix, int u, int v)
{
    if (u < 0 || v < 0 || u >= matrix.size() || v >= matrix.size())
        return false;

    vector<int> components(matrix.size(), -1);
    int componentId = 0;

    // Mark all components
    for (int i = 0; i < matrix.size(); i++)
    {
        if (components[i] == -1)
        {
            DFSComponent(matrix, components, i, componentId++);
        }
    }

    return components[u] == components[v];
}

void heapify(vector<int>& arr, int n, int i){

    int largest = i;

    int l = 2 * i + 1;

    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr){
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {

        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

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
NODE* createNode(int x)
{
    NODE* newNode = new NODE;
    newNode->key = x;
    newNode->pLeft = NULL;
    newNode->pRight = NULL;
    newNode->height = 1;

    return newNode;
}

int height(NODE* pRoot)
{
    if (pRoot == NULL)
        return 0;

    return pRoot->height;
}

int getBalance(NODE* pRoot)
{
    if (pRoot == NULL)
        return 0;

    return height(pRoot->pLeft) - height(pRoot->pRight);
}

void rotateLeft(NODE*& pRoot)
{
    if (pRoot == NULL)
        return;

    NODE* temp = pRoot->pRight;
    pRoot->pRight = temp->pLeft;
    temp->pLeft = pRoot;

    pRoot->height = 1 + max(height(pRoot->pLeft), height(pRoot->pRight));
    temp->height = 1 + max(height(temp->pLeft), height(temp->pRight));

    pRoot = temp;
}

void rotateRight(NODE*& pRoot)
{
    if (pRoot == NULL)
        return;

    NODE* temp = pRoot->pLeft;
    pRoot->pLeft = temp->pRight;
    temp->pRight = pRoot;

    pRoot->height = 1 + max(height(pRoot->pLeft), height(pRoot->pRight));
    temp->height = 1 + max(height(temp->pLeft), height(temp->pRight));

    pRoot = temp;
}

void balance(NODE*& pRoot)
{
    int bal = getBalance(pRoot);

    if (bal > 1 && getBalance(pRoot->pLeft) >= 0)
        rotateRight(pRoot);

    if (bal > 1 && getBalance(pRoot->pLeft) < 0)
    {
        rotateLeft(pRoot->pLeft);
        rotateRight(pRoot);
    }

    if (bal < -1 && getBalance(pRoot->pRight) <= 0)
        rotateLeft(pRoot);

    if (bal < -1 && getBalance(pRoot->pRight) > 0)
    {
        rotateRight(pRoot->pRight);
        rotateLeft(pRoot);
    }
}

void Insert(NODE*& pRoot, int x)
{
    if (pRoot == NULL)
    {
        pRoot = createNode(x);
        return;
    }

    if (x < pRoot->key)
        Insert(pRoot->pLeft, x);
    else if (x > pRoot->key)
        Insert(pRoot->pRight, x);

    pRoot->height = 1 + max(height(pRoot->pLeft), height(pRoot->pRight));
    balance(pRoot);
}

void Remove(NODE*& pRoot, int x)
{
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
            NODE* de = pRoot;
            pRoot = pRoot->pRight;
            delete de;
            de = NULL;
            return;
        }

        if (pRoot->pLeft != NULL && pRoot->pRight == NULL)
        {
            NODE* de = pRoot;
            pRoot = pRoot->pLeft;
            delete de;
            de = NULL;
            return;
        }

        NODE* temp = pRoot->pLeft;
        while (temp->pRight != NULL)
            temp = temp->pRight;

        pRoot->key = temp->key;
        Remove(pRoot->pLeft, temp->key);
    }

    if (pRoot == NULL)
        return;

    pRoot->height = 1 + max(height(pRoot->pLeft), height(pRoot->pRight));
    balance(pRoot);
}

int main()
{
    // vector<vector<int>> matrix = printAdjacencyList(fileName1);

    // vector<pair<int , int>> spanningTree;
    // vector<bool> visit(matrix.size(), false);

    // DFS(matrix, 0, visit, spanningTree);

    // BFS(matrix, 0, visit, spanningTree);

    // cout << endl;
    // for (auto x : spanningTree)
    //     cout << x.first << " - " << x.second << endl;

    // for (auto i : matrix)
    // {
    //     for (auto j : i)
    //         cout << j << " ";
    //     cout << endl;
    // }

    printAdjacenyMatrix(fileName2);
    return 0;
}

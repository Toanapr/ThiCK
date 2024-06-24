#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *next;
    Node(int _data)
    {
        data = _data;
        next = NULL;
    }
};

struct List
{
    Node *head;
    int size;
    List()
    {
        head = NULL;
        size = 0;
    }
};

void addHead(List &l, int data)
{
    Node *add = new Node(data);

    if (l.head == NULL)
    {
        l.head = add;
        l.size++;
    }
    else
    {
        add->next = l.head;
        l.head = add;
        l.size++;
    }
}

void addTail(List &l, int data)
{
    Node *add = new Node(data);

    if (l.head == NULL)
    {
        l.head = add;
        l.size++;
    }
    else
    {
        Node *temp = l.head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = add;
        l.size++;
    }
}

void addAt(List &l, int data, int index)
{
    if (index < 0 || index > l.size)
    {
        cout << "Index out of range" << endl;
        return;
    }

    if (index == 0)
        addHead(l, data);
    else if (index == l.size)
        addTail(l, data);
    else
    {
        Node *add = new Node(data);
        Node *temp = l.head;
        int cnt = 0;
        while (cnt < index - 1)
        {
            temp = temp->next;
            cnt++;
        }
        add->next = temp->next;
        temp->next = add;
        l.size++;
    }
}

void addAfterValue(List &l, int data, int value)
{
    Node *add = new Node(data);
    Node *temp = l.head;
    while (temp != NULL)
    {
        if (temp->data == value)
        {
            add->next = temp->next;
            temp->next = add;
            l.size++;
        }
        temp = temp->next;
    }
}

void deleteHead(List &l)
{
    if (l.head == NULL)
        return;

    Node *temp = l.head;
    l.head = l.head->next;
    delete temp;
    l.size--;
}

void deleteTail(List &l)
{
    if (l.head == NULL)
        return;
    else if (l.head->next == NULL)
    {
        delete l.head;
        l.head = NULL;
        l.size--;
        return;
    }
    else
    {
        Node *temp = l.head;
        while (temp->next->next != NULL)
            temp = temp->next;

        delete temp->next;
        temp->next = NULL;
        l.size--;
    }
}

void deleteAt(List &l, int index)
{
    if (index < 0 || index >= l.size)
    {
        cout << "Index out of range" << endl;
        return;
    }

    if (index == 0)
        deleteHead(l);
    else if (index == l.size - 1)
        deleteTail(l);
    else
    {
        Node *temp = l.head;
        int cnt = 0;
        while (cnt < index - 1)
        {
            temp = temp->next;
            cnt++;
        }

        Node *del = temp->next;
        temp->next = del->next;
        delete del;
        l.size--;
    }
}

void deleteValue(List &l, int data)
{
    while (l.head != NULL && l.head->data == data)
        deleteHead(l);

    Node *temp = l.head;
    while (temp != NULL && temp->next != NULL)
    {
        if (temp->next->data == data)
        {
            Node *del = temp->next;
            temp->next = del->next;
            delete del;
            l.size--;
        }
        else
            temp = temp->next;
    }
}

Node *reverse(Node *head)
{
    Node *curr = head;
    Node *prev = NULL;
    Node *next = NULL;
    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

void revertByRecursion(Node *&head, Node *curr, Node *prev)
{
    if (curr == NULL)
    {
        head = prev;
        return;
    }

    Node *next = curr->next;
    curr->next = prev;
    revertByRecursion(head, next, curr);
}

bool isPalindrome(Node *head)
{
    if (head == NULL)
        return true;

    Node *fast = head;
    Node *slow = head;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node *head2 = reverse(slow);
    Node *p = head2;
    Node *q = head;
    while (p != NULL && q != NULL)
    {
        if (p->data != q->data)
            return false;
        p = p->next;
        q = q->next;
    }

    head2 = reverse(head2);

    return true;
}
void swap(Node* prev1,  Node* prev2)
{
    Node* curr1 = prev1->next;
    Node* curr2 = prev2->next;
	prev1->next = curr2;
	prev2->next = curr1;
	Node* temp = curr1->next;
	curr1->next = curr2->next;
	curr2->next = temp;
}

void Sort(List& l)
{
	addHead(l, 0);

	Node* temp = l.head;
	for (Node* i = l.head; i != NULL && i->next != NULL; i = i->next)
		for (Node* j = i; j != NULL && j->next != NULL; j = j->next)
		{
			if (i->next->data < j->next->data)
			{
				swap(i, j);
			}
		}

	if (l.head != NULL)
		l.head = l.head->next;
}

void deleteDuplicate(List& l)
{
	Node* i = l.head;
	while (i != NULL && i->next != NULL)
	{
		Node* j = i;
		while (j != NULL && j->next != NULL)
		{
			if (i->data == j->next->data)
			{
				Node* temp = j->next;
				j->next = temp->next;
				delete temp;
				l.size--;
			}
			else
				j = j->next;
		}
		i = i->next;
	}
}

void printList(List l)
{
    Node *temp = l.head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main()
{

    List l;
    addHead(l, 3);
    addHead(l, 3);
    addHead(l, 6);
    addHead(l, 3);
    addHead(l, 8);
    addHead(l, 5);
    addHead(l, 5);
    addHead(l, 5);

    addTail(l, 6);
    addTail(l, 7);
    addTail(l, 8);
    addTail(l, 8);

    printList(l);

    // deleteValue(l, 5);
    // revertByRecursion(l.head, l.head, NULL);

    // printList(l);

    Sort(l);
    // deleteDuplicate(l);
    printList(l);

    return 0;
}
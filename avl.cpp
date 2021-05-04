#include <iostream>
using namespace std;

class Node
{
public:
    int data, height;
    Node *left, *right;

    Node(int data)
    {
        height = 0;
        this->data = data;
        left = right = nullptr;
    }
};

int height(Node *root)
{
    if (!root)
        return -1;
    return root->height;
}

Node *rotateTowardsLeft(Node *root)
{
    Node *newRoot = root->right;
    root->right = newRoot->left;
    root->height = max(height(root->left), height(root->right)) + 1;
    newRoot->left = root;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

Node *rotateTowardsRight(Node *root)
{
    Node *newRoot = root->left;
    root->left = newRoot->right;
    root->height = max(height(root->left), height(root->right)) + 1;
    newRoot->right = root;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

Node *insert(Node *root, int data)
{
    if (!root)
        return new Node(data);

    if (data > root->data)
        root->right = insert(root->right, data);
    else
        root->left = insert(root->left, data);

    int balance = height(root->left) - height(root->right);
    if (balance > 1)
    {
        if (height(root->right->left) > height(root->right->right))
            root->right = rotateTowardsRight(root->right);
        root = rotateTowardsLeft(root);
    }
    else if (balance < -1)
    {
        if (height(root->right->left) > height(root->right->right))
            root->right = rotateTowardsRight(root->right);
        root = rotateTowardsLeft(root);
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    return root;
}

void inorderTraversal(Node *root)
{
    if (!root)
        return;

    inorderTraversal(root->left);
    cout << root->data << " " << root->height << " ";
    inorderTraversal(root->right);
}

void preorderTraversal(Node *root)
{
    if (!root)
        return;

    cout << root->data << " " << root->height << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

//Note : can create nullptr access
int minNodeValueInSubtree(Node *root)
{
    while (root->left)
        root = root->left;

    return root->data;
}

Node *deleteNode(Node *root, int data)
{
    if (!root)
        return nullptr;

    if (root->data == data)
    {
        if (root->left && root->right)
        {
            root->data = minNodeValueInSubtree(root->right);
            root->right = deleteNode(root->right, root->data);
        }
        else if (root->left)
            root = root->left;
        else if (root->right)
            root = root->right;
        else
            return nullptr;
    }
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else
        root->left = deleteNode(root->left, data);

    int balance = height(root->left) - height(root->right);
    if (balance > 1)
    {
        if (height(root->right->left) > height(root->right->right))
            root->right = rotateTowardsRight(root->right);
        root = rotateTowardsLeft(root);
    }
    else if (balance < -1)
    {
        if (height(root->right->left) > height(root->right->right))
            root->right = rotateTowardsRight(root->right);
        root = rotateTowardsLeft(root);
    }

    root->height = max(height(root->left), height(root->right)) + 1;

    return root;
}

// returning pointer so later approaches can have the easiness
// to attach payload with a node
Node *search(Node *root, int key)
{
    if (!root)
        return nullptr;
    if (root->data == key)
        return root;
    if (key > root->data)
        return search(root->right, key);
    return search(root->left, key);
}

//test code
int main(int argc, char const *argv[])
{
    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    Node *root = nullptr;
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    inorderTraversal(root);
    cout << "\n";
    preorderTraversal(root);

    root = deleteNode(root, 2);

    cout << "\n";
    inorderTraversal(root);
    cout << "\n";
    preorderTraversal(root);

    return 0;
}

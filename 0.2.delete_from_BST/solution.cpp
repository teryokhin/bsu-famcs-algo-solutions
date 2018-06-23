#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class BinarySearchTree
{
    struct Node
    {
        int value;
        Node* left;
        Node* right;
        Node(int value): value(value), left(nullptr), right(nullptr) {};
    };

    private:
        Node* root;

        void add(int value, Node* node) {
            if (value < node->value) {
                if (node->left)
                    add(value, node->left);
                else
                    node->left = new Node(value);
            }
            if (value > node->value) {
                if (node->right)
                    add(value, node->right);
                else
                    node->right = new Node(value);
            }
        }

        Node* min(Node* node) {
            if (!node) return node;
            if (node->left)
                return min(node->left);
            return node;
        }

    public:
        BinarySearchTree(): root(nullptr) {}

        void add(int value) {
            if (root)
                add(value, root);
            else
                root = new Node(value);
        }

        string preorderLeft(){
            return preorderLeft(root);
        }


        string preorderLeft(Node* node){
            if (node) {
                 string s = to_string(node->value)+"\n";
                 s += preorderLeft(node->left);
                 s += preorderLeft(node->right);
                 return s;
            }
            else return string();
        }

        void remove(int value){
            root = remove(value, root);
        }

        Node* remove(int value, Node* node){
            if (!node)
                return node;
            if (value < node->value)
                node->left = remove(value, node->left);
            else if (value > node->value)
                node->right = remove(value, node->right);
            else if (node->left && node->right) {
                node->value = min(node->right)->value;
                node->right = remove(node->value, node->right);
            }
            else {
                if (node->left)
                    node = node->left;
                else
                    node = node->right;
            }
            return node;
        }
};


int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int to_remove;
    fin >> to_remove;

    int v;
    BinarySearchTree bst;
    while (fin >> v)
        bst.add(v);

    bst.remove(to_remove);
    fout << bst.preorderLeft();

    return 0;
}

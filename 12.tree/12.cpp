#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>


#define INF 1000000007

using namespace std;

class BinarySearchTree
{
    struct Node
    {
        int value;
        int height;

        int msl;

        int minDeepest;
        int minPreDeepest;

        Node* left;
        Node* right;
        Node(int value): value(value), minDeepest(INF), minPreDeepest(INF), left(nullptr), right(nullptr){};
    };

    private:
        Node* root;
        int max_msl;
        vector<Node*> msl_nodes;
        vector<int> resultSP;

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

        Node* minNode(Node* node) {
            if (!node) return node;
            if (node->left)
                return minNode(node->left);
            return node;
        }


        int minKeyWithDepth(Node* node, int depth, bool mustHaveChild=false) {
            if ((depth == 0 && (mustHaveChild && node->height!=0)) || (depth == 0 && node->height==0 && !mustHaveChild))
                    return node->value;
            else {
                int n1 = INF, n2 = INF;
                if (node->left)
                    n1 = minKeyWithDepth(node->left, depth-1, mustHaveChild);
                if (node->right)
                    n2 = minKeyWithDepth(node->right, depth-1, mustHaveChild);
                return min(n1, n2);
            }
        }

    public:
        BinarySearchTree(): root(nullptr), max_msl(-1){
        }


        void add(int value) {
            if (root)
                add(value, root);
            else
                root = new Node(value);

        }

        string preorderLeft(){
            return preorderLeft(root);
        }

        int setHeights(){
            return setHeights(root);
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

        int setHeights(Node* node){
            if (node) {
                int h1 = 0, h2 = 0, childC = 0;
                if (node->left) { h1 = setHeights(node->left); childC+=1; }
                if (node->right) { h2 = setHeights(node->right); childC+=1; }

                node->msl = h1+h2;
                if (node->msl > max_msl) {
                    max_msl = node->msl;
                    msl_nodes.clear();
                    msl_nodes.push_back(node);
                }
                else if (node->msl == max_msl)
                    msl_nodes.push_back(node);

                if (childC>0)
                    return node->height = max(h1,h2) + 1;
                else
                    return node->height = 0;
            } else return 0;
        }

        void savePathToResult(Node* from, int key) {
            if (from) resultSP.push_back(from->value);
            if (key < from->value)
                savePathToResult(from->left, key);
            else if (key > from->value)
                savePathToResult(from->right, key);
        }

        void maxSpecialSemipathRoot() {
            this->setHeights();
            resultSP.clear();

            if (max_msl==0) return;

            int min_key_sum = INF+1;
            Node* msl_node = nullptr;
            for(auto node: msl_nodes){
                if(node->left && node->right) {
                    node->left->minDeepest = minKeyWithDepth(node->left, node->left->height);
                    if (node->left->height-1 >= 0)
                        node->left->minPreDeepest = minKeyWithDepth(node->left, node->left->height-1, true);
                    else node->left->minPreDeepest = node->value;
                    node->right->minDeepest = minKeyWithDepth(node->right, node->right->height);
                    if (node->right->height-1 >= 0)
                        node->right->minPreDeepest = minKeyWithDepth(node->right, node->right->height-1, true);
                    else node->right->minPreDeepest = node->value;

                    int cur_min_key_sum = min((node->left->minDeepest+node->right->minPreDeepest), (node->left->minPreDeepest+node->right->minDeepest));
                    if (cur_min_key_sum < min_key_sum || (cur_min_key_sum == min_key_sum && node->value < msl_node->value)) {
                        min_key_sum = cur_min_key_sum;
                        msl_node = node;
                    }
                }
            }

            if ((max_msl == root->msl && (!root->left || !root->right))) {
                int deepestMinNode = minKeyWithDepth(root, root->height);
                if (deepestMinNode+root->value < min_key_sum || (deepestMinNode+root->value == min_key_sum && root->value<msl_node->value)) {
                    savePathToResult(root, deepestMinNode);
                    if (resultSP.size()%2 && resultSP.size()!=1) {
                        sort(resultSP.begin(), resultSP.end());
                        this->remove(resultSP[resultSP.size()/2]);
                    }
                    return;
                }
            }

            if ((msl_node->left->minDeepest+msl_node->right->minPreDeepest) < (msl_node->left->minPreDeepest+msl_node->right->minDeepest)){
                resultSP.push_back(msl_node->value);
                savePathToResult(msl_node->left, msl_node->left->minDeepest);
                if (msl_node->right->minPreDeepest != msl_node->value) savePathToResult(msl_node->right, msl_node->right->minPreDeepest);
            }
            else if ((msl_node->left->minDeepest+msl_node->right->minPreDeepest) > (msl_node->left->minPreDeepest+msl_node->right->minDeepest)){
                resultSP.push_back(msl_node->value);
                if (msl_node->left->minPreDeepest != msl_node->value) savePathToResult(msl_node->left, msl_node->left->minPreDeepest);
                savePathToResult(msl_node->right, msl_node->right->minDeepest);
            }
            else {
                int m1 = -1, m2 = -2;
                resultSP.push_back(msl_node->value);
                savePathToResult(msl_node->left, msl_node->left->minDeepest);
                if (msl_node->right->minPreDeepest != msl_node->value) savePathToResult(msl_node->right, msl_node->right->minPreDeepest);
                if (resultSP.size()%2) {
                    sort(resultSP.begin(), resultSP.end());
                    m1 = resultSP[resultSP.size()/2];
                }
                resultSP.clear();
                resultSP.push_back(msl_node->value);
                if (msl_node->left->minPreDeepest != msl_node->value) savePathToResult(msl_node->left, msl_node->left->minPreDeepest);
                savePathToResult(msl_node->right, msl_node->right->minDeepest);
                if (resultSP.size()%2) {
                    sort(resultSP.begin(), resultSP.end());
                    m2 = resultSP[resultSP.size()/2];
                }
                if (m1 == m2)
                    this->remove(m1);
                return;
            }
            if (resultSP.size()%2) {
                sort(resultSP.begin(), resultSP.end());
                //for (int a: resultSP)
                //    cerr << a << " ";
                this->remove(resultSP[resultSP.size()/2]);
            }

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
                node->value = minNode(node->right)->value;
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
    ifstream fin("tst.in");
    ofstream fout("tst.out");

    int v;
    BinarySearchTree bst;
    while (fin >> v)
        bst.add(v);

    bst.maxSpecialSemipathRoot();
    fout << bst.preorderLeft();

    return 0;
}

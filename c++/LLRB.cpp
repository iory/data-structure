#include <algorithm>
#include <bitset>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef vector<int> vec;
typedef vector<vec> mat;
static const double EPS = 1e-9;
static const double PI = acos(-1.0);

template <class T>
class LLRB{
public:

    static const bool RED  = true;
    static const bool BLACK= false;

    class Node{
    public:
        bool color;
        T key;
        Node *left;
        Node *right;

        Node(bool _color,T _key):color(_color),key(_key){
            left = NULL;
            right= NULL;
        }
    };

    LLRB(){
        root = NULL;
    }


    Node* root;

    bool isRed(Node *h){return h!=NULL && h->color == RED;}
    bool isBlack(Node *h){return h != NULL && h->color == BLACK;}

    Node* rotate_left(Node *h){
        Node *x = h->right;
        h->right = x->left;
        x->left = h;
        x->color = h->color;
        h->color = RED;
        return x;
    }

    Node* rotate_right(Node *h){
        Node *x = h->left;
        h->left = x->right;
        x->right = h;
        x->color = h->color;
        h->color = RED;
        return x;
    }

    void colorFlip(Node *h){
        h->color = !h->color;
        h->left->color = !h->left->color;
        h->right->color = !h->right->color;
    }

    Node* fixup(Node *h){
        if(isRed(h->right)) h = rotate_left(h);
        if(isRed(h->left) && isRed(h->left->left)) h = rotate_right(h);
        if(isRed(h->left) && isRed(h->right))colorFlip(h);
        return h;
    }

    void insert(T key){
        root = insert(root,key);
        root->color = BLACK;
    }

    Node* insert(Node *h,T key){
        if(h==NULL)return new Node(RED,key);
        if( key < h->key) h->left = insert(h->left,key);
        else if(key > h->key) h->right = insert(h->right,key);
        else h->key = key;
        return fixup(h);
    }

    void erase(T key){
        root =  erase(root,key);
        if(root != NULL)root->color = BLACK;
    }

    Node* erase(Node *h,T key){
        if(h==NULL)return NULL;
        else if(key < h->key){
            if(isBlack(h->left) && !isRed(h->left->left)) h = moveRedLeft(h);
            h->left = erase(h->left,key);
        }
        else {
            if(isRed(h->left)) h = rotate_right(h);
            if(isBlack(h->right) && !isRed(h->right->left)) h = moveRedRight(h);
            if(key == h->key){
                if(h->right == NULL) return NULL;
                else {
                    Node *rm = minimum(h->right);
                    h->key = rm->key;
                    h->right = deleteMin(h->right);
                }
            }
            else h->right = erase(h->right,key);
        }
        return fixup(h);
    }

    Node* minimum(Node *h){
        while(h->left != NULL)h = h->left;
        return h;
    }

    Node* deleteMin(Node *h){
        if(h->left == NULL)return NULL;
        if(isBlack(h->left) && !isRed(h->left->left)) h = moveRedLeft(h);
        h->left = deleteMin(h->left);
        return fixup(h);
    }

    Node* moveRedLeft(Node* h){
        colorFlip(h);
        if(isRed(h->right->left)){
            h->right = rotate_right(h->right);
            h = rotate_left(h);
            colorFlip(h);
        }
        return h;
    }

    Node* moveRedRight(Node *h){
        colorFlip(h);
        if(isRed(h->left->left)){
            h = rotate_right(h);
            colorFlip(h);
        }
        return h;
    }

    void print(){
        if( root != NULL){
            print_(root);
        } else {
            std::cout << "Tree is empty" << endl;
        }
    }

    void print_(Node *x){
        if(x->left != NULL){
            print_(x->left);
        }
        if(x != NULL){
            std::cout << x->key << " ";
            if(x->color == RED)
                std::cout << "RED ";
            else
                std::cout << "BLACK ";
            if(x->left != NULL)
                std::cout << x->left->key << " ";
            else
                std::cout << "NULL ";
            if(x->right != NULL)
                std::cout << x->right->key << " ";
            else
                std::cout << "NULL ";
        }
        std::cout << std::endl;
        if(x->right != NULL)
            print_(x->right);
    }
};

const int MAX = 100;
int main(){
    LLRB<int> test;
    for(int i=0;i<MAX;++i){
        test.insert(i+1);
    }
    test.print();
    for(int i=0;i<MAX;++i){
        test.erase(i+1);
    }

    for(int i=0;i<MAX;++i){
        test.insert(i*i);
        test.print();
    }

}

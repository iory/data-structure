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
#include <random>
#include <memory>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef vector<int> vec;
typedef vector<vec> mat;
static const double EPS = 1e-9;
static const double PI = acos(-1.0);

template <class T>
class RedBlackTree;


template <class T>
struct RedBlackTreeNode{

public:

    friend class RedBlackTree<T>;
    T getkey(){
        return key;

    }
    RedBlackTreeNode<T>(){
        right = NULL;
        left = NULL;
        p = NULL;
    }
    // RedBlackTreeNode<T> operator=(const RedBlackTreeNode<T> &obj ){
    //   right = obj->right;
    //   left = obj->left;
    //   p = obj->p;
    //   key = obj->key;
    // }
private:
    bool color;     // 0 = black , 1 = red
    std::shared_ptr< RedBlackTreeNode<T> > right;
    std::shared_ptr< RedBlackTreeNode<T> >  left;
    std::shared_ptr< RedBlackTreeNode<T> > p;
    // RedBlackTreeNode<T> *right;
    // RedBlackTreeNode<T> *left;
    // RedBlackTreeNode<T> *p;
    T key;

};



template <class T>
class RedBlackTree{
private:
    // shared_ptr< std::shared_ptr< RedBlackTreeNode<T> > > *nil;
    // shared_ptr< std::shared_ptr< RedBlackTreeNode<T> > > *rot
    std::shared_ptr< RedBlackTreeNode<T> > nil;
    std::shared_ptr< RedBlackTreeNode<T> > root;


public:
    enum COLOR{BLACK=0,RED=1};

    RedBlackTree()// : nil(new std::shared_ptr< RedBlackTreeNode<T> > ), root(nil)
        {
            std::shared_ptr< RedBlackTreeNode<T> > nil( new RedBlackTreeNode<T> );
            std::shared_ptr< RedBlackTreeNode<T> > root( new RedBlackTreeNode<T> );

            root = nil;
            nil->left = NULL;
            nil->right= NULL;
            nil->p    = NULL;
            nil->color = false;
        }

    ~RedBlackTree(){
        // delete nil;
        // delete root;
    }
    // std::shared_ptr< RedBlackTreeNode<T> >* search( T key){
    //   std::shared_ptr< RedBlackTreeNode<T> >* x = root;
    //   while(x != nil){
    //     if(key == x->key)return x;
    //     else if(key < x->key)
    // 	x = x->left;
    //     else
    // 	x = x->right;
    //   }
    //   return nil;
    // }


    std::shared_ptr< RedBlackTreeNode<T> > search( T key ){
        std::cout << "search..." << std::endl;
        std::shared_ptr< RedBlackTreeNode<T> > x(root);
        std::cout << "search..." << std::endl;
        while( x != nil ){
            std::cout << 1 << std::endl;
            if(key == x->key)
                return x;
            else if( key < x->key )
                x = x->left;
            else
                x = x->right;
        }
        std::cout << "search end" << std::endl;
        return nil;
    }

    void erase( T key ){
        std::shared_ptr< RedBlackTreeNode<T> > x = search( key );
        if( x != nil )
            del( x );
    }


    void display( ){
        if(root != nil){
            //std::cout << "value : color : p , left ,right" << std::endl;
            _display( root );
        }
        else {
            std::cout << "Tree is empty." << endl;
        }
    }

    void _display( std::shared_ptr< RedBlackTreeNode<T> > x){
        if(x->left != nil){
            _display(x->left);
        }
        if( x != nil){
            std::cout << x->key << " ";
            if(x->color == RED)
                std::cout << "RED ";
            else
                std::cout << "BLACK ";
            if(x->p != nil)
                std::cout << x->p->key << " ";
            else
                std::cout << "NIL ";
            if(x->left != nil)
                std::cout << x->left->key << " ";
            else
                std::cout << "NIL ";
            if(x->right != nil)
                std::cout << x->right->key << " ";
            else
                std::cout << "NIL ";
        }
        std::cout << std::endl;
        if(x->right != nil)
            _display(x->right);
    }

    void transplant(std::shared_ptr< RedBlackTreeNode<T> > *u,std::shared_ptr< RedBlackTreeNode<T> > *v){
        if(u->p == nil)
            root = v;
        else if( u == u->p->left)
            u->p->left = v;
        else
            u->p->right = v;
        v->p = u->p;
    }

    // void delete_fixup(std::shared_ptr< RedBlackTreeNode<T> > *x){
    //   while(x != root && x->color == BLACK){
    //     std::shared_ptr< RedBlackTreeNode<T> > *w = 0;
    //     if(x == x->p->left){
    // 	w = x->p->right;
    // 	if(w->color == RED){
    // 	  w->color = BLACK;
    // 	  x->p->color = RED;
    // 	  left_rotate(x->p);
    // 	  w = x->p->right;
    // 	}
    // 	if( x->left->color == BLACK && w->right->color == BLACK){
    // 	  w->color = RED;
    // 	  x = x->p;
    // 	}
    // 	else {
    // 	  if(w->right->color == BLACK){
    // 	    w->left->color = BLACK;
    // 	    w->color = RED;
    // 	    right_rotate(w);
    // 	    w = x->p->right;
    // 	  }
    // 	  w->color = x->p->color;
    // 	  x->p->color = BLACK;
    // 	  w->right->color = BLACK;
    // 	  left_rotate( x->p );
    // 	  x = root;
    // 	}
    //     }
    //     else {
    // 	w = x->p->left;
    // 	if(w->color == RED){
    // 	  w->color = BLACK;
    // 	  x->p->color = RED;
    // 	  right_rotate(x->p);
    // 	  w = x->p->left;
    // 	}
    // 	if(x->right->color == BLACK && w->left->color == BLACK){
    // 	  w->color = RED;
    // 	  x = x->p;
    // 	}
    // 	else{
    // 	  if(w->left->color == BLACK){
    // 	    w->right->color = BLACK;
    // 	    w->color = RED;
    // 	    left_rotate(w);
    // 	    w = x->p->left;
    // 	  }
    // 	  w->color = x->p->color;
    // 	  x->p->color = BLACK;
    // 	  w->left->color = BLACK;
    // 	  right_rotate(x->p);
    // 	  x = root;
    // 	}
    //     }
    //   }
    //   x->color = BLACK;
    // }

    void delete_fixup(std::shared_ptr< RedBlackTreeNode<T> > x){
        while( x != root && x->color == false ){
            std::shared_ptr< RedBlackTreeNode<T> > w (new RedBlackTreeNode<T> );
            if( x->p->left == x ){
                w = x->p->right;
                if( w->color == true ){
                    w->color = false;
                    x->p->color = true;
                    left_rotate( x->p );
                    w = x->p->right;
                }
                if( w->left->color == false && w->right->color == false ){
                    w->color = true;
                    x = x->p;
                }
                else{
                    if( w->right->color == false ){
                        w->left->color = false;
                        w->color = true;
                        right_rotate( w );
                        w = x->p->right;
                    }
                    w->color = x->p->color;
                    x->p->color = false;
                    w->right->color = false;
                    left_rotate( x->p );
                    x = root;
                }
            }
            else{
                w = x->p->left;
                if( w->color == true ){
                    w->color = false;
                    x->p->color = true;
                    right_rotate( x->p );
                    w = x->p->left;
                }
                if( w->right->color == false && w->left->color == false ){
                    w->color = true;
                    x = x->p;
                }
                else{
                    if( w->left->color == false ){
                        w->right->color = false;
                        w->color = true;
                        left_rotate( w );
                        w = x->p->left;
                    }
                    w->color = x->p->color;
                    x->p->color = false;
                    w->left->color = false;
                    right_rotate( x->p );
                    x = root;
                }
            }
        }
        x->color = false;
    }


    std::shared_ptr< RedBlackTreeNode<T> >* minimum(std::shared_ptr< RedBlackTreeNode<T> > x){
        while(x->left != nil)
            x = x->left;
        return x;
    }

    // void del( std::shared_ptr< RedBlackTreeNode<T> > *z){
    //   std::shared_ptr< RedBlackTreeNode<T> > *x = nil;
    //   std::shared_ptr< RedBlackTreeNode<T> > *y = z;

    //   bool color_y = y->color;
    //   if( z->left == nil || z->right == nil ){
    //     x = z->right;
    //     transplant(z,z->right);
    //   }
    //   else if(z->right == nil){
    //     x = z->left;
    //     transplant(z,z->left);
    //   }
    //   else {
    //     y = minimum(z->right);
    //     color_y = y->color;
    //     x = y->right;
    //     if(y->p == z)
    // 	x->p = y;
    //     else {
    // 	transplant(y,y->right);
    // 	y->right = z->right;
    // 	y->right->p = y;
    //     }
    //     transplant(z,y);
    //     y->left = z->left;
    //     y->left->p = y;
    //     y->color = z->color;
    //   }

    //   if(color_y == BLACK)
    //     delete_fixup(x);
    //   //delete y;
    // }

    std::shared_ptr< RedBlackTreeNode<T> > successor( std::shared_ptr< RedBlackTreeNode<T> > x ){
        if( x->right != nil ){
            while( x->left != nil )
                x = x->left;
            return x;
        }
        std::shared_ptr< RedBlackTreeNode<T> > y = x->p;
        while( y != nil && x == y->right ){
            x = y;
            y = y->p;
        }
        return y;
    }
    // std::shared_ptr< RedBlackTreeNode<T> > *successor(std::shared_ptr< RedBlackTreeNode<T> > *x){
    //   if( x->right != nil ){
    //     while( x->left != nil )
    // 	x = x->left;
    //     return x;
    //   }
    //   std::shared_ptr< RedBlackTreeNode<T> > *y = x->p;
    //   while( y != nil && x == y->right){
    //     x = y;
    //     y = y->p;
    //   }
    //   return y;
    // }

    void del( std::shared_ptr< RedBlackTreeNode<T> > z){
        std::shared_ptr< RedBlackTreeNode<T> > x = nil;
        std::shared_ptr< RedBlackTreeNode<T> > y = z;

        bool color_y = y->color;
        if( z->left == nil || z->right == nil )
            y = z;
        else
            y = successor(z);
        if( y->left != nil )
            x = y->left;
        else
            x = y->right;
        x->p = y->p;
        if( y->p == nil)
            root = x;
        else {
            if(y==y->p->left)
                y->p->left = x;
            else
                y->p->right = x;
        }
        if(y != z)
            z->key = y->key;
        if(color_y == BLACK)
            delete_fixup(x);
        //    delete y;
    }

    // void del( std::shared_ptr< RedBlackTreeNode<T> > *z ){
    //   std::shared_ptr< RedBlackTreeNode<T> > * x = nil;
    //   std::shared_ptr< RedBlackTreeNode<T> > * y = nil;
    //   if( z->left == nil || z->right == nil )
    //     y = z;
    //   else
    //     y = successor( z );
    //   if( y->left != nil )
    //     x = y->left;
    //   else
    //     x = y->right;
    //   x->p = y->p;
    //   if( y->p == nil )
    //     root = x;
    //   else{
    //     if( y == y->p->left )
    // 	y->p->left = x;
    //     else
    // 	y->p->right = x;
    //   }
    //   if( y != z )
    //     z->key = y->key;
    //   if( y->color == false )
    //     delete_fixup( x );
    //   delete y;
    // }

    // void erase(T key){
    //   std::shared_ptr< RedBlackTreeNode<T> > *t = search( key );
    //   if( t != nil){
    //     del(t);
    //     cout << "key is " << t->key << endl;
    //   }
    // }

    void left_rotate( std::shared_ptr< RedBlackTreeNode<T> > x ){		// x->right != nil
        std::shared_ptr< RedBlackTreeNode<T> > y = x->right;
        if( x->p == nil )
            root = y;
        else{
            if( x == x->p->left )
                x->p->left = y;
            else
                x->p->right = y;
        }
        y->p = x->p;
        x->right = y->left;
        y->left->p = x;
        y->left = x;
        x->p = y;
    }

    void right_rotate( std::shared_ptr< RedBlackTreeNode<T> > x ){
        std::shared_ptr< RedBlackTreeNode<T> > y = x->left;
        if( x->p == nil )
            root = y;
        else{
            if( x->p->left == x )
                x->p->left = y;
            else
                x->p->right = y;
        }
        y->p = x->p;
        x->left = y->right;
        y->right->p = x;
        y->right = x;
        x->p = y;
    }
    // void left_rotate(std::shared_ptr< RedBlackTreeNode<T> > *x){
    //   std::shared_ptr< RedBlackTreeNode<T> > *y = x->right;
    //   x->right = y->left;
    //   if(y->left){
    //     y->left->p = x;
    //   }
    //   y->p = x->p;
    //   if(x->p == nil){
    //     root = y;
    //   }
    //   else if(x == x->p->left){
    //     x->p->left = y;
    //   }
    //   else {
    //     x->p->right = y;
    //   }
    //   y->left = x;
    //   x->p = y;
    // }

    // void right_rotate(std::shared_ptr< RedBlackTreeNode<T> > *x){
    //   std::shared_ptr< RedBlackTreeNode<T> > *y = x->left;
    //   x->left = y->right;
    //   if(y->right){
    //     y->right->p = x;
    //   }
    //   y->p = x->p;
    //   if(x->p == nil){
    //     root = y;
    //   }
    //   else if(x == x->p->right){
    //     x->p->right = y;
    //   }
    //   else {
    //     x->p->left = y;
    //   }
    //   y->right = x;
    //   x->p = y;
    // }

    void insert_fixup( std::shared_ptr< RedBlackTreeNode<T> > z ){
        while( z->p->color  == true ){
            if( z->p == z->p->p->left ){
                std::shared_ptr< RedBlackTreeNode<T> > y = z->p->p->right;
                if( y->color == true ){
                    z->p->color = false;
                    y->color = false;
                    z->p->p->color = true;
                    z = z->p->p;
                }
                else{
                    if( z == z->p->right ){
                        z = z->p;
                        left_rotate( z );
                    }//
                    z->p->color = false;
                    z->p->p->color = true;
                    z->p->right->color = false;
                    right_rotate( z->p->p );
                }
            }
            else{
                std::shared_ptr< RedBlackTreeNode<T> > y = z->p->p->left;
                if( y->color == true ){
                    z->p->color = false;
                    y->color = false;
                    z->p->p->color = true;
                    z = z->p->p;
                }
                else{
                    if( z == z->p->left ){
                        z = z->p;
                        right_rotate( z );
                    }
                    z->p->color = false;
                    z->p->p->color = true;
                    z->p->left->color = false;
                    left_rotate( z->p->p );
                }
            }
        }
        root->color = false;
    }
    // void insert_fixup(std::shared_ptr< RedBlackTreeNode<T> > *z){
    //   while(z->p->color == RED){
    //     if(z->p == z->p->p->left){
    // 	std::shared_ptr< RedBlackTreeNode<T> > *y = z->p->p->right;
    // 	if(y->color==RED){
    // 	  z->p->color = BLACK;
    // 	  y->color = BLACK;
    // 	  z->p->p->color = RED;
    // 	  z = z->p->p;
    // 	}
    // 	else{
    // 	  if(z == z->p->right){
    // 	    z = z->p;
    // 	    left_rotate(z);
    // 	  }
    // 	  z->p->color = BLACK;
    // 	  z->p->p->color = RED;
    // 	  right_rotate(z->p->p);
    // 	}
    //     }
    //     else {
    // 	std::shared_ptr< RedBlackTreeNode<T> > *y = z->p->p->left;
    // 	if(y->color==RED){
    // 	  z->p->color = BLACK;
    // 	  y->color = BLACK;
    // 	  z->p->p->color = RED;
    // 	  z = z->p->p;
    // 	}
    // 	else{
    // 	  if(z == z->p->left){
    // 	    z = z->p;
    // 	    right_rotate(z);
    // 	  }
    // 	  z->p->color = BLACK;
    // 	  z->p->p->color = RED;
    // 	  left_rotate(z->p->p);
    // 	}
    //     }
    //   }
    //   root->color = BLACK;
    // }

    // void insert( T key){
    //   std::shared_ptr< RedBlackTreeNode<T> >* t = new std::shared_ptr< RedBlackTreeNode<T> >;
    //   t->key = key;
    //   std::shared_ptr< RedBlackTreeNode<T> >* y = nil;
    //   std::shared_ptr< RedBlackTreeNode<T> >* x = root;
    //   while( x != nil){
    //     y = x;
    //     if(key < x->key)
    // 	x = x->left;
    //     else
    // 	x =  x->right;
    //   }
    //   t->p = y;
    //   if(y==nil){
    //     root = t;
    //   }
    //   else {
    //     if(t->key < y->key)
    // 	y->left = t;
    //     else
    // 	y->right = t;
    //   }
    //   t->left = nil;
    //   t->right= nil;
    //   t->color = RED;
    //   insert_fixup(t);
    // }


    void insert( T key ){
        std::cout << "starting..." << std::endl;
        if(search(key)!=nil)return;
        //std::shared_ptr< RedBlackTreeNode<T> > t(new RedBlackTreeNode<T> );
        std::shared_ptr< RedBlackTreeNode<T> > t;
        //std::shared_ptr<std::shared_ptr< RedBlackTreeNode<T> > > t( new std::shared_ptr< RedBlackTreeNode<T> >);
        t->key = key;
        std::cout << "test" << std::endl;
        std::shared_ptr< RedBlackTreeNode<T> > x = root;
        std::shared_ptr< RedBlackTreeNode<T> > y = nil;
        while( x != nil ){
            y = x;
            if( key < x->key )
                x = x->left;
            else
                x = x->right;
        }
        std::cout << "test" << std::endl;
        t->p = y;
        if( y == nil )
            root = t;
        else{
            std::cout << "test" << std::endl;
            if ( t->key < y->key )
                y->left = t;
            else
                y->right = t;
        }
        std::cout << "test" << std::endl;
        t->left = nil;
        t->right = nil;
        t->color = true;
        insert_fixup( t );
    }
};



const int MAX = 10;


int main(){
    RedBlackTree<int> rbtree;
    std::random_device rnd;
    std::mt19937 engine( rnd() );
    std::uniform_int_distribution<int> dist( 1, 1000000);

    int temp;
    vector<int> v;
    for(int i=0;i<MAX;++i){
        temp = dist(engine);
        v.push_back(temp);
        cout << temp <<endl;
        rbtree.insert( temp );
    }
    rbtree.display();


    int input;
    int tmp;
    for(int i=0;i<MAX;++i){
        cout << "round " << i << endl << endl;
        rbtree.erase( v[i] );
        rbtree.display();
    }
    // while(1){
    //   cout << "1:add element, 2:delete element, 3.display, 9:end" << endl;
    //   cin >> input;

    //   if(input==1){
    //     cin >> tmp;
    //     rbtree.insert(tmp);
    //     rbtree.display();
    //   } else if(input==2){
    //     cin >> tmp;
    //     rbtree.erase(tmp);
    //     rbtree.display();
    //   }
    //   else if(input==3){
    //     rbtree.display();
    //   }
    //   else if(input==9)
    //     break;
    // }
    return 0;
}

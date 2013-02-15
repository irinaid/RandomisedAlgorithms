#ifndef RBST_HPP_
#define RBST_HPP_

#include <iostream>
#include <assert.h>
#include <vector>
#include <math.h>
#include <string.h>
#include <cstdlib>
#include <cstring>
#include "Key.hpp"
#include "DataStructure.hpp"


using namespace std;

class RBSTNode;
class RBSTNode: public Key {
public:
    RBSTNode(const Key& key):Key(key),m_left(NULL),m_right(NULL) {
   // 	left_size = 0;
   //     right_size = 0;
    }
    virtual ~RBSTNode() {}

    string getKey() {
        return *this;
    }

    string setKey(const Key& key) {
        assign(key);
        return Key(key);
    }

    RBSTNode* left() {
        return m_left;
    }
    RBSTNode* right() {
        return m_right;
    }

    RBSTNode* setLeft (RBSTNode* left) {
        m_left = left;
   //     left_size = left->left_size + 1 + left->right_size;
        return this;
    }
    RBSTNode* setRight (RBSTNode* right) {
        m_right =right;
  //     right_size = right->left_size + 1 + right->right_size;
        return this;
    }

    //int getNodeSize() {
    //  return left_size + 1 + right_size;
    //}
private:
    RBSTNode() {}
    RBSTNode* m_left;
    RBSTNode* m_right;
  //  unsigned int left_size;
  //  unsigned int right_size;
};


class RBST : public DataStructure {
public:
    RBST():m_head(NULL),m_size(0){};
    virtual ~RBST() {};

    //ADD FUNCTIONS
    int add(const Key& key, bool verbose=false);

    //FIND FUNCTIONS
    int find(const Key& key, bool verbose = false);

    //DEL FUNCTIONS
    int del(const Key& key, bool verbose=false);

    //DUMP FUNCTIONS
    int dump(char sep = ' ');
    int dump(RBSTNode* target, char sep);

private:
    RBSTNode* randomAdd(RBSTNode* target, const Key& key);
    RBSTNode* addRoot(RBSTNode* target, const Key& key);
    RBSTNode*  rightRotate(RBSTNode* target);
    RBSTNode*  leftRotate(RBSTNode* target);

    RBSTNode* del(RBSTNode* target, const Key& key);

    RBSTNode* find(RBSTNode* target, const Key& key);

    RBSTNode* m_head;
    unsigned int m_size;


};

#endif /*RBST_HPP_*/

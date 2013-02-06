#include "RBST.hpp"
/***********************************************************/
/******************* PROVIDED FUNCTIONS ********************/
/***********************************************************/

int RBST::add(const Key& key, bool verbose) {
    unsigned int oldSize = m_size;
    m_head = randomAdd(m_head, key);
    if (m_size > oldSize) {
        if (verbose) {
            cout<<"Node "<<key<< " is added into the tree."<<endl;
        }
        return 1;
    } else {
        if (verbose) {
            cout<<"Node "<<key<< " is already in the tree."<<endl;
        }
        return 0;
    }
    if (verbose) cout<<endl;
};

int RBST::del(const Key& key, bool verbose) {
    unsigned oldSize= m_size;
    m_head = del(m_head, key);
    if (m_size < oldSize) {
        if (verbose) {
            cout<<"Node "<<key<< " is deleted from the tree."<<endl;
        }
        return 1;
    } else {
        if (verbose) {
            cout<< "Node "<<key<< " is not in the tree."<<endl;
        }
        return 0;
    }
};

int RBST::find(const Key& key, bool verbose) {
    RBSTNode* ret = find(m_head, key);
    if (ret == NULL) {
        if (verbose) {
            cout<< "Node "<<key<< " is not in the tree."<<endl;
        }
        return 0;
    } else {
        if (verbose) {
            cout<<"Node "<<key<< " is in the tree."<<endl;
        }
        return 1;
    }
};

int RBST::dump(char sep) {
    int ret = dump(m_head, sep);
    cout<<"SIZE: " <<ret<<endl;
    return ret;
};

int RBST::dump(RBSTNode* target, char sep) {
    if (target == NULL) {
        return 0;
    }
    int ret = dump(target->left(), sep);
    cout<< *target<<sep;
    ret ++;
    ret += dump(target->right(), sep);
    return ret;
};



/***********************************************************/
/****************  FUNCTIONS TO BE COMPLETED  ***************/
/***********************************************************/


/////////////////////////////////////////////////////////////
/////////////////////  ADD FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

RBSTNode*  RBST::rightRotate(RBSTNode* target) {
    ////////////// Write your code below  ////////////////////////
    RBSTNode *l = target->left();
    l->setLeft(l->right());
    l->setRight(target);
    return l;
};

RBSTNode*  RBST::leftRotate(RBSTNode* target) {
    ////////////// Write your code below  ////////////////////////
    RBSTNode *l = target->right();
    l->setRight(l->left());
    l->setLeft(target);
    return l;
};

RBSTNode* RBST::addRoot(RBSTNode* target, const Key& key) {
    countAdd++;
    ////////////// Write your code below  ////////////////////////
    RBSTNode *newNode = new RBSTNode(key);
    if (!target) return newNode;
    if (key < dynamic_cast<Key&>(*target)) {
		target->setLeft(addRoot(target->left(), key));
		return rightRotate(target);
	} else {
		target->setRight(addRoot(target->right(), key));
		return leftRotate(target);
	}
    return target;
};


RBSTNode* RBST::randomAdd(RBSTNode* target, const Key& key) {
    countAdd++;
    ////////////// Write your code below  ////////////////////////
	RBSTNode *newNode = new RBSTNode(key);
    if (!target) return newNode;
	int r = rand() % (m_size - 1) + 1;
	if (r == 1) {
		m_size++;
		return addRoot(target, key);
	}	
	if (key < dynamic_cast<Key&>(*target)) {
		target->setLeft(randomAdd(target->left(), key));
	} else {
		target->setRight(randomAdd(target->right(), key));
	}
    m_size++;
    return target;
};

/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTIONS ///////////////////////
/////////////////////////////////////////////////////////////

RBSTNode* RBST::find(RBSTNode* target, const Key& key) {
    countFind++;
    ////////////// Write your code below  ////////////////////////
/*
    int cmp = strcmp(target,key);
    if(!cmp) {
        return target;
    }
    if(cmp>0) { //target bigger than key
        return find(target->left(), key);
    }
    if(cmp<0) { //target lesser than key
        return find(target->right(), key);
    }

*/
    return target;
}


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////


RBSTNode* RBST::del(RBSTNode* target, const Key& key) {
    countDelete++;
    ////////////// Write your code below  ////////////////////////




    return target;
};


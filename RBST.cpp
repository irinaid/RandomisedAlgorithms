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
	int r = rand() % (target->getNodeSize() - 1) + 1;
	if (r == 1) {
		//here we should increase the size of newNode,
                //but I'm not sure if it's still necessary
		return addRoot(target, key);
	}	
	if (key < dynamic_cast<Key&>(*target)) {
		target->setLeft(randomAdd(target->left(), key));
	} else {
		target->setRight(randomAdd(target->right(), key));
	}
    //m_size++;
    //not sure if the above should be replace or deleted
    return target;
};

/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTIONS ///////////////////////
/////////////////////////////////////////////////////////////

RBSTNode* RBST::find(RBSTNode* target, const Key& key) {
    countFind++;
    ////////////// Write your code below  ////////////////////////
    int cmp = strcmp(target->c_str(),key.c_str());

    if(!cmp) {
        return target;
    }
    if(cmp>0) { //target bigger than key
        if(target->left() == NULL) {return NULL;}
        return find(target->left(), key);
    }
    if(cmp<0) { //target lesser than key
        if(target->right() == NULL) {return NULL;}
        return find(target->right(), key);
    }

    return NULL;
}


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////


RBSTNode* RBST::del(RBSTNode* target, const Key& key) {
    countDelete++;
    ////////////// Write your code below  ////////////////////////

    RBSTNode *parent = NULL;
    RBSTNode *n = target;

    int dir = 0;

    while (1) {
        int cmp = strcmp(n->c_str(),key.c_str());
        if(!cmp) {
            break;
        }
        dir = cmp;
        if(cmp>0) { //target bigger than key
            parent = n;
            n = target->left();
            if(n == NULL) {return NULL;}
        }
        if(cmp<0) { //target lesser than key
            parent = n;
            n = target->right();
            if(n == NULL) {return NULL;}
        }
    }

    if(n==NULL) {return NULL;}

    if(target->left()!=NULL&&target->right()!=NULL) {
        //Both left and right.
        if(rand()&1) {
            //Swap left
            leftRotate(n);
            return del(n, key);
        } else {
            //Swap right
            rightRotate(n);
            return del(n, key);
        }
    } else {
        if(target->left()!=NULL || target->right()!=NULL) {
            //Has one node:
            if(target->left()!=NULL) {
                if(dir>0) {
                    parent->setLeft(target->left());
                } else {
                    parent->setRight(target->left());
                }
                return n;
            } else {
                if(dir>0) {
                    parent->setLeft(target->right());
                } else {
                    parent->setRight(target->right());
                }
                return n;
            }
        } else {
            if(dir>0) {
                parent->setLeft(NULL);
            } else {
                parent->setRight(NULL);
            }
            return n;
        }
    }

};


#include "SkipList.hpp"
/***********************************************************/
/********************** PROVIDED FUNCTIONS *****************/
/***********************************************************/
void SkipList::init(int maxHeight) {
    m_maxHeight = maxHeight;
    m_head = new SkipListNode("", m_maxHeight);
}

SkipList::~SkipList() {
    while (m_head != NULL) {
        SkipListNode* head = m_head;
        m_head = m_head->nextAtLevel(0);
        delete head;
    }
}

int SkipList::add(const Key& key, bool verbose) {
    if (find(key, false) != 0) {
        if (verbose) {
            cout<<"Node "<<key<<" is already in the list."<<endl;
        }
        return 0;
    }

    SkipListNode* newNode = new SkipListNode(key, randHeight());
    if (verbose) {
        cout<<"Add new node "<<*newNode<<" with height "<<newNode->height()<<endl;
    }
    int ret = add (m_head, newNode, m_maxHeight-1);
    if (ret == 0 ) {
        return ret;
    }
    return 1;
}

int SkipList::find(const Key &key, bool verbose) {
    SkipListNode* ret =find (m_head, key, m_maxHeight-1) ;
    if (ret == NULL) {
        if (verbose) {
            cout<< "Node "<<key<<" is not in the list"<<endl;
        }
        return 0;
    } else {
        if (verbose) {
            cout<< "Node "<<key<<" is in the list"<<endl;
        }
        return 1;
    }

}
int SkipList::del(const Key& key, bool verbose) {
    if (key.length() == 0){
      return 1;
    }
    SkipListNode* toBeDeleted  = del(m_head, key, m_maxHeight-1);

    if (toBeDeleted == NULL) {
        if (verbose) {
            cout<< "Node "<<key<<" is not in the list"<<endl;
        }
    } else {
        delete toBeDeleted;
        if (verbose) {
            cout<< "Node "<<key<<" is deleted from the list"<<endl;
        }
    }
    return 1;
}

void SkipList::dump(char sep) {
    int length = -1;
    cout<<"Current List: ";
    for ( SkipListNode* iter = m_head; (iter != NULL); iter=iter->nextAtLevel(0)) {
        length++;
        cout << string(*iter)<<" ";
        cout <<"("<< iter->height() <<":";
        unsigned int i;
        for (i=0; i< iter->height(); i++) {
            if (iter->nextAtLevel(i)) {
                cout<<" "<<i<<":"<<*(iter->nextAtLevel(i));
                cout.flush();
            }
        }
        cout<<")"<<sep;
    }
    cout<<length<<" nodes in total."<<endl;
}


/***********************************************************/
/***************  FUNCTIONS TO BE COMPLETED  ****************/
/***********************************************************/

/////////////////////////////////////////////////////////////
/////////////////////  ADD FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

unsigned int SkipList::randHeight() {
    ////////////// Write your code below  ////////////////////////
    int t = 1 + (rand() % (RAND_MAX - 1));
    int j = 2;
    unsigned int i = 1;
    for (; i <= m_maxHeight; ++i) {
      if (t > (RAND_MAX / j)) {
        break;
      }
      j <<= 1;
    }
    return i;
}


int SkipList::add(SkipListNode* target, SkipListNode* newNode, unsigned int level) {

    if (target->nextAtLevel(level) != NULL &&
            (*target->nextAtLevel(level)) < *newNode) {
        countAdd++;
    }
    ////////////// Write your code below  ////////////////////////
    SkipListNode *t = target->nextAtLevel(level);
    if (t == NULL || newNode < t) {
        if (level < newNode->height()) {
            newNode->setNextAtLevel(level, t);
            target->setNextAtLevel(level, newNode);
        }
        if(level) {add(target, newNode, level-1);}
        return 1;
    }
    return add(t,newNode,level);
}

/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTION ////////////////////////
/////////////////////////////////////////////////////////////
SkipListNode* SkipList::find(SkipListNode* target, const Key& key, unsigned int level) {

    if (target->nextAtLevel(level) != NULL && *(target->nextAtLevel(level)) < key) {
        countFind++;
    }
    ////////////// Write your code below  ////////////////////////
    if (target == NULL) {return NULL;}
    if (dynamic_cast<Key&>(*target) == key) {return target;}
   // if (level >= 0 && level < m_links.size())
    	SkipListNode *t = target->nextAtLevel(level);

    if (t == NULL || key < dynamic_cast<Key&>(*t)) {
        if (level==0) {return NULL;}
        return find(target, key, level-1);
    }

    return find(t,key,level);
}


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTION ////////////////////////
/////////////////////////////////////////////////////////////
SkipListNode* SkipList::del(SkipListNode* target, const Key& key, unsigned int level) {
    if (target->nextAtLevel(level) != NULL && *(target->nextAtLevel(level))
		< key) {
        countDelete++;
    }
/*	////////////// Write your code below  ////////////////////////
    if (target == NULL) return NULL;
	SkipListNode *x = target->nextAtLevel(level);
	//if next node is null go down one level or end reached 
	if (x == NULL || dynamic_cast<Key&>(*x) > key) {
		if (level > 0) { 
			return del(target, key, level-1);
		} else {
			return NULL;
		}
	} 

	//if next node is larger or equal to the given key
	if (dynamic_cast<Key&>(*x) >= key) {
        //if the key is in the next node
		if (dynamic_cast<Key&>(*x) == key) {
			target->setNextAtLevel(level, x->nextAtLevel(level));
			if (level > 0) {
				return del(target, key, level-1);
			} 
			else return x;
		}
		else return del(target, key, level-1);
	} 
	//if the key is bigger than the node try the next node
	else if (level == 0) return NULL;
	return del(x, key, level);
    

    ////////////// Write your code below  ////////////////////////
/*
    SkipListNode *n = target->nextAtLevel(level);
    if (n == NULL) {
        if (level > 0) {
            del(target,key,level-1);
        }
        return NULL;
    }

	if (dynamic_cast<Key&>(*n) >= key) {
        if (dynamic_cast<Key&>(*n) == key) {
            if (level == 0) {
                target->setNextAtLevel(level,n->nextAtLevel(level));
                return n;
            }
        }
        else
        {
            if (level == 0) {
                return n;
            }
        }
        del(target,key,level-1);
	}
	else
	{
	    del(target->nextAtLevel(level),key,level);
	}*/
}

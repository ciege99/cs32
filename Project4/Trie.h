#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>


//make sure to delete this
#include <iostream>

template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;

      // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    
    //delete this!!!!
    void printTest();

private:
    struct tNode {
        
        tNode(char val) {
            base = val;
        }
        std::vector<tNode*> children;
        //tNode* children[5];
        char base;
        std::vector<ValueType> values;
        
    };
    //helper functions
    
    //recursive
    void insertRecursive(const std::string& key, const ValueType& value, tNode* root);
    void deleteRecursive(tNode* ptr);
    std::vector<ValueType> findRecursive(const std::string& s, bool exactMatchOnly, tNode* ptr) const;
    

    void printTestRecurse(tNode* ptr) const;
    
    //member variables
    tNode* root;    //dummy root node
};



template <typename ValueType>
Trie<ValueType>::Trie() {
    root = new tNode(' ');  //arbritray value since this will be dummy
}


template <typename ValueType>
Trie<ValueType>::~Trie() {
    deleteRecursive(root);
}

template <typename ValueType>
void Trie<ValueType>::reset() {
    deleteRecursive(root);  //delete and reassign root
    root = new tNode(' ');  //create new dummy
}


template <typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value) {
    insertRecursive(key, value, root);  //call recursive function
}


template <typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const {
    int n = -1;
    std::vector<ValueType> v;
    for (int i = 0; i < root->children.size(); i++)
    {
        if (key[0] == root->children[i]->base)
        {
            n = i;
            break;
        }
    }
    if (n == -1)
        return v;
    return findRecursive(key, exactMatchOnly, root->children[n]);
}

template <typename ValueType>
void Trie<ValueType>::insertRecursive(const std::string& s, const ValueType& value, tNode* root) {
    if (s.size() == 0 ) //base of string being empty
    {
        root->values.push_back(value);
        return;
    }

    int n = 0;
    bool contains = false;
    for (int i = 0; i < root->children.size(); i++)
    {
        if (s[0] == root->children[i]->base)
        {
            contains = true;
            n = i;
            break;
        }
    }
    
    if(!contains)  //if pos empty, allocate new node
    {
        root->children.push_back(new tNode(s[0]));
        n = static_cast<int>(root->children.size() - 1);   //n is end of the vector
    }
    insertRecursive(s.substr(1), value, root->children[n]); //recursive call on smaller string
}


template <typename ValueType>
void Trie<ValueType>::deleteRecursive(tNode* ptr) {
    if (ptr == nullptr)
        return;
    
    for (int i = 0; i < ptr->children.size(); i++) //post order deletion
        deleteRecursive(ptr->children[i]);
    
    delete ptr;
}

template <typename ValueType>
std::vector<ValueType> Trie<ValueType>::findRecursive(const std::string& s, bool exactMatchOnly, tNode* ptr) const {
    
    std::vector<ValueType> v1;
    
    if (ptr == nullptr) //end of branch
        return v1;  //return empty vector
    
    if (s[0] != ptr->base && exactMatchOnly)    //not an exact match
        return v1;
    
    if ((s.size() == 1 && s[0] == ptr->base) ||
        (s.size() == 1 && s[0] != ptr->base && !(exactMatchOnly))) //return vector if at end and there is a match
        return ptr->values;
    
    if (s[0] != ptr->base && !(exactMatchOnly))
        exactMatchOnly = true;  //there has been a mismatch and no others can be different
    
    for (int i = 0; i < ptr->children.size(); i++)
    {   //recurse through children and add to vector
        std::vector<ValueType> v2 = findRecursive(s.substr(1), exactMatchOnly, ptr->children[i]);
        v1.insert(v1.end(), v2.begin(), v2.end());
    }
    
    return v1;  //return values that were combined
}

template <typename ValueType>
void Trie<ValueType>::printTest() {
    for (int i = 0; i < 5; i++)
        printTestRecurse(root->children[i]);
}

template <typename ValueType>
void Trie<ValueType>::printTestRecurse(tNode* ptr) const {

    if (ptr == nullptr)
        return;
    
    std::cout << ptr->base << std::endl;
    for (int i = 0; i < ptr->children.size(); i++)
        printTestRecurse(ptr->children[i]);
    
}


#endif // TRIE_INCLUDED


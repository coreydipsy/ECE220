//Corey Yu kaiyiyu2 
//Connor Tancctan2


#include "binary.h"
using namespace std;

/***
A Tree Node constructor. Set all the
member variables (key_, data_, left, right)
of the Node class. 

Input: 
T key - The key for the node
Y data - The actual value from the node

Output:
N/A
***/
template <class T, class Y>
Node<T, Y>::Node(T key, Y data){
   key_ = key;
   data_ = data;
   left = NULL;
   right = NULL;
} 

/***
A Node member getter function. This returns the
key of the node. 

Input: 
N/A

Output:
T - returns the key of the node that is of type T
***/
template <class T, class Y>
T Node<T, Y>::getKey(){
   return key_;
}

/***
A Node member getter function. This returns the
actual data of the node. 

Input: 
N/A

Output:
Y - Returns the data of the node that is of type Y
***/
template <class T, class Y>
Y Node<T, Y>::getData(){
   return data_;
}

/***
A Node member setter function. This sets the key
of a Node.

Input: 
T key - Sets the key of the Node of type T

Output:
N/A
***/
template <class T, class Y>
void Node<T, Y>::setKey(T key){
    key_ = key;
}

/***
A Node member setter function. This sets the actual
data of a Node.

Input: 
Y data - Sets the value of the Node of type Y

Output:
N/A
***/
template <class T, class Y>
void Node<T, Y>::setData(Y data){
    data_ = data;
}


/***
The BinaryTree constructor. Implicitly set the 
values of the member variables


Input: 
N/A

Output:
N/A
***/

template <class T, class Y>
BinaryTree<T,Y>::BinaryTree(){//for the class BinaryTree, define the funtion BinaryTree
    root = NULL;
}


/***
A BinaryTree Member fuction. This function takes in two arguments
and inserts a node. If the key already exists in the tree do nothing.

Input: 
Node<T,Y> *parent_node - The current root node
Node<T,Y> *data - The Node that you want to insert into the tree

Output:
N/A
***/
template <class T, class Y>
void BinaryTree<T,Y>::insert_node(Node<T,Y> *parent_node, Node<T,Y> *data){// data is the child
    if(parent_node == NULL){
        //parent_node = data;
        //parent_node -> left = NULL;
        //parent_node -> right = NULL;
        root = data; //i created a new node now the root should be pointing to the only existing node i created
        return; 
    }

    if(data -> getKey() == parent_node -> getKey()){
        return;
    }else if(data -> getKey() < parent_node -> getKey()){//the tree is sorted based on the key, this is the left side
        if(parent_node -> left == NULL){
            parent_node -> left =  data;
            //parent_node -> left -> left = NULL;
            //parent_node -> left -> right = NULL;
            return;
        }else{
            return insert_node(parent_node -> left, data);
        }
    }else{
        if(parent_node -> right == NULL){
            parent_node -> right = data;
            //parent_node -> right -> left = NULL;
            //parent_node -> right -> right = NULL;
            return;
        }else{
            return insert_node(parent_node -> right, data);
        }
    }
}

/***
A BinaryTree Member fuction. This function takes in one arguments
and finds the parent of a node given a key.
If the key does not exist in the tree return NULL.

Input: 
T key - The key of the node you are searching for.

Output:
Node<T,Y> * - returns the parent of the node you are searching for
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::find_node_parent(T key){// didn't give me the root node where do i start
    return find_node_parent(this->root, key);
}

/***
A BinaryTree Member fuction. This function takes in one arguments
and finds the node given a key.
If the key does not exist in the tree return NULL.

Input: 
T key - The key of the node you are searching for.

Output:
Node<T,Y> * - returns the node you are searching for
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::find_node(T key){
    return find_node(this->root, key);
}


/***
A BinaryTree Member fuction. This function deletes a node in
the binary tree. If the key does not exist do not do anything.

Input: 
T key - The key of the node you are trying to delete.

Output:
N/A
***/
template <class T, class Y>
void BinaryTree<T,Y>::delete_node(T key){

    this->root = delete_node(this->root, key);
}


/***
A BinaryTree helper fuction. This function deletes a node in
the binary tree. If the key does not exist in the tree return NULL.

Input: 
T key - The key of the node you are trying to delete.
Node<T,Y>*node - The root of the current subtree

Output:
Node<T,Y> * - The new root since the root can be deleted.
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::delete_node(Node<T,Y>* node, T key){
    if(node == NULL){
        return node;
    }else if(key < node->getKey()){
        node -> left = delete_node(node->left,key);
    }else if(key > node->getKey()){
        node -> right = delete_node(node->right,key);
    }else if(key == node->getKey()){
        if((node->left == NULL) && (node->right == NULL)){
            delete node;
            return NULL;
        }else if(node->left == NULL){
            Node<T,Y>* temp_node = node->right;
            delete node;
            return temp_node;
        }else if(node->right == NULL){
            Node<T,Y>* temp_node = node->left;
            delete node;
            return temp_node;
        }else if((node->left != NULL) && (node->right != NULL)){
            Node<T,Y>* temp_node = node->right;
            while(temp_node->left != NULL){
                temp_node = temp_node->left;
            }
            node->setKey(temp_node->getKey());
            node->setData(temp_node->getData());
            node->right = delete_node(node->right, temp_node->getKey());
        }
    }
    return node;
}


/***
A BinaryTree helper fuction. This function finds the parent node of
a node with a given key for the binary tree. If the key does not exist in the tree return NULL.

Input: 
T key - The key of the node you are trying to find.
Node<T,Y>*node - The root of the current subtree

Output:
Node<T,Y> * - Returns the parent of the key you were searching for
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::find_node_parent(Node<T,Y> *node,T key){
    // //check if node is null
    // if(node == NULL || node->getKey() == key){
    //     return NULL;
    // }else if(node == NULL || node->getKey() == key){
    //     return node;
    // }else if(node->left != NULL && node->left->getKey() == key){
    //     return node;
    // }else if(node->right != NULL && node->right->getKey() == key){
    //     return node;
    // }

    // if(node->getKey() > key){
    //     return find_node_parent(node->left,key);
    // }
    // return find_node_parent(node->right,key);


    if(node == NULL){
        return NULL;
    }

    if((node->left == NULL) && (node->right == NULL)){
        return NULL;
    }

    if((node->left != NULL)&&(node->left->getKey() == key)){
        return node;
    }else if((node->right != NULL)&&(node->right->getKey() == key)){
        return node;
    }else if(key < node->getKey()){
        if(node->left != NULL){
            return find_node_parent(node->left, key);
        }
        return NULL;
    }else{
        if(node->right != NULL){
            return find_node_parent(node->right, key);
        }
        return NULL;
    }
}

/***
A BinaryTree helper fuction. This function finds the node with 
a given key for the binary tree. If the key does not exist in 
the tree return NULL.

Input: 
T key - The key of the node you are trying to find.
Node<T,Y>*node - The root of the current subtree

Output:
Node<T,Y> * - Returns the Node in the Tree
              for the key you were searching for
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::find_node(Node<T,Y> *node,T key){
    // Node<T,Y> *p = find_node_parent(node,key);
    // if(node == NULL){
    //     return NULL;
    // }
    // if(p==NULL&&(node->getKey()!=key)){
    //     return NULL;
    // }else if(p==NULL&&(node->getKey() == key)){
    //     return node;
    // }else if((p->left != NULL)&&(p->left->getKey == key)){
    //     return p->left;
    // }
    // return p->right;

    if(node == NULL){
        return NULL;
    }

    if(node->getKey() == key){
        return node;
    }else if(key < node->getKey()){
        return find_node(node->left, key);
    }else{
        return find_node(node->right, key);
    }

}

/***
A BinaryTree member fuction. This function performs
pre_order traversal on the tree and stores the nodes
inside a list

Input: 
Node<T,Y> *node - The current root of the subtree
List<Node<T,Y>> - A list to store all the nodes.

Output:
N/A
***/
template <class T, class Y>
void BinaryTree<T,Y>::pre_order(Node<T,Y> *node, std::list<Node<T,Y> > &list){
    if(node!=NULL){
        //action
        list.push_back(*node);//node is a node pointer it is looking for node
        pre_order(node->left, list);//is the syntax for list correct
        pre_order(node->right, list);
    }
}

/***
A BinaryTree member fuction. This function performs
in_order traversal on the tree and stores the nodes
inside a list

Input: 
Node<T,Y> *node - The current root of the subtree
List<Node<T,Y>> - A list to store all the nodes.

Output:
N/A
***/
template <class T, class Y>
void BinaryTree<T,Y>::in_order(Node<T,Y> *node, std::list<Node<T,Y> > &list){
    if(node!=NULL){
        in_order(node->left, list);//is the syntax for list correct
        list.push_back(*node);
        in_order(node->right, list);
    }
}

/***
A BinaryTree member fuction. This function performs
post_order traversal on the tree and stores the nodes
inside a list

Input: 
Node<T,Y> *node - The current root of the subtree
List<Node<T,Y>> - A list to store all the nodes.

Output:
N/A
***/
template <class T, class Y>
void BinaryTree<T,Y>::post_order(Node<T,Y> *node, std::list<Node<T,Y> > &list){
    if(node!=NULL){
        post_order(node->left, list);//is the syntax for list correct
        post_order(node->right, list);
        list.push_back(*node);
    }
}

/***
A BinaryTree getter fuction. This function gets
the current root of the binary tree.

Input: 
N/A
Output:
Outputs the root of the binary tree
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::getRoot(){
   return root;
}


/***
The BinaryTree destructor. Make sure all
the TreeNodes that have been created get destroyed
and make sure there are no memory leaks.

Input: 
N/A

Output:
N/A
***/
template <class T, class Y>
BinaryTree<T,Y>::~BinaryTree(){
    while(this->getRoot() != NULL){
		delete_node(root->getKey());
	}
}

template class Node<int, std::string>;
template class Node<std::string, std::string>;
template class Node<int, int>;
template class Node<double, double>;
template class Node<std::string, long>;
template class Node<std::string, std::list<std::string> >;
template class Node<std::string, int >;

template class BinaryTree<std::string, std::list<std::string> >;
template class BinaryTree<std::string, std::string>;
template class BinaryTree<int, int>;
template class BinaryTree<int, std::string>;
template class BinaryTree<std::string, int>;

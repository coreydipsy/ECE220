//Corey Yu kaiyiyu2 
//Connor Tancctan2

#include "anagram.h"
#include <iostream>
#include <fstream>

/***
An AnagramDict constructor. This Constructor takes in a filepath
and then creates a binary tree out of all the words inside the 
binary tree. 

Input: 
std::string filename - the path to the file

Output:
N/A
***/
AnagramDict::AnagramDict(std::string filename) {
    filename_ = filename;
    std::string path = "dictionaries/" + filename_;
    std::ifstream file;
    file.open(path.c_str());
    std::string str;
    while(file >> str){
        addWord(str);
    }     

    file.close();
    
}

/***
An AnagramDict member function. This function sorts the given word in 
lexicographical order

Input: 
std::string word - the word that needs to be sorted

Output:
std::string - the sorted version of the input
***/
std::string AnagramDict::sortWord(std::string word) {
    std::sort(word.begin(),word.end());
   return word;
}

/***
An AnagramDict member function. This function adds a word to the tree.
If the words sorted version already exists in the tree add it to the linked
list of that node. If the sorted word does not exist in the tree create a new
node and insert it into the tree
Duplicated words should not be added to the tree.
Input: 
std::string word - the word that needs to inserted

Output:
N/A
***/
void AnagramDict::addWord(std::string word) {
    std::string sorted_word = sortWord(word);
    Node<std::string, std::list<std::string> > * target = this->tree.find_node(sorted_word);
    if(target != NULL){
        std::list<std::string> target_list = target->getData();
        for(std::list<std::string>::iterator it = target_list.begin(); it != target_list.end(); it++ ){
            if(*it==word){

                return;
            }
        }
        target_list.push_back(word);
        target->setData(target_list);
    }else{
        std::list<std::string> new_list;
        new_list.push_back(word);
        Node<std::string, std::list<std::string> > * corey = new Node<std::string, std::list<std::string> > (sorted_word, new_list);
        this->tree.insert_node(this->tree.getRoot(),corey);
    }

}

/***
An AnagramDict member function. Does a preorder, postorder, or inorder traversal
and then prints out all the anagrams and words.

The output file should be the traversal order of the tree, but only the data on each line. 
View on wiki for more information. 

Input: 
std::string order - The type of order you want to traverse. Can be "pre", "post", "in"

Output:
N/A
***/
void AnagramDict::saveAnagrams(std::string order) {
    std::string path = "output/" + order+"_"+ filename_;
    std::ofstream file;
    file.open(path.c_str());
    if(!file.is_open()) {
        //create new file
        file.open(path.c_str(),std::ios::out);
    }
    std::list<Node<std::string, std::list<std::string> > > new_list;
    if(order == "pre"){
        this->tree.pre_order(this->tree.getRoot(),new_list);
        for(std::list<Node<std::string, std::list<std::string> > >::iterator it = new_list.begin(); it != new_list.end(); it++ ){
            std::list<std::string> idk = it->getData();
            for(std::list<std::string>::iterator it2 = idk.begin(); it2 != idk.end(); it2++ ){
                file<<*it2<<" " ;
            }
            file<<std::endl;
        }


    }else if(order == "post"){
        this->tree.post_order(this->tree.getRoot(),new_list);
        for(std::list<Node<std::string, std::list<std::string> > >::iterator it = new_list.begin(); it != new_list.end(); it++ ){
            std::list<std::string> idk = it->getData();
            for(std::list<std::string>::iterator it2 = idk.begin(); it2 != idk.end(); it2++ ){
                file<<*it2<<" " ;
            }
            file<<std::endl;
        }

    }else if(order == "in"){
        this->tree.in_order(this->tree.getRoot(),new_list);
        for(std::list<Node<std::string, std::list<std::string> > >::iterator it = new_list.begin(); it != new_list.end(); it++ ){
            std::list<std::string> idk = it->getData();
            for(std::list<std::string>::iterator it2 = idk.begin(); it2 != idk.end(); it2++ ){
                file<<*it2<<" " ;
            }
            file<<std::endl;
        }

    }

    file.close();
    
}
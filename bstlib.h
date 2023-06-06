#ifndef BST_INCLUDED
#define BST_INCLUDED

#include <vector>
#include <string>
#include <type_traits>
#include <algorithm>
#include <cstdlib>
#include <iostream>

namespace mine {
    // tool
    template <typename T>
    bool myLess (std::pair<int, T> x, std::pair<int, T> y) {
        return x.first<y.first;
    }

    int stn (std::string x) {
        int y = 0;
        for (auto& el : x) {
            y+=static_cast<int>(el);
        }
        return y;
    }

    template <class Key,
              class T>
    class map {
        public:
            Key k;
            T val;
            map<int, T>* left = nullptr;
            map<int, T>* right = nullptr;

            // tool
            map<int, T>* searchNode(map<int, T>* root, int toFind) {
                if (toFind==root->k) return root;
                if (toFind<root->k) return searchNode(root->left, toFind);
                if (toFind>root->k) return searchNode(root->right, toFind);
            }

            void createTree (std::vector<T>& v) {
                int vsize = v.size();
                int mid = vsize / 2;
                if (vsize == 0) return;

                this->k = v[mid];
                this->val = 0;

                if (vsize != 1) {
                    std::vector<T> left_(v.begin(), v.begin() + mid);
                    std::vector<T> right_(v.begin() + mid + 1, v.end());

                    this->left = new map<Key, T> ();
                    this->left->createTree(left_);
                    this->right = new map<Key, T> ();
                    this->right->createTree(right_);
                }
            }

            void createTree (std::vector<std::pair<int, T>>& v) {
                int vsize = v.size();
                int mid = vsize / 2;
                if (vsize == 0) return;

                this->k = v[mid].first;
                this->val = v[mid].second;

                if (vsize != 1) {
                    std::vector<std::pair<int, T>> left_(v.begin(), v.begin() + mid);
                    std::vector<std::pair<int, T>> right_(v.begin() + mid + 1, v.end());

                    this->left = new map<int, T> ();
                    this->left->createTree(left_);
                    this->right = new map<int, T> ();
                    this->right->createTree(right_);
                }
            }

            map () {}
            map (T val_) : val(val_), left(nullptr), right(nullptr) {}
            map (T val_, map* left_) : val(val_), left(left_), right(nullptr) {}
            map (T val_, map* left_, map* right_) : val(val_), left(left_), right(right_) {}
            map (std::vector<T>& v) {
                sort(v.begin(), v.end());
                createTree(v);
            }
            map (std::initializer_list<std::pair<Key, T>> tmp) {
                std::vector<std::pair<int, T>> v;
                if (typeid(Key).name()==typeid(std::string).name() || typeid(Key).name()==typeid(char).name()) {
                    for (auto& el : tmp) {
                        std::pair<int, T> new_p = {stn(el.first), el.second};
                        v.push_back(new_p);
                    }
                } else {

                }

                sort(v.begin(), v.end(), mine::myLess<T>);
                createTree(v);
            }

            // utility
            T& operator[](Key toFind) {
                int new_toFind;
                int new_k;
                if (typeid(Key).name()==typeid(std::string).name()|| typeid(Key).name()==typeid(char).name()) {
                    new_toFind = stn(toFind);
                    new_k = stn(k);
                } else {}

                if (new_toFind==new_k) return this->val;
                if (new_toFind<new_k) return searchNode(left, new_toFind)->val;
                return searchNode(right, new_toFind)->val;
            }

    };

    template <typename Key,
              typename T>
    void printTree(map<Key, T>* root) {
        if (root==nullptr) return;
        if (root==NULL) return;


        std::cout<<root->k<<" "<<root->val<<std::endl;
        printTree(root->left);
        printTree(root->right);
    }

}

#endif

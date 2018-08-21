/*************************************************************************
    > File Name: huffman.cpp
    > Author:     linhaidong
    > Mail:       linhaidong@alibaba-inc.com 
    > Time:      2018年06月27日 16时21分18秒 CST
    > Abstract: 
 ************************************************************************/
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>

using namespace std;
#define MAX_LINE 512
#define LEN 512

struct huffman_node{
        char c;
        int weight;
        char huffman_code[LEN];
        huffman_node * left;
        huffman_node * right;
};

bool sort_by_weight(huffman_node * n1, huffman_node *n2)
{
   return n1->weight < n2->weight;
}


void print_map(map<char, int> &word)
{
    map<char, int>::iterator it;
    for (it = word.begin(); it != word.end(); it++) {
        cout<<it->second<<", "; 
    }
    cout<<endl;
}

void print_vectot(vector<huffman_node *> vec)
{
    vector<huffman_node *>::iterator it;
    for (it = vec.begin(); it != vec.end(); it++) {
        cout<<"("<<(*it)->c<<(*it)->weight<<")"<<", "; 
    }
    cout<<endl;
}
/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 *
 * @Param root
 * @Param word
 *
 * @Returns   
 */
/* ----------------------------------------------------------------------------*/
int huffman_tree_create(huffman_node *&root, map<char, int> &word){
        char line[MAX_LINE];

        vector<huffman_node *> huffman_tree_node;

        map<char, int>::iterator it_t;
        for (it_t = word.begin(); it_t != word.end(); it_t++){
                huffman_node *node = (huffman_node *)malloc(sizeof(huffman_node));
                node->c = it_t->first;
                node->weight = it_t->second;
                node->left = NULL;
                node->right = NULL;
                huffman_tree_node.push_back(node);
        }


        // 开始从叶节点开始构建Huffman树
        while (huffman_tree_node.size() > 0){
                // 按照weight升序排序
                sort(huffman_tree_node.begin(), huffman_tree_node.end(), sort_by_weight);
                print_vectot(huffman_tree_node);
                // 取出前两个节点
                if (huffman_tree_node.size() == 1) {// 只有一个根结点
                        root = huffman_tree_node[0];
                        huffman_tree_node.erase(huffman_tree_node.begin());
                }else{
                        //get begin two node, as new node
                        huffman_node *node_1 = huffman_tree_node[0];
                        huffman_node *node_2 = huffman_tree_node[1];
                        // delete bengin two small  node
                        huffman_tree_node.erase(huffman_tree_node.begin());
                        huffman_tree_node.erase(huffman_tree_node.begin());
                        //generate new node 
                        huffman_node *node = (huffman_node *)malloc(sizeof(huffman_node));
                        node->weight = node_1->weight + node_2->weight;
                        (node_1->weight < node_2->weight)?(node->left=node_1,node->right=node_2):(node->left=node_2,node->right=node_1);
                        huffman_tree_node.push_back(node);
                }
        }

        return 0;
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  把字符添加到map中
 *
 * @Param fn  文件
 * @Param word 存储字符的map, key 为字符，int 为字符出现的次数
 *
 * @Returns   
 */
/* ----------------------------------------------------------------------------*/
int read_file(FILE *fn, map<char, int> &word){
        if (fn == NULL) return 1;
        char line[MAX_LINE];
        while (fgets(line, 1024, fn)){
                fprintf(stderr, "%s\n", line);
                char *p = line;
                while (*p != '\0' && *p != '\n'){
                        map<char, int>::iterator it = word.find(*p);
                        if (it == word.end()){
                                word.insert(make_pair(*p, 1));
                        }else{
                                it->second ++;
                        }
                        p++;
                }
        }
        return 0;
}



void destory_huffman_tree(huffman_node *node){
        if (node != NULL){
                destory_huffman_tree(node->left);
                destory_huffman_tree(node->right);
                free(node);
                node = NULL;
        }
}


/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  层次遍历，上判下
 *            上面的节点，有左孩子，拷贝节点的编码到左孩子的编码，并在结尾编码添加0
 *            上面的节点，有右孩子，拷贝节点的编码到右孩子的编码，并在结尾编码添加1
 *
 * @Param node
 *
 * @Returns   
 */
/* ----------------------------------------------------------------------------*/
int get_huffman_code(huffman_node *&node){
        if (node == NULL) return 1;
        // 利用层次遍历，构造每一个节点
        huffman_node *p = node;
        queue<huffman_node *> q;
        q.push(p);
        while(q.size() > 0){
                //自左到右层次遍历
                p = q.front();
                q.pop();
                if (p->left != NULL){
                        //层次遍历，添加到队列
                        q.push(p->left);
                        //拷贝本节点编码到子节点
                        strcpy((p->left)->huffman_code, p->huffman_code);
                        char *ptr = (p->left)->huffman_code;
                        while (*ptr != '\0'){
                                ptr ++;
                        }
                        //左孩子节点，编码添加0
                        *ptr = '0';
                }
                if (p->right != NULL){
                        q.push(p->right);
                        strcpy((p->right)->huffman_code, p->huffman_code);
                        char *ptr = (p->right)->huffman_code;
                        while (*ptr != '\0'){
                                ptr ++;
                        }
                        //右孩子节点，编码添加1
                        *ptr = '1';
                }
        }
        return 0;
}



/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 *
 * @Param node
 */
/* ----------------------------------------------------------------------------*/
void print_huffman_pre(huffman_node *node){
        if (node != NULL){
                fprintf(stderr, "%c\t%d\n", node->c, node->weight);
                print_huffman_pre(node->left);
                print_huffman_pre(node->right);
        }
}


/* --------------------------------------------------------------------------*/
/**
 * @Synopsis 中序遍历 
 *
 * @Param node
 */
/* ----------------------------------------------------------------------------*/
void print_huffman_in(huffman_node *node){
        if (node != NULL){
                print_huffman_in(node->left);
                fprintf(stderr, "%c\t%d\n", node->c, node->weight);
                print_huffman_in(node->right);
        }
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 *
 * @Param node
 */
/* ----------------------------------------------------------------------------*/
void print_leaf(huffman_node *node){
        if (node != NULL){
                print_leaf(node->left);
                if (node->left == NULL && node->right == NULL) 
                    fprintf(stderr, "%c\t%s\n", node->c, node->huffman_code);
                print_leaf(node->right);
        }
}

int main(){
    // 读文件
    FILE *fn = fopen("huffman", "r");
    huffman_node *root = NULL;
    map<char, int> word;
    read_file(fn, word);
    huffman_tree_create(root, word);
    fclose(fn);
    fprintf(stderr, "pre-order:\n");
    print_huffman_pre(root);
    fprintf(stderr, "in-order:\n");
    print_huffman_in(root);

    get_huffman_code(root);
    fprintf(stderr, "the final result:\n");
    print_leaf(root);
    destory_huffman_tree(root);
    return 0;
}

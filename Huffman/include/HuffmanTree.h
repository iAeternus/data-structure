/**
 * @brief 哈夫曼树
 * @author Ricky
 * @date 2023/11/7
 * @version 1.0
 */
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>

#define MYLIB_BEGIN \
    namespace mylib \
    {
#define MYLIB_END }

// #define ADMINISTRATOR

MYLIB_BEGIN
class HuffmanTree
{
private:
    struct HuffmanTreeNode
    {
        HuffmanTreeNode() : 
            value('\0'), weight(0), parent(nullptr), left(nullptr), right(nullptr)
        {}

        HuffmanTreeNode(char value, int weight, HuffmanTreeNode *parent = nullptr, HuffmanTreeNode *left = nullptr, HuffmanTreeNode *right = nullptr) : 
            value(value), weight(weight), parent(parent), left(left), right(right)
        {}

        char value;                             // 存储的字符
        int weight;                             // 字符出现的次数
        HuffmanTreeNode *parent, *left, *right; // 父亲节点，左孩子，右孩子
    };
    using Node = HuffmanTreeNode;

    struct Comperator
    {
        bool operator()(Node *const node1, Node *const node2)
        {
            return node1->weight > node2->weight;
        }
    };

public:
    HuffmanTree() :
        root(nullptr)
    {}

    std::string encode(const std::string &filePath)
    {
        std::string code;
        std::string text = read(filePath);
        this->root = buildHuffmanTree(text);
        getKeys(root, "");

#ifdef ADMINISTRATOR
        std::cout << "keys = \n";
        for (const auto &key : keys)
        {
            std::cout << key.first << '\t' << key.second << std::endl;
        }
#endif

        for (char c : text)
        {
            code += keys[c];
        }
        return code;
    }

    std::string decode(const std::string& filePath)
    {
        std::string code = read(filePath);

        std::string text;
        Node* p = root;
        for(char c : code)
        {
            if(c == '0')
            {
                p = p->left;
            }
            else if(c == '1')
            {
                p = p->right;
            }
            else
            {
                throw std::runtime_error("Illegal coding!");
            }

            if(!p->left && !p->right)
            {
                text += p->value;
                p = root;
            }
        }

        return text;
    }

private:
    Node* root;                       // 根节点
    std::map<char, std::string> keys; // 密钥

    // 读取文件内容
    std::string read(const std::string &filePath)
    {
        std::string text;
        std::ifstream in(filePath);
        if (!in.is_open())
        {
            throw std::runtime_error("Failed to open the file: " + filePath);
        }
        
        try
        {
            std::string line;
            while (std::getline(in, line))
            {
                text += line;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error while reading the file: " << e.what() << std::endl;
        }

        return text;
    }

    // 写文件
    void write(const std::string &filePath, const std::string &content)
    {
        std::ofstream out(filePath);

        if (!out.is_open())
        {
            throw std::runtime_error("Failed to open the file for writing: " + filePath);
        }

        try
        {
            out << content;
            if (out.fail())
            {
                throw std::runtime_error("Error writing to the file: " + filePath);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error while writing to the file: " << e.what() << std::endl;
        }
    }

    // 映射哈希表
    static void getHash(const std::string& text, std::vector<int>& frequencies)
    {
        for (char c : text)
        {
            ++frequencies[static_cast<int>(c)];
        }
    }

    // 创建哈夫曼树节点
    static void creatHuffmanNode(std::priority_queue<Node*, std::vector<Node*>, Comperator>& q, const std::vector<int>& frequencies)
    {
        for (int i = 0; i < 128; i++)
        {
            if (frequencies[i] > 0)
            {
                Node *node = new Node();
                node->value = static_cast<char>(i);
                node->weight = frequencies[i];
                q.push(node);
            }
        }
    }

    Node *buildHuffmanTree(const std::string& text)
    {
        std::vector<int> frequencies(128, 0);
        getHash(text, frequencies);

        std::priority_queue<Node*, std::vector<Node*>, Comperator> q;
        creatHuffmanNode(q, frequencies);        

        int n = q.size();
        for (int i = 1; i < n; i++)
        {
            Node *x = q.top();
            q.pop();
            Node *y = q.top();
            q.pop();
            Node *z = new Node('0', x->weight + y->weight, nullptr, x, y);
            q.push(z);
        }
        return q.top();
    }

    void getKeys(Node *node, std::string code)
    {
        if (node)
        {
            if (!node->left && !node->right)
            {
                keys[node->value] = code;
            }

            getKeys(node->left, code + "0");
            getKeys(node->right, code + "1");
        }
    }
};
MYLIB_END // mylib
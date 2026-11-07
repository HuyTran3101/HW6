#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <string>

// Assignment 6: represent node colors using integers.
#define COLOR_RED 0
#define COLOR_BLACK 1

class RedBlackTree {
public:
    RedBlackTree();
    explicit RedBlackTree(int value);
    RedBlackTree(const RedBlackTree& other); 
    RedBlackTree& operator=(const RedBlackTree& other);
    ~RedBlackTree();

    void Insert(int value);

    // Searching and extrema take one path through the balanced tree.
    bool Contains(int value) const;
    int GetMin() const;
    int GetMax() const;
    unsigned long long int Size() const { return numItems; }

    // Required traversal formats; useful for testing Insert().
    std::string ToInfixString() const { return ToInfixString(root); }
    std::string ToPrefixString() const { return ToPrefixString(root); }
    std::string ToPostfixString() const { return ToPostfixString(root); }

    // Remove() belongs to Part 2

private:
    struct RBTNode {
        int data;
        int color;
        RBTNode* left;
        RBTNode* right;
        RBTNode* parent;

        explicit RBTNode(int value) : data(value), color(COLOR_RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    unsigned long long int numItems = 0;
    RBTNode* root = nullptr;

    void RotateLeft(RBTNode* node);
    void RotateRight(RBTNode* node);
    void FixInsert(RBTNode* node);

    std::string ToInfixString(RBTNode* node) const;
    std::string ToPrefixString(RBTNode* node) const;
    std::string ToPostfixString(RBTNode* node) const;

    void DeleteSubtree(RBTNode* node);
    RBTNode* CopySubtree(const RBTNode* node, RBTNode* parent);
};

#endif

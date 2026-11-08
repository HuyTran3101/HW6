// Implementation assistance: OpenAI ChatGPT, November 3, 2026.
// Insertion follows the standard red-black-tree insertion, recoloring, and rotation cases.
#include "RedBlackTree.h"

#include <stdexcept>
#include <string>
#include <utility>

// Additional implementation assistance: OpenAI ChatGPT, November 6, 2026.
// Copy nodes directly to preserve both the original shape and colors.
RedBlackTree::RBTNode* RedBlackTree::CopySubtree(const RBTNode* node, RBTNode* parent) {
    if (node == nullptr) return nullptr;
    RBTNode* copy = new RBTNode(node->data);
    copy->color = node->color;
    copy->parent = parent;
    try {
        copy->left = CopySubtree(node->left, copy);
        copy->right = CopySubtree(node->right, copy);
    } catch (...) {
        // A failed allocation must not leak a partially constructed copy.
        DeleteSubtree(copy);
        throw;
    }
    return copy;
}

RedBlackTree::RedBlackTree(const RedBlackTree& other)
    : numItems(other.numItems), root(CopySubtree(other.root, nullptr)) {}

RedBlackTree& RedBlackTree::operator=(const RedBlackTree& other) {
    // Copy before swapping so self-assignment and allocation failure are safe.
    RedBlackTree copy(other);
    std::swap(root, copy.root);
    std::swap(numItems, copy.numItems);
    return *this;
}

bool RedBlackTree::Contains(int value) const {
    const RBTNode* current = root;
    while (current != nullptr) {
        if (value == current->data) return true;
        current = value < current->data ? current->left : current->right;
    }
    return false;
}

int RedBlackTree::GetMin() const {
    if (root == nullptr) throw std::invalid_argument("Empty tree has no minimum");
    const RBTNode* current = root;
    while (current->left != nullptr) current = current->left;
    return current->data;
}

int RedBlackTree::GetMax() const {
    if (root == nullptr) throw std::invalid_argument("Empty tree has no maximum");
    const RBTNode* current = root;
    while (current->right != nullptr) current = current->right;
    return current->data;
}

// Constructor: an empty tree has no root.
RedBlackTree::RedBlackTree() = default;

// Optional constructor used by the provided tests.
RedBlackTree::RedBlackTree(int value) {
    Insert(value);
}

RedBlackTree::~RedBlackTree() {
    DeleteSubtree(root);
}

void RedBlackTree::DeleteSubtree(RBTNode* node) {
    if (node == nullptr) return;
    DeleteSubtree(node->left);
    DeleteSubtree(node->right);
    delete node;
}

void RedBlackTree::Insert(int value) {
    RBTNode* parent = nullptr;
    RBTNode* current = root;

    // First insert like an ordinary BST: follow left/right pointers.
    while (current != nullptr) {
        parent = current;

        if (value < current->data) {
            current = current->left;
        } else if (value > current->data) {
            current = current->right;
        } else {
            // The assignment requires an exception for duplicate values.
            throw std::invalid_argument("Value is already in the tree");
        }
    }

    // New nodes start RED, but FixInsert may recolor them.
    RBTNode* node = new RBTNode(value);
    node->parent = parent;

    if (parent == nullptr) {
        root = node;
    } else if (value < parent->data) {
        parent->left = node;
    } else {
        parent->right = node;
    }

    ++numItems;
    FixInsert(node);
}

void RedBlackTree::RotateLeft(RBTNode* node) {
    // The right child moves UP; node moves DOWN to its left.
    RBTNode* rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left != nullptr) {
        rightChild->left->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;
}

void RedBlackTree::RotateRight(RBTNode* node) {
    // The left child moves UP; node moves DOWN to its right.
    RBTNode* leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right != nullptr) {
        leftChild->right->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = leftChild;
    } else if (node == node->parent->left) {
        node->parent->left = leftChild;
    } else {
        node->parent->right = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;
}

void RedBlackTree::FixInsert(RBTNode* node) {
    // A RED parent and RED child violate the RB-tree properties.
    while (node != root && node->parent->color == COLOR_RED) {
        RBTNode* parent = node->parent;
        RBTNode* grandparent = parent->parent;

        if (parent == grandparent->left) {
            RBTNode* uncle = grandparent->right;

            if (uncle != nullptr && uncle->color == COLOR_RED) {
                // RED uncle: recolor and check higher in the tree.
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    // Left-Right -> Left-Left.
                    node = parent;
                    RotateLeft(node);
                }
                // Left-Left: rotate right at grandparent.
                node->parent->color = COLOR_BLACK;
                node->parent->parent->color = COLOR_RED;
                RotateRight(node->parent->parent);
            }
        } else {
            RBTNode* uncle = grandparent->left;

            if (uncle != nullptr && uncle->color == COLOR_RED) {
                // Symmetric RED-uncle case.
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    // Right-Left -> Right-Right.
                    node = parent;
                    RotateRight(node);
                }
                // Right-Right: rotate left at grandparent.
                node->parent->color = COLOR_BLACK;
                node->parent->parent->color = COLOR_RED;
                RotateLeft(node->parent->parent);
            }
        }
    }

    // The root must be BLACK, even after a recoloring propagates upward.
    root->color = COLOR_BLACK;
}

// Each node prints with leading and trailing spaces, e.g. " B30 ".
static std::string NodeLabel(int value, int color) {
    return std::string(" ") + (color == COLOR_RED ? "R" : "B")
           + std::to_string(value) + " ";
}

std::string RedBlackTree::ToInfixString(RBTNode* node) const {
    if (node == nullptr) return "";
    return ToInfixString(node->left)
           + NodeLabel(node->data, node->color)
           + ToInfixString(node->right);
}

std::string RedBlackTree::ToPrefixString(RBTNode* node) const {
    if (node == nullptr) return "";
    return NodeLabel(node->data, node->color)
           + ToPrefixString(node->left)
           + ToPrefixString(node->right);
}

std::string RedBlackTree::ToPostfixString(RBTNode* node) const {
    if (node == nullptr) return "";
    return ToPostfixString(node->left)
           + ToPostfixString(node->right)
           + NodeLabel(node->data, node->color);
}

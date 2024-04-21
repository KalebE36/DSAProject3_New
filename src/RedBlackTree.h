#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <iostream>
#include <queue>
using namespace std;


// Red-Black Tree implementation
template <typename Key, typename Value>
class RedBlackTree {
public:
    static const bool RED = true;     // Constant representing red color
    static const bool BLACK = false;  // Constant representing black color

    // Node structure representing elements in the tree
    struct Node {
        Key key;                      // Key of the node
        Value value;                  // Value associated with the key
        Node* left = nullptr;         // Pointer to the left child node
        Node* right = nullptr;        // Pointer to the right child node
        Node* parent = nullptr;       // Pointer to the parent node
        bool isRed = RED;             // Color of the node, true for red and false for black

        // Constructor initializing key and value
        //Node(Key k, Value v) : key(k), value(v) {}
        Node(Key k, Value v, bool isRed = true) : key(k), value(v), isRed(isRed) {}

    };
    Node* root;                       // Pointer to the root node of the tree

    // Constructor
    RedBlackTree() : root(nullptr) {}

    // Copy constructor
    RedBlackTree(const RedBlackTree& other) {
        root = copySubtree(other.root);
    }

    // Assignment operator
    RedBlackTree& operator=(const RedBlackTree& other) {
        if (this != &other) {
            clear(root);
            root = copySubtree(other.root);
        }
        return *this;
    }

    // Destructor
    ~RedBlackTree() {
        clear(root);
    }

    void insert(const Key& key, const Value& value);        // Method to insert a key-value pair into the tree
    bool remove(const Key& key);                            // Method to remove a key from the tree
    Value* search(const Key& key) const;                    // Method to search for a key in the tree and return its value
    Node* searchNode(const Key& key) const;                 // Method to search for a node with a given key in the tree
    void inOrderTraversal() const;                          // Traversal methods
    void preOrderTraversal() const;
    void postOrderTraversal() const;
    void levelOrderTraversal() const;
    vector<Value> getAllValues() const;                     // Method to retrieve all values from the tree in sorted order


private:
    // Helper functions
    Node* copySubtree(Node* node);
    void clear(Node* node);
    void insertFixUp(Node* node);
    void deleteFixUp(Node* node);
    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    void transplant(Node* u, Node* v);
    Node* minimum(Node* node) const;
    Node* maximum(Node* node) const;
    void inOrderHelper(Node* node) const;
    void preOrderHelper(Node* node) const;
    void postOrderHelper(Node* node) const;
    void levelOrderHelper(Node* node) const;
    void getAllValuesHelper(Node* node, vector<Value>& values) const;

};



// Method to insert a new key-value pair into the Red-Black Tree
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insert(const Key& key, const Value& value) {
    Node* newNode = new Node(key, value);           // Create a new node with the given key and value

    // Initialize variables for traversal
    Node* parentNode = nullptr;
    Node* currentNode = this->root;

    // Traverse the tree to find the appropriate position for the new node
    while (currentNode != nullptr) {
        // Store the current node as the parent node
        parentNode = currentNode;

        // Determine whether to move left or right based on the key comparison
        if (newNode->key < currentNode->key) {
            currentNode = currentNode->left;
        }
        else {
            currentNode = currentNode->right;
        }
    }

    // Set the parent of the new node
    newNode->parent = parentNode;

    // Update the appropriate child pointer of the parent node
    if (parentNode == nullptr) {
        root = newNode;
    }
    else if (newNode->key < parentNode->key) {
        parentNode->left = newNode;
    }
    else {
        parentNode->right = newNode;
    }

    // Set the color of the new node to red
    newNode->isRed = true;

    // Fix any violations of the Red-Black Tree properties caused by the insertion
    insertFixUp(newNode);
}


template <typename Key, typename Value>
void RedBlackTree<Key, Value>::clear(Node* node) {
    if (node) {
        clear(node->left);  // Recursively clear the left subtree
        clear(node->right); // Recursively clear the right subtree
        delete node;        // Delete the current node
    }
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::Node* RedBlackTree<Key, Value>::copySubtree(Node* node) {
    if (node == nullptr) return nullptr; // Base case: If the node is null, return null.

    Node* newNode = new Node(node->key, node->value, node->isRed); // Copy the node
    newNode->left = copySubtree(node->left);    // Recursively copy the left subtree
    newNode->right = copySubtree(node->right);  // Recursively copy the right subtree

    // Set the parent pointers of the new child nodes
    if (newNode->left != nullptr) newNode->left->parent = newNode;
    if (newNode->right != nullptr) newNode->right->parent = newNode;

    return newNode; // Return the newly created subtree root
}



// Method to fix any violations of the Red-Black Tree properties caused by inserting a node
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insertFixUp(Node* node) {
    // Continue fixing violations until the node becomes the root or its parent is black
    while (node != root && node->parent->isRed) {
        Node* grandparent = node->parent->parent;

        // Safety check to ensure grandparent is not null before using it
        if (!grandparent) {
            break; // Should not normally happen, as parent of root should not be red
        }

        // If the parent is the left child of the grandparent
        if (node->parent == grandparent->left) {
            Node* uncle = grandparent->right;

            // Case 1: Uncle is red
            if (uncle && uncle->isRed) {
                // Recolor nodes
                node->parent->isRed = BLACK;
                uncle->isRed = BLACK;
                grandparent->isRed = RED;
                node = grandparent;                 // Move up to the grandparent
            }
            else {
                // Case 2: Uncle is black and current node is a right child
                if (node == node->parent->right) {
                    node = node->parent;            // Move up to the parent
                    rotateLeft(node);               // Perform left rotation
                }
                // Case 3: Uncle is black and current node is a left child
                if (grandparent) { // Additional check for safety
                    node->parent->isRed = BLACK;
                    grandparent->isRed = RED;
                    rotateRight(grandparent);           // Perform right rotation
                }
            }
        }
        // If the parent is the right child of the grandparent
        else {
            Node* uncle = grandparent->left;

            // Case 1: Uncle is red
            if (uncle && uncle->isRed) {
                // Recolor nodes
                node->parent->isRed = BLACK;
                uncle->isRed = BLACK;
                grandparent->isRed = RED;
                node = grandparent;                 // Move up to the grandparent
            }
            else {
                // Case 2: Uncle is black and current node is a left child
                if (node == node->parent->left) {
                    node = node->parent;            // Move up to the parent
                    rotateRight(node);              // Perform right rotation
                }
                // Case 3: Uncle is black and current node is a right child
                if (grandparent) { // Additional check for safety
                    node->parent->isRed = BLACK;
                    grandparent->isRed = RED;
                    rotateLeft(grandparent);            // Perform left rotation
                }
            }
        }
    }
    root->isRed = BLACK;    // Ensure the root is black to maintain Red-Black Tree properties
}


// Method to remove a node with a given key from the Red-Black Tree
template <typename Key, typename Value>
bool RedBlackTree<Key, Value>::remove(const Key& key) {
    // Search for the node to delete
    Node* nodeToDelete = searchNode(key);
    if (!nodeToDelete) return false;                                // If node not found, return false

    Node* childNode = nullptr;                                      // Initialize pointer to child node
    Node* replacementNode = nodeToDelete;                           // Initialize replacement node to the node to delete
    bool originalColor = replacementNode->isRed;                    // Store original color of replacement node

    // Determine the child node based on the presence of left and right children
    if (nodeToDelete->left == nullptr) {
        childNode = nodeToDelete->right;                            // If left child is null, set child node to right child
        transplant(nodeToDelete, nodeToDelete->right);              // Replace nodeToDelete with its right child
    }
    else if (nodeToDelete->right == nullptr) {
        childNode = nodeToDelete->left;                             // If right child is null, set child node to left child
        transplant(nodeToDelete, nodeToDelete->left);               // Replace nodeToDelete with its left child
    }
    else {
        // If the node to delete has both left and right children
        replacementNode = minimum(nodeToDelete->right);             // Find the successor node
        originalColor = replacementNode->isRed;                     // Store original color of the successor node
        childNode = replacementNode->right;                         // Get the child node of the successor

        // If the successor is the right child of the node to delete
        if (replacementNode->parent == nodeToDelete) {
            if (childNode) childNode->parent = replacementNode;     // Set the parent of the child node to the replacement node
        }
        else {
            // Perform transplant operation
            transplant(replacementNode, replacementNode->right);    // Replace the replacement node with its right child
            replacementNode->right = nodeToDelete->right;           // Update right child of replacement node
            replacementNode->right->parent = replacementNode;       // Update parent of right child
        }

        // Perform transplant operation
        transplant(nodeToDelete, replacementNode);                  // Replace nodeToDelete with the successor node
        replacementNode->left = nodeToDelete->left;                 // Update left child of replacement node
        replacementNode->left->parent = replacementNode;            // Update parent of left child
        replacementNode->isRed = nodeToDelete->isRed;               // Update color of replacement node
    }

    delete nodeToDelete;                                            // Delete the node

    // If the original color was black, fix any violations of Red-Black Tree properties
    if (!originalColor) {
        deleteFixUp(childNode);                                     // Fix violations starting from the child node
    }

    return true;                                                    // Return true if deletion is successful 
}




// Method to search for a key in the Red-Black Tree and return its value if found, otherwise return nullptr
template <typename Key, typename Value>
Value* RedBlackTree<Key, Value>::search(const Key& key) const {
    Node* node = searchNode(key);                   // Search for the node with the given key
    return node ? &(node->value) : nullptr;         // If node found, return a pointer to its value, otherwise return nullptr
}

// Method to search for a node with a given key in the Red-Black Tree and return a pointer to it
template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::Node* RedBlackTree<Key, Value>::searchNode(const Key& key) const {
    Node* node = root;                              // Start searching from the root node
    while (node != nullptr) {
        if (key < node->key) {
            node = node->left;                      // If key is less than current node's key, move to the left child
        }
        else if (key > node->key) {
            node = node->right;                     // If key is greater than current node's key, move to the right child
        }
        else {
            return node;                            // If key matches current node's key, return pointer to the node
        }
    }
    return nullptr;                                 // If key not found, return nullptr
}



// Method to perform an in-order traversal of the Red-Black Tree starting from the root node
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::inOrderTraversal() const {
    inOrderHelper(root); // Call the helper function to perform in-order traversal
}

// Method to perform a pre-order traversal of the Red-Black Tree starting from the root node
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::preOrderTraversal() const {
    preOrderHelper(root); // Call the helper function to perform pre-order traversal
}

// Method to perform a post-order traversal of the Red-Black Tree starting from the root node
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::postOrderTraversal() const {
    postOrderHelper(root); // Call the helper function to perform post-order traversal
}

// Method to perform a level-order traversal of the Red-Black Tree starting from the root node
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::levelOrderTraversal() const {
    levelOrderHelper(root); // Call the helper function to perform level-order traversal
}


// Helper method for in-order traversal of the Red-Black Tree
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::inOrderHelper(Node* node) const {
    if (node != nullptr) {
        inOrderHelper(node->left);                              // Visit left child
        std::cout << "Key: " << node->key << ", Name: " << node->value.name << std::endl;  // Process current node's name
        inOrderHelper(node->right);                             // Visit right child
    }
}

// Helper method for pre-order traversal of the Red-Black Tree
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::preOrderHelper(Node* node) const {
    if (node != nullptr) {
        std::cout << "Key: " << node->key << ", Name: " << node->value.name << std::endl;
        preOrderHelper(node->left);     // Visit left child
        preOrderHelper(node->right);    // Visit right child
    }
}

// Helper method for post-order traversal of the Red-Black Tree
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::postOrderHelper(Node* node) const {
    if (node != nullptr) {
        postOrderHelper(node->left);    // Visit left child
        postOrderHelper(node->right);   // Visit right child
        std::cout << "Key: " << node->key << ", Name: " << node->value.name << std::endl;
    }
}


// Helper method for level-order traversal of the Red-Black Tree
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::levelOrderHelper(Node* node) const {
    if (!node) return;                                      // If node is null, return
    std::queue<Node*> q;                                    // Create a queue for level-order traversal
    q.push(node);                                           // Push the root node into the queue

    // Perform level-order traversal
    while (!q.empty()) {
        Node* current = q.front();                          // Get the front node of the queue
        q.pop();                                            // Remove the front node from the queue
        std::cout << "Key: " << current->key << ", Name: " << current->value.name << ", Description: "<< current->value.description <<std::endl;

        // Enqueue left and right children if they exist
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
}


// Method to perform a left rotation in the Red-Black Tree
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::rotateLeft(Node* currentNode) {
    Node* rightChild = currentNode->right;                  // Store the right child of the current node as 'rightChild'
    currentNode->right = rightChild->left;                  // Make the left child of 'rightChild' the right child of 'currentNode'

    // Update the parent pointer of the left child of 'rightChild'
    if (rightChild->left != nullptr) {
        rightChild->left->parent = currentNode;
    }

    rightChild->parent = currentNode->parent;               // Update the parent pointer of 'rightChild'

    // If 'currentNode' is the root of the tree, update the root to 'rightChild'
    if (currentNode->parent == nullptr) {
        root = rightChild;
    }
    // If 'currentNode' is a left child, update the left child of its parent to 'rightChild'
    else if (currentNode == currentNode->parent->left) {
        currentNode->parent->left = rightChild;
    }
    // If 'currentNode' is a right child, update the right child of its parent to 'rightChild'
    else {
        currentNode->parent->right = rightChild;
    }

    rightChild->left = currentNode;                         // Make 'currentNode' the left child of 'rightChild'
    currentNode->parent = rightChild;                       // Update the parent pointer of 'currentNode' to 'rightChild'
}



// Method to perform a right rotation in the Red-Black Tree
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::rotateRight(Node* currentNode) {
    Node* leftChild = currentNode->left;                // Store the left child of the current node as 'leftChild'
    currentNode->left = leftChild->right;               // Make the right child of 'leftChild' the left child of 'currentNode'

    // Update the parent pointer of the right child of 'leftChild'
    if (leftChild->right != nullptr) {
        leftChild->right->parent = currentNode;
    }

    leftChild->parent = currentNode->parent;            // Update the parent pointer of 'leftChild'

    // If 'currentNode' is the root of the tree, update the root to 'leftChild'
    if (currentNode->parent == nullptr) {
        root = leftChild;
    }
    // If 'currentNode' is a right child, update the right child of its parent to 'leftChild'
    else if (currentNode == currentNode->parent->right) {
        currentNode->parent->right = leftChild;
    }
    // If 'currentNode' is a left child, update the left child of its parent to 'leftChild'
    else {
        currentNode->parent->left = leftChild;
    }

    leftChild->right = currentNode;                     // Make 'currentNode' the right child of 'leftChild'
    currentNode->parent = leftChild;                    // Update the parent pointer of 'currentNode' to 'leftChild'
}

// Method to transplant a node in the Red-Black Tree
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::transplant(Node* oldNode, Node* newNode) {
    if (oldNode->parent == nullptr) {
        root = newNode;                                 // If 'oldNode' is the root, update the root to 'newNode'
    }
    else if (oldNode == oldNode->parent->left) {
        oldNode->parent->left = newNode;                // If 'oldNode' is a left child, update its parent's left child to 'newNode'
    }
    else {
        oldNode->parent->right = newNode;               // If 'oldNode' is a right child, update its parent's right child to 'newNode'
    }

    if (newNode != nullptr) {
        newNode->parent = oldNode->parent;              // Update the parent pointer of 'newNode' to 'oldNode's parent
    }
}


// Method to fix violations in Red-Black Tree after deletion
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::deleteFixUp(Node* currentNode) {
    while (currentNode != root && !currentNode->isRed) {
        // Case where currentNode is a left child
        if (currentNode == currentNode->parent->left) {
            Node* siblingNode = currentNode->parent->right;         // Store sibling node of currentNode as 'siblingNode'

            // Case where siblingNode is red
            if (siblingNode->isRed) {
                siblingNode->isRed = false;                         // Color siblingNode black
                currentNode->parent->isRed = true;                  // Color currentNode's parent red
                rotateLeft(currentNode->parent);                    // Perform left rotation on currentNode's parent
                siblingNode = currentNode->parent->right;           // Update siblingNode to the right child of currentNode's parent
            }

            // Case where siblingNode's children are both black
            if (!siblingNode->left->isRed && !siblingNode->right->isRed) {
                siblingNode->isRed = true;                          // Color siblingNode red
                currentNode = currentNode->parent;                  // Move up to currentNode's parent
            }
            else {
                // Case where siblingNode's right child is black
                if (!siblingNode->right->isRed) {
                    siblingNode->left->isRed = false;               // Color siblingNode's left child black
                    siblingNode->isRed = true;                      // Color siblingNode red
                    rotateRight(siblingNode);                       // Perform right rotation on siblingNode
                    siblingNode = currentNode->parent->right;       // Update siblingNode to the right child of currentNode's parent
                }

                siblingNode->isRed = currentNode->parent->isRed;    // Color siblingNode the same as currentNode's parent
                currentNode->parent->isRed = false;                 // Color currentNode's parent black
                siblingNode->right->isRed = false;                  // Color siblingNode's right child black
                rotateLeft(currentNode->parent);                    // Perform left rotation on currentNode's parent
                currentNode = root;                                 // Update currentNode to root
            }
        }
        // Case where currentNode is a right child
        else {
            Node* siblingNode = currentNode->parent->left;          // Store sibling node of currentNode as 'siblingNode'

            // Case where siblingNode is red
            if (siblingNode->isRed) {
                siblingNode->isRed = false;                         // Color siblingNode black
                currentNode->parent->isRed = true;                  // Color currentNode's parent red
                rotateRight(currentNode->parent);                   // Perform right rotation on currentNode's parent
                siblingNode = currentNode->parent->left;            // Update siblingNode to the left child of currentNode's parent
            }

            // Case where siblingNode's children are both black
            if (!siblingNode->right->isRed && !siblingNode->left->isRed) {
                siblingNode->isRed = true;                          // Color siblingNode red
                currentNode = currentNode->parent;                  // Move up to currentNode's parent
            }
            else {
                // Case where siblingNode's left child is black
                if (!siblingNode->left->isRed) {
                    siblingNode->right->isRed = false;              // Color siblingNode's right child black
                    siblingNode->isRed = true;                      // Color siblingNode red
                    rotateLeft(siblingNode);                        // Perform left rotation on siblingNode
                    siblingNode = currentNode->parent->left;        // Update siblingNode to the left child of currentNode's parent
                }

                siblingNode->isRed = currentNode->parent->isRed;    // Color siblingNode the same as currentNode's parent
                currentNode->parent->isRed = false;                 // Color currentNode's parent black
                siblingNode->left->isRed = false;                   // Color siblingNode's left child black
                rotateRight(currentNode->parent);                   // Perform right rotation on currentNode's parent
                currentNode = root;                                 // Update currentNode to root
            }
        }
    }
    currentNode->isRed = false;                                     // Color currentNode black
}



// Method to find the minimum node in the Red-Black Tree
template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::Node* RedBlackTree<Key, Value>::minimum(Node* currentNode) const {
    if (currentNode == nullptr) return nullptr;                     // Ensure that the passed node is not null
    while (currentNode->left != nullptr) {
        currentNode = currentNode->left;                            // Traverse left until reaching the leftmost node
    }
    return currentNode;                                             // Return the minimum node
}

// Method to find the maximum node in the Red-Black Tree
template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::Node* RedBlackTree<Key, Value>::maximum(Node* currentNode) const {
    if (currentNode == nullptr) return nullptr;                     // Ensure that the passed node is not null
    while (currentNode->right != nullptr) {
        currentNode = currentNode->right;                           // Traverse right until reaching the rightmost node
    }
    return currentNode;                                             // Return the maximum node
}


// This method collects all values from the tree into a vector in sorted order
template <typename Key, typename Value>
vector<Value> RedBlackTree<Key, Value>::getAllValues() const {
    vector<Value> values;                                           // Vector to store values from the tree
    getAllValuesHelper(root, values);                               // Call helper function to perform in-order traversal
    return values;                                                  // Return the vector of values
}

// Helper function to perform in-order traversal and collect values
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::getAllValuesHelper(Node* currentNode, vector<Value>& values) const {
    if (currentNode != nullptr) {
        getAllValuesHelper(currentNode->left, values);              // Traverse left subtree
        values.push_back(currentNode->value);                       // Store the value of the current node
        getAllValuesHelper(currentNode->right, values);             // Traverse right subtree
    }
}



#endif // REDBLACKTREE_H


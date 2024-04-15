#pragma once 
#include <iostream>

//	Properties of a Red-Black Tree
//	A Red - Black Tree is a self - balancing binary search tree with the following properties :
//
// 
//	1. Root Property: The root is black.
//  2. Node Color: Each node is either red or black.
//  3. External property (Leaf Property) : Every leaf (Leaf is a NULL child of a node) is black.
// 
//  4. Internal property (Red Node Property) : The children of a red node are black. Hence possible parent of red node is a black node.
//                        Red nodes can't have red children (no two red nodes can be adjacent).
// 
//  5. Black Height Property:
//          Depth property: All the leaves have the same black depth.
//          Path Property: Every path from root to descendant leaf node (or from a node to its descendant NIL nodes) has the same number of black nodes.
//
// 
// 
//        Key Operations:
//        The most critical operations for maintaining the Red-Black Tree properties are
//        ======================= insertion and deletion =======================
//        as these can potentially violate the Red-Black properties.
//
// 
//        Each of these operations has two stages:
//        - Perform the standard BST (Binary Search Tree) insert or delete.
//        - Fix the tree so that it maintains the Red-Black properties. This might involve a series of rotations and color changes.
// 
//        Insertion
//        Insert the Node: Insert as we would in a regular BST. Nodes are inserted as red.
//        Fix the Red-Black Tree Properties: After insertion, the tree might violate the properties of a Red-Black Tree.
//        We will have to adjust the colors and perform rotations on certain parts of the tree to restore these properties.
//        
// 
//        Rotations
//        Rotations are used to maintain the balance of the tree:
//
//        Left Rotation: Pivot around the node's right child.
//        Right Rotation: Pivot around the node's left child.
//        Rotations help to redistribute the nodes and are key to maintaining the Red-Black Tree properties after insertion and deletion.
//
//        Begin by implementing the insertion and search functionalities.
//        Ensure we can insert nodes and maintain the tree's properties.
//        Test our tree with various inputs to ensure it self-balances as expected.



template <typename Key, typename Value>
class RedBlackTree {
public:
    struct Node {
        Key key;
        Value value;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        bool isRed = true; // New nodes are red by default

        Node(Key k, Value v) : key(k), value(v) {}
    };


    // Helper Function Declarations as public
    void rotateLeft(Node* x);
    void rotateRight(Node* x);
    void insertFixUp(Node* node);
    void deleteFixUp(Node* node);
    Node* minimum(Node* node) const;
    Node* maximum(Node* node) const;
    Node* search(const Key& key) const;


    // Default Constructor 
    RedBlackTree() : root(nullptr) {}


    // Copy constructor
    // This is the declaration and implementation of the copy constructor. 
    // It initializes a new instance of a RedBlackTree by copying the content from another tree (other).
    // The constructor calls copySubtree, a recursive helper function, starting with the root of the tree to be copied.
    RedBlackTree(const RedBlackTree& other) {
        root = copySubtree(other.root);
    }


    // Copy Assignment Operator 
    RedBlackTree& operator=(const RedBlackTree& other) {
        if (this != &other) {               // Self-assignment check
            clear(root);                    // Clear the current tree
            root = copySubtree(other.root); // Copy the other tree
        }
        return *this;                       // Return a reference to this instance
    }


    // Destructor
    ~RedBlackTree() {
        clear(root); // Clear the entire tree
        root = nullptr; // Just to be safe, set root to nullptr
    }


    // Function to insert a key-value pair
    void insert(const Key& key, const Value& value) {

        // TODO: Implement insertion logic
    
    }

    // TO DO: This is very complex, and we need to fully understand the specific algorithms to maintain the Red-Black Tree properties.
    // This function's definition must be handled carefully
            // Need this header and function signature if we decide that this needs to be moved outside the class
            //  template <typename Key, typename Value>         
            //  bool RedBlackTree<Key, Value>::remove(const Key& key) {
    bool remove(const Key& key) {
        Node* nodeToDelete = searchNode(key); // finds the node with the given key
        if (!nodeToDelete) return false; // Key not found

        Node* y = nodeToDelete;
        Node* x = nullptr;
        bool originalColor = y->isRed;

        if (nodeToDelete->left == nullptr) {
            x = nodeToDelete->right;
            transplant(nodeToDelete, nodeToDelete->right);
        }
        else if (nodeToDelete->right == nullptr) {
            x = nodeToDelete->left;
            transplant(nodeToDelete, nodeToDelete->left);
        }
        else {
            y = minimum(nodeToDelete->right); // Find the minimum in the right subtree
            originalColor = y->isRed;
            x = y->right;

            if (y->parent == nodeToDelete) {
                if (x) x->parent = y;
            }
            else {
                transplant(y, y->right);
                y->right = nodeToDelete->right;
                y->right->parent = y;
            }

            transplant(nodeToDelete, y);
            y->left = nodeToDelete->left;
            y->left->parent = y;
            y->isRed = nodeToDelete->isRed;
        }

        delete nodeToDelete; // Free the memory of the deleted node

        if (!originalColor) {
            deleteFixUp(x);
        }

        return true;
    }

    // Function to search for a value by key
    Value* search(const Key& key) const {

        // TODO: Implement search logic
    
    }

    // Public traversal functions
    void inOrderTraversal() const {
        inOrderHelper(root);
    }

    void preOrderTraversal() const {
        preOrderHelper(root);
    }

    void postOrderTraversal() const {
        postOrderHelper(root);
    }

    void levelOrderTraversal() const {
        levelOrderHelper(root);
    }



private:
    Node* root = nullptr;



    // TO DO: IMPROVE / DEVELOP 
    // Note: this is a simplified example and doesn't cover all complexities involved in accurately copying every aspect of a Red-Black Tree.   
    // Recursive helper function for the copy constructor to create a deep copy of each subtree rooted at node.
    Node* copySubtree(Node* node) {
        if (node == nullptr) return nullptr;
        Node* newNode = new Node(node->key, node->value); // Create a new node with the same key and value
        newNode->isRed = node->isRed; // Copy the color of the node
        newNode->left = copySubtree(node->left); // Recursively copy the left subtree
        newNode->right = copySubtree(node->right); // Recursively copy the right subtree

        // Set the parent of the newly created left and right nodes
        if (newNode->left != nullptr) newNode->left->parent = newNode;
        if (newNode->right != nullptr) newNode->right->parent = newNode;

        return newNode; // Return the new subtree's root node
    }
    /*
    Base Case: If node is nullptr (indicating a leaf or the end of a branch), it returns nullptr,
    ensuring that the new tree accurately represents the structure of the original, including its leaves.

    Node Duplication: For each non-null node, it creates a new node with the same key, value, and color.

    Recursive Copy: It recursively copies the left and right children of the current node,
    ensuring that the entire structure of the subtree is duplicated.

    Parent Linking: After copying the children, it sets their parent pointers to the newly created node,
    maintaining the parent-child relationships found in the original tree.

    Returning the New Node: Finally, it returns a pointer to the newly created node (the root of the copied subtree),
    allowing the parent call to link this new subtree correctly into the larger tree being constructed.
    */



    // Helper function to clear the tree, recursively freeing memory
    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);  // Recursively clear the left subtree
            clear(node->right); // Recursively clear the right subtree
            delete node;        // Delete the current node
        }
    }


    void insertFixUp(Node* node) {

        // TODO: Implement fix-up logic to maintain Red-Black properties after insertion
        // This function involves a series of case-based adjustments, including rotations and re-coloring of nodes.

    }

    void rotateLeft(Node* node) {

        // TODO: Implement left rotation
        // Performs a left rotation around the given node x

    
    }

    void rotateRight(Node* node) {
        // TODO: Implement right rotation
        // Performs a right rotation around the given node x
    }

    // Any other helper functions we might need (e.g., transplant, deleteFixUp, etc.)




    // Transplant Function
        // The transplant function is used to replace one subtree as a child of its parent with another subtree.
        // When you delete a node from a Red - Black Tree, we might need to replace the deleted node with its child(if it exists).
        // The transplant function helps in doing this by linking the parent of the subtree being replaced to the new subtree.

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v; // u is the root node
        }
        else if (u == u->parent->left) {
            u->parent->left = v; // u is a left child
        }
        else {
            u->parent->right = v; // u is a right child
        }
        if (v != nullptr) {
            v->parent = u->parent; // Update parent
        }
    }





    // DeleteFixUp Function
        // The deleteFixUp function is called after deleting a node to ensure that the Red - Black Tree properties are preserved.
        // Deletion, especially when dealing with a black node, can lead to violations of the Red - Black properties.
        // For example, deleting a black node might reduce the black height in one part of the tree,
        // violating the property that all paths from the root to leaves have the same number of black nodes.

        // The deleteFixUp function addresses these violations through a series of steps that may include recoloring nodes and performing rotations.
        // The specific actions taken depend on the relationship between the node being fixed up (often the replacement node or the sibling of a removed leaf)
        // and its siblings, parents, and other relatives in the tree structure.

        // The actual implementation of deleteFixUp involves handling several specific cases based on the colors of the nodes involved and their positions in the tree.
        // The goal is to redistribute black heights and ensure the tree remains balanced according to Red - Black Tree properties.

        // Here is a starter:
    void deleteFixUp(Node* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right; // Sibling
                if (w->color == RED) {
                    // Case 1: x's sibling w is red
                    w->color = BLACK; // Make sibling black
                    x->parent->color = RED; // Make parent red
                    rotateLeft(x->parent); // Rotate on parent
                    w = x->parent->right; // Update sibling
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    // Case 2: Both of w's children are black
                    w->color = RED; // Recolor sibling
                    x = x->parent; // Move up the tree
                }
                else {
                    if (w->right->color == BLACK) {
                        // Case 3: w's right child is black
                        w->left->color = BLACK; // Make left child black
                        w->color = RED; // Make sibling red
                        rotateRight(w); // Rotate on sibling
                        w = x->parent->right; // Update sibling
                    }
                    // Case 4: w's right child is red
                    w->color = x->parent->color; // Sibling takes parent's color
                    x->parent->color = BLACK; // Parent becomes black
                    w->right->color = BLACK; // Right child becomes black
                    rotateLeft(x->parent); // Rotate on parent
                    x = root; // Break loop
                }
            }
            else { // Mirror cases for x being the right child
                Node* w = x->parent->left;
                // Similar logic as above, with "left" and "right" swapped
            }
        }
        x->color = BLACK; // Ensure the passed node is black
    }


    // Searches for a node by key and returns a pointer to the node.
    Node* searchNode(const Key& key) const {
        Node* current = root;
        while (current != nullptr) {
            if (key < current->key) {
                current = current->left; // Move to the left subtree if the key is less than the current node's key
            }
            else if (key > current->key) {
                current = current->right; // Move to the right subtree if the key is greater than the current node's key
            }
            else {
                return current; // Key is found, return the current node
            }
        }
        return nullptr; // Key is not found
    }



    // Finds the node with the minimum key in the subtree rooted at the given node.
    Node* minimum(Node* node) const {
        Node* current = node;
        while (current != nullptr && current->left != nullptr) {
            current = current->left; // Keep moving to the left child to find the minimum
        }
        return current; // The leftmost node is the minimum
    }



    // Finds the node with the maximum key in the subtree rooted at the given node.
    Node* maximum(Node* node) const {
        Node* current = node;
        while (current != nullptr && current->right != nullptr) {
            current = current->right; // Keep moving to the right child to find the maximum
        }
        return current; // The rightmost node is the maximum
    }



    // Finds the in-order successor of the given node
    Node* successor(Node* node) const {
        if (node->right != nullptr) {
            return minimum(node->right); // The minimum in the right subtree
        }
        // Else, move up the tree until we've moved left
        Node* current = node->parent;
        while (current != nullptr && node == current->right) {
            node = current;
            current = current->parent;
        }
        return current;
    }




    // Finds the in-order predecessor of the given node
    Node* predecessor(Node* node) const {
        if (node->left != nullptr) {
            return maximum(node->left); // The maximum in the left subtree
        }
        // Else, move up the tree until we've moved right
        Node* current = node->parent;
        while (current != nullptr && node == current->left) {
            node = current;
            current = current->parent;
        }
        return current;
    }

    // Private helper functions for traversals
    void inOrderHelper(Node* node) const {
        if (node != nullptr) {
            inOrderHelper(node->left);
            cout << node->value << " "; // Assuming you want to print the value
            inOrderHelper(node->right);
        }
    }

    void preOrderHelper(Node* node) const {
        if (node != nullptr) {
            cout << node->value << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void postOrderHelper(Node* node) const {
        if (node != nullptr) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->value << " ";
        }
    }

    void levelOrderHelper(Node* node) const {
        if (!node) return;
        queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->value << " ";
            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
    }



    /*
    
            Additional Functionalities and Considerations

        Search Operation: We need to make sure we have a robust search operation that can efficiently find elements within the tree based on their keys.

        Traversal Methods: Depending on our application's requirements, we might need to implement various tree traversal methods
        (in-order, pre-order, post-order, or level-order) to process or display the data stored in the tree in a particular order.

        Tree Balancing on Deletion: Besides the deleteFixUp function, make sure deletion process correctly handles different scenarios,
        like deleting a node with no children, one child, or two children, while maintaining the Red-Black Tree properties.

        Memory Management: Implement a destructor for the Red-Black Tree class that properly deallocates all allocated nodes to prevent memory leaks.
        We might also need copy constructor and copy assignment operator if we plan to copy our tree structures.

        Testing and Validation: Rigorous testing is crucial to ensure that the Red-Black Tree implementation correctly maintains its properties through all operations.
        Edge cases, such as inserting multiple items with the same key or removing items from a heavily imbalanced tree.

        Template Implementation
        The use of templates in our Red-Black Tree implementation allows it to be generic, meaning we can store any type of key-value pairs in the tree.
        Type Independence: We can use the same Red-Black Tree structure to store different types of data without needing to rewrite or overload the class specifically for those types.
        Reusability: The template-based implementation can be used across various parts of our program or even in future projects without being tied to a specific data type.
        Integration: With a template, we can define the key and value types at compile-time based on what we need for a particular instance of our application,
        making it easier to integrate with other parts of the system.

        Integration with the Main Program
        By designing our Red-Black Tree as a generic template, we enable the main program to instantiate trees with different data types as needed.
        This is especially useful in our case, where we want to compare the performance of Red-Black Trees against HashTables for storing and manipulating data.
        We can define the type of key and value that matches our data model (for example, using a string as the key and a custom struct as the value)
        and use the tree for efficient data storage and retrieval operations.

    */




    /*
    
        Implementing a copy constructor and a copy assignment operator for a complex data structure like a Red-Black Tree is important
        for ensuring that deep copies of the tree can be made safely and accurately.
        These functionalities are particularly useful in several scenarios:

        1. Creating a Backup
        In situations where we need to preserve the current state of a tree before performing operations
        that could potentially alter it significantly (such as bulk insertions or deletions),
        having a backup copy of the tree might be essential.
        This allows us to revert to the original state if needed.

        2. Functionality that Requires Copies
        Certain algorithms or operations may require working with copies of the tree rather than the original.
        For example, if we implement an undo feature or need to compare the states of a tree at different points in time,
        we would need to create copies of the tree structure.

        3. Passing Trees to Functions
        When passing a Red-Black Tree to a function, if we want to avoid modifying the original tree, passing a copy would be necessary.
        While passing by reference is common for efficiency, there are cases where working on a copy
        within a function is required to preserve the integrity of the original data.

        4. Returning Trees from Functions
        Similar to passing trees to functions, if we return a Red-Black Tree from a function and want to ensure that the caller gets a separate,
        modifiable copy that doesn't affect the original tree within the function, implementing deep copy logic is crucial.

        5. Working with Containers of Trees
        If we store multiple Red-Black Trees within a container (like a vector or a list),
        and we need to duplicate the container along with the trees inside it, having a copy constructor
        and a copy assignment operator ensures that each tree is properly duplicated.

        Implementing Deep Copy
        For a Red-Black Tree, a shallow copy (the default behavior if we don't explicitly implement copying) is insufficient
        because it would only copy the root node pointer, leading both the original and copied tree to share the same nodes.
        This sharing could result in changes to one tree affecting the other and lead to issues when one tree is deleted
        (the other would be left with dangling pointers). A deep copy ensures that a completely new tree is created,
        with its own nodes that replicate the structure and content of the original tree.

    */



    // Other helpers...
    // We can implement private helper functions here if they are simple enough, or
    // just declare them here and define them outside the class if they are complex. 
    // with this header for the template
    // template <typename Key, typename Value>

};




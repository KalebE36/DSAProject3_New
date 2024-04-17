#include <iostream>
#include "RedBlackTree.h"


// We can do a more robust test later using Catch2. For now I used this simple main function to test the functionalities of the Templated RBT. 
int main() {
    RedBlackTree<int, string> tree;

    // Test insertions
    cout << "Inserting elements into the tree...\n";
    tree.insert(10, "apple");
    tree.insert(20, "banana");
    tree.insert(30, "cherry");
    tree.insert(15, "date");
    tree.insert(25, "fig");

    // Test search for values
    cout << "Searching for values in the tree...\n";
    string* value = tree.search(20);
    if (value) {
        cout << "Search for 20: " << *value << endl;
    }
    else {
        cout << "Search for 20: Not found" << endl;
    }

    value = tree.search(100);
    if (value) {
        cout << "Search for 100: " << *value << endl;
    }
    else {
        cout << "Search for 100: Not found" << endl;
    }

    // Test deletion
    cout << "Deleting an element (20) from the tree...\n";
    if (tree.remove(20)) {
        cout << "20 deleted successfully.\n";
    }
    else {
        cout << "Failed to delete 20.\n";
    }

    // Test in-order traversal after deletion
    cout << "In-order traversal after deletion:\n";
    tree.inOrderTraversal();
    cout << endl;

    // Optionally test the searchNode function for internal adjustments
    cout << "Using searchNode to find an internal node...\n";
    auto node = tree.searchNode(15);
    if (node) {
        cout << "Node found: " << node->key << " - " << node->value;
        cout << (node->isRed ? " (Red)" : " (Black)") << endl;
    }
    else {
        cout << "Node with key 15 not found." << endl;
    }

    return 0;
}

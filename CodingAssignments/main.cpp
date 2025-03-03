//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Jermaine Wiggins
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Lab 5-2 Binary Search Tree
//============================================================================

#include <iostream>
#include <time.h>
#include <stack>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
            Node() {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    
    //root is equal to nullptr
   root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    
    // recurse from root deleting every node
    if (root == nullptr) {
        return;
    }
    
    // variables to traverse tree (current) and variable to check if right child has been processed
    Node* current = root;
    Node* lastProcessed = nullptr;
    
    // keep track of nodes as traversing tree
    stack<Node*> treeStack;
    
    // traverse tree
    while (current != nullptr || !treeStack.empty()) {
        // if current node isnt null add to stack keep moving down left side
        if (current != nullptr) {
            treeStack.push(current);
            current = current->left;
        }
        //if current is null look at top of stack and check right side of node
        else {
            Node* topNode = treeStack.top();
            // Delete topNode if its right child is null or already processed
            if (topNode->right ==  nullptr || lastProcessed == topNode->right ) {
                lastProcessed = topNode;
                treeStack.pop();
                delete topNode;
            }
            // traverse right side
            else {
                current = topNode->right;
            }
        }
    }
    // After deleting all nodes set root to null
    root = nullptr;
    
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    
    // call inOrder fuction and pass root
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    
    // postOrder root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    
    // preOrder root
    preOrder(root);
}



/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    addNode(root, bid);
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    
    // remove node root bidID
    removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    
    // set current node equal to root
    Node* current = root;

    // keep looping downwards until bottom reached or matching bidId found
    while ( current != nullptr) {
        
        // if match found, return current bid
        if (current->bid.bidId == bidId) {
            return current->bid;
        }
        // if bid is smaller than current node then traverse left
        else if (bidId < current->bid.bidId) {
            current = current->left;
        }
        // else larger so traverse right
        else {
            current = current->right;
        }
    }
    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    
    // If root is null, create a new node and set it as root
    if (root == nullptr) {
        root = new Node(bid);
        return;
    }

    // Traverse the tree to find the correct position to insert
    Node* current = root;
    while (current != nullptr) {
        // if bid  is smaller then add to left
        if (bid.bidId < current->bid.bidId) {
            if (current->left == nullptr) {
                // this node becomes left
                current->left = new Node(bid);
                return;
            }
            // else recurse down the left node
            else {
                current = current->left;
            }
        }
        // if bid id greater than current
        else {
            // if no right node
            if (current->right == nullptr) {
                // this node becomes right
                current->right = new Node(bid);
                return;
            }
            // recurse down the right node
            else {
                current = current->right;
            }
        }
    }
}

void BinarySearchTree::inOrder(Node* node) {
     
   
      //if node is equal to null ptr
    if (node == nullptr) {
        return;
    }
    //InOrder left
    inOrder(node->left);
    
    //output bidID, title, amount, fund
    cout << node->bid.bidId << ": "
    << node->bid.title << "|"
    << node->bid.amount << "|"
    << node->bid.fund << endl;
    
    //InOder right
    inOrder(node->right);
}

void BinarySearchTree::postOrder(Node* node) {
      
    //if node is equal to null ptr
    if (node == nullptr) {
        return;
    }
    //postOrder left
    postOrder(node->left);
    
    //postOrder right
    postOrder(node->right);
    
    //output bidID, title, amount, fund
    cout << node->bid.bidId << ": "
    << node->bid.title << "|"
    << node->bid.amount << "|"
    << node->bid.fund << endl;

}

void BinarySearchTree::preOrder(Node* node) {
      // FixMe (5b): Pre order root
    //if node is equal to null ptr
    if (node == nullptr) {
        return;
    }
      
    //output bidID, title, amount, fund
    cout << node->bid.bidId << ": "
    << node->bid.title << "|"
    << node->bid.amount << "|"
    << node->bid.fund << endl;
      
    //preOrder left
    preOrder(node->left);
    
    //preOrder right
    preOrder(node->right);
}

/**
 * Remove a bid from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    
    // if node = nullptr return node
    if (node == nullptr) {
        return node;
    }
    // (otherwise recurse down the left subtree)
    // check for match and if so, remove left node using recursive call
    if (bidId < node->bid.bidId) {
        node->left = removeNode(node->left, bidId);
    }
    // (otherwise recurse down the right subtree)
    // check for match and if so, remove right node using recursive call
    else if (bidId > node->bid.bidId) {
        node->right = removeNode(node->right, bidId);
    }
    // (otherwise no children so node is a leaf node)
    else {
        // if left node = nullptr && right node = nullptr delete node
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            cout << "Bid successfully removed." << endl;
            return nullptr;
        }
        // (otherwise check one child to the left)
        // if left node != nullptr && right node = nullptr delete node
        else if (node->left != nullptr && node->right == nullptr) {
            // create temp node to copy node to safely delete
            Node* tempLeft = node->left;
            delete node;
            cout << "Bid successfully removed." << endl;
            return tempLeft;
        }
        // (otherwise check one child to the right)
        // if left node = nullptr && right node != nullptr delete node
        else if (node->left == nullptr && node->right != nullptr) {
            // create temp node to copy node to safely delete
            Node* tempRight = node->right;
            delete node;
            cout << "Bid successfully removed." << endl;
            return tempRight;
        }
        // (otherwise more than one child so find the minimum)
        else {
            // Create a temporary node 'tempThree' to hold the right child of the current node
            Node* tempThree = node->right;
            
            // while left node is not nullptr keep moving temp left*
            while (tempThree->left != nullptr) {
                tempThree = tempThree->left;
            }
            // copy node bid to temp3 the successor node
            node->bid = tempThree->bid;
            // remove right node using recursive call
            removeNode(node->right, tempThree->bid.bidId);
        }
    }
    return node;
}



//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98223";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98223";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}

//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Joe De Lima
// Version     : 1.0
// Description : ABCU Course Planner using a Binary Search Tree
// ==============================

#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>



using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================



// define a structure to hold course information
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;

    Course() {
    }
// default constructor
    Course(string number, string name) {
        courseNumber = number;
        title = name;

    }
};

// Internal structure for tree node
struct Node {
     Course course;
    Node* left;
    Node* right;

   


   
    // initialize course, left and right
      Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

class BinarySearchTree {

// private members and methods
private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string courseNumber);

    // public members and methods
public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    void Remove(string courseNumber);
    Course Search(string courseNumber);
};

/**
 * Default constructor
 */

BinarySearchTree::BinarySearchTree() {
    //initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    
    // recurse from root deleting every node
    while (root != nullptr) {
        root = removeNode(root, root->course.courseNumber);
    }

}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // In order root
    
    // call inOrder fuction and pass root 
                
    inOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // Implement inserting into the tree
    // if root equal to null ptr
    if (root == nullptr) {
        // root is equal to new node course
        root = new Node(course);
    } else {
        // add Node root and course
        addNode(root, course);
    }
}

/**
 * Remove a course
 */
void BinarySearchTree::Remove(string courseNumber) {
    // Implement removing a course from the tree
    // remove node root courseNumber
    root = removeNode(root, courseNumber);
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseNumber) {
    // Implement searching the tree for a course
    // set current node equal to root
    Node* current = root;


    // keep looping downwards until bottom reached or matching courseNumber found
    while (current != nullptr) {
        // if match found, return current course
        if (current->course.courseNumber.compare(courseNumber) == 0) {
            return current->course;// return current course
        }

        // if courseNumber is smaller than current node then traverse left
        if (courseNumber.compare(current->course.courseNumber) < 0) {
            current = current->left;// traverse left
        }
        // else larger so traverse right
        else {
            current = current->right;// traverse right
        }
    }
    Course course;
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // Implement inserting a course into the tree
    // if node is larger then add to left
    if (course.courseNumber.compare(node->course.courseNumber) < 0) {

        // if no left node
        if (node->left == nullptr) {

            // this node becomes left
            node->left = new Node(course);
        }
        // else recurse down the left node
         else {
            addNode(node->left, course);
        }
    }
    // else
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);    
        }
        //else
        
            // recurse down the left node
         else {
            addNode(node->right, course);  
        }
    }                    
}

void BinarySearchTree::inOrder(Node* node) {
      // In order root
      //if node is not equal to null ptr
    if (node != nullptr) {
        //inOrder left
        inOrder(node->left);
        
      //output courseNumber, title
     cout << node->course.courseNumber << ", " << node->course.title << endl;
    
     
      //InOder right
        inOrder(node->right);
    }
}


/**
 * Remove a course from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string courseNumber) {
    // Implement removing a course from the tree
    // if node = nullptr return node
    if (node == nullptr) {
        return node;
    }
    // (otherwise recurse down the left subtree)
    // check for match and if so, remove left node using recursive call 
    if (courseNumber.compare(node->course.courseNumber) < 0) {
        node->left = removeNode(node->left, courseNumber);
    }
    // (otherwise recurse down the right subtree)
    // check for match and if so, remove right node using recursive call
    else if (courseNumber.compare(node->course.courseNumber) > 0) {
        node->right = removeNode(node->right, courseNumber);
    }
    // (otherwise no children so node is a leaf node)
        else {
    // if left node = nullptr && right node = nullptr delete node 
    if (node->left == nullptr && node->right == nullptr) {
        delete node;
        node = nullptr;
    }
    // (otherwise check one child to the left)
    // if left node != nullptr && right node = nullptr delete node 
    else if (node->left != nullptr && node->right == nullptr) {
        Node* temp = node;
        node = node->left;
        delete temp;
    }
    // (otherwise check one child to the right)
    // if left node = nullptr && right node != nullptr delete node
    else if (node->left == nullptr && node->right != nullptr) {
        Node* temp = node;
        node = node->right;
        delete temp;
    }
    // (otherwise more than one child so find the minimum)
    else {
    // create temp node to right
    Node* temp = node->right;
    // while left node is not nullptr keep moving temp left
    while (temp->left != nullptr) {
        temp = temp->left;
    }
    // make node course (right) equal to temp course (left)
    node->course = temp->course;
    // remove right node using recursive call
    node->right = removeNode(node->right, temp->course.courseNumber);
    }
}
    // return node
    return node;
}



//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
// display the course information to the console (std::out)
void displayCourse(Course course, BinarySearchTree* bst) {
    cout << course.courseNumber << ", " << course.title << endl;
// if prerequisites is empty output "Prerequisites: None"
    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    // else output "Prerequisites: " and list the prerequisites
    else {
        cout << "Prerequisites: ";
        for (unsigned int i = 0; i < course.prerequisites.size(); ++i) {
            Course prereqCourse = bst->Search(course.prerequisites[i]);
            cout << course.prerequisites[i];

            if (!prereqCourse.courseNumber.empty()) {
                cout << ", " << prereqCourse.title;
            }

            if (i < course.prerequisites.size() - 1) {
                cout << "; ";
            }
        }
        cout << endl;
    }
}
   

/**
 * Load a CSV file containing courses into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the courses read
 */
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");

    if (first == string::npos || last == string::npos) {
        return "";
    }
// return the substring from first to last
    return str.substr(first, last - first + 1);
}
//Load a CSV file containing courses into a container
bool loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

  
// open the file
   ifstream file(csvPath);
    string line;

  if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return false;
    }

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string token;
        vector<string> tokens;

         while (getline(ss, token, ',')) {
            tokens.push_back(trim(token));
}

        if (tokens.size() < 2) {
            continue;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.title = tokens[1];

        for (unsigned int i = 2; i < tokens.size(); ++i) {
            course.prerequisites.push_back(tokens[i]);
        }

        bst->Insert(course);
    }

    file.close();
    return true;
}   


/**
 * The one and only main() method
 */
int main() {
    bool dataLoaded = false;

  
    string csvPath, courseNumber;
 
    

    // Define a binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    int choice = 0;
      cout << "Welcome to the course planner." << endl << endl;
    
    while (choice != 9) {
      
        cout << "1. Load Data Structure." << endl;
	    cout << "2. Print Course List." << endl;
	    cout << "3. Print Course." << endl;
	    cout << "9. Exit" << endl << endl;
        
        // user is prompted to input selection
	    cout << "What would you like to do? ";
	    cin >> choice;

        switch (choice) {

        case 1:
         if (dataLoaded) {
             cout << "Data has already been loaded." << endl << endl;
             break;
         }
         cout << "Enter file name: ";
         cin >> csvPath;
            
           

            // Complete the method call to load the courses
           dataLoaded = loadCourses(csvPath, bst);

            //cout << bst->Size() << " courses read" << endl;
            if (dataLoaded) {
             cout << "Data loaded successfully." << endl << endl;
    
            }
            else {
                cout << "Failed to load data." << endl << endl;
            }
            
            break;

        case 2:
            if (!dataLoaded) {
                cout << "Data not loaded. Please load data first." << endl << endl;
                break;
            }
            cout << "Here is a sample schedule:" << endl << endl;
            bst->InOrder();
            cout << endl;
            break;

        case 3:
                if (!dataLoaded) {
                    cout << "Data not loaded. Please load data first." << endl << endl;
                    break;
                }
            

            cout << "What course do you want to know about? ";
            cin >> courseNumber;

            for (char& c : courseNumber) {
                 c = toupper(static_cast<unsigned char>(c));
}

            course = bst->Search(courseNumber);

            if (!course.courseNumber.empty()) {
               displayCourse(course, bst);
               cout << endl << endl;   
            } else {
            	cout << "Course Number " << courseNumber << " not found." << endl << endl;
            }

            

            break;
        case 9:
            break;
            default:
            cout << choice << " is not a valid option." << endl << endl;
            break;

        }
    }

      cout << "Thank you for using the course planner!" << endl << endl;

    delete bst;
    return 0;
}
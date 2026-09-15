/*
 * Element Database
 * Course  : CSE 225.11
 * Author  : Md. Sayadul Hoque
 * University : North South University, Dhaka, Bangladesh
 *
 * A console-based periodic element database implemented using a
 * Binary Search Tree (BST). Elements are sorted by atomic number.
 */

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// BST node representing a single chemical element
struct Element
{
    int atomicNumber;   // Unique key used to order the BST
    string symbol;      // Chemical symbol (e.g. "Li", "He")
    string name;        // Full element name (e.g. "Lithium")
    Element *left;      // Left child (smaller atomic number)
    Element *right;     // Right child (larger atomic number)
};

class ElementDatabase{
    private:
        Element* root;    // Root pointer of the BST

        // Compare two strings without regard to letter case
        static bool iequals(const string& a, const string& b) {
            if (a.size() != b.size()) {
                return false;
            }
            for (size_t i = 0; i < a.size(); i++) {
                if (tolower(a[i]) != tolower(b[i])) {
                    return false;
                }
            }
            return true;
        }

        // Recursively delete every node in the tree (post-order traversal)
        void clearTree(Element *&e) {
            if (e == NULL) {
                return;
            }
            clearTree(e->left);
            clearTree(e->right);
            delete e;
            e = NULL;
        }

        // Return the node with the smallest atomic number in the given subtree
        Element* findMin(Element *e) {
            while (e != NULL && e->left != NULL) {
                e = e->left;
            }
            return e;
        }

        // Recursively insert a new element into the BST by atomic number
        void addElement(Element *&e, int atomicNumber, string symbol, string name){
            if(e == NULL){
                // Create a new leaf node at the correct position
                e = new Element;
                e->atomicNumber = atomicNumber;
                e->symbol = symbol;
                e->name = name;
                e->left = NULL;
                e->right = NULL;
            }else if(atomicNumber < e->atomicNumber){
                addElement(e->left, atomicNumber, symbol, name);
            }else if(atomicNumber > e->atomicNumber){
                addElement(e->right, atomicNumber, symbol, name);
            }
            // Equal atomic numbers are ignored here; duplicates are blocked in the public method
        }

        // Print a single element in the required output format
        void printElement(const Element *e) const {
            cout << e->atomicNumber << ", " << e->symbol << ", " << e->name;
        }

        // In-order traversal: prints all elements sorted by atomic number
        void printElements(Element *e){
            if(e == NULL){
               return;
            }
            printElements(e->left);
            printElement(e);
            cout << "\n";
            printElements(e->right);
        }

        // Print one element, or a not-found message if the pointer is NULL
        void printspecificElement(Element *e){
            if(e == NULL){
               cout << "No element was found.";
               return;
            }
            printElement(e);
        }

        // Search the BST by atomic number and print the matching element
        void findspecificElement(Element *e, int atomicNumber){
            if(e == NULL){
                return;
            }

            if(e->atomicNumber == atomicNumber){
                printspecificElement(e);
                return;
            }else if(atomicNumber < e->atomicNumber){
                findspecificElement(e->left, atomicNumber);
            }else{
                findspecificElement(e->right, atomicNumber);
            }
        }

        // Return true if an element with the given atomic number exists in the BST
        bool availabilityofElement(Element *e, int atomicNumber){
            if(e == NULL){
                return false;
            }

            if(e->atomicNumber == atomicNumber){
                return true;
            }else if(atomicNumber < e->atomicNumber){
                return availabilityofElement(e->left, atomicNumber);
            }else{
                return availabilityofElement(e->right, atomicNumber);
            }
        }

        // Return true if any element in the tree has the given chemical symbol
        bool validityofSymbol(Element *e, string symbol){
            if(e == NULL){
               return false;
            }

            if (iequals(e->symbol, symbol)){
                return true;
            }

            return validityofSymbol(e->left, symbol) || validityofSymbol(e->right, symbol);
        }

        // Returns the address of the element if a match is found
        // Return NULL if no match is found
        Element* findElementBySymbol(Element *e, string symbol){
            if(e == NULL){
               return NULL;
            }

            if (iequals(e->symbol, symbol)){
                printspecificElement(e);
                return e;
            }

            Element *found = findElementBySymbol(e->left, symbol);
            if (found != NULL) {
                return found;
            }

            return findElementBySymbol(e->right, symbol);
        }

        // Return true if any element in the tree has the given name
        bool validityofName(Element *e, string name){
            if(e == NULL){
               return false;
            }

            if (iequals(e->name, name)){
                return true;
            }

            return validityofName(e->left, name) || validityofName(e->right, name);
        }

        // Returns the address of the element if a match is found
        // Return NULL if no match is found
        Element* findElementByName(Element *e, string name){
            if(e == NULL){
               return NULL;
            }

            if (iequals(e->name, name)){
                printspecificElement(e);
                return e;
            }

            Element *found = findElementByName(e->left, name);
            if (found != NULL) {
                return found;
            }

            return findElementByName(e->right, name);
        }

        // Recursively delete the node with the given atomic number from the BST
        void deleteElement(Element *&e, int atomicNumber){
            if(e == NULL){
                return;
            }

            if(atomicNumber < e->atomicNumber){
                deleteElement(e->left, atomicNumber);
            }else if(atomicNumber > e->atomicNumber){
                deleteElement(e->right, atomicNumber);
            }else{
                // Node to delete has been found — handle all three BST cases
                if(e->left == NULL && e->right == NULL){
                    // Case 1: leaf node
                    delete e;
                    e = NULL;
                }else if(e->left == NULL){
                    // Case 2: only right child
                    Element *temp = e->right;
                    delete e;
                    e = temp;
                }else if(e->right == NULL){
                    // Case 2: only left child
                    Element *temp = e->left;
                    delete e;
                    e = temp;
                }else{
                    // Case 3: two children — replace with inorder successor
                    Element *successor = findMin(e->right);
                    e->atomicNumber = successor->atomicNumber;
                    e->symbol = successor->symbol;
                    e->name = successor->name;
                    deleteElement(e->right, successor->atomicNumber);
                }
            }
        }

    public:
        // Initialize an empty database
        ElementDatabase(){
            root = NULL;
        }

        // Free all allocated nodes when the database is destroyed
        ~ElementDatabase(){
            clearTree(root);
        }

        // Add a new element; returns false if the atomic number already exists
        bool addElement(int atomicNumber, string symbol, string name){
            if (availabilityofElement(atomicNumber)) {
                return false;
            }
            addElement(root, atomicNumber, symbol, name);
            return true;
        }

        // Print every element in ascending order of atomic number
        void printElements(){
            printElements(root);
        }

        // Search by chemical symbol and print the result
        Element* findElementBySymbol(string symbol){
            return findElementBySymbol(root, symbol);
        }

        // Check whether a chemical symbol exists in the database
        bool validityofSymbol(string symbol){
            return validityofSymbol(root, symbol);
        }

        // Search by element name and print the result
        Element* findElementByName(string name){
            return findElementByName(root, name);
        }

        // Check whether an element name exists in the database
        bool validityofName(string name){
            return validityofName(root, name);
        }

        // Remove the element with the given atomic number
        void deleteElement(int atomicNumber){
            deleteElement(root, atomicNumber);
        }

        // Find and print the element with the given atomic number
        void findspecificElement(int atomicNumber){
            findspecificElement(root, atomicNumber);
        }

        // Return true if an element with the given atomic number exists
        bool availabilityofElement(int atomicNumber){
            return availabilityofElement(root, atomicNumber);
        }
};

// Display the main menu options
void printmenu(){
    cout << "1. Add an element\n";
    cout << "2. View elements\n";
    cout << "3. Search elements by chemical symbol\n";
    cout << "4. Search elements by element name\n";
    cout << "5. Delete an element\n";
    cout << "6. Exit program\n";
    cout << endl;
}

int main(){
    ElementDatabase ED;
    int option;

    // Keep showing the menu until the user chooses to exit
    do
    {
        cout << "\n";
        printmenu();
        cout << "Enter your choice: ";
        cin >> option;
        cout << endl;

        // Option 1: Add a new element to the BST
        if (option == 1)
        {
            int atN;
            string symb;
            string n;

            cout << "** Add an element **\n";
            cout << "Enter atomic number: ";
            cin >> atN;
            cout << "Enter chemical symbol: ";
            cin >> symb;
            cout << "Enter element name: ";
            cin >> n;

            if (ED.addElement(atN, symb, n)) {
                cout << "\n";
                cout << "Element added successfully.\n";
            } else {
                cout << "\n";
                cout << "Element with this atomic number already exists.\n";
            }
            cout << "\n";
            cout << "-----------------------------\n";
        }
        // Option 2: View all elements in sorted order
        else if (option == 2)
        {
            cout << "** View Elements **\n";
            ED.printElements();
            cout << "\n";
            cout << "-----------------------------\n";
        }
        // Option 3: Search for an element by its chemical symbol
        else if (option == 3)
        {
            string s;
            cout << "** Search Elements by Chemical Symbol **\n\n";
            cout << "Enter chemical symbol: ";
            cin >> s;

            cout << "\n";
            cout << "Search result:\n";
            if (ED.validityofSymbol(s)) {
                ED.findElementBySymbol(s);
            } else {
                cout << "No element was found.";
            }
            cout << "\n\n";
            cout << "-----------------------------\n";
        }
        // Option 4: Search for an element by its name
        else if (option == 4)
        {
            string n;
            cout << "** Search Elements by Element Name **\n\n";
            cout << "Enter element name: ";
            cin >> n;

            cout << "\n";
            cout << "Search result:\n";
            if (ED.validityofName(n)) {
                ED.findElementByName(n);
            } else {
                cout << "No element was found.";
            }
            cout << "\n\n";
            cout << "-----------------------------\n";
        }
        // Option 5: Delete an element after user confirmation
        else if (option == 5)
        {
            int a;
            char b;
            cout << "** Delete an element **\n\n";
            cout << "Enter atomic number: ";
            cin >> a;
            cout << "\n";

            if (ED.availabilityofElement(a)) {
                cout << "Do you want to delete:\n";
                ED.findspecificElement(a);
                cout << "\n\n";
                cout << "Enter y or n: ";
                cin >> b;
                b = toupper(b);

                if (b == 'Y') {
                    ED.deleteElement(a);
                    cout << "\n";
                    cout << "Element deleted successfully.\n";
                } else if (b == 'N') {
                    cout << "\n";
                    cout << "Delete cancelled.\n";
                } else {
                    cout << "\n";
                    cout << "Inappropriate input\n";
                }
                cout << "\n";
                cout << "-----------------------------\n";
            } else {
                cout << "No element was found.\n";
                cout << "\n";
                cout << "-----------------------------\n";
            }
        }
        // Option 6: Exit the program
        else if (option == 6)
        {
            cout << "Program has exited..\n";
            break;
        }

    } while (option <= 6 && option >= 1);

    return 0;
}

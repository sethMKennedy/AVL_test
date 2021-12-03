//Code by Seth Micaiah Kennedy

    //Collaborated with Gabby Cannella and Tristan McClain
    //Lots of help from Aman's lecture slides and GeeksforGeeks, specifically on removal function, levelorder (for debugging), and getMaxDepth
    //Specifically, Gabby's help on getting substrings
    //Tristan's help on printing the commas

using namespace std;
#include <string>
#include <iostream>
#include <queue>
#include <vector>
class Student {
public:

    string name = "";
    int id = 0;
    Student* left = nullptr;
    Student* right = nullptr;
    int balance = 0;

    Student();
    Student(string name_, unsigned  int id_);

    int getBalance() { return balance; }

};

Student::Student() {

}

Student::Student(string name_, unsigned  int id_) {
    name = name_;
    id = id_;
    cout << "successful" << endl; //If a student is added, this is where we learn it happened successfully
}

class AVL {

    Student* leftLeft(Student* stu);
    Student* leftRight(Student* stu);
    Student* rightLeft(Student* stu);
    Student* rightRight(Student* stu);


public:
    AVL();
    Student* root = nullptr;
    int maxDepth = 0;
    int numStudents = 0;

    //Student* add(int id);
    Student* add(string name, int id);
    Student* insert(Student* stu, string name, int id);
    // void remove(Student* stu);
    Student* remove(Student* stu, int id);
    bool search(Student* stu, string name);
    Student* search(Student* stu, int id);
    Student* min(Student* stu);
    void levelorder();
    void inorder(Student* stu, vector<Student*>* v);
    void preorder(Student* stu, vector<Student*>* v);
    void postorder(Student* stu, vector<Student*>* v);
    int getMaxDepth(Student* stu);
    Student* balance(Student* stu);


    Student* getRoot() { return root; }
};

AVL::AVL() {}

Student* AVL::add(string name, int id) {
    if (root == nullptr) { //If no root, make one
        root = new Student(name, id);
        return root;
    }
    else {//else go through standard bst insert
        root = insert(root, name, id);
        return root;
    }
}

Student* AVL::insert(Student* stu, string name, int id) {

    if (stu == nullptr) {// once you get to the appropriate leaf node, create a student there
        stu = new Student(name, id);
        return stu;
    }

    else if (id < stu->id) {
        stu->left = insert(stu->left, name, id);
    }
    else if (id > stu->id) {
        stu->right = insert(stu->right, name, id);
    }
    else {
        cout << "unsuccessful" << endl;
        return nullptr;
    }

    stu = balance(stu);
    return stu;
    //source: aman
}

Student* AVL::balance(Student* stu) {
    int l = getMaxDepth(stu->left);
    int r = getMaxDepth(stu->right);
    stu->balance = l - r;

    if (stu->balance == 2) {

        if (stu->left->balance == 1) {
            stu = leftLeft(stu);
        }

        else if (stu->left->balance == -1) {
            stu = leftRight(stu);
        }

    }

    else if (stu->balance == -2) {

        if (stu->right->balance == 1) {
            stu = rightLeft(stu);
        }

        else if (stu->right->balance == -1) {
            stu = rightRight(stu);
        }

    }
    return stu;
}
int AVL::getMaxDepth(Student* stu) {
    if (stu == nullptr)
        return 0;

    else {
        int lDepth = getMaxDepth(stu->left);
        int rDepth = getMaxDepth(stu->right);

        return (lDepth > rDepth ? lDepth + 1 : rDepth + 1);

    }
    //Algorithm from geeks for geeks
}

void AVL::levelorder() {
    queue<Student*> q;
    q.push(root);

    while (q.empty() == false)
    {

        int nodeCount = q.size();

        while (nodeCount > 0)
        {
            Student* node = q.front();
            cout << node->name << " ";
            q.pop();
            if (node->left != NULL)
                q.push(node->left);
            if (node->right != NULL)
                q.push(node->right);
            nodeCount--;
        }
        cout << endl;
    }
    //from geeks4geeks
}

void AVL::inorder(Student* stu, vector<Student*>* v) { //left root right
    if (stu == nullptr)
        return;
    else {
        inorder(stu->left, v);
        v->push_back(stu);
        inorder(stu->right, v);
    }

    //algorithm from amanpreet kapoor
}

void AVL::preorder(Student* stu, vector<Student*>* v) {//root left right
    if (stu == nullptr)
        return;
    else {
        v->push_back(stu);
        preorder(stu->left, v);
        preorder(stu->right, v);
    }

    //algorithm from amanpreet kapoor
}

void AVL::postorder(Student* stu, vector<Student*>* v) {//left right root
    if (stu == nullptr)
        return;
    else {
        postorder(stu->left, v);
        postorder(stu->right, v);
        v->push_back(stu);
    }

    //algorithm from amanpreet kapoor
}

Student* AVL::leftLeft(Student* stu) { //for left left case, performs right rotation

    Student* gc = stu->left->right;
    Student* newParent = stu->left;
    newParent->right = stu;

    stu->left = gc;

    stu = newParent;
    return stu;
}

Student* AVL::leftRight(Student* stu) { //for left right case, performs left rotation then right rotation

    stu->left = rightRight(stu->left);
    stu = leftLeft(stu);
    return stu;
}

Student* AVL::rightRight(Student* stu) {//for right right case, performs left rotation


    Student* gc = nullptr;

    if (stu->right->left != nullptr)
        gc = stu->right->left;
    Student* newParent = stu->right;
    newParent->left = stu;

    stu->right = gc;
    stu = newParent;
    return stu;
}

Student* AVL::rightLeft(Student* stu) {//for right left case performs right rotation then left rotation

    stu->right = leftLeft(stu->right);
    stu = rightRight(stu);
    return stu;
}


Student* AVL::remove(Student* stu, int id) { //recursive removal, if can't find prints unsuccessful 
    if (stu == nullptr) {
        cout << "unsuccessful" << endl;
        return stu;
    }
    else if (id < stu->id)
        stu->left = remove(stu->left, id);
    else if (id > stu->id)
        stu->right = remove(stu->right, id);
    else {
        if (stu->left == nullptr && stu->right == nullptr) {//if a leaf node then turns to nullptr
            cout << "successful" << endl;
            if (stu->id == root->id) {
                root == nullptr;
            }
            delete stu;
            return nullptr;
        }
        else if (stu->left == nullptr) {//for nodes with one child, swap them and delete the old
            Student* temp = stu->right;
            delete stu;
            cout << "successful" << endl;
            return temp;
        }
        else if (stu->right == nullptr) {
            Student* temp = stu->left;
            delete stu;
            cout << "successful" << endl;
            return temp;
        }
        else {
            Student* temp = min(stu->right);//if root node, replace with inorder successor 
            stu->id = temp->id;
            stu->name = temp->name;
            stu->right = remove(stu->right, temp->id);
        }

    }
    return stu;
    //Algorithm citation: Geeks for Geeks and Amanpreet Kapoor
}

bool AVL::search(Student* stu, string name) { //O(n) //brute force search
    bool found = false;
    if (stu == nullptr) {
        //print
        return false;

    }
    if (stu->name == name) {
        cout << stu->id << endl;
        found = true;
        //return true;
    }
    if (search(stu->left, name))
        found = true;
    if (search(stu->right, name))
        found = true;

    return found;
    //amanpreet kapoor
}
Student* AVL::search(Student* stu, int id) {//search by comparing id
    if (stu == nullptr) {
        cout << "unsuccessful" << endl;
        return nullptr;
    }
    else if (stu->id == id) {
        cout << stu->name << endl;
    }
    else if (id < stu->id) {
        search(stu->left, id);
    }
    else
        search(stu->right, id);
    return stu;
    //amanpreet kapoor
}

Student* AVL::min(Student* stu) {//finds minimum value in a tree
    Student* current = stu;

    while (current && current->left != nullptr)
        current = current->left;
    return current;
    //geeks4geeks
}

//Each test case is a function

AVL ll(AVL gatorAvl) {
    gatorAvl.add("JuniorMoffatt", 65810464);
    gatorAvl.add("Nickster", 50000000);
    gatorAvl.add("Roberton", 46000000);
    return gatorAvl;
}

AVL rl(AVL gatorAvl) {
    gatorAvl.add("JuniorMoffatt", 65810464);
    gatorAvl.add("Nickster", 70000000);
    gatorAvl.add("Roberton", 66000000);
    return gatorAvl;
}

AVL rr(AVL gatorAvl) {
    gatorAvl.add("mitch", 65810464);
    gatorAvl.add("simba", 70000000);
    gatorAvl.add("danny", 86000000);
    return gatorAvl;
}

AVL lr(AVL gatorAvl) {
    gatorAvl.add("mitch", 65810464);
    gatorAvl.add("simba", 60000000);
    gatorAvl.add("danny", 63000000);

    return gatorAvl;
}

AVL soloRoot(AVL gatorAvl) {
    gatorAvl.add("rich", 45674567);
    gatorAvl.remove(gatorAvl.getRoot(), 45674567);
    return gatorAvl;
}

AVL nullRoot(AVL gatorAvl) {
    gatorAvl.remove(gatorAvl.getRoot(), 12341234);
    return gatorAvl;
}

AVL searchOnNullID(AVL gatorAvl) {
    bool res = gatorAvl.search(gatorAvl.getRoot(), 12341234);
    if (!res)
        cout << "unsuccessful" << endl; // this extra code is in main method so i put it here too
    return gatorAvl;
}

AVL searchOnNullName(AVL gatorAvl) {
    bool res = gatorAvl.search(gatorAvl.getRoot(), "Abc");
    if (!res)
        cout << "unsuccessful" << endl; // this extra code is in main method so i put it here too
    return gatorAvl;
}

AVL removeLessThan(AVL gatorAvl) {
    gatorAvl.add("mitch", 65810464);
    gatorAvl.add("simba", 60000000);
    gatorAvl.add("danny", 63000000);
    gatorAvl.remove(gatorAvl.getRoot(), 12341234);
    return gatorAvl;
}

void print(vector<Student*>* v) { //Traverses through node vector and prints
    for (int i = 0; i < v->size(); i++) {
        if (i == v->size() - 1)
            cout << v->at(i)->name << endl;
        else
            cout << v->at(i)->name << ", ";
    }
}

int main() {
    AVL gatorAvl = AVL();
    vector<Student*>* stuVector = new vector<Student*>;

    int numCommands = 0;
    cin >> numCommands;


    while (numCommands > -1) { //Command loop

        string s;
        getline(cin, s);
        int space = s.find(" ");
        int quote1;
        int space2;
        int quote2;
        int id = -1;
        string command = s.substr(0, space);
        //command = tolower(s);
        s = s.substr(space + 1, s.length());

        if (command.compare("insert") == 0) {
            quote1 = s.find("\"");
            quote2 = s.find("\"", quote1 + 1);
            space2 = s.find(" ");
            //get name
            string name = s.substr(quote1 + 1, quote2 - 1);
            s = s.substr(quote2 + 1, s.length());
            //get string after name
            id = stoi(s);
            if (to_string(id).length() != 8) {//check if length is 8
                cout << "unsuccessful" << endl;
                break;
            }
            else {
                gatorAvl.add(name, id); //asuuming everything is good, add the student
            }
        }
        else if (command.compare("remove") == 0) {
            id = stoi(s);
            if (to_string(id).length() != 8) {
                cout << "unsuccessful" << endl;
            }
            else
                gatorAvl.root = gatorAvl.remove(gatorAvl.root, id); //call remove function with root

        }
        else if (command.compare("search") == 0) {

            if (gatorAvl.getRoot() != nullptr) {

                try {//try getting an int if it doesn't work assumem it's a string
                    id = stoi(s);
                }
                catch (exception e) {

                }
                if (id > -1) { //kind of a stupid way of seeing if id is storing an int
                    if (to_string(id).length() != 8)
                        cout << "unsuccessful" << endl;
                    else
                        gatorAvl.search(gatorAvl.getRoot(), id);
                }
                else {
                    quote1 = s.find("\""); //Get the substring of the name to search for
                    quote2 = s.find("\"", quote1 + 1);
                    string name = s.substr(quote1 + 1, quote2 - 1);

                    bool res = gatorAvl.search(gatorAvl.getRoot(), name); //Check if the function found the node, else print unsuccessful
                    if (!res)
                        cout << "unsuccessful" << endl;

                }
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
        else if (command.compare("printInorder") == 0) {//each print function works by running the respective traversal algorithm and adding nodes to a vector
            stuVector->clear();
            gatorAvl.inorder(gatorAvl.getRoot(), stuVector);
            print(stuVector);
        }
        else if (command.compare("printPreorder") == 0) {
            stuVector->clear();
            gatorAvl.preorder(gatorAvl.getRoot(), stuVector);
            print(stuVector);
        }
        else if (command.compare("printPostorder") == 0) {
            stuVector->clear();
            gatorAvl.postorder(gatorAvl.getRoot(), stuVector);
            print(stuVector);
        }
        else if (command.compare("printLevelCount") == 0) {
            cout << gatorAvl.getMaxDepth(gatorAvl.getRoot()) << endl; //prints the maxdedpth 
        }
        else if (command.compare("removeInorder") == 0) {
            int num = stoi(s);
            stuVector->clear();
            gatorAvl.inorder(gatorAvl.getRoot(), stuVector);//get inorder vector of students and then remove by id the student at the proper index
            gatorAvl.remove(gatorAvl.getRoot(), stuVector->at(num)->id);
        }
        else if (command.compare("level") == 0) {//fun method for debugging, prints  nodes by level
            gatorAvl.levelorder();
        }
        numCommands--;
    }

    return 0;
}

//
//  dList.cpp
//  
//
//  Created by Michael Caleb Davis on 2/23/18.
//

using namespace std;

struct node {
    int key;
    char type;
    struct node *next;
    struct node *prev;
};

class dList {
public:
    dList();
    dList(int[], char[], int);
    void addFront(int, char);
    void addBack(int, char);
    node* search(int);
    void find(char);
    void moveFront(node *);
    void moveBack(node *);
    void out(int, char = 'f');
    void sort();
    ~dList();
private:
    int size;
    node *head;
    node *tail;
};

dList::dList() {
    head = NULL;
    tail = NULL;
    size = 0;
    return;
}

dList::dList(int nums[], char letters[], int length) {
    for (int i = 0; i < length; i++) {
        node *newNode;
        newNode = new node;
        newNode->key = nums[i];
        newNode->type = letters[i];
        if (head == NULL) {
            head = newNode;
            tail = newNode;
            head->next = NULL;
            head->prev = NULL;
            tail->next = NULL;
            tail->next = NULL;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
            tail->next = NULL;
        }
        size++;
    }
    return;
}

void dList::addFront(int num, char letter) {
    node *newNode;
    newNode = new node;
    newNode->key = num;
    newNode->type = letter;
    if (head == NULL) {
        newNode->next = NULL;
        newNode->prev = NULL;
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        newNode->prev = NULL;
    }
    size++;
    return;
}

void dList::addBack(int num, char letter) {
    node *newNode;
    newNode = new node;
    newNode->key = num;
    newNode->type = letter;
    if (head == NULL) {
        newNode->next = NULL;
        newNode->prev = NULL;
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        tail->next = NULL;
    }
    size++;
    return;
}

node* dList::search(int num) {
    node *currNode, *foundNode;
    currNode = head;
    bool numFound = false;
    while(currNode != NULL) {
        if (currNode->key == num) {
            foundNode = currNode;
            numFound = true;
        }
        currNode = currNode->next;
    }
    if (numFound == false) {
        cout << "No pointer was found with that key" << endl;
    }
    else return foundNode;
    return NULL;
}

void dList::find(char searchLetter) {
    node *currNode;
    currNode = head;
    while (currNode != NULL) {
        if (currNode->type == searchLetter)
            cout << currNode->key << " " << currNode->type << "  ";
        currNode = currNode->next;
    }
    cout << endl;
    return;
}

void dList::moveFront(node *ptr) {
    node *currNode, *prevNode, *nextNode;
    currNode = head;
    while (currNode != NULL) {
        if (currNode == ptr) {
            if (currNode == head) {
                return;
            }
            else if (currNode == tail) {
                nextNode = NULL;
                tail = currNode->prev;
                currNode->prev = NULL;
                currNode->next = head;
                head->prev = currNode;
                head = currNode;
            }
            else {
                prevNode = currNode->prev;
                nextNode = currNode->next;
                prevNode->next = nextNode;
                nextNode->prev = prevNode;
                currNode->next = head;
                head->prev = currNode;
                currNode->prev = NULL;
                head = currNode;

            }
            return;
        }
        currNode = currNode->next;
    }
    return;
}

void dList::moveBack(node *ptr) {
    node *currNode, *prevNode, *nextNode;
    currNode = head;
    while (currNode != NULL) {
        if (currNode == ptr) {
            if (currNode == head) {
                prevNode = NULL;
                head = currNode->next;
                currNode->prev = tail;
                currNode->next = NULL;
                tail->next = currNode;
                tail = currNode;
            }
            else if (currNode == tail) {
                return;
            }
            else {
                prevNode = currNode->prev;
                nextNode = currNode->next;
                prevNode->next = nextNode;
                nextNode->prev = prevNode;
                currNode->prev = tail;
                currNode->next = NULL;
                tail->next = currNode;
                tail = currNode;
            }
            return;
        }
        currNode = currNode->next;
    }
    return;
}

void dList::out(int numItems, char startSide) {
    node *currNode;[p';/]
    if (startSide == 'f') {
        currNode = head;
        for(int i = 1; i <= numItems && currNode != NULL; i++) {
            cout << currNode->key << " " << currNode->type << "  ";
            currNode = currNode->next;
        }
        cout << endl;
    }
    else if (startSide == 'b') {
        currNode = tail;
        for(int i = 1; i <= numItems && currNode != NULL; i++) {
            cout << currNode->key << " " << currNode->type << "  ";
            currNode = currNode->prev;
        }
        cout << endl;
    }
    currNode = head;
    return;
}


dList::~dList() {
    while (head != NULL) {
        node *ptr = head;
        head = head->next;
        delete ptr;
    }
}

node* merge(node *first, node *second) {
    if (!first) {
        return second;
    }
    
    if (!second) {
        return first;
    }
    
    if (first->key < second->key) {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}
node* partition(node *head) {
    node *fast = head, *slow = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    node *temp = slow->next;
    slow->next = NULL;
    return temp;
}
node* mergeSort(node *head) {
    if (!head || !head->next) {
        return head;
    }
    node *second = partition(head);
    
    head = mergeSort(head);
    second = mergeSort(second);
    
    return merge(head, second);
}
void dList::sort() {
    head = mergeSort(head);
    node* temp;
    temp = head;
    while (temp != NULL) {
        if (temp->next == NULL) {
            tail = temp;
            return;
        }
        temp = temp->next;
    }
    return;
}


#include "node.h"

class LL {
  NodePtr hol; // head of linked list
  int size;

public:
  LL();
  int deletes(int value);
  int isEmpty();
  void insert(int value);
  void printList();
  void printList_reverse();

  ~LL();
};

LL::LL() {
  this->hol = NULL;
  size = 0;
}

LL::~LL() {
  cout << "deleting all nodes" << endl;
  NodePtr t;
  t = hol;
  int i;
  for (i = 0; i < size; i++) {
    hol = hol->get_next();
    delete t;
    t = hol;
  }
}

// insert a new value into the list in sorted order
void LL::insert(int value) {
  Node *previousPtr;
  Node *currentPtr;
  Node *tempPtr;

  Node *newPtr = new Node(value);

  if (newPtr != nullptr) {
    if (hol == nullptr) {
      hol = newPtr;
      newPtr->set_next(newPtr);
      newPtr->set_prev(newPtr);
    } else {
      currentPtr = hol;
      while (currentPtr->get_next() != hol &&
             value > (currentPtr->get_next())->get_data()) {
        currentPtr = currentPtr->get_next();
      }
      newPtr->set_next(currentPtr->get_next());
      currentPtr->get_next()->set_prev(newPtr);
      newPtr->set_prev(currentPtr);
      currentPtr->set_next(newPtr);

      if (value < hol->get_data()) {
        hol = newPtr;
      }
    }
    size++;
  } else {
    cout << value << " not inserted. No memory available.\n";
  }
} // end function insert

// delete a list element
int LL::deletes(int value) {
  Node *currentPtr = hol;  // pointer to current node in list
  Node *tempPtr = nullptr; // temporary node pointer

  if (currentPtr == nullptr) {
    return '\0';
  }
  // check if deleted one is at the head
  if (value == hol->get_data()) {
    tempPtr = hol;
    hol = hol->get_next();
    // Update the previous pointer of the new head

    if (hol != nullptr) {
      hol->set_prev(currentPtr->get_prev());
      currentPtr->get_prev()->set_next(hol);
    } else {
      // If the list becomes empty, set hol to nullptr
      hol = nullptr;
    }
    size--;
    delete tempPtr;
    return value;
  } else {
    currentPtr = hol->get_next();

    while (currentPtr != hol) { // looking for node to be deleted
      if (value == currentPtr->get_data()) {
        tempPtr = currentPtr;
        currentPtr->get_prev()->set_next(currentPtr->get_next());
        currentPtr->get_next()->set_prev(currentPtr->get_prev());
        size--;
        // circular ll updated

        delete tempPtr;
        return value;
      }
      currentPtr = currentPtr->get_next(); // slide
    }
  }

  return '\0';
}

// return 1 if the list is empty, 0 otherwise
int LL::isEmpty() { return hol == NULL; } // end function isEmpty

// print the list
void LL::printList() {
  NodePtr currentPtr = hol;
  // if list is empty
  if (size == 0) {
    cout << "List is empty." << endl;
  } // end if
  else {
    cout << "The list is:" << endl;

    // while not the end of the list
    // while ( currentPtr != NULL ) {
    int i;
    for (i = 0; i < size; i++) {
      currentPtr->print();
      cout << "  ->";
      currentPtr = currentPtr->get_next();
    } // end while
    currentPtr->print();
    puts("\n");
  } // end else
} // end function printList

void LL::printList_reverse() {
  if (size == 0) {
    cout << "List is empty" << endl;
    return;
  } else {
    cout << "The reverse list is:" << endl;
      NodePtr currentPtr = hol->get_prev();  // Start from the node before the head

      while (currentPtr != hol) {
        currentPtr->print();
        cout << "  ->";
        currentPtr = currentPtr->get_prev(); //loop backward
      }
      hol->print();
      cout << "  ->";
      currentPtr->get_prev()->print();
      puts("\n");
  }
}

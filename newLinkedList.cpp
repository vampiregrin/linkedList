#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <utility>

template <typename T> class Node {
public:
  T value;
  // private:
  Node *next;
  Node *prev;
};

template <typename T> class List {
public:
  Node<T> *head;
  Node<T> *tail;

  List();

  // void setHead();
  // void setTail();
  // Node<T> *getHead();
  Node<T> *getTail();
  T &getNthValue(int index);
  void addAtEnd(T newVal);
  void addAfterTail(T newVal);
  void addAtBeginning(T newVal);
  int listSize();
  bool insertAtGivenPosition(int x, T newVal);
  void printList();
  void printListBackwards();
  bool deleteNode(int x);
};

template <typename T> List<T>::List() {
  head = NULL;
  tail = NULL;
}

template <typename T> Node<T> *List<T>::getTail() {
  if (head == NULL) {
    std::cout << "NULL" << std::endl;
    return NULL;
  } else {
    Node<T> *current = head;
    if (current->next != NULL) {
      tail = current;
    } else {
      while (current->next == NULL) {
        current = current->next;
        tail = current;
      }
    }
  }
  return tail;
}

template <typename T> void List<T>::addAtEnd(T newVal) {

  Node<T> *newNode = new Node<T>();

  newNode->value = newVal;
  newNode->next = NULL;

  if (head == NULL) {
    newNode->prev = NULL;
    head = newNode;
  } else {
    // getTail();
    tail = head;
    while (tail->next != NULL) {
      tail = tail->next;
    }
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  }
}
template <typename T> void List<T>::addAtBeginning(T newVal) {

  Node<T> *newNode = new Node<T>();
  newNode->value = newVal;
  Node<T> *current = head;
  head = newNode;
  head->next = current;
}
template <typename T> void List<T>::addAfterTail(T newVal) {

  Node<T> *newNode = new Node<T>();

  newNode->value = newVal;
  newNode->next = NULL;

  if (head == NULL) {
    newNode->prev = NULL;
    head = newNode;
  } else {
    tail = getTail();
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  }
}
template <typename T> T &List<T>::getNthValue(int index) {

  Node<T> *current = head;

  int count = 0;
  while (current != NULL) {
    if (count == index)
      return (current->value);
    count++;
    current = current->next;
  }
  return current->value;
}
template <typename T> int List<T>::listSize() {
  Node<T> *current = head;

  int count = 0;
  while (current != NULL) {
    count++;
    current = current->next;
  }
  return count;
}
template <typename T> bool List<T>::insertAtGivenPosition(int x, T newVal) {

  int size = listSize();
  Node<T> *newNode = new Node<T>();
  newNode->value = newVal;
  Node<T> *current = head;
  Node<T> *prevNode;

  if (x == 0) {
    head = newNode;
    head->next = current;
    return true;
  } else if (x == size + 1) {
    addAtEnd(newVal);
    return true;
  } else if (x > size + 1) {
    return false;
  } else {
    int count = 0;
    while (current != NULL) {

      if (count == x) {
        prevNode = current->prev;
        break;
      }
      count++;
      current = current->next;
    }
    prevNode->next = newNode;
    newNode->next = current;
    return true;
  }
}
template <typename T> void List<T>::printList() {
  if (listSize() == 0) {
    std::cout << "List is empty" << std::endl;
  } else {
    Node<T> *current = head;
    int count = 0;
    while (current != NULL) {
      std::cout << count << ".";
      std::cout << current->value << std::endl;
      count++;
      current = current->next;
    }
  }
}

template <typename T> void List<T>::printListBackwards() {
  if (listSize() == 0) {
    std::cout << "List is empty" << std::endl;
  } else {
    tail = getTail();
    Node<T> *current = tail;
    int count = listSize() - 1;
    while (current != head) {
      std::cout << count << ".";
      std::cout << current->value << std::endl;
      count--;
      current = current->prev;
    }
    std::cout << "0." << head->value << std::endl;
  }
}

template <typename T> bool List<T>::deleteNode(int x) {

  int size = listSize();
  Node<T> *current = head;
  Node<T> *prevNode;
  Node<T> *nextNode;

  if (x == 0 && size == 1) {
    head = NULL;
    return true;
  } else if (x == 0) {
    head->next = head;
    std::cout << head->value << std::endl;
    return true;
  } else if (x > size + 1) {
    return false;
  } else if (size == 0) {
    return false;
  } else if (x == size) {
    tail->prev = tail;
    tail->next = NULL;
    return true;
  } else {
    int count = 0;
    while (current != NULL) {
      if (count == x) {
        prevNode = current->prev;
        nextNode = current->next;
        prevNode->next = nextNode;
        break;
      }
      count++;
      current = current->next;
    }
    return true;
  }
}

List<std::string> createSampleListOfStrings() {
  List<std::string> l = List<std::string>();
  l.addAtEnd("first");
  l.addAtEnd("second");
  l.addAtEnd("third");
  l.addAtEnd("fourth");
  return l;
}

List<int> createSampleListOfInts() {
  List<int> l = List<int>();
  l.addAtEnd(1);
  l.addAtEnd(2);
  l.addAtEnd(3);
  l.addAtEnd(4);
  return l;
}
void test_addAtEndOfEmptyString() {
  List<std::string> l = List<std::string>();
  l.addAtEnd("Hello");
  assert(l.head->value == "Hello");
  assert(l.tail->value == "Hello");
}

void test_addAtEndOfEmptyInt() {
  List<int> l = List<int>();
  l.addAtEnd(100);
  assert(l.head->value == 100);
  assert(l.tail->value == 100);
}

void test_emptyListInt() {
  List<int> l = List<int>();
  assert(l.head == NULL);
  assert(l.tail == NULL);
}
void test_getTailOfNonEmpty() {
  List<std::string> l = createSampleListOfStrings();
  assert(l.tail->value == "fourth");
}

void test_getNthValue() {
  List<std::string> l = createSampleListOfStrings();
  assert(l.getNthValue(0) == "first");
  assert(l.getNthValue(2) == "third");
}

void test_insertAtGivenPosition() {
  List<int> l = createSampleListOfInts();
  l.insertAtGivenPosition(0, 0);
  assert(l.getNthValue(0) == 0);
  assert(l.getNthValue(1) == 1);
  l.insertAtGivenPosition(l.listSize() + 1, 5);
  assert(l.getNthValue(5) == 5);
  assert(l.insertAtGivenPosition(10, 10) == false);
}
void test_listSize() {
  List<int> l = createSampleListOfInts();
  assert(l.listSize() == 4);
}
void test_addAfterTail() {
  List<std::string> l = createSampleListOfStrings();
  l.addAfterTail("last");
  assert(l.tail->value == "last");
}
void test_addAtBeginning() {
  List<std::string> l = createSampleListOfStrings();
  l.addAtBeginning("zero");
  assert(l.head->value == "zero");
}

void test_deleteNodeString() {
  List<std::string> l = createSampleListOfStrings();
  l.deleteNode(2);
  assert(l.getNthValue(2) == "fourth");
  assert(l.listSize() == 3);
  assert(l.deleteNode(5) == false);
}
int main() {

  // test_getTailOfNonEmpty();
  // test_getNthValue();
  // test_insertAtGivenPosition();
  // test_addAfterTail();
  // test_addAtBeginning();
  // test_listSize();
  // test_addAtEndOfEmptyInt();
  // test_getTailOfNonEmpty();
  // List<std::string> l = createSampleListOfStrings();
  test_emptyListInt();
  // // l.printListBackwards();
  // l.printList();
  // l.deleteNode(2);
  // test_deleteNodeString();
  // l.printList();
  return 0;
}

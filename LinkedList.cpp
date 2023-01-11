#include <cassert>
#include <iostream>
#include <regex>
#include <vector>

class Node {
public:
  std::string value; // word
  Node *next;
  Node *prev;
};

void printList(Node *n) {
  while (n != NULL) {
    std::cout << n->value << std::endl;
    n = n->next;
  }
}

void printListBackwards(Node **p_head) {
  Node *head = *p_head;
  std::cout << __LINE__ << "  head:" << head << "  head value:" << head->value
            << "  &head: " << &head << std::endl
            << std::endl;
  std::cout << __LINE__ << "  p_head:" << p_head << "  &p_head: " << &p_head
            << std::endl
            << std::endl;
  Node *tail = head;
  std::cout << __LINE__ << "  tail:" << tail << "  tail value:" << tail->value
            << "  &tail:" << &tail << std::endl;

  // Traversing till tail of the linked list
  while (tail->next != NULL) {
    tail = tail->next;
    std::cout << "tail value:  " << tail->value << std::endl;
  }

  // Traversing linked list from tail and printing the node->value
  while (tail != head) {
    std::cout << tail->value << " ";
    tail = tail->prev;
  }
  std::cout << tail->value << std::endl;
}

void insertAtTheFront(Node **head, std::string newValue) {
  // 1. Prepare a new Node
  Node *newNode = new Node();
  newNode->value = newValue;
  // 2. Put it in front of current head
  newNode->next = *head;
  // 3. Move head of the list to point of the newNode
  *head = newNode;
}

void insertAtTheEnd(Node **head, std::string newValue)
// Dodawanie na koncu, ale ta metoda nie wykorzystuje ogona
{
  assert(head != NULL);

  // 1. Prepare a new Node
  Node *newNode = new Node();
  newNode->value = newValue;
  newNode->next = NULL;
  // 2. Check if not empty, if yes -> newNode = head
  if (*head == NULL || head == 0) {
    newNode->prev = NULL;
    *head = newNode;
    return;
  } else {
    // 3. Find the last Node
    Node *last = *head; // we start at the first node & move to the next one
    while (last->next != NULL) {
      last = last->next;
    }
    // 4. Insert newNode after last node
    last->next = newNode;
  }
}

// void insertAtTheGivenPosition (Node ** head, std::string newValue) {
//   if (prev = NULL)
// }

std::vector<std::string> splitSentence(std::string sen) {
  assert(!sen.empty()); // mozna tak?
  std::vector<std::string> vecOfWords;
  std::regex rgx("\\!\\s*");
  std::sregex_token_iterator iter(sen.begin(), sen.end(), rgx, -1);
  std::sregex_token_iterator end;
  for (; iter != end; ++iter) {
    vecOfWords.push_back(*iter);
  }
  return vecOfWords;
}

std::string GetNth(Node *head, int index) {

  Node *current = head;

  // the index of the node we're currently looking at
  int count = 0;
  while (current != NULL) {
    if (count == index)
      return (current->value);
    count++;
    current = current->next;
  }
  return ".";
}

// void test_addElemAtTheEnd() {
//   List l;
//   Node* tail_before_extending = l.tail;
//   Node* n = new Node();
//   l.addAtEnd(n);
//   assert(l.tail == n);
//   assert(n->prev == tail_before_extending);
//   assert(tail_before_extending ->next == l.tail);
// }

int main() {

  Node *head = nullptr;
  Node *tail;

  std::vector<std::string> sentence = splitSentence("Ala! ma! kota!");

  for (int i = 0; i < sentence.size(); i++) {
    insertAtTheEnd(&head, sentence[i]);
  }
  insertAtTheFront(&head, "Uwaga");
  assert(head->value == "Uwaga");

  // Ciekawe, ze w tym przypadku to zero juz nie zostaje, dlaczego?
  // printList (head);
  std::cout << "---------------------" << std::endl;
  // std::cout << "Element at index .. is: '" << GetNth(head, 1) << "'"
  // <<std::endl;
  printListBackwards(&head);
}

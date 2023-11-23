#include "LinkedList.hpp"
#include <time.h> 

//for true randomness, set to false
#define TESTING true


LinkedList::LinkedList() {
    head = nullptr;
}

LinkedList::LinkedList(LinkedList &other) {
    head = nullptr;

  for (int i = 0; i < other.size(); ++i) {
      Node *node = new Node(*other.getNode(i));
      push(node);
  }
}


LinkedList::~LinkedList() {
  for(Node* node = head; node; node = node->next) {
    pop();
  }
}

void LinkedList::randomInsert(Node *node) {
  srand (time(NULL));
  //just get a random number for here
  int random = rand() % size();
  insertAt(random, node);
}

void LinkedList::insertAt(int index, Node *node) {
  Node *before = getNode(index - 1);
  Node *after = getNode(index);
  Tile *tile = new Tile(node->tile->colour, node->tile->shape);
  Node *copy = new Node(tile);
  before->next = copy;
  copy->next = after;
}

// pushes to the head of the list
void LinkedList::push(Node *node) {
  Node *copy = new Node(node->tile);
  copy->next = head;
  head = copy;
}


//deletes from the head of the list
void LinkedList::pop() {
    if (head -> next != nullptr) {
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
    } else {
      head = nullptr;
    } 
}


void LinkedList::swap(Node *nodeA, Node *nodeB) {
  Node temp = *nodeB;
  nodeB->next = nodeA->next;
  nodeB->prev = nodeA->prev;
  nodeA->next = temp.next;
  nodeB->prev = temp.prev;
}

int LinkedList::size() {
  int length = 0;
  for (Node *node = getHead(); node; node = node->next) {
    length++;
  }
  return length;
}

Node *LinkedList::getHead() {
  return head;
}

void LinkedList::setHead(Node *node) {
  this->head = node;
}

Node *LinkedList::getNode(int index) {
  Node *gottenNode = nullptr;

  if (index >= 0 && index < size()) {
    int counter = 0;
    Node *current = head;
    while (counter < index)
    {
      ++counter;
      current = current->next;
    }
    gottenNode = current;
  }
  return gottenNode;
}

void LinkedList::remove(int index)
{
  if (index >= 0 && index < size())
  {
    if (head != nullptr)
    {
      int counter = 0;
      Node *current = head;
      //pre should point to node before current;
      Node *prev = nullptr;

      while (counter != index)
      {
        ++counter;
        prev = current;
        current = current->next;
      }

      if (prev == nullptr)
      {
        head = current->next;
      }
      else
      {
        prev->next = current->next;
      }
    }
  }
}

void LinkedList::print()
{
  std::cout << "printing linked list, of size: " << size() << std::endl;
  for (Node *node = head; node; node = node->next)
  {
    std::cout << "tile colour: " << node->tile->colour << " tile shape: " << node->tile->shape << std::endl;
  }
}

void LinkedList::shuffle()
{
//if testing then the seed is set to have it be less random so tests can be run as per specs
  if (!TESTING) {
  srand (time(NULL));
  } else {
    srand (1);
  }
  int random;
  int iteration = 0;
  LinkedList *shuffleList = new LinkedList();
  LinkedList *listShuffled = new LinkedList();
  Node *shuffleNode = nullptr;

  for (shuffleNode = head; shuffleNode; shuffleNode = shuffleNode->next)
  {
    shuffleList->push(shuffleNode);
  }
  int initial_size = shuffleList->size();

  while (iteration < initial_size)
  {
    random = std::rand() % shuffleList->size(); //maybe can replace with initial_size-iteration

    Node *node = shuffleList->getNode(random);
    Colour colour = node->tile->colour;
    Shape shape = node->tile->shape;
    Tile *tileCopy = new Tile(colour, shape);
    Node *nodeCopy = new Node(tileCopy);
    
    listShuffled->push(nodeCopy);
    iteration++;
    shuffleList->remove(random);
  }

  for (int i = 0; i < listShuffled->size(); i++)
  {
    remove(i);
    push(listShuffled->getNode(i));
  }
  
}

// for(Node* node = list.getHead(); node; node = node->next) {     }  // you can loop through the list likee this!!!
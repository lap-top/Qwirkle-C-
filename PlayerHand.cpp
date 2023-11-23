#include "PlayerHand.hpp"

PlayerHand::PlayerHand() {}

PlayerHand::~PlayerHand() {}

void PlayerHand::print(std::ostream& file) {
  int count = 0;
    for(Node* node = getHead(); node; node = node->next) {
      file << node->tile->colour;
      file << node->tile->shape;
      if(count < (size()-1)) {     
        file << ", ";
      }
      count++;
    }
    file << "\n";
}

// Insertion by order of shape. Colour then shape.
void PlayerHand::add(Node *node) {
    Node *head = nullptr;
    // if head is null it's the inital adding to the linked list, or if it is the smallest tile (meaning smallest colour and shape)
    if (head == nullptr || (head->tile->colour >= node->tile->colour && head->tile->shape >= node->tile->shape)) {
        node->next = getHead();
        setHead(node);
        head = getHead(); 
    } else {
        // as know that head is not null, can initialise it and start looping from head node
        head = getHead();
        Node *current = head;
        //loops through colours first and then the shapes
        while(current->next!=nullptr && current->next->tile->colour < node->tile->colour) {
            current = current->next;
        }
        while(current->next!=nullptr && (current->next->tile->shape < node->tile->shape) && (current->next->tile->colour == node->tile->colour)) {
            current = current->next;
        } 
        //once found where node should be inserted in LinkedList, insert it.
        node->next = current->next;
        current->next = node;
    }
}

bool PlayerHand::tileExistsInHand(Tile* tile) {
    bool exists = false;
    for(Node *node = getHead(); node; node = node->next) {
        if ((node->tile->colour == tile->colour) && 
            (node->tile->shape == tile->shape)) {
            exists = true;
        }
    }
    return exists;
}

void PlayerHand::removeNode(Node* node) {
    Node* prev = nullptr;
    for(Node *loopNode = getHead(); loopNode; loopNode = loopNode->next) {
        if ((node->tile->colour == loopNode->tile->colour) && (node->tile->shape == loopNode->tile->shape)) {
            if(prev != nullptr) {
                prev->next = loopNode->next;
                // delete loopNode; TODO figure out if relevant
            } else {
                setHead(loopNode->next);
            }
        }
    prev = loopNode;
    }
}
#include "TileBag.hpp"

TileBag::TileBag() {
    fillBag();
}

TileBag::~TileBag() {
  
}

//fill in order
void TileBag::fillBag() {
  for(int i = 0; i < 2; i++) {
    for(Colour colour: COLOURS) {
      for(Shape shape: SHAPES) {
        push(new Node(new Tile(colour, shape)));
      }
    }
  }
  //LinkedList method
  shuffle();
}

void TileBag::print(std::ostream& file) {
    for(Node* node = getHead(); node; node = node->next) {     
        file << node->tile->colour;
        file << node->tile->shape << ", ";
    }
    file << "\n";
}




#ifndef CRITTER_H
#define CRITTER_H

typedef unsigned char CritterID;

// A critter's Memory of one other Critter
class Memory {
 public:
  // Is this who I'm thinking of?
  bool AssociatedP(CritterID otherID) { return otherID == this->otherID; } 

  // Constructors are awesome
  Memory(): otherID(0) {}

 private:
  CritterID otherID; // Who I'm thinking of
};

#endif /* CRITTER_H */

/*
Author: Camilla Calle
Date: April 1st, 2023
File: CardShop.cpp
Description: In this file I wrote the implementation for the sorting algorithms BubbleSort, InsertionSort.
(Did not complete quickSort and mergeSort.)
*/


#include "CardShop.hpp"
#include "Node.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


/**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
CardShop::CardShop(std::string input_file_name) 
{
  std::ifstream fin(input_file_name);
  if (fin.fail())
  {
    std::cerr << "File cannot be opened for reading. \n";
    exit(1); // exit if failed to open the file
  }
  //we don't use the first line
  std::string ignore;
  getline(fin, ignore);

  //the columns of the csv associated with the data members
  std::string name, type, race, attribute;
  int level_rank, atk, def;

  std::string temp_string;
  int temp_int;
  int item_counter = 0;
  while (getline(fin, temp_string, ','))
  {
    name = temp_string;

    getline(fin, type, ',');
  
    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    level_rank = temp_int;

    getline(fin, race, ',');

    getline(fin, attribute, ',');

    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    atk = temp_int;

    getline(fin, temp_string);
    std::istringstream(temp_string) >> temp_int;
    def = temp_int;

    //create new card
    YGOCard *card_ptr = new YGOCard(name, type, level_rank, race, attribute, atk, def);

    //add to linked list and increment counter
    insert(item_counter++, card_ptr);
  }
}

//@post: removes all cards from the shop
//Deallocate and delete items
void CardShop::clear()
{
  for (int i = 0; i < item_count_; i++)
  {
    YGOCard *ptr = getItem(i);
    delete ptr;
    ptr = nullptr;
  }
  DoublyLinkedList::clear();
}

//destructor
CardShop::~CardShop()
{
  clear();
}

//@post: displays information of all cards in the shop, one per line
void CardShop::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    getItem(i)->display();
  }
}

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
void CardShop::displayName(int startRange, int endRange)
{
  for (int i = startRange; i <= endRange; i++)
  {
    getItem(i)->displayName();
    if (i != endRange)
    {
      std::cout << ", ";
    }
    else
    {
      std::cout << std::endl;
    }
  }
}


//@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
bool CardShop::operator==(const CardShop &rhs) const
{
  if (getLength() != rhs.getLength())
  {
    return false;
  }
  for (int i = 0; i < getLength(); i++)
  {
    if (*(getPointerTo(i)->getItem()) == *(rhs.getPointerTo(i)->getItem()))
    {
    }
    else
    {
      return false;
    }
  }
  return true;
}

//Sorting Algorithms:
//quickSort
//mergeSort
//Sorting algorithms
//bubbleSort
//insertionSort

//mergeSort
template<class Comparator>
int CardShop::mergeSort(Comparator comp, std::string key){
}

//quickSort: Recursive Algorithm 
template <typename Comparator>
int CardShop::quickSort(Comparator comp, std::string key){
}

//bubbleSort
//DoublyLinkedList
//sorting functions will be templated, and will have a template Comparator parameter. 
//Using BubleSort I used the elements in the Linked List and sorted them in ascending order and descending order. 
//if(a > b) and then  swap won't work if we want to sort in the reverse order

template <typename Comparator>
int CardShop::bubbleSort(Comparator comp, std::string key){
  int counter = 0;
  for (int i = 0; i < item_count_; i++){
    for (int j = 0; j < item_count_ - i - 1; j++){
      if (key == "atk" && comp(getItem (j + 1) -> getAtk(), 
      getItem(j) -> getAtk())){
        swap(j, (j + 1)); 
        counter++;
      }
      if (key == "def" && comp(getItem (j + 1) -> getDef(), 
      getItem(j) -> getDef())){
        swap(j, (j + 1));
        counter++; 
      }
    }
  }
  std::cout << counter << '\n';
  return counter; //all sorting functions MUST RETURN THE NUMBER OF SWAPS performed by the sorting algorithm
}

//insertionSort 
//DoublyLinkedList
//For each node in doubly linked list we will visit and insert the node into our resulting list in a sorted manner.
//Select unsorted element, swap other elements to right and shift unsorted element. Then traverse list.

template<typename Comparator>
int CardShop::insertionSort(Comparator comp, std::string key){
  int counter = 0;
  for (int i = 1; i < item_count_; i++){
    int current = i;
    while ((current > 0) && key == "atk" && comp(getItem(current) 
    -> getAtk(), getItem(current - 1) -> getAtk())){
      swap(current, (current - 1));
      current--;
      counter++; 
    }
    while ((current > 0) && key == "def" && comp(getItem(current) 
    -> getDef(), getItem(current - 1) -> getDef())){
      swap(current, (current - 1));
      current --;
      counter ++; 
    }
  }
  std::cout << counter << '\n';
  return counter; //all sorting functions MUST RETURN THE NUMBER OF SWAPS performed by the sorting algorithm
}

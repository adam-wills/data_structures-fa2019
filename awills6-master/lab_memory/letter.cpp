/**
 * @file letter.cpp
 * Implementation of the Letter class.
 */

#include "letter.h"

// default constructor
Letter::Letter() : letter('-'), count(0)
{
}

// copy constructor
Letter::Letter(const Letter& other) : letter(other.letter), count(other.count)
{
}

// assignment operator
Letter& Letter::operator=(const Letter& other)
{
  this->letter = other.letter;
  this->count = other.count;
  return *this;
}

// destructor
Letter::~Letter()
{
}

void Letter::addStudent()
{
    count++;
}

bool Letter::operator<(const Letter& other) const
{
    return count > other.count;
}

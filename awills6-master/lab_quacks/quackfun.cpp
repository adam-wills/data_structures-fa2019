/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {
  using RecursionExercises::triangle;

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
  if (s.empty()) {return 0;} // nothing left to sum
  T val = s.top(); // store top element (each element kept individually on runtime stack)
  s.pop(); // pop top element
  T stackSum = sum(s); // sum remaining elements
  s.push(val); // puts elements back in reverse order, restoring stack
  return val + stackSum; // return stack.top() + sum of remaining elements
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
    stack<char> local;
    if (input.empty()) {return true;}
    if (input.back() == '[') {
      local.push(input.back());
    }
    else if (input.back() == ']') {
      if (local.empty()) {return false;}
      else {local.pop();}
    }
    input.pop();
    return isBalanced(input);
}


// Helper function for the scramble which determines if the
// iteration is odd or even and performs the appropriate pushes/pops
// feels like I'm doing it backwards
// why cant I just use deque
// waaah waaah
template <typename T,typename S>
void scramble_helper(queue<T>& q, stack<T>& s, S n) {
  S i = 0;
  if (n % 2 == 1) {
    for (i = 0; i < n; ++i) {
      T& temp = q.front();
      q.pop();
      q.push(temp);
    }
  }
  else{
    for (i = 0; i < n; ++i) {
      s.push(q.front());
      q.pop();
    }
    while (s.size()) {
      q.push(s.top());
      s.pop();
    }
  }
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
  stack<T> s{};
  int n = 0;
  int n_items = 0;
  while ((unsigned long)n_items < q.size()) {
    ++n;
    n_items = triangle(n);
  }
  n_items -= n;
  unsigned long l_diff = q.size() - (unsigned long)(n_items);

  int i = 1;
  while (i < n) {
    scramble_helper<T,int>(q,s,i);
    ++i;
  }
  scramble_helper<T,unsigned long>(q,s,l_diff);
}


/**
 * Checks if the parameter stack and queue are the same. A stack and a queue
 * are considered to the "the same" if they contain only elements of exactly
 * the same values in exactly the same order.
 *
 * @note You may assume the stack and queue contain the same number of items!
 *
 * @note The back of the queue corresponds to the top of the stack!
 *
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 *
 * @param s The stack to compare
 * @param q The queue to compare
 * @return  true if the stack and the queue are the same; false otherwise
 */

template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{

  bool retVal = true; // innocent until proven guilty
  /*
  T s_top = s.top(); // individual local variables stored on stack frame for each recursive call
  T q_front = q.front();
  q.pop();
  if (!q.empty()) {
    //q.pop();
    retVal = verifySame(s,q); //calls first four lines recursively until q is empty
  }
  s.pop(); // pop s after recursion so as to pop only once (compare top of s to back of q)
  if (q_front != s_top) {
    retVal = false;
    return retVal;
  }
  //else {retVal = true;}
  s.pop();
  q.push(q_front);
  s.push(s_top);
  */
  return retVal;
}

}

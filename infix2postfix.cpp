#include "stack.hpp"

using namespace std;

// Auxiliary method, you probably find it useful
// Operands are all lower case and upper case characters
bool isOperand(char c){
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Auxiliary method, you probably find it useful
int precedence(char c)
{
  if(c == '+' || c == '-'){
    return 0;
  }
  if(c == '*' || c == '/'){
    return 1;
  }
  if(c == '^'){
    return 2;
  }
  return -1;
}

int main(){
  freopen("input_infix2postfix.txt", "r", stdin);
  string input;
  string solution;
  int line_counter = 0;
  while(cin >> solution){
    cin >> input;
    Stack<char> stack;
    string result;

     //The input file is in the format "expected_solution infix_expression", 
     //where expected_solution is the infix_expression in postfix format

    for(int i=0; i<input.length(); ++i){
      // WRITE CODE HERE to store in 'result' the postfix transformation of 'input'
      if(isOperand(input[i]))
      {
        result += input[i]; //if an operand, append to result and go to next char in input
        continue;
      }

      if(input[i] == '(') //push open parenthesis
      {
        stack.push(input[i]);
      }

     else if (input[i] == ')')
      {
        while(stack.size() > 0 && stack.peek() != '(') //if input is ')' pop and append to result until find '('
        {
          
            result += stack.peek();
            stack.pop();
        }

        if(stack.size() > 0 && stack.peek() == '(')
         {
            stack.pop(); //discard the open parenthesis from stack
         }
      }
      else{
        while(stack.size() != 0 && precedence(stack.peek()) >= precedence(input[i]))
        {
          result += stack.pop();// keep popping while stack has higher precedence
                                // push on stack when input has lower precedence or stack is empty
        }
        stack.push(input[i]);
      }

    }
         while(stack.size() > 0 ) // pop from stack and append to result while stack has higher precedence than input operator
          {
            result += stack.peek();
            stack.pop();
           
          }
        
      
      
    
    
    
    // You need to do some extra stuff here to store in 'result' the postfix transformation of 'input'
    
    // Checking whether the result you got is correct
    if(result == solution){
      cout << "line " << line_counter << ": OK [" << solution << " " << result << "]" << endl;
    }else{
      cout << "line " << line_counter << ": ERROR [" << solution << " " << result << "]" << endl;
    }
    line_counter++;
  }
}

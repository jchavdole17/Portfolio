#  File: ExpressionTree.py
#  Description:
#  Student Name: Juan Chavarria
#  Student UT EID: jac23763
#  Partner Name: Antonio Gonzales
#  Partner UT EID: ag72672

import sys

operators = ['+', '-', '*', '/', '//', '%', '**']


# Stack Class
# Purpose: Used by the Tree Class to keep track of parenthesis and operators.
# You do not need to make changes to this class.
class Stack (object):
    def __init__(self):
        self.stack = []

    def push(self, data):
        self.stack.append(data)

    def pop(self):
        if(not self.is_empty()):
            return self.stack.pop()
        else:
            return None

    def is_empty(self):
        return len(self.stack) == 0


# Node Class
# Purpose: Used by the Tree Class to represent one operand or operators
#          in a binary expression. It includes data (a character) and
#          two pointers, to the left and right child nodes.
# You do not need to make changes to this class.
class Node(object):
    def __init__ (self, data = None, lChild = None, rChild = None):
        self.data = data
        self.lChild = lChild
        self.rChild = rChild
    


# Tree Class
# Purpose: To represent the string representation of operators and operands 
#          of a binary expression so it can be evaluated. 
# You need to make a lot f changes to this class!
class Tree (object):
    def __init__ (self):
        self.root = None
    
    # Input - String binary expression
    # Process - Converts the string to a binary expression tree representation
    # Output - The address of the root of the binary expression tree
    def create_tree (self, expr):
        # Create a stack to store internal nodes and the root
        s = Stack()
        func = expr.split() 
        
        # Set root to an empty Node
        self.root = Node()
        current = self.root
        
        # Iterate through every value in a function
        for i in func:
            
            # Left parenthesis creates a new node to the left
            if i == '(':
                node = Node()
                current.lChild = node
                s.push(current)
                current = current.lChild
            
            # Operators create right child node 
            elif i in operators:
                current.data = i
                s.push(current) # Store internal node in stack to go back
                current.rChild = Node()
                current = current.rChild
            
            # Check if i is an integer or a float (operand)
            elif i.isnumeric() or i.replace('.','',1).isdigit() == True:
                # Store i as a string
                current.data = i
                current = s.pop() # Goes back to parent node in stack
                
            # Right parenthesis indicates expression end (pop back to parent)
            elif i == ')':
                if s.is_empty() == False:
                    current = s.pop()
        
        # Return the address
        return self.root.data
    
    
    # Input - Binary Expression Tree Root
    # Process - Evaluates tree nodes to arrive at algebraic result 
    # Output - Integer or double expression result
    def evaluate(self, aNode):
        # Base case for leaf nodes (return empty string)
        if aNode is None:
            return ''
        
        # Recursively call the left node
        l = self.evaluate(aNode.lChild) 
        # Recursively call right nodes after left node
        r = self.evaluate(aNode.rChild)
        
        # Return a float for the root recursion only
        if aNode == self.root:
            return float(eval(l + aNode.data + r))
        
        # Return the evaluated left, middle, and right data 
        # Adheres to PEMDAS (number, operator, number) 
        return str(eval(l + aNode.data + r))
      
    
    # Input - Binary Expression Tree
    # Process - Performs preorder traversal of tree
    # Output - String version of expression in preorder notation 
    def pre_order(self, aNode):
        # Base case for lead nodes (return empty string) 
        if aNode == None:
            return ''
        # Recursively call left and right child
        l = self.pre_order(aNode.lChild)
        r = self.pre_order(aNode.rChild)
        
        # Structure return to print parent nodes first followed by children
        # Since left is called recursively first, left half will be first
        return (aNode.data + ' ' + l + r)
    
    
    # Input - Binary Expression Tree
    # Process - Performs postorder traversal of tree
    # Output - String version of expression in postorder notation 
    def post_order (self, aNode):
        # Base case for lead nodes
        if aNode == None:
            return ''
        
        # Recursively call left and right child
        l = self.post_order(aNode.lChild)
        r = self.post_order(aNode.rChild)
        
        # Return left and right nodes followed by parent node
        return (l + r  + ' ' + aNode.data)
        
        
# Do not change main(), except to change the debug flag before you submit.

def main():

    # Debug flag - set to False before submitting
    debug = True
    if debug:
        in_data = open('expression.in')
    else:
        in_data = sys.stdin
        
    # Read infix expression
    line = in_data.readline()
    expr = line.strip()
 
    tree = Tree()
    tree.create_tree(expr)
    
    # evaluate the expression and print the result
    print(expr, "=", str(tree.evaluate(tree.root)))

    # get the prefix version of the expression and print
    print("Prefix Expression:", tree.pre_order(tree.root).strip())

    # get the postfix version of the expression and print
    print("Postfix Expression:", tree.post_order(tree.root).strip())

if __name__ == "__main__":
    main()

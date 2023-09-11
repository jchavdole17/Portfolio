#  File: Josephus.py
#  Student Name: Juan Chavarria
#  Student UT EID: jac23763
#  Course Name: CS 313E
import sys

# This class represents one soldier. 
class Link():
    # Constructor
    def __init__ (self, data, next = None):
        self.data = data
        self.next = next
    def __str__(self):
        return str(self.data)
  
    
class CircularList():
    # Constructor
    def __init__ (self):
        self.tail = None
        self.head = None
        
    # return the size of the list
    def get_size(self):
        current = self.tail
        
        if self.is_empty() == True:
            return 0
        else:
            count = 1
            while current.next != self.tail:
                count += 1
                current = current.next 
            return count
    
    # returns true if emppty, otherwise false
    def is_empty(self):
        if self.tail == None:
            return True
        else:
            return False

    # Append an item at the end of the list
    def insert (self, newNode):
        n = Link(newNode)
        if self.tail == None:
            n.next = n
            self.head = n
            self.tail = n
            
        else: 
            n.next = self.head
            self.tail.next = n
            self.tail = self.tail.next
                 
    
    # Find the node with the given data (value)
    # or return None if the data is not there
    def find (self, data):
        # Check if the list is empty
        if self.is_empty() == True:
            return None
    
        # Check if the tail is the data value
        if data == self.tail.data:
            return self.tail
        
        # traverse through the rest of the list to find the data value
        current = self.head
        while (current != self.tail):
            if data == current.data:
                return current
            current = current.next
        
        # return None if value is not found
        return None
                
    
    # Delete a Link with a given data (value) and return the node
    # or return None if the data is not there
    def delete (self, data):
        
        # If list is empty, do nothing
        if self.is_empty() == True:
            return 
        
        # If there is one value, set tail equal to None 
        # (we need to return the value so I didn't set head equal to None)
        if self.get_size() == 1:
            b = self.tail
            self.tail = None
            self.head = None
            return b
            
        # For more than 1 value, check if data is in the list
        search = self.find(data)
        if search == None:
            return None
        
        # if the value to change is the head, reassign tail and head
        if search == self.head:
            self.head = self.head.next
            self.tail.next = self.head
            return search
        
        # Since value is in the list, find the value before data
        previous = self.tail
        while previous.next != search:
            previous = previous.next
        # If the value to delete is the tail, assign new tail
        if previous.next == self.tail:
            self.tail = previous
            self.tail.next = self.head
            return search
        # If the value is any other value in the list,
        previous.next = search.next
        return search
        
    # Delete the nth node starting from the start node
    # Return the data of the deleted node AND return the
    # next node after the deleted node in that order
    def delete_after (self, start_count, count):
        if self.is_empty() == True:
            return
        
        current = self.find(start_count) 
        for i in range(count-1):
            current = current.next
            
        d = current
        self.delete(current.data) # Delete function takes in an integer
        return(d.data, d.next)
    
    # Return a string representation of a Circular List
    # The format of the string will be the same as the __str__
    # format for normal Python lists
    
    def __str__ (self):
        if self.tail == None: # for empty list
            return '[]'
        
        if self.get_size() == 1:
            return '[' + str(self.head) + ']'
        
        s = '[' + str(self.head) + ', '
        c = self.head.next
        while c != self.tail:
            s = s + str(c) + ', '
            c = c.next
        s = s + str(c) + ']'
        return s
    
def main():
      
    # Debug flag - set to False before submitting
    debug = True
    if debug:
        in_data = open('josephus.in')
    else:
        in_data = sys.stdin
  
    # read the three numbers from the file
    line = in_data.readline().strip()
    num_soldiers = int(line)
  
    line = in_data.readline().strip()
    start_count = int(line)

    line = in_data.readline().strip()
    count = int(line)

    # Add code here
    
    # Create list and create the right amount of soldiers
    circular_list = CircularList()
    for i in range(1,num_soldiers+1):
        circular_list.insert(i)
    # print(circular_list)
    # Remove soldiers until one is left
    for i in range(num_soldiers-1):
        n = circular_list.delete_after(start_count, count)
        print(n[0]) # Print the data of deleted value
        start_count = n[1].data # update start count with man after
    print(circular_list.tail.data) # print surviving person
   
    
  

if __name__ == "__main__":
    main()
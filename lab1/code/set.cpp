#include "set.hpp"

/*
 * std::size_t is defined in the C++ standard library
 * std::size_t is an unsigned integer type that can store the maximum size of any possible object
 * sizes are non-negative integers -- i.e. unsigned integer type
 */

/* *********** class Node ************ */

// This class is private to class Set
// but all class Node members are public to class Set
class Set::Node {
public:
    // Constructor
    Node(int nodeVal = 0, Node* nextPtr = nullptr) : value{nodeVal}, next{nextPtr} {
        ++count_nodes;
    }

    // Destructor
    ~Node() {
        --count_nodes;
        assert(count_nodes >= 0);  // number of existing nodes can never be negative
    }
    int value;
    Node* next;

    // Total number of existing nodes -- used only to help to detect bugs in the code
    // Cannot be used in the implementation of any member functions
    static std::size_t count_nodes;

    friend std::ostream& operator<<(std::ostream& os, const Set& rhs);
};

/* ************************************ */

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/* *********** class Set member functions ************ */

// Default constructor
Set::Set() : head{new Node{}}, counter{0} {  // creates the dummy node
}

// Constructor for creating a singleton {x}
Set::Set(int x) : Set() {
	head->next = new Node{ x, nullptr }; // creates the first node with value x and next pointer is nullptr
	counter = 1; // set counter to 1 since there is only one element in the set (singleton)
}

// Constructor: create a set with elements
// elements is not sorted and values in it may not be unique
Set::Set(const std::vector<int>& elements) : Set() {
    /*
     * Sorting a vector cannot used here
     * std::sort and std::unique cannot be used
     */
   
    for(int value : elements) {

        insert(value);

    /*
		Node* ptr1 = head; // start at the dummy node
        while (ptr1->next != nullptr && ptr1->next->value < value) { // If not ptr1 next is nullptr and ptr1next value is less than value
            //Then set ptr1 to next node
            ptr1 = ptr1->next;
        }

		if (ptr1->next == nullptr || ptr1->next->value != value) {
			// If the value is not the last node or the value is not equal to the value of the next node
            ptr1->next = new Node(value, ptr1->next);
			// create a new node with the value and the next pointer is the next node
            counter++;
			// increment the counter
		}*/
    }
    //Converts the unsorted, potentially duplicate-containing elements vector into a unique, sorted linked list.
    


}

// copy constructor
Set::Set(const Set& rhs) : Set() {
    // ADD CODE
    Node* src = rhs.head->next; //Skip the dummy node from vector rhs
	Node* ptr1 = head; //first node (dummy node)

	while (src != nullptr) { // loop through the list
		ptr1->next = new Node(src->value, nullptr); // create a new node with the value of the source node
		ptr1 = ptr1->next; // move to the next node
		src = src->next; // move to the next node
    }

	counter = rhs.counter; // copy the counter
    
}

// Assignment operator: use copy-and-swap idiom
Set& Set::operator=(Set rhs) {

    std::swap(head, rhs.head);
    std::swap(counter, rhs.counter); // Swap the counters
    return *this; // Return the current object for chaining
}

// Destructor: deallocate all nodes
Set::~Set() {
    
	Node* ptr1 = head; //start at the dummy node

	while (ptr1 != nullptr) { // loop through the list
		Node* ptr2 = ptr1->next; // node to be removed
		delete ptr1; // deallocate the node
		ptr1 = ptr2; // move to the next node
    }

    /*
	Node* ptr1; // find the node prior to the node to be removed
	Node* ptr2 = ptr1->next; // node to be removed
	ptr1->next = ptr2->next; 

	delete ptr2; // deallocate the node
    */
}

// Return number of elements in the set
std::size_t Set::cardinality() const {
	return counter; 
}

// Test if set is empty
bool Set::empty() const {
	if (counter == 0) { // if the counter is 0, the set is empty
		return true; 
	}
    return false;
}

// Test if x is an element of the set
bool Set::member(int x) const {
    Node* ptr1 = head;
    while(ptr1->next != nullptr) { //While check if ptr1 value the same as x
        if (ptr1->next->value == x) {
            return true;
        }
        ptr1 = ptr1->next; // if not jump to next node
    }
    return false;  // delete, if needed
}

// Return true, if *this is a subset of Set b
// Otherwise, false is returned
bool Set::is_subset(const Set& b) const {

	Node* ptr1 = head->next; // start at the first node of the current set
	while (ptr1 != nullptr) { // loop through the list
		if (!b.member(ptr1->value)) { // if the value of the current node is not in the other set
			return false; // return false
		}
		ptr1 = ptr1->next; // move to the next node
    }
    return true;  
}

// Return a new Set representing the union of Sets *this and b
// Repeated values are not allowed
// Implement an algorithm similar to the one in exercise 3/Set 1, but don't use vectors
Set Set::set_union(const Set& b) const {
    // ADD CODE
    Node* ptr1 = head->next;
    Node* ptr2 = b.head->next;
    Set S3;

    while(ptr1 != nullptr && ptr2 != nullptr) {
        if(ptr1->value < ptr2->value) {
            S3.insert(ptr1->value);
            ptr1 = ptr1->next;

        }
        else if (ptr1->value > ptr2->value) {
			S3.insert(ptr2->value);
            ptr2 = ptr2->next;

        } else {
            S3.insert(ptr1->value); //eller ptr2->value spelar ingen roll
            ptr1 = ptr1->next;
			ptr2 = ptr2->next;
        }
    }


	//If one of the sets is longer than the other it will run this loop
    while (ptr1 != nullptr) {
        S3.insert(ptr1->value);
        ptr1 = ptr1->next;
    }

	while (ptr2 != nullptr) {
		S3.insert(ptr2->value);
		ptr2 = ptr2->next;
	}
    return S3;
}

// Return a new Set representing the intersection of Sets *this and b
Set Set::set_intersection(const Set& b) const {
	Node* ptr1 = head->next;
	Node* ptr2 = b.head->next;
	Set S3;

	while (ptr1 != nullptr && ptr2 != nullptr) {
		if (ptr1->value < ptr2->value) {
			ptr1 = ptr1->next;

		}
		else if (ptr1->value > ptr2->value) {
			ptr2 = ptr2->next;

		}
		else {
			S3.insert(ptr1->value); //eller ptr2->value spelar ingen roll
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
	}
    return S3;  // delete, if needed
}

// Return a new Set representing the difference between Set *this and Set b
Set Set::set_difference(const Set& b) const {
	Node* ptr1 = head->next;
	Node* ptr2 = b.head->next;
	Set S3;

	while (ptr1 != nullptr && ptr2 != nullptr) {
		if (ptr1->value < ptr2->value) {
            S3.insert(ptr1->value);
			ptr1 = ptr1->next;

		}
		else if (ptr1->value > ptr2->value) {
			ptr2 = ptr2->next;

		}
		else {
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
	}

    while (ptr1 != nullptr) {
		S3.insert(ptr1->value);
		ptr1 = ptr1->next;
    }
	return S3;
 
}

std::ostream& operator<<(std::ostream& os, const Set& rhs) {
    if (rhs.empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* ptr = rhs.head->next;
        os << "{ ";

        while (ptr != nullptr) {
            os << ptr->value << " ";
            ptr = ptr->next;
        }
        os << "}";
    }
    return os;
}

/********** Private member functions ************/

//fixa ny insert som inte går igenom allt

// Insert a new node with value x
void Set::insert(int x) {
	Node* ptr1 = head->next; // start at the dummy node
	Node* ptr2 = head; // start at the dummy node

	while (ptr1 != nullptr && ptr1->value < x) { // loop through the list
		ptr2 = ptr1; // move to the next node
		ptr1 = ptr1->next; // move to the next node
	}

	if (ptr1 == nullptr || ptr1->value != x) { 
        // if the value is not the last node or the value is not equal to the value of the next node
		
        ptr2->next = new Node(x, ptr1);
		counter++;
	}

    /*Or use from lecture 2, insert node {
    Node ptr1 = new Node;
    ptr1->value = 5
    ptr->next = L
    L = ptr
    }*/
}
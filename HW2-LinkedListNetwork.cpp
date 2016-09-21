// ==========================================
// File: Homework 2
// Author: Muntadher AlZayer
// Date: 9/20/2016
// Description: Linked List HW
// ==========================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct city
{
    string 	name; 			// name of the city
    city 	*next; 			// pointer to the next city
	int 	numberMessages;	// how many messages passed through this city
    string 	message; 		// message we are sending accross
};

city* addCity(city *head, city *previous, string cityName );
city* deleteCity(city *head, string cityName);
city* deleteEntireNetwork(city *head);
city* searchNetwork(city *head, string cityName);
city* loadDefaultSetup(city *head);
void transmitMsg(city *head, string receiver, string filename);
void printPath(city *head);
void displayMenu();
city* handleUserInput(city *head);

/* Do NOT modify main function */
int main(int argc, char* argv[])
{
    // pointer to the head of our network of cities
    city *head = NULL;

	head = handleUserInput(head);
	printPath(head);
	head = deleteEntireNetwork(head);
	if (head == NULL)
		cout << "Path cleaned" << endl;
	else
		printPath(head);

	cout << "Goodbye!" << endl;
    return 0;
}

/*
 * Purpose: handle the interaction with the user
 * @param head the start of the linked list
 * @return the start of the linked list
 * Do NOT modify
 */
city* handleUserInput(city *head)
{
    bool quit = false;
    string s_input;
    int input;

    // loop until the user quits
    while (!quit)
    {
        displayMenu();

		// read in input, assuming a number comes in
        getline(cin, s_input);
		input = stoi(s_input);

        switch (input)
        {
            // print all nodes
            case 1: 	//rebuild network
                head = loadDefaultSetup(head);
                printPath(head);
                break;

            case 2:		// print path
                printPath(head);
                break;

            case 3: //message is read in from file
			  {
        		string cityReceiver;
				cout << "Enter name of the city to receive the message: " << endl;
				getline(cin, cityReceiver);

				cout << "Enter the message to send: " << endl;
				string message;
				getline(cin, message);

                transmitMsg(head, cityReceiver, message);
			  }
                break;

            case 4:
			  {
        		string newCityName;
        		string prevCityName;
                cout << "Enter a new city name: " << endl;
                getline(cin, newCityName);

                cout << "Enter the previous city name (or First): " << endl;
                getline(cin, prevCityName);

                // find the node containing prevCity
    			city *tmp = NULL;
                if(prevCityName !="First")
                    tmp = searchNetwork(head, prevCityName);
                // add the new node
                head = addCity(head, tmp, newCityName);
                printPath(head);
			  }
                break;

            case 5: 	// delete city
			  {
        		string city;
                cout << "Enter a city name: " << endl;
                getline(cin, city);
                head = deleteCity(head, city);
                printPath(head);
			  }
                break;

            case 6: 	// delete network
                head = deleteEntireNetwork(head);
                break;

            case 7: 	// quit
                quit = true;
				cout << "Quitting... cleaning up path: " << endl;
                break;

            default: 	// invalid input
                cout << "Invalid Input" << endl;
                break;
        }
    }
	return head;
}

/* 
 * Purpose: Add a new city to the network 
 *   between the city *previous and the city that follows it in the network. 
 * @param head pointer to start of the list
 * @param previous name of the city that comes before the new city
 * @param cityName name of the new city
 * @return pointer to first node in list
 */
city* addCity(city *head, city *previous, string cityName )
{
	city* add = new city; //to distinguish and create the new node, i named it add
	add->name = cityName;
	city* tmp = new city;
	tmp=head;
	while(tmp != NULL && previous != tmp){
	 tmp = tmp->next;	
	}
	if(tmp == NULL){
		if(head == NULL){ // if the head is null then it creates a node for the head
			head = add;
			add->next = NULL;
		}
		return head;
	}
	else{
		add->next = tmp->next; //the pointer for the new node will be the next of the prev node
		tmp->next = add; // the prev node will now point to the new node
	}
	

    return head;
}


/*
 * Purpose: Search the network for the specified city and return a pointer to that node
 * @param ptr head of the list
 * @param cityName name of the city to look for in network
 * @return pointer to node of cityName, or NULL if not found
 * @see addCity, deleteCity
 */
city *searchNetwork(city *ptr, string cityName)
{
	city *tmp = new city;
	tmp = ptr;
	while(tmp != NULL && tmp->name != cityName){
		tmp = tmp->next;
	}
    return tmp;
}

/*
 * Purpose: deletes all cities in the network starting at the head city. 
 * @param ptr head of list
 * @return NULL as the list is empty
 */
city* deleteEntireNetwork(city *ptr)
{
	city *tmp = new city;
	while(ptr->next != NULL){
		tmp = ptr->next;
		cout << "deleting: " << ptr->name << endl;
		delete ptr;
		ptr = tmp;
	} //stops at the last node, so we need to delete it and make ptr = null
	cout << "deleting: " << ptr->name << endl;
	delete ptr;

	cout << "Deleted network" << endl;
    // return head, which should be NULL
    return ptr;
}

/* sends messages from file */
void transmitMsg(city *head, string receiver, string message)
{
	city *sender = new city;
	sender = head;

    if(head == NULL)
	{
        cout << "Empty list" << endl;
        return;
    }
	else{
		while(sender != NULL && sender->name != receiver){
			sender->numberMessages = sender->numberMessages + 1; //adds to the amount of times the city has intercepted a message
			sender->message = message; //the message will be changed everytime for every city
		    	cout << sender->name << " [# messages passed: " << sender->numberMessages << "] received: " << sender->message << endl;
			sender = sender->next; // moves on to the next city

		} // when the destination city is found the same 3 lines of code above will run but will end in termination of the function
		sender->numberMessages = sender->numberMessages +1;
		sender->message = message;
	    	cout << sender->name << " [# messages passed: " << sender->numberMessages << "] received: " << sender->message << endl;
		}
}


/* 
 * Purpose: delete the city in the network with the specified name. 
 * @param head first node in list
 * @param cityName name of the city to delete in the network
 * @return head node of list 
 */
city* deleteCity(city *head, string cityName)
{

	city *tmp = new city; //will traverse the list
	city *prev = new city; // will hold the previous city for tmp
	tmp = head;
	while(tmp != NULL && tmp->name != cityName){
		prev = tmp; 
		tmp = tmp->next;
	}
	if(tmp == NULL){
        cout << "City does not exist." << endl;
	}
	else{
		prev->next = tmp->next; //changes the previous next pointer to skip the deleted node
		delete tmp;
	}


    return head;
}


/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void printPath(city *ptr)
{
    cout << "== CURRENT PATH ==" << endl;

    if (ptr == NULL){
        	cout << "nothing in path" << endl;
	}
	else{
		city *tmp = new city; //to traverse the linked list
		tmp = ptr;
		while(tmp !=NULL){ //ends the traversal at the end of the list
			cout << tmp->name << " -> ";
			tmp = tmp->next;
		}
		cout << "NULL"<<endl; // prints null showing the end of the list
	}




    cout << "===" << endl;
}

/* 
 * Purpose: populates the network with the predetermined cities 
 * @param head start of list
 * @return head of list
 */
city* loadDefaultSetup(city *head)
{
//default network setup by adding all the cities after each other with tmp being the tail
    head = addCity(head,NULL,"Los Angeles");
	city *tmp = new city;
	tmp = head;
	addCity(head,tmp,"Pheonix");
	tmp = tmp->next;
	addCity(head,tmp,"Denver");
	tmp = tmp->next;
	addCity(head,tmp,"Dallas");
	tmp = tmp->next;
	addCity(head,tmp,"Atlanta");
	tmp = tmp->next;
	addCity(head,tmp,"New York");
    return head;
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
	cout << "Select a numerical option:" << endl;
    cout << "======Main Menu=====" << endl;
    cout << "1. Build Network" << endl;
    cout << "2. Print Network Path" << endl;
    cout << "3. Transmit Message" << endl;
    cout << "4. Add City" << endl;
    cout << "5. Delete City" << endl;
    cout << "6. Clear Network" << endl;
    cout << "7. Quit" << endl;
}


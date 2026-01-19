#include <iostream>
#include <string>
using namespace::std;

class book{
	public:
		int bookid;
		std::string book_title;
		bool isavailable;
		book(int id , string t){
			bookid=id;
			book_title=t;
			isavailable=true;
		}
		
		void display(){
			
			cout<<"\tBook ID: "<<bookid<<"\t"<<"Book Title: "<<book_title<<"\t"<<"Availablity: "<<isavailable<<endl;
		}
};
//Node class will have object of Book class
//This node classwill be used by Linklist store the different objects of Book class
class node{
	public:
		book* data;
		node* next;
		
		node(book* b){
			data=b; next=NULL;
		}
};
//Link list data structure is used to dynamically store objects.The different objects are stored randomly in memory
//Head pointer of Linklist point to the first object of Node(which has object of book and refrence of next object)
class linklist{
	public:
		node* head=NULL;
		node* tail=NULL;
	//insertion at head for O(1) time complexity
		void insert(book* b){
			node* newnode = new node(b);
			if(head==NULL){
				head=tail=newnode;
				return;
			}
			else{
			newnode->next=head;
			head=newnode;	
		}
		}
	//search function to find if a certain book is found in Library or not
		void search_LL(int k){
			if(head == NULL){
				cout<<"Empry list"<<endl;
				return ;
			}
			node* temp=head;
			while(temp != NULL){
				if( temp->data->bookid == k){
					cout<<"Book with ID"<<k<<" Found"<<endl;
					cout<<"--------------------------"<<endl;
					temp->data->display();
					cout<<"--------------------------"<<endl;
					break;
				}
				temp=temp->next;
			}
			cout<<"--------------------------"<<endl;
			cout<<"Book with ID"<<k<<" Not Found"<<endl;
			cout<<"--------------------------"<<endl;
		}
		
		//To issue a book with Certain ID from library
		void issue_ll(int id){
	        if(head==NULL){
	        	cout<<"List is Empty"<<endl;
	        	return;
			}
			//if list is not empty traverse the list to find the required bookid
			node* temp=head;
			while(temp != NULL){
				//if bookid is found check its avaialability status
				if(temp->data->bookid == id){
		            //if book is available , give a message to user that book is issued ,update status to false(not availabl)
					if(temp->data->isavailable == true){
					 	cout<<"Issuing book with id : "<<id<<endl;
				   	    temp->data->isavailable=false;
				     	return; //return ; not proceed furthur
				   }
				   //if the book is found and its available status is not true it must be issued
				   //print a message that book is already issued
				   else{
				  	cout<<"The book with id "<<id<<" already issued"<<endl;
				  	return;
				   }
				}
				//update the temp to reach the end
				temp=temp->next;
			}
			//if temp becomes NULL and ID was not found ; then this Book id does not exist in List
			if(temp == NULL){
				cout<<"Book with id "<<id<<" not found"<<endl;
			}
		}
	    //returning a book	
		void retur(int id){
			if(head==NULL){
				cout<<"List is empty"<<endl;
				return;
			}
			//traverse the list
			node* temp=head;
			cout<<"Returning book with "<<id<<endl;
			while(temp != NULL){
			//if the bookId is found
	         if(temp->data->bookid == id){
	         	//The current status is not available so update the status and print message that book with id is returned
	         	if(temp->data->isavailable == false){
	         		temp->data->isavailable=true;
	         		cout<<"Book with id "<<id<<" returned"<<endl;
	         		temp->data->display();
	         		return;
				 }
			 }
			 //update temp to go to furthur in list
			 temp=temp->next;
            }
            //if tempbecomes NULL and ID was not found
            //Then this bookID does not exist 
            if(temp == NULL){
            	cout<<"Book with non-existing ID "<<id<<endl;
            	return;
			}
		}
		
		void display_ll(){
			if(head == NULL){
				cout<<"List is empty"<<endl;
				return;
			}
			node* temp=head;
			while (temp != NULL){
				temp->data->display(); //displays each Book details
				temp=temp->next;      //update temp
			}
		}
		//to delete a Book record by ID
		node* remove(int b){
			if(head == NULL){
				cout<<"List is empty"<<endl;
				return NULL;
			}
			//2 cases possible when deleting
			node* temp=head;
		    //case 1: there was only one node and book was found at thatlocation(head)
			if( temp->data->bookid == b){
				//make the head=tail point to NULL and delete Temp
				head=NULL;
				tail=NULL;
				delete temp;
				return NULL;
			}
			
			//case 2: book is found in rest of list 
			node* prev=head; //to keep track of one less location then the one which needs to be deleted
			node* curr=head->next;
			
			//if Curr is not NULL and the required book id is not found ; update the pointers
			while( curr!=NULL && curr->data->bookid != b){
				prev=curr;
				curr=curr->next;
			}
			// if the whhile loops becomes then maybe the CUrr was NULL or book with ID was found
			//if Curr was NULL then the book must not be in list
			if ( curr == NULL){
				cout<<"Book with id "<<b<<" not found"<<endl;
				return NULL;
			}
			//else we had found found the book with required ID
			//so update the pointers
			//curr will be deleted so make prev connected to curr->next
			prev->next=curr->next;
			//if we are deleting tail so the prev will become the new tail
			if (curr == tail){
				tail=prev;
			}
			delete curr; //delete curr(book with ID)
		}
		
//		void search(int a){
//			if(head==NULL){
//				cout<<"Empty"<<endl;
//				return;
//			}
//			node* temp=head;
//			while(temp!=NULL){
//				if(temp->data->bookid == a){
//					cout<<"Book found"<<endl;
//					temp->data->display();
//					return;
//				}
//				temp=temp->next;
//			}
//		}
};

//Hash table has O(1) time complexity for search and insert(if each key is hashed to a unique index)

class hashc{
	public:
		//we used separate chainh techniwue to avoid collision
		//the hashtable has linklist at each index initially pointing to NULL
		linklist* hashtable[13];
		int tablesize=13;
		
		//constructing initializing the hashtable indices to NULL
		hashc(){
			for(int i=0;i<tablesize;i++){
				hashtable[i]=NULL;
			}
		}
		//hash function to hash the key to a specific index
		int hash_f(int key){
			return key%tablesize;
		}
		
		//we passed a book object to insert function in Hashtable
		void insert_hash(book* b){
			//the book->id is passed as key to hashfunction and the return value is stored as index
			int index=hash_f(b->bookid);
			
			//if the hashtable's that index is NULL
			//we will create a new linklist at that index  
			if(hashtable[index] == NULL){
				hashtable[index] = new linklist(); 
			}
			//if the linklist already exists at that index will just insert the book in that list(insert at head)
			hashtable[index]->insert(b);
		}
		//to delete get a index from hash function and delete the book at that index
		void delet(int a){
			int index=hash_f(a);
			hashtable[index]->remove(a);
			}
		//to issue the book pass the ID as key and get index then call issue fuction at that index	
		void issue(int a){
			int index=hash_f(a);
		    hashtable[index]->issue_ll(a);
		}	
		//to return a book passs the key as key and this will give you an index where the book is likely to be found out
		//call return unction at that index and update the status
		void rett(int a){
			int index = hash_f(a);
			hashtable[index]->retur(a);
		}
		//display function to help you visualize the entries in hashtable
		void display_h(){
			for(int i=0; i<tablesize ; i++){
				if(hashtable[i] != NULL){
					cout<<"hashtable["<<i<<"] =";
					hashtable[i]->display_ll();
				}
				else{
					cout<<"hashtable["<<i<<"] = empty"<<endl;
				}
			}
		}
		//search function to find a certain book 
		void search(int val){
			int i=hash_f(val);
			hashtable[i]->search_LL(val);
		}
};

int main(int argc, char** argv) {
    hashc* h1 = new hashc(); //create object of hash class
    
    int choice; //to get choice rom user
    while (choice != 7){
    	cout<<"Enter your chioce:\n 1 insert \n 2 search \n 3 delete \n 4 issue \n 5 return \n 6 display \n 7 exit"<<endl;
    	cin>>choice;
    	switch(choice){ //based on choice do the required action
    		case 1:{
				
    			   cout<<"Enter id "<<endl;
    			   int id;
    			   std::string n;
    			   cin>>id;
    			   cin.ignore(); //clears newline
    			   cout<<"Enter Title of Book: "<<endl;
				   getline(cin,n); //for long string with spaces
    			   h1->insert_hash(new book(id , n));
    			   break; }
    		case 2:{
			       
			      cout<<"Enter book id yyou want to search"<<endl;
				  int a;
				  cin>>a;
				  h1->search(a);	  
				  break;
			}
			case 3:{
			      cout<<"Enter the book id uyou want to delete "<<endl;
				  int d; cin>>d;
				  h1->delet(d);
				  break;}	   
			case 4:{
			      cout<<"Enter book id you want to issue"<<endl;
				  int i; cin>>i;
				  h1->issue(i);
				  break;
			}
			case 5:
				{
				  cout<<"Enter book id you want to return"<<endl;
				  int b; cin>>b;
				  h1->rett(b);
				  break;
			}
			case 6:
				{
			      h1->display_h();
			      break;}
			case 7:
			       cout<<"Exiting..."<<endl;
				   break;	  	  
		}
	}
	return 0;
}

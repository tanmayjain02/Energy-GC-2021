/*#include<iostream>
#include<algorithm>
#include<string>
#include<iomanip>
#include<queue>*/
#include<bits/stdc++.h>
using namespace std;

//====================================== our own hashing functions ==================================================
string my_hash( string A){
    string hash_A = "";
    char c;
    for(int i=0; i<A.length(); i++){
        c = (char)( ( (int)A[i] + 15 )%256 );
        //take ascii value of a char and add a random int between 0 and 100 
        //then take its char value 
        hash_A += c;
    }//if A is null(0 length) then null is returned
    return hash_A;
}
int my_hash(int A){
    int num =0;
    while(A != 0){
        int d = A%10;
        A = A/10;
        int d1 = (d*d)%10;
        num = num*10 + d1; 
    }
    return num;//if in itial A is 0 then 0 is returned
}


struct transaction_entry;


//===================================== utility structures for block-chain blocks =====================================
struct UserData{
    string username_hash;
    string password_hash;
    int ph_num_hash;
    int designation;
    double balance;
    queue<transaction_entry> user_ledger;//just to hold the various transaction entries

    UserData(){}
    UserData(string u, string p, int pn, int d, double b){
        username_hash = my_hash(u);
        password_hash = my_hash(p);
        ph_num_hash = my_hash(pn);
        designation = d;
        balance = b;
    };
    void display(){
        cout<<"Username hash : "<<username_hash<<endl;
        cout<<"Password hash : "<<password_hash<<endl;
        cout<<"phone number hash : "<< ph_num_hash<<endl;
        cout<<"Designation : "<< designation <<endl;
        cout<<"Current balance : "<<balance<<endl;
    }
    
};

//==============================================  TRANSTACTION  LEDGER  ======================================================
struct transaction_entry{
    string sender_name;
    struct UserData sender;
    string reciever_name;
    double amount;
    transaction_entry(string sname, struct UserData sndr, string reciever, double amt){
        sender_name = sname;
        sender = sndr;
        reciever_name = reciever;
        amount = amt;
    };
};

void display_ledger(queue<transaction_entry> q){
    if(q.empty()){
        cout<<"transcation_ledger is empty ie no transactions yet !!"<<endl;
        return;
    }
    cout<<"Transcation info : \n-------------------------------------------"<<endl;
    while(!q.empty()){
        transaction_entry t = q.front();
        cout<<"sender_name : "<< t.sender_name<<endl;
        cout<<"reciever name : "<< t.reciever_name <<endl;
        cout<<"Sender info stored in data-base : "<<endl;
        t.sender.display();
        cout<<"Amount transcated : "<< t.amount <<endl;
        cout<<"----------------------------------------------"<<endl;
        q.pop();
    }   
}


void update_user_ledger(UserData &u, queue<transaction_entry> q){
        u.user_ledger = q;//copy of original ledger
    }


//=========================================== block chain as DOUBLY-linked list datastructure================================
class Node{
public:    
    Node* parent;
    Node* child;
    struct UserData data;

    void initialise(Node* p, Node* c, struct UserData u){
        this->parent = p;
        this->child = c;
        this->data = u;
    }
};
/* Given a reference (pointer to pointer) to the head of a list and an int, inserts a new node on the front of the list. */
void push_at_front(Node** head_ref, struct UserData new_data)
{
    Node* new_node = new Node();/* 1. allocate node in memory*/
    new_node->data = new_data;    /* 2. put in the data */
    new_node->child = (*head_ref); /* 3. Make child of new node as head  and parent of it is NULL*/
    new_node->parent = NULL;
    (*head_ref)-> parent = new_node ;/* 3. Make parent of old node as the new node*/
    (*head_ref) = new_node; /* 4. move the head to point to the new node */
}
/* Given a node prev_node, insert a new node after the given prev_node */
void insertAfter(Node* prev_node, struct UserData new_data)
{
    if (prev_node == NULL)/*1. check if the given prev_node is NULL */
    {
        cout<<"The given previous node cannot be NULL";
        return;
    }
    Node* new_node = new Node();/* 2. allocate new node */
    new_node->data = new_data;  /* 3. put in the data */
    new_node->child = prev_node->child;/* 4. Make child of new node as next of prev_node */
    (prev_node->child)->parent = new_node;/* 5. Make parent of the child of prev_node as the new node */
    prev_node->child = new_node;/* 5. move the child of prev_node as new_node */
    new_node->parent = prev_node;/* 6. move the child of new node as prev_node */
}
/* Given a reference (pointer to pointer) to the head of a list and an int, appends a new node at the end */
void append(Node** head_ref, struct UserData new_data)
{
    Node* new_node = new Node();/* 1. allocate node */
    Node *last = *head_ref; /* used in step 5*/
    new_node->data = new_data;/* 2. put in the data */
    new_node->parent = NULL;
    new_node->child = NULL;/* 3. This new node is going to be the last node, so make next of it as NULL*/
    if (*head_ref == NULL)/* 4. If the Linked List is empty, then make the new node as head */
    {
        *head_ref = new_node;
        return;
    }
    while (last->child != NULL)/* 5. Else traverse till the last node */
    {
        last = last->child;
    }
    last->child = new_node;/* 6. Change the next of last node */
    new_node->parent = last;
    return;
}
// This function prints contents of linked list starting from head
void printChain(Node *node)
{
    while (node != NULL)
    {
        (node->data).display();
        node = node->child;
    }
}


bool UserValidation(Node** head_ref, string u, string p ){
    Node *last = *head_ref; 
    if (*head_ref == NULL)/* 4. If the Linked List is empty, then no validation*/
    {
        cout<<"Block-Chain has no data"<<endl;
        return false;
    }
    while (last != NULL)/* 5. Else traverse all the nodes */
    {
        struct UserData d1 = last->data;
        if( d1.username_hash==my_hash(u) && d1.password_hash==my_hash(p) )//check the following hash with the hash stored in our database
            return true; 
        last = last->child;
    }
    return false;//default if not found
}

Node* search_node(Node** head_ref, string u, string p ){
    Node *last = *head_ref; 
    if (*head_ref == NULL)/* 4. If the Linked List is empty, then no validation*/
    {
        cout<<"Block-Chain has no data"<<endl;
        return NULL;
    }
    while (last != NULL)/* 5. Else traverse all the nodes */
    {
        struct UserData d1 = last->data;
        if( d1.username_hash==my_hash(u) && d1.password_hash==my_hash(p) )//check the following hash with the hash stored in our database
            return last; 
        last = last->child;
    }
    return NULL;//default if not found
}


Node* search_node_for_payment(Node** head_ref, string u){
    Node *last = *head_ref; 
    if (*head_ref == NULL)/* 4. If the Linked List is empty, then no validation*/
    {
        cout<<"Block-Chain has no data"<<endl;
        return NULL;
    }
    while (last != NULL)/* 5. Else traverse all the nodes */
    {
        struct UserData d1 = last->data;
        if( d1.username_hash==my_hash(u) )//check the following hash with the hash stored in our database
            return last; 
        last = last->child;
    }
    return NULL;//default if not found
}

void transfer_money(Node** head_ref, string reciever_name, double amt){
    Node *recepient;
    recepient = search_node_for_payment(head_ref, reciever_name); 
    if (recepient == NULL)
    {
        cout<<"NO SUCH recepient !!"<<endl;
        return;
    }
    (recepient->data).balance += amt;
}

void update_recepient_ledger(Node** head_ref, string reciever_name, queue<transaction_entry> q)
{
    Node *recepient;
    recepient = search_node_for_payment(head_ref, reciever_name); 
    if (recepient == NULL)
    {
        cout<<"NO SUCH recepient !!"<<endl;
        return;
    }
    update_user_ledger((recepient->data),q);   
}

//=================================================== utility functions =====================================================

bool search_username(queue<string> q ,string u){
    while(!q.empty()){
        string s1 = q.front();
        if(s1 == u)
            return true;
        q.pop();
    }
    return false;
}

void display_usernames(queue<string> q){
    while(!q.empty()){
        string s1 = q.front();
        cout<<s1<<", ";
        q.pop();
    }
    cout<<endl;
}




//================================================= implementation ===========================================================
int main(){
    srand(time(0));
    queue<string> username_queue;//just to hold the various user names
    Node* root = NULL;//root of block_chain
    queue<transaction_entry> transaction_ledger;//just to hold the various transaction entries

    while(true){
        cout << "WELCOME"<<endl;
        cout << " press 1 for LOGIN and 2 for SignUp, press 3 to QUIT "<< endl;  
        int choice;
        cin >> choice;
        if ( choice == 1){//LOGIN
            string u,p;
            cout << "Enter username : "<<endl;
            cin >> u;
            cout << "Ener password : "<< endl;
            cin >> p;

            if( UserValidation(&root, u, p ) )
                cout<<"VALID CREDENTIALS!! :) "<<endl;
            else{
                cout << "INVALID CREDENTIALS !! :( "<<endl;
                continue;
            }
            

            int designation;
            //cout<< "Enter The Designation"<<endl;
            //cout<<"1 == Customer \n2==Dealer \n3==OEM \n4 == Supplier"<<endl;
            //cin>>designation;

           
            Node* current_node;
            current_node = search_node(&root, u, p);
            cout<<"YOUR info as stored in database is :"<<endl;
            (current_node->data).display();
            designation = (current_node->data).designation;

            while(true){
                int t ;
                cout << "Press 1 to makes transaction \nPress 2 to view transaction history and balance"<<endl; 
                cout<< "Press 3 to view list of Current users on the platform \nPress 4 to exit this transaction loop "<<endl;
                cin >>t;
                if(t==4) break;
                switch(t){
                    case 1 :
                    {
                        cout << "YOUR current balance is = "<< (current_node->data).balance <<endl;
                        string reciever;
                        cout << "ENTER the username of reciever"<<endl;
                        cin >> reciever;
                        while( !search_username(username_queue, reciever) ) {
                            cout << "Username doesnot exist Try again, \nEnter Another username to send money !" <<endl;
                            cin >> reciever;  
                        }
                        cout <<"ENTER the amount"<<endl;
                        double amount;
                        cin >> amount;
                        if(amount > 0){
                            if ( amount  <= (current_node->data).balance ) { 
                                (current_node->data).balance -= amount ;//update sender's balance
                                transfer_money(&root, reciever, amount);//update recepient's balance
                                cout << " !!!!TRANSACTION SUCCESFULL !!!!"<<endl;
                                cout<<"Your Current balance now is : "<< (current_node->data).balance << endl;
                                transaction_entry t(u, current_node->data, reciever, amount);
                                transaction_ledger.push(t);
                                update_user_ledger((current_node->data), transaction_ledger);
                                update_recepient_ledger(&root, reciever, transaction_ledger);
                            }
                            else {
                                cout <<"Not enough BALANCE !! :( "<< endl;
                            }
                        }
                        else cout<<"HEY enter positive amount !! "<<endl;
                    }
                        break;

                    case 2 :
                        display_ledger( (current_node->data).user_ledger);
                        break;
                    case 3 :
                        cout<<"List of all the current users"<<endl;
                        display_usernames(username_queue);
                        break;    
                    default:
                        cout<<"Wrong Input !! "<<endl;
                        break;                
                }//end of switch
             }//end of while
            
        }//end of LOGIN
        else if(choice == 2){//REGISTRATION
            string u,p;
            int balance, designation, phone;
            cout << "Write your username"<<endl;
            cin >> u;
            while( search_username(username_queue, u) ) {
                cout << "Username already in use try again, Try again, \nEnter Another username" <<endl;
                cin >> u;    
            }
            username_queue.push(u);//store the username separately
            cout<<"Username Accepted !!\nType your Password : "<<endl;
            cin >> p ;
            cout << "What's your designation, Press: " <<endl;
            cout<<"1 for Customer \n2 for Dealer \n3 for OEM \n4 for Supplier"<<endl;
            cin >> designation;
            cout<<"Type your Phone number (5digits) : "<<endl;
            cin >> phone ;

            switch(designation ){
                case 1 : balance = 1000; break;
                case 2 : balance = 10000; break;
                case 3 : balance = 50000; break;
                case 4 : balance = 100000; break;
                default: balance = 0;
            }

            // now assign hashes all these details, and store in our database
            struct UserData new_user(u,p,phone,designation,balance);//UserData(string u, string p, int pn, int d, double b)
            update_user_ledger(new_user, transaction_ledger);
            //Node* new_block = new Node();
            //new_block.initialise(NULL,NULL,new_user);
            append(&root, new_user);
            cout<<"YOUR info as stored in database is :"<<endl;
            new_user.display();
            cout<<"List of all the current users"<<endl;
            display_usernames(username_queue);
            cout<<"------------------------------------------"<<endl;
            //printChain(root);
        }//end of REGISTRATION

        else if(choice == 3) break;
        else {
        cout << "Invalid input"<<endl;
        continue;
        }
    
    }//end of while loop
    cout << "SUCCESFULLY TERMINATED !!"<<endl;

return 0;   
}


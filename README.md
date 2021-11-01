# Energy-GC-2021
Code Explained With 

Hash Function ::::
In This App we Have Used a simple Hashing Function ( creates a irreversible secret key for the the Username , PassWord , Phone Number ,   )

UserData :: 
It is a structure that would create Username Hash , Password Hash , Phone Number Hash , Designation of The User and The Balance They have , 
Contains A Function To Display all The data and an Initialiser.

We have Created a node (double - linked list )

We Need To Check If the User is Validated (UserValidation Function )
	It Would Check All the Hashes in The DataBase(Linked List ) and Check Whether The Hash of Input Username and Password matches with Stored In Database . 
If Nothing Matches Then Not Login .

Created Some Functions to Search Node for Payment as In The Payment side  Only Username Would be There So It should match Hashed Value and Then We can Access That User data

Created A Function To Transfer Money 
	It would Find the Node with particular data and Then Add the amount in the Wallet of that User


Created a structure  transcation_entry which would take the Sender Name , Receiver Name, Amount  and UserData. 

Created a Function To display Ledger Which Contains a List of All Transactions.

Created The InterFace For The CLI.


Further Planning 
===> Every User Would Have His Own Ledger Which Would Contain all the Transactions Visible To Him and It is always Re confirmed By Main Ledger Which Is immutable and Hence Only Limited Transactions Would be Visible Only Of His Use
This Is Inspired By The Hawk Method Of Securing The Data By 3rd Party Trusted Source (Main Ledger needs to be Kept Safe).


// 01001001 01010100 01010111
#include <iostream>
#include <string>
#include "LinkedList.h"
#include "IQueue.h"

using namespace std;

class Account
{
    // MEMBER VARIABLES
    private:
    string name="No names are assigned yet!"; // stores account owner's name
    Queue<string> likedList; // stores the songs' names liked by account owner in a queue comindexed with linked list
    public:
    Account(){} // default constructor 
    Account(string name) { this->name = name;} // overloaded constructor 
    // SET FUNCTIONS
    void setName(const string name){this->name = name;}
    void setLikedList(const Queue<string> likedList) {this->likedList = likedList;} // sets the whole likedList to the given parameter
    // GET FUNCTIONS
    string getname(){return name;}
    Queue<string>& getLikedList(){return likedList;}
    bool operator == (const Account &); // return true if names are same
    friend ostream& operator << (ostream &, const Account &);
    

};
    bool Account::operator == (const Account &o)
    {
        if(name == o.name)
        return true;
        else 
        return false;
    }
    ostream& operator << (ostream &myOut, const Account &o)
    {
        myOut << o.name ;
        return myOut;
    }
   

class Command
{
    private:
    string operatorInput; // holds the character which represents operation to be performed
    string personName="No account created yet!";// holds the account owner's name
    string songName="No songs are assigned yet!"; // holds the song name to be liked or unliked
    public:
    Command(){} // default constructor;
    // OVERLOADED CONSTRUCTORS
    Command(string operatorInput){this->operatorInput= operatorInput;}
    Command(string operatorInput, string personName)
    {
        this->operatorInput = operatorInput;
        this->personName = personName;
    }
    Command(string operatorInput, string personName, string songName)
    {
        this->operatorInput=operatorInput;
         this->personName=personName;
         this->songName=songName;
    }
    // SET FUNCTIONS
    void setOperatorInput(const string operatorInput){this->operatorInput = operatorInput;}
    void setPersonName(const string personName){this->personName = personName;}
    void setSongName(const string songName){this->songName = songName;}
    // GET FUNCTIONS
    string getOperatorInput(){return operatorInput;}
    string getPersonName(){return personName;}
    string getSongName(){return songName;}

 

};

void formatString(string &str) // make every character lowercase except first character, make first character uppercase
{
    for(int i=0; i<str.length();i++)
    {
        if(i==0)
        {
            str[i] = toupper(str[i]);
        }
        else
        {
            str[i] = tolower(str[i]);
        }
    }
}

void takeInput(Command &command)
{
    string line,*temp,temp2,temp3,fakeString;
    LLNode<Account> *tempNode;
    int i =0;
    Queue<char> charQueue;
    do // takeInput while an Input is invalid
    {
    temp = new string; // every single time loop turns reset the temp to avoid concatenating operatorInput strings
    getline(cin,line);
    while( line[i] !='\0')
    {
        charQueue.add(line[i]);

        i++;
    }
    
    
    while(charQueue.front() != ' ')
    {
        fakeString = charQueue.remove();
        *temp = *temp +fakeString;
        if(charQueue.isEmpty())
        {
            break;
        }
    }
    command.setOperatorInput(*temp);
    delete temp;
    i=0;
    
       if(command.getOperatorInput() =="c" || command.getOperatorInput() =="s" || command.getOperatorInput() =="e" || command.getOperatorInput() =="l" || command.getOperatorInput() =="n"||command.getOperatorInput() =="m" ) // if lowercase, make it uppercase
    {
        char temp = command.getOperatorInput()[0] - 32;
        string tempstring;
        tempstring = temp;
        command.setOperatorInput(tempstring) ;
    }
    if(!(command.getOperatorInput() =="C" || command.getOperatorInput() =="S" || command.getOperatorInput() =="E" || command.getOperatorInput() =="L" || command.getOperatorInput() =="S"|| command.getOperatorInput() =="M" || command.getOperatorInput() =="N"))
    {
        cerr<< "Invalid input! Please enter try again!"<<endl;
        charQueue.clearQueue();
    }
    
    if((command.getOperatorInput() =="C" || command.getOperatorInput() =="S" || command.getOperatorInput() =="E" || command.getOperatorInput() =="L" || command.getOperatorInput() =="S" )&& (!charQueue.isEmpty())) //  we need personName if operatorInput is not  N or M
    { while((charQueue.front() != ' ' || i<1))
    {
        fakeString = charQueue.remove();
        if(fakeString != " ")
        {
         temp2 = temp2 +fakeString;
        }
        i++;
        if(charQueue.isEmpty()) // if line is finished exit the loop
        break;
    }
    i=0;
    formatString(temp2);
    command.setPersonName(temp2);
    ;
    }
    if((command.getOperatorInput()== "S" ||command.getOperatorInput()=="E")&& (!charQueue.isEmpty())) // we need songName if operatorInput is S or E
      {
          while(!(charQueue.isEmpty()) )
    {
        fakeString = charQueue.remove();
        if(fakeString != " " || i>=1)
        {
         temp3 = temp3 +fakeString;
        }
    i++;
    }
    formatString(temp3);
    command.setSongName(temp3);
    }
    

    } while (!(command.getOperatorInput() =="C" || command.getOperatorInput() =="S" || command.getOperatorInput() =="E" || command.getOperatorInput() =="L" || command.getOperatorInput() =="S"|| command.getOperatorInput() =="M" || command.getOperatorInput() =="N"));
   
}




int main()
{
    // VARIABLES SECTION
    LinkedList<Account> accounts; // holds all the accounts
    Account *accountPtr,tempAcc; // temp account pointers
    LLNode<Account> *tempNode; // account node pointer
    LLNode<string> *tempStringNode; // string node pointer
    Command command; // holds inputs from command line
    bool error=false;
    bool noAccError=false;
    bool noSongError=true;
    // WELCOME MESSAGE & END-USER GUID SECTION
    cout<<"\t\t\tWELCOME TO THE SPOTIFY-LIKE APPLICATION!"<<endl<<endl;

    cout << "You can write the commands listed below to use this application."<<endl<<endl;
    cout << "Commands:"<<endl<<endl;
    cout << "- C<Name> => Create an account with your name"<<endl
         << "- S<Name><Song> => Like a song with the song's name"<<endl
         << "- E<Name><Song> => Unlike a song"<< endl
         << "- L<Name> => List the songs person <Name> likes"<<endl
         << "- N => List the names of all the registered people"<<endl
         << "- M => List all the songs that are liked by anyone"<<endl<<endl;
    while(1) // an infinite loop to take inputs & perform an operation depend on operatorInput infinitely
    {
        takeInput(command); // taking unput string from the command line
        
        if(command.getOperatorInput() == "C")
        {
            error = false;
            accountPtr = new Account;
            accountPtr->setName(command.getPersonName());
        tempNode = accounts.search(*accountPtr);
        if(tempNode != NULL) // if NULL it does not already exist
        {
           cerr << tempNode->data.getname() << " already exits!"<<endl;
           error = true;
           
        }
        
        if(!error)
        accounts.insertLast(*accountPtr); // insert account to the accounts linked list
        delete accountPtr;
           
         
        }
        if(command.getOperatorInput() == "S")
        {
            error = false;
            accountPtr = new Account;
            accountPtr->setName(command.getPersonName());
            tempNode = accounts.search(*accountPtr); // search for the account to insert the songName
            if(tempNode== NULL)
            {
                cerr << command.getPersonName() << " does not exist!"<<endl;
                error = true;
            }
            if(!error)
            tempNode->data.getLikedList().add(command.getSongName()); // insert the songName to the found account's likedList queue
            delete accountPtr;
           
        }
        if(command.getOperatorInput() == "E")
        {
            Queue<string> temp;   
            accountPtr = new Account;
            accountPtr->setName(command.getPersonName());
            tempNode = accounts.search(*accountPtr); // search for the account
            if(tempNode== NULL)
            {
                cerr << command.getPersonName() << " does not exist!"<<endl;
                error = true;
            }
            if(!error)
            {
                while(!(tempNode->data.getLikedList().isEmpty())) 
            {
                if(tempNode->data.getLikedList().front() != command.getSongName()) // if it is not the song to be deleted
                {
                    temp.add(tempNode->data.getLikedList().remove());  // add songes that are not to be removed to the another queue
                }
                else
                {
                    tempNode->data.getLikedList().remove(); // remove the songName   
                }
                     
            }
            tempNode->data.setLikedList(temp);
            }
            delete accountPtr;
            
         
        }
          
        if(command.getOperatorInput() == "L")
        {
            accountPtr = new Account;
            Queue<string> temp;
            accountPtr->setName(command.getPersonName());
            tempNode = accounts.search(*accountPtr); // search for the account
            if(tempNode== NULL)
            {
                cerr << command.getPersonName() << " does not exist!"<<endl;
                error = true;
            }
            if(!error)
            { 
                while(!tempNode->data.getLikedList().isEmpty()) // copy the values to the temp
            {
                temp.add(tempNode->data.getLikedList().remove());            
            }
            tempNode->data.setLikedList(temp);
            if(!temp.isEmpty())
            {
                while(!temp.isEmpty())
            {
                cout<< temp.remove()<<endl;
            }
            }
            else
            cerr<<"No songs have been assigned to person "<< command.getPersonName()<<endl;
            }
            delete accountPtr;
           
        }
        if(command.getOperatorInput()=="N")
        {
            if(!accounts.isEmpty())
            cout << accounts<<endl; // overloaded to output names
            else
            cerr<< "No accounts are created yet!"<<endl;
        }
        if(command.getOperatorInput()=="M")
        {
             if(accounts.isEmpty()) // handles crash if there is not account created yet
            {
                cerr<< "No account created yet!"<<endl;
                noAccError = true;
            }
            if(!noAccError)
            {
                Queue<string> temp;
            accountPtr = new Account;  
            *accountPtr = accounts.front();
            tempNode = accounts.search(*accountPtr); // set tempNode to first node
           
            
           for(int i=0; i< accounts.length();i++)
           {
               
            while(!tempNode->data.getLikedList().isEmpty()) // copy the values to the temp
            {
                temp.add(tempNode->data.getLikedList().remove());            
            }
            if(!temp.isEmpty())
            {
                noSongError = false;
            }
            tempNode->data.setLikedList(temp);
            if(noSongError)
            {
                cerr<<"No songs are liked by anyone!"<<endl;
                noSongError = true;
            }
            while(!temp.isEmpty())
            {
                cout<< temp.remove()<<endl;
            }
               tempNode = tempNode->next; // move to the next node
               
              
           }
           delete accountPtr;
           }
        }
        }
        
       
    

    
    return 0;
}
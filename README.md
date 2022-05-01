# Spotify-like-Application

Spotify-like program using queues utilizing linked list implementation. 
All data is stored in linked lists containing nodes where each node stores the name of a person and the queue of their playlist. 
Program works on the command line where the commands are given in one line as shown below:
C <Name> : Creates a person with the name given in the line
eg: C Ahmet
S <Name> <Song> : Sets the <Name> likes the <Song>
eg: S Ahmet Show must go on
E <Name> <Song> : Erases the assignment (<Name> doesn’t like the song anymore).
L <Name> : Lists the songs person <Name> likes.
N : List the names of all of the registered people
M : List all the songs that are liked by anyone

# Movie Streaming Service

This project was completed as part of an assignment in the Computer Science Department at the University of Crete. The assignment was for the course HY240 - Data Structures.

In this assignment, we were asked to develop a simplified movie streaming service. The service organizes movies into various thematic categories. 
Users can register, watch movies, add them to their viewing history, and perform filtered searches within the categories. 
To efficiently manage the data, data structures such as trees and a hash map were utilized.

This program works by initializin the database using a file which is given by the user and then read by the program. The program is based on "events". 
These events were set by the proffesor and the proffesor's TAs and we were asked to think the logic and use them in our programs.

## The events include :

R <userID >                                  - Register user
U < userID >                                 - Unregister user
A <mid > <category> <year>                   - Add movie to database
D                                            - Distribute movies based on their categories
Ι <movieID> <category>                       - Search movie with ID "movieID" in the category "category"
W <userID > <category><movieID> <score>      - Watch movie
F <uid > <score>                             - Filter movies
Q <userID>                                   - Average movie score the user has rated



## Events merged within the main function
M                                            - Print movies
P                                            - Print users



# Movie Streaming Service

This project was completed as part of an assignment in the Computer Science Department at the University of Crete. The assignment was for the course HY240 - Data Structures.

In this assignment, we were asked to develop a simplified movie streaming service. The service organizes movies into various thematic categories. 
Users can register, watch movies, add them to their viewing history, and perform filtered searches within the categories. 
To efficiently manage the data, data structures such as trees and a hash map were utilized.

This program functions by initializing the database using a file provided by the user, which is subsequently read by the program. The program is structured around "events." These events were defined by the professor and the teaching assistants, and we were tasked with devising the logic and incorporating them into our programs.
 <br />
## The events include :

R <userID >                                  - Register user <br />
U < userID >                                 - Unregister user <br />
A <mid > <category> <year>                   - Add movie to database <br />
D                                            - Distribute movies based on their categories <br />
Ι <movieID> <category>                       - Search movie with ID "movieID" in the category "category" <br />
W <userID > <category><movieID> <score>      - Watch movie <br />
F <uid > <score>                             - Filter movies <br />
Q <userID>                                   - Average movie score the user has rated <br />
 <br />
 <br />
 <br />
## Events merged within the main function
M                                            - Print movies <br />
P                                            - Print users <br />
 <br />
 <br />
In conclusion, this assignment was designed to enhance our understanding of data structures, providing both an engaging and educational experience.

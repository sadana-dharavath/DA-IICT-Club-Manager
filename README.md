P6 - Capstone Project : IT205
You need to build a manager for all the DA-IICT clubs. The manager ensures that a club member can be looked up in minimum time. A member can either be a faculty or a student. One should be able to search by name, ID, specific club name, or club category (i.e., arts, science & technology, sports, culture). Note that the user of this manager may not be a DA-IICT-ian and, therefore, may not know the clubs’ names.


Code Description : 

This C++ program is a club management system for DA-IICT (Dhirubhai Ambani Institute of Information and Communication Technology). Here's a breakdown of its key components and functionalities:

Data Structures:
The program uses several data structures, including unordered_map and vector, to store information about clubs and members.
Clubs are represented by the Club struct, which includes the club's name and category.
Members are represented by the Member struct, which includes the member's name, ID, and a list of clubs they belong to.

Club Categories:
The ClubCategory enum class defines four categories: Arts, Science, Sports, and Culture.

ClubManager Class:
The ClubManager class manages the clubs and members data.
It includes private member variables to store clubs and members data using unordered_maps.
The loadData method reads data from a CSV file and populates the clubsByName, clubsByCategory, membersById, and membersByName maps.
The searchMember method searches for a member by name or ID.
The searchClub method searches for clubs by name and prints the members of those clubs.
The searchClubByCategory method searches for clubs by category and prints the clubs along with their members.

Main Function:
The main function is the entry point of the program.
It creates an instance of ClubManager and loads data from a CSV file.
It displays a menu for the user to choose from various search options (by name, ID, club name, club category, or exit).
Based on the user's choice, it calls the corresponding methods of ClubManager to perform the search and display the results.

Input Handling:
The program uses getline to read user input for search options and queries.

Error Handling:
The program handles errors such as invalid input gracefully, printing appropriate messages to the console.
Overall, this program provides a simple and interactive way to manage and search for clubs and members at DA-IICT based on various criteria.

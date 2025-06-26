#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

// Define club categories
enum class ClubCategory {
    Arts,
    Science,
    Sports,
    Culture
};

// Define a structure for a club
struct Club {
    string name;
    ClubCategory category;

    Club(const string& n, ClubCategory c) {
        this->name = n;
        this->category = c;
    }
};

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Define a structure for a member
struct Member {
    string name;
    int id;
    vector<Club*> clubs;

    Member(const string& n, int i) {
        this->name = n;
        this->id = i;
    }
};

// Define a manager class to manage clubs and members
class ClubManager {
private:
    unordered_map<string, Club*> clubsByName;
    unordered_map<string, vector<Club*>> clubsByCategory;
    unordered_map<int, Member*> membersById;
    unordered_map<string, Member*> membersByName;

public:
    // Load data from CSV file
    void loadData(const string& filename) {
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string name, idStr, clubsStr;

            getline(ss, name, ',');
            getline(ss, idStr, ',');
            getline(ss, clubsStr, ',');

            int id;
            try {
                id = stoi(idStr);
            } 
            catch (const invalid_argument& e) {
                cerr << "";
                continue;
            }

            Member* member = new Member(name, id);

            membersById[id] = member;
            membersByName[name] = member;

            stringstream clubsSS(clubsStr);
            string clubName;

            while (getline(clubsSS, clubName, ';')) {
                Club* club;

                if (clubsByName.find(clubName) == clubsByName.end()) {

                    if ((clubName == "PMMC") || (clubName == "Muse") || (clubName == "Music") || (clubName == "Dance")) {
                        club = new Club(clubName, ClubCategory::Arts); 
                        clubsByName[clubName] = club;
                        clubsByCategory["Arts"].push_back(club); 
                    }

                    if ((clubName == "Research") || (clubName == "Programming") || (clubName == "MSTC") || (clubName == "Business") || (clubName == "Press")) {
                        club = new Club(clubName, ClubCategory::Science); 
                        clubsByName[clubName] = club;
                        clubsByCategory["Science"].push_back(club); 
                    }

                    if ((clubName == "Cubing") || (clubName == "Chess")) {
                        club = new Club(clubName, ClubCategory::Sports); 
                        clubsByName[clubName] = club;
                        clubsByCategory["Sports"].push_back(club); 
                    }

                    if ((clubName == "Heritage") || (clubName == "Khelaiya") || (clubName == "DTG")) {
                        club = new Club(clubName, ClubCategory::Culture); 
                        clubsByName[clubName] = club;
                        clubsByCategory["Culture"].push_back(club); 
                    }
                } 
                else {
                    club = clubsByName[clubName];
                }

                member->clubs.push_back(club);
            }
        }
    }

    //Search for a member by name or ID
    Member* searchMember(const string& query) {
        string lowercaseQuery = toLower(query);

        for (auto& entry : membersByName) {
            string lowercaseName = toLower(entry.first);

            if (lowercaseName == lowercaseQuery) {
                return entry.second;
            }
        }
        try {
            int id = stoi(query);

            if (membersById.find(id) != membersById.end()) {
                return membersById[id];
            }
        } 
        catch (const invalid_argument& e) {
            cerr << "Invalid query: " << query << endl;
        }
        return nullptr;
    }

    // Search for clubs by name
    vector<Club*> searchClub(const string& query) {
        vector<Club*> result;
        string lowercaseQuery = toLower(query);

        for (auto& entry : clubsByName) {
            string lowercaseName = toLower(entry.first);

            if (lowercaseName == lowercaseQuery) {
                result.push_back(entry.second);
            }
        }

        // Print members of found clubs
        for (Club* club : result) {
            int i = 1;
            cout << endl <<"Members of the " << club->name << " club :" << endl;

            for (auto& entry : membersByName) {
                Member* member = entry.second;

                for (Club* memberClub : member->clubs) {
                    string lowercaseClubName = toLower(memberClub->name);

                    if (lowercaseClubName == lowercaseQuery) {
                        printf("%d) %-10s ID : %d\n", i, member->name.c_str(), member->id);
                        i++;
                        break; 
                    }
                }
            }
        }

        return result;
    }

    // Search for clubs by category
    vector<Club*> searchClubByCategory(const string& userInput) {
        string lowercaseCategory = toLower(userInput);
        ClubCategory category;

        if (lowercaseCategory == "arts") {
            category = ClubCategory::Arts;
        } 
        else if (lowercaseCategory == "science") {
            category = ClubCategory::Science;
        } 
        else if (lowercaseCategory == "sports") {
            category = ClubCategory::Sports;
        } 
        else if (lowercaseCategory == "culture") {
            category = ClubCategory::Culture;
        }
        else {
            cout << "Invalid category." << endl;
            return {};
        }

        vector<Club*> result;

        for (auto& entry : clubsByCategory) {

            if (category == ClubCategory::Arts && entry.first == "Arts") {
                result.insert(result.end(), entry.second.begin(), entry.second.end());
            } 
            else if (category == ClubCategory::Science && entry.first == "Science") {
                result.insert(result.end(), entry.second.begin(), entry.second.end());
            } 
            else if (category == ClubCategory::Sports && entry.first == "Sports") {
                result.insert(result.end(), entry.second.begin(), entry.second.end());
            } 
            else if (category == ClubCategory::Culture && entry.first == "Culture") {
                result.insert(result.end(), entry.second.begin(), entry.second.end());
            }
        }

        // Print clubs and members of found category
        cout << "\nClubs in the Category " << userInput << " :" << endl << endl;
        int i = 1;
        for (Club* club : result) {
            cout << " " << i << "] " << club->name << " : " << endl ;
            int j = 1;

            for (auto& entry : membersByName) {
                Member* member = entry.second;

                for (Club* memberClub : member->clubs) {

                    if (memberClub == club) {
                        printf("  %d) %-10s ID : %d\n", j, member->name.c_str(), member->id);
                        j++;
                        break; 
                    }
                }
            }
            cout << endl;
            i++;
        }
        cout << endl;

        return result;
    }
};

int main() {
    ClubManager manager;
    manager.loadData("data.csv");

    cout << "\n-----> Welcome to DA-IICT Club Community <-----\n";

    string userInput;
    do {
        cout << "\nSEARCH OPTIONS :\n"
             << " 1. Search by name\n"
             << " 2. Search by ID\n"
             << " 3. Search by club name\n"
             << " 4. Search by club category\n"
             << " 5. Exit\n"
             << "\nENTER YOUR CHOICE : ";
        getline(cin, userInput);

        switch (stoi(userInput)) {
            case 1: {

                cout << "\nEnter the Member Name : ";
                getline(cin, userInput);
                Member* member = manager.searchMember(userInput);

                if (member != nullptr) {
                    cout << "\nMember Name : " << member->name << "\nID : " << member->id << endl;
                    cout << "Clubs : ";

                    for (size_t i = 0; i < member->clubs.size(); ++i) {
                        cout << member->clubs[i]->name;
                        if (i != member->clubs.size() - 1) {
                            cout << ", ";
                        }
                    }
                    cout << endl;
                } 
                
                else {
                    cout << "Member not found." << endl;
                }
                break;
            }

            case 2: {

                cout << "\nEnter the ID : ";
                getline(cin, userInput);
                Member* member = manager.searchMember(userInput);

                if (member != nullptr) {
                    cout << "\nMember name : " << member->name << "\nID : " << member->id << endl;
                    cout << "Clubs : ";

                    for (size_t i = 0; i < member->clubs.size(); ++i) {
                        cout << member->clubs[i]->name;

                        if (i != member->clubs.size() - 1) {
                            cout << ", ";
                        }
                    }
                    cout << endl;
                } 
                
                else {
                    cout << "Member not found." << endl;
                }
                break;
            }

            case 3: {

                cout << "\nEnter the Club Name : ";
                getline(cin, userInput);
                vector<Club*> clubs = manager.searchClub(userInput);

                if (clubs.empty()) {
                    cout << "\nClub not found." << endl;
                    cout << endl;
                }
                break;
            }

            case 4: {

                cout << "\nEnter the Category (Arts, Science, Sports, Culture) : ";
                getline(cin, userInput);
                vector<Club*> clubs = manager.searchClubByCategory(userInput);

                if (clubs.empty()) {
                    cout << "No clubs found in category " << userInput << "." << endl;
                }
                break;
            }

            case 5: {
                cout << "\n\tTHANK YOU!\n\nExiting program... " << endl;
                return 0;
            }

            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }

    } while (true);

    return 0;
}
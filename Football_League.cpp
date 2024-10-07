#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

struct Team {
    string name;
    string town;
    string stadium;
};

struct Match {
    string homeTeam;
    string awayTeam;
    string localTown;
    string stadium;
    int leg;
    int weekend;
}

// Jabez
void readTeamsFromFile(const string& filename, vector<Team>& teams) {
    ifstream file(filename);
    string line;

    getline(file, line);
    while (getline(file, line)) {
        stringstream s(line);
        Team team;
        getline(s, team.name, ',');   // Assuming comma-delimited file
        getline(s, team.town, ',');
        getline(s, team.stadium, ',');
        teams.push_back(team);
    }
    file.close();
}
// Jemima
void generateFixtures(const vector<Team>& teams, vector<Match>& fixtures) {
    int weekend = 1;
    int matchesThisWeekend = 0;
    vector<Match> localTownMatchesLeg1;
    vector<Match> localTownMatchesLeg2;
    set<string> usedStadiums;

    for (int leg = 1; leg <= 2; ++leg) {
        for (size_t i = 0; i < teams.size(); ++i) {
            for (size_t j = i + 1; j < teams.size(); ++j) {
                if (teams[i].town == teams[j].town) {

                    if (leg == 1) {
                        localTownMatchesLeg1.push_back({teams[i].name, teams[j].name, teams[i].town, teams[i].stadium, leg, 0});
                    } else {
                        localTownMatchesLeg2.push_back({teams[i].name, teams[j].name, teams[i].town, teams[i].stadium, leg, 0});
                    }
                } else {
                    Match match;
                    string stadium = (leg == 1) ? teams[i].stadium : teams[j].stadium;
                    if (usedStadiums.find(stadium) != usedStadiums.end()) {
                        continue;
                    }

                    if (leg == 1) {
                        match = {teams[i].name, teams[j].name, teams[i].town, teams[i].stadium, leg, weekend};
                    } else {
                        match = {teams[j].name, teams[i].name, teams[j].town, teams[j].stadium, leg, weekend};
                    }

                    fixtures.push_back(match);
                    usedStadiums.insert(stadium);
                    matchesThisWeekend++;

                    if (matchesThisWeekend == 2) {
                        weekend++;
                        matchesThisWeekend = 0;
                        usedStadiums.clear();
                    }
                }
            }
        }

        if (leg == 1) {
            for (auto& match : localTownMatchesLeg1) {
                string stadium = match.stadium;
                if (usedStadiums.find(stadium) != usedStadiums.end()) {
                    continue;
                }

                match.weekend = weekend;
                fixtures.push_back(match);
                usedStadiums.insert(stadium);
                matchesThisWeekend++;

                if (matchesThisWeekend == 2) {
                    weekend++;
                    matchesThisWeekend = 0;
                    usedStadiums.clear();
                }
            }
        }
    }

    for (auto& match : localTownMatchesLeg2) {
        string stadium = match.stadium;
        if (usedStadiums.find(stadium) != usedStadiums.end()) {
            continue;
        }

        match.weekend = weekend;
        fixtures.push_back(match);
        usedStadiums.insert(stadium);
        matchesThisWeekend++;

        if (matchesThisWeekend == 2) {
            weekend++;
            matchesThisWeekend = 0;
            usedStadiums.clear();
        }
    }
}

































// Schola
int main() {
    vector<Team> teams;
    readTeamsFromFile("teams.csv", teams);

    vector<Match> fixtures;
    generateFixtures(teams, fixtures);
    saveFixturesToFile(fixtures, "fixtures.csv");

    cout << "Welcome to the MatchMatrix!\n";
    cout << "Fixtures have been generated and saved to fixtures.csv\n";

    while (true) {
        int selectedWeekend;
        cout << "Please enter the weekend number (1 to 33) to view the fixtures, or 0 to exit: ";
        cin >> selectedWeekend;

        if (selectedWeekend == 0) {
            cout << "Thank you for using Matchmatrix. Goodbye!\n";
            break;
        }

        if (selectedWeekend < 1 || selectedWeekend > 33) {
            cout << "Invalid weekend number. Please enter a number between 1 and 33.\n";
        } else {
            displayWeekendMatches(fixtures, selectedWeekend);
            char choice;
            cout << "Would you like to view fixtures for another weekend? (y/n): ";
            cin >> choice;
            if (choice != 'y' && choice != 'Y') {
                cout << "Thank you for using Matchmatrix. Goodbye!\n";
                break;
            }
        }
    }

    return 0;
}
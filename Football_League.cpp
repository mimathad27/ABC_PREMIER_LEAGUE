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
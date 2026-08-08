
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

class Player
{
public:
    string name;
    int runs = 0, balls = 0, fours = 0, sixes = 0;
    Player() {}
    Player(string n) : name(n) {}
    void display() const
    {
        cout << left << setw(18) << name << runs << " (" << balls << ")";
        cout << " 4s:" << fours << " 6s:" << sixes << "\n";
    }
};

class Bowler
{
public:
    string name;
    int balls = 0, runs = 0;
    Bowler() {}
    Bowler(string n) : name(n) {}
    double overs() const { return balls / 6 + (balls % 6) / 10.0; }
    double economy() const
    {
        if (balls == 0)
            return 0;
        return runs / (balls / 6.0);
    }
    void display() const
    {
        cout << "Bowler : " << name << "\n";
        cout << "Overs : " << fixed << setprecision(1) << overs() << "\n";
        cout << "Runs  : " << runs << "\n";

        cout << "Eco   : " << fixed << setprecision(2) << economy() << "\n";
    }
};

class CricketScoreBoard
{
    string matchName, venue, date;
    string battingTeam, bowlingTeam;
    int totalRuns = 0, totalBalls = 0, target = 0;

    Player striker, nonStriker;
    Bowler bowler;

public:
    CricketScoreBoard()
    {
        matchName = "India vs Australia";
        venue = "Jaipur";
        date = "15-Aug-2026";

        battingTeam = "India";
        bowlingTeam = "Australia";

        target = 30;

        striker = Player("Virat Kohli");
        nonStriker = Player("Shubman Gill");
        bowler = Bowler("Mitchell Starc");
    }

    double overs() const
    {
        return totalBalls / 6 + (totalBalls % 6) / 10.0;
    }
    double crr() const
    {
        if (totalBalls == 0)
            return 0;
        return totalRuns / (totalBalls / 6.0);
    }
    int ballsLeft() const
    {
        int left = 12 - totalBalls;
        return left < 0 ? 0 : left;
    }
    double rrr() const
    {
        if (target == 0 || ballsLeft() == 0)
            return 0;
        int need = target - totalRuns;
        if (need < 0)
            need = 0;
        return need / (ballsLeft() / 6.0);
    }

    void updateBall()
    {
        // Check if 2 overs are already completed
        if (totalBalls >= 12)
        {
            cout << "\n";
            cout << "============================================================\n";
            cout << "                    INNINGS OVER\n";
            cout << "============================================================\n";
            cout << "                    2 Overs Completed!\n";
            cout << "============================================================\n";
            return;
        }

        // Check if target has already been reached
        if (totalRuns >= target)
        {
            cout << "\n";
            cout << "============================================================\n";
            cout << "                 " << battingTeam << " WON!\n";
            cout << "                    TARGET REACHED\n";
            cout << "============================================================\n";
            return;
        }

        cout << "\n";
        cout << "============================================================\n";
        cout << "                     BALL UPDATE\n";
        cout << "============================================================\n\n";

        int need = target - totalRuns;

        if (need < 0)
            need = 0;

        cout << "Current Score : "
             << battingTeam << " " << totalRuns << "\n";

        cout << "Target        : "
             << target << "\n";

        cout << "Need          : "
             << need << " runs\n";

        cout << "Overs         : "
             << fixed << setprecision(1) << overs() << "\n";

        cout << "Balls Left    : "
             << ballsLeft() << "\n";

        cout << "\n------------------------------------------------------------\n";

        cout << "\nBall Result (0,1,2,3,4,5,6): ";

        int run;
        cin >> run;

        // Validate run
        if (run < 0 || run > 6)
        {
            cout << "\nInvalid Run! Please enter a value between 0 and 6.\n";
            return;
        }

        // Update team score
        totalRuns += run;

        // Update striker
        striker.runs += run;
        striker.balls++;

        // Update bowler
        bowler.runs += run;
        bowler.balls++;

        // Update total balls
        totalBalls++;

        // Check boundary
        if (run == 4)
        {
            striker.fours++;

            cout << "\n";
            cout << "============================================================\n";
            cout << "                         FOUR!\n";
            cout << "============================================================\n";
        }

        if (run == 6)
        {
            striker.sixes++;

            cout << "\n";
            cout << "============================================================\n";
            cout << "                          SIX!\n";
            cout << "============================================================\n";
        }

        // Dot ball
        if (run == 0)
        {
            cout << "\n";
            cout << "                         DOT BALL\n";
        }

        // Change strike for odd runs
        if (run % 2 == 1)
        {
            swap(striker, nonStriker);
        }

        // Change strike at the end of the over
        if (totalBalls % 6 == 0)
        {
            swap(striker, nonStriker);

            cout << "\n";
            cout << "============================================================\n";
            cout << "                     OVER COMPLETED\n";
            cout << "============================================================\n";
        }

        // Check if target has been reached
        if (totalRuns >= target)
        {
            cout << "\n";
            cout << "============================================================\n";
            cout << "                 " << battingTeam << " WON!\n";
            cout << "                    TARGET REACHED\n";
            cout << "============================================================\n";
            return;
        }
    }
    void display()
    {
        cout << "\n\n";

        cout << "============================================================\n";
        cout << "                 " << battingTeam << " vs " << bowlingTeam << "\n";
        cout << "                       " << venue << "\n";
        cout << "                    " << date << "\n";
        cout << "============================================================\n\n";

        cout << "                         " << battingTeam << "\n";

        cout << "                         "
             << totalRuns << "\n";

        cout << "                         "
             << fixed << setprecision(1)
             << overs() << "\n";

        cout << "\n------------------------------------------------------------\n\n";

        int need = target - totalRuns;

        if (need < 0)
            need = 0;

        cout << left
             << setw(18) << "Current RR"
             << setw(15) << "Target"
             << setw(15) << "Need"
             << setw(15) << "Required RR"
             << "\n";

        cout << left
             << setw(18) << fixed << setprecision(2) << crr()
             << setw(15) << target
             << setw(15) << need
             << setw(15) << fixed << setprecision(2) << rrr()
             << "\n";

        cout << "\n------------------------------------------------------------\n\n";

        cout << "BATSMEN\n\n";

        cout << left
             << setw(22) << striker.name
             << striker.runs << " (" << striker.balls << ")"
             << "    4s:" << striker.fours
             << "   6s:" << striker.sixes
             << "\n";

        cout << left
             << setw(22) << nonStriker.name
             << nonStriker.runs << " (" << nonStriker.balls << ")"
             << "    4s:" << nonStriker.fours
             << "   6s:" << nonStriker.sixes
             << "\n";

        cout << "\n------------------------------------------------------------\n\n";

        cout << "BOWLER\n\n";

        cout << "Name   : " << bowler.name << "\n";

        cout << "Overs  : "
             << fixed << setprecision(1)
             << bowler.overs() << "\n";

        cout << "Runs   : "
             << bowler.runs << "\n";

        cout << "Eco    : "
             << fixed << setprecision(2)
             << bowler.economy() << "\n";

        cout << "\n============================================================\n";
    }

    void summary()
    {
        cout << "\n";

        cout << "============================================================\n";
        cout << "                    MATCH SUMMARY\n";
        cout << "============================================================\n\n";

        cout << "Match       : " << matchName << "\n";
        cout << "Venue       : " << venue << "\n";
        cout << "Date        : " << date << "\n";

        cout << "\n------------------------------------------------------------\n\n";

        cout << "Final Score : "
             << battingTeam << " "
             << totalRuns << "\n";

        cout << "Overs       : "
             << fixed << setprecision(1)
             << overs() << "\n";

        cout << "Current RR  : "
             << fixed << setprecision(2)
             << crr() << "\n";

        cout << "Target      : "
             << target << "\n";

        cout << "\n------------------------------------------------------------\n";

        if (totalRuns >= target)
        {
            cout << "\nResult      : "
                 << battingTeam
                 << " WON THE MATCH!\n";
        }
        else if (totalBalls >= 12)
        {
            cout << "\nResult      : "
                 << bowlingTeam
                 << " WON THE MATCH!\n";
        }
        else
        {
            cout << "\nResult      : MATCH STILL IN PROGRESS\n";
        }

        cout << "\n============================================================\n";
    }

    void menu()
    {
        int ch;

        do
        {
            cout << "\n";

            cout << "============================================================\n";
            cout << "                    MATCH CONTROLS\n";
            cout << "============================================================\n\n";

            cout << "              [1] UPDATE BALL\n";
            cout << "              [2] LIVE SCOREBOARD\n";
            cout << "              [3] MATCH SUMMARY\n";
            cout << "              [4] EXIT\n";

            cout << "\n============================================================\n";
            cout << "              Enter Choice : ";

            cin >> ch;

            switch (ch)
            {
            case 1:
                updateBall();
                break;

            case 2:
                display();
                break;

            case 3:
                summary();
                break;

            case 4:
                cout << "\n";
                cout << "============================================================\n";
                cout << "              THANK YOU FOR USING\n";
                cout << "               CRICKET SCOREBOARD\n";
                cout << "============================================================\n";
                break;

            default:
                cout << "\nInvalid choice! Please select 1-4.\n";
            }

        } while (ch != 4);
    }
};

int main()
{
    CricketScoreBoard match;

    match.menu();
    return 0;
}

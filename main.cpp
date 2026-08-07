
#include <iostream>
#include <iomanip>
#include <string>
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

        totalRuns = 0;

        totalBalls = 0;

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
        cout << "\nBall Result (0,1,2,3,4,6): ";
        int x;
        cin >> x;

        if (totalBalls >= 12)
        {
            cout << "\n====================================\n";
            cout << "2 Overs Completed!\n";
            cout << "Innings Over.\n";
            cout << "====================================\n";
            return;
        }

        if (totalRuns == target)
            cout << "India Won !" << endl;

        int run = x; 

        if ( run > 6)
        {
            cout << "Invalid Run\n";
            return;
        }
        totalRuns += run;
        striker.runs += run;
        striker.balls++;
        bowler.runs += run;
        bowler.balls++;
        totalBalls++;

        if (run == 4)
            striker.fours++;
        if (run == 6)
            striker.sixes++;

        if (run % 2 == 1)
        {
            swap(striker, nonStriker);
        }
        if (totalBalls % 6 == 0)
        {
            swap(striker, nonStriker);
        }
    }

    void display()
    {
        cout << "\n=====================================================\n";
        cout << "              LIVE CRICKET SCOREBOARD\n";
        cout << "=====================================================\n\n";
        cout << "Match : " << matchName << "\n";
        cout << "Venue : " << venue << "\n";
        cout << "Date  : " << date << "\n\n";
        cout << battingTeam << " : " << totalRuns  << " (" << fixed << setprecision(1) << overs() << ")\n\n";
        // fixed -> tells compiler that it is necessary to have 1 value after decimal .
        // if no value is present after decimal then it will automatically add 0 at the end .
        cout << "Current RR : " << fixed << setprecision(2) << crr() << "\n";
        if (target > 0)
        {
            int need = target - totalRuns;
            if (need < 0)
                need = 0;
            cout << "Target     : " << target << "\n";
            cout << "Need       : " << need << " runs from " << ballsLeft() << " balls\n";
            cout << "Required RR: " << fixed << setprecision(2) << rrr() << "\n";
        }
        cout << "\n---------------- Batsmen ----------------\n";
        striker.display();
        nonStriker.display();
        cout << "\n---------------- Bowler -----------------\n";
        bowler.display();
        cout << "=====================================================\n";
    }

    void summary()
    {
        cout << "\n========= MATCH SUMMARY =========\n";
        display();
        if (target > 0)
        {
            if (totalRuns >= target)
                cout << "\n"
                     << battingTeam << " won the match.\n";
            else if (totalBalls >= 12)
                cout << "\n"
                     << bowlingTeam << " won the match.\n";
        }
    }

    void menu()
    {
        int ch;
        do
        {
            cout << "\n1.Update Ball\n2.Show Scoreboard\n3.Match Summary\n4.Exit\nChoice : ";
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
                cout << "Thank you!\n";
                break;
            default:
                cout << "Invalid choice\n";
            }
        } while (ch != 5);
    }
};

int main()
{
    CricketScoreBoard match;

    match.menu();
    return 0;
}

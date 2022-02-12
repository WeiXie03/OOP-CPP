// evenwins.cpp

// My Computer Strategy below

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Wei (Tom) Xie
// St.# : 301466036
// Email: wxa38@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough detail
// so that someone can see the exact source and extent of the borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have not
// seen solutions from other students, tutors, websites, books, etc.
//
/////////////////////////////////////////////////////////////////////////

// My Computer Strategy
// My default strategy is to take the maximum possible marbles that will achieve an
// even score after taking. Additionally, I wrote out all the possible "paths" the
// game could take on paper (all choices for how many marbles human and computer can take)
// beginning at several smaller values of number of marbles left in the middle.
// Based on usually being able to win when 7 are left, I always try to take such that
// 7 remain when it is possible in 1 turn.
// This strategy is not perfect. If there are 5 left, the human's score is even
// and the computer's even, the human could take 4. Then there is 1 left and
// the computer would be forced to take 1, making my score odd.

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// global variables

// available taunts
const size_t NUM_TAUNTS = 5;
// cannot make array of std::string's
const char* TAUNTS[NUM_TAUNTS] = {
    "tremble before it's mighty brain!",
    "wowww, niiicee... better think about what you did wrong.",
    "ha, fool!",
    "I knew I'd win!",
    "so, you just gonna lose like that?"
};

struct Gamestate
{
    int marbles_in_middle = -1;
    int human_marbles     = -1;
    int computer_marbles  = -1;

    enum class Player {
        human,
        computer
    };
    Player whose_turn;

    // keep track of wins
    int num_Hwins = 0;
    int num_Cwins = 0;
};

void print_boxed_msg(const string& msg) {
    // top edge
    cout << '+';
    // one dash per char of msg, plus two total spaces of padding
    cout << string( msg.size()+2 , '-');
    cout << '+' <<'\n';

    // middle level
    cout << "| " << msg << " |" << '\n';

    // bottom edge, same as top
    cout << '+';
    // one dash per char of msg, plus two total spaces of padding
    cout << string( msg.size()+2 , '-');
    cout << '+' <<'\n';
}

void welcome_screen() {
    print_boxed_msg("Welcome to Even Wins!");
    cout << "Even Wins is a two-person game. You start with\n";
    cout << "27 marbles in the middle of the table.\n";
    cout << "\n";
    cout << "Players alternate taking marbles from the middle.\n";
    cout << "A player can take 1 to 4 marbles on their turn, and\n";
    cout << "turns cannot be skipped. The game ends when there are\n";
    cout << "no marbles left, and the winner is the one with an even\n";
    cout << "number of marbles.";
    cout << "\n";
}

string marbles_str(int n) {
    if (n == 1) return "1 marble";
    return to_string(n) + " marbles";
}

void choose_first_player(Gamestate& game_state) {
   for (;;) {
        cout << "\nDo you want to play first? (y/n) --> ";
        string ans;
        cin >> ans;
        if (ans == "y") {
            game_state.whose_turn = game_state.Player::human;
            return;
        } else if (ans == "n") {
            game_state.whose_turn = game_state.Player::computer;
            return;
        } else {
            cout << "\nPlease enter 'y' if you want to play first,\n";
            cout << "or 'n' if you want to play second.\n";
        }
    }
} // choose_first_player

void next_player(Gamestate& game_state) {
    bool now_human = (game_state.whose_turn == game_state.Player::human);
    bool now_comp = (game_state.whose_turn == game_state.Player::computer);

    // if now human, make next computer
    game_state.whose_turn = now_human ? game_state.Player::computer :
        (
         // if not now human, check if now computer
         // if so, make now human
         // otherwise something's wrong (not one of the enum values), and don't do anything
         now_comp ? game_state.Player::human : game_state.whose_turn
        );
}

void print_board(const Gamestate& game_state) {
    cout << "\n";
    cout << " marbles in the middle: " << game_state.marbles_in_middle 
         << " " << string(game_state.marbles_in_middle, '*') << "\n";
    cout << "    # marbles you have: " << game_state.human_marbles << "\n";
    cout << "# marbles computer has: " << game_state.computer_marbles << "\n";
    cout <<  "\n";
}

// returns true if s is an int, and false otherwise
// https://www.cplusplus.com/reference/string/stoi/
bool is_int(const string& s) {
    try {
        stoi(s); // throws an invalid_argument exception if conversion fails
        return true;
    } catch (...) {
        return false;
    }
}

void human_turn(Gamestate& game_state) {
    // get number in range 1 to min(4, game_state.marbles_in_middle)
    int max_choice = min(4, game_state.marbles_in_middle);
    cout << "It's your turn!\n";
    for(;;) {
        cout << "Marbles to take? (1 - " << max_choice << ") --> ";
        string s;
        cin >> s;
        if (!is_int(s)) {
            cout << "\n  Please enter a whole number from 1 to " << max_choice
                 << "\n";
            continue;
        }

        // convert s to an int so it can be compared
        int n = stoi(s);
        if (n < 1) {
            cout << "\n  You must take at least 1 marble\n";
            continue;
        }
        if (n > max_choice) {
            cout << "\n  You can take at most " << marbles_str(max_choice)
                 << "\n";
            continue;
        }

        cout << "\nOkay, taking " << marbles_str(n) << " ...\n";
        game_state.marbles_in_middle -= n;
        game_state.human_marbles += n;

        return;
    } // for
} // human_turn

int max_for_even(const Gamestate& game_state) {
    // calculates the maximum number of marbles one can take to achieve an even score
    int max_choice = min(4, game_state.marbles_in_middle);
    
    // if max possible odd
    if (max_choice % 2 != 0) {
        // and current score even, take even
        if (game_state.computer_marbles % 2 == 0)
            --max_choice;
        // otherwise, can take all
    }
    // if max possible even
    else {
        // and current score odd, take odd
        if (game_state.computer_marbles % 2 != 0)
            --max_choice;
        // otherwise, can take all
    }

    // make sure max_choice > 0
    if (max_choice == 0)
        max_choice = 1;

    return max_choice;
}

void computer_turn(Gamestate& game_state) {
    cout << "It's the computer's turn ...\n";
 
    // num to take
    int n = 0;
    // I manually worked through these cases on paper, writing out all possible "paths" for the game to take until game-end, based on n = 7 usually being cases where the computer can win
    switch (game_state.marbles_in_middle) {
        case 11:
            n = 4;
            break;
        case 10:
            n = 3;
            break;
        case 9:
            n = 2;
            break;
        case 8:
            n = 1;
            break;

        // for all others, just maximum possible that will get an even score
        default:
            n = max_for_even(game_state);
    }

    cout << "Computer takes " << marbles_str(n) << " ...\n";
    game_state.marbles_in_middle -= n;
    game_state.computer_marbles += n;
}

void game_over(Gamestate& game_state, const char* taunts[], size_t num_taunts) {
    // array of taunts and its size
 
    cout << "\n";
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
         << "!! All the marbles are taken: Game Over !!\n"
         << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    print_board(game_state);
    if (game_state.human_marbles % 2 == 0) {
        cout << "You are the winner! Congratulations!\n";
        game_state.num_Hwins ++;
    } else {
        // pick a random taunt
        int n = 1 + rand() % num_taunts;
        cout << "The computer wins: " << taunts[n] << '\n';
        game_state.num_Cwins ++;
    }
}

void play_game(Gamestate& game_state, const char* taunts[], size_t num_taunts) {
    // initialize the game state
    game_state.marbles_in_middle = 27;
    game_state.human_marbles = 0;
    game_state.computer_marbles = 0;
    print_board(game_state);

    for (;;) {
        if (game_state.marbles_in_middle == 0) {
            game_over(game_state, taunts, num_taunts);
            return;
        } else if (game_state.whose_turn == game_state.Player::human) {
            human_turn(game_state);
            print_board(game_state);
            next_player(game_state);
        } else if (game_state.whose_turn == game_state.Player::computer) {
            computer_turn(game_state);
            print_board(game_state);
            next_player(game_state);
        }
    } // for
} // play_game

void print_stats(const Gamestate& game_state) {
    // print play summary after user wants to stop
    string title = "Statistics";
    cout << title <<'\n';
    cout << string(title.size(), '-') << '\n';

    cout << "total games: " << game_state.num_Hwins + game_state.num_Cwins << '\n';
    cout << "human wins: " << game_state.num_Hwins << '\n';
    cout << "computer wins: " << game_state.num_Cwins << '\n';
}

int main() {
    srand(time(NULL));

    Gamestate gamestate;

    welcome_screen();

    for(;;) {
        // reset all game state except number of wins, games
        gamestate.marbles_in_middle = -1;
        gamestate.human_marbles     = -1;
        gamestate.computer_marbles  = -1;

        choose_first_player(gamestate);
        // use global const taunts
        play_game(gamestate, TAUNTS, NUM_TAUNTS);

        // ask if the user if they want to play again
        cout << "\nWould you like to play again? (y/n) --> ";
        string again;
        cin >> again;
        if (again == "y") {
            cout << "\nOk, let's play again ...\n";
        } else {
            cout << "\nOk, thanks for playing \n";
            print_stats(gamestate);
            cout << "Goodbye!\n";
            return 0;
        }
    } // for
} // main

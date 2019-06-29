#include <iostream>
#include <cstdlib> //dla time(int)
#include <ctime> //dla srand()

using namespace std;

class board {
    public:
        char bd[9];
        board() {
            char num = '1';
            for (int i = 0; i < 9; i++) {
                bd[i] = num++;
            }
        }

        void change(int index, bool player) {
            if (index > 0 && index < 10) {
                index--; //wyrownanie indeksacji

                if (!is_taken(index)) {
                    if (!player)
                        bd[index] = 'X';
                    else
                        bd[index] = 'O';
                }
                else
                    throw runtime_error("Invalid input!");
            }
            else
                throw runtime_error("Invalid input!");
        }

        static bool is_inside(int i, int j) {
            return  (i == 1 && (j == 1 || j == 5 || j == 9)) ||
                    (i == 5 && (j == 1 || j == 5 || j == 9)) ||
                    (i == 9 && (j == 1 || j == 5 || j == 9));
        }

        bool check_win() {
            if (bd[0] == bd[1] && bd[0] == bd[2] && bd[0] != ' ') //pierwszy rzad
                return true;

            else if (bd[3] == bd[4] && bd[3] == bd[5] && bd[3] != ' ') //drugi rzad
                return true;

            else if (bd[6] == bd[7] && bd[6] == bd[8] && bd[6] != ' ') //trzeci rzad
                return true;

            else if (bd[0] == bd[3] && bd[0] == bd[6] && bd[0] != ' ') //pierwsza kolumna
                return true;

            else if (bd[1] == bd[4] && bd[1] == bd[7] && bd[1] != ' ') //druga kolumna
                return true;

            else if (bd[2] == bd[5] && bd[2] == bd[8] && bd[2] != ' ') //trzecia kolumna
                return true;

            else if (bd[0] == bd[4] && bd[0] == bd[8] && bd[0] != ' ') //prawy-lewy skos
                return true;

            else if (bd[2] == bd[4] && bd[2] == bd[6] && bd[2] != ' ') //lewy-prawy skos
                return true;

            return false;
        }

        void clear_board() {
            for (int i = 0; i < 9; i++) {
                    bd[i] = ' ';
            }
        }

        int generate_move() {
        //zwraca cyfre 1-9 ktora oznacza w ktorym
        //miejscu ma zostac postawione 'O'

            /*srand(time(0));
            int index = rand() % 9;*/

            int index = 0;

            return ++index;
        }

        bool is_taken(int idx) {
            return bd[idx] == 'X' || bd[idx] == 'O';
        }

        friend ostream& operator<<(ostream& os, const board& rhv)  {
            int idx = 0;
            for (int i = 0; i < 11; i++) {
                for (int j = 0; j < 11; j++) {
                    if (is_inside(i, j)) {
                        os << rhv.bd[idx++];
                    }
                    else if (i == 3 || i == 7)
                        os << '-';
                    else if (j == 3 || j == 7)
                        os << '|';
                    else
                        os << ' ';

                    if (j == 10)
                        os << endl;
                }
            }
            return os;
        }
};

int main()
{
    int place = 0;
    bool player = 0;
    board game;
    cout << game;
    game.clear_board(); //chowa cyfry w polach

    for (int i = 0; i < 9; i++) {
        cout << endl << endl << "Your move: ";

        //kazda zla wprowadzona wartosc spowoduje blad
        //kod w bloku try zostaje pominiety
        try {
            if (!player)
                cin >> place;
            else
                place = game.generate_move();

            game.change(place, player);

            if (game.check_win()) {
                system("cls");
                cout << game;
                cout << "Game ended! ";
                if (!player)
                    cout << "You won!";
                else
                    cout << "You lost!";
                break;
            }

            if (!player)
                player = 1;
            else
                player = 0;
        }
        //gracz ma ruch, dopoki nie wykona prawidlowego ruchu
        catch (...) { i--; }

        system("cls");
        cout << game;
    }

    if (!game.check_win()) {
        cout << "Draw!";
    }

    return 0;
}

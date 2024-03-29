/*
Program umozliwia zagranie w kolko i krzyzk
z komputerem. Gracz wykonuje ruch wporwadzajac
wartosc 1-9 a algorytm generuje ruch dla komputera
*/

#include <iostream>

using namespace std;

class board {
    public:
        char bd[9];
        const char cpu = 'O'; //token komputera
        const char player = 'X'; //token gracza

        board() {
            char num = '1';
            for (int i = 0; i < 9; i++) {
                bd[i] = num++;
            }
        }

        //wprowadza tokeny do tablicy
        //zwraca true gdy dodanie powiodlo sie
        //wpp zwraca falsz
        bool change(int index, char on_mv) {
            if (index >= 0 && index < 9) {
                if (!is_taken(index)) {
                    if (on_mv == player) {
                        bd[index] = player;
                        return true;
                    }
                    else {
                        bd[index] = cpu;
                        return true;
                    }
                }
            }
            //gdy podano zly indeks
            return false;
        }

        //funckja sprawdza czy jakikolwiek gracz wygral
        bool check_win() {
            if (bd[0] == bd[1] && bd[0] == bd[2] && bd[0] != ' ') //pierwszy rzad
                return true;

            if (bd[3] == bd[4] && bd[3] == bd[5] && bd[3] != ' ') //drugi rzad
                return true;

            if (bd[6] == bd[7] && bd[6] == bd[8] && bd[6] != ' ') //trzeci rzad
                return true;

            if (bd[0] == bd[3] && bd[0] == bd[6] && bd[0] != ' ') //pierwsza kolumna
                return true;

            if (bd[1] == bd[4] && bd[1] == bd[7] && bd[1] != ' ') //druga kolumna
                return true;

            if (bd[2] == bd[5] && bd[2] == bd[8] && bd[2] != ' ') //trzecia kolumna
                return true;

            if (bd[0] == bd[4] && bd[0] == bd[8] && bd[0] != ' ') //prawy-lewy skos
                return true;

            if (bd[2] == bd[4] && bd[2] == bd[6] && bd[2] != ' ') //lewy-prawy skos
                return true;

            return false;
        }

        void clear_board() {
            for (int i = 0; i < 9; i++) {
                    bd[i] = ' ';
            }
        }

        //funkcja rekurencyjnie sprawdza wszystkie mozliwosci ruchu i
        //zwraca ewaluacje pozycji dla gracza ruszajacego sie, sprawdzajac
        //czy dana sekwencja ruchu prowadzi do wygrnej/porazki/remisu
        //on_mv informuje kto aktualnie wykonuje ruch
        int evaluate(char on_mv) {
            //jezeli gra sie skonczyla gracz ktory wczesniej wykonal ruch - wygral
            if (check_win() && on_mv == player)
                return 1; //ewaluacja dla wygranej komputera

            if (check_win() && on_mv == cpu)
                return -1; //ewaluajca dla wygranej gracza

            if (check_draw())
                return 0; //remis

            if (on_mv == cpu) {
                int best = -1; //najnizsza mozliwa ewaluacja, gdy ruch ma komputer
                for (int i = 0; i < 9; i++) {
                    if (!is_taken(i)) {
                        bd[i] = cpu;
                        //jezeli istnieje skwencja ruchow dajaca cpu remis lub wygrana
                        //evaluate(...) zworci wartosc wieksza niz -1
                        best = max(best, evaluate(player));
                        bd[i] = ' ';
                    }
                }
                return best;
            }

            //gdy na ruchu jest gracz
            else {
                int best = 1; //najnizsza mozliwa ewaluacja, gdy ruch ma gracz
                for (int i = 0; i < 9; i++) {
                    if (!is_taken(i)) {
                        bd[i] = player;
                        //jezeli istnieje sekwencja ruchow dajaca graczowi remis lub wygrana
                        //evalute(...) zwroci wartosc mniejsza niz 1
                        best = min(best, evaluate(cpu));
                        bd[i] = ' ';
                    }
                }
                return best;
            }
            return 0;
        }

        //zwraca cyfre 1-9 ktora oznacza w ktorym
        //miejscu ma zostac postawiony token cpu
        int generate_move() {
            int best = -1; //przechowuje najlepsza dotychczasowa ewaluacje
            int idx = -1;

            for (int i = 0; i < 9; i++) {
                if (!is_taken(i)) {
                    bd[i] = cpu;
                    int value = evaluate(player);
                    bd[i] = ' ';

                    if (value > best) {
                        best = value;
                        idx = i;
                    }
                }
            }
            return idx;
        }

        bool is_taken(int idx) {
            return bd[idx] != ' ';
        }

        //funkcja sprawdza czy nastapil remis
        bool check_draw() {
            if (check_win())
                return false;

            for (int i = 0; i < 9; i++) {
                if (!is_taken(i))
                    return false;
            }
            return true;
        }

        //funkcja pomoga wyznaczyc miejsca w ktorych
        //nalezy wyswietlic tokeny na konsoli
        static bool show_token(int i, int j) {
            return  (i == 1 && (j == 1 || j == 5 || j == 9)) ||
                    (i == 5 && (j == 1 || j == 5 || j == 9)) ||
                    (i == 9 && (j == 1 || j == 5 || j == 9));
        }


        //wyswietla plansze z tokenami na konsoli
        friend ostream& operator<<(ostream& os, const board& rhv)  {
            int idx = 0;
            for (int i = 0; i < 11; i++) {
                for (int j = 0; j < 11; j++) {
                    if (show_token(i, j)) {
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
    board game; //tablica zainicjowana cyframi 1-9
    int place = -1; //przechowuje informacje, gdzie zostal ustawiony token
    char on_move = game.player; //przechowuje informacje, kto wykonuje ruch

    cout << game;
    game.clear_board(); //czysci tablice z poczatkowych cyfr

    //game loop
    for (int i = 0; i < 9; i++) {
        cout << endl << endl << "Your move: ";

        if (on_move == game.player) {
            do {
                cin >> place;
                //gracz wprowadza wartosci 1-9 a
                //indeksacja talbicy jest 0-8
            } while (!game.change(--place, on_move));
            //gracz wykonuje ruch, dopoki nie wykona prawidlowego ruchu
        }
        else
            game.change(game.generate_move(), on_move);

        if (game.check_win()) {
            system("cls");
            cout << game;
            cout << "Game ended! ";
            if (on_move == game.player)
                cout << "You won!";
            else
                cout << "You lost!";
            break;
        }

        //zmiana ruchu
        if (on_move == game.player)
            on_move = game.cpu;
        else
            on_move = game.player;

        system("cls");
        cout << game;
    }

    if (!game.check_win())
        cout << "Draw!";

    return 0;
}

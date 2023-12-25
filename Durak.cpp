#include <iostream>
#include "Header.h"
using namespace std;

int main() {
    Game game;
    Bots bots;

    cout << " _____  _   _  _____    _____   ___    ___   _         ____     _     __  __  _____ \n";
    cout << "|_   _|| | | || ____|  |  ___| / _ \\  / _ \\ | |       / ___|   / \\   |  \\/  || ____|\n";
    cout << "  | |  | |_| ||  _|    | |_   | | | || | | || |      | |  _   / _ \\  | |\\/| ||  _|\n";
    cout << "  | |  |  _  || |___   |  _|  | |_| || |_| || |___   | |_| | / ___ \\ | |  | || |___\n";
    cout << "  |_|  |_| |_||_____|  |_|     \\___/  \\___/ |_____|   \\____|/_/   \\_\\|_|  |_||_____|\n";


    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    // Standard deck (each suit for each value) - 36 cards
    for (const auto& nom : NOMINALS) {
        for (const auto& suit : SUIT) {
            game.Deck.emplace_back(nom, suit);
        }
    }
    game.printDurakRules();

    ViewHistoyeGame();
    // Shuffle the deck
    game.shuffleDeck();
    // Drawing out the deck

    game.countBots();

    game.Dealing_cards(&bots);

    // Берем первую карту (козырная) и кладем в конец колоды
    game.trump_card = game.Deck[0].second;
    cout << "Trump card: " << game.Deck[0].first << game.Deck[0].second << endl;
    swap(game.Deck[0], game.Deck.back());

    game.verifTrump(bots);
    while (!game.Deck.empty() || !(bots.Deck.size() == 1)) {
        // Player attacks bot
        if (game.index_move == 0) {
            int result = 2;
            int move_index;
            // 0 - took the cards, 88 - bit
            while (true) {
                cout << endl;
                cout << "-------------------------------------------------------------------" << endl;
                game.tablePrint(bots);

                do {
                    move_index = bots.Verif_move();

                    if (move_index == 88) break;

                    result = game.AtacPlayer(move_index, &bots);
                } while (result == 6);

                // If the player has no cards to attack
                if (move_index == 88) {
                    game.bitaCards(&bots);

                    if ((bots.Deck[0].size() == 0) && game.Deck.empty()) {
                        cout << "Player win" << endl;
                        historyGame(game.count_p_g, "Win");
                        return 0;
                    }
                    else if (bots.Deck.size() == 1) {
                        cout << "Player loser" << endl;
                        historyGame(game.count_p_g, "Loser");
                        return 0;
                    }

                    cout << "Bita" << endl;
                    game.index_move += 1;
                    break;
                }

                result = game.verifDefinPlayer(game.index_move + 1, &bots);
                if (result == 0) {
                    
                    if ((bots.Deck[0].size() == 0) && game.Deck.empty()) {
                        cout << "Player win" << endl;
                        historyGame(game.count_p_g, "Win");
                        return 0;
                    }
                    else if (bots.Deck.size() == 1) {
                        cout << "Player loser" << endl;
                        historyGame(game.count_p_g, "Loser");
                        return 0;
                    }
                    cout << "Zabral" << endl;
                    if (bots.Deck[0].size() != 0) {
                        int b = game.playerTossing(&bots);
                    }

                    game.takesCards(&bots);

                    if(game.count_p == 1) game.index_move = 0;
                    else game.index_move += 1;
                    break;
                }
                //system("cls");
                cout << "-------------------------------------------------------------------" << endl;

            }
        }
        // Bot attacks player
        else if (game.index_move == game.count_p) {
            int result = 2;
            int move_index;
            // 0 - bit , 88 -took the cards
            while (true) {

                cout << endl;

                cout << "-------------------------------------------------------------------" << endl;

                if ((bots.Deck[0].size() == 0) && game.Deck.empty()) {
                    cout << "Player win" << endl;
                    historyGame(game.count_p_g, "Win");

                    return 0;
                }
                result = game.AtacBot(&bots);

                // If the bot has no cards to attack
                if (result == 6) {
                    game.tablePrint(bots);

                    if ((bots.Deck[0].size() == 0) && game.Deck.empty()) {
                        cout << "Player win" << endl;
                        historyGame(game.count_p_g, "Win");

                        return 0;
                    }
                    else if (bots.Deck.size() == 1) {
                        cout << "Player loser" << endl;
                        historyGame(game.count_p_g, "Loser");
                        return 0;
                    }
                    game.bitaCards(&bots);

                    game.index_move = 0;
                    //system("cls");
                    cout << "Bita" << endl;

                    break;
                }

                game.tablePrint(bots);

                do {
                    move_index = bots.Verif_move();

                    if (move_index == 88) break;

                    result = game.DefinPlayer(move_index, &bots);
                } while (result == 6);

                if (move_index == 88) {
                    game.takesCards(&bots);

                    if (bots.Deck.size() == 1) {
                        cout << "Player loser" << endl;
                        historyGame(game.count_p_g, "Loser");

                        return 0;
                    }

                    game.index_move = 1;
                    //system("cls");
                    cout << "Zabral" << endl;
                    break;
                }
                cout << "-------------------------------------------------------------------" << endl;
            }

        }
        // Bot vs bot        
        else {
            int result = 2;
            // 0 - took the cards, 8 - bit            
            while (true) {
                cout << endl;
                result = game.AtacBot(&bots);

                // If the bot has no cards to attack                
                if (result == 6) {

                    game.tablePrint(bots);
                    cout << "Bita" << endl;
                    game.bitaCards(&bots);

                    if ((bots.Deck[0].size() == 0) && game.Deck.empty()) {
                        cout << "Player win" << endl;
                        historyGame(game.count_p_g, "Win");
                        return 0;
                    }
                    else if (bots.Deck.size() == 1) {
                        cout << "Player loser" << endl;
                        historyGame(game.count_p_g, "Loser");
                        return 0;
                    }
                   
                    game.index_move += 1;
                    break;
                }

                result = game.verifDefinPlayer(game.index_move + 1, &bots);
                if (result == 0) {

                    cout << "-------------------------------------------------------------------" << endl;
                    game.tablePrint(bots);
                    cout << "-------------------------------------------------------------------" << endl;
                    game.takesCards(&bots);

                    if ((bots.Deck[0].size() == 0) && game.Deck.empty()) {
                        cout << "Player win" << endl;
                        historyGame(game.count_p_g, "Win");
                        return 0;
                    }
                    else if (bots.Deck.size() == 1) {
                        cout << "Player loser" << endl;
                        historyGame(game.count_p_g, "Loser");
                        return 0;
                    }

                    game.index_move += 1;
                    cout << "Zabral" << endl;
                    break;
                }

            }
        }
    }

    return 0;
}

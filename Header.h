#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>




using namespace std;

// Масти
//const string SPADES = "♠";
//const string HEARTS = "♥";
//const string DIAMS = "♦";
//const string CLUBS = "♣";
const vector<string> SUIT = {"s", "h", "d", "c"};

// Advantages of cards
const vector<string> NOMINALS = { "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

// Skin dignity rank
map<string, unsigned> RANK
{
    {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
    {"10", 10}, {"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14}
};

string path = "history.txt";


//Deck Creation 
const map<string, int> NAME_TO_VALUE = []() {
    map<string, int> map;
    for (int i = 0; i < NOMINALS.size(); ++i) {
        map[NOMINALS[i]] = i;
    }
    return map;
    }();

class Bots {
public:
    vector<vector<pair<string, string>>> Deck;

    void printDeckPlayer(int index) {
        for (const auto& card : Deck[index]) {
            cout << card.first << card.second << " ";
        }
        cout << endl;
    }

    void DeletePlayer(int index) {
        //if (Deck.size() == 2) {
        //    }
        cout << endl;
        cout << "bots left: " << Deck.size() << endl;
        cout << endl;
        Deck.erase(Deck.begin() + index);
        }

    int Verif_move() {
        int index_move;
        while (true) {
            cout << "Select a card by index: ";
            if ((cin >> index_move)) {
                if ((Deck[0].size() > index_move && index_move >= 0) || index_move == 88) {
                    // Ввод успешен
                    return index_move;
                }
                else {
                    cout << "index in out of input range" << endl;
                }
            }
            else {
                // Очистка флагов ошибок
                std::cin.clear();
                // Очистка буфера ввода
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Input Error. Please enter an integer." << endl;
            }
        }
    }
};

class Game {
public:
    vector<pair<string, string>> Deck;
    vector < pair < string, string >> attacking_cards;
    vector < pair < string, string >> defending_cards;
    int count_p;
    int index_move = 0;
    string trump_card;
    int count_p_g;

    void countBots() {
        int count;
        while (true) {
            cout << "Count bots (1 - 4): ";
            if ((cin >> count)) {
                if (count > 0 && count <= 4) {
                    // Ввод успешен
                    count_p = count;
                    count_p_g = count;
                    break;
                }
                else {
                    cout << "out of input range" << endl;
                }
            }
            else {
                // Очистка флагов ошибок
                std::cin.clear();
                // Очистка буфера ввода
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Input Error. Please enter an integer." << endl;
            }
        }
    }

    //Who goes first
    void verifTrump(Bots bot) {
        pair<string, string> card_t;
        for (int i = 0; i <= count_p; i++) {
            for (auto card : bot.Deck[i]) {
                if (((card.second == card_t.second) && (RANK[card.first] < RANK[card_t.first])) || (card_t.first.empty()) && (card.second == trump_card)) {
                    card_t = card;
                    index_move = i;
                    //cout << "index: " << i << endl;
                    //cout << "card: " << card_t.first << card_t.second << endl;
                }
            }
        }
    }
    
    //Displays the rules of the game
    void printDurakRules() {
        int check;
        while (true) {
            cout << "Would you like to know the rules of the game (1 - yes / 0 - no)?\033[0m" << endl;
            if ((cin >> check)) {
                if (check == 1 || check == 0) {
                    // Ввод успешен
                    break;
                }
                else {
                    cout << "Input Error. Please enter an integer." << endl;

                }
            }
            else {
                // Очистка флагов ошибок
                std::cin.clear();

                // Очистка буфера ввода
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Input Error. Please enter an integer." << endl;
            }
        }
        if (check) {
            std::cout << "**Durak Rules:**\n\n";

            std::cout << "**Deck:**\n";
            std::cout << "- A standard deck of 36 cards is used.\n\n";

            std::cout << "**Objective:**\n";
            std::cout << "- The goal is to get rid of all your cards.\n\n";

            std::cout << "**Card Values:**\n";
            std::cout << "- Jacks - 11 points, Queens - 12 points, Kings - 13 points, Aces - 14 points.\n";

            std::cout << "- s = SPADES\n\n";
            std::cout << "- h = HEARTS\n\n";
            std::cout << "- d = DIAMS\n\n";
            std::cout << "- c = CLUBS\n\n";

            std::cout << "- Other cards have values corresponding to their ranks.\n\n";

            std::cout << "**Card Order:**\n";
            std::cout << "- Ascending order: 6, 7, 8, 9, 10, Jack, Queen, King, Ace.\n\n";

            std::cout << "**Dealing Cards:**\n";
            std::cout << "1. Each player is dealt 6 (or sometimes 5) cards.\n";
            std::cout << "2. One card from the remaining deck is revealed and set face up. This card determines the trump suit.\n\n";

            std::cout << "**Trump Suit:**\n";
            std::cout << "- All cards of the trump suit are worth double points.\n\n";

            std::cout << "**Gameplay:**\n";
            std::cout << "1. The player with the trump six starts the game.\n";
            std::cout << "2. Going clockwise, each player makes a move by playing a card higher in rank or a trump card.\n";
            std::cout << "3. The player playing the card can \"beat\" the previous card by playing a higher rank or a trump.\n";
            std::cout << "4. If a player can't beat the previous card, they take all the cards on the table.\n";
            std::cout << "5. The goal is to get rid of all your cards.\n\n";
            std::cout << "6. To redeem the card or pick it up, click 88.\n\n";

            std::cout << "**Taking Cards:**\n";
            std::cout << "- If a player cannot beat the current card, they collect all the cards on the table.\n\n";

            std::cout << "**Scoring:**\n";
            std::cout << "- After each round, points are tallied. Jacks, queens, kings, and aces contribute points.\n\n";

            std::cout << "**End of Round:**\n";
            std::cout << "- The player who first gets rid of all their cards has the right to play the last card in the next round.\n\n";

            std::cout << "**End of Game:**\n";
            std::cout << "- The game continues until one player runs out of cards.\n";

            std::cout << "These are general rules, and variations exist. Additional rules, such as \"throw-in\" or \"adding on,\" might be introduced to make the game more interesting.\n";
            
            cout << "Enter any character to continue" << endl;
            cin >> check;
            system("cls");

        }
    }

    //The deck is shown to be shuffled
    void printDeck() {
        for (const auto& card : Deck) {
            cout << card.first << card.second << " ";
        }
        cout << endl;
    }

    // Function for shuffling the deck
    void shuffleDeck() {
        srand(static_cast<unsigned>(time(0)));
        for (int i = Deck.size() - 1; i > 0; --i) {
            int j = rand() % (i + 1);
            swap(Deck[i], Deck[j]);
        }
    }

    //Dealing cards
    void Dealing_cards(Bots *deck) {
        vector<pair<string, string>> deck_p(6);
        for (int j = 0; j < count_p + 1; j++) {
            for (int i = 0; i < 6; i++) {
                deck_p[i] = Deck[0];
                Deck.erase(Deck.begin());
            }
            deck->Deck.push_back(deck_p);
        }

    }
   
    //Table output
    void tablePrint(Bots bot) {
        if (index_move == 0) {
            cout << "Player atac bot#" << index_move + 1 << endl;
            cout << endl;
        }
        else if (index_move == count_p) {
            cout << "Bot#"<< index_move << " atac player" << endl;
            cout << endl;
        }
        else {
            cout << "Bot#" << index_move << " atac bot#" << index_move + 1 << endl;
            cout << endl;
        }

        cout << "Size deck: " << Deck.size() << endl;
        cout << endl;
        cout << "Trump card: " << trump_card << endl;
        cout << endl;



        cout << "\033[1;31mAtacing cards:  \033[0m";
        for (int i = 0; i < attacking_cards.size(); i++) {
            cout << attacking_cards[i].first << attacking_cards[i].second << ", ";
        }
        cout << endl;
        cout << endl;

        cout << "\033[1;34mDefin cards: \033[0m";
        for (int i = 0; i < defending_cards.size(); i++) {
            cout << defending_cards[i].first << defending_cards[i].second << ", ";
        }
        cout << endl;
        cout << endl;
        if (index_move == 0) {
            cout << "\033[1;32mYour cards: \033[0m";
            bot.printDeckPlayer(0);
            cout << endl;
            cout << "Bit cards == 88";
        }
        else if (index_move == count_p) {
            cout << "\033[1;32mYour cards: \033[0m";
            bot.printDeckPlayer(0);
            cout << endl;
            cout << "Take cards == 88";
        }
        cout << endl;

    }
    
    //Player attack
    int AtacPlayer(int index, Bots* bot) {
        if (attacking_cards.empty() && defending_cards.empty()) {
            attacking_cards.push_back(bot->Deck[0][index]);
            bot->Deck[0].erase(bot->Deck[0].begin() + index);
            return 2;
        }
        for (pair <string, string> card : attacking_cards) {
            if (bot->Deck[0][index].first == card.first) {
                attacking_cards.push_back(bot->Deck[0][index]);
                bot->Deck[0].erase(bot->Deck[0].begin() + index);
                return 2;
            }
        }
        for (pair <string, string> card : defending_cards) {
            if (bot->Deck[0][index].first == card.first) {
                attacking_cards.push_back(bot->Deck[0][index]);
                bot->Deck[0].erase(bot->Deck[0].begin() + index);
                return 2;
            }
        }
        return 6;
    }

    //Bot protection
    int verifDefinPlayer(int index, Bots* bot) {
        pair <string, string> atac_card = attacking_cards[attacking_cards.size() - 1];
        for (int i = 0; i < bot->Deck[index].size(); i++) {
            // проверяет есть ли карта такой же масти, но с большим наминалом

            if (RANK[bot->Deck[index][i].first] > RANK[atac_card.first]
                && bot->Deck[index][i].second == atac_card.second){

                defending_cards.push_back(bot->Deck[index][i]);
                bot->Deck[index].erase(bot->Deck[index].begin() + i);
                return 2;
            }
        }
        // если атакуещая карта козырь, тогда забераем
        if (trump_card == atac_card.second) return 0;
        

        for (int i = 0; i < bot->Deck[index].size(); i++) {
            //pair <string, string> atac_card = attacking_cards[attacking_cards.size() - 1];
            // проверяет есть ли карта козырь
            if (bot->Deck[index][i].second == trump_card) {

                defending_cards.push_back(bot->Deck[index][i]);
                bot->Deck[index].erase(bot->Deck[index].begin() + i);
                return 2;
            }
        }
        return 0;
    }
    
    //takes the cards
    void takesCards(Bots* bot) {
        if (bot->Deck[index_move].size() != 0) {
            for (int i = bot->Deck[index_move].size(); i < 6; i++) {
                if (Deck.size() == 0) break;
                bot->Deck[index_move].push_back(Deck[0]);
                Deck.erase(Deck.begin());
            }
        }
        if (index_move == count_p) index_move = -1;
        //cout << "index_move: " << index_move << endl;
        for (pair <string, string> card : attacking_cards) {
            bot->Deck[index_move+1].push_back(attacking_cards[0]);
            attacking_cards.erase(attacking_cards.begin());
        }
        for (pair <string, string> card : defending_cards) {
            bot->Deck[index_move+1].push_back(defending_cards[0]);
            defending_cards.erase(defending_cards.begin());
        }
    }

    //cards to the fool
    void bitaCards(Bots* bot) {
        for (pair <string, string> card: attacking_cards) {
            attacking_cards.erase(attacking_cards.begin());
        }
        for (pair <string, string> card : defending_cards) {
            defending_cards.erase(defending_cards.begin());
        }
        //если нет карт в колоде 
        if (Deck.size() != 0  && bot->Deck[index_move].size() != 0) {
            for (int i = bot->Deck[index_move].size(); i < 6; i++) {
                if (Deck.size() == 0) break;
                bot->Deck[index_move].push_back(Deck[0]);
                Deck.erase(Deck.begin());
            }
            //проверка на наличие карт 
            if (bot->Deck[index_move].size() == 0) {
                cout << endl;
                cout << index_move;
                bot->DeletePlayer(index_move);
                if (index_move == count_p) index_move = -1;
                count_p -= 1;
            }
            if (index_move == count_p) index_move = -1;
            //cout << "index_move: " << index_move << endl;
            for (int i = bot->Deck[index_move+1].size(); i < 6; i++) {
                if (Deck.size() == 0) break;
                bot->Deck[index_move +1].push_back(Deck[0]);
                Deck.erase(Deck.begin());
            }
        }

        if (index_move == count_p) index_move = -1;
        if (bot->Deck[index_move +1].size() == 0)
        {
            if (index_move == 1 && bot->Deck.size() == 1) {
                count_p -= 1;
            }
            else {
                cout << endl;
                bot->DeletePlayer(index_move + 1); count_p -= 1;
            }
        }

    }
    
    //Atac bot
    int AtacBot(Bots* bot) {
        if (bot->Deck[index_move].size() == 0) {
            cout << endl;
            cout << index_move;
            bot->DeletePlayer(index_move);
            count_p -= 1;
            return 6;
        }
        if (attacking_cards.empty() && defending_cards.empty()) {
            attacking_cards.push_back(bot->Deck[index_move][0]);
            bot->Deck[index_move].erase(bot->Deck[index_move].begin());
            return 2;
        }
        for (pair <string, string> card : attacking_cards) {
            for (int i = 0; i < bot->Deck[index_move].size(); i++) {
                if (bot->Deck[index_move][i].first == card.first) {
                    attacking_cards.push_back(bot->Deck[index_move][i]);
                    bot->Deck[index_move].erase(bot->Deck[index_move].begin() + i);
                    return 2;
                }
            }
        }
        for (pair <string, string> card : defending_cards) {
            for (int i = 0; i < bot->Deck[index_move].size(); i++) {
                if (bot->Deck[index_move][i].first == card.first) {
                    attacking_cards.push_back(bot->Deck[index_move][i]);
                    bot->Deck[index_move].erase(bot->Deck[index_move].begin() + i);
                    return 2;
                }
            }
        }
        return 6;
    }
    
    //Define player
    int DefinPlayer(int index, Bots* bot) {
        pair <string, string> atac_card = attacking_cards[attacking_cards.size() - 1];
        // checks whether there is a card of the same suit, but with a higher denomination
        if (RANK[bot->Deck[0][index].first] > RANK[atac_card.first]
            && bot->Deck[0][index].second == atac_card.second) {
            defending_cards.push_back(bot->Deck[0][index]);
            bot->Deck[0].erase(bot->Deck[0].begin() + index);
            return 2;
        }

        // if the attacking card is a trump card and has a high value
        if (trump_card == atac_card.second) return 6;
        // checks whether there is a trump card
        if (bot->Deck[0][index].second == trump_card) {

            defending_cards.push_back(bot->Deck[0][index]);
            bot->Deck[0].erase(bot->Deck[0].begin() + index);
            return 2;
        }

        return 6;
    }

    //Player tossing cards
    int playerTossing(Bots* bot){
        int check;
        do {
            cout << "-------------------------------------------------------------------" << endl;
            while (true) {

                tablePrint(*bot);
                cout << "Which card would you like to throw by index: ";
                if ((cin >> check)) {
                    if (bot->Deck[0].size() > check && check >= 0) {
                        break;
                    }
                    else if (check == 88) {
                        return 0;
                    }
                    else {
                        cout << "index in out of input range" << endl;
                    }
                }
                else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Input Error. Please enter an integer." << endl;
                }
            }

            for (pair <string, string> card : attacking_cards) {
                for (int i = 0; i < bot->Deck[0].size(); i++) {
                    if (bot->Deck[0][check].first == card.first) {
                        attacking_cards.push_back(bot->Deck[0][check]);
                        bot->Deck[0].erase(bot->Deck[0].begin() + check);
                        break;
                    }
                }
            }

            for (pair <string, string> card : defending_cards) {
                for (int i = 0; i < bot->Deck[0].size(); i++) {
                    if (bot->Deck[0][check].first == card.first) {
                        attacking_cards.push_back(bot->Deck[0][check]);
                        bot->Deck[0].erase(bot->Deck[0].begin() + check);
                        break;
                    }
                }
            }

            cout << "You can't flip this card" << endl;
            cout << "-------------------------------------------------------------------" << endl;

        } while (true);
    }
};

void historyGame(int cout_p, string result) {
    ofstream fout;

    fout.open(path, ofstream::app);
    cout << endl;
    if (!fout.is_open()) {
        cout << "Some error has occurred" << endl;
        cout << endl;
    }
    else {
        fout << "\nplayer who played against " << cout_p << " bot(s) - " << result << "\n";
        fout.close();
    }
}

void ViewHistoyeGame() {
    ifstream fin;
    fin.open(path);

    if (!fin.is_open()) {
        cout << endl;
        cout << "game history not found" << endl;
    }
    else {
        int check;

        while (true) {
            cout << "Would you like to see the history of games? (1 - yes / 0 - no)?" << endl;
            if ((cin >> check)) {
                if (check == 1) {
                    int check_w = 0;
                    int check_l = 0;

                    cout << endl;
                    cout << "History game: " << endl;
                    string str;
                    string word;
                    while (!fin.eof()) {
                        str = "";
                        cout << endl;
                        getline(fin, str);
                        cout << str << endl;
                        cout << endl;
                        istringstream iss(str);
                        while (iss >> word) {
                            if (word == "Win") {
                                check_w++;
                                break;
                            }
                            if (word == "Loser") {
                                check_l++;
                                break;
                            }
                        }
                    }
                    cout << endl;
                    cout << "From " << check_l + check_w << " game you have so many victories: " << check_w << endl;
                    fin.close();
                    break;
                }
                else if (check == 0) {
                    break;
                }
                else {
                    cout << "Input Error. Please enter an integer." << endl;

                }
            }
            else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Input Error. Please enter an integer." << endl;
            }
        }

    }

}

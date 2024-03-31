#include <iostream>
#include <vector>
#include <random>

const int MIN_BOARD_SIZE = 5;
const int MAX_BOARD_SIZE = 10;
const int MIN_NUM_SHIPS = 3;

void initializeBoard(std::vector<std::vector<char>>& board, int size) {
    // Inicjalizacja planszy pustymi polami
    for (int i = 0; i < size; ++i) {
        std::vector<char> row;
        for (int j = 0; j < size; ++j) {
            row.push_back('.');
        }
        board.push_back(row);
    }
}

void printBoard(const std::vector<std::vector<char>>& board, bool showShips) {
    // Wyświetlenie planszy
    std::cout << " ";
    for (size_t i = 0; i < board.size(); ++i) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    for (size_t i = 0; i < board.size(); ++i) {
        std::cout << i << " ";
        for (size_t j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == 'S' && !showShips) {
                std::cout << '.' << " ";
            }
            else {
                std::cout << board[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
}

void placeShips(std::vector<std::vector<char>>& board, int numShips) {
    // Umieszczenie statków na planszy
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, board.size() - 1);

    int shipsPlaced = 0;
    while (shipsPlaced < numShips) {
        int row = dis(gen);
        int col = dis(gen);
        if (board[row][col] != 'S') {
            board[row][col] = 'S';
            shipsPlaced++;
        }
    }
}

bool isValidInput(const std::vector<std::vector<char>>& board, int row, int col) {
    // Sprawdzenie, czy wprowadzone współrzędne są prawidłowe
    return row >= 0 && row < board.size() && col >= 0 && col < board.size();
}

bool isHit(std::vector<std::vector<char>>& board, int row, int col) {
    // Sprawdzenie, czy trafiono statek
    if (board[row][col] == 'S') {
        board[row][col] = 'X'; // Oznacz trafienie na planszy
        return true;
    }
    return false;
}

bool allShipsSunk(const std::vector<std::vector<char>>& board) {
    // Sprawdzenie, czy pozostały jeszcze statki do trafienia
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == 'S') {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int boardSize;
    int maxAttempts = 0;
    std::cout << "Podaj rozmiar planszy (" << MIN_BOARD_SIZE << "-" << MAX_BOARD_SIZE << "): ";
    std::cin >> boardSize;
    if (boardSize < MIN_BOARD_SIZE || boardSize > MAX_BOARD_SIZE) {
        std::cerr << "Nieprawidlowy rozmiar planszy!\n";
        return 1;
    }

    maxAttempts = (boardSize * boardSize) - boardSize;

    int numShips = std::max(MIN_NUM_SHIPS, boardSize / 2);

    std::vector<std::vector<char>> board;
    initializeBoard(board, boardSize);
    placeShips(board, numShips);

    std::cout << "Witaj w grze w statki!\n";

    int attempts = 0;
    while (true) {
        std::cout << "Plansza:\n";
        printBoard(board, false); // Nie pokazuj statków

        int row, col;
        std::cout << "Podaj wiersz (0-" << boardSize - 1 << "): ";
        std::cin >> row;
        std::cout << "Podaj kolumne (0-" << boardSize - 1 << "): ";
        std::cin >> col;

        if (!isValidInput(board, row, col)) {
            std::cout << "Nieprawidlowe wspolrzedne!\n";
            continue;
        }

        if (board[row][col] == '*' || board[row][col] == 'X') {
            std::cout << "Juz strzelałes w to miejsce!\n";
            continue;
        }

        if (isHit(board, row, col)) {
            std::cout << "Trafiony!\n";
        }
        else {
            std::cout << "Pudlo!\n";
            board[row][col] = '*';
        }

        attempts++;
        if (allShipsSunk(board)) {
            printBoard(board, true);
            std::cout << "Gratulacje! Zatopiles wszystkie statki!\n";
            break;
        }
        else if (attempts >= maxAttempts) {
            printBoard(board, true);
            std::cout << "Koniec gry! Nie udalo się zatopic wszystkich statkow.\n";
            break;
        }
    }



    return 0;
}

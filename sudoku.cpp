#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 9;

// Functie de imprimare sudoku
void printGrid(vector<vector<int>>& grid) {
    for (int rand = 0; rand < N; rand++) {
        for (int coloana = 0; coloana < N; coloana++)
            cout << grid[rand][coloana] << " ";
        cout << endl;
    }
}

// Functie pentru a verifica daca un valoarear poate fi plasat intr-o celula
bool isSafe(vector<vector<int>>& grid, int rand, int coloana, int valoare) {
    // Verificati daca valoarearul nu este deja prezent in rand sau coloanaoana
    for (int x = 0; x < N; x++)
        if (grid[rand][x] == valoare || grid[x][coloana] == valoare)
            return false;

    // Verificati daca valoarearul nu este deja prezent in grila curenta 3*3
    int startrand = rand - rand % 3;
    int startcoloana = coloana - coloana % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startrand][j + startcoloana] == valoare)
                return false;

    return true;
}

// Functia genereaza un puzzle aleatoriu
void generateSudoku(vector<vector<int>>& grid) {
    srand(time(0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (rand() % 4 == 0) // Se vor umple aleatoriu 25% din celule
                grid[i][j] = rand() % N + 1;
            else
                grid[i][j] = 0; // Celulele ramase se vor umple cu 0
        }
    }
}

// Functia pentru a rezolva puzzelul, folosind metoda backtrack ing
bool solveSudoku(vector<vector<int>>& grid) {
    int rand, coloana;

    // Gasirea unei celule goale
    bool isEmpty = false;
    for (rand = 0; rand < N; rand++) {
        for (coloana = 0; coloana < N; coloana++) {
            if (grid[rand][coloana] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty)
            break;
    }

    // Daca nu se gasesc celule goale, puzzelul este rezolvat
    if (!isEmpty)
        return true;

    // Se vor plasa valoareere de la 1 la 9 in celulele goale (0)
    for (int valoare = 1; valoare <= N; valoare++) {
        if (isSafe(grid, rand, coloana, valoare)) {
            // valoarearul se va seta daca pozitia lui este sigura
            grid[rand][coloana] = valoare;

            // Rezolvati recursiv restul puzzel
            if (solveSudoku(grid))
                return true;

            // Daca valoarearul plasat nu duce la o solutie valida, se revine
            grid[rand][coloana] = 0;
        }
    }

    // Daca nu se poate plasa un valoarear in celula respectiva, puzzle ul este imposibil de rezolvat
    return false;
}

int main() {
    vector<vector<int>> sudokuGrid(N, vector<int>(N, 0));

    generateSudoku(sudokuGrid);

    cout << "Generare aleatorie de Oussle Sudoku:" << endl;
    printGrid(sudokuGrid);
    cout << endl;

    cout << "Introduceti solutia Dvs pentru pussle (rand, coloanaoana, valoare):" << endl;
    cout << "Exemplu: 0 0 5 (valoarearul 5 o sa fie plasat in prima celula)" << endl;
    cout << "Introduceti valoarea -1 pentru avaloareare joc." << endl;

    while (true) {
        int rand, coloana, valoare;
        cout << "Specificati miscarea: ";
        cin >> rand >> coloana >> valoare;

        if (rand == -1 || coloana == -1 || valoare == -1)
            break;

        if (rand < 0 || rand >= N || coloana < 0 || coloana >= N || valoare < 1 || valoare > 9) {
            cout << "Miscare imposibila! Reincercati!" << endl;
            continue;
        }

        if (sudokuGrid[rand][coloana] != 0) {
            cout << "Celula este deja plina! Reincercati" << endl;
            continue;
        }

        if (!isSafe(sudokuGrid, rand, coloana, valoare)) {
            cout << "Miscare invalida! Valoarea intentionata nu poate sa fie plasata in celula, conform regulilor jocului. Reincercati." << endl;
            continue;
        }

        sudokuGrid[rand][coloana] = valoare;
        cout << "Updated Sudoku puzzle:" << endl;
        printGrid(sudokuGrid);
        cout << endl;

        if (solveSudoku(sudokuGrid)) {
            cout << "Bravo bursuc! Se vede ca esti la mate info!" << endl;
            break;
        }

        cout << "Continua..." << endl;
    }

    return 0;
}
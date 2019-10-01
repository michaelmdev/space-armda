#include <iostream>

using namespace std;

struct Ship {
    int speed, cargo, power;
};

// декларация, реализация ниже
void recursive(int n, const bool available_indexes[], Ship request[], Ship ship[]);

bool is_acceptable(Ship req, Ship ship);

// вносим переменные в область видимости класса, пока нет класса значит будут глобальными
static int ships_size = 0;
static int request_size = 0;
static bool ok = false;

//const int MAX_REQ = 100;
//const int MAX_SHIPS = 100;

// легкий оверкилл по памяти зато простой синтакс
// typedef bool Array[MAX_REQ][MAX_SHIPS];
// глобальная переменная
// static Array matrix;

// индексы на выходе из рекурсии
static bool *result;

int main() {
    cin >> ships_size;
    Ship ship[ships_size];
    for (int i = 0; i < ships_size; ++i) {
        cin >> ship[i].speed >> ship[i].cargo >> ship[i].power;
    }

    cin >> request_size;
    Ship request[request_size];
    for (int i = 0; i < request_size; i++) {
        cin >> request[i].speed >> request[i].cargo >> request[i].power;
    }

    // Multidimensional arrays are evil in C++ :((
    // http://www.cplusplus.com/forum/articles/17108/
    // bool matrix[request_size][ships_size];

    // very very bad approach
    // https://www.dyclassroom.com/c/c-pointers-and-two-dimensional-array
    // m = &matrix[0][0];

    /*
    // заполняем матрицу в один проход используя неявное приведение типов bool -> int
    for (int i = 0; i < request_size; ++i) {
        for (int j = 0; j < ships_size; ++j) {
            matrix[i][j] = request[i].speed <= ship[j].speed && request[i].cargo <= ship[j].cargo && request[i].power <= ship[j].power;
        }
    }

    // отладка - вывод матриц совпадений желаемого и возможного
    for (int i = 0; i < request_size; i++) {
        for (int j = 0; j < ships_size; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
     */

    // выбиваем false-ами
    bool available[ships_size];
    for (int i = 0; i < ships_size; i++) available[i] = true;

    // резервируем память ибо копия имеющаяся в рекурсии будет грохнута по выходе из ней
    bool res[ships_size];
    result = res;

    recursive(-1, available, request, ship);

    if (ok) {
        // debug
        for (int i = 0; i < ships_size; i++)
            cout << result[i] << ' ';
        cout << '\n';

        // REAL RESULT
        for (int i = 0; i < ships_size; i++)
            if(!result[i])
                cout << i << '\n';

    } else {
        cout << -1;
    }

    return 0;
}

void recursive(int n, const bool available[], Ship request[], Ship ship[]) {
    if (ok) return;

    // инкрементируем индекс и проверяем достижение границы
    if (++n >= request_size) {
        ok = true;
        // копируем результат в заранее подготовленное место, ибо по выходе из метода этот массив грохнут
        for (int i = 0; i < ships_size; ++i) {
            result[i] = available[i];
        }
    }

    // копаем пока нет успеха, возможно успех был достигнут иной веткой
    if (!ok) {
        for (int i = 0; i < ships_size; i++) {
            if (/*matrix[n][i]*/ is_acceptable(request[n], ship[i]) && available[i]) {

                // копируем кроме одного элемента, который "метим"
                bool use_it[ships_size];
                for (int j = 0; j < ships_size; ++j) {
                    use_it[j] = (i != j) ? available[j] : false;
                }

                recursive(n, use_it, request, ship);
            }
        }
    }
}

bool is_acceptable(Ship req, Ship ship) {
    return req.speed <= ship.speed && req.cargo <= ship.cargo && req.power <= ship.power;;
}


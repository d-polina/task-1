// Создать класс, описывающий одномерный массив.
// Определить, упорядочен ли массив, и направление упорядоченности (во возрастанию / убыванию)
// Создать класс-наследник, описывающий двумерную прямоугольную матрицу. 
// Определить номер первой (если считать от строки с индексом 0), 
// упорядоченной в заданном направлении (возрастание/убывание) строки.

#include <iostream>
using namespace std;

class Check {
    private:
        unsigned int i;
    public:
        Check(){
        }

        int InputCheck(string s, int flag){
            cin >> s;
            if (flag == 0) {
                if (s.length() == 1 and ((s == "1") or (s == "2"))) {
                    return stoi(s);
                } else {
                    cout << "Некорректный ввод\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } else if (flag == 1) {
                for (i = 0; s[i] != '\0'; i++) {
                    if (!(isdigit(s[i]))) {
                        cout << "Некорректный ввод\n";
                        return 0;
                    }
                }
                return stoi(s);
            }
            return 0;
        }
};

class Array{
    protected:
        int size; 
        int *a;
    public:
        Array(int s) {
            size = s;
            a = new int[size];
        }
        ~Array(){
            delete[] a;
        }

        void set(int i, int val) {
            if (i >= 0 && i < size) {
                a[i] = val;
            }
        }
        void print(){
            for(int i = 0; i < size; i++) {
                cout << a[i] << " ";
            }
            cout << endl;
        }
        
        string isOrder(int a[], int size){
            int equal, greater, less;
            equal = greater = less = 0;
            for (int i = 0; i < size - 1; i++) {
                if (a[i] == a[i + 1]) {
                    equal++;
                }
                if (a[i] < a[i + 1]) {
                    greater++;
                }
                if (a[i] > a[i + 1]) {
                    less++;
                }
            }
            if (equal == (size - 1)) {
                return "\nВсе элементы одинаковы\n";
            } else if (greater == (size - 1)) {
                return "\nУпорядочен по возрастанию\n";
            } else if (less == (size - 1)) {
                return "\nУпорядчен по убыванию\n";
            } else {
                return "\nНикак не упорядочен\n";
            }
        }

        void checkOrder() {
            string order = isOrder(a, size);
            cout << order << endl;
        }
};

class Matrix : public Array {
    protected:
        int row;
        int col;
        int **m;

    public:
        Matrix(int r, int c) : Array (r+c) {
            row = r;
            col = c;
            m = new int *[row];
            for (int i = 0; i < row; i++) {
                m[i] = new int[col];
            }
        }
        
        void set(int i, int j, int val) {
            if (i >= 0 && i < row) {
                if (j >= 0 && j < col) {
                    m[i][j] = val;
                }
            }
        }
        void print() {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                cout << m[i][j] << " ";
                }
                cout << endl;
            }
        }

        void checkOrder() {
            int increasingRow = -1;
            int decreadingRow = -1;
            
            for (int i = 0; i < row; i++) {
                string order = isOrder(m[i], col);
                if (order == "\nУпорядочен по возрастанию\n") {
                    increasingRow = i;
                    cout << "\nПервая упорядоченная по возрастанию строка: " << increasingRow + 1 << "\n" << endl;
                    break;
                }
            }
            for (int i = 0; i < row; i++) { 
                string order = isOrder(m[i], col);
                if (order == "\nУпорядчен по убыванию\n") {
                    decreadingRow = i;
                    cout << "\nПервая упорядоченная по убыванию строка: " << decreadingRow + 1 << "\n" << endl;
                    break;
                }
            }
            if (increasingRow == -1) {
                cout << "\nНет упорядоченных по возрастанию строк\n" << endl;
            }

            if (decreadingRow == -1) {
                cout << "Нет упорядоченных по убыванию строк\n" << endl;
            }
        }
        ~Matrix(){
            for (int i = 0; i < row; i++){
                delete[] m[i];
            }
            delete[] m;
        }
};



int main() {

    cout << "\nВыберите опцию:" << endl;
    cout << "\t1) Одномерный массив" << endl;
    cout << "\t2) Двумерная матрица" << endl;

    string option, str;
    int optionNumber, flag;
    Check ch1;
    optionNumber = ch1.InputCheck(option, flag = 0);

    switch (optionNumber) {
        case 1:
        {
            cout << "\nВы выбрали одномерный массив\n" << endl;

            cout << "Введите кол-во элементов массива: \n";
            int size;
            size = ch1.InputCheck(str, flag = 1);

            if (size > 0) {
            Array array1(size);

            cout << "Введите элементы массива: \n";
            for (int i = 0; i < size; i++) {
                int value;
                value = ch1.InputCheck(str, flag = 1);
                array1.set(i, value); 
            }
            cout << "Одномерный массив: ";
            array1.print();

            array1.checkOrder();
            break;

            } else {
                return 0;
            }
        }
        case 2:
        {
            cout << "\nВы выбрали двумерную матрицу\n" << endl;

            cout << "Для двумерной матрицы введите число строк и столбцов: \n";
            int rows, cols;
            rows = ch1.InputCheck(str, flag = 1);
            cols = ch1.InputCheck(str, flag = 1);
            cout << "Строк " << rows << " и cтолбцов " << cols << endl;

            Matrix matrix1(rows, cols);
            cout << "Введите элементы двумерной матрицы (их должно быть " << rows*cols << "): " << endl;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    int value;
                    value = ch1.InputCheck(str, flag = 1);
                    matrix1.set(i, j, value); 
                }
            }
            cout << "Двумерная матрица:" << endl;
            matrix1.print();
            matrix1.checkOrder();
            break;
        }
        default:
            cout << "Неверная опция" << endl;
        
    }
    return 0;

}

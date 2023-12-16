//2+73*(32/9)-5=


#include <iostream>
#include <vector>
#include <string>

// Функция для проверки корректности расстановки скобок в выражении
bool checkBrackets(std::vector<char>& str)
{
    int cnt = 0;
    // Проходим по символам выражения и подсчитываем количество открывающих и закрывающих скобок
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '(') { cnt += 1; }
        else if (str[i] == ')') { cnt -= 1; }
        // Если встретилась закрывающая скобка без предшествующей открывающей, выходим из цикла
        if (cnt == -1) { break; }
    }
    // Проверяем, что количество открывающих и закрывающих скобок совпадает
    // и что последний символ выражения - знак равенства '='
    if (cnt != 0 or str[str.size() - 1] != '=') { return false; }
    return true;
}

// Функция для проверки принадлежности символа алфавиту
bool inalphabet(std::vector<char>& alphabet, char symbol)
{
    for (int i = 0; i < alphabet.size(); i++)
    {
        if (alphabet[i] == symbol) { return true; }
    }
    return false;
}

// Функция, возвращающая приоритет оператора
int prior(char operand)
{
    int out = 0;
    switch (operand)
    {
    case 43:   // '+'
        out = 1;
        break;
    case 45:   // '-'
        out = 1;
        break;
    case 42:   // '*'
        out = 2;
        break;
    case 47:   // '/'
        out = 2;
        break;
    }
    return out;
}

int main() {
    // Создаем вектор символов для операторов и скобок
    std::vector<char> signlist{ '+', '-', '=', '*', '/', '(', ')' };
    // Создаем вектор символов для цифр
    std::vector<char> numberlist{ '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
    // Создаем вектор, в который будем сохранять символы из введенной строки
    std::vector<char> list;

    // Запрашиваем ввод строки у пользователя
    std::string s;
    std::cout << "Enter str: ";
    std::cin >> s;
    std::cout << std::endl;
    std::string tempNumber{};  // Временная строка для сохранения чисел

    // Проходим по каждому символу введенной строки
    for (int i = 0; i < s.size(); i++)
    {
        // Проверяем, если два оператора идут подряд, и они не являются открывающейся и закрывающейся скобкой
        if (i > 0 and inalphabet(signlist, s[i]) and inalphabet(signlist, s[i - 1]))
        {
            if (not(s[i] == '(' or s[i - 1] == ')'))
            {
                std::cout << "Ошибка: два знака подряд" << std::endl;
                return -11111;
            }
        }

        // Проверяем деление на ноль
        if (i > 0 and s[i - 1] == '/' and s[i] == '0')
        {
            std::cout << "Ошибка: деление на ноль" << std::endl;
            return -11111;
        }

        // Проверяем, что символ является допустимым оператором или цифрой
        if (not(inalphabet(signlist, s[i]) or inalphabet(numberlist, s[i])))
        {
            std::cout << "Ошибка: некорректный символ" << std::endl;
            return -11111;
        }

        // Если символ - оператор, обрабатываем предыдущее число и добавляем оператор в список
        if (inalphabet(signlist, s[i]))
        {
            if (tempNumber.size() != 0)
            {
                int tint = std::atoi(tempNumber.c_str());
                list.push_back((char)tint);
                tempNumber.clear(); // Очищаем tempNumber для следующего числа
            }
            list.push_back(s[i]);
        }

        // Если символ - цифра, добавляем его во временную строку
        if (inalphabet(numberlist, s[i])) { tempNumber.push_back(s[i]); }
    }

    // Проверяем корректность расстановки скобок
    if (not checkBrackets(list))
    {
        std::cout << "Ошибка: ()" << std::endl;
        return -11111;
    }

// Создаем вектор чисел и инициализируем переменные для работы со стеками чисел и знаков
std::vector<float> numbersQ;
int numberQtop = -1;

std::vector<char> signQ;
int signQtop = -1;
int countskob = 0;

// Проходим по списку символов, сформированному на предыдущем этапе
for (int i = 0; i < list.size() - 1; i++)
{
    // Если текущий символ - число, добавляем его в стек чисел
    if (not inalphabet(signlist, list[i]))
    {
        numbersQ.push_back(float(list[i]));
        numberQtop += 1;
    }
    else
    {
        // Если символ - открывающая скобка или стек знаков пуст, добавляем его в стек знаков
        if (list[i] == '(' or signQtop == -1)
        {
            signQ.push_back(list[i]);
            signQtop += 1;
            // Если это открывающая скобка, увеличиваем счетчик скобок
            if (list[i] == '(')
            {
                countskob += 1;
            }
        }
        else
        {
            // Если приоритет текущего оператора больше, чем приоритет оператора в вершине стека,
            // или если вершина стека - открывающая скобка, добавляем текущий оператор в стек знаков
            if (signQ[signQtop] == '(' or (signQ[signQtop] != '(' and list[i] != ')' and (prior(list[i]) > prior(signQ[signQtop]))))
            {
                signQ.push_back(list[i]);
                signQtop += 1;
            }
            // Если текущий символ - закрывающая скобка, выполняем вычисления до открывающей скобки
            else if (list[i] == ')')
            {
                while (signQ[signQtop] != '(')
                {
                    // Находим открывающую скобку в стеке
                    int pointer;
                    for (int p = signQ.size() - 1; p >= 0; p--)
                    {
                        if (signQ[p] == '(')
                        {
                            pointer = p;
                            break;
                        }
                    }

                    // Находим оператор с максимальным приоритетом после открывающей скобки
                    int maxPrior = 0;
                    for (int k = pointer + 1; k < signQ.size(); k++)
                    {
                        if (prior(signQ[k - 1]) <= prior(signQ[k]))
                        {
                            maxPrior = k;
                        }
                    }

                    // Выполняем операцию с числами и оператором максимального приоритета
                    float temp1 = numbersQ[maxPrior - countskob];
                    float temp2 = numbersQ[maxPrior + 1 - countskob];
                    float tempout;
                    numbersQ.erase(numbersQ.begin() + (maxPrior - countskob));
                    numbersQ.erase(numbersQ.begin() + (maxPrior - countskob));
                    switch (signQ[maxPrior])
                    {
                    case 43:  // +
                        tempout = temp1 + temp2;
                        break;
                    case 45:  // -
                        tempout = temp1 - temp2;
                        break;
                    case 42:  // *
                        tempout = temp1 * temp2;
                        break;
                    case 47:  // деление
                        // Проверка деления на ноль
                        if (temp2 == 0)
                        {
                            std::cout << "Ошибка: деление на ноль!!!!!" << std::endl;
                            return -11111;
                        }
                        tempout = temp1 / temp2;
                        break;
                    }
                    numbersQ.insert(numbersQ.begin() + (maxPrior - countskob), tempout);
                    numberQtop -= 1;
                    signQtop -= 1;
                    signQ.erase(signQ.begin() + (maxPrior));
                }

                // Удаляем открывающую скобку из стека знаков
                signQ.pop_back();

                // Уменьшаем счетчик скобок
                countskob -= 1;
                signQtop -= 1;
            }
            // Если приоритет текущего оператора меньше или равен приоритету оператора в вершине стека,
                // выполняем вычисления с числами и операторами в стеке
            else
            {
                float temp1 = numbersQ[numberQtop - 1];
                float temp2 = numbersQ[numberQtop];
                float tempout;
                numbersQ.pop_back();
                numbersQ.pop_back();
                switch (signQ[signQtop])
                {
                case 43:  // '+'
                    tempout = temp1 + temp2;
                    break;
                case 45:  // '-'
                    tempout = temp1 - temp2;
                    break;
                case 42:  // '*'
                    tempout = temp1 * temp2;
                    break;
                case 47:  // '/'
                    // Проверка деления на ноль
                    if (temp2 == 0)
                    {
                        std::cout << "Ошибка: деление на ноль!!!!!" << std::endl;
                        return -11111;
                    }
                    tempout = temp1 / temp2;
                    break;
                }
                // Добавляем результат вычислений в стек чисел
                numbersQ.push_back(tempout);
                numberQtop -= 1;

                // Заменяем оператор в вершине стека на текущий оператор
                signQ[signQtop] = list[i];
            }
        }
    }
}
// Пока в стеке чисел не останется одно число (результат выражения)
while (numberQtop != 0)
{
    // Находим оператор с максимальным приоритетом в стеке знаков
    int maxPrior = 0;
    for (int i = 1; i < signQ.size(); i++)
    {
        if (prior(signQ[i - 1]) <= prior(signQ[i]))
        {
            maxPrior = i;
        }
    }

    // Получаем два числа для выполнения операции
    float temp1 = numbersQ[maxPrior];
    float temp2 = numbersQ[maxPrior + 1];
    float tempout;

    // Удаляем числа из стека чисел
    numbersQ.erase(numbersQ.begin() + (maxPrior + 1));
    numbersQ.erase(numbersQ.begin() + maxPrior);

    // Выполняем операцию в соответствии с оператором
    switch (signQ[maxPrior])
    {
    case 43:  // '+'
        tempout = temp1 + temp2;
        break;
    case 45:  // '-'
        tempout = temp1 - temp2;
        break;
    case 42:  // '*'
        tempout = temp1 * temp2;
        break;
    case 47:  // '/'
        // Проверка деления на ноль
        if (temp2 == 0)
        {
            std::cout << "Ошибка: деление на ноль!!!!!" << std::endl;
            return -11111;
        }
        tempout = temp1 / temp2;
        break;
    }

    // Вставляем результат операции в стек чисел
    numbersQ.insert(numbersQ.begin() + maxPrior, tempout);

    // Уменьшаем счетчик чисел и знаков в стеке
    numberQtop -= 1;
    signQtop -= 1;

    // Удаляем использованный оператор из стека знаков
    signQ.erase(signQ.begin() + maxPrior);
}

// Выводим ответ
std::cout << "Ответ: " << numbersQ[0];
return 0;
}

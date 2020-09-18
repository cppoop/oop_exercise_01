/**
 * Почаев Михаил
 * на github: cppoop
 * Создать класс Bottle для работы с емкостями. Класс должен состоять из двух вещественных чисел: 
 * a- объем емкости в литрах и b – процент наполнения емкости (0 – пустая, 1 – полная). 
 * Реализовать операции сложения и вычитания, а также сравнения объектов класса бутылка. 
 *  При сложении должен складываться фактический объем заполнения бутылок.
 * */


// main.cpp: определяет точку входа для приложения.
//

#include "main.h"

using namespace std;

// границы значений a и b 
const double maxA = 100.0;
const double minA = 0.25;
const double maxB = 1.0;
const double minB = 0.0;

/// <summary>
/// Класс для работы с ёмкостями
/// </summary>
class Bottle
{
public:
    // конструктор по умолчанию
    Bottle() { this->a = minA; this->b = minB; };
    // конструктор с параметрами
    Bottle(double a, double b);
    // геттер для A
    double GetA() { return a; }
    // геттер для B
    double GetB() { return b; }
    // сложение
    Bottle* operator+ (const Bottle& b);
    // вычитание
    Bottle* operator- (const Bottle& b);
    // операторы сравнения
    friend bool operator== (const Bottle& b1, const Bottle& b2);
    friend bool operator!= (const Bottle& b1, const Bottle& b2);
private:
    double a;   // объём ёмкости в литрах
    double b;   // процент наполнения емкости(0 – пустая, 1 – полная).
};

Bottle::Bottle(double a, double b)
{
    // проверяем выход переменных за логический диапозон
    // объём бутылки от 0.25 до 100 литров, процент наполнения от 0 до 1
    if (a > maxA)
    {
        this->a = maxA;
        cout << "WARNING: the volume of bottle is too large, it was reduced to 100" << endl;
    }
    else if (a < minA)
    {
        this->a = minA;
        cout << "WARNING: the volume of bottle is too small, it was reduced to 0.25" << endl;
    }
    else
    {
        this->a = a;
    }

    if (b > maxB)
    {
        this->b = maxB;
        cout << "WARNING: the volume of bottle is too large, it was reduced to 1" << endl;
    }
    else if (b < minB)
    {
        this->b = minB;
        cout << "WARNING: the volume of bottle is too small, it was reduced to 0" << endl;
    }
    else
    {
        this->b = b;
    }
}

Bottle* Bottle::operator+ (const Bottle& b)
{
    // фактические объёмы заполнения
    double v1 = this->a * this->b;
    double v2 = b.a * b.b;

    double totalV = v1 + v2;

    // если суммарный объем превышает maxA
    if (totalV > maxA)
    {
        cout << "WARNING: the maximum volume of bottle is exceeded by "
            << totalV - maxA << " liters" << endl;

        return new Bottle(maxA, maxB);
    }

    return new Bottle(totalV, maxB);
}

Bottle* Bottle::operator- (const Bottle& b)
{
    // фактические объёмы заполнения
    double v1 = this->a * this->b;
    double v2 = b.a * b.b;

    double substractV;

    if (v1 > v2)
    {
        substractV = v1 - v2;
    }
    else if (v2 > v1)
    {
        substractV = v2 - v1;
    }
    else
    {
        substractV = 0;
        return new Bottle(substractV, minB);
    }

    return new Bottle(substractV, maxB);
}

bool operator== (const Bottle& b1, const Bottle& b2)
{
    return (b1.a == b2.a && b1.b == b2.b);
}

bool operator != (const Bottle& b1, const Bottle& b2)
{
    return !(b1 == b2);
}

int main()
{
    // тестирование
    double a1, b1, a2, b2;

    cout << "Please input a and b parameters of the bottle 1 and 2 (separated spaces): ";
    cin >> a1 >> b1 >> a2 >> b2;

    Bottle bottle1(a1, b1);
    Bottle bottle2(a2, b2);
    // указатель на результирующий объект для сложения и вычитания
    Bottle* result;

    // тест сложения
    result = bottle1 + bottle2;
    cout << "sum result: " << result->GetA() << " " << result->GetB() << endl;
    // нужно удалить объект по указателю, после использования, так как он возвращается через new
    delete result;

    // тест вычитания
    result = bottle1 - bottle2;
    cout << "sub result: " << result->GetA() << " " << result->GetB() << endl;
    delete result;

    // тест сравнения
    cout << "eq result: " << (bottle1 == bottle2) << endl;

    system("pause");
    return 0;
}


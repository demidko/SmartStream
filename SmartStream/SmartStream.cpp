#include "SmartStream.h"
#include <Windows.h>
#include <iostream>

namespace
{
    // Вспомогательная функция определяет что курсор находится в самом начале строки
    bool IsNewLine()
    {
        CONSOLE_SCREEN_BUFFER_INFO res;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &res);
        return res.dwCursorPosition.X == 0;
    }

    // Универсальные ввод и вывод - их нельзя делать операторами, 
    // т к тогда пользователь не сможет переопределить ввод (вывод) для своих сущностей для любого потока,
    // т к тогда при его использовании компилятор не сможет выбрать нужную функцию 
    // (функция пользователя для его типа и любого потока ИЛИ эта функция для этого потока и любого типа) 
    // и выдаст ошибку.

    template<typename T> SmartStream::Stream &Read(SmartStream::Stream &s, T &v)
    {
        if (IsNewLine())
        {
            std::cout << s.Spaces();
        }
        std::cin >> v;
        return s;
    }

    template<typename T> SmartStream::Stream &Print(SmartStream::Stream &s, const T &v)
    {
        if (IsNewLine())
        {
            std::cout << s.Spaces();
        }
        std::cout << v;
        return s;
    }
}

namespace SmartStream
{
    std::string Stream::Spaces() const
    {
        return std::string(4 * Counter, ' ');
    }

    Stream &Stream::ReadLine(std::string &s)
    {
        if (IsNewLine())
        {
            std::cout << Spaces();
        }
        std::getline(std::cin, s);
        return *this;
    }

    Stream::Stream()
    {
        std::ios::sync_with_stdio(false);
        std::locale::global(std::locale("RU"));
        std::cout << "Русский язык включён." << std::endl;
    }

    Stream io;

    Stream &operator<<(Stream & s, Stream &(f)(Stream&))
    {
        return f(s);
    }

    Stream & operator<<(Stream & s, const std::string_view & str)
    {
        return Print(s, str);
    }

    Stream & operator<<(Stream & s, const char & ch)
    {
        return Print(s, ch);
    }

    Stream & operator<<(Stream & s, const unsigned long long int & n)
    {
        return Print(s, n);
    }

    Stream & operator<<(Stream & s, const long double & n)
    {
        return Print(s, n);
    }

    Stream & operator<<(Stream & s, const double & n)
    {
        Stream &operator<<(Stream &s, const long double &n);
    }

    Stream & operator<<(Stream & s, const int & n)
    {
        return Print(s, n);
    }

    Stream & operator<<(Stream & s, const long long int & n)
    {
        return Print(s, n);
    }

    Stream &endl(Stream &s)
    {
        std::cout << std::endl;
        return s;
    }
    
    Stream &tab(Stream & s)
    {
        ++s.Counter;
        return s;
    }

    Stream &untab(Stream & s)
    {
        if (s.Counter > 0)
        {
            --s.Counter;
        }
        return s;
    }

    Stream &tabl(Stream & s)
    {
        return tab(endl(s));
    }

    Stream &untabl(Stream & s)
    {
        return untab(endl(s));
    }

    Stream &wait(Stream &s)
    {
        std::cin.get();
        return s;
    }

    Stream & operator>>(Stream & s, std::string & str)
    {
        return Read(s, str);
    }

    Stream & operator>>(Stream & s, char & ch)
    {
        return Read(s, ch);
    }

    Stream & operator>>(Stream & s, double & n)
    {
        return Read(s, n);
    }

    Stream & operator>>(Stream & s, long double & n)
    {
        return Read(s, n);
    }

    Stream & operator>>(Stream & s, unsigned long long int & n)
    {
        return Read(s, n);
    }

    Stream & operator>>(Stream & s, int & n)
    {
        return Read(s, n);
    }

    Stream & operator>>(Stream & s, long long int & n)
    {
        return Read(s, n);
    }
}
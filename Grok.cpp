#include "Grok.h"
#include <algorithm>
#include <locale>
#include <execution>

namespace
{
    std::string Uppercase(const std::string_view &str)
    {
        std::string res(str);
        std::transform(cbegin(res), cend(res), begin(res), [loc = std::locale("RU")](const auto &i)
        {
            return std::toupper(i, loc);
        });
        return res;
    }

    bool Match(const std::string_view &upAnswer, const std::string_view &word)
    {
        // Если найдено слово
        return upAnswer.find(word) != -1 &&
            // и не найдено иных букв кроме букв этого слова
            std::find_if(cbegin(upAnswer), cend(upAnswer),
                [&word](const char &i) { return word.find(i) == -1; }) == cend(upAnswer);
        // То это нужное слово или его вариация
    }
}

bool Grok::IsPositiveRuWord(const std::string_view &mixedcaseAnswer)
{
    const auto positiveUppercaseAnswers = { "ДА", "1", "YES", "ХОЧУ", "СОГЛАСЕН", "ПУСТЬ", "OK" /*(en)*/, "ОК" /*(ru)*/ ,
        "ПУСКАЙ", "ПОЙДЁТ", "ПОЙДЕТ", "СОЙДЁТ", "СОЙДЕТ", "НОРМ", "НОРМАЛЬНО", "ОКИ", "ОКЕЙ",
        "ДЕЛАЙ", "СДЕЛАЙ", "СДЕЛАЙТЕ", "ДЕЛАЙТЕ", "РАЗУМЕЕТСЯ", "КОНЕЧНО", "ТОЧНО", "АГА", "АГАСЬ", "УГУ",
        "ЙЕС", "Е", "TRUE", "НОРМАС", "ДО"
    };
    return std::find_if(std::execution::par_unseq,
        cbegin(positiveUppercaseAnswers),
        cend(positiveUppercaseAnswers),
        [u = Uppercase(mixedcaseAnswer)](const auto &i){ return Match(u, i); }) != cend(positiveUppercaseAnswers);
}
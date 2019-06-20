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
        // ���� ������� �����
        return upAnswer.find(word) != -1 &&
            // � �� ������� ���� ���� ����� ���� ����� �����
            std::find_if(cbegin(upAnswer), cend(upAnswer),
                [&word](const char &i) { return word.find(i) == -1; }) == cend(upAnswer);
        // �� ��� ������ ����� ��� ��� ��������
    }
}

bool Grok::IsPositiveRuWord(const std::string_view &mixedcaseAnswer)
{
    const auto positiveUppercaseAnswers = { "��", "1", "YES", "����", "��������", "�����", "OK" /*(en)*/, "��" /*(ru)*/ ,
        "������", "���Ĩ�", "������", "���Ĩ�", "������", "����", "���������", "���", "����",
        "�����", "������", "��������", "�������", "����������", "�������", "�����", "���", "�����", "���",
        "���", "�", "TRUE", "������", "��"
    };
    return std::find_if(std::execution::par_unseq,
        cbegin(positiveUppercaseAnswers),
        cend(positiveUppercaseAnswers),
        [u = Uppercase(mixedcaseAnswer)](const auto &i){ return Match(u, i); }) != cend(positiveUppercaseAnswers);
}
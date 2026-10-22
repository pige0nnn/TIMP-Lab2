#include "RouteCipher.h"
#include "cipher_error.h"
#include <iostream>
#include <algorithm>
#include <cwctype>

std::wstring RouteCipher::getValidKey(const std::wstring& s) {
    if (s.empty()) throw cipher_error("Пустой ключ");
    std::wstring tmp(s);
    for (auto& c : tmp) {
        if (!iswdigit(c)) throw cipher_error("Ключ должен состоять только из цифр");
    }
    return tmp;
}

std::wstring RouteCipher::getValidOpenText(const std::wstring& s) {
    std::wstring tmp;
    for (auto c : s) {
        if (iswalpha(c)) {
            wchar_t up = towupper(c);
            if ((up >= L'А' && up <= L'Я') || up == L'Ё') {
                tmp.push_back(up);
            }
        }
    }
    if (tmp.empty()) throw cipher_error("В тексте нет допустимых русских букв");
    return tmp;
}

std::wstring RouteCipher::getValidCipherText(const std::wstring& s) {
    if (s.empty()) throw cipher_error("Пустой шифротекст");
    std::wstring tmp;
    for (auto c : s) {
        if (c == L' ') {
            tmp.push_back(c); 
        } else if ((c >= L'А' && c <= L'Я') || c == L'Ё') {
            tmp.push_back(c);
        } else {
            throw cipher_error("Шифротекст содержит недопустимые символы (только русские заглавные буквы)");
        }
    }
    return tmp;
}

RouteCipher::RouteCipher(const std::wstring& skey) {
    std::wstring validKeyStr = getValidKey(skey);
    try { key = std::stoi(validKeyStr); } 
    catch (...) { throw cipher_error("Ключ слишком большой"); }
    if (key <= 0) throw cipher_error("Ключ должен быть положительным числом");
}

std::wstring RouteCipher::encrypt(const std::wstring& open_text) {
    std::wstring validText = getValidOpenText(open_text);
    if (validText.empty()) return L"";

    int rows = (validText.length() + key - 1) / key;
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(key, L' '));

    int index = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < key; j++)
            if (index < (int)validText.length())
                table[i][j] = validText[index++];

    std::wstring result;
    for (int j = key - 1; j >= 0; j--)
        for (int i = 0; i < rows; i++)
            result += table[i][j];

    return result;
}

std::wstring RouteCipher::decrypt(const std::wstring& cipher_text) {
    std::wstring validText = getValidCipherText(cipher_text);
    if (validText.empty()) return L"";

    int rows = (validText.length() + key - 1) / key;
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(key, L' '));

    int index = 0;
    for (int j = key - 1; j >= 0; j--)
        for (int i = 0; i < rows; i++)
            if (index < (int)validText.length())
                table[i][j] = validText[index++];

    std::wstring result;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < key; j++)
            result += table[i][j];

    while (!result.empty() && result.back() == L' ') result.pop_back();
    return result;
}

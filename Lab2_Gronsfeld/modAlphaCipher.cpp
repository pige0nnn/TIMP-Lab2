#include "modAlphaCipher.h"
#include "cipher_error.h"
#include <cwctype>

std::wstring modAlphaCipher::getValidKey(const std::wstring& s) {
    if (s.empty()) throw cipher_error("Пустой ключ");
    std::wstring tmp;
    for (auto c : s) {
        if (numAlpha.find(towupper(c)) == std::wstring::npos)
            throw cipher_error("Недопустимый символ в ключе (только русские буквы)");
        tmp.push_back(towupper(c));
    }
    return tmp;
}

std::wstring modAlphaCipher::getValidOpenText(const std::wstring& s) {
    std::wstring tmp;
    for (auto c : s) {
        if (numAlpha.find(towupper(c)) != std::wstring::npos)
            tmp.push_back(towupper(c));
    }
    if (tmp.empty()) throw cipher_error("В тексте нет допустимых русских букв");
    return tmp;
}

std::wstring modAlphaCipher::getValidCipherText(const std::wstring& s) {
    if (s.empty()) throw cipher_error("Пустой шифротекст");
    std::wstring tmp;
    for (auto c : s) {
        if (numAlpha.find(c) == std::wstring::npos)
            throw cipher_error("Шифротекст содержит недопустимые символы");
        tmp.push_back(c);
    }
    return tmp;
}

modAlphaCipher::modAlphaCipher(const std::wstring& skey) {
    for (unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    std::wstring validKey = getValidKey(skey);
    key = convert(validKey);
}

std::vector<int> modAlphaCipher::convert(const std::wstring& s) {
    std::vector<int> result;
    for (auto c : s) result.push_back(alphaNum[c]);
    return result;
}

std::wstring modAlphaCipher::convert(const std::vector<int>& v) {
    std::wstring result;
    for (auto i : v) result.push_back(numAlpha[i]);
    return result;
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text) {
    std::vector<int> work = convert(getValidOpenText(open_text));
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text) {
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

#include <iostream>
#include <string>
#include <locale>
#include <limits>
#include <codecvt>
#include "modAlphaCipher.h"
#include "cipher_error.h"

using namespace std;

static wstring toWide(const string& s) {
    wstring_convert<codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(s);
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wcout << L"=== Шифр Гронсфельда (Русский) ===" << endl;
    
    wstring keyStr;
    modAlphaCipher* cipher = nullptr;

    while (true) {
        wcout << L"Введите ключ (слово на русском): ";
        wcin >> keyStr;
        try {
            cipher = new modAlphaCipher(keyStr);
            wcout << L"Ключ принят." << endl;
            break;
        } catch (const cipher_error& e) {
            wcerr << L"Ошибка ключа: " << toWide(e.what()) << L". Попробуйте еще раз." << endl;
            wcin.clear(); wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
        }
    }

    int choice;
    while (true) {
        wcout << L"\n0 - выход, 1 - зашифровать, 2 - расшифровать: ";
        if (!(wcin >> choice)) { wcin.clear(); wcin.ignore(numeric_limits<streamsize>::max(), L'\n'); continue; }
        if (choice == 0) break;
        if (choice != 1 && choice != 2) { wcout << L"Неизвестная операция." << endl; continue; }
        
        wcin.ignore(); 
        wcout << L"Введите текст: ";
        wstring text; getline(wcin, text);

        try {
            if (choice == 1) wcout << L"Зашифровано: " << cipher->encrypt(text) << endl;
            else wcout << L"Расшифровано: " << cipher->decrypt(text) << endl;
        } catch (const cipher_error& e) {
            wcerr << L"Ошибка: " << toWide(e.what()) << endl;
        }
    }
    delete cipher;
    return 0;
}

#include <iostream>
#include "../headers/reminder.h"

#define TIME_SIZE 8

Reminder::Reminder() {
    this->hours = 0;
    this->minutes = 0;
    this->seconds = 0;
    this->message = nullptr;
}

Reminder::Reminder(int hours,
                   int minutes,
                   int seconds,
                   char *message) {
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
    if (message != nullptr) {
        this->message = new char[StrLen(message) + 1];
        StrCpy(this->message, message);
    } else {
        this->message = nullptr;
    }
}

Reminder::Reminder(const Reminder &object) {
    this->hours = object.hours;
    this->minutes = object.minutes;
    this->seconds = object.seconds;
    if (object.message != nullptr) {
        this->message = new char[StrLen(object.message) + 1];
        StrCpy(this->message, object.message);
    } else {
        this->message = nullptr;
    }
}

Reminder::~Reminder() {
    delete[] this->message;
}

int Reminder::GetHours() {
    return this->hours;
}

int Reminder::GetMinutes() {
    return this->minutes;
}

int Reminder::GetSeconds() {
    return this->seconds;
}

char *Reminder::GetMessage() {
    char *result = new char[StrLen(message) + 1];
    StrCpy(result, this->message);

    return result;
}

void Reminder::SetTime(int hours,
                       int minutes,
                       int seconds) {
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
}

void Reminder::SetMessage(char *message) {
    this->message = new char[StrLen(message) + 1];
    StrCpy(this->message, message);
}

int Reminder::StrLen(char *string) {
    int len = 0;

    if (string != nullptr) {
        for (int i = 0; string[i] != '\0'; i++) {
            len++;
        }
    }

    return len;
}

char *Reminder::StrCpy(char *dest, const char *src) {
    char *result = dest;

    while ((*dest++ = *src++) != '\0');
    return result;
}

void Reminder::StrReverse(char* string) {
    int len = StrLen(string);
    for (int i = 0; i < len / 2; i++) {
        char tmp = string[i];
        string[i] = string[len - i - 1];
        string[len - i - 1] = tmp;
    }
}

char* Reminder::TimeToString(int number) {
    char* string = new char[3];

    if (number < 10) {
        string[0] = '0';
        string[1] = number + '0';
        string[2] = '\0';
    } else {
        string[2] = '\0';
        string[1] = number % 10 + '0';
        number /= 10;
        string[0] = number + '0';
    }

    return string;
}

std::ostream &operator<<(std::ostream &os, const Reminder &reminder) {
    os << static_cast<char*>(reminder);
    return os;
}

//std::ofstream &operator<<(std::ofstream &out, const Reminder &reminder) {
//
//}

Reminder *Reminder::operator+(const Reminder &reminder) {
    Reminder* result = nullptr;
    char *concat_message = new char[StrLen(this->message) + StrLen(reminder.message) + 2];

    unsigned i = 0;

    for (unsigned j = 0; this->message[j] != '\0'; j++) {
        concat_message[i++] = this->message[j];
    }

    concat_message[i++] = ' ';  // add a space char

    for (unsigned j = 0; reminder.message[j] != '\0'; j++) {
        concat_message[i++] = reminder.message[j];
    }

    concat_message[i] = '\0';  // add a null-term

    result = new Reminder(
        this->hours,
        this->minutes,
        this->seconds,
        concat_message
    );

    delete[] concat_message;
    return result;
}

Reminder* operator-(const Reminder& reminder_1, const Reminder& reminder_2) {
    Reminder* result = nullptr;
    char* diff_message = nullptr;

    int len_1 = Reminder::StrLen(reminder_1.message);
    int len_2 = Reminder::StrLen(reminder_2.message);

    if (len_1 > len_2) {
        int diff = len_1 - len_2;
        diff_message = new char[diff + 1];
        
        for (int i = 0; i < diff; i++) {
            diff_message[i] = reminder_1.message[len_2 + i];
        }

        diff_message[diff] = '\0';
    }

    result = new Reminder(
        reminder_1.hours,
        reminder_1.minutes,
        reminder_1.seconds,
        diff_message
    );

    if (diff_message) delete[] diff_message;
    return result;
}

Reminder &Reminder::operator=(const Reminder &reminder) {
    // Self-assigment check
    if (this != &reminder) {
        hours = reminder.hours;
        minutes = reminder.minutes;
        seconds = reminder.seconds;

        if (message) delete[] message;

        int len = StrLen(reminder.message);
        message = new char[len + 1];

        for (int i = 0; i < len; i++) {
            message[i] = reminder.message[i];
        }
        message[len] = '\0';
    }

    return *this;
}

Reminder &Reminder::operator++() {
    if (hours == 23)
        hours = 0;
    else
        ++hours;

    return *this;
}

Reminder Reminder::operator++(int) {
    Reminder result = *this;
    ++(*this);
    return result;
}

Reminder::operator char*() const {
    char* result = new char[TIME_SIZE + StrLen(this->message) + 2];  // "12:30:00 Message"

    int k = 0;  // Number of written symbols

    char* time = TimeToString(this->hours);
    StrCpy(result + k, time);
    k += 2;
    delete[] time;
    result[k++] = ':';

    time = TimeToString(this->minutes);
    StrCpy(result + k, time);
    k += 2;
    delete[] time;
    result[k++] = ':';

    time = TimeToString(this->seconds);
    StrCpy(result + k, time);
    k += 2;
    delete[] time;
    result[k++] = ' ';

    StrCpy(result + k, this->message);
    return result;
}

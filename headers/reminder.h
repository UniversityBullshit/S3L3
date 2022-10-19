#ifndef HEADERS_REMINDER_H_
#define HEADERS_REMINDER_H_


class Reminder {
public:
    // Constructors
    Reminder();
    Reminder(int hours, int minutes, int seconds, char* message);
    Reminder(const Reminder & object);
    ~Reminder();

    int GetHours();
    int GetMinutes();
    int GetSeconds();
    char* GetMessage();

    void SetTime(int hours, int minutes, int seconds);
    void SetMessage(char* message);

    friend std::ostream& operator<<(std::ostream& os, const Reminder& reminder);

    Reminder* operator+(const Reminder& reminder);
    friend Reminder* operator-(const Reminder& reminder_1, const Reminder& reminder_2);
    Reminder& operator=(const Reminder& reminder);
    Reminder& operator++();
    Reminder operator++(int);
    operator char*() const;

private:
    int hours;
    int minutes;
    int seconds;
    char* message;

    static int StrLen(char* string);
    static char* StrCpy(char* dest, const char* src);
};

#endif  // HEADERS_REMINDER_H_

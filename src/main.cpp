#include <iostream>
#include <fstream>
#include "../headers/reminder.h"
#include "../headers/header.h"

#define MAX_MESSAGE_LENGTH 128

int main() {
    Reminder **reminders = nullptr;
    int reminders_count = 0;
    bool status = true;

    while (status) {
        status = Menu(&reminders, &reminders_count);
    }

    // Clearing reminders array
    if (reminders != nullptr) {
        for (int i = 0; i < reminders_count; i++) {
            delete reminders[i];
        }
        delete[] reminders;
    }

    return 0;
}

bool Menu(Reminder ***reminders, int *const reminders_count) {
    bool status = true;
    int option;

    PrintMenu();
    option = GetInt();

    switch (option) {
        case 1:  // Reminders list
            RemindersList(*reminders, *reminders_count);
            break;
        case 2:  // New reminder
            AddReminder(reminders, reminders_count);
            break;
        case 3:  // Change reminder
            ChangeReminder(*reminders, *reminders_count);
            break;
        case 4:  // Sum two reminders
            Sum(reminders, reminders_count);
            break;
        case 5:  // Diff two reminders
            Diff(reminders, reminders_count);
            break;
        case 6:  // Assigment
            Assigment(*reminders, *reminders_count);
            break;
        case 7:  // Prefix increment
            PreIntocreting(*reminders, *reminders_count);
            break;
        case 8:  // Postfix increment
            PostIntocreting(*reminders, *reminders_count);
            break;
        case 9:  // Cast to char*
            Cast(*reminders, *reminders_count);
            break;
        case 10: // Write to file
            WriteToFile(*reminders, *reminders_count);
            break;
        case 11: // Write to binary file
            BWriteToFile(*reminders, *reminders_count);
            break;
        case 12: // Read from binary file
            BReadFromFile(reminders, reminders_count);
            break;
        case 13:  // Exit
            status = false;
            break;
        default:
            std::cout << "No such value\n";
            break;
    }

    if (status) {
        std::cout << std::endl;
    }

    return status;
}

void PrintMenu() {
    std::cout << "1. Reminders list\n"
              << "2. New reminder\n"
              << "3. Change reminder\n"
              << "4. Sum two reminders\n"
              << "5. Difference two reminders\n"
              << "6. Assign one to another\n"
              << "7. Prefix Intocreting\n"
              << "8. Postfix Intocreting\n"
              << "9. Cast to char*\n"
              << "10. Write to file\n"
              << "11. Write to binary file\n"
              << "12. Read from binary file\n"
              << "13. Exit\n"
              << "> ";
}

int GetInt() {
    int value;
    std::cin >> value;
    if (!(std::cin)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        value = -1;
    }

    return value;
}

void RemindersList(Reminder **reminders, const int reminders_count) {
    if (reminders == nullptr) {
        std::cout << "No reminders" << std::endl;
    } else {
        std::cout << "Reminders:" << std::endl;
        for (int i = 0; i < reminders_count; i++) {
            std::cout << i + 1
                      << ". "
                      << *reminders[i]
                      << std::endl;
        }
    }
}

void AddReminder(Reminder ***reminders, int *const reminders_count) {
    std::cout << "Creating a new reminder" << std::endl;
    Reminder *reminder = ReminderInit();

    if (reminder != nullptr) {
        std::cout << *reminder << std::endl;

        Reminder **tmp = Realloc(*reminders, reminders_count);

        if (*reminders != nullptr && tmp != nullptr) {
            delete[] *reminders;
            *reminders = nullptr;
        }

        if (tmp != nullptr) {
            tmp[*reminders_count - 1] = reminder;
            *reminders = tmp;
        }
    }
}

void AddReminder(Reminder ***reminders, int *const reminders_count, Reminder *reminder) {
    if (reminder != nullptr) {
        Reminder **tmp = Realloc(*reminders, reminders_count);

        // Clear previous array
        if (*reminders != nullptr && tmp != nullptr) {
            delete[] *reminders;
            *reminders = nullptr;
        }

        // Add new one reminder, set tmp as *reminders
        if (tmp != nullptr) {
            tmp[*reminders_count - 1] = reminder;
            *reminders = tmp;
        }
    }
}

Reminder *ReminderInit() {
    Reminder *reminder = nullptr;
    int hours, minutes, seconds;
    char* message = nullptr;
    bool status = 1;

    if (status) {
        std::cout << "Hours (0-23): ";
        hours = GetInt();
        if (hours < 0 || hours > 23) status = 0;
    }

    if (status) {
        std::cout << "Minutes (0-59): ";
        minutes = GetInt();
        if (minutes < 0 || minutes > 59) status = 0;
    }

    if (status) {
        std::cout << "Seconds (0-59): ";
        seconds = GetInt();
        if (seconds < 0 || seconds > 59) status = 0;
    }

    if (status) {
        message = new char[MAX_MESSAGE_LENGTH];
        std::cout << "Message (128 - max length): ";
        std::cin.get(); // Get \n from buffer
        std::cin.getline(message, MAX_MESSAGE_LENGTH);
        reminder = new Reminder(hours, minutes, seconds, message);
        delete[] message;
    }

    if (!status) {
        std::cout << "Incorrect input" << std::endl;
    }

    return reminder;
}

Reminder** Realloc(Reminder **reminders, int *const reminders_count) {
    Reminder **tmp = new Reminder* [++(*reminders_count)];

    for (int i = 0; i < *reminders_count - 1; i++) {
        tmp[i] = reminders[i];
    }
    tmp[*reminders_count - 1] = nullptr;

    return tmp;
}

void ChangeReminder(Reminder **reminders, const int reminders_count) {
    if (reminders == nullptr) {
        std::cout << "No reminders" << std::endl;
    } else {
        std::cout << "Choose reminder\n"
                  << "> ";
        int reminder = GetInt();

        if (reminder < 1 || reminder > reminders_count) {
            std::cout << "Incorrect input" << std::endl;
        } else {
            delete reminders[reminder - 1];
            reminders[reminder - 1] = ReminderInit();
        }
    }
}

void Sum(Reminder ***reminders, int *const reminders_count) {
    int fr, sr;  // first / second reminders

    std::cout << "Choose first reminder\n"
              << ">";
    fr = GetInt() - 1;

    std::cout << "Choose second reminder\n"
              << ">";
    sr = GetInt() - 1;

    if ((fr + 1 < 1 || fr + 1 > *reminders_count) ||
        (sr + 1 < 1 || sr + 1 > *reminders_count) ||
        (fr == sr)) {
        std::cout << "Incorrect input" << std::endl;
    } else {
        AddReminder(
            reminders,
            reminders_count,
            *reminders[0][fr] + *reminders[0][sr]
        );
    }
}

void Diff(Reminder ***reminders, int *const reminders_count) {
    int fr, sr;  // first / second reminders

    std::cout << "Choose first reminder\n"
              << ">";
    fr = GetInt() - 1;

    std::cout << "Choose second reminder\n"
              << ">";
    sr = GetInt() - 1;

    if ((fr + 1 < 1 || fr + 1 > *reminders_count) ||
        (sr + 1 < 1 || sr + 1 > *reminders_count) ||
        (fr == sr)) {
        std::cout << "Incorrect input" << std::endl;
    } else {
        AddReminder(
            reminders,
            reminders_count,
            *reminders[0][fr] - *reminders[0][sr]
        );
    }
}

void Assigment(Reminder **reminders, const int reminders_count) {
    int fr, sr;  // first / second reminders

    std::cout << "Choose first reminder to assign\n"
              << ">";
    fr = GetInt() - 1;

    std::cout << "Choose second reminder\n"
              << ">";
    sr = GetInt() - 1;

    if ((fr + 1 < 1 || fr + 1 > reminders_count) ||
        (sr + 1 < 1 || sr + 1 > reminders_count) ||
        (fr == sr)) {
        std::cout << "Incorrect input" << std::endl;
    } else {
        *reminders[fr] = *reminders[sr];
    }
}

void PreIntocreting(Reminder **reminders, const int reminders_count) {
    int reminder;

    std::cout << "Choose reminder\n"
              << ">";
    reminder = GetInt() - 1;

    if (reminder + 1 < 1 || reminder + 1 > reminders_count) {
        std::cout << "Incorrect input" << std::endl;
    } else {
        ++(*reminders[reminder]);
    }
}

void PostIntocreting(Reminder **reminders, const int reminders_count) {
    int reminder;

    std::cout << "Choose reminder\n"
              << ">";
    reminder = GetInt() - 1;

    if (reminder + 1 < 1 || reminder + 1 > reminders_count) {
        std::cout << "Incorrect input" << std::endl;
    } else {
        (*reminders[reminder])++;
    }
}

void Cast(Reminder **reminders, const int reminders_count) {
    int reminder;

    std::cout << "Choose reminder\n"
              << ">";
    reminder = GetInt() - 1;

    if (reminder + 1 < 1 || reminder + 1 > reminders_count) {
        std::cout << "Incorrect input" << std::endl;
    } else {
        char* string = static_cast<char*>(*reminders[reminder]);
        std::cout << "Casted message: " << string << std::endl;
        delete[] string;
    }
}

void WriteToFile(Reminder **reminders, const int reminders_count) {
    if (reminders == nullptr) {
        std::cout << "No reminders to write" << std::endl;
    } else {
        std::ofstream out;
        out.open("out.txt");
        if (out.is_open()) {
            for (int i = 0; i < reminders_count; i++) {
                out << *reminders[i];
                if (i < reminders_count - 1) {
                    out << std::endl;
                }
            }
        }
    }
}

void BWriteToFile(Reminder **reminders, const int reminders_count) {
    if (reminders == nullptr) {
        std::cout << "No reminders to write" << std::endl;
    } else {
        std::fstream out;
        out.open("out.bin", std::ios::out | std::ios::binary);
        if (out.is_open()) {
            out.write((char*)&reminders_count, sizeof(int));
            for (int i = 0; i < reminders_count; i++) {
                out << *reminders[i];
            }
        }
    }
}

void BReadFromFile(Reminder ***reminders, int* const reminders_count) {
    std::fstream in;
    in.open("out.bin", std::ios::in | std::ios::binary);
    if (in.is_open()) {
        int sz;
        in.read((char*)&sz, sizeof(int));
        for (int i = 0; i < sz; i++) {
            Reminder* reminder = new Reminder();
            in >> *reminder;
            AddReminder(reminders, reminders_count, reminder);
        }
    }
}

#ifndef HEADERS_HEADER_H_
#define HEADERS_HEADER_H_

bool Menu(Reminder ***reminders, int *const reminders_count);
void PrintMenu();

int GetInt();

void RemindersList(Reminder **reminders, const int reminders_count);

void AddReminder(Reminder ***reminders, int *const reminders_count);
void AddReminder(Reminder ***reminders, int *const reminders_count, Reminder* reminder);
Reminder *ReminderInit();
Reminder** Realloc(Reminder **reminders, int *const reminders_count);

void ChangeReminder(Reminder **reminders, const int reminders_count);

void Sum(Reminder ***reminders, int *const reminders_count);
void Diff(Reminder ***reminders, int *const reminders_count);
void Assigment(Reminder **reminders, const int reminders_count);
void PreIntocreting(Reminder **reminders, const int reminders_count);
void PostIntocreting(Reminder **reminders, const int reminders_count);
void Cast(Reminder **reminders, const int reminders_count);
void WriteToFile(Reminder **reminders, const int reminders_count);
void BWriteToFile(Reminder ** reminders, const int reminders_count);
void BReadFromFile(Reminder ***reminders, int* const reminders_count);

#endif  // HEADERS_HEADER_H_

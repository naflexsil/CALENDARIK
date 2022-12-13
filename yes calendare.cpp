           
              /*************************************
              *                                    *
              *      Старикова Алина Павловна      *
              *             "Календарь"            *
              *               ПИ-221               *
              *                                    *
              **************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

using namespace std;
int fullDay = 8;  // ск-ко всего дней в неделе
string dayWeek[8] = {"Пн", " Вт", " Ср", " Чт", " Пт", " Сб", " Вс", " Дкч"};
int daysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct monthRow {
  string months; string weekRow; int amountOfWeeks = 0;
  string days[10] = {" ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
};
bool finalYear(int year) {  // "bool" - логический тип(true/false)
  if(year % 400 == 0) {
    return true;
  }
  if(year % 100 == 0) {
    return false;
  }
  if(year % 4 == 0) {
    return true;
  }
  return false;
}

int firstDayOfMonth(int year, int month) {
  int shifts[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
  int shift = shifts[month - 1];

  if(finalYear(year) and (month > 2)) {
    shift += 1;
  };

  year = (year - 1) % 400;
  int century = year / 100;
  int index = ((4 * century) + (year % 100)) % fullDay;

  int dayWeek = (index + (index / 4)) + shift;
  return(dayWeek % fullDay);
}

int main() {
  int year;
  cout << " введите год: ";
  cin >> year;

  monthRow columns[4];
  columns[0].months += string(13, ' ') + "Январь" + string(31, ' ') + "Февраль" + string(31, ' ') + "Март";
  columns[1].months += string(13, ' ') + "Апрель" + string(33, ' ') + "Май" + string(33, ' ') + "Июнь";
  columns[2].months += string(13, ' ') + "Июль" + string(33, ' ') + "Август" + string(31, ' ') + "Сентябрь";
  columns[3].months += string(13, ' ') + "Октябрь" + string(30, ' ') + "Ноябрь" + string(30, ' ') + "Декабрь";

  for(int columnsIndex = 0; columnsIndex < 4; ++columnsIndex) {
    for(int weekColumns = 0; weekColumns < 3; ++weekColumns) {
      for(int weekDayIndex = 0; weekDayIndex < fullDay; ++weekDayIndex) {
        columns[columnsIndex].weekRow += dayWeek[weekDayIndex] + string(1, ' ');  // расст-е между днями недели
      }
      columns[columnsIndex].weekRow += string(5, ' ');  // сдвиг дней недели
    }
  }
  int columnsIndex = 0; int weekIndex; int maxDay = 13;
  for(int monthIndex = 1; monthIndex < maxDay; ++monthIndex) {
    weekIndex = 0;

    int numberInWeek = 0;
    int spacesBeforeFirstDay = firstDayOfMonth(year, monthIndex);
    while(spacesBeforeFirstDay) {
      columns[columnsIndex].days[weekIndex] += string(4, ' ');
      --spacesBeforeFirstDay;
      ++numberInWeek;
    };

    for(int dayIndex = 1; dayIndex < daysInMonths[monthIndex - 1] + 1; ++dayIndex) {
      if(dayIndex < 10) {
        columns[columnsIndex].days[weekIndex] += " " + to_string(dayIndex);
        columns[columnsIndex].days[weekIndex] += string(2, ' ');  // расст-е между днями(цифрами)
      } else {
        columns[columnsIndex].days[weekIndex] += to_string(dayIndex);
        columns[columnsIndex].days[weekIndex] += string(2, ' ');
      }
      ++numberInWeek;

      if(numberInWeek == fullDay) {
        columns[columnsIndex].days[weekIndex] += string(5, ' ');
        numberInWeek = 0;
        ++weekIndex;
      }

      int placeAfterLastDay;
      if(monthIndex == 2 && finalYear(year) && dayIndex == fullDay) {
        columns[columnsIndex].days[weekIndex] += to_string(dayIndex);
        placeAfterLastDay = (fullDay - numberInWeek + 1) * fullDay;
        columns[columnsIndex].days[weekIndex] += string(placeAfterLastDay, ' ');
      } else if(dayIndex + 1 > daysInMonths[monthIndex - 1]) {
        placeAfterLastDay = (fullDay - numberInWeek) * fullDay;
        columns[columnsIndex].days[weekIndex] += string(placeAfterLastDay, ' ');
      }
    }
    if(weekIndex > columns[columnsIndex].amountOfWeeks) {
      columns[columnsIndex].amountOfWeeks = weekIndex;
    }
    if(monthIndex % 3 == 0) {
      ++columnsIndex;
    }
  }
  for(int columnsIndex = 0; columnsIndex < 4; ++columnsIndex) {
    cout << endl << endl << columns[columnsIndex].months << endl << columns[columnsIndex].weekRow << endl;
    for(int row = 0; row < columns[columnsIndex].amountOfWeeks; ++row) {
      cout << columns[columnsIndex].days[row] << endl;
    }
  }
  return 0;
}


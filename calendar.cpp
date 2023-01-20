/**
*  
* Solution to course project # 10
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Nayle Gavazova
* @idnumber 0MI060226
* @compiler VC
*
* <file with helper functions>
*
*/

#include <iostream>
#include <ctime>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//useful materials
string months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
string daysNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
string daysNamesMon[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
int DATE, MONTH, YEAR, DAY;

//conversing date into string
string todayTomorrowIntoString (int date, int month, int year)
{
    string d, m;
    switch (date)
    {
        case 1: d = "01"; break;
        case 2: d = "02"; break;
        case 3: d = "03"; break;
        case 4: d = "04"; break;
        case 5: d = "05"; break;
        case 6: d = "06"; break;
        case 7: d = "07"; break;
        case 8: d = "08"; break;
        case 9: d = "09"; break;
        default: d = to_string(date); break;
    }
    switch( month)
    {
        case 1: m = "01"; break;
        case 2: m = "02"; break;
        case 3: m = "03"; break;
        case 4: m = "04"; break;
        case 5: m = "05"; break;
        case 6: m = "06"; break;
        case 7: m = "07"; break;
        case 8: m = "08"; break;
        case 9: m = "09"; break;
        default: m = to_string(month); break;
    }
    string result = d + "/" + m + "/" + to_string (year);
    return result;

}

//Printing the current date
void Asctime (const struct tm *timeptr)
{
    char wday_name[][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    char mon_name[][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    string day = wday_name[timeptr->tm_wday];
    string month = mon_name[timeptr->tm_mon];
    int date = timeptr->tm_mday;
    int year = 1900 + timeptr->tm_year;
    DATE = date;
    DAY = timeptr->tm_wday;
    MONTH = timeptr->tm_mon + 1;
    YEAR = year;
    cout << "Welcome! Today is " << day << ", " << date << " " << month << " " << year << ". "<< endl << endl;
}

/*A Function that returns the index of the day
  of the date- day/month/year
  For e.g-
 
  Index     Day
  0         Sunday
  1         Monday
  2         Tuesday
  3         Wednesday
  4         Thursday
  5         Friday
  6         Saturday*/
int dayNumber (int day, int month, int year)
{
    int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    year -= month < 3;
    return (year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;
}

/*A Function that returns the index of the day
  of the date- day/month/year
  For e.g-
 
  Index     Day
  0         Monday
  1         Tuesday
  2         Wednesday
  3         Thursday
  4         Friday
  5         Saturday
  6         Sunday*/
int dayNumberMon(int day, int month, int year)
{
    int t[] = { 6, 2, 1, 4, 6, 2, 4, 0, 3, 5, 1, 3 };
    year -= month < 3;
    return ( year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;
}
 
/*
  A Function that returns the name of the month
  with a given month number
 
  Month Number     Name
  0                January
  1                February
  2                March
  3                April
  4                May
  5                June
  6                July
  7                August
  8                September
  9                October
  10               November
  11               December */
string getMonthName (int monthNumber)
{
    return (months[monthNumber]);
}
 
/* A Function to return the number of days in
   a month
 
  Month Number     Name        Number of Days
  0                January     31
  1                February    28 (non-leap) / 29 (leap)
  2                March       31
  3                April       30
  4                May         31
  5                June        30
  6                July        31
  7                August      31
  8                September   30
  9                October     31
  10               November    30
  11               December    31
 
*/
int numberOfDays (int monthNumber, int year)
{
    switch (monthNumber)
    {
        case 0:
        case 2:
        case 4:
        case 6:
        case 7:
        case 9:
        case 11: return 31; break;
        case 1: // If the year is leap then February has 29 days
                if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
                {
                    return 29;break;
                }
                else
                {
                    return 28; break;
                }
        case 3:
        case 5:
        case 8:
        case 10: return 30; break;
        default: return -1;
    }
}
//finding the number of event in a particular day
int brEventsInDay (int day, int month, int year)
{
    string today  = todayTomorrowIntoString (day, month, year);
    int countToday=0;
    //counting the number of events
    int count;
    ifstream numEvents;
    numEvents.open("numEventsPeriods.txt", ios ::in);
    if (numEvents.is_open())
    {
        string temp;
        numEvents >> temp;
        count = stoi (temp);
        numEvents.close();
    }
    ifstream read;
    read.open ("eventStartPeriods.txt", ios ::in);
    if (read.is_open())
    {
        string date;
        int i = 0;
        while (i<count)
        {
            read >> date;
            if (date == today)
            {
                countToday++;
            }
            i++;
        }
        read.close();
    }
    return countToday;
}

const int SPACES=7;
// Function to print the calendar when the first day is Sun
void printCalendarSun(int month, int year)
{
    // Index of the day from 0 to 6
    int current = dayNumber (1, month, year);
    int days = numberOfDays (month-1, year);

    //Print the month name
    cout << "\n ----------------- " << getMonthName (month-1) << " "<< year << " -----------------\n";
 
    if (year == YEAR && month == MONTH)
    {
        // Print the columns
        for (int i = 0; i < 7; i++)
        {
            if (i == DAY)
            {
                cout << "   " << "["  << daysNames[i] << "]";
            }
            else
            {
                cout << "    " << daysNames[i];
            }
        }
        cout << endl;
        // Print appropriate spaces
        int k;
        for (k = 0; k < current; k++)
        {
            cout << setw (SPACES) << "  ";
        }
        for (int j = 1; j <= days; j++)
        {
            int br = brEventsInDay (j, month, year);
            if (j == DATE)
            {
                if (br == 0)
                {
                    cout << setw (SPACES - 3) << "[" << j << "]";
                }
                else 
                {
                    cout << setw (SPACES-4) << "[" << j << "]" << "(" << br << ")";
                }
            }
            else
            {
                if (br == 0)
                {
                    cout << setw (SPACES) << j;
                }
                else
                {
                    cout << setw (SPACES-3) << j << "(" << br << ")";
                }
            }
            if (++k > 6)
            {
                k = 0;
                cout << endl;
            }
        }
    }
    else
    {
        // Print the columns
        for (int i = 0; i < 7; i++)
        {
            cout << "    " << daysNames[i];
            
        }
        cout << endl;
        // Print appropriate spaces
        int k;
        for (k = 0; k < current; k++)
        {
            cout << setw (SPACES) << " ";
        }
        for (int j = 1; j <= days; j++)
        {
            int br = brEventsInDay (j, month, year);
            if (br == 0)
            {
                cout << setw (SPACES) << j;
            }
            else
            {
                cout << setw (SPACES - 3) << j << "(" << br << ")";
            }
            if (++k > 6)
            {
                k = 0;
                cout << endl;
            }
        }
    }
    
}

// Function to print the calendar when the first day is Mon
void printCalendarMon (int month, int year)
{
    // Index of the day from 0 to 6
    int current = dayNumberMon (1, month, year);
    int days = numberOfDays (month-1, year);
    //Print the month name
    cout << "\n ---------------- " << getMonthName (month-1) << " "<< year << " ----------------\n";
 
    if (year == YEAR && month == MONTH)
    {
        // Print the columns
        for (int i = 0; i < 7; i++)
        {
            if (i == DAY-1)
            {
                cout << "   "<< "["  << daysNamesMon[i] << "]";
            }
            else
            {
                cout << "    " << daysNamesMon[i];
            }
        }
        cout << endl;
        // Print appropriate spaces
        int k;
        for (k = 0; k < current; k++)
        {
            cout << setw(SPACES) << "  ";
        }
        for (int j = 1; j <= days; j++)
        {
            int br = brEventsInDay (j, month, year);
            if (j == DATE)
            {
                if (br == 0)
                {
                    cout << setw (SPACES - 3) << "[" << j << "]";
                }
                else 
                {
                    cout << setw (SPACES-4) << "[" << j << "]" << "(" << br << ")";
                }
            }
            else
            {
                if (br == 0)
                {
                    cout << setw (SPACES) << j;
                }
                else
                {
                    cout << setw (SPACES - 3) << j << "(" << br << ")";
                }
            }
            if (++k > 6)
            {
                k = 0;
                cout << endl;
            }
        }
    }
    else
    {
        // Print the columns
        for (int i = 0; i < 7; i++)
        {
            cout << "    " << daysNamesMon[i];
            
        }
        cout << endl;
        // Print appropriate spaces
        int k;
        for (k = 0; k < current; k++)
        {
            cout << setw (SPACES) << " ";
        }
        for (int j = 1; j <= days; j++)
        {
            int br = brEventsInDay (j, month, year);
            if (br == 0)
            {
                cout << setw (SPACES) << j;
            }
            else
            {
                cout << setw (SPACES-3) << j << "(" << br << ")" ;
            }

            if (++k > 6)
            {
                k = 0;
                cout << endl;
            }
        }
    }
    
}

//function finding the number of the day
int dayNum (char dayNumber[])
{
    int a, b;
    switch (dayNumber[0])
    {
        case '0': a = 0; break;
        case '1': a = 1; break;
        case '2': a = 2; break;
        case '3': a = 3; break;
        case '4': a = 4; break;
        case '5': a = 5; break;
        case '6': a = 6; break;
        case '7': a = 7; break;
        case '8': a = 8; break;
        case '9': a = 9; break;
        default: a= -1; break;
    }
    switch (dayNumber[1])
    {
        case '0': b = 0; break;
        case '1': b = 1; break;
        case '2': b = 2; break;
        case '3': b = 3; break;
        case '4': b = 4; break;
        case '5': b = 5; break;
        case '6': b = 6; break;
        case '7': b = 7; break;
        case '8': b = 8; break;
        case '9': b = 9; break;
        default: b= -1; break;
    }
    return a*10+b;
}

//function finding the number of the month
int monthNum (char printMonth[])
{
    int a, b;
    switch (printMonth[0])
    {
        case '0': a=0; break;
        case '1': a=1; break;
        default: a=2; break;
    }
    switch (printMonth[1])
    {
        case '0': b = 0; break;
        case '1': b = 1; break;
        case '2': b = 2; break;
        case '3': b = 3; break;
        case '4': b = 4; break;
        case '5': b = 5; break;
        case '6': b = 6; break;
        case '7': b = 7; break;
        case '8': b = 8; break;
        case '9': b = 9; break;
        default: b= -1; break;
    }
    return (a*10+b);
}

//function finding the number of the year
int yearNum (char printMonth[])
{
    int a, b, c, d;
    switch (printMonth[3])
    {
        case '0': a = 0; break;
        case '1': a = 1; break;
        case '2': a = 2; break;
        case '3': a = 3; break;
        case '4': a = 4; break;
        case '5': a = 5; break;
        case '6': a = 6; break;
        case '7': a = 7; break;
        case '8': a = 8; break;
        case '9': a = 9; break;
        default: a= -1; break;
    }
    switch (printMonth[4])
    {
        case '0': b = 0; break;
        case '1': b = 1; break;
        case '2': b = 2; break;
        case '3': b = 3; break;
        case '4': b = 4; break;
        case '5': b = 5; break;
        case '6': b = 6; break;
        case '7': b = 7; break;
        case '8': b = 8; break;
        case '9': b = 9; break;
        default: b= -1; break;
    }
    switch (printMonth[5])
    {
        case '0': c = 0; break;
        case '1': c = 1; break;
        case '2': c = 2; break;
        case '3': c = 3; break;
        case '4': c = 4; break;
        case '5': c = 5; break;
        case '6': c = 6; break;
        case '7': c = 7; break;
        case '8': c = 8; break;
        case '9': c = 9; break;
        default: c= -1; break;
    }
    switch (printMonth[6])
    {
        case '0': d = 0; break;
        case '1': d = 1; break;
        case '2': d = 2; break;
        case '3': d = 3; break;
        case '4': d = 4; break;
        case '5': d = 5; break;
        case '6': d = 6; break;
        case '7': d = 7; break;
        case '8': d = 8; break;
        case '9': d = 9; break;
        default: d= -1; break;
    }
    return (a*1000+b*100+c*10+d);
}

//function checking if a date is correct
bool isCorrectDate (string date)
{
    char dateNum[2];
    dateNum[0] = date[0];
    dateNum[1] = date[1];
    char monthN[2];
    monthN[0] = date[3];
    monthN[1] = date[4];
    char yearN[7];
    yearN[3] = date[6];
    yearN[4] = date[7];
    yearN[5] = date[8];
    yearN[6] = date[9];
    if (monthNum (monthN)>0 && monthNum (monthN)<13 && dayNum (dateNum)>0 && dayNum (dateNum)<=numberOfDays (monthNum (monthN)-1, yearNum (yearN)))
    {
        return true;
    }
    else 
    {
        return false;
    }
}

//function checking if the start date of the event is before the end date
bool startBeforeEnd (string start, string end)
{
    //start year
    char yearS[7];
    yearS[3] = start[6];
    yearS[4] = start[7];
    yearS[5] = start[8];
    yearS[6] = start[9];

    //end year
    char yearE[7];
    yearE[3] = end[6];
    yearE[4] = end[7];
    yearE[5] = end[8];
    yearE[6] = end[9];

    if (yearNum (yearS) < yearNum (yearE))
    {
        return true;
    }
    else if (yearNum (yearS) == yearNum (yearE))
    {
        //start month
        char monthS[2];
        monthS[0] = start[3];
        monthS[1] = start[4];

        //END month
        char monthE[2];
        monthE[0] = end[3];
        monthE[1] = end[4];

        if (monthNum (monthS) <= monthNum (monthE))
        {
            //start date
            char dateS[2];
            dateS[0] = start[0];
            dateS[1] = start[1];

            //end date
            char dateE[2];
            dateE[0] = end[0];
            dateE[1] = end[1];

            if (dayNum (dateS) <= dayNum (dateE))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

//function checking for an existing event
bool existingEvent (string event)
{
    int temp = 0;
    ifstream allEvents;
    allEvents.open ("eventName.txt", ios ::in);
    if (allEvents.is_open())
    {
        while (!allEvents.eof()) 
        {
            string existing("");
            getline (allEvents, existing);
            if (event == existing)
            {
                temp = 1;
                break;
            }
        }
        allEvents.close();
    }
    if (temp == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//function finding the min date
int brMinDate (int index, string array[], int br)
{
    int result = 0;
    string check = array[index];
    for (int i = 0; i < br; i++)
    {
        if (array[i] == check)
        {
            result++;
        }
    }
    return result;
}

//function finding the index of the min date
int minDateIndex (string array[], int br)
{
    int index = 0;
    string min = array[0];
    for (int i = 0; i < br; i++)
    {
        if (startBeforeEnd (array[i], min) == true)
        {
            index = i;
        }
    }
    return index;
}
//function sorting the files eventStart, eventName, eventWholeInf
void sortFiles ()
{
    //finding the num of events in these files
    int counterEvents;
    ifstream numEvent;
    numEvent.open ("numberEvents.txt", ios ::in);
    if(numEvent.is_open())
    {
        string temp;
        numEvent >> temp;
        counterEvents = stoi (temp);
        numEvent.close();
    }
    //saving the events from the files in arrais
    ifstream readName, readDates, readWhole;
    string arrayName[counterEvents];
    string arrayDates[counterEvents];
    string arrayWhole[counterEvents];
    readName.open ("eventName.txt", ios ::in);
    readDates.open ("eventStart.txt", ios ::in);
    readWhole.open ("eventWholeInf.txt", ios ::in);
    int i = 0;
    if (readName.is_open() && readDates.is_open() && readWhole.is_open())
    {
        while (i < counterEvents)
        {
            string name("");
            getline(readName, name);
            string dates;
            readDates >> dates;
            string whole("");
            getline (readWhole, whole);
            arrayName[i] = name;
            arrayDates[i] = dates;
            arrayWhole[i] = whole;
            i++;
        }
        readName.close();
        readDates.close();
        readWhole.close();
    }
    for (int i = 0; i < counterEvents; i++)
    {
        for (int j = i+1; j < counterEvents; j++)
        {
            if (startBeforeEnd(arrayDates[j], arrayDates[i]) == true)
            {
                string date = arrayDates[j];
                arrayDates[j] = arrayDates[i];
                arrayDates[i] = date;
                string name = arrayName[j];
                arrayName[j] = arrayName[i];
                arrayName[i] = name;
                string whole = arrayWhole[j];
                arrayWhole[j] = arrayWhole[i];
                arrayWhole[i] = whole;
            }
        }
    }
    for (int i = 0; i < counterEvents;)
    {
        int br = 1;
        for (int j = i+1; j < counterEvents; j++)
        {
            if (arrayDates[i] == arrayDates[j])
            {
                br++;
            }
            else
            {
                break;
            }
        }
        if(br > 1)
        {
            string array[br];
            string arrayW[br];
            for (int q = i, s = 0; q < i + br; q++, s++)
            {
                array[s] = arrayName[q];
                arrayW[s] = arrayWhole[q];
            }
            for (int s = 0; s < br; s++)
            {
                for (int t = s+1; t < br; t++)
                {
                    if (array[s] > array[t])
                    {
                        //swapping names
                        string temp = array[s];
                        array[s] = array[t];
                        array[t] = temp;
                        //swapping whole
                        string tempW = arrayW[s];
                        arrayW[s] = arrayW[t];
                        arrayW[t] = tempW;
                    }
                }
            }
            for (int q = i, s = 0; q < i + br; q++, s++)
            {
                arrayName[q] = array[s];
                arrayWhole[q] = arrayW[s];
            }
            i = i + br;
        }
        else
        {
            i++;
        }
    }
    //arrais into files
    ofstream writeName, writeDates, writeWhole;
    writeName.open ("eventName.txt", ios ::out);
    writeDates.open ("eventStart.txt", ios ::out);
    writeWhole.open ("eventWholeInf.txt", ios ::out);
    int p = 0;
    if (writeName.is_open() && writeDates.is_open() && writeWhole.is_open())
    {
        while (p < counterEvents)
        {
            writeName << arrayName[p] << endl;
            writeDates << arrayDates[p] << endl;
            writeWhole << arrayWhole[p] << endl;
            p++;
        }
        writeName.close();
        writeDates.close();
        writeWhole.close();
    }
}
//function sorting the files eventNamesPeriods, eventStartPeriods
void sortFilesPeriods()
{
    //finding the num of events in these files
    int counterEvents;
    ifstream numEvent;
    numEvent.open ("numEventsPeriods.txt", ios ::in);
    if (numEvent.is_open())
    {
        string temp;
        numEvent >> temp;
        counterEvents = stoi (temp);
        numEvent.close();
    }
    //saving the events from the files in arrais
    ifstream readName, readDates;
    string arrayName[counterEvents];
    string arrayDates[counterEvents];
    readName.open ("eventNamePeriods.txt", ios ::in);
    readDates.open ("eventStartPeriods.txt", ios ::in);
    int i=0;
    if (readName.is_open() && readDates.is_open())
    {
        while (i < counterEvents)
        {
            string name("");
            getline(readName, name);
            string dates;
            readDates >> dates;
            arrayName[i] = name;
            arrayDates[i] = dates;
            i++;
        }
        readName.close();
        readDates.close();
    }
    for (int i = 0; i < counterEvents; i++)
    {
        for (int j = i + 1; j < counterEvents; j++)
        {
            if(startBeforeEnd (arrayDates[j], arrayDates[i]) == true)
            {
                string date = arrayDates[j];
                arrayDates[j] = arrayDates[i];
                arrayDates[i] = date;
                string name = arrayName[j];
                arrayName[j] = arrayName[i];
                arrayName[i] = name;
            }
        }
    }
    for (int i = 0; i < counterEvents;)
    {
        int br=1;
        for (int j = i + 1; j < counterEvents; j++)
        {
            if (arrayDates[i] == arrayDates[j])
            {
                br++;
            }
            else
            {
                break;
            }
        }
        if (br > 1)
        {
            string array[br];
            for (int q = i, s = 0; q < i + br; q++, s++)
            {
                array[s] = arrayName[q];
            }
            for (int s = 0; s < br; s++)
            {
                for (int t = s + 1; t < br; t++)
                {
                    if(array[s] > array[t])
                    {
                        //swapping names
                        string temp = array[s];
                        array[s] = array[t];
                        array[t] = temp;
                    }
                }
            }
            for (int q = i, s = 0; q < i + br; q++, s++)
            {
                arrayName[q] = array[s];
            }
            i = i + br;
        }
        else
        {
            i++;
        }
    }
    //arrais into files
    ofstream writeName, writeDates;
    writeName.open ("eventNamePeriods.txt", ios ::out);
    writeDates.open ("eventStartPeriods.txt", ios ::out);
    int p = 0;
    if (writeName.is_open() && writeDates.is_open())
    {
        while (p < counterEvents)
        {
            writeName << arrayName[p] << endl;
            writeDates << arrayDates[p] << endl;
            p++;
        }
        writeName.close();
        writeDates.close();
    }
}

//function adding event
void addEvent (string event, string start, string end)
{
    ofstream newEvent;
    if (start == end)
    {
        newEvent.open ("eventWholeInf.txt", ios ::app);
        if (newEvent.is_open())
        {
            newEvent << event << " (" << start << ")" << endl;
            newEvent.close();
        }
        newEvent.open ("eventStartPeriods.txt", ios ::app);
        if (newEvent.is_open())
        {
            newEvent << start << endl;
            newEvent.close();
        }
        newEvent.open ("eventNamePeriods.txt", ios ::app);
        if (newEvent.is_open())
        {
            newEvent << event << endl;
            newEvent.close();
        }
        int counterEvents;
        ifstream numEvents;
        numEvents.open ("numEventsPeriods.txt", ios ::in);
        if (numEvents.is_open())
        {
            string temp;
            numEvents >> temp;
            counterEvents = stoi(temp);
            numEvents.close();
        }
        ofstream newNumEvents;
        newNumEvents.open ("numEventsPeriods.txt", ios ::out);
        if (newNumEvents.is_open())
        {
            counterEvents++;
            newNumEvents << counterEvents;
            newNumEvents.close();
        }
    }
    else 
    {
        newEvent.open ("eventWholeInf.txt", ios ::app);
        if (newEvent.is_open())
        {
            newEvent << event << " (" << start <<  " - " << end << ")" << endl;
            newEvent.close();
        }
        //saving the new number of the events (-1)
        int counterEvents;
        ifstream numEvents;
        numEvents.open ("numEventsPeriods.txt", ios ::in);
        if (numEvents.is_open())
        {
            string temp;
            numEvents >> temp;
            counterEvents = stoi (temp);
            numEvents.close();
        }
            
        string date = start;
        ofstream newDate;
        newEvent.open ("eventNamePeriods.txt", ios ::app);
        newDate.open ("eventStartPeriods.txt", ios ::app);
        if (newEvent.is_open() && newDate.is_open())
        {
            while (date != end)
            {
                newEvent << event << endl;
                newDate << date << endl;
                int day, month, year;
                char days[2] = {date[0], date[1]};
                char monthYear[7] = {date[3], date[4], date[5], date[6], date[7], date[8], date[9]};
                day = dayNum (days);
                month = monthNum (monthYear);
                year = yearNum (monthYear);
                int pr = month-1;
                int r = numberOfDays (pr, year);
                if (day == r)
                {
                    if (month == 12)
                    {
                        date = todayTomorrowIntoString (1, 1, year+1);
                    }
                    else
                    {
                        date = todayTomorrowIntoString (1, month+1, year);
                    }
                }
                else
                {
                    date = todayTomorrowIntoString (day+1, month, year);
                }
                counterEvents++;
            }
            newDate << end << endl;
            newEvent << event << endl;
            
            newEvent.close();
            newDate.close();
        }
        ofstream newNumEvents;
        newNumEvents.open ("numEventsPeriods.txt", ios ::out);
        if (newNumEvents.is_open())
        {
            counterEvents++;
            newNumEvents << counterEvents;
            newNumEvents.close();
        }

    }
    newEvent.open ("eventName.txt", ios ::app);
    if (newEvent.is_open())
    {
        newEvent << event << endl;
        newEvent.close();
    }
    newEvent.open ("eventStart.txt", ios ::app);
    if (newEvent.is_open())
    {
        newEvent << start << endl;
        newEvent.close();
    }
}

//function removing event
void removeEvent (string event)
{
    int counterEvents;
    ifstream numEvent;
    numEvent.open ("numberEvents.txt", ios ::in);
    if (numEvent.is_open())
    {
        string temp;
        numEvent >> temp;
        counterEvents = stoi(temp);
        numEvent.close();
    }
    ifstream readName, readWhole, readDates;
    string arrayWhole[counterEvents];
    string arrayName[counterEvents];
    string arrayDates[counterEvents];
    //saving all evets from eventName (whithout the one we want to delete) in an array
    readName.open ("eventName.txt", ios ::in);
    readWhole.open ("eventWholeInf.txt", ios ::in);
    readDates.open ("eventStart.txt", ios ::in);
    int i=0;
    if (readName.is_open() && readWhole.is_open() && readDates.is_open())
    {
        while (i < counterEvents)
        {
            string name("");
            getline(readName, name);
            string wholeInf("");
            getline(readWhole, wholeInf);
            string dates("");
            getline(readDates, dates);
            if(name != event)
            {
                arrayName[i] = name;
                arrayWhole[i] = wholeInf;
                arrayDates[i] = dates;
                i++;
            }
            else
            {
                counterEvents--;
            }
        }
        readName.close();
        readWhole.close();
        readDates.close();
    }

    //empting eventName and saving the elements from the array in it
    ofstream writeName, writeWhole, writeDates;
    writeName.open ("eventName.txt", ios ::out);
    writeWhole.open ("eventWholeInf.txt", ios ::out);
    writeDates.open ("eventStart.txt", ios ::out);
    int p = 0;
    if (writeName.is_open() && writeWhole.is_open() && writeDates.is_open())
    {
        while (p < i)
        {
            writeName << arrayName[p] << endl;
            writeWhole << arrayWhole[p] << endl;
            writeDates << arrayDates[p] << endl;
            p++;
        }
        writeName.close();
        writeWhole.close();
        writeDates.close();
    }


    //saving the new number of the events (-1)
    int counter;
    ifstream numEvents;
    numEvents.open ("numEventsPeriods.txt", ios ::in);
    if(numEvents.is_open())
    {
        string temp;
        numEvents >> temp;
        counter = stoi (temp);
        numEvents.close();
    }
    string nPeriods[counter];
    string dPeriods[counter];
    ifstream nRead, dRead;
    nRead.open ("eventNamePeriods.txt", ios ::in);
    dRead.open ("eventStartPeriods.txt", ios ::in);
    int t = 0;
    if (nRead.is_open() && dRead.is_open())
    {
        while (t < counter)
        {
            string name("");
            getline(nRead, name);
            string date("");
            getline(dRead, date);
            if (name != event)
            {
                nPeriods[t] = name;
                dPeriods[t] = date;
                t++;
            }
            else
            {
                counterEvents--;
            }
        }
        nRead.close();
        dRead.close();
    }
    //empting eventName and saving the elements from the array in it
    ofstream nWrite, dWrite;
    nWrite.open ("eventNamePeriods.txt", ios ::out);
    dWrite.open( "eventStartPeriods.txt", ios ::out);
    int q = 0;
    if (nWrite.is_open() && dWrite.is_open())
    {
        while (q < t)
        {
            nWrite << nPeriods[q] << endl;
            dWrite << dPeriods[q] << endl;
            q++;
        }
        nWrite.close();
        dWrite.close();
    }
    ofstream newNumEvents;
    newNumEvents.open ("numEventsPeriods.txt", ios ::out);
    if(newNumEvents.is_open())
    {
        t--;
        newNumEvents << t;
        newNumEvents.close();
    }

}

//function finding the events today/tomorrow
void eventsTodayTomorrow()
{
    string today = todayTomorrowIntoString (DATE, MONTH, YEAR), tomorrow;
    int pr = MONTH-1;
    int r = numberOfDays (pr, YEAR);
    if (DATE == r)
    {
        if (MONTH == 12)
        {
            tomorrow = todayTomorrowIntoString (1, 1, YEAR+1);
        }
        else
        {
            tomorrow = todayTomorrowIntoString (1, MONTH+1, YEAR);
        }
    }
    else
    {
        tomorrow = todayTomorrowIntoString (DATE+1, MONTH, YEAR);
    }
    int countToday=0, countTomorrow=0;
    //counting the number of events
    int counterEvents;
    ifstream numEvents;
    numEvents.open ("numEventsPeriods.txt", ios ::in);
    if (numEvents.is_open())
    {
        string temp;
        numEvents >> temp;
        counterEvents = stoi (temp);
        numEvents.close();
    }
    ifstream read;
    read.open ("eventStartPeriods.txt", ios ::in);
    if (read.is_open())
    {
        string date;
        int i = 0;
        while (i < counterEvents)
        {
            read >> date;
            if (date == today)
            {
                countToday++;
            }
            else if (date == tomorrow)
            {
                countTomorrow++;
            }
            i++;
        }
        read.close();
    }
    if (countToday != 0)
    {
        ifstream readEvent;
        read.open ("eventStartPeriods.txt", ios ::in);
        readEvent.open ("eventNamePeriods.txt", ios ::in);
        if (read.is_open() && readEvent.is_open())
        {
            int i = 1;
            cout << "Events today:" << endl;
            while (!read.eof())
            {
                string date;
                read >> date;
                string event("");
                getline(readEvent, event);
                if (date == today)
                {
                    cout << i << ". " << event << endl;
                    i++;
                }
            }
            read.close();
            readEvent.close();
        }
    }
    else
    {
        if (countTomorrow == 1)
        {
            cout << "You have 1 event tomorrow." << endl;
        }
        else
        {
            cout << "You have " << countTomorrow << " events tomorrow." << endl;
        }
    }
}
//function finding which day of the event is
string whichDay (int position, string event)
{
    //finding the num of events
    int counterEvents;
    ifstream numEvent;
    numEvent.open ("numEventsPeriods.txt", ios ::in);
    if (numEvent.is_open())
    {
        string temp;
        numEvent >> temp;
        counterEvents = stoi (temp);
        numEvent.close();
    }
    //saving the events from the files in arrais
    ifstream readName, readDates;
    string arrayName[counterEvents];
    readName.open ("eventNamePeriods.txt", ios ::in);
    int p=0;
    if (readName.is_open())
    {
        while (p < counterEvents)
        {
            string name("");
            getline(readName, name);
            arrayName[p] = name;
            p++;
        }
        readName.close();
    }
    int eventsBefore=0, eventsAfter=0, allEvents=0;
    for (int i = 0; i < position; i++)
    {
        if (arrayName[i] == event)
        {
            eventsBefore++;
        }
    }
    for (int i = position+1; i < counterEvents; i++)
    {
        if (arrayName[i] == event)
        {
            eventsAfter++;
        }
    }
    allEvents = 1 + eventsBefore + eventsAfter;
    if (allEvents == 1)
    {
        return " ";
    }
    else
    {
        return "(Day " + to_string (eventsBefore + 1) + "/" + to_string (allEvents) + ")";
    }

}
//function for choice 3
void printEventsForMonth (int month, int year)
{
    int days = numberOfDays (month-1, year);
    //counting the number of events
    int count;
    ifstream numEvents;
    numEvents.open ("numEventsPeriods.txt", ios ::in);
    if (numEvents.is_open())
    {
        string temp;
        numEvents >> temp;
        count = stoi (temp);
        numEvents.close();
    }
    for (int i = 1; i <= days; i++)
    {
        string today = todayTomorrowIntoString (i,month, year);
        ifstream readDate, readName;
        readDate.open ("eventStartPeriods.txt", ios ::in);
        readName.open ("eventNamePeriods.txt", ios ::in);
        if (readDate.is_open() && readName.is_open())
        {
            string date, newDate;
            string name("");
            int p = 0;
            while (p < count)
            {
                readDate >> date;
                getline (readName, name);
                if (date == today)
                {
                    if (date==newDate)
                    {
                        cout << "           " << name << "   " << whichDay(p,name)<< endl;
                    }
                    else
                    {
                        string currentDay;
                        ifstream dayOfTheWeek;
                        dayOfTheWeek.open ("dayOfTheWeek.txt", ios ::in);
                        if (dayOfTheWeek.is_open())
                        {
                            dayOfTheWeek >> currentDay;
                            dayOfTheWeek.close();
                        }
                        string nameDay;
                        if (currentDay == "Sun")
                        {
                            nameDay = daysNames[dayNumber (i, month, year)];
                        }
                        else
                        {
                            nameDay = daysNamesMon[dayNumberMon (i, month, year)];
                        }
                        cout <<  nameDay << ", " << setw (3) << i << "   " << name << "   " << whichDay (p,name)<< endl;
                    }

                }
                newDate = date;
                p++;
            }
            readDate.close();
            readName.close();
        }
    }
}

int main ()
{
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    Asctime (timeinfo);

    //events today or tomorrow
    eventsTodayTomorrow();

    //menu
    cout << endl << "Choose an option:" << endl;
    cout << "     1. Show calendar" << endl;
    cout << "     2. Show schedule" << endl;
    cout << "     3. List events" << endl;
    cout << "     4. Add event" << endl;
    cout << "     5. Remove event" << endl;
    cout << "     6. Set first weekday" << endl;
    cout << endl << "Enter your choice: ";
    //checking the choice
    int choice;
    cin >> choice;

    //Show calendar
    if (choice == 1)
    {
        cout << "Enter month (MM/YYYY): ";
        char printMonth[7];
        cin >> printMonth;
        int month = monthNum (printMonth);
        if (month > 0 && month < 13)
        {
            string currentDay;
            ifstream currentD;
            currentD.open ("dayOfTheWeek.txt", ios ::in);
            if (currentD.is_open())
            {
                while (!currentD.eof())
                {
                    currentD >> currentDay;
                }
                currentD.close();
            }
            int year = yearNum (printMonth);
            if (currentDay == "Sun")
            {
                printCalendarSun (month, year);
            }
            else if (currentDay== "Mon")
            {
                printCalendarMon (month, year);
            }
        }
        else
        {
            cout << "Invalid month!"<< endl;;
        }
    }

    //Show schedule
    else if (choice == 2)
    {
        //counting the number of events
        int counterEvents;
        ifstream numEvents;
        numEvents.open ("numberEvents.txt", ios ::in);
        if(numEvents.is_open())
        {
            string temp;
            numEvents >> temp;
            counterEvents = stoi (temp);
            numEvents.close();
        }
        if (counterEvents == 0)
        {
            cout << "There is no events!" << endl;
        }
        else
        {
            ifstream allEvents;
            cout << "You have the following events:" << endl;
            allEvents.open ("eventWholeInf.txt", ios ::in);
            if (allEvents.is_open())
            {
                int i = 1;
                while (i <= counterEvents) 
                {
                    string p("");
                    getline (allEvents, p);
                    cout << i << ". " << p << endl;
                    i++;
                }
                allEvents.close();
            }
        }
    }

    //List events
    else if (choice == 3)
    {
        cout << "Enter month (MM/YYYY): ";
        char date[7];
        cin >> date;
        int month = monthNum(date);
        if(month > 0 && month < 13)
        {
            int year = yearNum (date);
            cout << endl << getMonthName (month-1) << " " << to_string (year) << endl;
            cout << "------------" << endl;
            printEventsForMonth (month, year);
        }
        else
        {
            cout << "Invalid month!" << endl;
        }

    }

    //Add event
    else if (choice == 4)
    {
        string event;
        cout << "Enter name: ";
        getline (cin>>ws, event);
        if (existingEvent (event) == false)
        {
            string start;
            cout << "Enter start date (DD/MM/YYYY): ";
            cin >> start;
            if (isCorrectDate(start) == true)
            {
                string end;
                cout << "Enter end date (DD/MM/YYYY): ";
                cin >> end;
                if (isCorrectDate(end) == true)
                {
                    if (startBeforeEnd (start, end))
                    {
                        addEvent (event, start, end);
                        //saving the new number of the events (+1)
                        int counterEvents;
                        ifstream numEvents;
                        numEvents.open ("numberEvents.txt", ios ::in);
                        if (numEvents.is_open())
                        {
                            string temp;
                            numEvents >> temp;
                            counterEvents = stoi (temp);
                            numEvents.close();
                        }
                        ofstream newNumEvents;
                        newNumEvents.open ("numberEvents.txt", ios ::out);
                        if (newNumEvents.is_open())
                        {
                            counterEvents++;
                            newNumEvents << counterEvents;
                            newNumEvents.close();
                        }
                        sortFiles();
                        sortFilesPeriods();
                        cout << endl << "Event added successfully!" << endl;
                    }
                    else
                    {
                        cout << "Incorrect date!" << endl;
                    }
                }
                else
                {
                    cout << "Incorrecct date!" << endl;
                }
            }
            else
            {
                cout << "Incorrect date!" << endl;
            }
        }
        else
        {
            cout << "There is already such event!" << endl;
        }

    }

    //Remove event
    else if (choice == 5)
    {
        cout << "Enter name: ";
        string eventDelete("");
        getline(cin>>ws,eventDelete);
        if (existingEvent (eventDelete) == true)
        {
            removeEvent (eventDelete);
            //saving the new number of the events (-1)
            int counterEvents;
            ifstream numEvents;
            numEvents.open ("numberEvents.txt", ios ::in);
            if (numEvents.is_open())
            {
                string temp;
                numEvents >> temp;
                counterEvents = stoi (temp);
                numEvents.close();
            }
            ofstream newNumEvents;
            newNumEvents.open ("numberEvents.txt", ios ::out);
            if (newNumEvents.is_open())
            {
                counterEvents--;
                newNumEvents << counterEvents;
                newNumEvents.close();
            }
            cout << endl << "Event deleted successfully!" << endl;
        }
        else
        {
            cout << "There is no such event!"<< endl;
        }
        
    }

    // Set first weekday
    else if (choice == 6)
    {
        string currentDay;
        ifstream dayOfTheWeek;
        dayOfTheWeek.open ("dayOfTheWeek.txt", ios ::in);
        if (dayOfTheWeek.is_open())
        {
            dayOfTheWeek >> currentDay;
            dayOfTheWeek.close();
        }
        cout << "The first day of the week is currently " << currentDay << "."<< endl;
        cout << endl << "Enter new (Mon/Sun): ";
        cin >> currentDay;
        if (currentDay == "Sun" || currentDay == "Mon")
        {
            ofstream newDayOfTheWeek;
            newDayOfTheWeek.open ("dayOfTheWeek.txt", ios ::out);
            if (newDayOfTheWeek.is_open())
            {
                newDayOfTheWeek << currentDay;
                newDayOfTheWeek.close();
            }
            cout << "Saved!" << endl;
        }
        else
        {
            cout << "Invalid day!" << endl;
        }

    }
    else
    {
        cout << "There is no such choice!"<< endl;
    }
}

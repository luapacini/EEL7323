#include <iostream>
#include "clockCalendar.h"

using namespace std;

Clock::Clock (int h, int s, int m, int pm){
    hr = h;
    min = m;
    sec = s;
    isPm = pm;
}

void Clock::setClock (int h, int m, int s, int pm){
    hr = h;
    min = m;
    sec = s;
    isPm = pm;
}

void Clock::readClock (int& h, int& m, int& s, int& pm){
    h = hr;
    m = min;
    s = sec;
    pm = isPm;
}

void Clock::advance (){
    if (sec < 59)
        sec++;
    else {
        sec = 0;
        if (min < 59)
            min++;
        else {
            min = 0;
            if (hr < 12)
                hr++;
            else {
                hr = 0;
            }
        }
    }
}

Calendar::Calendar (int m, int d, int y){
    mo = m;
    day = d;
    yr = y;
}

void Calendar::setCalendar (int m, int d, int y){
    mo = m;
    day = d;
    yr = y;
}

void Calendar::readCalendar (int& m, int& d, int& y){
    m = mo;
    d = day;
    y = yr;
}

ClockCalendar::ClockCalendar (int mt, int d, int y, int h, int m, int s, int pm) : Clock (h, m, s, pm), Calendar (mt, d, y){
}

void ClockCalendar::advance (){ // avancar o calendario, caso o clock
   int wasPm = isPm;       // mude de AM para PM.
   Clock::advance();
   if (wasPm && !isPm)
      Calendar::advance();
}

// int main(){

//    int h, m, s, pm;

//    ClockCalendar cc(0, 0, 0, 0, 0, 0, 0);
   
//    cc.setClock (11, 59, 58, 0);
   
//    cc.readClock (h, m, s, pm);
//    cout << h << ":" << m << ":" << s << " " << (pm ? "pm" : "am") << endl;
//    for (int i = 0; i < 5000; i++)
//       cc.advance();
   
//    cc.readClock (h, m, s, pm);
   
//    cout << h << ":" << m << ":" << s << " " << (pm ? "pm" : "am") << endl;

// }

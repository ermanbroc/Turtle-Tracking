//
// Nate Burns
// 
// Time and Date Setting Code
//
// Corrects the time and date from standardized satellite time to account for leap years, daylights savings time, time zones
//

void Get_TaD() {                                 // Getting correct time and date
  if (hour_act < 0) {                       
    hour_act = hour_act + 24;                   // Account for 12 am to 5 am
    day_act = day_act - 1;                      // Go back a day
    get_date_from_month();                      // Setting date, month, year
  }
  check_DST();
  if (DST == 1) { hour_act = hour_act + 1; }    // Accounting for daylight savings time for next 10 years
}

void get_date_from_month(void){
    if (day_act <= 0){
      month_act = month_act - 1;                // If going back a day sends you to previous month, account for this
      if (month_act < 1) {
        month_act = 12;                         // If gone back from January, make december and below, go back year
        year_act = year_act - 1;
      }
      switch (month_act) {                      // Setting what date to go to based on month
        case 1:                                 // Could insert DST here
          day_act = 31;
          break;
        case 2:
          if ((year_act == 28) || (year_act == 32) || (year_act == 36) || (year_act == 40) || (year_act == 44) || (year_act == 48)) {     // Leap year for next 6 occasions
            day_act = 29;
          } else day_act = 28;
          break;
        case 3:
          day_act = 31;
          break;
        case 4:
          day_act = 30;
          break;
        case 5:
          day_act = 31;
          break;
        case 6:
          day_act = 30;
          break;
        case 7:
          day_act = 31;
          break;
        case 8:
          day_act = 31;
          break;
        case 9:
          day_act = 30;
          break;
        case 10:
          day_act = 31;
          break;
        case 11:
          day_act = 30;
          break;
        case 12:
          day_act = 31;
          break;
        default:
          day_act = day_act;
          break;
      }
    } else day_act = day_act;
}

void check_DST(void){
  switch (year_act) {
    case 25:
      if ((month_act > 3 && month_act < 11) ||                                  // Between April and October
        (month_act == 3 && (day_act > 9 || (day_act == 9 && hour_act >= 2))) || // March 9, 2:00 AM or later
        (month_act == 11 && (day_act < 2 || (day_act == 2 && hour_act < 2)))) { // Before November 2, 2:00 AM
          DST = 1;                                                              // Daylight Saving Time is active
      } else {
          DST = 0;                                                              // Standard Time
        }
      break;
    case 26:
      if ((month_act > 3 && month_act < 11) ||                                  // Between April and October
        (month_act == 3 && (day_act > 8 || (day_act == 8 && hour_act >= 2))) || // March 9, 2:00 AM or later
        (month_act == 11 && (day_act < 1 || (day_act == 1 && hour_act < 2)))) { // Before November 2, 2:00 AM
          DST = 1;                                                              // Daylight Saving Time is active
      } else {
          DST = 0;                                                              // Standard Time
        }
      break;
    case 27:
      if ((month_act > 3 && month_act < 11) ||                                    // Between April and October
        (month_act == 3 && (day_act > 14 || (day_act == 14 && hour_act >= 2))) || // March 9, 2:00 AM or later
        (month_act == 11 && (day_act < 7 || (day_act == 7 && hour_act < 2)))) {   // Before November 2, 2:00 AM
          DST = 1;                                                                // Daylight Saving Time is active
      } else {
          DST = 0;                                                                // Standard Time
        }
      break;
    case 28:
      if ((month_act > 3 && month_act < 11) ||                                    // Between April and October
        (month_act == 3 && (day_act > 12 || (day_act == 12 && hour_act >= 2))) || // March 9, 2:00 AM or later
        (month_act == 11 && (day_act < 5 || (day_act == 5 && hour_act < 2)))) {   // Before November 2, 2:00 AM
          DST = 1;                                                                // Daylight Saving Time is active
      } else {
          DST = 0;                                                                // Standard Time
        }
      break;
    case 29:
      if ((month_act > 3 && month_act < 11) ||                                    // Between April and October
        (month_act == 3 && (day_act > 11 || (day_act == 11 && hour_act >= 2))) || // March 9, 2:00 AM or later
        (month_act == 11 && (day_act < 4 || (day_act == 4 && hour_act < 2)))) {   // Before November 2, 2:00 AM
          DST = 1;                                                                // Daylight Saving Time is active
      } else {
          DST = 0;                                                                // Standard Time
        }
      break;
    case 30:
      if ((month_act > 3 && month_act < 11) ||                                    // Between April and October
        (month_act == 3 && (day_act > 10 || (day_act == 10 && hour_act >= 2))) || // March 9, 2:00 AM or later
        (month_act == 11 && (day_act < 3 || (day_act == 3 && hour_act < 2)))) {   // Before November 2, 2:00 AM
          DST = 1;                                                                // Daylight Saving Time is active
      } else {
          DST = 0;                                                                // Standard Time
        }
      break;
    case 31:
      if ((month_act > 3 && month_act < 11) ||                                    // Between April and October
        (month_act == 3 && (day_act > 9 || (day_act == 9 && hour_act >= 2))) ||   // March 9, 2:00 AM or later
        (month_act == 11 && (day_act < 2 || (day_act == 2 && hour_act < 2)))) {   // Before November 2, 2:00 AM
          DST = 1;                                                                // Daylight Saving Time is active
      } else {
          DST = 0;                                                                // Standard Time
        }
      break;
    case 32:
      if ((month_act > 3 && month_act < 11) ||                                    // Between April and October
        (month_act == 3 && (day_act > 14 || (day_act == 14 && hour_act >= 2))) || // March 9, 2:00 AM or later
        (month_act == 11 && (day_act < 7 || (day_act == 7 && hour_act < 2)))) {   // Before November 2, 2:00 AM
          DST = 1;                                                                // Daylight Saving Time is active
      } else {
          DST = 0;                                                                // Standard Time
        }
      break;
    case 33:
      if ((month_act > 3 && month_act < 11) ||                                    // Between April and October
        (month_act == 3 && (day_act > 13 || (day_act == 13 && hour_act >= 2))) || // March 9, 2:00 AM or later
        (month_act == 11 && (day_act < 6 || (day_act == 6 && hour_act < 2)))) {   // Before November 2, 2:00 AM
          DST = 1;                                                                // Daylight Saving Time is active
      } else {
          DST = 0;                                                                // Standard Time
        }
      break;
    case 34:
      if ((month_act > 3 && month_act < 11) ||                                    // Between April and October
        (month_act == 3 && (day_act > 12 || (day_act == 12 && hour_act >= 2))) || // March 9, 2:00 AM or later
        (month_act == 11 && (day_act < 5 || (day_act == 5 && hour_act < 2)))) {   // Before November 2, 2:00 AM
          DST = 1;                                                                // Daylight Saving Time is active
      } else {
          DST = 0;                                                                // Standard Time
        }
      break;
    case 35:
      if ((month_act > 3 && month_act < 11) ||                                    // Between April and October
        (month_act == 3 && (day_act > 11 || (day_act == 11 && hour_act >= 2))) || // March 9, 2:00 AM or later
        (month_act == 11 && (day_act < 4 || (day_act == 4 && hour_act < 2)))) {   // Before November 2, 2:00 AM
          DST = 1;                                                                // Daylight Saving Time is active
      } else {
          DST = 0;                                                                // Standard Time
        }
      break;
    default:
      DST = 0;
      break;
  }
}

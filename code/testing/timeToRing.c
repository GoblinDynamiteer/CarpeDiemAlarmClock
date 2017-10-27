#include <stdio.h>
#include <stdlib.h>

/* Time right now */
int alarmHour = 1;
int alarmMinute = 30;

int timeTo(int nowHour, int nowMinute)
{
  /* Something to get hours and minutes left */
  int nowTot_min = nowHour * 60 + nowMinute;
  int alarmTot_min = alarmHour * 60 + alarmMinute;
  
  int dif = alarmTot_min - nowTot_min;
  
  if(dif < 0)
  {
	  return 24 * 60 + dif;
  }
  
  return dif;
}

int main()
{
  printf("Minutes left to the alarm: %d", timeTo(23, 30));
}


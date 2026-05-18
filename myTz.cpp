#include "_m5Core2-only.h"

#include <myTz.h>

// US Eastern Time Zone (New York, Detroit)
TimeChangeRule usEDT = {"EDT", Second, Sun, Mar, 2, -240};	// UTC - 4 hours
TimeChangeRule usEST = {"EST", First, Sun, Nov, 2, -300};	// UTC - 5 hours

//---------------------------
#include <TinyGPS++.h>
#include <MultipleSatellite.h>

extern MultipleSatellite gpsM5;

#define CalendarYrToTm(Y) ((Y) - 1970)

uint16_t yearNow;
uint8_t  monthNow;
uint8_t  dayNow;
uint8_t  hourNow;
uint8_t  minuteNow;
uint8_t  secondNow;
uint32_t epochTimeNow;

uint32_t getEpochTimeFromGPS() 
{
    // 1. Extract individual pieces of date/time from TinyGPS++
    yearNow 	= gpsM5.date.year();
    monthNow 	= gpsM5.date.month();
    dayNow 	= gpsM5.date.day();
    hourNow 	= gpsM5.time.hour();
    minuteNow  = gpsM5.time.minute();
    secondNow  = gpsM5.time.second();

    // 2. Format into the standard tmElements_t structure
    // Note: Weekday can be calculated or set to 0 as a dummy value

    tmElements_t tm;
    
    tm.Year 	= CalendarYrToTm(yearNow); // Converts e.g., 2026 to 56
    tm.Month 	= monthNow;
    tm.Day 		= dayNow;
    tm.Hour 	= hourNow;
    tm.Minute 	= minuteNow;
    tm.Second 	= secondNow;

    // 3. Convert to UNIX epoch time (seconds since 1/1/1970)
    epochTimeNow = (uint32_t) makeTime(tm);

    //Serial.print("Current Epoch Time: ");
    //Serial.println(epochTime);
   
    return epochTimeNow;
    
}
//---------------------------
char *getHHMMSS(uint32_t utc)
{
	static char msg[70];
	Timezone usEastern(usEDT, usEST);  // setup dst and timezone recipes

    time_t local = usEastern.toLocal(utc);
    
	struct tm *remote ;
	remote = localtime( &local );

	strftime(msg, sizeof(msg), "%I:%M:%S", remote);
	return msg;
}
//---------------------------

char *getHHMM(uint32_t utc)
{
	static char msg[70];
	Timezone usEastern(usEDT, usEST);  // setup dst and timezone recipes

    time_t local = usEastern.toLocal(utc);
    
	struct tm *remote ;
	remote = localtime( &local );

	strftime(msg, sizeof(msg), "%I:%M", remote);
	return msg;
}

char *getHHMMSSapm(uint32_t utc)
{
	static char msg[70];
	Timezone usEastern(usEDT, usEST);  // setup dst and timezone recipes

    time_t local = usEastern.toLocal(utc);
    
	struct tm *remote ;
	remote = localtime( &local );

	strftime(msg, sizeof(msg), "%I:%M:%S %p", remote);
	return msg;
}


char *getHHMMapm(uint32_t utc)
{
	static char msg[70];
	Timezone usEastern(usEDT, usEST);  // setup dst and timezone recipes

    time_t local = usEastern.toLocal(utc);
    
	struct tm *remote ;
	remote = localtime( &local );

	strftime(msg, sizeof(msg), "%I:%M%p", remote);
	return msg;
}

char *getDDMMYY(uint32_t utc)
{
	static char msg[70];
	Timezone usEastern(usEDT, usEST);  // setup dst and timezone recipes

    time_t local = usEastern.toLocal(utc);
    
	struct tm *remote ;
	remote = localtime( &local );

	//https://www.geeksforgeeks.org/cpp/strftime-function-in-c/

	strftime(msg, sizeof(msg), "%d/%b/%y", remote);
	return msg;
}



char *autoFILENAME(char*prefix, char *ext )
{
	uint32_t utc = getEpochTimeFromGPS();
	static char retval[70];
	char msg[70];
	Timezone usEastern(usEDT, usEST);  // setup dst and timezone recipes

    time_t local = usEastern.toLocal(utc);
    
	struct tm *remote ;
	remote = localtime( &local );

	strftime(msg, sizeof(msg), "%y%m%d", remote);  // all numbers yymmdd

	snprintf(retval, sizeof(retval),  "%s%X.%s", prefix, atoi(msg), ext);
	return retval;
}



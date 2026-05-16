#ifndef __MYTZ
#define __MYTZ

#include <Timezone.h>
#include <TimeLib.h> // Or <Time.h>

char *getHHMM(uint32_t utc);
char *getHHMMSS(uint32_t utc);

char *getHHMMapm(uint32_t utc);
char *getHHMMSSapm(uint32_t utc);

char *getDDMMYY(uint32_t utc);
uint32_t getEpochTimeFromGPS();

char *autoFILENAME(char *prefix, char *ext );


#endif

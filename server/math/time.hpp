#ifndef TIME
#define TIME

const float BLOCKS_PER_SECOND = 1;
const float SECONDS_PER_BLOCK = 1 / BLOCKS_PER_SECOND;

double                  now();
void                    sleep(int len); // miliseconds

typedef	double			Seconds;

#endif // TIME

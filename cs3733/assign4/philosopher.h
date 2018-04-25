void creatPhilosophers(int nthreads);
void thinking();
void pickUpChopsticks(int threadIndex);
void eating();
void putDownChopsticks(int threadIndex);

typedef struct ti
{
    int n;
    int first;
    int out_flag;
    int result;
} *thread_info_t, ti;

typedef struct tiArr
{
    int size;
    thread_info_t *arr;
} *tInfoArr, tiArr;
 #define READY 0
 #define RUNNING 1
 #define WAITING 2
 #define DONE 3

typedef char *string;

void part0(string s1, string s2); 
void display(string heading, string s1, string s2);
void fcfs(string s1, string s2, int x1, int y1, int z1, int x2, int y2, int z2);
void sjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2);
void psjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2);
void rr(char *s1, char *s2, int quantum, int x1, int y1, int z1, int x2, int y2, int z2);
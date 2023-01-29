#include<stdio.h>
#include<time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// starting from zero
#define MIN 0
 
// 1 hr= 60 min ; 1 min= 60 sec
#define MAX 60
 
#define MILLI 200000
 
int i, j, k, n, s;
char c;
pthread_t t1;

int keyboardhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
 
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
    ch = getchar();
 
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
 
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
 
    return 0;
}

void alarmdef(){
    printf("Tell the time for going off\nHours Minutes Seconds seperated :");
    int h,m,s;
    scanf("%d %d %d",&h,&m,&s);
    while(1){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int a=tm.tm_hour,b=tm.tm_min,c=tm.tm_sec;
    if(a<h||b<m||c<s){
        printf("\rThe time now is %02d:%02d:%02d",a,b,c);
        fflush(stdout);
    }else{
        break;
    }
    } printf("\nThe alarm went off");
}
void timerdef(){
    printf("Set a timer of\nHours Minutes Seconds seperated :");
    int hour,minute,second;
    scanf("%d %d %d",&hour,&minute,&second);
    while(1) {
        second--;
        if(second < 0) {
            minute -= 1;
            second = 59;
        }
        if(minute < 0) {
            hour -= 1;
            minute = 59;
        }
        if(hour < 0) {
            hour = 0;
            minute = 59;
            second = 59;
        }
        fflush(stdout);
        printf("\r %02d : %02d : %02d ",hour,minute,second);
        sleep(1);
        if(minute==0&&second==0&&hour==0){
            break;
        }
        
   }
   printf("\nThe time has ended");
   
}
void stopwatchdef(){
    int hour=0,minute=0,second=0,i=0;
    int a[100][4];
    char *b,*x="x",*m="p";
    printf("Press enter to note the time\n");
    while(1){
        second++;
        if(second>59){
            minute += 1;
            second =0;
        }
        if(minute>59){
            hour +=1;
            minute=0;
        }
        fflush(stdout);
        printf("\r %02d : %02d : %02d ",hour,minute,second);
       
        sleep(1);
    }
    printf("The noted time is %02d : %02d : %02d ",hour,minute,second);
}

void timenow()
{
    while(1){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\rDate and time: %d-%02d-%02d %02d:%02d:%02d",tm.tm_mday, tm.tm_mon + 1,tm.tm_year +1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fflush(stdout);
    sleep(1);
}}



int main(){
    printf("Clock\n");
    int c;
    printf("\nEnter the choice:\n1 Show current time\n2 Alarm\n3 Timer\n4 Stopwatch\n\n");
    scanf("%d",&c);
    switch(c){
        case 1:
        timenow();
        break;
        
        case 2:
        alarmdef();
        break;
        
        case 3:
        timerdef();
        break;
        
        case 4:
        stopwatchdef();
        break;
        
        default:
        printf("Invalid choice !!");
        break;
    }
}


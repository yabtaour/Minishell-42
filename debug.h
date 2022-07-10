#ifndef DEBUG_H
# define DEBUG_H

//fonts color
#define FBLACK      "\033[30m"
#define FRED        "\033[31m"
#define FGREEN      "\033[32m"
#define FYELLOW     "\033[33m"
#define FBLUE       "\033[34m"
#define FPURPLE     "\033[35m"
#define D_FGREEN    "\033[6m"
#define FWHITE      "\033[7m"
#define FCYAN       "\x1b[36m"

//end color
#define NONE        "\033[0m"

# define HERE printf("File [%s%s%s] in Func [%s%s%s] on the Line [%s%d%s]\n",FYELLOW, __FILE__, NONE, FYELLOW, __func__, NONE, FRED, __LINE__, NONE);
# define LEAKS system("leaks minishell");
# define LOOP while(1);
# define PID printf("[procces pid %d]\n", getpid());
# define DATE printf("the current date is %s%s%s\n",FRED, __DATE__, NONE);
# define TIME printf("The current time is %s%s%s\n",FRED, __TIME__, NONE);
# define Warning(...) fprintf(stderr, __VA_ARGS__)
// < ---- MATH ----> 
# define PI 3.14

#endif
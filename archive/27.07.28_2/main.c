
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
int event(void) {
   return (0);
 }
void handler (int status)
{
   rl_replace_line("word",0);
   rl_redisplay();
   rl_done = 1;
}

int main (int argc, char** argv)
{
   char* entry;
   rl_event_hook=event;
   signal(SIGINT,handler);

			while ((entry = readline("> ")) != NULL)
			{
				printf("%s\n", entry);
         }

   printf("\nEnd");
   return 0;
}



// int event(void) {
//    return (0);
//  }
// void handler (int status)
// {
//    rl_replace_line("word",0);
//    rl_redisplay();
//    rl_done = 1;
// }

// int main (int argc, char** argv)
// {
//    char* entry;
//    rl_event_hook=event;
//    signal(SIGINT,handler);
//    entry = readline("");

//    printf("\nEntry was: %s\n", entry);
//    return 0;
// }
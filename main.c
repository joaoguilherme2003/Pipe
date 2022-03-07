#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define QTD_MESSAGES 2

int main() {

   int pipeFileDescriptors[2];
   int returnstatus;
   int pid;
   char writemessages[QTD_MESSAGES][20]={"Maria", "Joao andou a noite"};
   char readmessage[20];

   returnstatus = pipe(pipeFileDescriptors);

   if (returnstatus == -1) {
      printf("Error when create pipe\n");
      return 1;
   }

   pid = fork();
   
   if (pid == 0) {
      read(pipeFileDescriptors[0], readmessage, sizeof(readmessage));
      printf("Processo filho, Lendo do pipe, mensagem 1 é %s\n", readmessage);
      read(pipeFileDescriptors[0], readmessage, sizeof(readmessage));
      printf("Processo filho, Lendo do pipe, mensagem 2 é %s\n", readmessage);
   } else { 
      printf("Processo pai, escrevendo para o pipe, mensagem 1 é %s\n", writemessages[0]);
      write(pipeFileDescriptors[1], writemessages[0], sizeof(writemessages[0]));
      printf("Processo pai, escrevendo para o pipe, mensagem 2 é %s\n", writemessages[1]);
      write(pipeFileDescriptors[1], writemessages[1], sizeof(writemessages[1]));
   }
   return 0;
}

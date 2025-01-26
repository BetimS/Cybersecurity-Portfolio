#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

//accept up to 16 command-line arguments
#define MAXARG 16

//allow up to 64 environment variables
#define MAXENV 64

//keep the last 500 commands in history
#define HISTSIZE 500

//accept up to 1024 bytes in one command
#define MAXLINE 1024

static char **parseCmd(char cmdLine[]) {
  char **cmdArg, *ptr;
  int i;

  //(MAXARG + 1) because the list must be terminated by a NULL ptr
  cmdArg = (char **) malloc(sizeof(char *) * (MAXARG + 1));
  if (cmdArg == NULL) {
    perror("parseCmd: cmdArg is NULL");
    exit(1);
  }
  for (i = 0; i <= MAXARG; i++) //note the equality
    cmdArg[i] = NULL;
  i = 0;
  ptr = strsep(&cmdLine, " ");
  while (ptr != NULL) {
    // (strlen(ptr) + 1)
    cmdArg[i] = (char *) malloc(sizeof(char) * (strlen(ptr) + 1));
    if (cmdArg[i] == NULL) {
      perror("parseCmd: cmdArg[i] is NULL");
      exit(1);
    }
    strcpy(cmdArg[ i++ ], ptr);
    if (i == MAXARG)
      break;
    ptr = strsep(&cmdLine, " ");
  }
  return(cmdArg);
}

int main(int argc, char *argv[], char *envp[]) {
  char cmdLine[MAXLINE], **cmdArg, *history[HISTSIZE];
  int status, i, debug, historySize = 0;
  pid_t pid;
  char *env[MAXENV];
  int k = 0;
  

  debug = 0;
  i = 1;
  while (i < argc) {
    if (! strcmp(argv[i], "-d") )
      debug = 1;
    i++;
  }

  //store env to mem space of code
    while (envp[k] != NULL) {
      env[k] = envp[k];
      k++;
    }
    env[k] = NULL;
  
  while (( 1 )) {
    //char historyLine[MAXLINE];
    printf("bsh> ");                      //prompt
    fgets(cmdLine, MAXLINE, stdin);       //get a line from keyboard
    cmdLine[strlen(cmdLine) - 1] = '\0';  //strip '\n'
    history[historySize] = malloc(MAXLINE);
    strcpy(history[historySize], cmdLine);
    historySize++;
    cmdArg = parseCmd(cmdLine);
    if (debug) {
      i = 0;
      while (cmdArg[i] != NULL) {
	printf("\t%d (%s)\n", i, cmdArg[i]);
	i++;
      }
    }

    //store env to mem space of code
    if(env[0] == NULL){
    while (envp[k] != NULL) {
      env[k] = envp[k];
      k++;
    }
    env[k] = NULL;
    }

    //built-in command exit
    if (strcmp(cmdArg[0], "exit") == 0) {
      if (debug)
	printf("exiting\n");
      break;
    }
    //built-in command env
    else if (strcmp(cmdArg[0], "env") == 0) {
      for(i = 0; i < k; i++){
	printf("%s\n", env[i]);
      }
    }
    //built-in command setenv
    else if (strcmp(cmdArg[0], "setenv") == 0) {
      char str[MAXLINE], *envTemp, tempString[MAXLINE], *split;
      int flag = 0;
      
      strcpy(str, cmdArg[1]);
      strcat(str, "=");
      strcat(str, cmdArg[2]);
      
      for(i = 0; i < k; i++) {
	strcpy(tempString, env[i]);
	split = tempString;
	envTemp = strsep(&split, "=");
	if((strcmp(envTemp, cmdArg[1])) == 0){
	  env[i] = malloc(sizeof(str) + 1);
	  strcpy(env[i], str);
	  flag = 1;
	}
      }
      if(flag == 0){
	env[k] = malloc(sizeof(str) + 1);
	strcpy(env[k], str);
	env[k+1] = NULL;
	k++;
      }
    }
    //built-in command unsetenv
    else if (strcmp(cmdArg[0], "unsetenv") == 0) {
      int flag = 0;
      char *envTemp, tempString[1024], *split;

      for(i = 0; i < k; i++){
	strcpy(tempString, env[i]);
	split = tempString;
	envTemp = strsep(&split, "=");
	if((strcmp(envTemp, cmdArg[1])) == 0){
	  free(env[i]);
	  for(int j = i; j < k-1; j++){
	    strcpy(env[j], env[j+1]);
	  }
	  k--;
	}
      }
    }
    //built-in command cd
    else if (strcmp(cmdArg[0], "cd") == 0) {
      char *envTemp, tempString[1024], *split, *address;
      char *envTemp2, tempString2[1024], *split2, tempString3[1024]; 
      if(cmdArg[1] == NULL || (strcmp(cmdArg[1], "∼") == 0)){
	for(i = 0; i < k; i++){
	  strcpy(tempString, env[i]);
	  split = tempString;
	  envTemp = strsep(&split, "=");
	  if((strcmp(envTemp, "HOME")) == 0){
	    address = strchr(env[i], '=') + sizeof(char);
	    chdir(address);
	  }
	}
	for(i = 0; i < k; i++){
	  strcpy(tempString2, env[i]);
	  split2 = tempString2;
	  envTemp2 = strsep(&split2, "=");
	  if((strcmp(envTemp2, "PWD")) == 0){
	    strcpy(tempString3, "PWD=");
	    strcat(tempString3,address);
	    env[i] = (char *) malloc(sizeof(tempString3) + 1);
	    strcpy(env[i], tempString3);
	  }
	}
      }
      else{
	chdir(cmdArg[1]);
	printf("%s\n", getcwd(tempString, 1024));
	for(i = 0; i < k; i++){
          strcpy(tempString2, env[i]);
          split2 = tempString2;
          envTemp2 = strsep(&split2, "=");
          if((strcmp(envTemp2, "PWD")) == 0){
            strcpy(tempString3, "PWD=");
	    strcat(tempString3,getcwd(tempString, 1024));
            env[i] = (char *) malloc(sizeof(tempString3) + 1);
            strcpy(env[i], tempString3);
          }
        }
      }
    }
    //built-in command history
    else if (strcmp(cmdArg[0], "history") == 0) {
      for(i = 0; i < historySize; i++){
	printf("%d  %s\n", (i + 1), history[i]);
      }
    }

    //implement how to execute Linux commands here
    else{
      char *envTemp, tempString[1024], *split, *address, *split2, command[1024], *address2;
      for(i = 0; i < k; i++){
	strcpy(tempString, env[i]);
	split = tempString;
	envTemp = strsep(&split, "=");
	if((strcmp(envTemp, "PATH")) == 0){

	  address = strchr(env[i], '=') + sizeof(char);
	  address2 = malloc (1024);
	  strcpy(address2, address);

	  while(address2 != NULL){
	    split2 = strsep(&address2, ":");
	    strcpy(command, split2);
	    strcat(command, "/");
	    strcat(command, cmdArg[0]);
	    
	    if(access(command, X_OK) == 0){
	      break;
	    }
	    
	  }
	  if(access(command, X_OK) == 0){
	    pid = fork();
              if (pid != 0) {
                waitpid(pid, &status, 0);
              } else {
                status = execv(command, cmdArg);                                                                                      }
	  } else {
	    printf("\tno such command (%s)\n", cmdArg[0]);
	  }
	  
	  break;
	}
      }
    }
    //the following is a template for using fork() and execv()
    /***remove this else case from your final code for bsh.c
    else {
      if (debug)
	printf("calling fork()\n");
      pid = fork();
      if (pid != 0) {
	if (debug)
	  printf("parent %d waiting for child %d\n", getpid(), pid);
	waitpid(pid, &status, 0);
      }
      else {
	status = execv(cmdArg[0], cmdArg);
	if (status) {
	  printf("\tno such command (%s)\n", cmdArg[0]);
	  return 1;
	}
      }
    }
    ****remove up to this point*/

    //clean up before running the next command
    i = 0;
    while (cmdArg[i] != NULL)
      free( cmdArg[i++] );
    free(cmdArg);
  }

  return 0;
}

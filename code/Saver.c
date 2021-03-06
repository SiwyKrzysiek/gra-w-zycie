#include "Saver.h"

void setup(){
	myTime = time(NULL);
	dirName = ctime(&myTime);
	dirName[strlen(dirName) - 1] = '\0';
	counter = 1;
	tempString = NULL;
}

void saveCommon(Board** history, Config* config, int i, char* extension){
	if( i == 0 ) setup();
	temp = i;
    counter = 0;
    while (temp != 0){
       temp /= 10;
       counter++;
    }
    if (counter == 0) counter  = 1;
    temp = config->number_of_generations;
    path = malloc(strlen(config->output_dest) + strlen(dirName) + counter + 9);
    strcpy(path, config->output_dest);
    tempString = malloc(counter+1);
    sprintf(tempString, "%d", i*config->step);
    strcat(path, extension);
    strcat(path, dirName);
    strcat(path, "/");
    mkdir(path, 0777);
    strcat(path, tempString);
    strcat(path, ".");
    strcat(path, extension);
    if(strcmp(extension, "png") == 0) savePng(history[i], path);
    else{
        FILE* f = fopen(path, "w");
        fprintf(f, "%s", serializeBoard(history[i]));
        fclose(f);
    }
    free(tempString);
    free(path);
}

void saveAsGif(Board** history, Config* config, int historySize){
	setup();
	path = malloc(strlen(config->output_dest) + strlen(dirName) + 5);
	strcpy(path, config->output_dest);
	strcat(path, dirName);
	strcat(path, ".gif");
	saveHistoryAsGif(history, historySize, path, config->delay / 10);
	free(path);
}

void saveAsPng(Board** history, Config* config, int i){
	saveCommon(history, config, i, "png");
}

void saveAsTxt(Board** history, Config* config, int i){
	saveCommon(history, config, i, "txt");
}

void printToStdout(Board** history, Config* config, int i){
    clear();
    char* b = boardToString(history[i]);
    printf("%s", b);
    free(b);
    //puts("\n-------------------------------------------------\n\n");
    usleep(config->delay * 1000);
}

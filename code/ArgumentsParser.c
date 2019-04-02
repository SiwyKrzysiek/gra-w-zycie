#include "ArgumentsParser.h"

void disposeConfig(Config* c){
	free(c->output_dest);
	free(c);
}

Config* parseArgs(int argc, char** argv) {

	int c;
	char ch;
	int read;
	char* defualtOutput = "result/";


	Config* args = malloc(sizeof(*args));

	args->help = 0;
	args->file = "";
	args->output_dest = malloc(strlen(defualtOutput) + 1);
	strcpy(args->output_dest, defualtOutput);
	args->type = GIF;
	args->number_of_generations = 15;
	args->step = 1;
	args->delay = 500;
	args->sizeX = 10;
	args->sizeY = 10;

	if (argc == 1){
		printf("To view help, call the program with -h / --help flag\n");
		exit(EXIT_FAILURE);
	}
	while (1) {
		int option_index = 0;
		static struct option long_options[] = {
				{"help", no_argument,       0,  'h' },
                {"file",  required_argument, 0,  'f' },
                {"output_dest",  required_argument,       0,  'o' },
                {"type",  required_argument,       0,  't' },
                {"number_of_generations",  required_argument,       0,  'n' },
                {"step",  required_argument,       0,  'p' },
                {"delay",  required_argument,       0,  'd' },
                {"size",  required_argument,       0,  's' }
               };

		c = getopt_long(argc, argv, "hf:o:t:n:p:d:s:",
			long_options, &option_index);

		if (c == -1)
			break;

		switch (c) {

			default:
				printf("To view help, call the program with -h / --help flag\n");
				exit(1);

			case 'h':
				args->help = 1;
				break;

			case 'f':
				args->file = optarg;
				break;

			case 'o':
				if(optarg[strlen(optarg) - 1] != '/'){
					if(realloc(args->output_dest, strlen(optarg) + 2) == NULL){
						printf("Memory error");
						exit(EXIT_FAILURE);
					}
					strcpy(args->output_dest, optarg);
					strcat(args->output_dest, "/");
				}else{
					if(realloc(args->output_dest, strlen(optarg) + 1) == NULL){
						printf("Memory error");
						exit(EXIT_FAILURE);
					}
					strcpy(args->output_dest, optarg);
				}
				break;

			case 't':
				if(strcmp(optarg, "txt") == 0) args->type = TXT;
				else if(strcmp(optarg, "png") == 0) args->type = PNG;
				else if(strcmp(optarg, "gif") == 0) args->type = GIF;
				else if(strcmp(optarg, "out") == 0) args->type = OUT;
				else{
					printf("\nNierozpoznany typ pliku wyjściowego, wybrany domyślny - .gif\n");
				}

				break;

			case 'n':
				args->number_of_generations = atoi(optarg);
				if (args->number_of_generations == 0)
				{
					args->number_of_generations = 15;
					printf("Invalid number of generations\nSet to default - 15\n");
				}

				break;

			case 'p':
				args->step = atoi(optarg);	
				if (args->step == 0)
				{
					args->step = 1;
					printf("Invalid value of steps\nSet to default - 1\n");
				}

				break;

			case 'd':
				args->delay = atoi(optarg);
				if (args->delay == 0)
				{
					args->delay = 500;
					printf("Invalid delay\nSet to default - 500\n");
				}

				break;
			case 's':
				read = sscanf(optarg, "%d%c%d", &(args->sizeX), &ch, &(args->sizeY));
				if (read != 3 || ch != 'x'){
					printf("Invalid size\nSet to default - 10x10");
					args->sizeX = 10;
					args->sizeY = 10;
				}
				break;
		}
	}

	if (optind < argc) {
		 printf("To view help call the program with -h / --help flag\n");
         exit(EXIT_FAILURE);
	}
	mkdir(args->output_dest, 0777);
	return args;
}

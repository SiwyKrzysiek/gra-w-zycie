#include "ArgumentsParser.h"

Config* parseArgs(int argc, char** argv) {

	int c;

	Config* args = malloc(sizeof(*args));

	args->help = 0;
	args->file = "";
	args->output_dest = "";
	args->type = GIF;
	args->number_of_generations = 15;
	args->step = 1;
	args->delay = 1000;

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
               };

		c = getopt_long(argc, argv, "hf:o:t:n:p:d:",
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
				args->output_dest = optarg;
				break;

			case 't':
				if(strcmp(optarg, "txt") == 0) args->type = TXT;
				else if(strcmp(optarg, "png") == 0) args->type = PNG;
				else if(strcmp(optarg, "gif") == 0) args->type = GIF;
				else{
					printf("\nNierozpoznany typ pliku wyjściowego, wybrany domyślny - .gif\n");
				}

				break;

			case 'n':
				args->number_of_generations = atoi(optarg);
				break;

			case 'p':
				args->step = atoi(optarg);	
				break;

			case 'd':
				args->delay = atoi(optarg);
				break;
		}
	}

	if (optind < argc) {
		 printf("To view help call the program with -h / --help flag\n");
         exit(EXIT_FAILURE);
	}
	return args;
}

#include <stdio.h> 
#include <stdlib.h>    
#include <getopt.h>

typedef struct{
	int help;
	char* file;
	char* output_dest;
	char* type;
	int amount_of_generations;
	int step;
	int delay;
}Config;

Config parseArgs(int argc, char** argv) {

	int c;

	Config args;

	args.help = 0;
	args.file = "";
	args.output_dest = "";
	args.type = "";
	args.amount_of_generations = 15;
	args.step = 1;
	args.delay = 1000;

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
                {"amount_of_generations",  required_argument,       0,  'n' },
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
				args.help = 1;
				break;

			case 'f':
				args.file = optarg;
				break;

			case 'o':
				args.output_dest = optarg;
				break;

			case 't':
				args.type = optarg;
				break;

			case 'n':
				args.amount_of_generations = atoi(optarg);
				break;

			case 'p':
				args.step = atoi(optarg);	
				break;

			case 'd':
				args.delay = atoi(optarg);
				break;
		}
	}

	if (optind < argc) {
		 printf("To view help call the program with -h / --help flag\n");
         exit(EXIT_FAILURE);
	}
	return args;
}

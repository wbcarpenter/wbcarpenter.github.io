#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

// Helper to print timestamps for debugging
void print_timestamp() {
	time_t t = time(NULL);
	char buf[64];
	strftime(buf, sizeof(buf), "%H:%M:%S", localtime(&t));
	printf("[TIME] %s\n", buf);
}

void vulnerable_file_access(const char *filename) {
	printf("[Victim] === STARTING ACCESS ATTEMPT ===\n");

	// ---TIME OF CHECK (TOC) PHASE
	print_timestamp();

	int check_result = 0;

	// Check: does the file exist AND is it writable by the current user?
	if (access(filename, W_OK) == 0) {
		printf("[Victim] [CHECK SUCCESS] File exists and is writable.\n");
		check_result = 1;
	} else {
		printf("[Victim] [CHECK FAILED] File does not exist or is not writable.\n");
		return; // Exit if the initial check fails
	}

	print_timestamp();

	// --- DELAY: Creates the TOCTOU Window (1 second) ---
	// This delay makes it easier for the attacker to race against us
	printf("[Victim] [DELAY PHASE] Waiting 1 second before use....\n");
	sleep(1);
	print_timestamp();

	// --- TIME OF USE (TOU) PHASE ---
	if (check_result == 1) {
		FILE *file_ptr = fopen(filename, "a"); // CRITICAL: The use happens here!

		if (file_ptr != NULL) {
			printf("[Victim] [USE PHASE] Opening file for writing...\n");

			time_t t = time(NULL);
			char time_str[30];
			strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&t));

			fprintf(file_ptr, "\n--- Access Granted by Victim Program at %s ---\n", time_str);
			printf("[Victim] [SUCCESS] File successfully written to!\n");
			fclose(file_ptr);
		} else {
			// This failure indicates the file was likely swapped out or permissions changed
			// between the access() call and the fopen() call
			perror("[Victim] [USE FAILED] Error durin the use phase (fopen failed)");
			printf("[Victim] [FAILURE ANALYSIS] The check passed, but the use failed! TOCTOU likely occured.\n");
		}
	}

	print_timestamp();
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename_to_watch>\n", argv[1]);
		return EXIT_FAILURE;
	}

	vulnerable_file_access(argv[1]);
	printf("[Victim] === ENDING ACCESS ATTEMPT ===\n");
	return EXIT_SUCCESS;
}

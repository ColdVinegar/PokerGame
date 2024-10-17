void loggame(int state, int ch1, int ch2, int bank, int mv1, int mv2, int *cards1, int *cards2, int *table, int bb, int onboard, int equal, int whowin, int erebuy, int hrebuy){
	return; // Comment to enable logging
	FILE *logfile = fopen("log.txt", "a+");

	fprintf(logfile, "BB: %d, 1_chips: %d, 2_chips: %d, bank: %d, equal: %d\n", bb, ch1, ch2, bank, equal);

	switch(state){
		case 1:
			fprintf(logfile, "\n\n\nGame started!\n");
			fprintf(logfile, "Player 1: %d, %d\n", cards1[0], cards1[1]);
			fprintf(logfile, "Table: %d, %d, %d, %d, %d\n", table[0], table[1], table[2], table[3], table[4]);
			fprintf(logfile, "Player 2: %d, %d\n", cards2[0], cards2[1]);
			break;
		case 2:
			fprintf(logfile, "Player 1 move: %d\n\n", mv1);
			break;
		case 3:
			fprintf(logfile, "Player 2 move: %d\n\n", mv2);
			break;
		case 4:
			fprintf(logfile, "\n\nNew round. Onboard: %d\n", onboard);
			break;
		case 5:
			fprintf(logfile, "Gameover! whowin: %d\n", whowin);
			break;
		case 6:
			fprintf(logfile, "Player 1 rebuy. Total rebuy: %d\n", hrebuy);
			break;
		case 7:
			fprintf(logfile, "Player 2 rebuy. Total rebuy: %d\n", erebuy);
			break;
	}
	fclose(logfile);
}

void logstat(int games, int ebotwins, int ebotch, int eprofit, int ereb, int hbotwins, int hbotch, int hprofit, int hreb, int draws, int drawsch){
	FILE *logfile = fopen("stat.txt", "a+");
	fprintf(logfile, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", games, ebotwins, ebotch, eprofit, ereb, hbotwins, hbotch, hprofit, hreb, draws, drawsch);
	fclose(logfile);
}
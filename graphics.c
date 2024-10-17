#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#define cardtop ((const unsigned char*)"┌───────┐")
#define cardbottom ((const unsigned char*)"└───────┘")
#define hiddencard ((const unsigned char*)"│ ///// │")
#define emptycard ((const unsigned char*)"│       │")
#define highlightup ((const unsigned char*)"\\/\\/\\/\\/")
#define highlightdown ((const unsigned char*)"/\\/\\/\\/\\")

int betmenu(int y, int x, int playerchips, int minbet){
	int pos = 1, movementflag = 0;
	int ch;
	int output;	
	move(y, 0);
	clrtobot();
	mvprintw(y+1, x-2, ">");
	mvprintw(y, x,   "┌───────────┐     ┌───────────┐");
	mvprintw(y+1, x, "│  Custom   │     │  ALL-IN   │");
	mvprintw(y+2, x, "└───────────┘     └───────────┘");
	while((ch = getch()) != 10 && ch != 32){
		if(ch == KEY_LEFT){
			move(y, 0);
			clrtobot();
			if(pos == 2 && movementflag == 0){					// Переход со 2 на 1 позицию
				pos--;
				movementflag = 1;
				mvprintw(y+1, x-2, ">");
			}
			mvprintw(y, x,   "┌───────────┐");
			mvprintw(y+1, x, "│  Custom   │");
			mvprintw(y+2, x, "└───────────┘");
			if(pos == 1 && movementflag == 0){				// Переход с 1 на 2 позицию
				pos++;
				movementflag = 1;
				mvprintw(y+1, x+15, ">");				
			}
			mvprintw(y, x+18,   "┌───────────┐");
			mvprintw(y+1, x+18, "│  ALL-IN   │");
			mvprintw(y+2, x+18, "└───────────┘");
		}
		if(ch == KEY_RIGHT){
			move(y, 0);
			clrtobot();
			if(pos == 1 && movementflag == 0){					// Переход с 1 на 2 позицию
				pos++;
				movementflag = 1;
				mvprintw(y+1, x+15, ">");
			}
			mvprintw(y, x,   "┌───────────┐");
			mvprintw(y+1, x, "│  Custom   │");
			mvprintw(y+2, x, "└───────────┘");
			if(pos == 2 && movementflag == 0){				// Переход со 2 на 1 позицию
				pos--;
				movementflag = 1;
				mvprintw(y+1, x-2, ">");				
			}
			mvprintw(y, x+18,   "┌───────────┐");
			mvprintw(y+1, x+18, "│  ALL-IN   │");
			mvprintw(y+2, x+18, "└───────────┘");
		}
		movementflag = 0;
	}

	if(pos == 2){
		output = playerchips;
		return output;
	}
	if(pos){
		move(y+3, x);
		printw("input your bet: ");
		echo();
		while(1){
			if(scanw("%d", &output) != 1 || output > playerchips || output <= 0 || output < 10){
				mvprintw(y+5, x+8, "Недостаточно денег или неправильный формат ввода, нажмите любуе кнопку чтобы ввести ещё раз");
			}
			else{
				if(output%10 != 0){
					int ost = output%10;
					output = (output/10)*10;
					if(ost>0) output+=10;
				}
				if(output > playerchips) output = playerchips;
				break;
			}
			getch();
			move(y+3, x+16);
			clrtobot();
		}
		noecho();
		move(y+3, 0);
		clrtobot();

		return output;
	}
}

void ggmenu(int y, int x, int whowin){
	mvprintw(y, x,   "┌───────────────────────────────────────────────┐");
	switch(whowin){
	case 0:
		mvprintw(y+1, x, "│                    D R A W                    │");
		break;
	case 1:
		mvprintw(y+1, x, "│                B O T    W I N                 │");
		break;
	case 2:
		mvprintw(y+1, x, "│                Y O U    W I N                 │");
	}
	mvprintw(y+2, x, "└───────────────────────────────────────────────┘");
	mvprintw(y+3, x, " Нажмите любую кнопку для того чтобы выйти в меню");
	getch();
}

int actionmenu(int y, int x, int playerchips, int minbet){
	int pos = 1, movementflag = 0;
	int ch;
	mvprintw(y+1, x-2, ">");
	mvprintw(y, x,   "┌───────────┐     ┌───────────┐     ┌───────────┐");
	mvprintw(y+1, x, "│Check/Call │     │    Bet    │     │   Fold    │");
	mvprintw(y+2, x, "└───────────┘     └───────────┘     └───────────┘");
	while((ch = getch()) != 10 && ch != 32){

		if(ch == KEY_LEFT){
			move(y, 0);
			clrtobot();
			if(pos == 2 && movementflag == 0){					// Переход со 2 на 1 позицию
				pos--;
				movementflag = 1;
				mvprintw(y+1, x-2, ">");
			}
			mvprintw(y, x,   "┌───────────┐");
			mvprintw(y+1, x, "│Check/Call │");
			mvprintw(y+2, x, "└───────────┘");
			if(pos == 3 && movementflag == 0){				// Переход с 3 на 2 позицию
				pos--;
				movementflag = 1;
				mvprintw(y+1, x+15, ">");				
			}
			mvprintw(y, x+18,   "┌───────────┐");
			mvprintw(y+1, x+18, "│    Bet    │");
			mvprintw(y+2, x+18, "└───────────┘");
			if(pos == 1 && movementflag == 0){				// Переход с 1 на 3 позицию
				pos = 3;
				movementflag = 1;
				mvprintw(y+1, x+33, ">");				
			}
			mvprintw(y, x+36,   "┌───────────┐");
			mvprintw(y+1, x+36, "│   Fold    │");
			mvprintw(y+2, x+36, "└───────────┘");
		}

		if(ch == KEY_RIGHT){
			move(y, 0);
			clrtobot();
			if(pos == 3 && movementflag == 0){					// Переход с 3 на 1 позицию
				pos = 1;
				movementflag = 1;
				mvprintw(y+1, x-2, ">");
			}
			mvprintw(y, x,   "┌───────────┐");
			mvprintw(y+1, x, "│Check/Call │");
			mvprintw(y+2, x, "└───────────┘");
			if(pos == 1 && movementflag == 0){				// Переход с 1 на 2 позицию
				pos++;
				movementflag = 1;
				mvprintw(y+1, x+15, ">");				
			}
			mvprintw(y, x+18,   "┌───────────┐");
			mvprintw(y+1, x+18, "│    Bet    │");
			mvprintw(y+2, x+18, "└───────────┘");
			if(pos == 2 && movementflag == 0){				// Переход со 2 на 3 позицию
				pos++;
				movementflag = 1;
				mvprintw(y+1, x+33, ">");				
			}
			mvprintw(y, x+36,   "┌───────────┐");
			mvprintw(y+1, x+36, "│   Fold    │");
			mvprintw(y+2, x+36, "└───────────┘");
		}

		movementflag = 0;
	}

	if(pos == 2){ 
		pos = betmenu(y, x, playerchips, minbet); 
	}
	if(minbet != 0 && pos == 1){
		if(playerchips < minbet) return playerchips;
		else return minbet;
	}
	return pos;
}
int difficultymenu(){
	int x, y;
	getmaxyx(stdscr, y, x);
	int pos = 1, movementflag = 0; // Позиция и флаг чтобы при перемещении не ломался код 
	int ch;
	mvprintw(2, x/3-10, "  _____ _____ ______ ______ _____ _____ _    _ _   _________     __");
	mvprintw(3, x/3-10, " |  __ \\_   _|  ____|  ____|_   _/ ____| |  | | | |__   __\\ \\   / /");
	mvprintw(4, x/3-10, " | |  | || | | |__  | |__    | || |    | |  | | |    | |   \\ \\_/ /");
	mvprintw(5, x/3-10, " | |  | || | |  __| |  __|   | || |    | |  | | |    | |    \\   /");
	mvprintw(6, x/3-10, " | |__| || |_| |    | |     _| || |____| |__| | |____| |     | |");
	mvprintw(7, x/3-10, " |_____/_____|_|    |_|    |_____\\_____|\\____/|______|_|     |_|");
	mvprintw(y/3-2, x/3+11, ">");
	mvprintw(y/3-2, x/3+13, "EASY DIFFICULTY");
	mvprintw(y/3, x/3+13, "HARD DIFFICULTY");	
	mvprintw(y/3+2, x/3+17, "GO BACK");

	while((ch = getch()) != 10 && ch != 32){

		if(ch == KEY_DOWN){			// Нажатие вниз
			move(y/3-2, 0);
			clrtobot();			// очистка всего под ascii-art

			if(pos == 3 && movementflag == 0){					// Переход с 3 на 1 позицию
				pos = 1;
				movementflag = 1;
				mvprintw(y/3-2, x/3+11, ">");
			}
			if(pos == 2 && movementflag == 0){				// Переход со 2 на 3 позицию
				pos++;
				movementflag = 1;
				mvprintw(y/3+2, x/3+11, ">");				
			}
			if(pos == 1 && movementflag == 0){				// Переход с 1 на 2 позицию
				pos++;
				movementflag = 1;
				mvprintw(y/3, x/3+11, ">");				
			}

			mvprintw(y/3-2, x/3+13, "EASY DIFFICULTY");
			mvprintw(y/3, x/3+13, "HARD DIFFICULTY");
			mvprintw(y/3+2, x/3+17, "GO BACK");
			refresh();
		}
		
		if(ch == KEY_UP){				//Нажатие вверх
			move(y/3-2, 0);
			clrtobot();			// очистка всего под ascii-art
			if(pos == 2 && movementflag == 0){				// Переход со 2 на 1 позицию
				pos--;
				movementflag = 1;
				mvprintw(y/3-2, x/3+11, ">");				
			}
			if(pos == 3 && movementflag == 0){					// Переход с 3 на 2 позицию
				pos--;
				movementflag = 1;
				mvprintw(y/3, x/3+11, ">");
			}
			if(pos == 1 && movementflag == 0){				// Переход с 1 на 3 позицию
				pos = 3;
				movementflag = 1;
				mvprintw(y/3+2, x/3+11, ">" );				
			}
			mvprintw(y/3-2, x/3+13, "EASY DIFFICULTY");
			mvprintw(y/3, x/3+13, "HARD DIFFICULTY");
			mvprintw(y/3+2, x/3+17, "GO BACK");
			refresh();
		}

		movementflag = 0;
	}

	return pos;
}

int mainmenu(){
	int x, y;
	getmaxyx(stdscr, y, x); // Берём размер окна терминала
	int pos = 1, movementflag = 0; // Позиция и флаг чтобы не ломался код при перемещении
	int ch;
	mvprintw(2, x/3, "  _____     ____    _  __  ______   _____    ");
	mvprintw(3, x/3, " |  __ \\   / __ \\  | |/ / |  ____| |  __ \\   ");
	mvprintw(4, x/3, " | |__) | | |  | | | ' /  | |__    | |__) |  ");
	mvprintw(5, x/3, " |  ___/  | |  | | |  <   |  __|   |  _  /   ");
	mvprintw(6, x/3, " | |      | |__| | | . \\  | |____  | | \\ \\   ");
	mvprintw(7, x/3, " |_|       \\____/  |_|\\_\\ |______| |_|  \\_\\  ");
	mvprintw(y/3-2, x/3+14, ">");
	mvprintw(y/3-2, x/3+20, "PLAY");
	mvprintw(y/3, x/3+17, "BOT VS BOT");
	mvprintw(y/3+2, x/3+14, "   RESET PROG");
	mvprintw(y/3+4, x/3+19, "LEAVE");
	

	while((ch = getch()) != 10 && ch != 32){
		if(ch == KEY_DOWN){			// Нажатие вниз
			move(y/3-2, 0);
			clrtobot();

			if(pos == 4 && movementflag == 0){				// Переход с 4 на 1 позицию
				pos = 1;
				movementflag = 1;
				mvprintw(y/3-2, x/3+14, ">");				
			}

			if(pos == 3 && movementflag == 0){					// Переход с 3 на 4 позицию
				pos++;
				movementflag = 1;
				mvprintw(y/3+4, x/3+14, ">");
			}

			if(pos == 2 && movementflag == 0){				// Переход со 2 на 3 позицию
				pos++;
				movementflag = 1;
				mvprintw(y/3+2, x/3+14, ">");				
			}

			if(pos == 1 && movementflag == 0){				// Переход с 1 на 2 позицию
				pos++;
				movementflag = 1;
				mvprintw(y/3, x/3+14, ">");				
			}

			mvprintw(y/3-2, x/3+20, "PLAY");
			mvprintw(y/3, x/3+17, "BOT VS BOT");
			mvprintw(y/3+2, x/3+17, "RESET PROG");
			mvprintw(y/3+4, x/3+19, "LEAVE");
			movementflag = 0;
			refresh();
		}
		
		if(ch == KEY_UP){				//Нажатие вверх
			move(y/3-2, 0);
			clrtobot();

			if(pos == 2 && movementflag == 0){				// Переход со 2 на 1 позицию
				pos--;
				movementflag = 1;
				mvprintw(y/3-2, x/3+14, ">");				
			}

			if(pos == 1 && movementflag == 0){				// Переход с 1 на 4 позицию
				pos = 4;
				movementflag = 1;
				mvprintw(y/3+4, x/3+14, ">" );				
			}

			if(pos == 3 && movementflag == 0){					// Переход с 3 на 2 позицию
				pos--;
				movementflag = 1;
				mvprintw(y/3, x/3+14, ">");
			}

			if(pos == 4 && movementflag == 0){					// Переход с 4 на 3 позицию
				pos--;
				movementflag = 1;
				mvprintw(y/3+2, x/3+14, ">");
			}

			mvprintw(y/3-2, x/3+20, "PLAY");
			mvprintw(y/3, x/3+17, "BOT VS BOT");
			mvprintw(y/3+2, x/3+17, "RESET PROG");
			mvprintw(y/3+4, x/3+19, "LEAVE");
			movementflag = 0;
			refresh();
		}
	}

	return pos;
}

void deshif(int card, char* output){
	int mast = card%100;
	int num = card/100;
	output[0] = '\0';
	if(num <= 10){
		sprintf(output, "%d", num);	
	}
	else{
		switch(num){
			case 11:
				strcat(output, "J");
				break;
			case 12:
				strcat(output, "Q");
				break;
			case 13:
				strcat(output, "K");
				break;
			case 14:
				strcat(output, "A"); 
				break;
		}
	}
	switch(mast){
		case 1:
			strcat(output, "♠");
			break;
		case 2:
			strcat(output, "♥");
			break;
		case 3:
			strcat(output, "♣");
			break;
		case 4:
			strcat(output, "♦");
			break;
	}
}

void deshifcomb(int num, char* output){
	output[0] = '\0';
	switch(num){
		case 1:
			strcpy(output, "Старшая карта");
			break;
		case 2:
			strcpy(output, "Пара");
			break;
		case 3:
			strcpy(output, "Две пары");
			break;
		case 4:
			strcpy(output, "Сет");
			break;
		case 5:
			strcpy(output, "Стрит");
			break;
		case 6:
			strcpy(output, "Флеш");
			break;
		case 7:
			strcpy(output, "Фулл Хаус");
			break;
		case 8:
			strcpy(output, "Каре");
			break;
		case 9:
			strcpy(output, "Стрит Флеш");
			break;
		case 10:
			strcpy(output, "Рояль Флеш");
			break;
	}
}

void printcards(int cardamount, int *cards, int hidden, int cury, int x){
	char cardpart[140];
	cardpart[0] = '\0';
	if(hidden){
		mvprintw(cury, x/3-10, "%s  %s\n", cardtop, cardtop);
		for(int i = 0; i < 4; i++){
			mvprintw(cury+1+i, x/3-10, "%s  %s", hiddencard, hiddencard);
		}
		mvprintw(cury+5, x/3-10, "%s  %s", cardbottom, cardbottom);
	}
	else{
		for(int iter = 0; iter < 6; iter++){
			for(int i = 0; i < cardamount; i++){
				char deshifed[6];
				deshif(cards[i], deshifed);

				if(iter == 0){
					strcat(cardpart, cardtop); 
				}

				if(iter == 1){
					strcat(cardpart, "│ ");
					strcat(cardpart, deshifed);

					for(int count = 0; count< 8-strlen(deshifed); count++){
						strcat(cardpart, " ");
					}
					strcat(cardpart, "│");
				}

				if(iter == 2 || iter == 3){
					strcat(cardpart, emptycard);
				}

				if(iter == 4){
					strcat(cardpart, "│");
					for(int count = 0; count< 8	-strlen(deshifed); count++){
						strcat(cardpart, " ");
					}
					strcat(cardpart, deshifed);
					strcat(cardpart, " │");
				}

				if(iter == 5){
					strcat(cardpart, cardbottom);
				}

				strcat(cardpart, "  "); 
			}
			mvprintw(cury+iter, x/3-10, "%s\n", cardpart);
			cardpart[0] = '\0';
		}
	}
}

void highlightcards(int* bcombo, int* pcombo, int* bot, int* player, int* table, int x){
	int i = 0, y = 5;
	int highlightbot[7];
	int highlightplr[7];

	while(i < 2){
  		highlightbot[i] = count(bcombo, 5, bot[i]);
  		highlightplr[i] = count(pcombo, 5, player[i]);
  		i++;
	}
	i = 0;
	while(i < 5){
  		highlightbot[2+i] = count(bcombo, 5, table[i]);
  		highlightplr[2+i] = count(pcombo, 5, table[i]);
  		i++;
	}
	attron(COLOR_PAIR(1));
	for(i = 0; i < 7; i++){
		if(i < 2 ){
			if(highlightbot[i]){
			mvprintw(y, x/3-6+(i*11), "▼");
			}
		}else{
			if(highlightbot[i]){
				y = 14;
				mvprintw(y, x/3-6+((i-2)*11), "▼");
			}
		}
	}
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	for(i = 0; i < 7; i++){
		if(i < 2 ){
			y = 31;
			if(highlightplr[i]){
			mvprintw(y, x/3-6+(i*11), "▲");
			}
		}else{
			if(highlightplr[i]){
				y = 21;
				mvprintw(y, x/3-6+((i-2)*11), "▲");
			}
		}
	}
	attroff(COLOR_PAIR(2));
	getch();

}

int printtable(int pcombnum, int bcombnum, int pcombo[5], int bcombo[5], int minbet, int bankchips, int playerchips, int botchips, int onboard, int *table, int *bot, int *player, int hiddenbot, int gameover, int botmove, int whowin, int bb){
	clear();
	int y, x, cury, curx;
	int actionoutput;
	getmaxyx(stdscr, y,x);
	mvprintw(2, x/3-10, "Фишки бота: $%d", botchips);
	mvprintw(2, x/3+40, "Банк: $%d", bankchips);
	if(bb){
		mvprintw(8, x/3-25, "DEALER (SB)");
	}
	else{
		mvprintw(27, x/3-25, "DEALER (SB)");
	}
	switch(botmove){
		case 0:
			break;
		case 1:
			mvprintw(3, x/3-10, "Бот сделал check.");
			break;
		case 3:
			mvprintw(3, x/3-10, "Бот сделал fold.");
			break;
		default:
			if(botchips == 0) mvprintw(3, x/3-10, "Бот поставил ALL-IN");
			else mvprintw(3, x/3-10, "Бот поставил: $%d", botmove);
			break;
	}
	cury = 6;
	printcards(2, bot, hiddenbot, cury, x);
	cury = 15;
	printcards(onboard, table, 0, cury, x);
	cury = 25;
	printcards(2, player, 0, cury, x);
	mvprintw(34, x/3-10, "Фишки игрока: $%d", playerchips);
	if(!gameover) actionoutput = actionmenu(36, x/3-10, playerchips, minbet);
	else{
		if(onboard == 5){
			char deshifed1[25], deshifed2[25];
			deshifcomb(bcombnum, deshifed1);
			deshifcomb(pcombnum, deshifed2);

			attron(COLOR_PAIR(1));
			mvprintw(4, x/3-10, "Комбинация: %s", deshifed1);
			attroff(COLOR_PAIR(1));

			attron(COLOR_PAIR(2));
			mvprintw(33, x/3-10, "Комбинация: %s", deshifed2);
			attroff(COLOR_PAIR(2));

			highlightcards(bcombo, pcombo, bot, player, table, x);
		}
		ggmenu(36, x/3-10, whowin);
	}
	clear();
	return actionoutput;
}

int tablelogic(int pcombnum, int bcombnum, int pcombo[5], int bcombo[5], int minbet, int bankchips, int playerchips, int botchips, int onboard, int *table, int *bot, int *player, int hiddenbot, int gameover, int botmove, int whowin, int bb){
	int playerchoise = printtable(pcombnum, bcombnum, pcombo, bcombo, minbet, bankchips, playerchips, botchips, onboard, table, bot, player, hiddenbot, gameover, botmove, whowin, bb);
	return playerchoise;
}

int chkwinsize(){
	int y, x;
	getmaxyx(stdscr, y, x);
	if((y<45) || (x < 90)){
		printw("Для корректной работы программы требуется полноэкранный\n");
		printw("режим терминала, либо приближенный к полноэкранному\n");
		printw("Для завершения работы нажмите любую кнопку");
		return 1;
	}
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int min(int a, int b){
	return a > b ? b : a;
}

int max(int a, int b){
	return a < b ? b : a;
}

int absolute(int a){
	return a >= 0 ? a : -1*a;
}

typedef struct stack{
    int val;
    struct stack* next;
} stack;

void push(stack** top, int cardid){
    stack* new = malloc(sizeof(stack));
    new->val = cardid;
    new->next = *top;
    *top = new;
}

int pop(stack** top){
    if(*top == NULL)
        return 0;
    
    int cardid =(*top)->val;
 
    stack* new =(*top)->next;
    free(*top);
    *top = new;

    return cardid;
}

void shuffle(stack** top){
	int cards[52];
	int counter = 0;
	for(int i = 1; i < 5; i++){
		for(int j = 2; j < 15; j++){
			cards[counter] = j*100+i;
			counter++;
		}
	}
	counter = 0;
	while(counter!=52){
		int point = rand()%52;
		if(cards[point]!=0){
			counter++;
			push(top, cards[point]);
			cards[point] = 0;
		}
	}
}

void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

void sort(int mas[], int l, int r, int reverse){
    if(l < r){
        int pivot = mas[r];
        int i =(l - 1);
        
        for(int j = l; j < r; j++){
            if(!reverse ?(mas[j] < pivot) : (mas[j] > pivot)){
                i++;
                swap(&mas[i], &mas[j]);
            }
        }
        swap(&mas[i + 1], &mas[r]);
        
        int pi = i + 1;
        
        sort(mas, l, pi - 1, reverse);
        sort(mas, pi + 1, r, reverse);
    }
}

void doublesort(int mas1[], int mas2[], int l, int r, int reverse){ // Сортировка двух взаимосвязанных массивов по первому массиву
    if(l < r){
        int pivot = mas1[r];
        int i =(l - 1);
        
        for(int j = l; j < r; j++){
            if(!reverse ?(mas1[j] < pivot) : (mas1[j] > pivot)){
                i++;
                swap(&mas1[i], &mas1[j]);
                swap(&mas2[i], &mas2[j]);
            }
        }
        swap(&mas1[i + 1], &mas1[r]);
        swap(&mas2[i + 1], &mas2[r]);
        
        int pi = i + 1;
        
        doublesort(mas1, mas2, l, pi - 1, reverse);
        doublesort(mas1, mas2, pi + 1, r, reverse);
    }
}

int count(int* mas, int n, int num){
	int counter = 0;
	for(int i = 0; i < n; i++){
		if(mas[i] == num) counter++;
	}
	return counter;
}

int sum(int* mas, int n){
	int summ = 0;
	for(int i = 0; i < n; i++) summ+=mas[i];
	return summ;
}

int maxi(int* mas, int n){
	int maxx = 0;
	for(int i = 0; i < n; i++)(mas[i] > maxx) ?(maxx = mas[i]) : (0);
	return maxx;
}

int mini(int* mas, int n){
	int minn = 0;
	for(int i = 0; i < n; i++)(mas[i] < minn) ?(minn = mas[i]) : (0);
	return minn;
}

void chckcomb(int board[5], int hand[2], int* num, int* combo){
	int full[7];
	int tmpcombo[5], tmpnum = 0;
	for(int i = 0; i < 7; i++){
		if(i < 2) full[i] = hand[i];
		else full[i] = board[i-2];
	}
	sort(full, 0, 6, 0);
	int masti[7], nums[7];
	for(int i = 0; i < 7; i++){
		masti[i] = full[i]%100;
		nums[i] =(int)full[i]/100;
	}
	int highthree = 0, hightwo = 0, twoappender = 0, threeappender = 0;
	int threerang = 0, tworang = 0;
	int twopair[6], fullhouse[9];
	int fivemast = 0;
	int mask[7];
	int isstraight = 1;
	int isflushstraight = 1;

	for(int i = 0; i < 7; i++) mask[i] = count(nums, 7, nums[i]);
	if(sum(mask, 7) < 14){
		if(maxi(mask, 7) == 3){
			int index = -1;
			for(int i = 0; i < 3; i++){
				int nabor[5], appender = 0;
				for(int j = 0; j < 7; j++){
					if(mask[j] == 1) nabor[appender] = full[j];
					else{
						if(index == -1) index = j;
						if(j == index){
							nabor[appender] = full[index];
							appender++;
						}
					}
				}
				index++;
				int newmasti[5], newnums[5];
				for(int j = 0; j < 5; j++){
					newmasti[j] = nabor[j]%100;
					newnums[j] =(int)(nabor[j]/100);
				}
				fivemast = 0;
				int flushcomb[5], lenflush = 0;
				for(int j = 1; j < 5; j++){
					if(count(newmasti, 7, j) >= 5) fivemast = j;
				}
				isstraight = 1;
				for(int j = 0; j < 4; j++){
					if(newnums[j+1]-newnums[j]!=1) isstraight = 0;
				}
				if(isstraight){
					if((newnums[4] == 14) && fivemast != 0) tmpnum = 10;
					else{
						if(fivemast != 0) tmpnum = 9;
						else tmpnum = 5;
					}
				}
				else{
					if(fivemast != 0){
						tmpnum = 6;
						appender = 0;
						for(int j = 4; j >= 0; j--){
							if(nabor[j]%100==fivemast){
								flushcomb[appender] = nabor[j];
								appender++;
							}
						}
					}
				}
				if(tmpnum >= *num){
					*num = tmpnum;
					for(int j = 0; j < 5; j++){
						if(tmpnum == 6) combo[j] = flushcomb[j];
						else combo[j] = nabor[j];
					}
					tmpnum = -1;
				}
			}
		}
		else{
			if(maxi(mask, 7) == 2){
				int combinat = 0;
				int index1 = -1, index2 = -1;
				int flipflag = 0;
				if(sum(mask, 7) == 11) combinat = 4;
				else combinat = 2;
				for(int i = 0; i < combinat; i++){
					int nabor[5], appender = 0;
					int twocount = 0;
					for(int j = 0; j < 7; j++){
						if(mask[j] == 1){
							nabor[appender] = full[j];
							appender++;
						}
						else{
							if(combinat == 2){
								if(index1 == -1) index1 = j;
								if(j == index1){
									nabor[appender] = full[index1];
									appender++;
								}
							}
							else{
								twocount++;
								if(index1 == -1) index1 = j;
								if((index2 == -1) && (twocount > 2)) index2 = j;
								if(j == index1){
									nabor[appender] = full[index1];
									appender++;
								}
								if(j == index2){
									nabor[appender] = full[index2];
									appender++;
								}
							}
						}
					}
					if(flipflag == 0) index1++;
					if(flipflag == 1) index2++;
					if(flipflag == 2) index1--;
					flipflag++;
					int newm[6], newn[6];
					int c = 5; // len(nabor)
					if(combinat == 4) c = 6;
					for(int j = 0; j < c; j++){
						newm[j] = nabor[j]%100;
						newn[j] =(int)(nabor[j]/100);
					}
					fivemast = 0;
					int flushcomb[5];
					int tmpnums[7], tmpmasti[7];
					for(int j = 0; j < 7; j++){
						tmpnums[j] = newn[j];
						tmpmasti[j] = newm[j];
					}
					doublesort(tmpmasti, tmpnums, 0, 6, 0);
					for(int n = 0; n < c-4; n++){
						int newmasti[5], newnums[5], flushnewmasti[5], flushnewnums[5];
						for(int j = 0; j < 5; j++){
							newmasti[j] = newm[n+j];
							newnums[j] = newn[n+j];
							flushnewmasti[j] = tmpmasti[n+j];
							flushnewnums[j] = tmpnums[n+j];
						}
						for(int j = 1; j < 5; j++){
							if(count(newmasti, 5, j) >= 5) fivemast = j;
							if(count(flushnewmasti, 5, j) >= 5) fivemast = j;
						}
						isstraight = 1;
						for(int j = 0; j < 4; j++){
							if(newnums[j+1]-newnums[j]!=1) isstraight = 0;
						}
						isflushstraight = 1;
						for(int j = 0; j < 4; j++){
							if(flushnewnums[j+1]-flushnewnums[j]!=1) isflushstraight = 0;
						}
						if(isstraight) tmpnum = 5;
						if(isflushstraight){
							if((flushnewnums[4] == 14) && (fivemast != 0)) tmpnum = 10;
							else{
								if(fivemast != 0) tmpnum = 9;
								else tmpnum = 5;
							}
						}
						else{
							if(fivemast != 0){
								tmpnum = 6;
								appender = 0;
								for(int j = c; j >= 0; j--){
									if((nabor[j]%100==fivemast) && (appender < 5)){
										flushcomb[appender] = nabor[j];
										appender++;
									}
								}
							}
						}
						if(tmpnum >= *num){
							*num = tmpnum;
							for(int j = 0; j < 5; j++){
								if(tmpnum == 6) combo[j] = flushcomb[j];
								else combo[j] = nabor[j+n];
							}
							tmpnum = -1;
						}
					}
				}
			}
		}
		fivemast = 0;
		int flushcomb[5];
		int tmpnums[7], tmpmasti[7];
		for(int j = 0; j < 7; j++){
			tmpnums[j] = nums[j];
			tmpmasti[j] = masti[j];
		}
		doublesort(tmpmasti, tmpnums, 0, 6, 0);
		for(int n = 0; n < 3; n++){
			int newmasti[5], newnums[5], flushnewmasti[5], flushnewnums[5];
			for(int j = 0; j < 5; j++){
				newmasti[j] = masti[n+j];
				newnums[j] = nums[n+j];
				flushnewmasti[j] = tmpmasti[n+j];
				flushnewnums[j] = tmpnums[n+j];
			}
			for(int j = 1; j < 5; j++){
				if(count(newmasti, 5, j) >= 5) fivemast = j;
				if(count(flushnewmasti, 5, j) >= 5) fivemast = j;
			}
			isstraight = 1;
			for(int j = 0; j < 4; j++){
				if(newnums[j+1]-newnums[j]!=1) isstraight = 0;
			}
			isflushstraight = 1;
			for(int j = 0; j < 4; j++){
				if(flushnewnums[j+1]-flushnewnums[j]!=1) isflushstraight = 0;
			}
			if(isstraight) tmpnum = 5;
			if(isflushstraight){
				if((flushnewnums[4] == 14) && (fivemast != 0)) tmpnum = 10;
				else{
					if(fivemast != 0) tmpnum = 9;
					else tmpnum = 5;
				}
			}
			else{
				if(fivemast != 0){
					tmpnum = 6;
					int appender = 0;
					for(int j = 6; j >= 0; j--){
						if((full[j]%100==fivemast) && (appender < 5)){
							flushcomb[appender] = full[j];
							appender++;
						}
					}
				}
			}
			if(tmpnum >= *num){
				*num = tmpnum;
				for(int j = 0; j < 5; j++){
					if(tmpnum == 6) combo[j] = flushcomb[j];
					else combo[j] = full[j+n];
				}
				tmpnum = -1;
			}
		}
	}

	for(int i = 0; i < 4; i++){
		if(nums[i+3]-nums[i] == 0) tmpnum = 8;
		if(tmpnum >= *num){
			*num = tmpnum;
			for(int j = 0; j < 4; j++) combo[j] = full[j+i];
			for(int j = 6; j >= 0; j--){
				if(count(combo, 4, full[j]) == 0){
					combo[4] = full[j];
					break;
				}
			}
			tmpnum = -1;
		}
	}

	for(int i = 0; i < 5; i++){
		if(nums[i+2]-nums[i]==0){
			tmpnum = 4;
			highthree = 1;
			threerang = nums[i];
			for(int j = 0; j < 3; j++){
				fullhouse[threeappender] = full[j+i];
				threeappender++;
			}
		}
		if(tmpnum >= *num){
			*num = tmpnum;
			int counter = 0;
			for(int j = 0; j < 3; j++){
				combo[j] = full[j+i];
			}
			for(int j = 6; j >= 0; j--){
				if((count(combo, 3, full[j]) == 0) && (counter < 2)){
					combo[3+counter] = full[j];
					counter++;
				}
			}
			tmpnum = -1;
		}
	}

	for(int i = 0; i < 6; i++){
		if(nums[i+1]-nums[i]==0){
			tmpnum = 2;
			for(int j = 0; j < 2; j++){
				twopair[twoappender] = full[j+i];
				twoappender++;
			}
			if(hightwo && (tworang != nums[i])) tmpnum = 3;
			if(highthree && (threerang != nums[i])) tmpnum = 7;
			hightwo = 1;
			tworang = nums[i];
		}
		if(tmpnum >= *num){
			*num = tmpnum;
			if(tmpnum == 2){
				for(int j = 0; j < 2; j++) combo[j] = full[j+i];
			}
			else{
				if(tmpnum == 3){
					for(int j = 0; j < 4; j++) combo[j] = twopair[twoappender-4+j];
				}
				else{
					if(tmpnum == 7){
						for(int j = 0; j < 3; j++) combo[j] = fullhouse[threeappender-3+j];
						for(int j = 3; j < 5; j++) combo[j] = twopair[twoappender-2+j-3];
					}
				}
			}
			int counter = 0;
			for(int j = 6; j >= 0; j--){
				if((tmpnum == 2) && (counter < 3)){
					if(count(combo, 2, full[j]) == 0){
						combo[2+counter] = full[j];
						counter++;
					}
				}
				else{
					if((tmpnum == 3) && (counter < 1)){
						if(count(combo, 4, full[j]) == 0){
							combo[4] = full[j];
							counter++;
						}
					}
					else break;
				}
			}
			tmpnum = -1;
		}
	}

	if(*num == 1){
		for(int i = 6; i >= 2; i--) combo[i-2] = full[i];
	}
}

void saveprogress(int bb, int pchips, int bchips){
	FILE *gamefile = fopen("game.save", "a+"); // На случай если файла не существует
	fclose(gamefile);
	gamefile = fopen("game.save", "w");
	fprintf(gamefile, "%d %d %d", bb, pchips, bchips);
	fclose(gamefile);
}

void loadprogress(int *bb, int *pchips, int *bchips){
	if(access("game.save", F_OK) == 0){
		FILE *gamefile = fopen("game.save", "r");
		fscanf(gamefile, "%d %d %d", bb, pchips, bchips);
		fclose(gamefile);
	}
}

void resetprogress(){
	FILE *gamefile = fopen("game.save", "w");
	fprintf(gamefile, "%d %d %d", 0, 10000, 10000);
	fclose(gamefile);
}

#include "graphics.c" 
#include "secondbot.c"
#include "firstbot.c"
#include "logging.c"

int main(){
	setlocale(LC_ALL, "");
	int row,col;
	int difficult, menuchoice, moveprior = 1, bb = 1;
	int bankchips, playerchips, botchips;
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

	if(chkwinsize()){
		getch();
		return 0;
	}

	start:

	if((menuchoice = mainmenu()) == 4){
		system("clear");
		return 0;
	}else{
		if(menuchoice == 3){
			resetprogress();
			goto start;
		}
		clear();
		if(menuchoice == 2){
			difficult = 3;
		}
		else{
			if((difficult = difficultymenu()) == 3){
				clear();
				goto start; 
			}
		}
	}

	srand(time(NULL));

	int vyborka = 1;

	replay:

	bankchips = 0, playerchips = 10000, botchips = 10000;

	int games = 0, ebotwins = 0, hbotwins = 0, draws = 0, drawsch = 0, ebotproc = 0, hbotproc = 0, ebotch = 0, hbotch = 0, hrebuy = botchips, erebuy = playerchips;

	while(1){
		stack* top = NULL;

		shuffle(&top);

		int playerhand[2], bothand[2], board[5];

		for(int i = 0; i < 5; i++){
			if(i < 2){
				bothand[i] = pop(&top);
				playerhand[i] = pop(&top);
			}
			board[i] = pop(&top);
		}

		/*int bothand[2] = {301, 501};
		int board[5] = {702, 304, 1404, 601, 901};
		int playerhand[2] = {802, 1203};*/

		bb  = !bb;

		int pcombnum = 1, bcombnum = 1;
		int pcombo[5], bcombo[5]; // Будет в дальнейшем использоваться для хайлайтинга комбинаций
		int whowin = 0; // 0 -draw, 1 - bot win, 2 - player win

		int hiddenbot = 1, onboard = 0;

		int playermove = 0, botmove = 0; // 1 - check, 3 - fold, * - bet(>=10)

		int equal = 0, first = 1;

		if(difficult == 3) loggame(1, botchips, playerchips, bankchips, botmove, playermove, bothand, playerhand, board, bb, onboard, equal, whowin, erebuy, hrebuy);
		else loadprogress(&bb, &playerchips, &botchips);

		if(difficult != 3){
			if(botchips < 200){
				botchips += 10000;
				hrebuy+=10000;
				loggame(6, botchips, playerchips, bankchips, botmove, playermove, bothand, playerhand, board, bb, onboard, equal, whowin, erebuy, hrebuy);
			}
			if(playerchips < 200){
				playerchips += 10000;
				erebuy+=10000;
				loggame(7, botchips, playerchips, bankchips, botmove, playermove, bothand, playerhand, board, bb, onboard, equal, whowin, erebuy, hrebuy);
			}
		}

		while(onboard <= 5){
			if(onboard == 0){
				if(bb){
					botmove=100;
					playermove=200;
				}
				else{
					playermove=100;
					botmove=200;
				}
				playerchips-=playermove;
				botchips-=botmove;
				bankchips+=playermove+botmove;

				equal = absolute(botmove-playermove);
			}

			if(difficult == 3) loggame(4, botchips, playerchips, bankchips, botmove, playermove, bothand, playerhand, board, bb, onboard, equal, whowin, erebuy, hrebuy);

			while(equal != 0 || first){
				if(bb){
					if(botchips == 0){
						botmove = 0;
						equal = 0;
					}
					else{
						if(difficult) botmove = secondbot(bothand, board, onboard, botchips, equal);
						else botmove = firstbot(bothand, board, onboard, botchips, equal, bankchips);
					}

					if(difficult == 3) loggame(2, botchips, playerchips, bankchips, botmove, playermove, bothand, playerhand, board, bb, onboard, equal, whowin, erebuy, hrebuy);

					if(botmove == 3){
						whowin = 2;
						break;
					}

					if(!first){
						if(botmove <= equal || (equal==0 && botmove == 1)){
							botmove = min(equal, botchips);
							botchips-=botmove;
							bankchips+=botmove;
							equal = 0;
						}
						else{
							botchips-=botmove;
							bankchips+=botmove;
							equal = botmove-equal;
						}
					}
					else{
						if(botmove > 3){
							botchips-=botmove;
							bankchips+=botmove;
							equal = botmove - equal;
						}
						else equal = 1;
					}

					if(equal <= 0){
						playermove = 0;
						break;
					}

					if(difficult == 3) playermove = secondbot(playerhand, board, onboard, playerchips, equal);
					else playermove = tablelogic(pcombnum, bcombnum, pcombo, bcombo, equal, bankchips, playerchips, botchips, onboard, board, bothand, playerhand, hiddenbot, 0, botmove, whowin, bb);

					if(difficult == 3) loggame(3, botchips, playerchips, bankchips, botmove, playermove, bothand, playerhand, board, bb, onboard, equal, whowin, erebuy, hrebuy);

					if(playermove == 3){
						whowin = 1;
						break;
					}

					if(equal == 1){
						if(playermove == 1) break;
						equal = 0;
					}

					if(playermove <= equal){
						playermove = min(equal, playerchips);
						playerchips-=playermove;
						bankchips+=playermove;
						equal = 0;
					}
					else{
						playerchips-=playermove;
						bankchips+=playermove;
						equal = playermove-equal;
					}
				}
				else{
					if(playerchips == 0){
						playermove = 0;
						equal = 0;
					}
					else{
						if(difficult == 3) playermove = secondbot(playerhand, board, onboard, playerchips, equal);
						else playermove = tablelogic(pcombnum, bcombnum, pcombo, bcombo, equal, bankchips, playerchips, botchips, onboard, board, bothand, playerhand, hiddenbot, 0, botmove, whowin, bb);
					}

					if(difficult == 3) loggame(3, botchips, playerchips, bankchips, botmove, playermove, bothand, playerhand, board, bb, onboard, equal, whowin, erebuy, hrebuy);

					if(playermove == 3){
						whowin = 1;
						break;
					}

					if(!first){
						if(playermove == equal || (equal==0 && playermove == 1)){
							playermove = min(equal, playerchips);
							playerchips-=playermove;
							bankchips+=playermove;
							equal = 0;
						}
						else{
							playerchips-=playermove;
							bankchips+=playermove;
							equal = playermove-equal;
						}
					}
					else{
						if(playermove > 3){
							playerchips-=playermove;
							bankchips+=playermove;
							equal = playermove - equal;
						}
						else equal = 1;
					}

					if(equal <= 0){
						botmove = 0;
						break;
					}

					if(difficult) botmove = secondbot(bothand, board, onboard, botchips, equal);
					else botmove = firstbot(bothand, board, onboard, botchips, equal, bankchips);

					if(difficult == 3) loggame(2, botchips, playerchips, bankchips, botmove, playermove, bothand, playerhand, board, bb, onboard, equal, whowin, erebuy, hrebuy);

					if(botmove == 3){
						whowin = 2;
						break;
					}

					if(equal == 1){
						if(botmove == 1) break;
						equal = 0;
					}

					if(botmove <= equal){
						botmove = min(equal, botchips);
						botchips-=botmove;
						bankchips+=botmove;
						equal = 0;
					}
					else{
						botchips-=botmove;
						bankchips+=botmove;
						equal = botmove-equal;
					}
				}
				first = 0;
			}
			equal = 0;
			if(whowin!=0) break;
			onboard < 2 ? onboard+=3 : onboard++;
			first = 1;
		}

		if(onboard>5) onboard = 5;

		chckcomb(board, bothand, &bcombnum, bcombo);
		chckcomb(board, playerhand, &pcombnum, pcombo);

		if(whowin == 0 && onboard == 5){
			if(bcombnum > pcombnum) whowin = 1;
			if(pcombnum > bcombnum) whowin = 2;
			if(pcombnum == bcombnum){
				for(int j=0; j<5; j++){
					if(bcombo[j]>pcombo[j]){
						whowin = 1;
						break;
					}
					if(pcombo[j]>bcombo[j]){
						whowin = 2;
						break;
					}
				}
			}
		}

		if(difficult == 3){
			if(bcombnum > pcombnum) hbotch+=1;
			if(pcombnum > bcombnum) ebotch+=1;
			if(pcombnum == bcombnum){
				int fl = 1;
				for(int j=0; j<5; j++){
					if(bcombo[j]>pcombo[j]){
						hbotch+=1;
						fl = 0;
						break;
					}
					if(pcombo[j]>bcombo[j]){
						ebotch+=1;
						fl = 0;
						break;
					}
				}
				if(fl) drawsch+=1;
			}
		}

		switch(whowin){
			case 0:
				draws+=1;
				playerchips+=bankchips/2;
				botchips+=bankchips/2;
				bankchips = 0;
				break;
			case 1:
				hbotwins+=1;
				botchips+=bankchips;
				bankchips = 0;
				break;
			case 2:
				ebotwins+=1;
				playerchips+=bankchips;
				bankchips = 0;
				break;
		}

		ebotproc = playerchips;
		hbotproc = botchips;

		if(difficult != 3) saveprogress(bb, playerchips, botchips);

		if(difficult != 3) tablelogic(pcombnum, bcombnum, pcombo, bcombo, 0, bankchips, playerchips, botchips, onboard, board, bothand, playerhand, 0, 1, botmove, whowin, bb);
		else loggame(5, botchips, playerchips, bankchips, botmove, playermove, bothand, playerhand, board, bb, onboard, equal, whowin, erebuy, hrebuy);
		games++;
		if(difficult != 3) goto start;
		else{
			if(games == 10000 || botchips == 0 || playerchips == 0) goto statistics;
		}
	}

	statistics:

	clear();
	int y, x, cury = 2;
	getmaxyx(stdscr, y,x);
	mvprintw(cury, x/3-10, "Поколение: %d", vyborka);
	mvprintw(cury, x/3-10, "Сыграно игр: %d", games);
	mvprintw(cury+1, x/3-10, "Выиграл Easy bot: %d", ebotwins);
	mvprintw(cury+1, x/3+30, "Выигрывал по раскладу: %d", ebotch);
	int eprofit = ebotproc-erebuy;
	mvprintw(cury+1, x/3+70, "Профит: $ %d", eprofit);
	int ereb = (erebuy-10000 > 0) ? (erebuy-10000)/10000 : 0;
	mvprintw(cury+1, x/3+110, "Докупался %d", ereb);
	mvprintw(cury+2, x/3-10, "Выиграл Hard bot: %d", hbotwins);
	mvprintw(cury+2, x/3+30, "Выигрывал по раскладу: %d", hbotch);
	int hprofit = hbotproc-hrebuy;
	mvprintw(cury+2, x/3+70, "Профит: $ %d", hprofit);
	int hreb = (hrebuy-10000 > 0) ? (hrebuy-10000)/10000 : 0;
	mvprintw(cury+2, x/3+110, "Докупался %d", hreb);
	mvprintw(cury+3, x/3-10, "Ничьи: %d, по раскладу: %d", draws, drawsch);
	logstat(games, ebotwins, ebotch, eprofit, ereb, hbotwins, hbotch, hprofit, hreb, draws, drawsch);
	if(vyborka == 1000){
		getch();
		goto start;
	}
	else{
		vyborka++;
		goto replay;
	}
	
	getch();
	endwin();
	return 0;
}

float bluff(){ // Случайная величина от 0 до 1 (чистый / абсолютный блеф)
	return (float)rand()/RAND_MAX;
}

int procbluff(int proc){ // Выпадение 1 с какой-то вероятностью (от 0 до 10) (процентный блеф / степень блефа)
	if(rand()%10 <= proc) return 1;
	return 0;
}

int ratehand(int *hand, int chips, int minbet){
	int maxbet = max(500, minbet);
	int randbet = 1;
	while(randbet <= 10) randbet = ((int)(bluff()*maxbet))/10*10;
	int num1 = hand[0]/100, num2 = hand[1]/100;
	int mast1 = hand[0]%100, mast2 = hand[1]%100;
	if(num1 == num2 || num1 > 10 || num2 > 10){
		int rnd = procbluff(7);
		if(rnd){
			int rnd2;
			if(minbet!=0) rnd2 = procbluff(1);
			else rnd2 = procbluff(2);
			if(rnd2) return chips;
			return randbet;
		}
		return 1;
	}
	else{
		int rnd2;
		if(minbet > (int)(0.15*(float)chips)) rnd2 = procbluff(6);
		else rnd2 = procbluff(3);
		if(rnd2) return 3;
		return 1;
	}
}

int rateall(int *hand, int *table, int onboard, int chips, int minbet){
	int maxbet = max(500, minbet);
	int randbet = 1;
	while(randbet <= 10) randbet = ((int)(bluff()*maxbet))/10*10;
	int n = 2+onboard;
	int full[n];
	for(int i = 0; i < n; i++){
		if(i < 2) full[i] = hand[i];
		else full[i] = table[i-2];
	}
	int nums[n], masti[n];
	for(int i = 0; i < n; i++){
		nums[i] = full[i]/100;
		masti[i] = full[i]%100;
	}

	if(n!=7){
		int nummask[n], mastmask[n];
		for(int i = 0; i < n; i++){
			nummask[i] = count(nums, n, nums[i]);
			mastmask[i] = count(masti, n, masti[i]);
		}
		int nmask = sum(nummask, n);
		int mmask = sum(mastmask, n);
		int abs = maxi(nums, n)-mini(nums, n);
		if(n == 5){
			if((nmask >= 7) || (mmask >= 9) || (nmask == 5 && abs < 5)){
				int rnd = procbluff(7);
				if(rnd){
					int rnd2;
					if(minbet!=0) rnd2 = procbluff(1);
					else rnd2 = procbluff(2);
					if(rnd2) return chips;
					return randbet;
				}
				return 1;
			}
			else{
				int rnd2;
				if(minbet > (int)(0.15*(float)chips)) rnd2 = procbluff(5);
				else rnd2 = procbluff(3);
				if(rnd2) return 3;
				return 1;
			}
		}

		if(n == 6){
			if((nmask > 10) || (mmask > 10) || ( (mmask == 10 || mmask == 8) && (nmask == 10 || nmask == 8) ) || (nmask == 6 && abs < 5)){
				int rnd = procbluff(7);
				if(rnd) return min(randbet, chips);
				return 1;
			}
			else{
				int rnd2;
				if(minbet > (int)(0.15*(float)chips)) rnd2 = procbluff(4);
				else rnd2 = procbluff(3);
				if(rnd2) return 3;
				return 1;
			}
		}
	}
	else{
		int goodtable = 0;
		int combnum = 1, combo[5];
		chckcomb(table, hand, &combnum, combo);
		int tnums[5], tmasti[5];
		for(int i = 0; i < 5; i++){
			tnums[i] = table[i]/100;
			tmasti[i] = table[i]%100;
		}
		int nummask[n], mastmask[n];
		for(int i = 0; i < 5; i++){
			nummask[i] = count(tnums, n, tnums[i]);
			mastmask[i] = count(tmasti, n, tmasti[i]);
		}
		int nmask = sum(nummask, n);
		int mmask = sum(mastmask, n);
		int abs = maxi(tnums, n)-mini(tnums, n);
		if((nmask > 7) || (mmask > 9) || (nmask == 5 && abs < 5)) goodtable = 1;
		if(combnum > 4){
			int rnd = procbluff(combnum);
			if(rnd){
				int rnd2 = procbluff(3-!goodtable);
				if(rnd2) return chips;
				return min(randbet, chips);
			}
			return 1;
		}
		else{
			int rnd2;
			if(minbet > (int)(0.15*(float)chips)) rnd2 = procbluff(4);
			else rnd2 = procbluff(2);
			if(rnd2) return 3;
			return 1;
		}
	}
}

int secondbot(int *hand, int *table, int onboard, int chips, int minbet){ // Функция вернёт значение хода по аналогии с игроком (1 - check, 3 - fold, * - bet(>=10))
	int move = 0;
	if(minbet > chips) minbet = chips;
	if(onboard == 0) move = ratehand(hand, chips, minbet);
	else move = rateall(hand, table, onboard, chips, minbet);

	if(move > 3 && move%10 != 0){
		int ost = move%10;
		move = (move/10)*10;
		if(ost>=5) move+=10;
	}
	if(move > chips) move = chips;
	if(move < minbet && move!=3) move = minbet;
	return move;
}
int abs(int a){
	return (a > 0) ? a : -1*a;
}

int smstr(int a, int b){
	int sm = 0;
	for(int i = a; i <= b; i++) sm+=i;
	return sm;
}

int combs(int *hand, int *table, int n){
	if(n == 5){
		int full[5];
		for(int i = 0; i < 5; i++){
			if(i<2) full[i]=hand[i];
			else full[i]=table[i-2];
		}
		int nums[5], masti[5];
		for(int i = 0; i < 5; i++){
			nums[i] = full[i]/100;
			masti[i] = full[i]%100;
		}
		int nmask[5], mmask[5];
		for(int i = 0; i < 5; i++){
			nmask[i] = count(nums, 5, nums[i]);
			mmask[i] = count(masti, 5, masti[i]);
		}
		int nsumm = sum(nmask, 7), msumm = sum(mmask, 7);
		int fl1 = 0, fl2 = 0;
		if(msumm == 25) fl1 = 1;
		if(smstr(mini(nums, 5), maxi(nums, 5))==sum(nums, 5)) fl2 = 1;
		if(fl1 && fl2) return 9;
		if(fl2){
			if(maxi(nums, 5) == 14) return 10;
			return 5;
		}
		if(nsumm == 17) return 8;
		if(nsumm == 13) return 7;
		if(fl1) return 6;
		if(nsumm == 11) return 4;
		if(nsumm == 9) return 3;
		if(nsumm == 7) return 2;
		return 1;
	}
	else{
		for(int j = 0; j < 6; j++){
			int full[5];
			int appender = 0;
			int fl = 0;
			for(int i = 0; i < 6; i++){
				if(i!=j){
					if(appender<2) full[appender]=hand[i-fl];
					else full[appender]=table[i-2-fl];
					appender++;
				}
				else{
					fl=1;
				}
			}
			int nums[5], masti[5];
			for(int i = 0; i < 5; i++){
				nums[i] = full[i]/100;
				masti[i] = full[i]%100;
			}
			int nmask[5], mmask[5];
			for(int i = 0; i < 5; i++){
				nmask[i] = count(nums, 5, nums[i]);
				mmask[i] = count(masti, 5, masti[i]);
			}
			int nsumm = sum(nmask, 7), msumm = sum(mmask, 7);
			int fl1 = 0, fl2 = 0;
			if(msumm == 25) fl1 = 1;
			if(smstr(mini(nums, 5), maxi(nums, 5))==sum(nums, 5)) fl2 = 1;
			if(fl1 && fl2) return 9;
			if(fl2){
				if(maxi(nums, 5) == 14) return 10;
				return 5;
			}
			if(nsumm == 17) return 8;
			if(nsumm == 13) return 7;
			if(fl1) return 6;
			if(nsumm == 11) return 4;
			if(nsumm == 9) return 3;
			if(nsumm == 7) return 2;
			return 1;
		}
	}
}

float handrate(int *hand){
	int n1 = hand[0]/100, n2 = hand[1]/100;
	int m1 = hand[0]%100, m2 = hand[1]%100;
	if(n1==n1){
		if(n1==14) return 0.85;
		if(n1==13) return 0.82;
		if(n1==12) return 0.8;
		if(n1==11) return 0.77;
		if(n1==10) return 0.75;
		if(n1==9) return 0.72;
		if(n1==8) return 0.69;
		if(n1==7) return 0.66;
		if(n1==6) return 0.63;
		if(n1==2) return 0.5;

		return (float)((10+rand()%40)/100.0);
	}
	if(abs(n1-n2)==1){
		if(n1==14 || n2==14){
			if(m1==m2) return 0.67;
			return 0.65;
		}
		if((n1==13 && n2==12) || (n1==12 && n2==13)){
			if(m1==m2) return 0.66;
			return 0.63;
		}
		if((n1==11 && n2==12) || (n1==12 && n2==11)){
			if(m1==m2) return 0.62;
			return 0.6;
		}
		if((n1==11 && n2==10) || (n1==10 && n2==11)){
			if(m1==m2) return 0.61;
			return 0.58;
		}
		if((n1==9 && n2==10) || (n1==10 && n2==9)){
			if(m1==m2) return 0.58;
			return 0.56;
		}
		if((n1==9 && n2==8) || (n1==8 && n2==9)){
			if(m1==m2) return 0.55;
			return 0.52;
		}
		if((n1==7 && n2==8) || (n1==8 && n2==7)){
			if(m1==m2) return 0.53;
			return 0.49;
		}
		if((n1==7 && n2==6) || (n1==6 && n2==7)){
			if(m1==m2) return 0.51;
			return 0.47;
		}
		if((n1==5 && n2==6) || (n1==6 && n2==5)){
			if(m1==m2) return 0.50;
			return 0.45;
		}
		return (float)((10+rand()%35)/100.0);
	}
	if((n1==14 && (n2==12 || n2==11)) || ((n1==12 || n1==11) && n2==14)){
		if(m1==m2) return 0.66;
		return 0.64;
	}
	if((n1==14 && n2==10) || (n1==12 && n2==10)){
		if(m1==m2) return 0.65;
		return 0.63;
	}
	return (float)((10+rand()%53)/100.0);
}

float pairrate(int *hand){
	int n1 = hand[0]/100, n2 = hand[1]/100;
	int m1 = hand[0]%100, m2 = hand[1]%100;

	if(n1==n2) return 0.19;
	if(m1==m2) return 0.1202;
	return 0.065;
}

float floprate(int combnum){
	switch(combnum){
	case 10:
		return 0.98;
		break;
	case 9:
		return 0.93;
		break;
	case 8:
		return 0.9;
		break;
	case 7:
		return 0.8;
		break;
	case 6:
		return 0.85;
		break;
	case 5:
		return 0.8;
		break;
	case 4:
		return 0.74;
		break;
	case 3:
		return 0.67;
		break;
	case 2:
		return 0.55;
		break;
	case 1:
		return 0.15;
		break;
	}
}

float floptoturn(int combnum){
	switch(combnum){
		case 1:
			return 0.16;
			break;
		case 2:
			return 0.171;
			break;
		case 3:
			return 0.085;
			break;
		case 4:
			return 0.15;
			break;
		default:
			return 0.38;
			break;
	}
}

float turnrate(int combnum){
	switch(combnum){
	case 10:
		return 0.98;
		break;
	case 9:
		return 0.98;
		break;
	case 8:
		return 0.95;
		break;
	case 7:
		return 0.9;
		break;
	case 6:
		return 0.88;
		break;
	case 5:
		return 0.82;
		break;
	case 4:
		return 0.74;
		break;
	case 3:
		return 0.65;
		break;
	case 2:
		return 0.50;
		break;
	case 1:
		return 0.05;
		break;
	}
}

float turntoriver(int combnum){
	switch(combnum){
		case 1:
			return 0.1521;
			break;
		case 2:
			return 0.174;
			break;
		case 3:
			return 0.087;
			break;
		case 4:
			return 0.227;
			break;
		default:
			return 0.38;
			break;
	}
}

float riverrate(int combnum){
	switch(combnum){
	case 10:
		return 0.99;
		break;
	case 9:
		return 0.98;
		break;
	case 8:
		return 0.97;
		break;
	case 7:
		return 0.81;
		break;
	case 6:
		return 0.77;
		break;
	case 5:
		return 0.72;
		break;
	case 4:
		return 0.61;
		break;
	case 3:
		return 0.45;
		break;
	case 2:
		return 0.34;
		break;
	case 1:
		return 0.15;
		break;
	}
}

int think(int *hand, int *table, int onboard, int chips, int minbet, int bank){
	int maxbet = max(max((int)(bank/3)/10*10, 300), minbet);
	int randbet = 1;
	while(randbet <= 10) randbet = ((int)(bluff()*maxbet))/10*10;
	if(onboard == 0){
		float proc = (pairrate(hand)+handrate(hand))/2.0;
		if(proc < 0.33){
			int rnd;
			if(minbet > (int)(0.1*(float)chips)) rnd = procbluff(3);
			else rnd = procbluff(6);
			if(rnd) return 1;
			return 3;
		}
		if(proc < 0.35){
			int rnd = procbluff(6);
			if(rnd){
				int rnd2 = procbluff(2);
				if(rnd2) return chips;
				return randbet;
			}
			return  1;
		}
		int rnd = procbluff(7);
		if(rnd){
			int rnd2;
			if(minbet!=0) rnd2 = procbluff(1);
			else rnd2 = procbluff(2);
			if(rnd2) return chips;
			return randbet;
		}
		return  1;
	}

	if(onboard == 3){
		int combnum = combs(hand, table, onboard+2);
		float proc = (floprate(combnum)+floptoturn(combnum))/2.0;
		if(proc > 0.4){
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
		int rnd;
		if(minbet > (int)(0.1*(float)chips)) rnd = procbluff(3);
		else rnd = procbluff(5);
		if(rnd) return 1;
		return 3;
	}

	if(onboard == 4){
		int combnum = combs(hand, table, onboard+2);
		float proc = (turnrate(combnum)+turntoriver(combnum))/2.0;
		if(proc > 0.45){
			int rnd = procbluff(6);
			if(rnd){
				int rnd2;
				if(minbet!=0) rnd2 = procbluff(1);
				else rnd2 = procbluff(2);
				if(rnd2) return chips;
				return randbet;
			}
			return 1;
		}
		int rnd;
		if(minbet > (int)(0.1*(float)chips)) rnd = procbluff(2);
		else rnd = procbluff(4);
		if(rnd) return 1;
		return 3;
	}

	if(onboard == 5){
		int combnum = 1, combo[5];
		chckcomb(table, hand, &combnum, combo);
		//float proc = (riverrate(combnum)+tablerate(table))/2.0;
		float proc = riverrate(combnum);
		if(proc > 0.5){
			int rnd = procbluff(5);
			if(rnd){
				int rnd2;
				if(minbet!=0) rnd2 = procbluff(1);
				else rnd2 = procbluff(2);
				if(rnd2) return chips;
				return randbet;
			}
			return 1;
		}
		int rnd;
		if(minbet > (int)(0.1*(float)chips)) rnd = procbluff(2);
		else rnd = procbluff(4);
		if(rnd) return 1;
		return 3;
	}
}

int firstbot(int *hand, int *table, int onboard, int chips, int minbet, int bank){
	if(minbet > chips) minbet = chips;

	int move = think(hand, table, onboard, chips, minbet, bank);

	if(move > 3 && move%10 != 0){
		int ost = move%10;
		move = (move/10)*10;
		if(ost>=5) move+=10;
	}
	if(move > chips) move = chips;
	if(move < minbet && move!=3) move = minbet;
	return move;
}
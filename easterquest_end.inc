functionEQ LoadEasterObjects(){
	new query[128];
    mysql_format(SQL, query, sizeof(query), "SELECT * FROM `easterquestobjects`");
	mysql_tquery(SQL, query, "LoadIepuras", "");
}
stock GetPlayerSprayedEggs(playerid){
	new ammount;
	for(new i; i <= eastertotalobjects; i++){
		if(PlayerEasterQuest[playerid][i] == 1) ammount++;
	}
	return ammount;
}
CMD:addeasterobject(playerid){
	if(PlayerInfo[playerid][pAdmin] < 7) return 1;
	if(eastertotalobjects == 30) return 1;
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	new queryEQ[128];
	mysql_format(SQL, queryEQ, sizeof(queryEQ), "INSERT INTO easterquestobjects (id, x, y, z) VALUES('%d','%f', '%f', '%f')",eastertotalobjects, x, y, z);
	mysql_tquery(SQL, queryEQ, "", "");
	eastertotalobjects++;
	format(queryEQ, 128, "Object Added! Resart the server for effect! Objects: %d", eastertotalobjects);
	SCM(playerid, -1, queryEQ);
	return 1;
}
CMD:startquest(playerid){
	if(!IsPlayerInRangeOfPoint(playerid, 2, -230.4442,2661.8601,62.6266)) return 1;
	if(ineaster[playerid] == 1) return 1;
	if(PlayerEasterQuestToday[playerid] == 1) return 1;
	if(GetPlayerSprayedEggs(playerid) == eastertotalobjects) return 1;
	ineaster[playerid] = 1;
	LoadPlayerEasterQuest(playerid);
	SCM(playerid, -1, "Ai inceput quest-ul de paste! Mergi la un 24/7 si cumpara un Spray Can pentru a vopsi ouale!");

	return 1;
}
CMD:buyspraycan(playerid, params[]){
	if(InBussines[playerid] > 0)
	if(BizzInfo[InBussines[playerid]][bType] == 6){
		if(GetPlayerCash(playerid) < 10000) return SCM(playerid, -1, "Ai nevoie de $10.000 pentru a cumpara un spray can!");
		GivePlayerCash(playerid, -10000);
		GivePlayerWeaponEx(playerid, 41, 1000);
		SCM(playerid, -1, "Ai cumparat un spraycan pentru a vopsi ouale! Tasteaza /questinfo pentru a vedea ce trebuie sa faci.");
	}
    return 1;
}
CMD:questinfo(playerid){
	new string[64];
	format(string, 64, "{ac75f4}Progress Quest: %d / %d", GetPlayerSprayedEggs(playerid), eastertotalobjects);
	SCM(playerid, -1, string);
	SCM(playerid, -1, "{ac75f4}Cumpara un spray can dintr-un magazin 24/7 folosind comanda /buyspraycan, apoi");
	SCM(playerid, -1, "{ac75f4}incepe quest-ul in Las Payasadas folosind comanda /startquest.");
	SCM(playerid, -1, "{ac75f4}Mergi langa un ou de paste si apasa LMB cu un spray can in mana pentru a-l colora.");
	SCM(playerid, -1, "{ac75f4}Quest-ul se reseteaza zilnic la ora 7:00 si NU se salveaza la relog.");
	return 1;
}
stock CheckEggRange(playerid, newkeys){
	if(newkeys == KEY_FIRE && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
		for(new i; i <= eastertotalobjects; i++){
			if(IsPlayerInRangeOfPoint(playerid, 2, ECInfo[i][qX], ECInfo[i][qY], ECInfo[i][qZ]))
			if(GetPlayerWeapon(playerid) == 41)
			if(PlayerEasterQuest[playerid][i] == 0){
				ShowPlayerSprayTextdraws(playerid);
				TogglePlayerControllable(playerid, 0);
				currentegg[playerid] = i;
				return 1;
			}
		}
	}

	else return 0;
	return 1;
}
functionEQ ShowPlayerSprayTextdraws(playerid){
	for(new glob; glob <= 10; glob++) TextDrawShowForPlayer(playerid, EasterTDGlobal[glob]);
	PlayerTextDrawShow(playerid, EasterTDPlayer[playerid][0]);
	PlayerTextDrawShow(playerid, EasterTDPlayer[playerid][1]);
	new progresstring[32];
	format(progresstring, 32, "Quest progress: %d/%d", GetPlayerSprayedEggs(playerid), eastertotalobjects);
	PlayerTextDrawSetString(playerid, EasterTDPlayer[playerid][1], progresstring);
	SelectTextDraw(playerid, 0xFFFF00FF);
	InEgg[playerid] = 1;
}
functionEQ HidePlayerSprayTextdraws(playerid){
	for(new glob; glob <= 10; glob++) TextDrawHideForPlayer(playerid, EasterTDGlobal[glob]);
	PlayerTextDrawHide(playerid, EasterTDPlayer[playerid][0]);
	PlayerTextDrawHide(playerid, EasterTDPlayer[playerid][1]);
	CancelSelectTextDraw(playerid);
	TogglePlayerControllable(playerid, 1);
	currentegg[playerid] = -1;
	InEgg[playerid] = 0;
}
functionEQ ResetSprAim(playerid){
	ClearAnimations(playerid);
	InSprayAnim[playerid] = 0;
	new eggspr;
	for(new i; i < 6; i++) if(eqclick[playerid][i][currentegg[playerid]] == 1) eggspr++;
	new progresstring[32];
	format(progresstring, 32, "Egg progress: %d %", floatround(16.6 * eggspr, floatround_round));
	PlayerTextDrawSetString(playerid, EasterTDPlayer[playerid][0], progresstring);
	SetPlayerObjectMaterial(playerid, currentegg[playerid] , 0, -1, "none", "none", 0xFFcc0066);
	if(eqclick[playerid][0][currentegg[playerid]] == 1 && eqclick[playerid][1][currentegg[playerid]] == 1 && eqclick[playerid][2][currentegg[playerid]] == 1 && eqclick[playerid][3][currentegg[playerid]] == 1 && eqclick[playerid][4][currentegg[playerid]] == 1 && eqclick[playerid][5][currentegg[playerid]] == 1){
		PlayerEasterQuest[playerid][currentegg[playerid]] = 1;
		new progresstring22[32];
		eqclick[playerid][0][currentegg[playerid]] = 0;
		eqclick[playerid][1][currentegg[playerid]] = 0;
		eqclick[playerid][2][currentegg[playerid]] = 0;
		eqclick[playerid][3][currentegg[playerid]] = 0;
		eqclick[playerid][4][currentegg[playerid]] = 0;
		eqclick[playerid][5][currentegg[playerid]] = 0;
		format(progresstring22, 32, "Quest progress: %d/%d", GetPlayerSprayedEggs(playerid), eastertotalobjects);
		RemovePlayerMapIcon(playerid, 99 - currentegg[playerid]);
		SCM(playerid, -1, progresstring22);
		DestroyPlayerObject(playerid, EasterEgg[playerid][currentegg[playerid]]);
		PlayerTextDrawSetString(playerid, EasterTDPlayer[playerid][0], "egg progress: 0 %");
		HidePlayerSprayTextdraws(playerid);
		if(GetPlayerSprayedEggs(playerid) == eastertotalobjects){
			new string[128];
			format(string, 128, "Iepurasul de paste:{ffffff} %s a terminat de vopsit toate oaule!", GetName(playerid));
			SendClientMessageToAll(0xff0000FF, string);
			new randmoney = 200000 + random(1800000);
			new randpp = 1 + random(3);
			new randrp = 2 + random(5);
			format(string, 128, "Ai terminat quest-ul de paste si ai primit $%s, %d RP si %d PP", FormatNumber(randmoney), randrp, randpp);
			SCM(playerid, -1, string);
			GivePlayerCash(playerid, randmoney);
			PlayerInfo[playerid][pPremiumPoints] += randpp;
			Update(playerid, pPremiumPointsx);
			PlayerInfo[playerid][pExp] += randrp;
			Update(playerid,pRP);
			
		}
	}
}

stock SprayClickCheck(playerid, Text:clickedid){
	for(new i = 3; i<= 8; i++){
		if(clickedid == EasterTDGlobal[i]){
			if(InEgg[playerid] == 1) SelectTextDraw(playerid, 0xFFFF00FF);
			if(InSprayAnim[playerid] == 1) return 1;
			TextDrawHideForPlayer(playerid, EasterTDGlobal[i]);
			ApplyAnimation(playerid, "GRAFFITI", "spraycan_fire", 4.1, 0, 0 ,0, 0, 0, 0);
			GameTextForPlayer(playerid, "~w~Spraying...", 5000, 4);
			InSprayAnim[playerid] = 1;
			
			eqclick[playerid][i - 3][currentegg[playerid]] = 1;
			
			SetTimerEx("ResetSprAim", 5000, 0, "ii", playerid);
		}
	}
	return 1;
}
functionEQ LoadEasterPlayerTD(playerid){
	
	EasterTDPlayer[playerid][0] = CreatePlayerTextDraw(playerid, 86.682373, 293.899932, "Egg progress: 0%");
	PlayerTextDrawLetterSize(playerid, EasterTDPlayer[playerid][0], 0.181647, 1.104166);
	PlayerTextDrawAlignment(playerid, EasterTDPlayer[playerid][0], 2);
	PlayerTextDrawColor(playerid, EasterTDPlayer[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, EasterTDPlayer[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, EasterTDPlayer[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, EasterTDPlayer[playerid][0], 255);
	PlayerTextDrawFont(playerid, EasterTDPlayer[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, EasterTDPlayer[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, EasterTDPlayer[playerid][0], 0);

	EasterTDPlayer[playerid][1] = CreatePlayerTextDraw(playerid, 86.682373, 304.699768, "quest progress: 29/30");
	PlayerTextDrawLetterSize(playerid, EasterTDPlayer[playerid][1], 0.181647, 1.104166);
	PlayerTextDrawAlignment(playerid, EasterTDPlayer[playerid][1], 2);
	PlayerTextDrawColor(playerid, EasterTDPlayer[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, EasterTDPlayer[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, EasterTDPlayer[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, EasterTDPlayer[playerid][1], 255);
	PlayerTextDrawFont(playerid, EasterTDPlayer[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, EasterTDPlayer[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, EasterTDPlayer[playerid][1], 0);
	
	eqclick[playerid][0][currentegg[playerid]] = 0;
	eqclick[playerid][1][currentegg[playerid]] = 0;
	eqclick[playerid][2][currentegg[playerid]] = 0;
	eqclick[playerid][3][currentegg[playerid]] = 0;
	eqclick[playerid][4][currentegg[playerid]] = 0;
	eqclick[playerid][5][currentegg[playerid]] = 0;
}
CMD:restartt(playerid) return SendRconCommand("gmx");
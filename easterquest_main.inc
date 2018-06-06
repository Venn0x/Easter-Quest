#define functionEQ%0(%1) forward%0(%1); public%0(%1)
new eastertotalobjects;
enum easterinfo{qID, Float:qX, Float:qY, Float:qZ}
new ECInfo[35][easterinfo];
new PlayerEasterQuestToday[MAX_PLAYERS];
new PlayerEasterQuest[MAX_PLAYERS][31];
new ineaster[MAX_PLAYERS];
new EasterEgg[MAX_PLAYERS][30];
new Text:EasterTDGlobal[11];
new PlayerText:EasterTDPlayer[MAX_PLAYERS][2];
new InSprayAnim[MAX_PLAYERS];
new InEgg[MAX_PLAYERS];
new eqclick[MAX_PLAYERS][6][30];
new currentegg[MAX_PLAYERS];
functionEQ ResetCheck(){
	new hour, minute, sec;
	gettime(hour, minute, sec);
	if(hour == 7 && minute == 0){
		for(new i; i < MAX_PLAYERS; i++){
			ResetEasterVars(i);
			for(new x; x <= eastertotalobjects; x++) RemovePlayerMapIcon(i, 99 - x);
			PlayerEasterQuestToday[i] = 0;
			new var[128];
			mysql_format(SQL, var, sizeof(var), "UPDATE `users` SET `todayquest`='0'");
			mysql_tquery(SQL,var,"","");
		}
	}
}

functionEQ LoadIepuras(){
	eastertotalobjects = cache_num_rows();
    for(new i = 0; i <= eastertotalobjects; i++)
    {
		ECInfo[i][qID]              		= cache_get_field_content_int(i, "id");
		ECInfo[i][qX]              	    	= cache_get_field_content_float(i, "x");
		ECInfo[i][qY]              	    	= cache_get_field_content_float(i, "y");
		ECInfo[i][qZ]              	    	= cache_get_field_content_float(i, "z");
	}
	printf("Easter Quest Objects: %d", eastertotalobjects);
	new pui = CreateActor(167, -230.4442,2661.8601,62.6266,277.8036);
	ApplyActorAnimation(pui, "SMOKING", "M_smklean_loop", 4.0, 1, 0, 0, 0, 0);
	Create3DTextLabel("Use {FFFF00}/startquest{FFFFFF} to start the easter quest", -1, -230.4442,2661.8601,62.6266, 20, 0, 0);
	LoadEasterGlobalTD();
	SetTimer("ResetCheck", 60000, 1);
}
functionEQ LoadPlayerEasterQuest(playerid){
	for(new i = 0; i <= eastertotalobjects ; i++){
		if(PlayerEasterQuest[playerid][i] == 0)
		if(ECInfo[i][qX] != 0 && ECInfo[i][qY] != 0 && ECInfo[i][qZ] != 0){
			EasterEgg[playerid][i] = CreatePlayerObject(playerid, 19341, ECInfo[i][qX], ECInfo[i][qY], ECInfo[i][qZ], 0, 0, 0, 0);
			SetPlayerObjectMaterial(playerid, EasterEgg[playerid][i] , 0, 5033, "union_las", "lasunion7", 0);
			SetPlayerMapIcon(playerid, 99 - i, ECInfo[i][qX], ECInfo[i][qY], ECInfo[i][qZ], 56, -1, MAPICON_GLOBAL);
		}
	}
}
functionEQ ResetEasterVars(playerid){
	ineaster[playerid] = 0;
	for(new i; i <= eastertotalobjects; i++){
		DestroyPlayerObject(playerid, EasterEgg[playerid][i]);
		PlayerEasterQuest[playerid][i] = 0;
		InSprayAnim[playerid] = 0;
		InEgg[playerid] = 0;
		eqclick[playerid][0][i] = 0;
		eqclick[playerid][1][i] = 0;
		eqclick[playerid][2][i] = 0;
		eqclick[playerid][3][i] = 0;
		eqclick[playerid][4][i] = 0;
		eqclick[playerid][5][i] = 0;
		currentegg[playerid] = -1;
		ineaster[playerid] = 0;
	}
	LoadEasterPlayerTD(playerid);
}
functionEQ LoadEasterGlobalTD(){
	EasterTDGlobal[0] = TextDrawCreate(35.705913, 180.666732, "box");
	TextDrawLetterSize(EasterTDGlobal[0], 0.000000, 11.317620);
	TextDrawTextSize(EasterTDGlobal[0], 135.000000, 0.000000);
	TextDrawAlignment(EasterTDGlobal[0], 1);
	TextDrawColor(EasterTDGlobal[0], 255);
	TextDrawUseBox(EasterTDGlobal[0], 1);
	TextDrawBoxColor(EasterTDGlobal[0], 255);
	TextDrawSetShadow(EasterTDGlobal[0], 0);
	TextDrawSetOutline(EasterTDGlobal[0], 0);
	TextDrawBackgroundColor(EasterTDGlobal[0], 255);
	TextDrawFont(EasterTDGlobal[0], 1);
	TextDrawSetProportional(EasterTDGlobal[0], 1);
	TextDrawSetShadow(EasterTDGlobal[0], 0);

	EasterTDGlobal[1] = TextDrawCreate(35.411758, 287.416809, "box");
	TextDrawLetterSize(EasterTDGlobal[1], 0.000000, 5.291110);
	TextDrawTextSize(EasterTDGlobal[1], 135.000000, 0.000000);
	TextDrawAlignment(EasterTDGlobal[1], 1);
	TextDrawColor(EasterTDGlobal[1], -16776961);
	TextDrawUseBox(EasterTDGlobal[1], 1);
	TextDrawBoxColor(EasterTDGlobal[1], 100);
	TextDrawSetShadow(EasterTDGlobal[1], 0);
	TextDrawSetOutline(EasterTDGlobal[1], 0);
	TextDrawBackgroundColor(EasterTDGlobal[1], 255);
	TextDrawFont(EasterTDGlobal[1], 2);
	TextDrawSetProportional(EasterTDGlobal[1], 1);
	TextDrawSetShadow(EasterTDGlobal[1], 0);

	EasterTDGlobal[2] = TextDrawCreate(26.858678, 162.599914, "");
	TextDrawLetterSize(EasterTDGlobal[2], 0.000000, 0.000000);
	TextDrawTextSize(EasterTDGlobal[2], 118.000000, 132.000000);
	TextDrawAlignment(EasterTDGlobal[2], 1);
	TextDrawColor(EasterTDGlobal[2], -1);
	TextDrawSetShadow(EasterTDGlobal[2], 0);
	TextDrawSetOutline(EasterTDGlobal[2], 0);
	TextDrawBackgroundColor(EasterTDGlobal[2], 0);
	TextDrawFont(EasterTDGlobal[2], 5);
	TextDrawSetProportional(EasterTDGlobal[2], 0);
	TextDrawSetShadow(EasterTDGlobal[2], 0);
	TextDrawSetPreviewModel(EasterTDGlobal[2], 19343);
	TextDrawSetPreviewRot(EasterTDGlobal[2], 0.000000, 0.000000, 0.000000, 1.000000);

	EasterTDGlobal[3] = TextDrawCreate(68.294113, 192.916748, "hud:radar_spray");
	TextDrawLetterSize(EasterTDGlobal[3], 0.000000, 0.000000);
	TextDrawTextSize(EasterTDGlobal[3], 12.000000, 13.000000);
	TextDrawAlignment(EasterTDGlobal[3], 1);
	TextDrawColor(EasterTDGlobal[3], -1);
	TextDrawSetShadow(EasterTDGlobal[3], 0);
	TextDrawSetOutline(EasterTDGlobal[3], 0);
	TextDrawBackgroundColor(EasterTDGlobal[3], 255);
	TextDrawFont(EasterTDGlobal[3], 4);
	TextDrawSetProportional(EasterTDGlobal[3], 0);
	TextDrawSetShadow(EasterTDGlobal[3], 0);
	TextDrawSetSelectable(EasterTDGlobal[3], true);

	EasterTDGlobal[4] = TextDrawCreate(84.764717, 206.333328, "hud:radar_spray");
	TextDrawLetterSize(EasterTDGlobal[4], 0.000000, 0.000000);
	TextDrawTextSize(EasterTDGlobal[4], 12.000000, 13.000000);
	TextDrawAlignment(EasterTDGlobal[4], 1);
	TextDrawColor(EasterTDGlobal[4], -1);
	TextDrawSetShadow(EasterTDGlobal[4], 0);
	TextDrawSetOutline(EasterTDGlobal[4], 0);
	TextDrawBackgroundColor(EasterTDGlobal[4], 255);
	TextDrawFont(EasterTDGlobal[4], 4);
	TextDrawSetProportional(EasterTDGlobal[4], 0);
	TextDrawSetShadow(EasterTDGlobal[4], 0);
	TextDrawSetSelectable(EasterTDGlobal[4], true);

	EasterTDGlobal[5] = TextDrawCreate(68.764701, 221.499954, "hud:radar_spray");
	TextDrawLetterSize(EasterTDGlobal[5], 0.000000, 0.000000);
	TextDrawTextSize(EasterTDGlobal[5], 12.000000, 13.000000);
	TextDrawAlignment(EasterTDGlobal[5], 1);
	TextDrawColor(EasterTDGlobal[5], -1);
	TextDrawSetShadow(EasterTDGlobal[5], 0);
	TextDrawSetOutline(EasterTDGlobal[5], 0);
	TextDrawBackgroundColor(EasterTDGlobal[5], 255);
	TextDrawFont(EasterTDGlobal[5], 4);
	TextDrawSetProportional(EasterTDGlobal[5], 0);
	TextDrawSetShadow(EasterTDGlobal[5], 0);
	TextDrawSetSelectable(EasterTDGlobal[5], true);

	EasterTDGlobal[6] = TextDrawCreate(85.705894, 232.583267, "hud:radar_spray");
	TextDrawLetterSize(EasterTDGlobal[6], 0.000000, 0.000000);	
	TextDrawTextSize(EasterTDGlobal[6], 13.000000, 13.000000);
	TextDrawAlignment(EasterTDGlobal[6], 1);
	TextDrawColor(EasterTDGlobal[6], -1);
	TextDrawSetShadow(EasterTDGlobal[6], 0);
	TextDrawSetOutline(EasterTDGlobal[6], 0);
	TextDrawBackgroundColor(EasterTDGlobal[6], 255);
	TextDrawFont(EasterTDGlobal[6], 4);
	TextDrawSetProportional(EasterTDGlobal[6], 0);
	TextDrawSetShadow(EasterTDGlobal[6], 0);
	TextDrawSetSelectable(EasterTDGlobal[6], true);

	EasterTDGlobal[7] = TextDrawCreate(67.352935, 247.166503, "hud:radar_spray");
	TextDrawLetterSize(EasterTDGlobal[7], 0.000000, 0.000000);
	TextDrawTextSize(EasterTDGlobal[7], 12.000000, 13.000000);
	TextDrawAlignment(EasterTDGlobal[7], 1);
	TextDrawColor(EasterTDGlobal[7], -1);
	TextDrawSetShadow(EasterTDGlobal[7], 0);
	TextDrawSetOutline(EasterTDGlobal[7], 0);
	TextDrawBackgroundColor(EasterTDGlobal[7], 255);
	TextDrawFont(EasterTDGlobal[7], 4);
	TextDrawSetProportional(EasterTDGlobal[7], 0);
	TextDrawSetShadow(EasterTDGlobal[7], 0);
	TextDrawSetSelectable(EasterTDGlobal[7], true);

	EasterTDGlobal[8] = TextDrawCreate(86.176483, 257.083190, "hud:radar_spray");
	TextDrawLetterSize(EasterTDGlobal[8], 0.000000, 0.000000);
	TextDrawTextSize(EasterTDGlobal[8], 12.000000, 13.000000);
	TextDrawAlignment(EasterTDGlobal[8], 1);
	TextDrawColor(EasterTDGlobal[8], -1);
	TextDrawSetShadow(EasterTDGlobal[8], 0);
	TextDrawSetOutline(EasterTDGlobal[8], 0);
	TextDrawBackgroundColor(EasterTDGlobal[8], 255);
	TextDrawFont(EasterTDGlobal[8], 4);
	TextDrawSetProportional(EasterTDGlobal[8], 0);
	TextDrawSetShadow(EasterTDGlobal[8], 0);
	TextDrawSetSelectable(EasterTDGlobal[8], true);

	EasterTDGlobal[9] = TextDrawCreate(51.882354, 283.916656, "Easter quest");
	TextDrawLetterSize(EasterTDGlobal[9], 0.218823, 1.051666);
	TextDrawAlignment(EasterTDGlobal[9], 1);
	TextDrawColor(EasterTDGlobal[9], -16776961);
	TextDrawSetShadow(EasterTDGlobal[9], 0);
	TextDrawSetOutline(EasterTDGlobal[9], 1);
	TextDrawBackgroundColor(EasterTDGlobal[9], 255);
	TextDrawFont(EasterTDGlobal[9], 2);
	TextDrawSetProportional(EasterTDGlobal[9], 1);
	TextDrawSetShadow(EasterTDGlobal[9], 0);

	EasterTDGlobal[10] = TextDrawCreate(86.682373, 315.899597, "Press click to spray");
	TextDrawLetterSize(EasterTDGlobal[10], 0.181647, 1.104166);
	TextDrawAlignment(EasterTDGlobal[10], 2);
	TextDrawColor(EasterTDGlobal[10], -1);
	TextDrawSetShadow(EasterTDGlobal[10], 0);
	TextDrawSetOutline(EasterTDGlobal[10], 1);
	TextDrawBackgroundColor(EasterTDGlobal[10], 255);
	TextDrawFont(EasterTDGlobal[10], 2);
	TextDrawSetProportional(EasterTDGlobal[10], 1);
	TextDrawSetShadow(EasterTDGlobal[10], 0);

}
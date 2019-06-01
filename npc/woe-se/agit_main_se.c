//================= Hercules Script =======================================
//=       _   _                     _
//=      | | | |                   | |
//=      | |_| | ___ _ __ ___ _   _| | ___  ___
//=      |  _  |/ _ \ '__/ __| | | | |/ _ \/ __|
//=      | | | |  __/ | | (__| |_| | |  __/\__ \
//=      \_| |_/\___|_|  \___|\__,_|_|\___||___/
//================= License ===============================================
//= This file is part of Hercules.
//= http://herc.ws - http://github.com/HerculesWS/Hercules
//=
//= Copyright (C) 2012-2015  Hercules Dev Team
//= Copyright (C)  Cookie
//= Copyright (C)  Euphy
//= Copyright (C)  Brian
//= Copyright (C)  Zephyrus
//= Copyright (C)  L0ne_W0lf
//=
//= Hercules is free software: you can redistribute it and/or modify
//= it under the terms of the GNU General Public License as published by
//= the Free Software Foundation, either version 3 of the License, or
//= (at your option) any later version.
//=
//= This program is distributed in the hope that it will be useful,
//= but WITHOUT ANY WARRANTY; without even the implied warranty of
//= MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//= GNU General Public License for more details.
//=
//= You should have received a copy of the GNU General Public License
//= along with this program.  If not, see <http://www.gnu.org/licenses/>.
//=========================================================================
//= War of Emperium SE - Template File
//================= Description ===========================================
//= Like agit_main, this file is required for SE castles to function.
//================= Current Version =======================================
//= 1.4a
//=========================================================================

//== Core, triggers all other events =======================
-	script	Manager#template	FAKE_NPC,{
OnAgitInit2:
OnRecvCastle2:
	if (strnpcinfo(2) == "template") end;
	/*
	if (!getcastledata(strnpcinfo(2),1)) {
		donpcevent strnpcinfo(0)+"::OnStart";
		// Monster spawns are identical for all castles.
		monster strnpcinfo(2),0,0,"Evil Druid",1117,10;
		monster strnpcinfo(2),0,0,"Khalitzburg",1132,4;
		monster strnpcinfo(2),0,0,"Abysmal Knight",1219,3;
		monster strnpcinfo(2),0,0,"Executioner",1205,1;
		monster strnpcinfo(2),0,0,"Penomena",1216,10;
		monster strnpcinfo(2),0,0,"Alarm",1193,18;
		monster strnpcinfo(2),0,0,"Clock",1269,9;
		monster strnpcinfo(2),0,0,"Raydric Archer",1276,12;
		monster strnpcinfo(2),0,0,"Wanderer",1208,3;
		monster strnpcinfo(2),0,0,"Alice",1275,1;
		monster strnpcinfo(2),0,0,"Bloody Knight",1268,2;
		monster strnpcinfo(2),0,0,"Dark Lord",1272,2;
		monster strnpcinfo(2),0,0,"Tower Keeper",1270,4;
	}
	*/
	if (getcastledata(strnpcinfo(2),9) < 1)
		disablenpc "Kafra Employee#"+substr(strnpcinfo(2),0,1)+substr(strnpcinfo(2),8,9);
	end;

OnAgitStart2:
	if (strnpcinfo(2) == "template") end;
	if (agitcheck2()) {
		maprespawnguildid strnpcinfo(2),getcastledata(strnpcinfo(2),1),2;
		gvgon strnpcinfo(2);
		donpcevent strnpcinfo(0)+"::OnStart";
	}
	else for(.@i = 0; .@i<4; ++.@i)
		donpcevent "RL"+.@i+"#"+strnpcinfo(2)+"::OnDisable";
	end;

OnAgitEnd2:
	if (strnpcinfo(2) == "template") end;
	gvgoff strnpcinfo(2);
	if (getcastledata(strnpcinfo(2),1)) {
		.@str$ = substr(strnpcinfo(2),0,1)+substr(strnpcinfo(2),8,9);
		killmonster strnpcinfo(2),"Steward#"+.@str$+"::OnStartArena";
		donpcevent strnpcinfo(0)+"::OnReset";
		donpcevent "Steward#"+.@str$+"::OnStop";
	}
	end;

OnGuildBreak:
	if (strnpcinfo(2) == "template") end;
	killmonster strnpcinfo(2),"gard1#"+strnpcinfo(2)+"::OnGuardianDied";
	killmonster strnpcinfo(2),"gard2#"+strnpcinfo(2)+"::OnGuardianDied";
	disablenpc "Kafra Employee#"+substr(strnpcinfo(2),0,1)+substr(strnpcinfo(2),8,9);
	setcastledata strnpcinfo(2),1,0;
	sleep 7000;
	announce "Le ch�teau de [ "+getcastlename(strnpcinfo(2))+" ] a �t� abandonn�.",0;
	donpcevent strnpcinfo(0)+"::OnRecvCastle2";
	end;

OnStart:
	// $agit_ar0x[] - $agit_sc0x[]
	// 1st Guardian stone, 2nd Guardian stone, Barrier 1, Barrier 2, Barrier 3, Summon Guardians
	// Settings for all but Summon Guardians: 0 = Okay | 1 = Destroyed | 2 = Repairing
	// Summon Guardians: 0 = Do not Summon | 1 = Summon
	if (getcastledata(strnpcinfo(2),1)) {
		setarray getd("$agit_"+substr(strnpcinfo(2),0,1)+substr(strnpcinfo(2),8,9)+"[0]"),0,0,0,0,0,0;
		donpcevent "df1#"+strnpcinfo(2)+"::OnEnable";
		donpcevent "df2#"+strnpcinfo(2)+"::OnEnable";
		for (.@i = 0; .@i<4; ++.@i)
			donpcevent "RL"+.@i+"#"+strnpcinfo(2)+"::OnEnable";
	}

OnEmpSpawn:
	.@str$ = substr(strnpcinfo(2),0,1)+substr(strnpcinfo(2),8,9);
	if (mobcount(strnpcinfo(2),"Steward#"+.@str$+"::OnStartArena")) end;
	if (compare(strnpcinfo(2),"arug")) {
		if (strnpcinfo(2) == "arug_cas01") setarray .@i[0],87,219;
		else if (strnpcinfo(2) == "arug_cas02") setarray .@i[0],89,256;
		else setarray .@i[0],141,293;	// Castles 3,4,5 are identical.
	}
	else {
		if (strnpcinfo(2) == "schg_cas02") setarray .@i[0],162,193;
		else if (strnpcinfo(2) == "schg_cas03") setarray .@i[0],338,202;
		else setarray .@i[0],120,272;	// Castles 1,4,5 are identical.
	}
	if (agitcheck2() == 1){
	monster strnpcinfo(2),.@i[0],.@i[1],"Emperium",1288,1,"Steward#"+.@str$+"::OnStartArena";
	}
	end;

OnReset:
	.@str$ = substr(strnpcinfo(2),0,1)+substr(strnpcinfo(2),8,9);
	donpcevent "df1#"+strnpcinfo(2)+"::OnDisable";
	donpcevent "df2#"+strnpcinfo(2)+"::OnDisable";
	donpcevent "gard1#"+strnpcinfo(2)+"::OnReset";
	donpcevent "gard2#"+strnpcinfo(2)+"::OnReset";
	donpcevent "1st Guardian Stone#"+.@str$+"::OnDisable";
	donpcevent "2nd Guardian Stone#"+.@str$+"::OnDisable";
	for(.@i = 1; .@i<4; ++.@i)
		donpcevent "Control Device0"+.@i+"#"+.@str$+"::OnDisable";
	for(.@i = 0; .@i<4; ++.@i)
		donpcevent "RL"+.@i+"#"+strnpcinfo(2)+"::OnDisable";
	if (agitcheck2())
		setarray getd("$agit_"+substr(strnpcinfo(2),0,1)+substr(strnpcinfo(2),8,9)+"[0]"),0,0,1,1,1,0;
	end;

OnChange:
	.@str$ = substr(strnpcinfo(2),0,1)+substr(strnpcinfo(2),8,9);
	setarray getd("$agit_"+.@str$+"[0]"),2,2,1,1,2,0;
	donpcevent strnpcinfo(0)+"::OnEmpSpawn";
	donpcevent "Control Device03#"+.@str$+"::OnEnable";
	donpcevent "1st Guardian Stone#"+.@str$+"::OnEnable";
	donpcevent "2nd Guardian Stone#"+.@str$+"::OnEnable";
	end;

OnClock2230:
	// Spawn Treasure Chests based on castle economy.
	if (strnpcinfo(2) == "template") end;
	if (!getcastledata(strnpcinfo(2),1)) end;
	killmonster strnpcinfo(2),strnpcinfo(0)+"::OnTreasureDied";
	if (getcastledata(strnpcinfo(2),4)) {
		.@Economy = getcastledata(strnpcinfo(2),2);
		setcastledata strnpcinfo(2),2,.@Economy+getcastledata(strnpcinfo(2),4)+(rand(2) && getgdskilllv(getcastledata(strnpcinfo(2),1),10014));
		if (getcastledata(strnpcinfo(2),2) > 100) setcastledata strnpcinfo(2),2,100;
		setcastledata strnpcinfo(2),4,0;
	}
	if (getcastledata(strnpcinfo(2),5)) {
		.@defence = getcastledata(strnpcinfo(2),3);
		setcastledata strnpcinfo(2),3,.@defence+getcastledata(strnpcinfo(2),5);
		if (getcastledata(strnpcinfo(2),3) > 100) setcastledata strnpcinfo(2),3,100;
		setcastledata strnpcinfo(2),5,0;
	}
	.@Treasure = getcastledata(strnpcinfo(2),2)/5+4;
	if (!.@Treasure) end;
	freeloop(1);
	if (compare(strnpcinfo(2),"arug")) {
		
		if (strnpcinfo(2) == "arug_cas05") {
			.@treasurebox = 1324;
			setarray .@treasurex[0],291,292,293,294,295,296,293,294,295,296,297,298,291,292,293,294,295,296,293,294,295,296,297,298;
			setarray .@treasurey[0],276,276,276,276,276,276,274,274,274,274,274,274,272,272,272,272,272,272,269,269,269,269,269,269;
		}
	}
	for(.@i = 0; .@i<4; ++.@i)
		monster strnpcinfo(2),.@treasurex[.@i],.@treasurey[.@i],"Treasure Chest",1324,1,strnpcinfo(0)+"::OnTreasureDied";
	for(.@i = 4; .@i<24; ++.@i) {
		if (.@Treasure < .@i+1) break;
		monster strnpcinfo(2),.@treasurex[.@i],.@treasurey[.@i],"Treasure Chest",1324,1,strnpcinfo(0)+"::OnTreasureDied";
	}//(.@i%2)?
	freeloop(0);
	end;

OnTreasureDied:
	end;
}

//== Guild Manager =========================================
-	script	Steward#template	FAKE_NPC,{
	.@GID = getcastledata(strnpcinfo(4),1);
	if (!.@GID) {
		mes "[ Steward ]";
		mes "I await for the master";
		mes "whom destiny will choose";
		mes "for me. Do you think you";
		mes "have to courage and strength";
		mes "to conquer this stronghold?";
		close;
	}
	if (getcharid(2) != .@GID || strcharinfo(0) != getguildmaster(.@GID)) {
		mes "[ Steward ]";
		mes "Hmpf. Your threats don't";
		mes "scare me! Guardians, drive";
		mes "this infidel away from here!";
		mes "I will always be loyal to the";
		mes "master of this stronghold,";
		mes "the one and only ^FF0000"+getguildmaster(.@GID)+"^000000.";
		close;
	}
	mes "[ Steward ]";
	mes "Ah, Master ^FF0000"+getguildmaster(.@GID)+"^000000...";
	mes "How shall I serve you today?";
	mes "Was there an aspect of this";
	mes "stronghold's maintenance";
	mes "you wanted to discuss?";
	next;
	switch(select("Stronghold Briefing", "Invest in Commercial Growth", "Invest in Defense growth", "Hire/Fire Storage Staff", "Go to Master's room")) {
	case 1:
		mes "[ Steward ]";
		mes "The Commercial Growth";
		mes "Level of the stronghold is ^0000ff"+getcastledata(strnpcinfo(4),2)+".";
		if (getcastledata(strnpcinfo(4),4) > 0) {
			mes "Last time, you invested in";
			mes "Commercial Growth "+getcastledata(strnpcinfo(4),4)+".";
		}
		next;
		mes "[ Steward ]";
		mes "Our stronghold's";
		mes "safeguard level is "+getcastledata(strnpcinfo(4),3)+".";
		if (getcastledata(strnpcinfo(4),5) > 0) {
			mes "Last time, you invested";
			mes "in defense "+getcastledata(strnpcinfo(4),5)+" times.";
		}
		mes " ";
		mes "That is all, master.";
		close;
	case 2:
		.@Economy = getcastledata(strnpcinfo(4),2);
		setarray .@cost[0],5000,10000,20000,35000,55000,80000,110000,145000,185000,230000,280000,335000,395000,460000,530000,605000,685000,770000,860000,955000;
		.@j = 0;
		for(.@i = 6; .@i<101; .@i += 5) {
			if (.@Economy < .@i) {
				.@eco_invest = .@cost[.@j];
				break;
			}
			++.@j;
		}
		// Quadruple the cost of investing if you've already invested once.
		if (getcastledata(strnpcinfo(4),4))
			.@eco_invest *= 4;
		mes "[ Steward ]";
		mes "Raising the stronghold's";
		mes "commercial growth will";
		mes "increase the quantity of";
		mes "goods produced for the guild.";
		mes "Investing in commercial growth";
		mes "will help the guild's future.";
		next;
		mes "[ Steward ]";
		mes "You can make one investment";
		mes "each day, but if you can make";
		mes "two investments if you pay";
		mes "more Zeny: this will speed";
		mes "up commercial development,";
		mes "but can be quite expensive.";
		next;
		if (.@Economy == 100) {
			mes "[ Steward ]";
			mes "However, our stronghold's";
			mes "commerical growth level is";
			mes "at 100%. It's not possible to";
			mes "develop commercial growth";
			mes "any further than that.";
			close;
		}
		if (getcastledata(strnpcinfo(4),4) >= 2) {
			mes "[ Steward ]";
			mes "You've already made two";
			mes "investments today, so you'll";
			mes "have to wait until tomorrow";
			mes "to make another investment.";
			close;
		}
		if (getcastledata(strnpcinfo(4),4) == 0) {
			mes "[ Steward ]";
			mes "You must pay ^FF0000"+.@eco_invest+"^000000 Zeny";
			mes "to make an investment";
			mes "Will you invest in this";
			mes "stronghold's commerical";
			mes "development now?";
		}
		else {
			mes "[ Steward ]";
			mes "You must pay ^FF0000"+.@eco_invest+"^000000";
			mes "more Zeny to make a second";
			mes "investment today. Will you";
			mes "invest one more time?";
		}
		next;
		switch(select("Invest in Commercial Growth", "Cancel")) {
		case 1:
			if (getcastledata(strnpcinfo(4),4) >= 2) {
				mes "[ Steward ]";
				mes "You've already made two";
				mes "investments today, so you'll";
				mes "have to wait until tomorrow";
				mes "to make another investment.";
				close;
			}
			if (Zeny < .@eco_invest) {
				mes "[ Steward ]";
				mes "I'm sorry, Master, but";
				mes "you do not have enough";
				mes "Zeny to make an investment";
				mes "for the guild today.";
				close;
			}
			Zeny -= .@eco_invest;
			setcastledata strnpcinfo(4),4,getcastledata(strnpcinfo(4),4)+1;
			mes "[ Steward ]";
			mes "A wise use of the guild's";
			mes "funds, Master. We can expect";
			mes "to see the results of this";
			mes "investment by tomorrow.";
			close;
		case 2:
			mes "[ Steward ]";
			mes "As you command, Master.";
			close;
		}
	case 3:
		.@defence = getcastledata(strnpcinfo(4),3);
		setarray .@cost[0],10000,20000,40000,70000,110000,160000,220000,290000,370000,460000,560000,670000,790000,920000,1060000,1210000,1370000,1540000,1720000,1910000;
		.@j = 0;
		for(.@i = 6; .@i<101; .@i += 5) {
			if (.@defence < .@i) {
				.@def_invest = .@cost[.@j];
				break;
			}
			++.@j;
		}
		// Quadruple the cost of investing if you've already invested once.
		if (getcastledata(strnpcinfo(4),5))
			.@def_invest *= 4;
		mes "[ Steward ]";
		mes "Investing in our stronghold's";
		mes "defense will enhance the";
		mes "durability of our Guardians";
		mes "and the Emperium. We'll need";
		mes "every advantage to protect";
		mes "ourselves from our enemies.";
		next;
		mes "[ Steward ]";
		mes "You can invest in defense";
		mes "once per day, but if you pay";
		mes "more Zeny, you can invest";
		mes "a maximum of two times daily.";
		next;
		mes "[ Steward ]";
		if (getcastledata(strnpcinfo(4),3) == 100) {
			mes "The Defense Level of this";
			mes "stronghold is 100%, and";
			mes "cannot be increased further.";
			close;
		}
		if (getcastledata(strnpcinfo(4),5) >= 2) {
			mes "Master, you've already";
			mes "invested in Defense twice";
			mes "today. You'll need to wait";
			mes "until tomorrow if you really";
			mes "want to increase our defenses.";
			close;
		}
		if (getcastledata(strnpcinfo(4),5) == 0) {
			mes "We need ^FF0000"+.@def_invest+"^000000";
			mes "Zeny to invest in our";
			mes "stronghold's defenses.";
			mes "Will you invest now?";
		}
		else {
			mes "We need ^FF0000"+.@def_invest+"^000000";
			mes "Zeny to invest in our";
			mes "stronghold's defenses";
			mes "a second time today.";
			mes "Will you invest now?";
		}
		next;
		switch(select("Invest in Defense", "Cancel")) {
		case 1:
			if (getcastledata(strnpcinfo(4),5) >= 2) {
				mes "[ Steward ]";
				mes "Master, you've already";
				mes "invested in Defense twice";
				mes "today. You'll need to wait";
				mes "until tomorrow if you really";
				mes "want to increase our defenses.";
				close;
			}
			if (Zeny < .@def_invest) {
				mes "[ Steward ]";
				mes "I'm sorry, Master, but";
				mes "you do not have enough";
				mes "Zeny to make an investment";
				mes "for the guild today.";
				close;
			}
			Zeny -= .@def_invest;
			setcastledata strnpcinfo(4),5,getcastledata(strnpcinfo(4),5)+1;
			mes "[ Steward ]";
			mes "A wise use of the guild's";
			mes "funds, Master. Increasing";
			mes "the frequency of treasure";
			mes "procured by the guild will";
			mes "definitely help us all.";
			close;
		case 2:
			mes "[ Steward ]";
			mes "As you command, Master.";
			close;
		}
	case 4:
		if (getcastledata(strnpcinfo(4),9) == 1) {
			mes "[ Steward ]";
			mes "Do you wish to dismiss";
			mes "the Kafra Employee that";
			mes "we've hired for the guild?";
			next;
			switch(select("Dismiss", "Cancel")) {
			case 1:
				cutin "kafra_01",2;
				mes "[ Hired Kafra Employee ]";
				mes "Master, please reconsider!";
				mes "I've been working very hard";
				mes "for the success of the guild!";
				mes "I'll try harder to serve the";
				mes "guild members of this";
				mes "stronghold, I promise!";
				next;
				switch(select("Dismiss", "Cancel")) {
				case 1:
					mes "[ Hired Kafra Employee ]";
					mes "Why?! What have I done";
					mes "to deserve this? Waaah~!";
					next;
					cutin "kafra_01",255;
					break;
				case 2:
					mes "[ Hired Kafra Employee ]";
					mes "Thank you, Master!";
					mes "I'll obey your every";
					mes "command as best I can!";
					mes "You won't regret this!";
					close;
				}
				break;
			case 2:
				mes "[ Steward ]";
				mes "She works very hard,";
				mes "in my opinion. It was in";
				mes "all of our best interests to";
				mes "allow her to stay with us.";
				close;
			}
			disablenpc "Kafra Employee#"+strnpcinfo(2);
			setcastledata strnpcinfo(4),9,0;
			mes "[ Steward ]";
			mes "That Kafra Employee";
			mes "has been dismissed.";
			mes "Were really dissatisfied";
			mes "by the quality of her service?";
			close;
		}
		else {
			mes "[ Steward ]";
			mes "Will you hire a";
			mes "Kafra Employee to serve";
			mes "our stronghold? You must";
			mes "pay ^FF000010,000 Zeny^000000 to hire one.";
			next;
			switch(select("Hire", "Cancel")) {
			case 1:
				if (getgdskilllv(.@GID,10001) == 0) {
					mes "[ Steward ]";
					mes "Master, we cannot hire a";
					mes "Kafra Employee because";
					mes "you have not yet attained";
					mes "the ^FF0000Contract with Kafra^000000";
					mes "guild skill.";
					close;
				}
				if (Zeny < 10000) {
					mes "[ Steward ]";
					mes "Master, we cannot hire a";
					mes "Kafra Employee because";
					mes "we do not have enough";
					mes "funds to pay the contract fee.";
					close;
				}
				Zeny -= 10000;
				enablenpc "Kafra Employee#"+strnpcinfo(2);
				setcastledata strnpcinfo(4),9,1;
				mes "[ Steward ]";
				mes "Very well. We have formed";
				mes "a contract with the Kafra";
				mes "Head Office, and hired a";
				mes "Kafra Employee for our";
				mes "stronghold. Here she is~";
				next;
				cutin "kafra_01",2;
				mes "[ Hired Kafra Employee ]";
				mes "How do you do? I've";
				mes "been dispatched by the";
				mes "Kafra Head Office to";
				mes "serve your guild's needs.";
				mes "I'll do my best to follow";
				mes "your every command, Master.";
				next;
				cutin "kafra_01",255;
				mes "[ Steward ]";
				mes "Our contract will expire";
				mes "after one month, so we must";
				mes "pay additional fees to keep";
				mes "this Kafra Employee in";
				mes "the service of our guild.";
				close;
			case 2:
				mes "[ Steward ]";
				mes "As you command, Master.";
				mes "However, I suggest hiring";
				mes "a Kafra Employee as soon";
				mes "as possible since our guild";
				mes "would greatly benefit from";
				mes "the convenient Kafra services.";
				close;
			}
		}
	case 5:
		mes "[ Steward ]";
		mes "Do you wish to enter the";
		mes "Guild Treasure Room?";
		mes "Only you, the Guild Master,";
		mes "are permitted to enter.";
		next;
		mes "[ Steward ]";
		mes "Please remember to open";
		mes "the Treasure Boxes at the";
		mes "proper time. Otherwise, the";
		mes "treasure may disappear if";
		mes "something unexpected happens.";
		next;
		switch(select("Go to Treasure Room", "Cancel")) {
		case 1:
			mes "[ Steward ]";
			mes "Allow me to guide you";
			mes "on the secret path to";
			mes "the Treasure Room.";
			mes "Press the secret switch";
			mes "when you wish to return here.";
			close2;
			if (compare(strnpcinfo(4),"arug")) {
				if (strnpcinfo(4) == "arug_cas01") setarray .@i[0],250,363;
				else if (strnpcinfo(4) == "arug_cas02") setarray .@i[0],382,227;
				else setarray .@i[0],292,266;	// Castles 3,4,5 are identical.
			}
			else {
				if (strnpcinfo(4) == "schg_cas02") setarray .@i[0],249,373;
				else if (strnpcinfo(4) == "schg_cas03") setarray .@i[0],190,16;
				else setarray .@i[0],381,381;	// Castles 1,4,5 are identical.
			}
			warp strnpcinfo(4),.@i[0],.@i[1];
			end;
		case 2:
			mes "[ Steward ]";
			mes "Items in the Treasure Room";
			mes "are produced once each day.";
			mes "Therefore, you must obtain";
			mes "the treasure items everyday.";
			mes "For the sake of the guild,";
			mes "prioritize treasure harvesting!";
			close;
		}
	}

OnStop:
	awake strnpcinfo(0);
	end;

OnStartArena:
	.@GID = getcharid(2);
	.@region$ = (compare(strnpcinfo(4),"arug"))?"Valfreyja":"Nithafjoll";
	// Lower castle Economy
	.@Economy = getcastledata(strnpcinfo(4),2)-5;
	if (.@Economy < 0) .@Economy = 0;
	setcastledata strnpcinfo(4),2,.@Economy;
	// Lower Castle Defence
	.@defence = getcastledata(strnpcinfo(4),3)-5;
	if (.@defence < 0) .@defence = 0;
	setcastledata strnpcinfo(4),3,.@defence;
	// Set new owner
	setcastledata strnpcinfo(4),1,.@GID;
	// Clear castle's data.
	for(.@i = 4; .@i<10; ++.@i)
		setcastledata strnpcinfo(4),.@i,0;
	// Disable Kafra
	disablenpc "Kafra Employee#"+strnpcinfo(2);

	announce "La guilde [ "+getguildname(.@GID)+" ] a conquis le ch�teau de "+getcastlename(strnpcinfo(4))+" !",bc_all|bc_woe;
	mapannounce strnpcinfo(4),"L'emperium a �t� d�truit.",bc_map,"0x00FF00",FW_NORMAL,20,0,40;
	donpcevent "Manager#"+strnpcinfo(4)+"::OnReset";
	maprespawnguildid strnpcinfo(4),getcastledata(strnpcinfo(4),1),2;
	donpcevent "Manager#"+strnpcinfo(4)+"::OnRecvCastle2";
	donpcevent "::OnRecvCastle"+ strtoupper( substr( strnpcinfo(2), 0, 0 ) ) + substr( strnpcinfo(2), 1, getstrlen( strnpcinfo(2) ) -1 );
	sleep 10000;
	if (agitcheck2()) {
		donpcevent "Manager#"+strnpcinfo(4)+"::OnChange";
		mapannounce strnpcinfo(4),"Reconstruisez vos d�fenses et gardien pour s�curiser votre ch�teau !",bc_map,"0x00FF00",FW_NORMAL,20,0,40;
	}
	end;
}

//== Castle Guardians ======================================
-	script	Guardian#template	FAKE_NPC,{
	.@GID = getcastledata(strnpcinfo(4),1);
	.@n$ = "["+strnpcinfo(1)+"]";
	if (!.@GID) {
		mes .@n$;
		mes "Great job. Now, all you";
		mes "need to do is destroy this";
		mes "Emperium to gain ownership";
		mes "over this stronghold.";
		close;
	}
	if (getcharid(2) == .@GID) {
		if (strcharinfo(0) != getguildmaster(.@GID)) {
			mes .@n$;
			mes "As guardian of this";
			mes "stronghold, I answer only";
			mes "to the master of the guild";
			mes "that controls this place.";
			close;
		}
		else {
			if (!agitcheck2()) {
				mes .@n$;
				mes "I am "+strnpcinfo(1)+", guardian of";
				mes "this stronghold. For now,";
				mes "all is quiet in this place.";
				next;
				switch(select("Converse", "Cancel")) {
				case 1:
					mes .@n$;
					mes "Do you have any questions";
					mes "about this stronghold?";
					next;
					switch(select("Guardian Stones", "Fortress Gates", "Link Flags", "Battle Strategy", "Cancel")) {
					case 1:
						mes .@n$;
						mes "There is one Emperium";
						mes "and two Guardian Stones in";
						mes "each fortress. These stones";
						mes "are the first line of defense,";
						mes "and must be destroyed before";
						mes "enemies can even enter.";
						next;
						mes .@n$;
						mes "The stones are located in";
						mes "^4D4DFFGate Houses^000000 which must be";
						mes "protected to prevent enemies";
						mes "from reaching the Emperium.";
						mes "Guardian Stones can ^4D4DFFrecall";
						mes "your Guardians^000000 for protection.";
						next;
						mes .@n$;
						mes "Fortresses with higher levels";
						mes "of defense can summon more";
						mes "Guardians: this is why it is";
						mes "so important for guilds to";
						mes "invest in Defense Growth.";
						next;
						mes .@n$;
						mes "Guardian Stones that have";
						mes "been destroyed can be revived";
						mes "after a certain time, but one of the guild members must give";
						mes "me the order. I can also report the status of the Guardian Stones.";
						close;
					case 2:
						mes .@n$;
						mes "^4D4DFFFortress Gates^000000 are the second  line of guild stronghold defense,";
						mes "and are protected by extra barricades activated by the Guardian Stones.";
						mes "These gates are located in three different parts of the fortress.";
						next;
						mes .@n$;
						mes "Barricades are protected by";
						mes "Guardian Stones, and are";
						mes "restored when the Guardian";
						mes "Stones are retrieved. However,";
						mes "it is not as easy to restore";
						mes "destroyed Fortress Gates.";
						next;
						mes .@n$;
						mes "Fortress Gates can only be";
						mes "restored when the ^4D4DFFguild";
						mes "master of a stronghold";
						mes "changes^000000, or if ^4D4DFFrestoration";
						mes "is requested by the guild";
						mes "master of the stronghold^000000.";
						close;
					case 3:
						mes .@n$;
						mes "Strongholds have many";
						mes "Link Flags that allow you";
						mes "to access vital areas within";
						mes "restrictions placed by the";
						mes "Barricades. Usually, ^4D4DFFFlag 1";
						mes "links to the Gate House^000000.";
						next;
						mes .@n$;
						mes "Many flags link directly to";
						mes "the flag near the Emperium.";
						mes "The final numbered flag is";
						mes "linked to the Convenience";
						mes "Facility of the stronghold's";
						mes "owner. Keep this in mind.";
						close;
					case 4:
						mes .@n$;
						mes "Strategy? It would be better";
						mes "to develop your battle plan to";
						mes "exploit your guild's advantages";
						mes "and your enemies' weaknesses.";
						mes "Use the Gate Houses and Barricades, and rebuild as quickly as you can!";
						close;
					case 5:
						mes .@n$;
						mes "You have no questions";
						mes "to ask of me? Well, I'm";
						mes "here to serve your needs.";
						close;
					}
				case 2:
					mes .@n$;
					mes "I'm always here, so";
					mes "feel free to request my";
					mes "assistance whenever";
					mes "the need arises.";
					close;
				}
			}
			else {
				mes .@n$;
				mes "Greetings, "+strcharinfo(0)+".";
				mes "What are your orders?";
				next;
				switch(select("Increase Stronghold Defense", "Situational Briefing", "Cancel")) {
				case 1:
					if (!getd("$agit_"+strnpcinfo(2)+"[5]")) {
						if (getgdskilllv(.@GID,10002) == 0) {
							mes .@n$;
							mes "I'm sorry, but the Guardian";
							mes "Stones aren't powerful enough";
							mes "to summon Guardians yet. We";
							mes "need to accumulate more";
							mes "knowledge before they can";
							mes "summon any Guardians.";
							close;
						}
						else {
							mes .@n$;
							mes "I shall endeavor to summon";
							mes "a Guardian through a Guardian";
							mes "Stone. However, keep in mind";
							mes "that this will not work if the";
							mes "Guardian Stone is destroyed.";
							setd "$agit_"+strnpcinfo(2)+"[5]",1;
							if (!getd("$agit_"+strnpcinfo(2)+"[0]"))
								donpcevent "gard1#"+strnpcinfo(4)+"::OnEnable";
							if (!getd("$agit_"+strnpcinfo(2)+"[1]"))
								donpcevent "gard2#"+strnpcinfo(4)+"::OnEnable";
							close;
						}
					}
					else {
						mes .@n$;
						mes "You've already commanded";
						mes "me to summon a Guardian";
						mes "to defend the stronghold.";
						close;
					}
				case 2:
					mes .@n$;
					mes "Our defense status is...";
					setarray .@status$[0],"^4D4DFFOperational","^FF0000Destroyed","^008000Repairing";
					mes "1st Guardian Stone: "+.@status$[getd("$agit_"+strnpcinfo(2)+"[0]")]+"^000000";
					mes "2nd Guardian Stone: "+.@status$[getd("$agit_"+strnpcinfo(2)+"[1]")]+"^000000";
					mes "1st Fortress Gate: "+.@status$[getd("$agit_"+strnpcinfo(2)+"[2]")]+"^000000";
					mes "2nd Fortress Gate: "+.@status$[getd("$agit_"+strnpcinfo(2)+"[3]")]+"^000000";
					mes "3rd Fortress Gate: "+.@status$[getd("$agit_"+strnpcinfo(2)+"[4]")]+"^000000";
					close;
				case 3:
					mes .@n$;
					mes "I'll be standing by,";
					mes "awaiting your orders.";
					close;
				}
			}
		}
	}
	else {
		mes .@n$;
		mes "Who are you? Scoundrel!";
		mes "Leave this stronghold now!";
		close;
	}

OnInit:
	setarray getd("$agit_"+strnpcinfo(2)+"[0]"),0,0,0,0,0,0;
	end;
}

//== Guild Kafras ==========================================
-	script	Kafra#template	FAKE_NPC,{
	cutin "kafra_01",2;
	.@GID = getcastledata(strnpcinfo(4),1);
	if (getcharid(2) == .@GID && getgdskilllv(.@GID,10001)) {
		mes "[Kafra Employee]";
		mes "Welcome, proud member";
		mes "of the ^FF0000"+getguildname(.@GID)+"^000000 Guild!";
		mes "The Kafra Corporation is ready";
		mes "to assist you wherever you go!";
		next;
		switch(select("Use Storage", "Use Warp Service", "Rent Pushcart", "Cancel")) {
		case 1:
			if (basicskillcheck() && getskilllv("NV_BASIC") < 6) {
				mes "[Kafra Employee]";
				mes "I'm so sorry, but you must";
				mes "have at least Novice Skill";
				mes "Lv.6 to use the Storage.";
			}
			else openstorage;
			break;
		case 2:
			mes "[Kafra Employee]";
			mes "Please tell me your";
			mes "Warp destination.";
			next;
			switch(select("Rachel -> 200 z", "Cancel")) {
			case 1:
				if (Zeny < 200) {
					mes "[Kafra Employee]";
					mes "I'm sorry, but you don't";
					mes "have enough Zeny to pay";
					mes "the warp fee. Would you";
					mes "please check your funds again?";
					close2;
					cutin "kafra_01",255;
					end;
				}
				Zeny -= 200;
				warp "rachel",115,125;
				end;
			case 2:
				cutin "kafra_01",255;
				break;
			}
			break;
		case 3:
			if (BaseClass != Job_Merchant) {
				mes "[Kafra Employee]";
				mes "I'm sorry, but the Pushcart";
				mes "rental service can only be";
				mes "used by Merchant, Blacksmith,";
				mes "and Alchemist class characters.";
			}
			else if (checkcart() == 1) {
				mes "[Kafra Employee]";
				mes "Hm? You've already";
				mes "rented a Pushcart.";
			}
			else {
				mes "[Kafra Employee]";
				mes "The Pushcart rental fee";
				mes "is 800 Zeny. Would you";
				mes "like to rent a Pushcart?";
				next;
				switch(select("Rent Pushcart", "Cancel")) {
				case 1:
					if (Zeny < 800) {
						mes "[Kafra Employee]";
						mes "I'm sorry, but you don't";
						mes "have enough Zeny to rent";
						mes "one of our Pushcarts.";
						close2;
						cutin "kafra_01",255;
						end;
					}
					Zeny -= 800;
					setcart;
					break;
				case 2:
					break;
				}
			}
			break;
		case 4:
			mes "[Kafra Employee]";
			mes "Thank you for using the";
			mes "Kafra Service. Wherever";
			mes "you go, Kafra will be";
			mes "there to support you!";
			close2;
			cutin "kafra_01",255;
			end;
		}
		close2;
		cutin "kafra_01",255;
		end;
	}
	else {
		mes "[Kafra Employee]";
		mes "I'm sorry, but I've been";
		mes "exclusively contracted";
		mes "to the members of the";
		mes "^FF0000"+getguildname(.@GID)+"^000000 Guild.";
		mes "You'll have to ask another";
		mes "Kafra Employee to help you...";
		close2;
		cutin "kafra_01",255;
		end;
	}
}

//== Guardian Stones (2) ===================================
-	script	Guardian Stone#template	FAKE_NPC,{
	.@GID = getcastledata(strnpcinfo(4),1);
	.@num = atoi(charat(strnpcinfo(1),0));
	.@var$ = "$agit_"+strnpcinfo(2);
	if (getcharid(2) == .@GID) {
		mes "^3355FFYou will need the";
		mes "following materials to";
		mes "rebuild a destroyed";
		mes "Guardian Stone.^000000";
		next;
		mes "1 Oridecon";
		mes "1 Elunium";
		mes "30 Stones";
		mes "5 Blue Gemstones";
		mes "5 Yellow Gemstones";
		mes "5 Red Gemstones";
		next;
		mes "^3355FFDo you want to continue?^000000";
		next;
		if(select("No", "Continue") == 1) {
			mes "^3355FFWork canceled.^000000";
			close;
		}
		if ((countitem(Oridecon) > 0) && (countitem(Elunium) > 0) && (countitem(Stone) > 29) && (countitem(Blue_Gemstone) > 4) && (countitem(Yellow_Gemstone) > 4) && (countitem(Red_Gemstone) > 4)) {
			mes "^3355FFArrange Stones, Elunium, and";
			mes "Oridecon, in that order, in the";
			mes "center. Then you must arrange";
			mes "the enchanted Gemstones to";
			mes "rebuild the Guardian Stone.^000000";
			next;
			setarray .@stone$[0],"Elunium","Oridecon","Stones";
			.@i = select("Elunium", "Oridecon", "Stone")-1;
			if (.@i == 2) .@nice += 10;
			mes "^3355FF"+.@stone$[.@i]+" has been";
			mes "placed in the center.^000000";
			next;
			.@i = select("Elunium", "Oridecon", "Stone")-1;
			if (.@i == 0) .@nice += 10;
			mes "^3355FFYou have lined the";
			mes "outside of the center";
			mes "with some "+.@stone$[.@i]+".^000000";
			next;
			.@i = select("Elunium", "Oridecon", "Stone")-1;
			if (.@i == 1) .@nice += 10;
			mes "^3355FFYou covered the";
			mes "rest of the materials";
			mes "with some "+.@stone$[.@i]+".^000000";
			next;
			mes "^3355FFNow you need to arrange";
			mes "the enchanted Gemstones";
			mes "accordingly. You can identify";
			mes "their Magic properties by";
			mes "their casting effect.^000000";
			next;
			setarray .@effect[0],56,54,225;
			setarray .@color$[0],"Red","Yellow","Blue";
			while(1) {
				if (.@roof0 > 7) break;
				.@i = rand(3);
				specialeffect .@effect[.@i];
				mes "^3355FFThe Gemstones must";
				mes "be arranged in the correct";
				mes "order according to their";
				mes "magic properties and power.^000000";
				next;
				.@j = select("Red Gemstone", "Yellow Gemstone", "Blue Gemstone")-1;
				mes "^3355FFYou placed the "+.@color$[.@j]+" Gemstone.^000000";
				if (.@i == .@j) {
					mes "^3355FFHowever, the Guardian Stone";
					mes "Repair System failed because";
					mes "of a magic power conflict.^000000";
					close;
				}
				.@nice += 10;
				++.@roof0;
				specialeffect EF_STEAL;
				next;
			}
			if (.@nice > 90) {
				if (!getd(.@var$+"["+(.@num-1)+"]")) {
					mes "^3355FFThe Guardian Stone";
					mes "Repair System has";
					mes "already completed.^000000";
					close;
				}
				else {
					if (!agitcheck2()) {
						mes "^3355FFIt is impossible to";
						mes "rebuild the Guardian";
						mes "Stone because the";
						mes "Emperium is not present.^000000";
						close;
					}
					else {
						mes "^3355FFThe Gemstones have been";
						mes "arranged, and the Guardian";
						mes "Stone is successfully repaired.^000000";
						delitem Oridecon,1;
						delitem Elunium,1;
						delitem Stone,30;
						delitem Blue_Gemstone,5;
						delitem Yellow_Gemstone,5;
						delitem Red_Gemstone,5;
						close2;
						donpcevent "df"+.@num+"#"+strnpcinfo(4)+"::OnEnable";
						specialeffect EF_ICECRASH;
						disablenpc strnpcinfo(0);
						setd .@var$+"["+(.@num-1)+"]",0;
						.@df_all = getd(.@var$+"[0]")+getd(.@var$+"[1]");
						if (!.@df_all) {
							mapannounce strnpcinfo(4),"Both Guardian Stones have been erected, bolstering this stronghold's defenses!",bc_map,"0x00ff00";
							donpcevent "RL0#"+strnpcinfo(4)+"::OnEnable";
						}
						else mapannounce strnpcinfo(4),"The "+strnpcinfo(1)+" has been repaired successfully.",bc_map,"0x00ff00";
						if (getd(.@var$+"[5]") == 1)
							donpcevent "gard"+.@num+"#"+strnpcinfo(4)+"::OnEnable";
						end;
					}
				}
			}
			else {
				mes "^3355FFAfter all of that work...";
				mes "It looks like you failed";
				mes "to fix the Guardian Stone,";
				mes "and lost some materials.^000000";
				delitem Stone,10;
				delitem Blue_Gemstone,2;
				delitem Yellow_Gemstone,2;
				delitem Red_Gemstone,2;
				close;
			}
		}
		else {
			mes "^3355FFYou don't have enough";
			mes "materials to repair";
			mes "the Guardian Stone.^000000";
			close;
		}
	}
	end;

OnInit:
OnDisable:
	disablenpc strnpcinfo(0);
	end;

OnEnable:
	enablenpc strnpcinfo(0);
	specialeffect EF_MAPPILLAR2;
	end;
}

//== Control Devices (3) ===================================
-	script	Control#template	FAKE_NPC,{
	.@GID = getcastledata(strnpcinfo(4),1);
	.@num = atoi(charat(strnpcinfo(1),15));
	.@var$ = "$agit_"+strnpcinfo(2);
	if (getcharid(2) == .@GID) {
		if (strcharinfo(0) == getguildmaster(.@GID)) {
			if (getd(.@var$+"["+(.@num+1)+"]") == 2) {
				mes "^3355FFDemolished Fortress";
				mes "Gates can be repaired,";
				mes "but you will need to gather";
				mes "the following materials.^000000";
				next;
				mes "^4D4DFF10 Steel^000000,";
				mes "^4D4DFF30 Trunks^000000,";
				mes "^4D4DFF5 Oridecon^000000, and";
				mes "^4D4DFF10 Emveretarcon^000000.";
				next;
				select("Continue");
				if ((countitem(Wooden_Block) > 29) && (countitem(Steel) > 9) && (countitem(Emveretarcon) > 9) && (countitem(Oridecon) > 4)) {
					mes "^3355FFYou will need Trunks to";
					mes "repair the support frame,";
					mes "Oridecon to enhance the";
					mes "gate's endurance, and";
					mes "Emveretarcon to basically";
					mes "hold everything together.^000000";
					next;
					.@ro_of01 = rand(10,15);
					while(1) {
						if (.@ro_of02 == .@ro_of01) break;
						else {
							switch(rand(1,4)) {
							case 1:
								mes "^3355FFThe support frame";
								mes "is badly damaged:";
								mes "fixing this part";
								mes "is a top priority.^000000";
								next;
								switch(select("Trunk", "Steel", "Emveretarcon", "Oridecon")) {
								case 1:
									mes "^3355FFThe frame has been";
									mes "reinforced with wood.^000000";
									++.@rp_temp;
									++.@ro_of02;
									specialeffect2 EF_REPAIRWEAPON;
									next;
									break;
								case 2:
									mes "^3355FFYou tried using steel,";
									mes "but it's not working very";
									mes "well. You'll have to try";
									mes "something else.^000000";
									close;
								case 3:
									mes "^3355FFYou tried using emveretarcon";
									mes "to reinforce the gate, but it's";
									mes "not working well at all.";
									mes "You'll have to start over.^000000";
									close;
								case 4:
									mes "^3355FFYou tried using oridecon,";
									mes "but it's not working very";
									mes "well. You'll have to try";
									mes "something else.^000000";
									close;
								}
								break;
							case 2:
								mes "^3355FFIt looks like the gate's";
								mes "overall endurance needs to";
								mes "be reinforced with something.^000000";
								next;
								switch(select("Trunk", "Steel", "Emveretarcon", "Oridecon")) {
								case 1:
									mes "^3355FFYou tried using wood";
									mes "to reinforce the gate.^000000";
									++.@ro_of02;
									next;
									break;
								case 2:
									mes "^3355FFYou tried using steel";
									mes "to reinforce the gate, but";
									mes "it's not working well at all.";
									mes "You'll have to start over.^000000";
									close;
								case 3:
									mes "^3355FFYou tried using emveretarcon";
									mes "to reinforce the gate, but it's";
									mes "not working well at all.";
									mes "You'll have to start over.^000000";
									close;
								case 4:
									mes "^3355FFYou hammered the";
									mes "oridecon: it looks";
									mes "like this will work.^000000";
									++.@rp_temp;
									++.@ro_of02;
									specialeffect2 EF_REPAIRWEAPON;
									next;
									break;
								}
								break;
							case 3:
								mes "^3355FFThe damage to the gate";
								mes "has caused all these";
								mes "cracks. You'll have to";
								mes "weld them solid somehow.^000000";
								next;
								switch(select("Trunk", "Steel", "Emveretarcon", "Oridecon")) {
								case 1:
									mes "^3355FFYou tried using wood to fix";
									mes "this problem, but it seems";
									mes "to have made it worse.";
									mes "You'll have to start all over.^000000";
									close;
								case 2:
									mes "^3355FFYou used steel to weld";
									mes "all the cracks: the gate is";
									mes "is starting to look more solid.^000000";
									++.@rp_temp;
									++.@ro_of02;
									specialeffect2 EF_REPAIRWEAPON;
									next;
									break;
								case 3:
									mes "^3355FFYou tried using emveretarcon";
									mes "to reinforce the gate, but it's";
									mes "not working well at all.";
									mes "You'll have to start over.^000000";
									close;
								case 4:
									mes "^3355FFYou tried using oridecon,";
									mes "but it's not working very";
									mes "well. You'll have to try";
									mes "something else.^000000";
									close;
								}
								break;
							case 4:
								mes "^3355FFNow you need to make";
								mes "sure that the gate is held";
								mes "together pretty solidly.^000000";
								next;
								switch(select("Trunk", "Steel", "Emveretarcon", "Oridecon")) {
								case 1:
									mes "^3355FFYou tried using wood to fix";
									mes "this problem, but it seems";
									mes "to have made it worse.";
									mes "You'll have to start all over.^000000";
									close;
								case 2:
									mes "^3355FFYou tried using steel,";
									mes "but it's not working very";
									mes "well. You'll have to try";
									mes "something else.^000000";
									close;
								case 3:
									mes "^3355FFYou successfully used";
									mes "the emveretarcon to repair";
									mes "much of the gate's damage.^000000";
									++.@rp_temp;
									++.@ro_of02;
									specialeffect2 EF_REPAIRWEAPON;
									next;
									break;
								case 4:
									mes "^3355FFYou tried using oridecon,";
									mes "but it's not working very";
									mes "well. You'll have to try";
									mes "something else.^000000";
									close;
								}
							}
						}
					}
					mes "^3355FFWell, it looks like";
					mes "you're just about done";
					mes "with repairing the gate.^000000";
					next;
					if (!agitcheck2()) {
						mes "^3355FFUnfortunately, the Fortress";
						mes "Gate can't be reconstructed:";
						mes "the Emperium is no longer here.^000000";
						close;
					}
					else {
						if (.@rp_temp == .@ro_of01) {
							mes "^3355FFThe Fortress Gate has";
							mes "been successfully repaired!^000000";
							delitem Wooden_Block,30;
							delitem Steel,10;
							delitem Emveretarcon,10;
							delitem Oridecon,5;
							close2;
							donpcevent "RL"+.@num+"#"+strnpcinfo(4)+"::OnEnable";
							disablenpc strnpcinfo(0);
							if (.@num == 1) .@str$ = "1st";
							else if (.@num == 2) .@str$ = "2nd";
							else if (.@num == 3) .@str$ = "3rd";
							mapannounce strnpcinfo(4),"The "+.@str$+" Fortress Gate has been reconstructed!",bc_map,"0x00ff00";
							if (.@num == 1) setd .@var$+"[2]",0;
							else {
								setarray getd(.@var$+"["+.@num+"]"),2,0;
								donpcevent "Control Device0"+(.@num-1)+"#"+strnpcinfo(2)+"::OnEnable";
							}
							end;
						}
						else {
							mes "^3355FFThe wall has been breached,";
							mes "and the attempt to repair the";
							mes "Fortress Gate has failed.";
							mes "You lost some of your";
							mes "repair resources...^000000";
							delitem Oridecon,2;
							delitem Steel,4;
							delitem Wooden_Block,14;
							delitem Emveretarcon,3;
							close;
						}
					}
				}
				else {
					mes "^3355FFYou can't attempt to repair";
					mes "the Fortress Gate if you don't";
					mes "have all the needed materials.^000000";
					close;
				}
			}
		}
	}
	end;

OnInit:
OnDisable:
	disablenpc strnpcinfo(0);
	end;

OnEnable:
	enablenpc strnpcinfo(0);
	end;
}

//== Guardian Summoners (2) ================================
-	script	gard#template	FAKE_NPC,{
OnEnable:
	// .@x[i],.@y[i]: Normal coordinates, #0-21.
	// .@w[x],.@w[y]: Special coordinates if 'defence' is under 11.
	if (compare(strnpcinfo(2),"arug")) {
		if (strnpcinfo(2) == "arug_cas01") {
			setarray .@w[0],195,250,292,188;
			setarray .x[0],233,252,232,201,224,196,269,252,201,224,222, 294,256,240,246,235,235,246,240,256,254,242;
			setarray .y[0], 83, 81,108,130,168,137, 89, 81,130,168,129, 210,203,133, 92,132,132, 92,133,203, 95,151;
		}
		else if (strnpcinfo(2) == "arug_cas02") {
			setarray .@w[0],20,169,268,169;
			setarray .x[0],104,67,67,113,122,67, 90, 91,122, 20,67, 175,204,211,209,161,186,183,150,161,209,211;
			setarray .y[0], 32,36,85, 87,112,60,167,119,112,169,85,  31, 32, 63, 88, 91,170,121,110, 91, 88, 63;
		}
		else {	// Castles 3,4,5 are identical.
			setarray .@w[0],66,157,211,159;
			setarray .x[0],130,128,128,128,110,91,65, 65,110,128,128, 156,172,154,156,155,187,212,211,155,156,172;
			setarray .y[0], 60, 77, 90,100, 96,53,71,103, 96,100, 77, 101, 95, 90, 77, 60, 54, 67,105, 60, 77, 95;
		}
	}
	else {
		if (strnpcinfo(2) == "schg_cas02") {
			setarray .@w[0],337,95,307,222;
			setarray .x[0],326,337,334,296,285,236,285,296,334,337,334, 359,300,337,317,307,300,337,317,307,359,236;
			setarray .y[0], 83, 95,119, 82, 40, 41, 40, 82,119, 95,119,  85,119,154,183,222,119,154,183,222, 85, 41;
		}
		else if (strnpcinfo(2) == "schg_cas03") {
			setarray .@w[0],306,325,364,305;
			setarray .x[0],323,273,288,306,323,323,273,288,306,273,273, 338,364,365,317,338,338,364,365,317,364,329;
			setarray .y[0],308,309,306,326,308,308,309,306,325,309,309, 309,305,261,318,310,309,305,261,318,305,314;
		}
		else {	// Castles 1,4,5 are identical.
			setarray .@w[0],108,32,128,42,187,15;	// Contains an extra pair, for whatever reason.
			setarray .x[0],111,109,65,110,88,64,47,109,111,112,120, 130,129,151,187,128,152,187,128,130,130,151;
			setarray .y[0], 18, 44,22, 40,20,40,43, 48, 18, 32, 37,  22, 47, 18, 15, 42, 43, 15, 42, 22, 28, 18;
		}
	}
	if (charat(strnpcinfo(1),4) == "2")
		.@z = 11;
	freeloop(1);
	.@defence = getcastledata(strnpcinfo(2),3);
	callsub OnSummon,.@z;
	if (.@defence > 70) set getd(".MyMobCount_"+charat(strnpcinfo(1),4)+strnpcinfo(2)),5;
	else if (.@defence > 50) set getd(".MyMobCount_"+charat(strnpcinfo(1),4)+strnpcinfo(2)),4;
	else if (.@defence > 30) set getd(".MyMobCount_"+charat(strnpcinfo(1),4)+strnpcinfo(2)),3;
	else if (.@defence > 10) set getd(".MyMobCount_"+charat(strnpcinfo(1),4)+strnpcinfo(2)),2;
	if (.@w[4] && .@z)
		guardian strnpcinfo(2),.@w[4],.@w[5],"Guardian Soldier",1899,strnpcinfo(0)+"::OnGuardianDied";
	else if (.@defence < 11) {
		set getd(".MyMobCount_"+charat(strnpcinfo(1),4)+strnpcinfo(2)),2;
		.@i = (.@z)?2:0;
		guardian strnpcinfo(2),.@w[.@i],.@w[.@i+1],"Guardian Soldier",1899,strnpcinfo(0)+"::OnGuardianDied";
	}
	else for(.@i = 1; .@i<getd(".MyMobCount_"+charat(strnpcinfo(1),4)+strnpcinfo(2)); ++.@i)
		callsub OnSummon,.@i+.@z;
	freeloop(0);
	copyarray getd(".x_"+strnpcinfo(2)+"[0]"),.@x[0],22;
	copyarray getd(".y_"+strnpcinfo(2)+"[0]"),.@y[0],22;
	setd ".timer_"+charat(strnpcinfo(1),4)+strnpcinfo(2),4+.@z;
	setarray .count$[5],"1st","2nd","3rd","4th","5th";
	initnpctimer;
	end;

OnTimer300000:
OnTimer900000:
OnTimer1800000:
OnTimer2700000:
OnTimer3600000:
	if (charat(strnpcinfo(1),4) == "2") end;
	.@var$ = ".timer_"+charat(strnpcinfo(1),4)+strnpcinfo(2);
	setd .@var$, getd(.@var$)+1;
	set getd(".MyMobCount_"+charat(strnpcinfo(1),4)+strnpcinfo(2)),getd(".MyMobCount_"+charat(strnpcinfo(1),4)+strnpcinfo(2))+1;
	callsub OnSummon,getd(.@var$);
	setarray .count$[5],"1st","2nd","3rd","4th","5th";
	mapannounce strnpcinfo(2),"The "+.count$[getd(.@var$)]+" Guardian has been summoned from the Gate House.",bc_map,"0xff4500";
	if (getd(.@var$) == 9) {
		setd .@var$,0;
		stopnpctimer;
	}
	end;

OnTimer600000:
OnTimer1200000:
OnTimer2100000:
OnTimer3000000:
OnTimer3900000:
	if (!(charat(strnpcinfo(1),4) == "2")) end;
	.@var$ = ".timer_"+charat(strnpcinfo(1),4)+strnpcinfo(2);
	setd .@var$, getd(.@var$)+1;
	set getd(".MyMobCount_"+charat(strnpcinfo(1),4)+strnpcinfo(2)),getd(".MyMobCount_"+charat(strnpcinfo(1),4)+strnpcinfo(2))+1;
	callsub OnSummon,getd(.@var$);
	if (getd(.@var$) == 20) {
		setd .@var$,0;
		stopnpctimer;
	}
	end;

OnSummon:
	guardian strnpcinfo(2),getd(".x_"+strnpcinfo(2)+"["+getarg(0)+"]"),getd(".y_"+strnpcinfo(2)+"["+getarg(0)+"]"),"Guardian Soldier",1899,strnpcinfo(0)+"::OnGuardianDied";
	return;

OnGuardianDied:
	if (charat(strnpcinfo(1),4) == "2")
		.@z = 11;
	set getd(".MyMobCount_"+charat(strnpcinfo(1),4)+strnpcinfo(2)),getd(".MyMobCount_"+charat(strnpcinfo(1),4)+strnpcinfo(2))-1;
	if (getd(".MyMobCount_"+charat(strnpcinfo(1),4)+strnpcinfo(2)) < 2) {
		set getd(".MyMobCount_"+charat(strnpcinfo(1),4)+strnpcinfo(2)),getd(".MyMobCount_"+charat(strnpcinfo(1),4)+strnpcinfo(2))+1;
		callsub OnSummon,10+.@z;
	}
	end;

OnReset:
	stopnpctimer;
	killmonster strnpcinfo(2),strnpcinfo(0)+"::OnGuardianDied";
	deletearray getd(".x_"+strnpcinfo(2)+"[0]"),22;
	deletearray getd(".y_"+strnpcinfo(2)+"[0]"),22;
	end;
}

//== Guardian Stone Summoners (2) ==========================
-	script	df#template	FAKE_NPC,{
OnEnable:
	if (compare(strnpcinfo(2),"arug")) {
		if (strnpcinfo(2) == "arug_cas01") setarray .@i[0],210,234,308,189;
		else if (strnpcinfo(2) == "arug_cas02") setarray .@i[0],33,168,245,168;
		else setarray .@i[0],65,171,212,149;	// Castles 3,4,5 are identical.
	}
	else {
		if (strnpcinfo(2) == "schg_cas02") setarray .@i[0],231,58,335,230;
		else if (strnpcinfo(2) == "schg_cas03") setarray .@i[0],242,309,376,251;
		else setarray .@i[0],27,35,207,75;	// Castles 1,4,5 are identical.
	}
	.@num = atoi(charat(strnpcinfo(1),2));
	.@j = (.@num == 1)?0:2;
	guardian strnpcinfo(2),.@i[.@j],.@i[.@j+1],((.@num == 1)?"1st":"2nd")+" Guardian Stone",1906+.@num,strnpcinfo(0)+"::OnGuardianStoneDied";
	end;

OnDisable:
	killmonster strnpcinfo(2),strnpcinfo(0)+"::OnGuardianStoneDied";
	setd "$agit_"+substr(strnpcinfo(2),0,1)+substr(strnpcinfo(2),8,9)+"["+(atoi(charat(strnpcinfo(1),2))-1)+"]",1;
	stopnpctimer;
	end;

OnGuardianStoneDied:
	.@num = atoi(charat(strnpcinfo(1),2));
	.@var$ = "$agit_"+substr(strnpcinfo(2),0,1)+substr(strnpcinfo(2),8,9);
	setd .@var$+"["+(.@num-1)+"]",1;
	if (getd(.@var$+"[0]") == 1 || getd(.@var$+"[0]") == 2) {
		++.@destroyed;
	}
	if (getd(.@var$+"[1]") == 1 || getd(.@var$+"[1]") == 2) {
		++.@destroyed;
	}
	if (.@destroyed == 2) {
		mapannounce strnpcinfo(2),"All of the Guardian Stones have been destroyed!",bc_map,"0x00ff00";
		donpcevent "RL0#"+strnpcinfo(2)+"::OnDisable";
	}
	else mapannounce strnpcinfo(2),"The "+((.@num == 1)?"1st":"2nd")+" Guardian Stone has been destroyed!",bc_map,"0x00ff00";
	donpcevent "gard"+.@num+"#"+strnpcinfo(2)+"::OnReset";
	initnpctimer;
	end;

OnTimer300000:
	.@num = atoi(charat(strnpcinfo(1),2));
	.@str$ = substr(strnpcinfo(2),0,1)+substr(strnpcinfo(2),8,9);
	donpcevent ((.@num == 1)?"1st":"2nd")+" Guardian Stone#"+.@str$+"::OnEnable";
	setd "$agit_"+.@str$+"["+(atoi(charat(strnpcinfo(1),2))-1)+"]",2;
	stopnpctimer;
	end;
}

//== Barrier Summoners (4) =================================
-	script	RL#template	FAKE_NPC,{
OnEnable:
	.@num = atoi(charat(strnpcinfo(1),2));
	if (.@num == 0) {
		if (compare(strnpcinfo(2),"arug")) {
			if (strnpcinfo(2) == "arug_cas01") {
				setarray .@wall[0],238,74,8,6,0;
				setarray .@x[0],239,241,243,245;
				setarray .@y[0], 73, 73, 73, 73;
			}
			else if (strnpcinfo(2) == "arug_cas02") {
				setarray .@wall[0],136,136,8,6,0;
				setarray .@x[0],137,139,141,143;
				setarray .@y[0],137,137,137,137;
			}
			else {	// Castles 3,4,5 are identical.
				setarray .@wall[0],138,110,8,6,0;
				setarray .@x[0],139,141,143,145;
				setarray .@y[0],111,111,111,111;
			}
		}
		else {
			if (strnpcinfo(2) == "schg_cas02") {
				setarray .@wall[0],290,98,8,0,0;
				setarray .@x[0],289,289,289,289;
				setarray .@y[0], 98,100,102,104;
			}
			else if (strnpcinfo(2) == "schg_cas03") {
				setarray .@wall[0],326,301,6,6,0;
				setarray .@x[0],326,328,330;
				setarray .@y[0],300,300,300;
			}
			else {	// Castles 1,4,5 are identical.
				setarray .@wall[0],114,48,13,6,0;
				setarray .@x[0],115,117,119,121,123,125;
				setarray .@y[0], 49, 49, 49, 49, 49, 49;
			}
		}
	}
	else if (.@num == 1) {
		if (compare(strnpcinfo(2),"arug")) {
			if (strnpcinfo(2) == "arug_cas01") {
				setarray .@wall[0],239,53,8,6,1;
				setarray .@x[0],239,241,243,240,242,244;
				setarray .@y[0], 55, 55, 55, 54, 54, 54;
			}
			else if (strnpcinfo(2) == "arug_cas02") {
				setarray .@wall[0],150,223,12,6,1;
				setarray .@x[0],151,153,155,157,159,161;
				setarray .@y[0],222,222,222,222,222,222;
			}
			else {	// Castles 3,4,5 are identical.
				setarray .@wall[0],139,158,6,6,1;
				setarray .@x[0],140,142,144,139,141,143;
				setarray .@y[0],157,157,157,156,156,156;
			}
		}
		else {
			if (strnpcinfo(2) == "schg_cas02") {
				setarray .@wall[0],279,98,8,0,1;
				setarray .@x[0],280,280,280,281,281,281;
				setarray .@y[0], 98,100,102, 99,101,103;
			}
			else if (strnpcinfo(2) == "schg_cas03") {
				setarray .@wall[0],325,277,8,6,1;
				setarray .@x[0],326,328,330,327,329,331;
				setarray .@y[0],278,278,278,279,279,279;
			}
			else {	// Castles 1,4,5 are identical.
				setarray .@wall[0],114,51,13,6,1;
				setarray .@x[0],115,117,119,121,123,125;
				setarray .@y[0], 50, 50, 50, 50, 50, 50;
			}
		}
	}
	else if (.@num == 2) {
		if (compare(strnpcinfo(2),"arug")) {
			if (strnpcinfo(2) == "arug_cas01") {
				setarray .@wall[0],107,124,6,6,1;
				setarray .@x[0],107,109,111,108,110,112;
				setarray .@y[0],122,122,122,123,123,123;
			}
			else if (strnpcinfo(2) == "arug_cas02") {
				setarray .@wall[0],125,342,8,0,1;
				setarray .@x[0],126,126,126,127,127,127;
				setarray .@y[0],343,345,347,344,346,348;
			}
			else {	// Castles 3,4,5 are identical.
				setarray .@wall[0],138,210,8,6,1;
				setarray .@x[0],140,142,144,139,141,143;
				setarray .@y[0],209,209,209,208,208,208;
			}
		}
		else {
			if (strnpcinfo(2) == "schg_cas02") {
				setarray .@wall[0],230,213,6,0,1;
				setarray .@x[0],231,231,231,232,232,232;
				setarray .@y[0],213,215,217,213,215,217;
			}
			else if (strnpcinfo(2) == "schg_cas03") {
				setarray .@wall[0],200,230,8,0,1;
				setarray .@x[0],201,201,201,202,202,202;
				setarray .@y[0],231,233,235,232,234,236;
			}
			else {	// Castles 1,4,5 are identical.
				setarray .@wall[0],114,154,13,6,1;
				setarray .@x[0],115,117,119,121,123,125;
				setarray .@y[0],153,153,153,153,153,153;
			}
		}
	}
	else {
		if (compare(strnpcinfo(2),"arug")) {
			if (strnpcinfo(2) == "arug_cas01") {
				setarray .@wall[0],84,171,8,6,1;
				setarray .@x[0], 84, 86, 88, 90;
				setarray .@y[0],170,170,170,170;
			}
			else if (strnpcinfo(2) == "arug_cas02") {
				setarray .@wall[0],38,314,12,6,1;
				setarray .@x[0], 40, 42, 44, 46;
				setarray .@y[0],315,315,315,315;
			}
			else {	// Castles 3,4,5 are identical.
				setarray .@wall[0],138,263,8,6,1;
				setarray .@x[0],139,141,143,145;
				setarray .@y[0],262,262,262,262;
			}
		}
		else {
			if (strnpcinfo(2) == "schg_cas02") {
				setarray .@wall[0],160,141,6,6,1;
				setarray .@x[0],160,162,164,166;
				setarray .@y[0],140,140,140,140;
			}
			else if (strnpcinfo(2) == "schg_cas03") {
				setarray .@wall[0],285,198,8,0,1;
				setarray .@x[0],284,284,284,284;
				setarray .@y[0],199,201,203,205;
			}
			else {	// Castles 1,4,5 are identical.
				setarray .@wall[0],116,241,11,6,1;
				setarray .@x[0],116,118,120,122;
				setarray .@y[0],240,240,240,240;
			}
		}
	}
	if (.@num == 3) set getd(".MyMobCount_"+.@num+strnpcinfo(2)),4;
	else if (.@num) set getd(".MyMobCount_"+.@num+strnpcinfo(2)),6;
	setwall strnpcinfo(2),.@wall[0],.@wall[1],.@wall[2],.@wall[3],.@wall[4],substr(strnpcinfo(2),0,1)+substr(strnpcinfo(2),8,9)+"_"+strnpcinfo(1);
	.@j = (getd(".MyMobCount_"+.@num+strnpcinfo(2)))?getd(".MyMobCount_"+.@num+strnpcinfo(2)):getarraysize(.@x);
	for (.@i = 0; .@i<.@j; ++.@i)
		guardian strnpcinfo(2),.@x[.@i],.@y[.@i]," ",1905,strnpcinfo(0)+"::OnBarrierDestroyed";
	end;

OnBarrierDestroyed:
	.@num = atoi(charat(strnpcinfo(1),2));
	if (!.@num) end;
	set getd(".MyMobCount_"+.@num+strnpcinfo(2)),getd(".MyMobCount_"+.@num+strnpcinfo(2))-1;
	if (getd(".MyMobCount_"+.@num+strnpcinfo(2)) == 0) {
		.@var$ = substr(strnpcinfo(2),0,1)+substr(strnpcinfo(2),8,9);
		setd "$agit_"+.@var$+"["+(.@num+1)+"]",1;
		setarray .@count$[0],"1st","2nd","3rd";
		mapannounce strnpcinfo(2),"The "+.@count$[.@num-1]+" Fortress Gate is destroyed.",bc_map,"0x00ff00";
		delwall .@var$+"_"+strnpcinfo(1);
	}
	end;

OnDisable:
	delwall substr(strnpcinfo(2),0,1)+substr(strnpcinfo(2),8,9)+"_"+strnpcinfo(1);
	killmonster strnpcinfo(2),strnpcinfo(0)+"::OnBarrierDestroyed";
	end;
}

//== Link Flags (function) =================================
function	script	LinkFlag	{
	if (!getcharid(2) || getcharid(2) != getcastledata(strnpcinfo(4),1)) end;
	if (getarg(0) == "Convenience Facility") {
		mes "^3355FFThis is the Stronghold";
		mes "Teleport Service. Would";
		mes "you like to teleport to the";
		mes "Convenience Facility for";
		mes "guild members?^000000";
		if(select("Go to Convenience Facility", "Cancel") == 1)
			warp strnpcinfo(4),getarg(1),getarg(2);
		close;
	}
	if (getarg(0) == "Emperium Center") {
		mes "^3355FFThis is the Stronghold";
		mes "Teleport Service. Would";
		mes "you like to teleport to";
		mes "the Emperium Center?^000000";
		if(select("Teleport", "Cancel") == 1)
			warp strnpcinfo(4),getarg(1),getarg(2);
		close;
	}
	mes "^3355FFThis is the Stronghold";
	mes "Teleport Service. Please";
	mes "choose a destination";
	mes "within the stronghold.^000000";
	for (.@i = 0; .@i<getargcount(); .@i += 3)
		.@menu$ += getarg(.@i)+":";
	.@menu$ += "Cancel";
	.@i = select(.@menu$)-1;
	if (.@i != getargcount()/3)
		warp strnpcinfo(4),getarg(.@i*3+1),getarg(.@i*3+2);
	close;
}

//== Return Flags (function) ===============================
function	script	ReturnFlag	{
	.@str$ = (compare(strnpcinfo(4),"aru"))?"Arunafeltz":"Schwaltzvalt";
	.@GID = getcastledata(getarg(0),1);
	if (!.@GID) {
		mes "[ "+.@str$+" Royal Edict ]";
		mes "The Holy Kingdom of";
		mes .@str$+" declares that";
		mes "one has yet to claim lordship";
		mes "over this stronghold. The one";
		mes "that breaks the Emperium will";
		mes "be recognized as its new owner.";
		close;
	}
	if (getcharid(2) == .@GID && getarg(1,0)) {
		mes "[ Ringing Voice ]";
		mes "Courageous one,";
		mes "do you wish to return";
		mes "to your stronghold?";
		next;
		if(select("Return to the Stronghold", "Cancel") == 1 && getcharid(2) == getcastledata(getarg(0),1)) {
			if (compare(getarg(0),"arug")) {
				if (getarg(0) == "arug_cas01") setarray .@i[0],67,193;
				else if (getarg(0) == "arug_cas02") setarray .@i[0],43,256;
				else setarray .@i[0],121,318;	// Castles 3,4,5 are identical.
			}
			else {
				if (getarg(0) == "schg_cas02") setarray .@i[0],136,188;
				else if (getarg(0) == "schg_cas03") setarray .@i[0],308,202;
				else setarray .@i[0],120,290;	// Castles 1,4,5 are identical.
			}
			warp getarg(0),.@i[0],.@i[1];
		}
		close;
	}
	mes "[ "+.@str$+" Royal Edict ]";
	mes "The Holy Kingdom of";
	mes .@str$+" decrees that";
	mes "this stronghold is owned";
	mes "by the ^FF0000"+getguildname(.@GID)+"^000000 Guild.";
	next;
	mes "[ "+.@str$+" Royal Edict ]";
	mes "^FF0000"+getguildmaster(.@GID)+"^000000 is";
	mes "Guild Master of ^FF0000"+getguildname(.@GID)+"^000000.";
	mes "Any that object must claim this";
	mes "stronghold through strength of";
	mes "steel and magic during the";
	mes "appointed Guild Siege times.";
	close;
}

//== Treasure Room Switches ================================
-	script	Switch#template	FAKE_NPC,{
	mes " ";
	mes "^3355FFWill you pull";
	mes "this small lever?^000000";
	next;
	if(select("Pull Lever", "Cancel") == 2) close;
	if (compare(strnpcinfo(4),"arug")) {
		if (strnpcinfo(4) == "arug_cas01") setarray .@i[0],121,357;
		else if (strnpcinfo(4) == "arug_cas02") setarray .@i[0],387,323;
		else setarray .@i[0],321,57;	// Castles 3,4,5 are identical.
	}
	else {
		if (strnpcinfo(4) == "schg_cas02") setarray .@i[0],339,79;
		else if (strnpcinfo(4) == "schg_cas03") setarray .@i[0],57,13;
		else setarray .@i[0],275,244;	// Castles 1,4,5 are identical.
	}
	warp strnpcinfo(4),.@i[0],.@i[1];
	close;
}

//== Guild Dungeon Warps ===================================
-	script	Sunflower#template	FAKE_NPC,{
	if (getcharid(2) == getcastledata(strnpcinfo(4),1)) {
		mes "- It's an amazingly huge sunflower; as big as a human! ... You feel something mysterious emanating from the flower. -";
		next;
		switch(select("Hold the stem.", "Do nothing.")) {
		case 1:
			if (compare(strnpcinfo(4),"arug")) {
				.@map$ = "arug_dun01";
				setarray .@mapx[0],350,350,50, 50,200;
				setarray .@mapy[0],350, 50,50,350,386;
			}
			else {
				.@map$ = "schg_dun01";
				setarray .@mapx[0],262, 94, 79,212,322;
				setarray .@mapy[0],314,284,140, 70,166;
			}
			.@i = atoi(charat(strnpcinfo(4),9))-1;
			warp .@map$,.@mapx[.@i],.@mapy[.@i];
			close;
		case 2:
			mes "It's too scary to touch unknown things.";
			close;
		}
	}
}
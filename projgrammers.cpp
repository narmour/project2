//Function "action" attempts to apply rules 24-49.
int SyntacticalAnalyzer::action() {
	int errors = 0;

	printDebug("Stepping into action with Token: " + token_names[token] + ", Lexeme: " + lex->GetLexeme());

	switch (token) {
		case IF_T:
			//24
			printDebug("Applying rule 24.");
			token = lex->GetToken();
			errors += stmt();
			errors += stmt();
			errors += else_part();
			break;
		case COND_T:
			//25
			printDebug("Applying rule 25.");
			token = lex->GetToken();
			if (token == LPAREN_T) {
				token = lex->GetToken();
				errors += stmt_pair_body();
			}
			else {
				errors++;
			}
			break;
		case LISTOP_T:
			//26
			printDebug("Applying rule 26.");
			token = lex->GetToken();
			errors += stmt();
			break;
		case CONS_T:
			//27
			printDebug("Applying rule 27.");
			token = lex->GetToken();
			errors += stmt();
			errors += stmt();
			break;
		case AND_T:
			//28
			printDebug("Applying rule 28.");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case OR_T:
			//29
			printDebug("Applying rule 29.");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case NOT_T:
			//30
			printDebug("Applying rule 30.");
			token = lex->GetToken();
			errors += stmt();
			break;
		case NUMBERP_T:
			//31
			printDebug("Applying rule 31.");
			token = lex->GetToken();
			errors += stmt();
			break;
		case LISTP_T:
			//32
			printDebug("Applying rule 32.");
			token = lex->GetToken();
			errors += stmt();
			break;
		case ZEROP_T:
			//33
			printDebug("Applying rule 33.");
			token = lex->GetToken();
			errors += stmt();
			break;
		case NULLP_T:
			//34
			printDebug("Applying rule 34.");
			token = lex->GetToken();
			errors += stmt();
			break;
		case STRINGP_T:
			//35
			printDebug("Applying rule 35.");
			token = lex->GetToken();
			errors += stmt();
			break;
		case PLUS_T:
			//36
			printDebug("Applying rule 36.");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case MINUS_T:
			//37
			printDebug("Applying rule 37.");
			token = lex->GetToken();
			errors += stmt();
			errors += stmt_list();
			break;
		case DIV_T:
			//38
			printDebug("Applying rule 38.");
			token = lex->GetToken();
			errors += stmt();
			errors += stmt_list();
			break;
		case MULT_T:
			//39
			printDebug("Applying rule 39.");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case MODULO_T:
			//40
			printDebug("Applying rule 40.");
			token = lex->GetToken();
			errors += stmt();
			errors += stmt();
			break;
		case ROUND_T:
			//41
			printDebug("Applying rule 41.");
			token = lex->GetToken();
			errors += stmt();
			break;
		case EQUALTO_T:
			//42
			printDebug("Applying rule 42.");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case GT_T:
			//43
			printDebug("Applying rule 43.");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case LT_T:
			//44
			printDebug("Applying rule 44.");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case GTE_T:
			//45
			printDebug("Applying rule 45.");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case LTE_T:
			//46
			printDebug("Applying rule 46.");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case IDENT_T:
			//47
			printDebug("Applying rule 47.");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case DISPLAY_T:
			//48
			printDebug("Applying rule 48.");
			token = lex->GetToken();
			errors += stmt();
			break;
		case NEWLINE_T:
			//49
			printDebug("Applying rule 49.");
			token = lex->GetToken();
			break;
		default:
			//Error
			reportError("Error: could not apply any rule (24-49).");
			printDebug("Error: could not apply any rule (24-49).");
			errors++;
			break;
	}

	return errors;
}

//Function "any_other_token" attempts to apply rules 50-81.
int SyntacticalAnalyzer::any_other_token() {
	int errors = 0;

	printDebug("Stepping into any_other_token with Token: " + token_names[token] + ", Lexeme: " + lex->GetLexeme());

	switch (token) {
		case LPAREN_T:
			//50
			printDebug("Applying rule 50.");
			token = lex->GetToken();
			errors += more_tokens();
			if (token == RPAREN_T) {
				token = lex->GetToken();
			}
			else {
				errors++;
			}
			break;
		case IDENT_T:
			//51
			printDebug("Applying rule 51.");
			token = lex->GetToken();
			break;
		case NUMLIT_T:
			//52
			printDebug("Applying rule 52.");
			token = lex->GetToken();
			break;
		case STRLIT_T:
			//53
			printDebug("Applying rule 53.");
			token = lex->GetToken();
			break;
		case CONS_T:
			//54
			printDebug("Applying rule 54.");
			token = lex->GetToken();
			break;
		case IF_T:
			//55
			printDebug("Applying rule 55.");
			token = lex->GetToken();
			break;
		case DISPLAY_T:
			//56
			printDebug("Applying rule 56.");
			token = lex->GetToken();
			break;
		case NEWLINE_T:
			//57
			printDebug("Applying rule 57.");
			token = lex->GetToken();
			break;
		case LISTOP_T:
			//58
			printDebug("Applying rule 58.");
			token = lex->GetToken();
			break;
		case AND_T:
			//59
			printDebug("Applying rule 59.");
			token = lex->GetToken();
			break;
		case OR_T:
			//60
			printDebug("Applying rule 60.");
			token = lex->GetToken();
			break;
		case NOT_T:
			//61
			printDebug("Applying rule 61.");
			token = lex->GetToken();
			break;
		case DEFINE_T:
			//62
			printDebug("Applying rule 62.");
			token = lex->GetToken();
			break;
		case NUMBERP_T:
			//63
			printDebug("Applying rule 63.");
			token = lex->GetToken();
			break;
		case LISTP_T:
			//64
			printDebug("Applying rule 64.");
			token = lex->GetToken();
			break;
		case ZEROP_T:
			//65
			printDebug("Applying rule 65.");
			token = lex->GetToken();
			break;
		case NULLP_T:
			//66
			printDebug("Applying rule 66.");
			token = lex->GetToken();
			break;
		case STRINGP_T:
			//67
			printDebug("Applying rule 67.");
			token = lex->GetToken();
			break;
		case PLUS_T:
			//68
			printDebug("Applying rule 68.");
			token = lex->GetToken();
			break;
		case MINUS_T:
			//69
			printDebug("Applying rule 69.");
			token = lex->GetToken();
			break;
		case DIV_T:
			//70
			printDebug("Applying rule 70.");
			token = lex->GetToken();
			break;
		case MULT_T:
			//71
			printDebug("Applying rule 71.");
			token = lex->GetToken();
			break;
		case MODULO_T:
			//72
			printDebug("Applying rule 72.");
			token = lex->GetToken();
			break;
		case ROUND_T:
			//73
			printDebug("Applying rule 73.");
			token = lex->GetToken();
			break;
		case EQUALTO_T:
			//74
			printDebug("Applying rule 74.");
			token = lex->GetToken();
			break;
		case GT_T:
			//75
			printDebug("Applying rule 75.");
			token = lex->GetToken();
			break;
		case LT_T:
			//76
			printDebug("Applying rule 76.");
			token = lex->GetToken();
			break;
		case GTE_T:
			//77
			printDebug("Applying rule 77.");
			token = lex->GetToken();
			break;
		case LTE_T:
			//78
			printDebug("Applying rule 78.");
			token = lex->GetToken();
			break;
		case SQUOTE_T:
			//79
			printDebug("Applying rule 79.");
			token = lex->GetToken();
			errors += any_other_token();
			break;
		case COND_T:
			//80
			printDebug("Applying rule 80.");
			token = lex->GetToken();
			break;
		case ELSE_T:
			//81
			printDebug("Applying rule 81.");
			token = lex->GetToken();
			break;
		default:
			//Error
			reportError("Error: could not apply any rule (50-81).");
			printDebug("Error: could not apply any rule (50-81).");
			errors++;
			break;
	}

	return errors;
}

//Function "stmt_pair" attempts to apply rules 20-21.
int SyntacticalAnalyzer::stmt_pair() {
	int errors = 0;

	printDebug("Stepping into stmt_pair with Token: " + token_names[token] + ", Lexeme: " + lex->GetLexeme());

	//If LPAREN_T, apply rule 20.
	if (token == LPAREN_T) {
		printDebug("Applying rule 20...");
		token = lex->GetToken();
		errors += stmt_pair_body();
	}
	//Else, apply rule 21 (lambda).
	else printDebug("Applying rule 21...");

	return errors;
}

//Function "param_list" attempts to apply rules 16-17.
int SyntacticalAnalyzer::param_list() {
	int errors = 0;

	printDebug("Stepping into param_list with Token: " + token_names[token] + ", Lexeme: " + lex->GetLexeme());

	//If IDENT_T, apply rule 16. 
	if (token == IDENT_T) {
		printDebug("Applying rule 16...");
		token = lex->GetToken(); 
		errors += param_list();
	}
	//Else, apply rule 17 (lambda).
	else printDebug("Applying rule 17...");

	return errors;
}
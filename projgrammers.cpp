//action
int SyntacticalAnalyzer::action() {
	int errors = 0;

	switch (token) {
		case IF_T:
			//24
			token = lex->GetToken();
			errors += stmt();
			errors += stmt();
			errors += else_part();
			break;
		case COND_T:
			//25
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
			token = lex->GetToken();
			errors += stmt();
			break;
		case CONS_T:
			//27
			token = lex->GetToken();
			errors += stmt();
			errors += stmt();
			break;
		case AND_T:
			//28
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case OR_T:
			//29
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case NOT_T:
			//30
			token = lex->GetToken();
			errors += stmt();
			break;
		case NUMBERP_T:
			//31
			token = lex->GetToken();
			errors += stmt();
			break;
		case LISTP_T:
			//32
			token = lex->GetToken();
			errors += stmt();
			break;
		case ZEROP_T:
			//33
			token = lex->GetToken();
			errors += stmt();
			break;
		case NULLP_T:
			//34
			token = lex->GetToken();
			errors += stmt();
			break;
		case STRINGP_T:
			//35
			token = lex->GetToken();
			errors += stmt();
			break;
		case PLUS_T:
			//36
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case MINUS_T:
			//37
			token = lex->GetToken();
			errors += stmt();
			errors += stmt_list();
			break;
		case DIV_T:
			//38
			token = lex->GetToken();
			errors += stmt();
			errors += stmt_list();
			break;
		case MULT_T:
			//39
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case MODULO_T:
			//40
			token = lex->GetToken();
			errors += stmt();
			errors += stmt();
			break;
		case ROUND_T:
			//41
			token = lex->GetToken();
			errors += stmt();
			break;
		case EQUALTO_T:
			//42
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case GT_T:
			//43
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case LT_T:
			//44
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case GTE_T:
			//45
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case LTE_T:
			//46
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case IDENT_T:
			//47
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case DISPLAY_T:
			//48
			token = lex->GetToken();
			errors += stmt();
			break;
		case NEWLINE_T:
			//49
			token = lex->GetToken();
			break;
		default:
			errors++;
			break;
	}

	return errors;
}

//any_other_token
int SyntacticalAnalyzer::any_other_token() {
	int errors = 0;

	switch (token) {
		case LPAREN_T:
			//50
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
			token = lex->GetToken();
			break;
		case NUMLIT_T:
			//52
			token = lex->GetToken();
			break;
		case STRLIT_T:
			//53
			token = lex->GetToken();
			break;
		case CONS_T:
			//54
			token = lex->GetToken();
			break;
		case IF_T:
			//55
			token = lex->GetToken();
			break;
		case DISPLAY_T:
			//56
			token = lex->GetToken();
			break;
		case NEWLINE_T:
			//57
			token = lex->GetToken();
			break;
		case LISTOP_T:
			//58
			token = lex->GetToken();
			break;
		case AND_T:
			//59
			token = lex->GetToken();
			break;
		case OR_T:
			//60
			token = lex->GetToken();
			break;
		case NOT_T:
			//61
			token = lex->GetToken();
			break;
		case DEFINE_T:
			//62
			token = lex->GetToken();
			break;
		case NUMBERP_T:
			//63
			token = lex->GetToken();
			break;
		case LISTP_T:
			//64
			token = lex->GetToken();
			break;
		case ZEROP_T:
			//65
			token = lex->GetToken();
			break;
		case NULLP_T:
			//66
			token = lex->GetToken();
			break;
		case STRINGP_T:
			//67
			token = lex->GetToken();
			break;
		case PLUS_T:
			//68
			token = lex->GetToken();
			break;
		case MINUS_T:
			//69
			token = lex->GetToken();
			break;
		case DIV_T:
			//70
			token = lex->GetToken();
			break;
		case MULT_T:
			//71
			token = lex->GetToken();
			break;
		case MODULO_T:
			//72
			token = lex->GetToken();
			break;
		case ROUND_T:
			//73
			token = lex->GetToken();
			break;
		case EQUALTO_T:
			//74
			token = lex->GetToken();
			break;
		case GT_T:
			//75
			token = lex->GetToken();
			break;
		case LT_T:
			//76
			token = lex->GetToken();
			break;
		case GTE_T:
			//77
			token = lex->GetToken();
			break;
		case LTE_T:
			//78
			token = lex->GetToken();
			break;
		case SQUOTE_T:
			//79
			token = lex->GetToken();
			errors += any_other_token();
			break;
		case COND_T:
			//80
			token = lex->GetToken();
			break;
		case ELSE_T:
			//81
			token = lex->GetToken();
			break;
		default:
			//Error
			errors++;
			break;
	}

	return errors;
}

//stmt_pair
int SyntacticalAnalyzer::stmt_pair() {
	int errors = 0;

	//If LPAREN_T, apply rule 20.
	if (token == LPAREN_T) {
		token = lex->GetToken();
		errors += stmt_pair_body();
	}
	//Else, apply rule 21 (lambda).

	return errors;
}

//param_list
int SyntacticalAnalyzer::param_list() {
	int errors = 0;

	//If IDENT_T, apply rule 16. 
	if (token == IDENT_T) {
		token = lex->GetToken(); 
		errors += param_list();
	}
	//Else, apply rule 17 (lambda).

	return errors;
}
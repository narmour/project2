#include <iostream>
#include <iomanip>
#include <fstream>
#include "SyntacticalAnalyzer.h"

using namespace std;

// 34 X 14
// {LPAREN_T,EOF_T,IDENT_T,RPAREN_T,DEFINE_T,NUMLIT_T,STRLIT_T,SQUOTE_T,ELSE_T,IF_T,COND_T,LISTOP_T,CONS_T,AND_T,OR_T,NOT_T,NUMBERP_T,LISTP_T,ZEROP_T,NULLP_T,STRINGP_T,PLUS_T,MINUS_T,DIV_T,MULT_T,MODULO_T,ROUND_T,EQUALTO_T,GT_T,LT_T,GTE_T,LTE_T,DISPLAY_T,NEWLINE_T},
static int syntacticalRuleNumbers [][34] = 
	{
	{1,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83}, 	// <program> 			0
	{83,82,3,83,2,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83}, 		// <more_defines>		1
	{82,83,83,83,4,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83},		// <define>				2
	{5,83,5,6,83,5,5,5,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83}, 			// <stmt_list>			3
	{9,83,8,82,83,7,7,7,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83}, 		// <stmt>				4
	{82,83,82,82,83,10,11,12,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83}, 	// <literal>			5
	{13,83,13,82,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13}, 	// <quoted_lit>			6
	{14,83,14,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14}, 	// <more_tokens>		7
	{83,83,16,17,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83}, 	// <param_list>			8
	{18,83,18,19,83,18,18,18,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83}, 	// <else_part>			9
	{20,83,83,21,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83}, 	// <stmt_pair>			10
	{22,83,22,82,83,22,22,22,23,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83}, 	// <stmt_pair_body>		11
	{83,83,47,82,83,83,83,83,83,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,48,49}, 	// <action>				12
	{50,83,51,82,62,52,53,79,81,55,80,58,54,59,60,61,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,56,57} 	//<any_other_token>		13
};

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{	
	// a token maps to a row in the syntactical
	// analyzer table. 
	// token_T -> [token_M]
	row[LPAREN_T] = LPAREN_M;
	row[EOF_T] = EOF_M;
	row[IDENT_T] = IDENT_M;
	row[RPAREN_T] = RPAREN_M;
	row[DEFINE_T] = DEFINE_M;
	row[NUMLIT_T] = NUMLIT_M;
	row[STRLIT_T] = STRLIT_M;
	row[SQUOTE_T] = SQUOTE_M;
	row[ELSE_T] = ELSE_M;
	row[IF_T] = IF_M; // 10
	row[COND_T] = COND_M;
	row[LISTOP_T] = LISTOP_M;
	row[CONS_T] = CONS_M;
	row[AND_T] = AND_M;
	row[OR_T] = OR_M;
	row[NOT_T] = NOT_M;
	row[NUMBERP_T] = NUMBERP_M;
	row[LISTP_T] = LISTP_M;
	row[ZEROP_T] = ZEROP_M;
	row[NULLP_T] = NULLP_M; // 20
	row[STRINGP_T] = STRINGP_M;
	row[PLUS_T] = PLUS_M;
	row[MINUS_T] = MINUS_M;
	row[DIV_T] = DIV_M;
	row[MULT_T] = MULT_M;
	row[MODULO_T] = MODULO_M;
	row[ROUND_T] = ROUND_M;
	row[EQUALTO_T] = EQUALTO_M;
	row[GT_T] = GT_M; 
	row[LT_T] = LT_M; // 30
	row[GTE_T] = GTE_M;
	row[LTE_T] = LTE_M;
	row[DISPLAY_T] = DISPLAY_M;
	row[NEWLINE_T] = NEWLINE_M; // 34
	

	lex = new LexicalAnalyzer (filename);

	string name = filename;
	name = name.substr(0, name.length()-3);

	string debugFileName = name + ".dbg";
    debug.open(debugFileName);

	string p2FileName = name + ".p2";
	p2file.open(p2FileName);

    token = lex->GetToken();
	int ttlErrs = program ();
	cout << "SYNTAX ERRORS: " << ttlErrs << endl;

}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
    debug.close();
	listing.close();
	p2file.close();
	delete lex;
}

void SyntacticalAnalyzer::printListingFile(const string &msg) {
	/* A listing of the original src code and syntactical analyzer */
	listing << msg << endl;
}
void SyntacticalAnalyzer::printP2File(const string &functionName, 
										const string &tokenName, 
										const string &lex) {
	/* Contains a list of rules applied and functions visited 
	 * Format:
	 * Entering Program function; current token is: LPAREN_T, lexeme: (
	 * Using Rule 1 (this is printed using printP2FileUsing(ruleNumber))
	*/
	p2file << "Entering " << functionName << " function; ";
	p2file << "current token is: " << tokenName << ", ";
	p2file << "lexeme: " << lex << endl;
}

void SyntacticalAnalyzer::printP2FileUsing(const string &ruleNumber)
{
	/* Used to print a list of terminal and non-terminal symbols 
	 * Using Rule 1
	*/
	p2file << "Using Rule " << ruleNumber << endl;
}

void SyntacticalAnalyzer::printP2Exiting(const string &funkyName, const string &tokenName)
{
	/* Exiting Program function; current token is: EOF_T */
	p2file << "Exiting " << funkyName << " function; current token is: " << tokenName << endl;
}


void SyntacticalAnalyzer::printDebug(const string &msg) {
	
	debug << msg << endl;
}


int SyntacticalAnalyzer::program(){
    int errors = 0;
	printP2File("Program", lex->GetTokenName(token), lex->GetLexeme());
	while (!isValidToken(PROGRAM_F, token))
		token = lex->GetToken();
	

    if(token==LPAREN_T)
	{
		printP2FileUsing("1");
        token = lex->GetToken();  // WE APPLIED RULE 1
	}
	else {
		errors++; 
		printListingFile("Error: expected LPAREN_T, but received: ");
	}
	if (token == DEFINE_T)
	{
		errors += define();
	}
	else
	{
		errors++;
		printListingFile("Error: expected DEFINE_T, but received: ");
	}
	if (token == LPAREN_T)
	{
		token = lex->GetToken();
	}
	else
	{
		errors++;
		printListingFile("Error: expected L_PARENT, but received: ");
	}
	// p2file << "calling more_defines.." << endl;
	errors += more_defines();
	// errors += more_defines();

	printP2Exiting("Program", token_names[token]);
    return errors;
}


int SyntacticalAnalyzer::stmt(){
	int errors = 0;
	printP2File("Stmt", token_names[token], lex->GetLexeme());
	while (!isValidToken(STMT_F, token))
	{
		cout << "token: " << lex->GetTokenName(token) << " is invalid advancing" << endl;
		token = lex->GetToken();
	}
	cout << "token: " << lex->GetTokenName(token) << " is valid" << endl;
		

	if(token==IDENT_T){
		printP2FileUsing("8");
    	token = lex->GetToken();  // consume
    }
	else if (token == LPAREN_T){
	    printP2FileUsing("9");
    	token = lex->GetToken();  // consume
		errors+= action();
		if(token == RPAREN_T){
    		token = lex->GetToken();  // consume
		}
		else{
	        printListingFile("Error: could not apply any rule9.");
			errors++;
        }
	}
	else if (token == NUMLIT_T || token ==  STRLIT_T || token ==  SQUOTE_T) {
	    printP2FileUsing("7");
        errors+=literal();
    }
	else {
		errors++;
	}

	printP2Exiting("Stmt", token_names[token]);
	return errors;

}

int SyntacticalAnalyzer::stmt_pair_body(){
	int errors = 0;
	printP2File("Stmt_Pair_Body", token_names[token], lex->GetLexeme());
	while (!isValidToken(STMT_PAIR_BODY_F, token))
		token = lex->GetToken();

	if(token == ELSE_T){
		printP2FileUsing("23");
    	token = lex->GetToken();  // consume
		errors+=stmt();
		if(token==RPAREN_T)
    		token = lex->GetToken();  // consume
		else{
	        printListingFile("Error: could not apply any rule 23.");
			errors++;
        }
	}
	else {
		printP2FileUsing("22");
		errors+=stmt();
		errors+=stmt();
		if(token==RPAREN_T)
    		token = lex->GetToken();  // consume
		else{
	        printListingFile("Error: could not apply any rule22.");
			errors++;
        }
		errors+=stmt_pair();
	}
	
	printP2Exiting("Stmt_Pair_Body", token_names[token]);
	return errors;
}



int SyntacticalAnalyzer::stmt_list()
{
	int errors = 0;
	printP2File("Stmt_List", token_names[token], lex->GetLexeme());
	while (!isValidToken(STMT_LIST_F, token))
		token = lex->GetToken();

	// [0,"LPAREN_T","EOF_T","IDENT_T","RPAREN_T","DEFINE_T","NUMLIT_T","STRLIT_T","SQUOTE_T","ELSE_T","IF_T","COND_T","LISTOP_T","CONS_T","AND_T","OR_T","NOT_T","NUMBERP_T","LISTP_T","ZEROP_T","NULLP_T","STRINGP_T","PLUS_T","MINUS_T","DIV_T","MULT_T","MODULO_T","ROUND_T","EQUALTO_T","GT_T","LT_T","GTE_T","LTE_T","DISPLAY_T","NEWLINE_T","$"],
    
	// Rule 5
    if (token == LPAREN_T || token == IDENT_T || token == NUMLIT_T || token == STRLIT_T || token == SQUOTE_T)
    {
		printP2FileUsing("5");
        errors += stmt();
        errors+= stmt_list();
    }
    // Rule 6
	// LAMBDA
    else if (token == RPAREN_T)
	    printP2FileUsing("6");
	
	printP2Exiting("Stmt_List", lex->GetTokenName(token));
    return errors;
}

int SyntacticalAnalyzer::more_defines(){
	int errors = 0;
	printP2File("More_Defines", token_names[token], lex->GetLexeme());
	while (!isValidToken(MORE_DEFINES_F, token))
		token = lex->GetToken();
    // apply rule 2
    // <more_defines> -> <define> LPARENT_T <more_defines>
    // apply rules 3
    // <more_defines> -> IDENT_T <stmt_list> RPAREN_T
    if (token == IDENT_T)
    {
		printP2FileUsing("3");
        token = lex->GetToken();
        errors += stmt_list();
        if (token == RPAREN_T)
        {
            token = lex->GetToken();
        }
        else 
        {
            errors++;
	        printListingFile("Error: could not apply any rule3.");
        }

    }
    else if (token == DEFINE_T)
	// else
    {
        printP2FileUsing("2");
        errors += define();

        if (token == LPAREN_T)
        {
            token = lex->GetToken();
        }
        else
        {
            printListingFile("Error: expected L_PAREN_T but got: ");
            errors++;
        }
		
		errors += more_defines();
		
	
    }

	printP2Exiting("More_Defines", lex->GetTokenName(token));
    return errors;

}
int SyntacticalAnalyzer::define(){
    int errors = 0;
	printP2File("Define", token_names[token], lex->GetLexeme());
	while (!isValidToken(DEFINE_F, token))
		token = lex->GetToken();

    if(token == DEFINE_T){
	    // printP2File("Applying rule 4.");
		printP2FileUsing("4");
        token = lex->GetToken();  // consume
        if(token==LPAREN_T){
            token = lex->GetToken();  // consume
            if(token==IDENT_T){
                token = lex->GetToken();  // consume
                errors += param_list();
                if(token==RPAREN_T){
                    token = lex->GetToken();  // consume
                    errors+=stmt();
                    errors+=stmt_list();
                    if(token==RPAREN_T){
                        token = lex->GetToken();  // consume
                    }
                    else{
	                    printListingFile("Error: could not apply any rule4.");
                        errors++;
                    }
                }
                else{
	                printListingFile("Error: could not apply any rule4.");
                    errors++;
                }
            }
            else{
	            printListingFile("Error: could not apply any rule4.");
                errors++;
            }
        }
        else{
	        printListingFile("Error: could not apply any rule4.");
            errors++;
        }

    }
    else{
	    printListingFile("Error: could not apply any rule4.");
        errors++;
    }

	printP2Exiting("Define", lex->GetTokenName(token));
    return errors;
}

//Function "action" attempts to apply rules 24-49.
int SyntacticalAnalyzer::action() {
	int errors = 0;
	printP2File("Action", token_names[token], lex->GetLexeme());
	while (!isValidToken(ACTION_F, token))
	{
		// cout << "token: " << lex->GetTokenName(token) << " is invalid" << endl;
		token = lex->GetToken();
	}
	// cout << "token: " << lex->GetTokenName(token) << " is VALID" << endl;

	switch (token) {
		case IF_T:
			//24
			printP2FileUsing("24");
			token = lex->GetToken();
			errors += stmt();
			errors += stmt();
			errors += else_part();
			break;
		case COND_T:
			//25
			printP2FileUsing("25");
			token = lex->GetToken();
			if (token == LPAREN_T) {
				token = lex->GetToken();
				errors += stmt_pair_body();
			}
			else {
				printListingFile("Trying to apply rule 25, expecting '(', instead saw Token: " + token_names[token] + ", Lexeme: " + lex->GetLexeme());
				errors++;
			}
			break;
		case LISTOP_T:
			//26
			printP2FileUsing("26");
			token = lex->GetToken();
			errors += stmt();
			break;
		case CONS_T:
			//27
			printP2FileUsing("27");
			token = lex->GetToken();
			errors += stmt();
			errors += stmt();
			break;
		case AND_T:
			//28
			printP2FileUsing("28");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case OR_T:
			//29
			printP2FileUsing("29");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case NOT_T:
			//30
			printP2FileUsing("30");
			token = lex->GetToken();
			errors += stmt();
			break;
		case NUMBERP_T:
			//31
			printP2FileUsing("31");
			token = lex->GetToken();
			errors += stmt();
			break;
		case LISTP_T:
			//32
			printP2FileUsing("32");
			token = lex->GetToken();
			errors += stmt();
			break;
		case ZEROP_T:
			//33
			printP2FileUsing("33");
			token = lex->GetToken();
			errors += stmt();
			break;
		case NULLP_T:
			//34
			printP2FileUsing("34");
			token = lex->GetToken();
			errors += stmt();
			break;
		case STRINGP_T:
			//35
			printP2FileUsing("35");
			token = lex->GetToken();
			errors += stmt();
			break;
		case PLUS_T:
			//36
			printP2FileUsing("36");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case MINUS_T:
			//37
			printP2FileUsing("37");
			token = lex->GetToken();
			errors += stmt();
			errors += stmt_list();
			break;
		case DIV_T:
			//38
			printP2FileUsing("38");
			token = lex->GetToken();
			errors += stmt();
			errors += stmt_list();
			break;
		case MULT_T:
			//39
			printP2FileUsing("39");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case MODULO_T:
			//40
			printP2FileUsing("40");
			token = lex->GetToken();
			errors += stmt();
			errors += stmt();
			break;
		case ROUND_T:
			//41
			printP2FileUsing("41");
			token = lex->GetToken();
			errors += stmt();
			break;
		case EQUALTO_T:
			//42
			printP2FileUsing("42");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case GT_T:
			//43
			printP2FileUsing("43");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case LT_T:
			//44
			printP2FileUsing("44");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case GTE_T:
			//45
			printP2FileUsing("45");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case LTE_T:
			//46
			printP2FileUsing("46");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case IDENT_T:
			//47
			printP2FileUsing("47");
			token = lex->GetToken();
			errors += stmt_list();
			break;
		case DISPLAY_T:
			//48
			printP2FileUsing("48");
			token = lex->GetToken();
			errors += stmt();
			break;
		case NEWLINE_T:
			//49
			printP2FileUsing("49");
			token = lex->GetToken();
			break;
		default:
			//Error
			printListingFile("Error: could not apply any rule (24-49).");
			errors++;
			// We are going to recursively call this until we
			// get a valid token.
			// token = lex->GetToken();
			// errors += action();
			break;
	}
	printP2Exiting("Action", lex->GetTokenName(token));
	return errors;
}

//Function "any_other_token" attempts to apply rules 50-81.
int SyntacticalAnalyzer::any_other_token() {
	int errors = 0;
	printP2File("Any_Other_Token", token_names[token], lex->GetLexeme());
	while (!isValidToken(ANY_OTHER_TOKEN_F, token))
		token = lex->GetToken();

	switch (token) {
		case LPAREN_T:
			//50
			printP2FileUsing("50");
			token = lex->GetToken();
			errors += more_tokens();
			if (token == RPAREN_T) {
				token = lex->GetToken();
			}
			else {
				printListingFile("Trying to apply rule 50, expecting ')', instead saw Token: " + token_names[token] + ", Lexeme: " + lex->GetLexeme());
				errors++;
			}
			break;
		case IDENT_T:
			//51
			printP2FileUsing("51");
			token = lex->GetToken();
			break;
		case NUMLIT_T:
			//52
			printP2FileUsing("52");
			token = lex->GetToken();
			break;
		case STRLIT_T:
			//53
			printP2FileUsing("53");
			token = lex->GetToken();
			break;
		case CONS_T:
			//54
			printP2FileUsing("54");
			token = lex->GetToken();
			break;
		case IF_T:
			//55
			printP2FileUsing("55");
			token = lex->GetToken();
			break;
		case DISPLAY_T:
			//56
			printP2FileUsing("56");
			token = lex->GetToken();
			break;
		case NEWLINE_T:
			//57
			printP2FileUsing("57");
			token = lex->GetToken();
			break;
		case LISTOP_T:
			//58
			printP2FileUsing("58");
			token = lex->GetToken();
			break;
		case AND_T:
			//59
			printP2FileUsing("59");
			token = lex->GetToken();
			break;
		case OR_T:
			//60
			printP2FileUsing("60");
			token = lex->GetToken();
			break;
		case NOT_T:
			//61
			printP2FileUsing("61");
			token = lex->GetToken();
			break;
		case DEFINE_T:
			//62
			printP2FileUsing("62");
			token = lex->GetToken();
			break;
		case NUMBERP_T:
			//63
			printP2FileUsing("63");
			token = lex->GetToken();
			break;
		case LISTP_T:
			//64
			printP2FileUsing("64");
			token = lex->GetToken();
			break;
		case ZEROP_T:
			//65
			printP2FileUsing("65");
			token = lex->GetToken();
			break;
		case NULLP_T:
			//66
			printP2FileUsing("66");
			token = lex->GetToken();
			break;
		case STRINGP_T:
			//67
			printP2FileUsing("67");
			token = lex->GetToken();
			break;
		case PLUS_T:
			//68
			printP2FileUsing("68");
			token = lex->GetToken();
			break;
		case MINUS_T:
			//69
			printP2FileUsing("69");
			token = lex->GetToken();
			break;
		case DIV_T:
			//70
			printP2FileUsing("70");
			token = lex->GetToken();
			break;
		case MULT_T:
			//71
			printP2FileUsing("71");
			token = lex->GetToken();
			break;
		case MODULO_T:
			//72
			printP2FileUsing("72");
			token = lex->GetToken();
			break;
		case ROUND_T:
			//73
			printP2FileUsing("73");
			token = lex->GetToken();
			break;
		case EQUALTO_T:
			//74
			printP2FileUsing("74");
			token = lex->GetToken();
			break;
		case GT_T:
			//75
			printP2FileUsing("75");
			token = lex->GetToken();
			break;
		case LT_T:
			//76
			printP2FileUsing("76");
			token = lex->GetToken();
			break;
		case GTE_T:
			//77
			printP2FileUsing("77");
			token = lex->GetToken();
			break;
		case LTE_T:
			//78
			printP2FileUsing("78");
			token = lex->GetToken();
			break;
		case SQUOTE_T:
			//79
			printP2FileUsing("79");
			token = lex->GetToken();
			errors += any_other_token();
			break;
		case COND_T:
			//80
			printP2FileUsing("80");
			token = lex->GetToken();
			break;
		case ELSE_T:
			//81
			printP2FileUsing("81");
			token = lex->GetToken();
			break;
		default:
			//Error
			printListingFile("Error: could not apply any rule (50-81).");
			errors++;
			break;
	}

	printP2Exiting("Any_Other_Token", lex->GetTokenName(token));
	return errors;
}

//Function "stmt_pair" attempts to apply rules 20-21.
int SyntacticalAnalyzer::stmt_pair() {
	int errors = 0;
	printP2File("Stmt_Pair", token_names[token], lex->GetLexeme());
	while (!isValidToken(STMT_PAIR_F, token))
		token = lex->GetToken();

	// rule 20.
	if (token == LPAREN_T) {
		printP2FileUsing("20");
		token = lex->GetToken();
		errors += stmt_pair_body();
	}
	else if (token == RPAREN_T)
		printP2FileUsing("21");
	else
	{
		errors++;
		printListingFile("Error: expected a RPAREN_T or a LPARENT_T but got: ");
	}


	printP2Exiting("Stmt_Pair", lex->GetTokenName(token));
	return errors;
}


//Function "param_list" attempts to apply rules 16-17.
int SyntacticalAnalyzer::param_list() {
	int errors = 0;
	printP2File("Param_List", token_names[token], lex->GetLexeme());
	while (!isValidToken(PARAM_LIST_F, token))
		token = lex->GetToken();

	//If IDENT_T, apply rule 16. 
	if (token == IDENT_T) {
		printP2FileUsing("16");
		token = lex->GetToken(); 
		errors += param_list();
	}

	//Else, apply rule 17 (lambda).
	else if (token == RPAREN_T)
	{
		printP2FileUsing("17");	
	}

	else 
	{
		errors++;
		printListingFile("Error: couldnt apply rule 16 or 17 in param_list");
	}
		
	printP2Exiting("Param_List", lex->GetTokenName(token));
	return errors;
}

int SyntacticalAnalyzer::else_part()
{
    // [0,"LPAREN_T","EOF_T","IDENT_T","RPAREN_T","DEFINE_T","NUMLIT_T","STRLIT_T","SQUOTE_T","ELSE_T","IF_T","COND_T","LISTOP_T","CONS_T","AND_T","OR_T","NOT_T","NUMBERP_T","LISTP_T","ZEROP_T","NULLP_T","STRINGP_T","PLUS_T","MINUS_T","DIV_T","MULT_T","MODULO_T","ROUND_T","EQUALTO_T","GT_T","LT_T","GTE_T","LTE_T","DISPLAY_T","NEWLINE_T","$"],
    int errors = 0;
	printP2File("Else_Part", token_names[token], lex->GetLexeme());
	while (!isValidToken(ELSE_PART_F, token))
		token = lex->GetToken();

    // Rule 18
    if (token == LPAREN_T || token == IDENT_T || token == NUMLIT_T || token == STRLIT_T || token == SQUOTE_T)
    {
		printP2FileUsing("18");
        // token = lex->GetToken();
        errors += stmt();
    }
    // Rule 19 (lambda)
    else if (token == RPAREN_T)
    {
		printP2FileUsing("19");
    }
	else 
	{
		printListingFile("Error: Couldnt apply rule 14 or 15...");
		errors++;
	}

	printP2Exiting("Else_Part", lex->GetTokenName(token));
    return errors;
}
int SyntacticalAnalyzer::quoted_lit()
{
    int errors = 0;
	printP2File("Quoted_Lit", token_names[token], lex->GetLexeme());
	while (!isValidToken(QUOTED_LIT_F, token))
		token = lex->GetToken();

    if (token == EOF_T || token == RPAREN_T) {
		printListingFile("Error: Couldnt apply rule 10 or 13...");
        errors++;
    }
	// applying rule 13
    else
    {
		// printP2File("Applying rule 13");
		printP2FileUsing("13");
        // token = lex->GetToken();
        errors += any_other_token();
    }

	printP2Exiting("Quoted_Lit", lex->GetTokenName(token));
    return errors;
}
int SyntacticalAnalyzer::literal()
{
    int errors = 0;
	printP2File("Literal", token_names[token], lex->GetLexeme());
	while (!isValidToken(LITERAL_F, token))
		token = lex->GetToken();

	// 10
    if (token == NUMLIT_T)
    {
		printP2FileUsing("10");
        token = lex->GetToken();
    }
	// 11
	else if (token == STRLIT_T)
	{
		printP2FileUsing("11");
		token = lex->GetToken();
	}
	// 12
	else if (token == SQUOTE_T)
	{
		printP2FileUsing("12");
		token = lex->GetToken();
		errors += quoted_lit();
	}
	else 
	{
		printListingFile("Error: Couldnt apply rule 10 or 11 or 12...");
		errors++;
	}

	printP2Exiting("Literal", lex->GetTokenName(token));
    return errors;
}


int SyntacticalAnalyzer::more_tokens()
{
    // [0,14,83,14,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,83], // <more_tokens>    
    int errors = 0;
	printP2File("More_Tokens", token_names[token], lex->GetLexeme());
	while (!isValidToken(MORE_TOKENS_F, token))
		token = lex->GetToken();

	// This is the only rule that can throw an err
    if (token == EOF_T) 
    {
		printListingFile("Error: Couldnt apply rule 14 or 15...");
        errors++;
    }

    // Rule 15 (lambda)
    else if (token == RPAREN_T)
    {
		printP2FileUsing("15");
    }

	// Rule 14
	// else if its not RPARENT_T || EOF_T
	// 5 - 34
    // token == DEFINE_T || token == NUMLIT_T || token == STRLIT_T || token == SQUOTE_T || token == ELSE_T || token == IF_T || token == COND_T || token == LISTOP_T || token == CONS_T || token == AND_T || token == OR_T || token == NOT_T || token == NUMBERP_T || token == LISTP_T || token == ZEROP_T || token == NULLP_T || STRINGP_T,PLUS_T,MINUS_T","DIV_T","MULT_T","MODULO_T || ROUND_T || EQUALTO_T || GT_T || LT_T || GTE_T || LTE_T || DISPLAY_T || NEWLINE_T
	else {
		printP2FileUsing("14");
		errors += any_other_token();
		errors += more_tokens();
	}

	printP2Exiting("More_Tokens", lex->GetTokenName(token));
    return errors;
}

bool SyntacticalAnalyzer::isValidToken(functionRuleNumberMapping fMap, token_type token_T)
{
	if (token == EOF_T)
		return true;

	tokenMapper token_M = row[token_T];
	// bool tt = false;
	// if (token_T == AND_T)
	// {	
	// 	tt = true;
	// 	cout << "value of token_M: " << token_M << endl;
	// }
	//cout << "fMap: " << fMap << endl;
	//cout << "token_M: " << token_M << endl;
	//cout << "test val: " << syntacticalRuleNumbers[0][0] << endl;
	if (syntacticalRuleNumbers[fMap][token_M] != 82 && syntacticalRuleNumbers[fMap][token_M] != 83)
	{
		return true;
	}
	//'"quotedLit1"' unexpected

	lex->ReportError(string("\'")
			+ lex->GetLexeme()
			+ string("\'")
			+ string(" unexpected"));
	return false;
}
  

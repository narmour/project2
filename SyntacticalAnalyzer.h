#ifndef SYN_H
#define SYN_H

#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"

using namespace std;

enum functionRuleNumberMapping {
      PROGRAM_F,
    MORE_DEFINES_F,
    DEFINE_F,
    STMT_LIST_F,
    STMT_F,
    LITERAL_F,
    QUOTED_LIT_F,
    MORE_TOKENS_F,
    PARAM_LIST_F,
    ELSE_PART_F,
    STMT_PAIR_F,
    STMT_PAIR_BODY_F,
    ACTION_F,
    ANY_OTHER_TOKEN_F,
};

enum tokenMapper {
    LPAREN_M, EOF_M,IDENT_M,RPAREN_M,DEFINE_M,NUMLIT_M,STRLIT_M,SQUOTE_M,ELSE_M,IF_M,COND_M,LISTOP_M,CONS_M,AND_M,OR_M,NOT_M,NUMBERP_M,LISTP_M,ZEROP_M,NULLP_M,STRINGP_M,PLUS_M,MINUS_M,DIV_M,MULT_M,MODULO_M,ROUND_M,EQUALTO_M,GT_M,LT_M,GTE_M,LTE_M,DISPLAY_M,NEWLINE_M,
};

class SyntacticalAnalyzer 
{
    public:
	SyntacticalAnalyzer (char * filename);
    int program();
    int more_defines();
    int define();
    int stmt_list();
    int stmt();
    int literal();
    int quoted_lit();
    int more_tokens();
    int param_list();
    int else_part();
    int stmt_pair();
    int stmt_pair_body();
    int action();
    int any_other_token();
	~SyntacticalAnalyzer ();

    private:
	LexicalAnalyzer * lex;
	token_type token;
    ofstream debug;
    ofstream listing;
    ofstream p2file;

    void printListingFile(const string &msg);
	void printP2File(const string &functionName, const string &tokenName, const string &lex);
    void printP2FileUsing(const string &ruleNumber);
    void printP2Exiting(const string &funkyName, const string &token);
	void printDebug(const string &msg);
    bool isValidToken(functionRuleNumberMapping fMap, token_type token);
    map <token_type, tokenMapper> row; 
};
	
#endif

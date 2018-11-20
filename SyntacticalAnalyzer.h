#ifndef SYN_H
#define SYN_H

#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"

using namespace std;

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
	void printListingFile(const string &msg);
	void printP2File(const string &functionName, const string &tokenName, const string &lex);
    void printP2FileUsing(const string &ruleNumber);
    void printP2Exiting(const string &funkyName, const string &token);

	void printDebug(const string &msg);
	~SyntacticalAnalyzer ();
    private:
	LexicalAnalyzer * lex;
	token_type token;
    ofstream debug;
    ofstream listing;
    ofstream p2file;
};
	
#endif

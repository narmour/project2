#include <iostream>
#include <iomanip>
#include <fstream>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
	lex = new LexicalAnalyzer (filename);
	token_type t;
	// program ();
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
}

int SyntacticalAnalyzer::program(){
    int errors = 0;

    if(token==LPAREN_T){
        token = lex->GetToken();  // WE APPLIED RULE 1
        errors += define();

        if(token==LPAREN_T){
            token = lex->GetToken();  // consume
            errors+=more_defines();
            if(token==EOF_T)
                token = lex->GetToken();  // consume
            else{
                //cout 
                errors+=1;
            }
        }
        else
            errors+=1;
    }
    else{
        errors +=1;
    }
    return errors;
}


int SyntacticalAnalyzer::more_defines(){
    int errors;
    return errors;
}
int SyntacticalAnalyzer::define(){
    int errors = 0;
    if(token == DEFINE_T){
        token = lex->GetToken();  // consume
        if(token==LPAREN_T){
            token = lex->GetToken();  // consume
            if(token==IDENT_T){
                token = lex->GetToken();  // consume
                param_list();
                if(token==RPAREN_T){
                    token = lex->GetToken();  // consume
                    stmt();
                    stmt_list();
                    if(token==RPAREN_T){
                        token = lex->GetToken();  // consume
                    }
                    else
                        errors++;
                }
                else
                    errors++;
            }
            else
                errors++;
        }
        else
            errors++;

    }
    else{
        errors++;
    }
    return errors;
}

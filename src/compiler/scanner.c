/** \file scanner.c
	\brief Contains all lexical analyzer operations.
  */

#include "scanner.h"

void run_scanner(file_struct *file)
{
	char c;
	char *word;
	
	FILE *i = fopen(INTERIM_FILENAME, "r");
	FILE *o = fopen("data.tmp", "w");

	/* getword() returns a string, so a NULL signifies that
     * nothing useful was retrieved from the input stream 
	 */
	while( (word = getword(i)) != NULL ){
		switch(word[0]){
		
			/* First, the possible keyword tokens */
			case 'a':
                /* auto */
				break;
			case 'b':
                /* break */
				break;
			case 'c':
				/* case */
				/* char */
				/* const */
				/* continue */
				break;
			
			case 'd':
				/* default */
				/* do */
				/* double */
				break;

			case 'e':
				/* else */
				/* enum */
				/* extern */
				break;
			case 'f':
				/* float */
				/* for */
				break;

			case 'g':
				/* goto */
				break;
	
			case 'i':
				/* int */
                /* if */
                //printf("%s\n", word);
                
                if( !strcmp(word, "int") ) {
                    sprintf(tk_buffer0, "%d", TK_KEYWORD);
                    sprintf(tk_buffer1, "%d", TK_INT);
                    
                    /* Write out lexeme to output file! */
                    put_lexeme(o, tk_buffer0, tk_buffer1);
                }
                else if ( !strcmp(word, "if") ){
                    sprintf(tk_buffer0, "%d", TK_KEYWORD);
                    sprintf(tk_buffer1, "%d", TK_IF);
                    
                    /* Write out lexeme to output file! */
                    put_lexeme(o, tk_buffer0, tk_buffer1);
                    
                }
                else {
					int m, n;
                    char *token = extract_token(word);
					char *tmp = NULL;
					size_t tk_size = strlen(token);
                    size_t word_size = strlen(word);
					size_t diff = word_size - tk_size;
					printf("Start-\n\n");
					
					while( 1 ){
						if(tmp != NULL){
							if(strlen(tmp) > 0)
								break;
							free(tmp);
						}
						tmp = (char*)xmalloc(sizeof(char)*diff);
						
						//printf("Word Size: %d\nTk Size: %d\nDiff: %d\n", word_size, tk_size, diff);
						
					
						//for(m = tk_size, n = 0; m < word_size; n++, m++){
						//	tmp[n] = word[m];
						//}
						
						/* Do things here */
						
						printf("\n\nExtracted Token: %s\n", tmp);
						
						/* Free token before reassignment */
						free(token);
						token = extract_token(tmp);
						
						tk_size = strlen(token);
						
						diff = word_size - tk_size;
						
						/* Free tmp here */
						
						
					}	
						
						
						
                    
                    
                   // printf("\n\nToken: %s\n", token);
                 
                    //sprintf(tk_buffer0, "%d", TK_KEYWORD);
                    //sprintf(tk_buffer1, "%d", TK_INT);
                    //
                    ///* Write out lexeme to output file! */
                    //put_lexeme(o, tk_buffer0, tk_buffer1);
                
                    //free(token);
                    
                }
				
				
				
				break;

			case 'l':
				/* long */
				break;
			
			case 'r':
				/* register */
				/* return */
				break;
		
			case 's':
				/* short */
				/* signed */
				/* sizeof */
				/* static */
				/* struct */
				/* switch */
				break;

			case 't':
				/* typedef */
				break;

			case 'u':
				/* union */
				/* unsigned */
				break;

			case 'v':
				/* void */
				/* volatile */
				break;

			case 'w':
				/* while */
				break;

			/* Now, we deal with other tokens (operators, constants, id's, etc) */

			case '{':
				break;

			case '}':
				break;

			case '(':
				/* ( */
				/* (casting) */
				break;

			case ')':
				break;

			case ']':
				break;

			case '[':
				break;

			case '.':
				break;

			case '!':
				break;

			case '~':
				/* ~ */
				/* ~= */
				break;
			
			case '+':
				/* + */
				/* ++ */
				/* += */
				break;

			case '-':
				/* - */
				/* -- */
				/* -= */
				break;

			case '*':
				/* * */
				/* *= */
				break;

			case '&':
				/* & */
				/* && */
				/* &= */
				break;

			case '/':
				/* / */
				/* /= */
				break;
			
			case '%':
				/* % */
				/* %= */
				break;

			case '<':
				/* < */
				/* << */
				/* <= */
				/* <<= */
				break;

			case '>':
				/* > */
				/* >> */
				/* >= */
				/* >>= */			
				break;

			case '=':
				/* = */
				/* == */
				break;

			case '|':
				/* | */
				/* || */
				/* |= */
				break;

			case '^':
				/* ^ */
				/* ^= */
				break;

			case '?':
				break;

			case ':':
				break;
            
            case ';':
                break;

			/* Constants */

			case '\'':
				break;
		
			/* String Literals */
			case '"':
				break;

			default:
			/* Try To See if it's a identifier, if not: 
			 ERROR! Given token is not part of the lang def. */

				break;
				
		}
		free(word);
	}
    
	fclose(i);
	fclose(o);
	
	
}

void put_lexeme(FILE *o, char *tk_name, char *tk_value)
{
	size_t tk_name_size = strlen(tk_name);
	size_t tk_value_size = strlen(tk_value);
	
	putc('<', o);
	fwrite(tk_name, sizeof(char), tk_name_size, o);
	putc(',', o);
	fwrite(tk_value, sizeof(char), tk_value_size, o);
	putc('>', o);
}

void put_ulexeme(FILE *o, char *tk_name)
{
	size_t tk_name_size = strlen(tk_name);
	
	putc('<', o);
	fwrite(tk_name, sizeof(char), tk_name_size, o);
	putc('>', o);
}


/* NOTE TO SELF: Still need to handle the multiple character
 * token extractions!! That is, say, '<<' as opposed to '<'
 */

char *extract_token(char *word)
{
	switch(word[0]){
		case '{':
			return copy_alloced("{");
		case '}':
			return copy_alloced("}");
		case '(':
			return copy_alloced("(");
		case ')':
			return copy_alloced(")");
		case ']':
			return copy_alloced("]");
		case '[':
			return copy_alloced("[");
		case '.':
			return copy_alloced(".");
		case '!':
			return copy_alloced("!");
		case '~':
			return copy_alloced("~");
				/* ~ */
				/* ~= */
		case '+':
			return copy_alloced("+");
			/* + */
			/* ++ */
			/* += */
		case '-':
			return copy_alloced("-");
			/* - */
			/* -- */
			/* -= */
		case '*':
			return copy_alloced("*");
			/* * */
			/* *= */
		case '&':
			return copy_alloced("&");
			/* & */
			/* && */
			/* &= */
		case '/':
			return copy_alloced("/");
			/* / */
			/* /= */	
		case '%':
			return copy_alloced("%");
			/* % */
			/* %= */
		case '<':
			return copy_alloced("<");
			/* < */
			/* << */
			/* <= */
			/* <<= */
		case '>':
			return copy_alloced(">");
			/* > */
			/* >> */
			/* >= */
			/* >>= */			
		case '=':
			return copy_alloced("=");
			/* = */
			/* == */
		case '|':
			return copy_alloced("|");
			/* | */
			/* || */
			/* |= */
		case '^':
			return copy_alloced("^");
			/* ^ */
			/* ^= */
		case '?':
			return copy_alloced("?");
		case ':':
			return copy_alloced(":");
		case ';':
			return copy_alloced(";");
		/* Constants */

		case '\'':
			return copy_alloced("'");
		/* String Literals */
		/* Questioning if this even belongs here?*/
		case '"':
			return copy_alloced("\"");
			break;
		
		default:
			return return_keyword(word);
			break;
		
		
	}
    return NULL;
}

char *return_keyword(char *word)
{
	if (word == NULL){
		return NULL;
	}
	
	size_t size = strlen(word);
	int i;
	for(i = 0; i < size; i++){
		if( !isdigit(word[i]) && !isalpha(word[i]) && word[i] != '_'){
			break;	
		}
	}
	/* 'i' is the size of the valid keyword or id */
	char *keyword = (char *)xmalloc(sizeof(char)* i  + 1);
	
	strcpy(keyword, word);
	keyword[i] = '\0';
	
	return keyword;
	
}

int is_valid_id(char *word)
{
	size_t size = strlen(word);
	
	int j;
	for(j = 0; j < size; j++){
		if( !isalpha(word[j]) && !isdigit(word[j]) && word[j] != '_' ){
			
			return 0;
		}
		
	}

	return size;
}


/* This is part of the parser! */
/*
char *get_lexeme(FILE *i)
{
	return NULL;
}

char *get_valid_id(char *lexeme)
{
	return NULL;
}

char *get_token_name(char *lexeme)
{
	return NULL;
}
*/



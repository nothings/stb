#define STB_C_LEX_C_DECIMAL_INTS    Y  
#define STB_C_LEX_C_HEX_INTS        Y
#define STB_C_LEX_C_OCTAL_INTS      Y
#define STB_C_LEX_C_DECIMAL_FLOATS  Y
#define STB_C_LEX_C99_HEX_FLOATS    Y
#define STB_C_LEX_C_IDENTIFIERS     Y
#define STB_C_LEX_C_DQ_STRINGS      Y
#define STB_C_LEX_C_SQ_STRINGS      Y
#define STB_C_LEX_C_CHARS           Y
#define STB_C_LEX_C_COMMENTS        Y
#define STB_C_LEX_CPP_COMMENTS      Y
#define STB_C_LEX_C_COMPARISONS     Y
#define STB_C_LEX_C_LOGICAL         Y
#define STB_C_LEX_C_SHIFTS          Y 
#define STB_C_LEX_C_INCREMENTS      Y
#define STB_C_LEX_C_ARROW           Y
#define STB_C_LEX_EQUAL_ARROW       Y
#define STB_C_LEX_C_BITWISEEQ       Y
#define STB_C_LEX_C_ARITHEQ         Y

#define STB_C_LEX_PARSE_SUFFIXES    Y
#define STB_C_LEX_DECIMAL_SUFFIXES  "uUlL"
#define STB_C_LEX_HEX_SUFFIXES      "lL"
#define STB_C_LEX_OCTAL_SUFFIXES    "lL"
#define STB_C_LEX_FLOAT_SUFFIXES    "uulL"

#define STB_C_LEX_0_IS_EOF             N
#define STB_C_LEX_INTEGERS_AS_DOUBLES  N
#define STB_C_LEX_MULTILINE_DSTRINGS   Y
#define STB_C_LEX_MULTILINE_SSTRINGS   Y
#define STB_C_LEX_USE_STDLIB           N
#define STB_C_LEX_DOLLAR_IDENTIFIER    Y
#define STB_C_LEX_FLOAT_NO_DECIMAL     Y  

#define STB_C_LEX_DEFINE_ALL_TOKEN_NAMES  Y  
#define STB_C_LEX_DISCARD_PREPROCESSOR    Y  
#define STB_C_LEXER_DEFINITIONS         

#define STB_C_LEXER_IMPLEMENTATION
#define STB_C_LEXER_SELF_TEST
#include "../stb_c_lexer.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
	if(size<3){
		return 0;
	}
	char *input_stream = (char *)malloc(size);
	if (input_stream == NULL){
		return 0;
	}
	memcpy(input_stream, data, size);

	stb_lexer lex;
	char *input_end = input_stream+size-1;
	char *store = (char *)malloc(0x10000);
	int len = 0x10000;
	
	stb_c_lexer_init(&lex, input_stream, input_end, store, len);
	while (stb_c_lexer_get_token(&lex)) {
		if (lex.token == CLEX_parse_error) {
			break;
		}
	}
	
	free(input_stream);
	free(store);
	return 0;
}

/* A recursive-descent parser generated by peg 0.1.2 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYRULECOUNT 13

  #include "cspec.h"

  #define YYSTYPE char *
  
  #define LPAREN '{'
  #define RPAREN '}'

  #define DUP yy = strdup(yytext)
  
  #define OUT printf("%s", yytext)
  
  #define YY_INPUT(buf, result, max_size) { \
      int yyc = getc(stdin); \
      result = (EOF == yyc) ? 0 : (*(buf) = yyc, 1); \
      yyprintf((stderr, "<%c>", yyc)); \
    }
    
  #define SUITE(S) \
    printf("Suite *suite_%d = Suite_new(%s);\n", nsuites++, S);
    
  #define SPEC(S) \
    BLOCK("Spec", S) \
    printf("Suite_push_block(suite_%d, block_%d);\n", nsuites, nblocks-1);
        
  #define BLOCK(S, D) \
    printf("Block *block_%d = Block_new(blockType%s, %s, &block_%d_callback);\n", nblocks, S, D == NULL ? "NULL" : D, nblocks); \
    nblocks++;
    
  #define CODE(S) \
    printf("void block_%d_callback() {\n %s \n}\n", nblocks-1, S);
  
  static int nsuites = 0;
  static int nblocks = 0;
    

#ifndef YY_VARIABLE
#define YY_VARIABLE(T)	static T
#endif
#ifndef YY_LOCAL
#define YY_LOCAL(T)	static T
#endif
#ifndef YY_ACTION
#define YY_ACTION(T)	static T
#endif
#ifndef YY_RULE
#define YY_RULE(T)	static T
#endif
#ifndef YY_PARSE
#define YY_PARSE(T)	T
#endif
#ifndef YYPARSE
#define YYPARSE		yyparse
#endif
#ifndef YYPARSEFROM
#define YYPARSEFROM	yyparsefrom
#endif
#ifndef YY_INPUT
#define YY_INPUT(buf, result, max_size)			\
  {							\
    int yyc= getchar();					\
    result= (EOF == yyc) ? 0 : (*(buf)= yyc, 1);	\
    yyprintf((stderr, "<%c>", yyc));			\
  }
#endif
#ifndef YY_BEGIN
#define YY_BEGIN	( yybegin= yypos, 1)
#endif
#ifndef YY_END
#define YY_END		( yyend= yypos, 1)
#endif
#ifdef YY_DEBUG
# define yyprintf(args)	fprintf args
#else
# define yyprintf(args)
#endif
#ifndef YYSTYPE
#define YYSTYPE	int
#endif

#ifndef YY_PART

typedef void (*yyaction)(char *yytext, int yyleng);
typedef struct _yythunk { int begin, end;  yyaction  action;  struct _yythunk *next; } yythunk;

YY_VARIABLE(char *   ) yybuf= 0;
YY_VARIABLE(int	     ) yybuflen= 0;
YY_VARIABLE(int	     ) yypos= 0;
YY_VARIABLE(int	     ) yylimit= 0;
YY_VARIABLE(char *   ) yytext= 0;
YY_VARIABLE(int	     ) yytextlen= 0;
YY_VARIABLE(int	     ) yybegin= 0;
YY_VARIABLE(int	     ) yyend= 0;
YY_VARIABLE(int	     ) yytextmax= 0;
YY_VARIABLE(yythunk *) yythunks= 0;
YY_VARIABLE(int	     ) yythunkslen= 0;
YY_VARIABLE(int      ) yythunkpos= 0;
YY_VARIABLE(YYSTYPE  ) yy;
YY_VARIABLE(YYSTYPE *) yyval= 0;
YY_VARIABLE(YYSTYPE *) yyvals= 0;
YY_VARIABLE(int      ) yyvalslen= 0;

YY_LOCAL(int) yyrefill(void)
{
  int yyn;
  while (yybuflen - yypos < 512)
    {
      yybuflen *= 2;
      yybuf= realloc(yybuf, yybuflen);
    }
  YY_INPUT((yybuf + yypos), yyn, (yybuflen - yypos));
  if (!yyn) return 0;
  yylimit += yyn;
  return 1;
}

YY_LOCAL(int) yymatchDot(void)
{
  if (yypos >= yylimit && !yyrefill()) return 0;
  ++yypos;
  return 1;
}

YY_LOCAL(int) yymatchChar(int c)
{
  if (yypos >= yylimit && !yyrefill()) return 0;
  if (yybuf[yypos] == c)
    {
      ++yypos;
      yyprintf((stderr, "  ok   yymatchChar(%c) @ %s\n", c, yybuf+yypos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchChar(%c) @ %s\n", c, yybuf+yypos));
  return 0;
}

YY_LOCAL(int) yymatchString(char *s)
{
  int yysav= yypos;
  while (*s)
    {
      if (yypos >= yylimit && !yyrefill()) return 0;
      if (yybuf[yypos] != *s)
        {
          yypos= yysav;
          return 0;
        }
      ++s;
      ++yypos;
    }
  return 1;
}

YY_LOCAL(int) yymatchClass(unsigned char *bits)
{
  int c;
  if (yypos >= yylimit && !yyrefill()) return 0;
  c= yybuf[yypos];
  if (bits[c >> 3] & (1 << (c & 7)))
    {
      ++yypos;
      yyprintf((stderr, "  ok   yymatchClass @ %s\n", yybuf+yypos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchClass @ %s\n", yybuf+yypos));
  return 0;
}

YY_LOCAL(void) yyDo(yyaction action, int begin, int end)
{
  while (yythunkpos >= yythunkslen)
    {
      yythunkslen *= 2;
      yythunks= realloc(yythunks, sizeof(yythunk) * yythunkslen);
    }
  yythunks[yythunkpos].begin=  begin;
  yythunks[yythunkpos].end=    end;
  yythunks[yythunkpos].action= action;
  ++yythunkpos;
}

YY_LOCAL(int) yyText(int begin, int end)
{
  int yyleng= end - begin;
  if (yyleng <= 0)
    yyleng= 0;
  else
    {
      while (yytextlen < (yyleng - 1))
	{
	  yytextlen *= 2;
	  yytext= realloc(yytext, yytextlen);
	}
      memcpy(yytext, yybuf + begin, yyleng);
    }
  yytext[yyleng]= '\0';
  return yyleng;
}

YY_LOCAL(void) yyDone(void)
{
  int pos;
  for (pos= 0;  pos < yythunkpos;  ++pos)
    {
      yythunk *thunk= &yythunks[pos];
      int yyleng= thunk->end ? yyText(thunk->begin, thunk->end) : thunk->begin;
      yyprintf((stderr, "DO [%d] %p %s\n", pos, thunk->action, yytext));
      thunk->action(yytext, yyleng);
    }
  yythunkpos= 0;
}

YY_LOCAL(void) yyCommit()
{
  if ((yylimit -= yypos))
    {
      memmove(yybuf, yybuf + yypos, yylimit);
    }
  yybegin -= yypos;
  yyend -= yypos;
  yypos= yythunkpos= 0;
}

YY_LOCAL(int) yyAccept(int tp0)
{
  if (tp0)
    {
      fprintf(stderr, "accept denied at %d\n", tp0);
      return 0;
    }
  else
    {
      yyDone();
      yyCommit();
    }
  return 1;
}

YY_LOCAL(void) yyPush(char *text, int count)	{ yyval += count; }
YY_LOCAL(void) yyPop(char *text, int count)	{ yyval -= count; }
YY_LOCAL(void) yySet(char *text, int count)	{ yyval[count]= yy; }

#endif /* YY_PART */

#define	YYACCEPT	yyAccept(yythunkpos0)

YY_RULE(int) yy__(); /* 13 */
YY_RULE(int) yy_EOF(); /* 12 */
YY_RULE(int) yy_EOL(); /* 11 */
YY_RULE(int) yy_nl(); /* 10 */
YY_RULE(int) yy_source(); /* 9 */
YY_RULE(int) yy_ws(); /* 8 */
YY_RULE(int) yy_string(); /* 7 */
YY_RULE(int) yy_s(); /* 6 */
YY_RULE(int) yy_end(); /* 5 */
YY_RULE(int) yy_block(); /* 4 */
YY_RULE(int) yy_spec(); /* 3 */
YY_RULE(int) yy_suite(); /* 2 */
YY_RULE(int) yy_main(); /* 1 */

YY_ACTION(void) yy_2_string(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_string\n"));
   DUP ;
}
YY_ACTION(void) yy_1_string(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_string\n"));
   DUP ;
}
YY_ACTION(void) yy_1_source(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_source\n"));
   DUP ;
}
YY_ACTION(void) yy_5_block(char *yytext, int yyleng)
{
#define a yyval[-1]
  yyprintf((stderr, "do yy_5_block\n"));
   CODE(a) ;
#undef a
}
YY_ACTION(void) yy_4_block(char *yytext, int yyleng)
{
#define a yyval[-1]
  yyprintf((stderr, "do yy_4_block\n"));
   BLOCK("After", NULL) ;
#undef a
}
YY_ACTION(void) yy_3_block(char *yytext, int yyleng)
{
#define a yyval[-1]
  yyprintf((stderr, "do yy_3_block\n"));
   BLOCK("AfterEach", NULL) ;
#undef a
}
YY_ACTION(void) yy_2_block(char *yytext, int yyleng)
{
#define a yyval[-1]
  yyprintf((stderr, "do yy_2_block\n"));
   BLOCK("Before", NULL) ;
#undef a
}
YY_ACTION(void) yy_1_block(char *yytext, int yyleng)
{
#define a yyval[-1]
  yyprintf((stderr, "do yy_1_block\n"));
   BLOCK("BeforeEach", NULL) ;
#undef a
}
YY_ACTION(void) yy_1_spec(char *yytext, int yyleng)
{
#define a yyval[-1]
  yyprintf((stderr, "do yy_1_spec\n"));
   SPEC(a) ;
#undef a
}
YY_ACTION(void) yy_1_suite(char *yytext, int yyleng)
{
#define a yyval[-1]
  yyprintf((stderr, "do yy_1_suite\n"));
   SUITE(a) ;
#undef a
}
YY_ACTION(void) yy_3_main(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_3_main\n"));
   printf("%s", yytext) ;
}
YY_ACTION(void) yy_2_main(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_main\n"));
   printf("\n%c\n", RPAREN) ;
}
YY_ACTION(void) yy_1_main(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_main\n"));
   OUT ;
}

YY_RULE(int) yy__()
{
  yyprintf((stderr, "%s\n", "_"));
  l2:;	
  {  int yypos3= yypos, yythunkpos3= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\002\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l3;  goto l2;
  l3:;	  yypos= yypos3; yythunkpos= yythunkpos3;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "_", yybuf+yypos));
  return 1;
}
YY_RULE(int) yy_EOF()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "EOF"));
  {  int yypos5= yypos, yythunkpos5= yythunkpos;  if (!yymatchDot()) goto l5;  goto l4;
  l5:;	  yypos= yypos5; yythunkpos= yythunkpos5;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "EOF", yybuf+yypos));
  return 1;
  l4:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "EOF", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_EOL()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "EOL"));
  {  int yypos7= yypos, yythunkpos7= yythunkpos;  if (!yy_nl()) goto l8;  goto l7;
  l8:;	  yypos= yypos7; yythunkpos= yythunkpos7;  if (!yy_EOF()) goto l6;
  }
  l7:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "EOL", yybuf+yypos));
  return 1;
  l6:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "EOL", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_nl()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "nl"));
  {  int yypos10= yypos, yythunkpos10= yythunkpos;  if (!yymatchChar('\n')) goto l11;  goto l10;
  l11:;	  yypos= yypos10; yythunkpos= yythunkpos10;  if (!yymatchString("\r\n")) goto l12;  goto l10;
  l12:;	  yypos= yypos10; yythunkpos= yythunkpos10;  if (!yymatchChar('\r')) goto l9;
  }
  l10:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "nl", yybuf+yypos));
  return 1;
  l9:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "nl", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_source()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "source"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l13;
  {  int yypos16= yypos, yythunkpos16= yythunkpos;  if (!yy_end()) goto l16;  goto l13;
  l16:;	  yypos= yypos16; yythunkpos= yythunkpos16;
  }  if (!yymatchDot()) goto l13;
  l14:;	
  {  int yypos15= yypos, yythunkpos15= yythunkpos;
  {  int yypos17= yypos, yythunkpos17= yythunkpos;  if (!yy_end()) goto l17;  goto l15;
  l17:;	  yypos= yypos17; yythunkpos= yythunkpos17;
  }  if (!yymatchDot()) goto l15;  goto l14;
  l15:;	  yypos= yypos15; yythunkpos= yythunkpos15;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l13;  yyDo(yy_1_source, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "source", yybuf+yypos));
  return 1;
  l13:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "source", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_ws()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "ws"));
  {  int yypos19= yypos, yythunkpos19= yythunkpos;  if (!yymatchChar(' ')) goto l20;  goto l19;
  l20:;	  yypos= yypos19; yythunkpos= yythunkpos19;  if (!yymatchChar('\t')) goto l21;  goto l19;
  l21:;	  yypos= yypos19; yythunkpos= yythunkpos19;  if (!yy_nl()) goto l18;
  }
  l19:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "ws", yybuf+yypos));
  return 1;
  l18:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "ws", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_string()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "string"));
  {  int yypos23= yypos, yythunkpos23= yythunkpos;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l24;  if (!yymatchChar('\'')) goto l24;
  l25:;	
  {  int yypos26= yypos, yythunkpos26= yythunkpos;
  {  int yypos27= yypos, yythunkpos27= yythunkpos;  if (!yymatchChar('\'')) goto l27;  goto l26;
  l27:;	  yypos= yypos27; yythunkpos= yythunkpos27;
  }  if (!yymatchDot()) goto l26;  goto l25;
  l26:;	  yypos= yypos26; yythunkpos= yythunkpos26;
  }  if (!yymatchChar('\'')) goto l24;  yyText(yybegin, yyend);  if (!(YY_END)) goto l24;  yyDo(yy_1_string, yybegin, yyend);  goto l23;
  l24:;	  yypos= yypos23; yythunkpos= yythunkpos23;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l22;  if (!yymatchChar('"')) goto l22;
  l28:;	
  {  int yypos29= yypos, yythunkpos29= yythunkpos;
  {  int yypos30= yypos, yythunkpos30= yythunkpos;  if (!yymatchChar('"')) goto l30;  goto l29;
  l30:;	  yypos= yypos30; yythunkpos= yythunkpos30;
  }  if (!yymatchDot()) goto l29;  goto l28;
  l29:;	  yypos= yypos29; yythunkpos= yythunkpos29;
  }  if (!yymatchChar('"')) goto l22;  yyText(yybegin, yyend);  if (!(YY_END)) goto l22;  yyDo(yy_2_string, yybegin, yyend);
  }
  l23:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "string", yybuf+yypos));
  return 1;
  l22:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "string", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_s()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "s"));  if (!yymatchClass((unsigned char *)"\000\002\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l31;
  l32:;	
  {  int yypos33= yypos, yythunkpos33= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\002\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l33;  goto l32;
  l33:;	  yypos= yypos33; yythunkpos= yythunkpos33;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "s", yybuf+yypos));
  return 1;
  l31:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "s", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_end()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "end"));  if (!yy_ws()) goto l34;  if (!yymatchString("end")) goto l34;  if (!yy_ws()) goto l34;
  yyprintf((stderr, "  ok   %s @ %s\n", "end", yybuf+yypos));
  return 1;
  l34:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "end", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_block()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "block"));
  {  int yypos36= yypos, yythunkpos36= yythunkpos;  if (!yy_ws()) goto l37;  if (!yymatchString("before each")) goto l37;  if (!yy_ws()) goto l37;  yyDo(yy_1_block, yybegin, yyend);  goto l36;
  l37:;	  yypos= yypos36; yythunkpos= yythunkpos36;  if (!yy_ws()) goto l38;  if (!yymatchString("before")) goto l38;  if (!yy_ws()) goto l38;  yyDo(yy_2_block, yybegin, yyend);  goto l36;
  l38:;	  yypos= yypos36; yythunkpos= yythunkpos36;  if (!yy_ws()) goto l39;  if (!yymatchString("after each")) goto l39;  if (!yy_ws()) goto l39;  yyDo(yy_3_block, yybegin, yyend);  goto l36;
  l39:;	  yypos= yypos36; yythunkpos= yythunkpos36;  if (!yy_ws()) goto l35;  if (!yymatchString("after")) goto l35;  if (!yy_ws()) goto l35;  yyDo(yy_4_block, yybegin, yyend);
  }
  l36:;	  if (!yy_source()) goto l35;  yyDo(yySet, -1, 0);  yyDo(yy_5_block, yybegin, yyend);  if (!yy_end()) goto l35;
  yyprintf((stderr, "  ok   %s @ %s\n", "block", yybuf+yypos));  yyDo(yyPop, 1, 0);
  return 1;
  l35:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "block", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_spec()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "spec"));  if (!yymatchString("it")) goto l40;  if (!yy_s()) goto l40;  if (!yy_string()) goto l40;  yyDo(yySet, -1, 0);  yyDo(yy_1_spec, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "spec", yybuf+yypos));  yyDo(yyPop, 1, 0);
  return 1;
  l40:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "spec", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_suite()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "suite"));  if (!yymatchString("describe")) goto l41;  if (!yy_s()) goto l41;  if (!yy_string()) goto l41;  yyDo(yySet, -1, 0);  yyDo(yy_1_suite, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "suite", yybuf+yypos));  yyDo(yyPop, 1, 0);
  return 1;
  l41:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "suite", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_main()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "main"));
  {  int yypos43= yypos, yythunkpos43= yythunkpos;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l44;
  {  int yypos47= yypos, yythunkpos47= yythunkpos;  if (!yymatchString("describe")) goto l47;  goto l44;
  l47:;	  yypos= yypos47; yythunkpos= yythunkpos47;
  }  if (!yymatchDot()) goto l44;
  l45:;	
  {  int yypos46= yypos, yythunkpos46= yythunkpos;
  {  int yypos48= yypos, yythunkpos48= yythunkpos;  if (!yymatchString("describe")) goto l48;  goto l46;
  l48:;	  yypos= yypos48; yythunkpos= yythunkpos48;
  }  if (!yymatchDot()) goto l46;  goto l45;
  l46:;	  yypos= yypos46; yythunkpos= yythunkpos46;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l44;  yyDo(yy_1_main, yybegin, yyend);  goto l43;
  l44:;	  yypos= yypos43; yythunkpos= yythunkpos43;  if (!yy_suite()) goto l49;  goto l43;
  l49:;	  yypos= yypos43; yythunkpos= yythunkpos43;  if (!yy_spec()) goto l50;  goto l43;
  l50:;	  yypos= yypos43; yythunkpos= yythunkpos43;  if (!yy_block()) goto l51;  goto l43;
  l51:;	  yypos= yypos43; yythunkpos= yythunkpos43;  if (!yy_end()) goto l52;  yyDo(yy_2_main, yybegin, yyend);  goto l43;
  l52:;	  yypos= yypos43; yythunkpos= yythunkpos43;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l42;  if (!yymatchDot()) goto l42;  yyText(yybegin, yyend);  if (!(YY_END)) goto l42;  yyDo(yy_3_main, yybegin, yyend);
  }
  l43:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "main", yybuf+yypos));
  return 1;
  l42:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "main", yybuf+yypos));
  return 0;
}

#ifndef YY_PART

typedef int (*yyrule)();

YY_PARSE(int) YYPARSEFROM(yyrule yystart)
{
  int yyok;
  if (!yybuflen)
    {
      yybuflen= 1024;
      yybuf= malloc(yybuflen);
      yytextlen= 1024;
      yytext= malloc(yytextlen);
      yythunkslen= 32;
      yythunks= malloc(sizeof(yythunk) * yythunkslen);
      yyvalslen= 32;
      yyvals= malloc(sizeof(YYSTYPE) * yyvalslen);
      yybegin= yyend= yypos= yylimit= yythunkpos= 0;
    }
  yybegin= yyend= yypos;
  yythunkpos= 0;
  yyval= yyvals;
  yyok= yystart();
  if (yyok) yyDone();
  yyCommit();
  return yyok;
  (void)yyrefill;
  (void)yymatchDot;
  (void)yymatchChar;
  (void)yymatchString;
  (void)yymatchClass;
  (void)yyDo;
  (void)yyText;
  (void)yyDone;
  (void)yyCommit;
  (void)yyAccept;
  (void)yyPush;
  (void)yyPop;
  (void)yySet;
  (void)yytextmax;
}

YY_PARSE(int) YYPARSE(void)
{
  return YYPARSEFROM(yy_main);
}

#endif


int main() {
  printf("void test() {\n");
  while (YYPARSE()) ;
  printf("\n}\n");
  return 0;
}

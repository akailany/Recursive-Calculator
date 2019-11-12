
#include <math.h>
#include "input_token.h"
#include "error.h"

int eval_expon_1(int opn1);  
int eval_expon();

int eval_expr_MulDiv_3(int opn1,int opr1,int opn2);
int eval_expr_MulDiv_2(int opn1,int opr1);  

int eval_expr_PlusMinus_3(int opn1,int opr1,int opn2);
int eval_expr_PlusMinus_2(int opn1,int opr1);  

int eval_expr_paren();

int eval_expr_1(int opn1);  
int eval_expr();

int evaluate_expression() {  
   int w, val;
   val =  eval_expr();
   if (get_token(&w)!=EOF) error(1);
   return val;
}

int eval_expr()
/* have seen

        nothing

   read until EOF or CloseBracket.
   return the integer value computed.
   also un-get the last token (EOF of CloseBracket) read.
*/
{int w;
    switch (get_token(&w))
    { case OpenBracket:
           return(eval_expr_1(eval_expr_paren()));
      case CloseBracket:
           error(2);
      case Plus:
           error(3);
      case Minus:
           error(4);
      case Mult:
           error(5);
      case Divide:
           error(6);
      case Expon:
           error(7);
      case Operand:
           return(eval_expr_1(w));
      case EOF:
           error(8);
    }
}

int eval_expr_paren() 
/* have seen

        (

   read until we find a matching parenthesis.
   the expression enclosed is evaluated.
   return the integer value computed.
*/
{int w, val;
   val = eval_expr(); 
   if (get_token(&w)!=CloseBracket) error(9);
   return val; 
}

int eval_expr_1(int opn1)
/* have seen

        opn1

   where opn1 is an operand

   read until EOF or CloseBracket.
   return the integer value computed.
   also un-get the last token (EOF of CloseBracket) read.
*/
{int w;
    switch (get_token(&w))
    { case OpenBracket:
           error(10);
      case CloseBracket:
           unget_token(CloseBracket);
           return(opn1);
      case Plus:
           return(eval_expr_PlusMinus_2(opn1,Plus));
      case Minus:
           return(eval_expr_PlusMinus_2(opn1,Minus));
      case Mult:
           return(eval_expr_1(eval_expr_MulDiv_2(opn1,Mult)));
      case Divide:
           return(eval_expr_1(eval_expr_MulDiv_2(opn1,Divide)));
      case Expon:
	   return(eval_expr_1(pow(opn1,eval_expon())));
      case Operand:
           error(11);
      case EOF:
           unget_token(EOF);
           return(opn1);
    }
}

int eval_expr_PlusMinus_2(int opn1,int opr1)
/* have seen

        opn1 opr1

   where opn1 is an operand
     and opr1 is Plus or Minus

   read until EOF or CloseBracket.
   return the integer value computed.
   also un-get the last token (EOF of CloseBracket) read.
*/
{int w;
    switch (get_token(&w))
    { case OpenBracket:
           return(eval_expr_PlusMinus_3(opn1,opr1,eval_expr_paren()));
      case CloseBracket:
           error(12);
      case Plus:
           error(13);
      case Minus:
           error(14);
      case Mult:
           error(15);
      case Divide:
           error(16);
      case Expon:
           error(17);
      case Operand:
           return(eval_expr_PlusMinus_3(opn1,opr1,w));
      case EOF:
           error(18);
    }
}

int eval_expr_PlusMinus_3(int opn1,int opr1, int opn2)
/* have seen

        opn1 opr1 opn2

   where opn1 and opn2 are operands, 
         opr1 is Plus or Minus

   read until EOF or CloseBracket.
   return the integer value computed.
   also un-get the last token (EOF of CloseBracket) read.
*/
{int w;
    switch (get_token(&w))
    { case OpenBracket:
           error(19);
      case CloseBracket:
           unget_token(CloseBracket);
           switch (opr1) 
           { case Plus:   return(opn1+opn2);
             case Minus:  return(opn1-opn2);
           }
      case Plus:
           switch (opr1) 
           { case Plus:   return(eval_expr_PlusMinus_2(opn1+opn2,Plus));
             case Minus:  return(eval_expr_PlusMinus_2(opn1-opn2,Plus));
           }
      case Minus:
           switch (opr1) 
           { case Plus:   return(eval_expr_PlusMinus_2(opn1+opn2,Minus));
             case Minus:  return(eval_expr_PlusMinus_2(opn1-opn2,Minus));
           }
      case Mult:
           return(eval_expr_PlusMinus_3(opn1,opr1,eval_expr_MulDiv_2(opn2,Mult)));  
      case Divide:
           return(eval_expr_PlusMinus_3(opn1,opr1,eval_expr_MulDiv_2(opn2,Divide)));  
      case Expon:
	   return(eval_expr_PlusMinus_3(opn1,opr1,pow(opn2,eval_expon()))); 
      case Operand:
           error(20);
      case EOF:
           unget_token(EOF);
           switch (opr1) 
           { case Plus:   return(opn1+opn2);
             case Minus:  return(opn1-opn2);
           }
    }
}

int eval_expr_MulDiv_2(int opn1,int opr1)
/* have seen

        opn1 opr1

   where opn1 is an operand
     and opr1 is Mult or Divide

   read until EOF, CloseBracket, Plus, or Minus is encountered.
   return the integer value computed.
   also un-get the last token (EOF of CloseBracket) read.
*/
{int w;
    switch (get_token(&w))
    { case OpenBracket:
           return(eval_expr_MulDiv_3(opn1,opr1,eval_expr_paren()));
      case CloseBracket:
           error(21);
      case Plus:
           error(22);
      case Minus:
           error(23);
      case Mult:
           error(24);
      case Divide:
           error(25);
      case Expon:
           error(26);
      case Operand:
           return(eval_expr_MulDiv_3(opn1,opr1,w));
      case EOF:
           error(27);
    }
}

int eval_expr_MulDiv_3(int opn1,int opr1, int opn2)
/* have seen

        opn1 opr1 opn2

   where opn1 and opn2 are operands, 
         opr1 is Mult or Divide

   read until EOF, CloseBracket, Plus, or Minus is encountered.
   return the integer value computed.
   also un-get the last token (EOF of CloseBracket) read.
*/
{int w;
    switch (get_token(&w))
    { case OpenBracket:
           error(28);
      case CloseBracket:
           unget_token(CloseBracket);
           switch (opr1) 
           { case Mult:    return(opn1*opn2);
             case Divide:  return(opn1/opn2);
           }
      case Plus:
           unget_token(Plus);
           switch (opr1) 
           { case Mult:    return(opn1*opn2);
             case Divide:  return(opn1/opn2);
           }
      case Minus:
           unget_token(Minus);
           switch (opr1) 
           { case Mult:    return(opn1*opn2);
             case Divide:  return(opn1/opn2);
           }
      case Mult:
           switch (opr1)
           { case Mult:    return(eval_expr_MulDiv_2(opn1*opn2,Mult));  
             case Divide:  return(eval_expr_MulDiv_2(opn1/opn2,Mult));
           }
      case Divide:
           switch (opr1)
           { case Mult:    return(eval_expr_MulDiv_2(opn1*opn2,Divide));  
             case Divide:  return(eval_expr_MulDiv_2(opn1/opn2,Divide));
           }
      case Expon:
	   return(eval_expr_MulDiv_3(opn1,opr1,pow(opn2,eval_expon()))); 
      case Operand:
           error(29);
      case EOF:
           unget_token(EOF);
           switch (opr1) 
           { case Mult:    return(opn1*opn2);
             case Divide:  return(opn1/opn2);
           }
    }
}


int eval_expon() 
/*
   have just seen an exponentiation operator ^

   read until an operator of lower priority 
   or a closing parenthesis or EOF is encountered.

   observe the right associate law of exponentiation.

   return the exponent value.
*/
{int w;
    switch (get_token(&w))
    { case OpenBracket:
           return(eval_expon_1(eval_expr_paren()));
      case CloseBracket:
           error(30);
      case Plus:
           error(31);
      case Minus:
           error(32);
      case Mult:
           error(33);
      case Divide:
           error(34);
      case Expon:
           error(35);
      case Operand:
           return(eval_expon_1(w));
      case EOF:
           error(36);
    }
}

int eval_expon_1(int opn1) 
/*
   same context as for eval_expon()

   just seen an operand, and before that an exponentiation ^ operator

*/
{int w;
    switch (get_token(&w))
    { case OpenBracket:
           error(37);
      case CloseBracket:
           unget_token(CloseBracket);
           return(opn1);
      case Plus:
           unget_token(Plus);
           return(opn1);
      case Minus:
           unget_token(Minus);
           return(opn1);
      case Mult:
           unget_token(Mult);
           return(opn1);
      case Divide:
           unget_token(Divide);
           return(opn1);
      case Expon:
           return(pow(opn1,eval_expon()));
      case Operand:
           error(38);
      case EOF:
           unget_token(EOF);
           return(opn1);
    }
}

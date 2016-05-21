%{
#include "whitespace.tab.h"
%}

%option noyywrap

%%

[ ] {
    return SPACE;
}

\t {
    return TAB;
}

\n {
    return LF;
}

. ;

%%

%{
#include "whitespace.tab.h"
%}

%option noyywrap

%%

\n\n\n {
    return PROGRAM_END;
}

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


:- use_module(library(pfl)).

:- set_clpbn_flag(solver,ve).
%:- set_clpbn_flag(solver,fove).


t(ann).
t(dave).

% p(ann,t).

bayes p(X)::[t,f] ; [0.1, 0.3] ; [t(X)].

% use standard Prolog queries: provide evidence first.

?- p(ann,t), p(ann,X).

% ?- p(ann,X).


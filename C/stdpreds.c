
/*************************************************************************
*									 *
*	 YAP Prolog 							 *
*									 *
*	Yap Prolog was developed at NCCUP - Universidade do Porto	 *
*									 *
* Copyright L.Damas, V. Santos Costa and Universidade do Porto 1985--	 *
*									 *
**************************************************************************
*									 *
* File:		stdpreds.c						 *
* comments:	General-purpose C implemented system predicates		 *
*									 *
* Last rev:     $Date: 2008-07-24 16:02:00 $,$Author: vsc $
**
* $Log: not supported by cvs2svn $
* Revision 1.131  2008/06/12 10:55:52  vsc
* fix syntax error messages
*
* Revision 1.130  2008/04/06 11:53:02  vsc
*  fix some restore bugs
*
* Revision 1.129  2008/03/15 12:19:33  vsc
* fix flags
*
* Revision 1.128  2008/02/15 12:41:33  vsc
* more fixes to modules
*
* Revision 1.127  2008/02/13 10:15:35  vsc
* fix some bugs from yesterday plus improve support for modules in
* operators.
*
* Revision 1.126  2008/02/07 23:09:13  vsc
* don't break ISO standard in current_predicate/1.
* Include Nicos flag.
*
* Revision 1.125  2008/01/23 17:57:53  vsc
* valgrind it!
* enable atom garbage collection.
*
* Revision 1.124  2007/11/26 23:43:08  vsc
* fixes to support threads and assert correctly, even if inefficiently.
*
* Revision 1.123  2007/11/06 17:02:12  vsc
* compile ground terms away.
*
* Revision 1.122  2007/10/18 08:24:16  vsc
* fix global variables
*
* Revision 1.121  2007/10/10 09:44:24  vsc
* some more fixes to make YAP swi compatible
* fix absolute_file_name (again)
* fix setarg
*
* Revision 1.120  2007/10/08 23:02:15  vsc
* minor fixes
*
* Revision 1.119  2007/04/18 23:01:16  vsc
* fix deadlock when trying to create a module with the same name as a
* predicate (for now, just don't lock modules). obs Paulo Moura.
*
* Revision 1.118  2007/02/26 10:41:40  vsc
* fix prolog_flags for chr.
*
* Revision 1.117  2007/01/28 14:26:37  vsc
* WIN32 support
*
* Revision 1.116  2006/12/13 16:10:23  vsc
* several debugger and CLP(BN) improvements.
*
* Revision 1.115  2006/11/28 13:46:41  vsc
* fix wide_char support for name/2.
*
* Revision 1.114  2006/11/27 17:42:03  vsc
* support for UNICODE, and other bug fixes.
*
* Revision 1.113  2006/11/16 14:26:00  vsc
* fix handling of infinity in name/2 and friends.
*
* Revision 1.112  2006/11/08 01:56:47  vsc
* fix argument order in db statistics.
*
* Revision 1.111  2006/11/06 18:35:04  vsc
* 1estranha
*
* Revision 1.110  2006/10/10 14:08:17  vsc
* small fixes on threaded implementation.
*
* Revision 1.109  2006/09/15 19:32:47  vsc
* ichanges for QSAR
*
* Revision 1.108  2006/09/01 20:14:42  vsc
* more fixes for global data-structures.
* statistics on atom space.
*
* Revision 1.107  2006/08/22 16:12:46  vsc
* global variables
*
* Revision 1.106  2006/08/07 18:51:44  vsc
* fix garbage collector not to try to garbage collect when we ask for large
* chunks of stack in a single go.
*
* Revision 1.105  2006/06/05 19:36:00  vsc
* hacks
*
* Revision 1.104  2006/05/19 14:31:32  vsc
* get rid of IntArrays and FloatArray code.
* include holes when calculating memory usage.
*
* Revision 1.103  2006/05/18 16:33:05  vsc
* fix info reported by memory manager under DL_MALLOC and SYSTEM_MALLOC
*
* Revision 1.102  2006/04/28 17:53:44  vsc
* fix the expand_consult patch
*
* Revision 1.101  2006/04/28 13:23:23  vsc
* fix number of overflow bugs affecting threaded version
* make current_op faster.
*
* Revision 1.100  2006/02/05 02:26:35  tiagosoares
* MYDDAS: Top Level Functionality
*
* Revision 1.99  2006/02/05 02:17:54  tiagosoares
* MYDDAS: Top Level Functionality
*
* Revision 1.98  2005/12/17 03:25:39  vsc
* major changes to support online event-based profiling
* improve error discovery and restart on scanner.
*
* Revision 1.97  2005/11/22 11:25:59  tiagosoares
* support for the MyDDAS interface library
*
* Revision 1.96  2005/10/28 17:38:49  vsc
* sveral updates
*
* Revision 1.95  2005/10/21 16:09:02  vsc
* SWI compatible module only operators
*
* Revision 1.94  2005/09/08 22:06:45  rslopes
* BEAM for YAP update...
*
* Revision 1.93  2005/08/04 15:45:53  ricroc
* TABLING NEW: support to limit the table space size
*
* Revision 1.92  2005/07/20 13:54:27  rslopes
* solved warning: cast from pointer to integer of different size
*
* Revision 1.91  2005/07/06 19:33:54  ricroc
* TABLING: answers for completed calls can now be obtained by loading (new
*option) or executing (default) them from the trie data structure.
*
* Revision 1.90  2005/07/06 15:10:14  vsc
* improvements to compiler: merged instructions and fixes for ->
*
* Revision 1.89  2005/05/26 18:01:11  rslopes
* *** empty log message ***
*
* Revision 1.88  2005/04/27 20:09:25  vsc
* indexing code could get confused with suspension points
* some further improvements on oveflow handling
* fix paths in Java makefile
* changs to support gibbs sampling in CLP(BN)
*
* Revision 1.87  2005/04/07 17:48:55  ricroc
* Adding tabling support for mixed strategy evaluation (batched and local
*scheduling)
*   UPDATE: compilation flags -DTABLING_BATCHED_SCHEDULING and
*-DTABLING_LOCAL_SCHEDULING removed. To support tabling use -DTABLING in the
*Makefile or --enable-tabling in configure.
*   NEW: yap_flag(tabling_mode,MODE) changes the tabling execution mode of all
*tabled predicates to MODE (batched, local or default).
*   NEW: tabling_mode(PRED,MODE) changes the default tabling execution mode of
*predicate PRED to MODE (batched or local).
*
* Revision 1.86  2005/03/13 06:26:11  vsc
* fix excessive pruning in meta-calls
* fix Term->int breakage in compiler
* improve JPL (at least it does something now for amd64).
*
* Revision 1.85  2005/03/02 19:48:02  vsc
* Fix some possible errors in name/2 and friends, and cleanup code a bit
* YAP_Error changed.
*
* Revision 1.84  2005/03/02 18:35:46  vsc
* try to make initialization process more robust
* try to make name more robust (in case Lookup new atom fails)
*
* Revision 1.83  2005/03/01 22:25:09  vsc
* fix pruning bug
* make DL_MALLOC less enthusiastic about walking through buckets.
*
* Revision 1.82  2005/02/21 16:50:04  vsc
* amd64 fixes
* library fixes
*
* Revision 1.81  2005/02/08 04:05:35  vsc
* fix mess with add clause
* improves on sigsegv handling
*
* Revision 1.80  2005/01/05 05:32:37  vsc
* Ricardo's latest version of profiler.
*
* Revision 1.79  2004/12/28 22:20:36  vsc
* some extra bug fixes for trail overflows: some cannot be recovered that
*easily,
* some can.
*
* Revision 1.78  2004/12/08 04:45:03  vsc
* polish changes to undefp
* get rid of a few warnings
*
* Revision 1.77  2004/12/05 05:07:26  vsc
* name/2 should accept [] as a valid list (string)
*
* Revision 1.76  2004/12/05 05:01:25  vsc
* try to reduce overheads when running with goal expansion enabled.
* CLPBN fixes
* Handle overflows when allocating big clauses properly.
*
* Revision 1.75  2004/12/02 06:06:46  vsc
* fix threads so that they at least start
* allow error handling to work with threads
* replace heap_base by Yap_heap_base, according to Yap's convention for globals.
*
* Revision 1.74  2004/11/19 22:08:43  vsc
* replace SYSTEM_ERROR_INTERNAL by out OUT_OF_WHATEVER_ERROR whenever
*appropriate.
*
* Revision 1.73  2004/11/19 17:14:14  vsc
* a few fixes for 64 bit compiling.
*
* Revision 1.72  2004/11/18 22:32:37  vsc
* fix situation where we might assume nonextsing double initialization of C
*predicates (use
* Hidden Pred Flag).
* $host_type was double initialized.
*
* Revision 1.71  2004/07/23 21:08:44  vsc
* windows fixes
*
* Revision 1.70  2004/06/29 19:04:42  vsc
* fix multithreaded version
* include new version of Ricardo's profiler
* new predicat atomic_concat
* allow multithreaded-debugging
* small fixes
*
* Revision 1.69  2004/06/16 14:12:53  vsc
* miscellaneous fixes
*
* Revision 1.68  2004/05/14 17:11:30  vsc
* support BigNums in interface
*
* Revision 1.67  2004/05/14 16:33:45  vsc
* add Yap_ReadBuffer
*
* Revision 1.66  2004/05/13 20:54:58  vsc
* debugger fixes
* make sure we always go back to current module, even during initizlization.
*
* Revision 1.65  2004/04/27 15:14:36  vsc
* fix halt/0 and halt/1
*									 *
*									 *
*************************************************************************/
#ifdef SCCS
static char SccsId[] = "%W% %G%";
#endif

#define HAS_CACHE_REGS 1
/*
* This file includes the definition of a miscellania of standard predicates
* for yap refering to: Consulting, Executing a C predicate from call,
* Comparisons (both general and numeric), Structure manipulation, Direct
* access to atoms and predicates, Basic support for the debugger
*
* It also includes a table where all C-predicates are initializated
*
*/

#include "Yap.h"
#if YAP_JIT
#include "amijit.h"
#endif
#include "Yatom.h"
#include "YapHeap.h"
#include "eval.h"
#include "yapio.h"
#include "Foreign.h"
#ifdef TABLING
#include "tab.macros.h"
#endif /* TABLING */
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <stdio.h>
#if HAVE_STRING_H
#include <string.h>
#endif
#if HAVE_MALLOC_H
#include <malloc.h>
#endif
#if YAP_JIT
#include <JIT_Compiler.hpp>
#endif
#include <wchar.h>
#include <fcntl.h>

static Int p_setval(USES_REGS1);
static Int p_value(USES_REGS1);
static Int p_values(USES_REGS1);
#ifdef undefined
static CODEADDR *FindAtom(CODEADDR, int *);
#endif /* undefined */
static Int p_opdec(USES_REGS1);
static Int p_univ(USES_REGS1);
static Int p_abort(USES_REGS1);
#ifdef BEAM
Int p_halt(USES_REGS1);
#else
static Int p_halt(USES_REGS1);
#endif
static Int current_predicate(USES_REGS1);
static Int cont_current_predicate(USES_REGS1);
static OpEntry *NextOp(OpEntry *CACHE_TYPE);
static Int init_current_op(USES_REGS1);
static Int cont_current_op(USES_REGS1);
static Int init_current_atom_op(USES_REGS1);
static Int cont_current_atom_op(USES_REGS1);
static Int TrailMax(void);
static Int GlobalMax(void);
static Int LocalMax(void);
static Int p_statistics_heap_max(USES_REGS1);
static Int p_statistics_global_max(USES_REGS1);
static Int p_statistics_local_max(USES_REGS1);
static Int p_statistics_heap_info(USES_REGS1);
static Int p_statistics_stacks_info(USES_REGS1);
static Int p_statistics_trail_info(USES_REGS1);
static Int p_cputime(USES_REGS1);
static Int p_systime(USES_REGS1);
static Int p_runtime(USES_REGS1);
static Int p_walltime(USES_REGS1);
static Int p_break(USES_REGS1);

#if YAP_JIT
void *(*Yap_JitCall)(JIT_Compiler *jc, yamop *p);
void (*Yap_llvmShutdown)(void);
Int (*Yap_traced_absmi)(void);

static Int p_jit(USES_REGS1) { /* '$set_value'(+Atom,+Atomic) */
  void *jit_handle;

  if ((jit_handle = Yap_LoadForeignFile(YAP_YAPJITLIB, 0))) {
    if (!Yap_CallForeignFile(jit_handle, "init_jit"))
      fprintf(stderr, "Could not load JIT\n");
    return FALSE;
  }
  return TRUE;
}

#endif /* YAP_JIT */

#ifdef BEAM
Int use_eam(USES_REGS1);
Int eager_split(USES_REGS1);
Int force_wait(USES_REGS1);
Int commit(USES_REGS1);
Int skip_while_var(USES_REGS1);
Int wait_while_var(USES_REGS1);
Int show_time(USES_REGS1);
Int start_eam(USES_REGS1);
Int cont_eam(USES_REGS1);

extern int EAM;
extern int eam_am(PredEntry *);
extern int showTime(void);

Int start_eam(USES_REGS1) {
  if (eam_am((PredEntry *)0x1))
    return (TRUE);
  else {
    cut_fail();
    return (FALSE);
  }
}

Int cont_eam(USES_REGS1) {
  if (eam_am((PredEntry *)0x2))
    return (TRUE);
  else {
    cut_fail();
    return (FALSE);
  }
}

Int use_eam(USES_REGS1) {
  if (EAM)
    EAM = 0;
  else {
    Yap_PutValue(AtomCArith, 0);
    EAM = 1;
  }
  return (TRUE);
}

Int commit(USES_REGS1) {
  if (EAM) {
    printf("Nao deveria ter sido chamado commit do stdpreds\n");
    exit(1);
  }
  return (TRUE);
}

Int skip_while_var(USES_REGS1) {
  if (EAM) {
    printf("Nao deveria ter sido chamado skip_while_var do stdpreds\n");
    exit(1);
  }
  return (TRUE);
}

Int wait_while_var(USES_REGS1) {
  if (EAM) {
    printf("Nao deveria ter sido chamado wait_while_var do stdpreds\n");
    exit(1);
  }
  return (TRUE);
}

Int force_wait(USES_REGS1) {
  if (EAM) {
    printf("Nao deveria ter sido chamado force_wait do stdpreds\n");
    exit(1);
  }
  return (TRUE);
}

Int eager_split(USES_REGS1) {
  if (EAM) {
    printf("Nao deveria ter sido chamado eager_split do stdpreds\n");
    exit(1);
  }
  return (TRUE);
}

Int show_time(USES_REGS1) /* MORE PRECISION */
{
  return (showTime());
}

#endif /* BEAM */
       // @{

/**
   @defgroup YAPSetVal
   @ingroup Internal_Database

   Maintain a light-weight map where the key is an atom, and the value can be
   any constant.
*/

/** @pred  set_value(+ _A_,+ _C_)


    Associate atom  _A_ with constant  _C_.

    The `set_value` and `get_value` built-ins give a fast alternative to
    the internal data-base. This is a simple form of implementing a global
    counter.

    ~~~~~
    read_and_increment_counter(Value) :-
    get_value(counter, Value),
    Value1 is Value+1,
    set_value(counter, Value1).
    ~~~~~
    This predicate is YAP specific.
*/
static Int p_setval(USES_REGS1) { /* '$set_value'(+Atom,+Atomic) */
  Term t1 = Deref(ARG1), t2 = Deref(ARG2);
  if (!IsVarTerm(t1) && IsAtomTerm(t1) &&
      (!IsVarTerm(t2) && (IsAtomTerm(t2) || IsNumTerm(t2)))) {
    Yap_PutValue(AtomOfTerm(t1), t2);
    return (TRUE);
  }
  return (FALSE);
}

/** @pred  get_value(+ _A_,- _V_)
    In YAP, atoms can be associated with constants. If one such
    association exists for atom  _A_, unify the second argument with the
    constant. Otherwise, unify  _V_ with `[]`.

    This predicate is YAP specific.
*/
static Int p_value(USES_REGS1) { /* '$get_value'(+Atom,?Val) */
  Term t1 = Deref(ARG1);
  if (IsVarTerm(t1)) {
    Yap_Error(INSTANTIATION_ERROR, t1, "get_value/2");
    return (FALSE);
  }
  if (!IsAtomTerm(t1)) {
    Yap_Error(TYPE_ERROR_ATOM, t1, "get_value/2");
    return (FALSE);
  }
  return (Yap_unify_constant(ARG2, Yap_GetValue(AtomOfTerm(t1))));
}

static Int p_values(USES_REGS1) { /* '$values'(Atom,Old,New) */
  Term t1 = Deref(ARG1), t3 = Deref(ARG3);

  if (IsVarTerm(t1)) {
    Yap_Error(INSTANTIATION_ERROR, t1, "set_value/2");
    return (FALSE);
  }
  if (!IsAtomTerm(t1)) {
    Yap_Error(TYPE_ERROR_ATOM, t1, "set_value/2");
    return (FALSE);
  }
  if (!Yap_unify_constant(ARG2, Yap_GetValue(AtomOfTerm(t1)))) {
    return (FALSE);
  }
  if (!IsVarTerm(t3)) {
    if (IsAtomTerm(t3) || IsNumTerm(t3)) {
      Yap_PutValue(AtomOfTerm(t1), t3);
    } else
      return (FALSE);
  }
  return (TRUE);
}

//@}

static Int p_opdec(USES_REGS1) { /* '$opdec'(p,type,atom)		 */
  /* we know the arguments are integer, atom, atom */
  Term p = Deref(ARG1), t = Deref(ARG2), at = Deref(ARG3);
  Term tmod = Deref(ARG4);
  if (tmod == TermProlog) {
    tmod = PROLOG_MODULE;
  }
  return Yap_OpDec((int)IntOfTerm(p), (char *)RepAtom(AtomOfTerm(t))->StrOfAE,
                   AtomOfTerm(at), tmod);
}

#ifdef NO_STRTOD

#if HAVE_CTYPE_H
#include <ctype.h>
#endif

double strtod(s, pe) char *s, **pe;
{
  double r = atof(s);
  *pe = s;
  while (*s == ' ') {
    ++s;
  }
  if (*s == '+' || *s == '-') {
    ++s;
  }
  if (!isdigit(*s)) {
    return (r);
  }
  while (isdigit(*s)) {
    ++s;
  }
  if (*s == '.') {
    ++s;
  }
  while (isdigit(*s)) {
    ++s;
  }
  if (*s == 'e' || *s == 'E') {
    ++s;
  }
  if (*s == '+' || *s == '-') {
    ++s;
  }
  while (isdigit(*s)) {
    ++s;
  }
  *pe = s;
  return (r);
}

#else

#include <stdlib.h>

#endif

#ifndef INFINITY
#define INFINITY (1.0 / 0.0)
#endif

static UInt runtime(USES_REGS1) {
  return (Yap_cputime() - Yap_total_gc_time() - Yap_total_stack_shift_time());
}

/* $runtime(-SinceInterval,-SinceStart)	 */
static Int p_runtime(USES_REGS1) {
  Int now, interval, gc_time, ss_time;
  Term tnow, tinterval;

  Yap_cputime_interval(&now, &interval);
  gc_time = Yap_total_gc_time();
  now -= gc_time;
  ss_time = Yap_total_stack_shift_time();
  now -= ss_time;
  interval -= (gc_time - LOCAL_LastGcTime) + (ss_time - LOCAL_LastSSTime);
  LOCAL_LastGcTime = gc_time;
  LOCAL_LastSSTime = ss_time;
  tnow = MkIntegerTerm(now);
  tinterval = MkIntegerTerm(interval);
  return (Yap_unify_constant(ARG1, tnow) &&
          Yap_unify_constant(ARG2, tinterval));
}

/* $cputime(-SinceInterval,-SinceStart)	 */
static Int p_cputime(USES_REGS1) {
  Int now, interval;
  Yap_cputime_interval(&now, &interval);
  return (Yap_unify_constant(ARG1, MkIntegerTerm(now)) &&
          Yap_unify_constant(ARG2, MkIntegerTerm(interval)));
}

static Int p_systime(USES_REGS1) {
  Int now, interval;
  Yap_systime_interval(&now, &interval);
  return (Yap_unify_constant(ARG1, MkIntegerTerm(now)) &&
          Yap_unify_constant(ARG2, MkIntegerTerm(interval)));
}

static Int p_walltime(USES_REGS1) {
  Int now, interval;
  Yap_walltime_interval(&now, &interval);
  return (Yap_unify_constant(ARG1, MkIntegerTerm(now)) &&
          Yap_unify_constant(ARG2, MkIntegerTerm(interval)));
}

static Int p_univ(USES_REGS1) { /* A =.. L			 */
  unsigned int arity;
  register Term tin;
  Term twork, t2;
  Atom at;

  tin = Deref(ARG1);
  t2 = Deref(ARG2);
  if (IsVarTerm(tin)) {
    /* we need to have a list */
    Term *Ar;
    if (IsVarTerm(t2)) {
      Yap_Error(INSTANTIATION_ERROR, t2, "(=..)/2");
      return (FALSE);
    }
    if (!IsPairTerm(t2)) {
      if (t2 == TermNil)
        Yap_Error(DOMAIN_ERROR_NON_EMPTY_LIST, t2, "(=..)/2");
      else
        Yap_Error(TYPE_ERROR_LIST, ARG2, "(=..)/2");
      return (FALSE);
    }
    twork = HeadOfTerm(t2);
    if (IsVarTerm(twork)) {
      Yap_Error(INSTANTIATION_ERROR, twork, "(=..)/2");
      return (FALSE);
    }
    if (IsNumTerm(twork)) {
      Term tt = TailOfTerm(t2);
      if (IsVarTerm(tt)) {
        Yap_Error(INSTANTIATION_ERROR, tt, "(=..)/2");
        return (FALSE);
      }
      if (tt != MkAtomTerm(AtomNil)) {
        Yap_Error(TYPE_ERROR_ATOMIC, twork, "(=..)/2");
        return (FALSE);
      }
      return (Yap_unify_constant(ARG1, twork));
    }
    if (!IsAtomTerm(twork)) {
      Term tt = TailOfTerm(t2);
      if (IsVarTerm(tt)) {
        Yap_Error(INSTANTIATION_ERROR, twork, "(=..)/2");
        return (FALSE);
      } else if (tt == MkAtomTerm(AtomNil)) {
        Yap_Error(TYPE_ERROR_ATOMIC, twork, "(=..)/2");
        return (FALSE);
      } else {
        Yap_Error(TYPE_ERROR_ATOM, twork, "(=..)/2");
        return (FALSE);
      }
    }
    at = AtomOfTerm(twork);
    twork = TailOfTerm(t2);
    if (IsVarTerm(twork)) {
      Yap_Error(INSTANTIATION_ERROR, twork, "(=..)/2");
      return (FALSE);
    } else if (!IsPairTerm(twork)) {
      if (twork != TermNil) {
        Yap_Error(TYPE_ERROR_LIST, ARG2, "(=..)/2");
        return (FALSE);
      }
      return (Yap_unify_constant(ARG1, MkAtomTerm(at)));
    }
  build_compound:
    /* build the term directly on the heap */
    Ar = HR;
    HR++;

    while (!IsVarTerm(twork) && IsPairTerm(twork)) {
      *HR++ = HeadOfTerm(twork);
      if (HR > ASP - 1024) {
        /* restore space */
        HR = Ar;
        if (!Yap_gcl((ASP - HR) * sizeof(CELL), 2, ENV, gc_P(P, CP))) {
          Yap_Error(RESOURCE_ERROR_STACK, TermNil, LOCAL_ErrorMessage);
          return FALSE;
        }
        twork = TailOfTerm(Deref(ARG2));
        goto build_compound;
      }
      twork = TailOfTerm(twork);
    }
    if (IsVarTerm(twork)) {
      Yap_Error(INSTANTIATION_ERROR, twork, "(=..)/2");
      return (FALSE);
    }
    if (twork != TermNil) {
      Yap_Error(TYPE_ERROR_LIST, ARG2, "(=..)/2");
      return (FALSE);
    }
#ifdef SFUNC
    DOES_NOT_WORK();
    {
      SFEntry *pe = (SFEntry *)Yap_GetAProp(at, SFProperty);
      if (pe)
        twork = MkSFTerm(Yap_MkFunctor(at, SFArity), arity, CellPtr(TR),
                         pe->NilValue);
      else
        twork = Yap_MkApplTerm(Yap_MkFunctor(at, arity), arity, CellPtr(TR));
    }
#else
    arity = HR - Ar - 1;
    if (at == AtomDot && arity == 2) {
      Ar[0] = Ar[1];
      Ar[1] = Ar[2];
      HR--;
      twork = AbsPair(Ar);
    } else {
      *Ar = (CELL)(Yap_MkFunctor(at, arity));
      twork = AbsAppl(Ar);
    }
#endif
    return (Yap_unify(ARG1, twork));
  }
  if (IsAtomicTerm(tin)) {
    twork = MkPairTerm(tin, MkAtomTerm(AtomNil));
    return (Yap_unify(twork, ARG2));
  }
  if (IsRefTerm(tin))
    return (FALSE);
  if (IsApplTerm(tin)) {
    Functor fun = FunctorOfTerm(tin);
    if (IsExtensionFunctor(fun)) {
      twork = MkPairTerm(tin, MkAtomTerm(AtomNil));
      return (Yap_unify(twork, ARG2));
    }
    arity = ArityOfFunctor(fun);
    at = NameOfFunctor(fun);
#ifdef SFUNC
    if (arity == SFArity) {
      CELL *p = CellPtr(TR);
      CELL *q = ArgsOfSFTerm(tin);
      int argno = 1;
      while (*q) {
        while (*q > argno++)
          *p++ = MkVarTerm();
        ++q;
        *p++ = Deref(*q++);
      }
      twork = Yap_ArrayToList(CellPtr(TR), argno - 1);
      while (IsIntTerm(twork)) {
        if (!Yap_gc(2, ENV, gc_P(P, CP))) {
          Yap_Error(RESOURCE_ERROR_STACK, TermNil, LOCAL_ErrorMessage);
          return (FALSE);
        }
        twork = Yap_ArrayToList(CellPtr(TR), argno - 1);
      }
    } else
#endif
    {
      while (HR + arity * 2 > ASP - 1024) {
        if (!Yap_gcl((arity * 2) * sizeof(CELL), 2, ENV, gc_P(P, CP))) {
          Yap_Error(RESOURCE_ERROR_STACK, TermNil, LOCAL_ErrorMessage);
          return (FALSE);
        }
        tin = Deref(ARG1);
      }
      twork = Yap_ArrayToList(RepAppl(tin) + 1, arity);
    }
  } else {
    /* We found a list */
    at = AtomDot;
    twork = Yap_ArrayToList(RepPair(tin), 2);
  }
  twork = MkPairTerm(MkAtomTerm(at), twork);
  return (Yap_unify(ARG2, twork));
}

static Int p_abort(USES_REGS1) { /* abort			 */
  /* make sure we won't go creeping around */
  Yap_Error(ABORT_EVENT, TermNil, "");
  return (FALSE);
}

#ifdef BEAM
extern void exit_eam(char *s);

Int
#else
static Int
#endif
    p_halt(USES_REGS1) { /* halt				 */
  Term t = Deref(ARG1);
  Int out;

#ifdef BEAM
  if (EAM)
    exit_eam("\n\n[ Prolog execution halted ]\n");
#endif

  if (IsVarTerm(t)) {
    Yap_Error(INSTANTIATION_ERROR, t, "halt/1");
    return (FALSE);
  }
  if (!IsIntegerTerm(t)) {
    Yap_Error(TYPE_ERROR_INTEGER, t, "halt/1");
    return (FALSE);
  }
  out = IntegerOfTerm(t);
#if YAP_JIT
  if (ExpEnv.analysis_struc.stats_enabled ||
      ExpEnv.analysis_struc.time_pass_enabled) {
    if (strcmp(((char *)ExpEnv.analysis_struc.outfile), "STDERR")) {
      int stderrcopy = dup(2);
      if (strcmp(((char *)ExpEnv.analysis_struc.outfile), "STDOUT") == 0) {
        dup2(1, 2);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
        shutdown_llvm();
#pragma GCC diagnostic pop
        dup2(stderrcopy, 2);
      } else {
        int Outputfile = open(((char *)ExpEnv.analysis_struc.outfile),
                              O_CREAT | O_APPEND | O_WRONLY, 0777);
        if (Outputfile < 0) {
          fprintf(stderr,
                  "Error:: I can not write analysis passes's output on %s...\n",
                  ((char *)ExpEnv.analysis_struc.outfile));
          fprintf(stderr, "        %s...\n", strerror(errno));
          errno = 0;
          exit(1);
        }
        dup2(Outputfile, 2);
        shutdown_llvm();
        close(Outputfile);
        dup2(stderrcopy, 2);
      }
      close(stderrcopy);
    } else
      shutdown_llvm();
  }
#endif

  Yap_exit(out);
  return TRUE;
}

static bool valid_prop(Prop p, Term task) {
  if (RepPredProp(p)->OpcodeOfPred == UNDEF_OPCODE)
    return false;
  if ((RepPredProp(p)->PredFlags & (HiddenPredFlag | StandardPredFlag))) {
    return (task == SYSTEM_MODULE || task == TermTrue || IsVarTerm(task));
  } else {
    return (task == USER_MODULE || task == TermTrue || IsVarTerm(task));
  }
}

static PropEntry *followLinkedListOfProps(PropEntry *p, Term task) {
  while (p) {
    if (p->KindOfPE == PEProp && valid_prop(p, task)) {
      // found our baby..
      return p;
    }
    p = p->NextOfPE;
  }
  return NIL;
}

static PropEntry *getPredProp(PropEntry *p, Term task) {
  PredEntry *pe;
  if (p == NIL)
    return NIL;
  pe = RepPredProp(p);
  while (p != NIL) {
    if (p->KindOfPE == PEProp && valid_prop(p, task)) {
      return p;
    } else if (p->KindOfPE == FunctorProperty) {
      // first search remainder of functor list
      Prop pf;
      if ((pf = followLinkedListOfProps(RepFunctorProp(p)->PropsOfFE, task))) {
        return pf;
      }
    }
    p = p->NextOfPE;
  }
  return NIL;
}

static PropEntry *nextPredForAtom(PropEntry *p, Term task) {
  PredEntry *pe;
  if (p == NIL)
    return NIL;
  pe = RepPredProp(p);
  if (pe->ArityOfPE == 0 ||
      (pe->PredFlags & (NumberDBPredFlag |AtomDBPredFlag) ) ) {
     // if atom prop, search atom list
    return followLinkedListOfProps(p->NextOfPE, task);
  } else {
    FunctorEntry *f = pe->FunctorOfPred;
    // first search remainder of functor list
    PropEntry *pf;
    if ((pf = followLinkedListOfProps(p->NextOfPE, task))) {
      return pf;
    }

    // if that fails, follow the functor
    return getPredProp(f->NextOfPE, task);
  }
}

static Prop initFunctorSearch(Term t3, Term t2, Term task) {
  if (IsAtomTerm(t3)) {
    Atom at = AtomOfTerm(t3);
    // access the entry at key address.
    return followLinkedListOfProps(RepAtom(at)->PropsOfAE, task);
  } else if (IsIntTerm(t3)) {
    if (IsNonVarTerm(t2) && t2 != IDB_MODULE) {
      Yap_Error(TYPE_ERROR_CALLABLE, t3, "current_predicate/2");
      return NULL;
    } else {
      Prop p;
      // access the entry at key address.
      // a single property (this will be deterministic
      p = AbsPredProp(Yap_FindLUIntKey(IntOfTerm(t3)));
      if (valid_prop(p, task))
        return p;
    }
    Yap_Error(TYPE_ERROR_CALLABLE, t3, "current_predicate/2");
    return NULL;
  } else {
    Functor f;
    if (IsPairTerm(t3)) {
      f = FunctorDot;
    } else {
      f = FunctorOfTerm(t3);
      if (IsExtensionFunctor(f)) {
        Yap_Error(TYPE_ERROR_CALLABLE, t3, "current_predicate/2");
        return NULL;
      }
    }
    return followLinkedListOfProps(f->PropsOfFE, task);
  }
}

static PredEntry *firstModulePred(PredEntry *npp, Term task) {
  if (!npp)
    return NULL;
  do {
    npp = npp->NextPredOfModule;
  } while (npp && !valid_prop(AbsPredProp(npp), task));
  return npp;
}

static PredEntry *firstModulesPred(PredEntry *npp, ModEntry *m, Term task) {
  do {
    while (npp && !valid_prop(AbsPredProp(npp), task))
      npp = npp->NextPredOfModule;
    if (npp)
      return npp;
    m = m->NextME;
    if (m) {
      npp = m->PredForME;
    } else
      return NULL;
  } while (npp || m);
  return npp;
}

static Int cont_current_predicate(USES_REGS1) {
  UInt Arity;
  Term name, task;
  Term t1 = ARG1, t2 = ARG2, t3 = ARG3;
  bool rc, will_cut = false;
  Functor f;
  PredEntry *pp;
  t1 = Yap_YapStripModule(t1, &t2);
  t3 = Yap_YapStripModule(t3, &t2);
  task = Deref(ARG4);

  pp = AddressOfTerm(EXTRA_CBACK_ARG(4, 1));
  if (IsNonVarTerm(t3)) {
    PropEntry *np, *p;

    if (IsNonVarTerm(t2)) {
      // module and functor known, should be easy
      if (IsAtomTerm(t2)) {
        if ((p = Yap_GetPredPropByAtom(AtomOfTerm(t3), t2)) &&
            valid_prop(p, task)) {
          cut_succeed();
        } else {
          cut_fail();
        }
      } else {
        if ((p = Yap_GetPredPropByFunc(FunctorOfTerm(t3), t2)) &&
            valid_prop(p, task)) {
          cut_succeed();
        } else {
          cut_fail();
        }
      }
    }

    // t3 is a functor, or compound term,
    // just follow the functor chain
    p = AbsPredProp(pp);
    if (!p) {
      // initial search, tracks down what is the first call with
      // that name, functor..
      p = initFunctorSearch(t3, t2, task);
      // now, we can do lookahead.
      if (p == NIL)
        cut_fail();
      pp = RepPredProp(p);
    }
    np = followLinkedListOfProps(p->NextOfPE, task);
    Term mod = pp->ModuleOfPred;
    if (mod == PROLOG_MODULE)
      mod = TermProlog;
    bool b = Yap_unify(t2, mod);
    if (!np) {
      if (b)
        cut_succeed();
      else
        cut_fail();
    } else {
      EXTRA_CBACK_ARG(4, 1) = MkAddressTerm(RepPredProp(np));
      B->cp_h = HR;
      return b;
    }
  } else if (IsNonVarTerm(t1)) {
    PropEntry *np, *p;
    // run over the same atom any predicate defined for that atom
    // may be fair bait, depends on whether we know the module.
    p = AbsPredProp(pp);
    if (!p) {
      // initialization time
      if (IsIntTerm(t1)) {
        // or this or nothing....
        p = AbsPredProp(Yap_FindLUIntKey(IntOfTerm(t3)));
      } else if (IsAtomTerm(t1)) {
        // should be the usual situation.
        Atom at = AtomOfTerm(t1);
        p = getPredProp(RepAtom(at)->PropsOfAE, task);
      } else {
        Yap_Error(TYPE_ERROR_CALLABLE, t1, "current_predicate/2");
        return false;
      }
      if (!p)
        cut_fail();
      pp = RepPredProp(p);
    }
    // now, we can do lookahead.
    np = nextPredForAtom(p, task);
    if (!np)
      will_cut = true;
    else {
      EXTRA_CBACK_ARG(4, 1) = MkAddressTerm(RepPredProp(np));
      B->cp_h = HR;
    }
  } else if (IsNonVarTerm(t2)) {
    // operating within the same module.
    PredEntry *npp;

    if (!pp) {
      if (!IsAtomTerm(t2)) {
        Yap_Error(TYPE_ERROR_ATOM, t2, "current_predicate/2");
      }
      ModEntry *m = Yap_GetModuleEntry(t2);
      pp = firstModulePred(m->PredForME, task);
      if (!pp)
        cut_fail();
    }
    npp = firstModulePred(pp, task);

    if (!npp)
      will_cut = true;
    // just try next one
    else {
      EXTRA_CBACK_ARG(4, 1) = MkAddressTerm(npp);
      B->cp_h = HR;
    }
  } else {
    // operating across all modules.
    PredEntry *npp = pp;
    ModEntry *me;
    
    if (!pp) {
      pp = firstModulesPred(CurrentModules->PredForME, CurrentModules, task);
    }
    if (!pp)
      cut_fail();
    if (pp->ModuleOfPred == PROLOG_MODULE)
      me = Yap_GetModuleEntry(TermProlog);
    else
      me = Yap_GetModuleEntry(pp->ModuleOfPred);
    npp = firstModulesPred(pp->NextPredOfModule, me, task);
    if (!npp)
      will_cut = true;
    // just try next module.
    else {
      EXTRA_CBACK_ARG(4, 1) = MkAddressTerm(npp);
      B->cp_h = HR;
    }
  }

  if (pp->ModuleOfPred != IDB_MODULE) {
    f = pp->FunctorOfPred;
    Arity = pp->ArityOfPE;
    if (Arity)
      name = MkAtomTerm(NameOfFunctor(f));
    else
      name = MkAtomTerm((Atom)f);
  } else {
    if (pp->PredFlags & NumberDBPredFlag) {
      name = MkIntegerTerm(pp->src.IndxId);
      Arity = 0;
    } else if (pp->PredFlags & AtomDBPredFlag) {
      f = pp->FunctorOfPred;
      name = MkAtomTerm((Atom)f);
      Arity = 0;
    } else {
      f = pp->FunctorOfPred;
      name = MkAtomTerm(NameOfFunctor(f));
      Arity = ArityOfFunctor(pp->FunctorOfPred);
    }
  }
  if (Arity) {
    rc = Yap_unify(t3, Yap_MkNewApplTerm(f, Arity));
  } else {
    rc = Yap_unify(t3, name);
  }
  rc = rc && Yap_unify(t2, ModToTerm(pp->ModuleOfPred)) && Yap_unify(t1, name);
  if (will_cut) {
    if (rc)
      cut_succeed();
    cut_fail();
  }
  return rc;
}

static Int current_predicate(USES_REGS1) {
  EXTRA_CBACK_ARG(4, 1) = MkAddressTerm(NULL);
  // ensure deref access to choice-point fields.
  return cont_current_predicate(PASS_REGS1);
}

static OpEntry *NextOp(OpEntry *pp USES_REGS) {
  while (!EndOfPAEntr(pp) && pp->KindOfPE != OpProperty &&
         (pp->OpModule != PROLOG_MODULE || pp->OpModule != CurrentModule))
    pp = RepOpProp(pp->NextOfPE);
  return (pp);
}

int Yap_IsOp(Atom at) {
  CACHE_REGS
  OpEntry *op = NextOp(RepOpProp((Prop)(RepAtom(at)->PropsOfAE)) PASS_REGS);
  return (!EndOfPAEntr(op));
}

int Yap_IsOpMaxPrio(Atom at) {
  CACHE_REGS
  OpEntry *op = NextOp(RepOpProp((Prop)(RepAtom(at)->PropsOfAE)) PASS_REGS);
  int max;

  if (EndOfPAEntr(op))
    return 0;
  max = (op->Prefix & 0xfff);
  if ((op->Infix & 0xfff) > max)
    max = op->Infix & 0xfff;
  if ((op->Posfix & 0xfff) > max)
    max = op->Posfix & 0xfff;
  return max;
}

static Int unify_op(OpEntry *op USES_REGS) {
  Term tmod = op->OpModule;

  if (tmod == PROLOG_MODULE)
    tmod = TermProlog;
  return Yap_unify_constant(ARG2, tmod) &&
         Yap_unify_constant(ARG3, MkIntegerTerm(op->Prefix)) &&
         Yap_unify_constant(ARG4, MkIntegerTerm(op->Infix)) &&
         Yap_unify_constant(ARG5, MkIntegerTerm(op->Posfix));
}

static Int cont_current_op(USES_REGS1) {
  OpEntry *op = (OpEntry *)IntegerOfTerm(EXTRA_CBACK_ARG(5, 1)), *next;

  READ_LOCK(op->OpRWLock);
  next = op->OpNext;
  if (Yap_unify_constant(ARG1, MkAtomTerm(op->OpName)) &&
      unify_op(op PASS_REGS)) {
    READ_UNLOCK(op->OpRWLock);
    if (next) {
      EXTRA_CBACK_ARG(5, 1) = (CELL)MkIntegerTerm((CELL)next);
      B->cp_h = HR;
      return TRUE;
    } else {
      cut_succeed();
    }
  } else {
    READ_UNLOCK(op->OpRWLock);
    if (next) {
      EXTRA_CBACK_ARG(5, 1) = (CELL)MkIntegerTerm((CELL)next);
      B->cp_h = HR;
      return FALSE;
    } else {
      cut_fail();
    }
  }
}

static Int init_current_op(
    USES_REGS1) { /* current_op(-Precedence,-Type,-Atom)		 */
  EXTRA_CBACK_ARG(5, 1) = (CELL)MkIntegerTerm((CELL)OpList);
  B->cp_h = HR;
  return cont_current_op(PASS_REGS1);
}

static Int cont_current_atom_op(USES_REGS1) {
  OpEntry *op = (OpEntry *)IntegerOfTerm(EXTRA_CBACK_ARG(5, 1)), *next;

  READ_LOCK(op->OpRWLock);
  next = NextOp(RepOpProp(op->NextOfPE) PASS_REGS);
  if (unify_op(op PASS_REGS)) {
    READ_UNLOCK(op->OpRWLock);
    if (next) {
      EXTRA_CBACK_ARG(5, 1) = (CELL)MkIntegerTerm((CELL)next);
      B->cp_h = HR;
      return TRUE;
    } else {
      cut_succeed();
    }
  } else {
    READ_UNLOCK(op->OpRWLock);
    if (next) {
      EXTRA_CBACK_ARG(5, 1) = (CELL)MkIntegerTerm((CELL)next);
      B->cp_h = HR;
      return FALSE;
    } else {
      cut_fail();
    }
  }
}

static Int init_current_atom_op(
    USES_REGS1) { /* current_op(-Precedence,-Type,-Atom)		 */
  Term t = Deref(ARG1);
  AtomEntry *ae;
  OpEntry *ope;

  if (IsVarTerm(t) || !IsAtomTerm(t)) {
    Yap_Error(TYPE_ERROR_ATOM, t, "current_op/3");
    cut_fail();
  }
  ae = RepAtom(AtomOfTerm(t));
  if (EndOfPAEntr((ope = NextOp(RepOpProp(ae->PropsOfAE) PASS_REGS)))) {
    cut_fail();
  }
  EXTRA_CBACK_ARG(5, 1) = (CELL)MkIntegerTerm((Int)ope);
  B->cp_h = HR;
  return cont_current_atom_op(PASS_REGS1);
}

void Yap_show_statistics(void) {
  CACHE_REGS
  unsigned long int heap_space_taken;
  double frag;

#if USE_SYSTEM_MALLOC && HAVE_MALLINFO
  struct mallinfo mi = mallinfo();

  heap_space_taken = (mi.arena + mi.hblkhd) - Yap_HoleSize;
#else
  heap_space_taken =
      (unsigned long int)(Unsigned(HeapTop) - Unsigned(Yap_HeapBase)) -
      Yap_HoleSize;
#endif
  frag = (100.0 * (heap_space_taken - HeapUsed)) / heap_space_taken;

  fprintf(stderr, "Code Space:  %ld (%ld bytes needed, %ld bytes used, "
                  "fragmentation %.3f%%).\n",
          (unsigned long int)(Unsigned(H0) - Unsigned(Yap_HeapBase)),
          (unsigned long int)(Unsigned(HeapTop) - Unsigned(Yap_HeapBase)),
          (unsigned long int)(HeapUsed), frag);
  fprintf(stderr, "Stack Space: %ld (%ld for Global, %ld for local).\n",
          (unsigned long int)(sizeof(CELL) * (LCL0 - H0)),
          (unsigned long int)(sizeof(CELL) * (HR - H0)),
          (unsigned long int)(sizeof(CELL) * (LCL0 - ASP)));
  fprintf(stderr, "Trail Space: %ld (%ld used).\n",
          (unsigned long int)(sizeof(tr_fr_ptr) * (Unsigned(LOCAL_TrailTop) -
                                                   Unsigned(LOCAL_TrailBase))),
          (unsigned long int)(sizeof(tr_fr_ptr) *
                              (Unsigned(TR) - Unsigned(LOCAL_TrailBase))));
  fprintf(stderr, "Runtime: %lds.\n", (unsigned long int)(runtime(PASS_REGS1)));
  fprintf(stderr, "Cputime: %lds.\n", (unsigned long int)(Yap_cputime()));
  fprintf(stderr, "Walltime: %lds.\n", (unsigned long int)(Yap_walltime()));
}

static Int p_statistics_heap_max(USES_REGS1) {
  Term tmax = MkIntegerTerm(HeapMax);

  return (Yap_unify(tmax, ARG1));
}

/* The results of the next routines are not to be trusted too */
/* much. Basically, any stack shifting will seriously confuse the */
/* results */

static Int TrailTide = -1, LocalTide = -1, GlobalTide = -1;

/* maximum Trail usage */
static Int TrailMax(void) {
  CACHE_REGS
  Int i;
  Int TrWidth = Unsigned(LOCAL_TrailTop) - Unsigned(LOCAL_TrailBase);
  CELL *pt;

  if (TrailTide != TrWidth) {
    pt = (CELL *)TR;
    while (pt + 2 < (CELL *)LOCAL_TrailTop) {
      if (pt[0] == 0 && pt[1] == 0 && pt[2] == 0)
        break;
      else
        pt++;
    }
    if (pt + 2 < (CELL *)LOCAL_TrailTop)
      i = Unsigned(pt) - Unsigned(LOCAL_TrailBase);
    else
      i = TrWidth;
  } else
    return (TrWidth);
  if (TrailTide > i)
    i = TrailTide;
  else
    TrailTide = i;
  return (i);
}

static Int p_statistics_trail_max(USES_REGS1) {
  Term tmax = MkIntegerTerm(TrailMax());

  return (Yap_unify(tmax, ARG1));
}

/* maximum Global usage */
static Int GlobalMax(void) {
  CACHE_REGS
  Int i;
  Int StkWidth = Unsigned(LCL0) - Unsigned(H0);
  CELL *pt;

  if (GlobalTide != StkWidth) {
    pt = HR;
    while (pt + 2 < ASP) {
      if (pt[0] == 0 && pt[1] == 0 && pt[2] == 0)
        break;
      else
        pt++;
    }
    if (pt + 2 < ASP)
      i = Unsigned(pt) - Unsigned(H0);
    else
      /* so that both Local and Global have reached maximum width */
      GlobalTide = LocalTide = i = StkWidth;
  } else
    return (StkWidth);
  if (GlobalTide > i)
    i = GlobalTide;
  else
    GlobalTide = i;
  return (i);
}

static Int p_statistics_global_max(USES_REGS1) {
  Term tmax = MkIntegerTerm(GlobalMax());

  return (Yap_unify(tmax, ARG1));
}

static Int LocalMax(void) {
  CACHE_REGS
  Int i;
  Int StkWidth = Unsigned(LCL0) - Unsigned(H0);
  CELL *pt;

  if (LocalTide != StkWidth) {
    pt = LCL0;
    while (pt - 3 > HR) {
      if (pt[-1] == 0 && pt[-2] == 0 && pt[-3] == 0)
        break;
      else
        --pt;
    }
    if (pt - 3 > HR)
      i = Unsigned(LCL0) - Unsigned(pt);
    else
      /* so that both Local and Global have reached maximum width */
      GlobalTide = LocalTide = i = StkWidth;
  } else
    return (StkWidth);
  if (LocalTide > i)
    i = LocalTide;
  else
    LocalTide = i;
  return (i);
}

static Int p_statistics_local_max(USES_REGS1) {
  Term tmax = MkIntegerTerm(LocalMax());

  return (Yap_unify(tmax, ARG1));
}

static Int p_statistics_heap_info(USES_REGS1) {
  Term tusage = MkIntegerTerm(HeapUsed);

#if USE_SYSTEM_MALLOC && HAVE_MALLINFO
  struct mallinfo mi = mallinfo();

  UInt sstack = Yap_HoleSize + (LOCAL_TrailTop - LOCAL_GlobalBase);
  UInt mmax = (mi.arena + mi.hblkhd);
  Term tmax = MkIntegerTerm(mmax - sstack);
  tusage = MkIntegerTerm(mmax - (mi.fordblks + sstack));
#else
  Term tmax = MkIntegerTerm((LOCAL_GlobalBase - Yap_HeapBase) - Yap_HoleSize);
#endif

  return (Yap_unify(tmax, ARG1) && Yap_unify(tusage, ARG2));
}

static Int p_statistics_stacks_info(USES_REGS1) {
  Term tmax = MkIntegerTerm(Unsigned(LCL0) - Unsigned(H0));
  Term tgusage = MkIntegerTerm(Unsigned(HR) - Unsigned(H0));
  Term tlusage = MkIntegerTerm(Unsigned(LCL0) - Unsigned(ASP));

  return (Yap_unify(tmax, ARG1) && Yap_unify(tgusage, ARG2) &&
          Yap_unify(tlusage, ARG3));
}

static Int p_statistics_trail_info(USES_REGS1) {
  Term tmax =
      MkIntegerTerm(Unsigned(LOCAL_TrailTop) - Unsigned(LOCAL_TrailBase));
  Term tusage = MkIntegerTerm(Unsigned(TR) - Unsigned(LOCAL_TrailBase));

  return (Yap_unify(tmax, ARG1) && Yap_unify(tusage, ARG2));
}

static Int p_statistics_atom_info(USES_REGS1) {
  UInt count = 0, spaceused = 0, i;

  for (i = 0; i < AtomHashTableSize; i++) {
    Atom catom;

    READ_LOCK(HashChain[i].AERWLock);
    catom = HashChain[i].Entry;
    if (catom != NIL) {
      READ_LOCK(RepAtom(catom)->ARWLock);
    }
    READ_UNLOCK(HashChain[i].AERWLock);
    while (catom != NIL) {
      Atom ncatom;
      count++;
      spaceused +=
          sizeof(AtomEntry) + strlen((char *)RepAtom(catom)->StrOfAE) + 1;
      ncatom = RepAtom(catom)->NextOfAE;
      if (ncatom != NIL) {
        READ_LOCK(RepAtom(ncatom)->ARWLock);
      }
      READ_UNLOCK(RepAtom(catom)->ARWLock);
      catom = ncatom;
    }
  }
  for (i = 0; i < WideAtomHashTableSize; i++) {
    Atom catom;

    READ_LOCK(WideHashChain[i].AERWLock);
    catom = WideHashChain[i].Entry;
    if (catom != NIL) {
      READ_LOCK(RepAtom(catom)->ARWLock);
    }
    READ_UNLOCK(WideHashChain[i].AERWLock);
    while (catom != NIL) {
      Atom ncatom;
      count++;
      spaceused +=
          sizeof(AtomEntry) +
          sizeof(wchar_t) * (wcslen((wchar_t *)(RepAtom(catom)->StrOfAE) + 1));
      ncatom = RepAtom(catom)->NextOfAE;
      if (ncatom != NIL) {
        READ_LOCK(RepAtom(ncatom)->ARWLock);
      }
      READ_UNLOCK(RepAtom(catom)->ARWLock);
      catom = ncatom;
    }
  }
  return Yap_unify(ARG1, MkIntegerTerm(count)) &&
         Yap_unify(ARG2, MkIntegerTerm(spaceused));
}

static Int p_statistics_db_size(USES_REGS1) {
  Term t = MkIntegerTerm(Yap_ClauseSpace);
  Term tit = MkIntegerTerm(Yap_IndexSpace_Tree);
  Term tis = MkIntegerTerm(Yap_IndexSpace_SW);
  Term tie = MkIntegerTerm(Yap_IndexSpace_EXT);

  return Yap_unify(t, ARG1) && Yap_unify(tit, ARG2) && Yap_unify(tis, ARG3) &&
         Yap_unify(tie, ARG4);
}

static Int p_statistics_lu_db_size(USES_REGS1) {
  Term t = MkIntegerTerm(Yap_LUClauseSpace);
  Term tit = MkIntegerTerm(Yap_LUIndexSpace_Tree);
  Term tic = MkIntegerTerm(Yap_LUIndexSpace_CP);
  Term tix = MkIntegerTerm(Yap_LUIndexSpace_EXT);
  Term tis = MkIntegerTerm(Yap_LUIndexSpace_SW);

  return Yap_unify(t, ARG1) && Yap_unify(tit, ARG2) && Yap_unify(tic, ARG3) &&
         Yap_unify(tis, ARG4) && Yap_unify(tix, ARG5);
}

static Int p_executable(USES_REGS1) {
  if (GLOBAL_argv && GLOBAL_argv[0])
    Yap_TrueFileName(GLOBAL_argv[0], LOCAL_FileNameBuf, FALSE);
  else
    strncpy(LOCAL_FileNameBuf, Yap_FindExecutable(), YAP_FILENAME_MAX - 1);

  return Yap_unify(MkAtomTerm(Yap_LookupAtom(LOCAL_FileNameBuf)), ARG1);
}

static Int p_system_mode(USES_REGS1) {
  Term t1 = Deref(ARG1);

  if (IsVarTerm(t1)) {
    if (LOCAL_PrologMode & SystemMode)
      return Yap_unify(t1, MkAtomTerm(AtomTrue));
    else
      return Yap_unify(t1, MkAtomTerm(AtomFalse));
  } else {
    Atom at = AtomOfTerm(t1);
    if (at == AtomFalse)
      LOCAL_PrologMode &= ~SystemMode;
    else
      LOCAL_PrologMode |= SystemMode;
  }
  return TRUE;
}

static Int p_lock_system(USES_REGS1) {
  LOCK(GLOBAL_BGL);
  return TRUE;
}

static Int p_unlock_system(USES_REGS1) {
  UNLOCK(GLOBAL_BGL);
  return TRUE;
}

static Int enter_undefp(USES_REGS1) {
  if (LOCAL_DoingUndefp) {
    return FALSE;
  }
  LOCAL_DoingUndefp = TRUE;
  return TRUE;
}

static Int exit_undefp(USES_REGS1) {
  if (LOCAL_DoingUndefp) {
    LOCAL_DoingUndefp = FALSE;
    return TRUE;
  }
  return FALSE;
}

#ifdef DEBUG
extern void DumpActiveGoals(void);

static Int p_dump_active_goals(USES_REGS1) {
  DumpActiveGoals();
  return (TRUE);
}
#endif

#ifdef INES
static Int p_euc_dist(USES_REGS1) {
  Term t1 = Deref(ARG1);
  Term t2 = Deref(ARG2);
  double d1 = (double)(IntegerOfTerm(ArgOfTerm(1, t1)) -
                       IntegerOfTerm(ArgOfTerm(1, t2)));
  double d2 = (double)(IntegerOfTerm(ArgOfTerm(2, t1)) -
                       IntegerOfTerm(ArgOfTerm(2, t2)));
  double d3 = (double)(IntegerOfTerm(ArgOfTerm(3, t1)) -
                       IntegerOfTerm(ArgOfTerm(3, t2)));
  Int result = (Int)sqrt(d1 * d1 + d2 * d2 + d3 * d3);
  return (Yap_unify(ARG3, MkIntegerTerm(result)));
}

volatile int loop_counter = 0;

static Int p_loop(USES_REGS1) {
  while (loop_counter == 0)
    ;
  return (TRUE);
}
#endif

static Int p_break(USES_REGS1) {
  Atom at = AtomOfTerm(Deref(ARG1));
  if (at == AtomTrue) {
    LOCAL_BreakLevel++;
    return TRUE;
  }
  if (at == AtomFalse) {
    LOCAL_BreakLevel--;
    return TRUE;
  }
  return FALSE;
}

void Yap_InitBackCPreds(void) {
  Yap_InitCPredBack("$current_predicate", 4, 1, current_predicate,
                    cont_current_predicate, SafePredFlag | SyncPredFlag);
  Yap_InitCPredBack("$current_op", 5, 1, init_current_op, cont_current_op,
                    SafePredFlag | SyncPredFlag);
  Yap_InitCPredBack("$current_atom_op", 5, 1, init_current_atom_op,
                    cont_current_atom_op, SafePredFlag | SyncPredFlag);
#ifdef BEAM
  Yap_InitCPredBack("eam", 1, 0, start_eam, cont_eam, SafePredFlag);
#endif

  Yap_InitBackAtoms();
  Yap_InitBackIO();
  Yap_InitBackDB();
  Yap_InitUserBacks();
}

typedef void (*Proc)(void);

Proc E_Modules[] = {/* init_fc,*/ (Proc)0};

#ifdef YAPOR
static Int p_parallel_mode(USES_REGS1) { return FALSE; }

static Int p_yapor_workers(USES_REGS1) { return FALSE; }
#endif /* YAPOR */

void Yap_InitCPreds(void) {
  /* numerical comparison */
  Yap_InitCPred("set_value", 2, p_setval, SafePredFlag | SyncPredFlag);
  Yap_InitCPred("get_value", 2, p_value,
                TestPredFlag | SafePredFlag | SyncPredFlag);
  Yap_InitCPred("$values", 3, p_values, SafePredFlag | SyncPredFlag);
  /* general purpose */
  Yap_InitCPred("$opdec", 4, p_opdec, SafePredFlag | SyncPredFlag);
  Yap_InitCPred("=..", 2, p_univ, 0);
  /** @pred  _T_ =..  _L_ is iso


  The list  _L_ is built with the functor and arguments of the term
  _T_. If  _T_ is instantiated to a variable, then  _L_ must be
  instantiated either to a list whose head is an atom, or to a list
  consisting of just a number.


  */
  Yap_InitCPred("$statistics_trail_max", 1, p_statistics_trail_max,
                SafePredFlag | SyncPredFlag);
  Yap_InitCPred("$statistics_heap_max", 1, p_statistics_heap_max,
                SafePredFlag | SyncPredFlag);
  Yap_InitCPred("$statistics_global_max", 1, p_statistics_global_max,
                SafePredFlag | SyncPredFlag);
  Yap_InitCPred("$statistics_local_max", 1, p_statistics_local_max,
                SafePredFlag | SyncPredFlag);
  Yap_InitCPred("$statistics_heap_info", 2, p_statistics_heap_info,
                SafePredFlag | SyncPredFlag);
  Yap_InitCPred("$statistics_stacks_info", 3, p_statistics_stacks_info,
                SafePredFlag | SyncPredFlag);
  Yap_InitCPred("$statistics_trail_info", 2, p_statistics_trail_info,
                SafePredFlag | SyncPredFlag);
  Yap_InitCPred("$statistics_atom_info", 2, p_statistics_atom_info,
                SafePredFlag | SyncPredFlag);
  Yap_InitCPred("$statistics_db_size", 4, p_statistics_db_size,
                SafePredFlag | SyncPredFlag);
  Yap_InitCPred("$statistics_lu_db_size", 5, p_statistics_lu_db_size,
                SafePredFlag | SyncPredFlag);
  Yap_InitCPred("$executable", 1, p_executable, SafePredFlag);
  Yap_InitCPred("$runtime", 2, p_runtime, SafePredFlag | SyncPredFlag);
  Yap_InitCPred("$cputime", 2, p_cputime, SafePredFlag | SyncPredFlag);
  Yap_InitCPred("$systime", 2, p_systime, SafePredFlag | SyncPredFlag);
  Yap_InitCPred("$walltime", 2, p_walltime, SafePredFlag | SyncPredFlag);
  Yap_InitCPred("$system_mode", 1, p_system_mode, SafePredFlag | SyncPredFlag);
  Yap_InitCPred("abort", 0, p_abort, SyncPredFlag);
  /** @pred  abort


  Abandons the execution of the current goal and returns to top level. All
  break levels (see break/0 below) are terminated. It is mainly
  used during debugging or after a serious execution error, to return to
  the top-level.


  */
  Yap_InitCPred("$break", 1, p_break, SafePredFlag);
#ifdef BEAM
  Yap_InitCPred("@", 0, eager_split, SafePredFlag);
  Yap_InitCPred(":", 0, force_wait, SafePredFlag);
  Yap_InitCPred("/", 0, commit, SafePredFlag);
  Yap_InitCPred("skip_while_var", 1, skip_while_var, SafePredFlag);
  Yap_InitCPred("wait_while_var", 1, wait_while_var, SafePredFlag);
  Yap_InitCPred("eamtime", 0, show_time, SafePredFlag);
  Yap_InitCPred("eam", 0, use_eam, SafePredFlag);
#endif
  Yap_InitCPred("$halt", 1, p_halt, SyncPredFlag);
  Yap_InitCPred("$lock_system", 0, p_lock_system, SafePredFlag);
  Yap_InitCPred("$unlock_system", 0, p_unlock_system, SafePredFlag);
  Yap_InitCPred("$enter_undefp", 0, enter_undefp, SafePredFlag);
  Yap_InitCPred("$exit_undefp", 0, exit_undefp, SafePredFlag);

#ifdef YAP_JIT
  Yap_InitCPred("$jit_init", 1, p_jit, SafePredFlag | SyncPredFlag);
#endif /* YAPOR */
#ifdef INES
  Yap_InitCPred("euc_dist", 3, p_euc_dist, SafePredFlag);
  Yap_InitCPred("loop", 0, p_loop, SafePredFlag);
#endif
#if QSAR
  Yap_InitCPred("in_range", 8, p_in_range, TestPredFlag | SafePredFlag);
  Yap_InitCPred("in_range", 4, p_in_range2, TestPredFlag | SafePredFlag);
#endif
#ifdef DEBUG
  Yap_InitCPred("dump_active_goals", 0, p_dump_active_goals,
                SafePredFlag | SyncPredFlag);
#endif

  Yap_InitArrayPreds();
  Yap_InitAtomPreds();
  Yap_InitBBPreds();
  Yap_InitBigNums();
  Yap_InitCdMgr();
  Yap_InitCmpPreds();
  Yap_InitCoroutPreds();
  Yap_InitDBPreds();
  Yap_InitErrorPreds();
  Yap_InitExecFs();
  Yap_InitGlobals();
  Yap_InitInlines();
  Yap_InitIOPreds();
  Yap_InitExoPreds();
  Yap_InitLoadForeign();
  Yap_InitModulesC();
  Yap_InitSavePreds();
  Yap_InitRange();
  Yap_InitSysPreds();
  Yap_InitUnify();
  Yap_InitQLY();
  Yap_InitQLYR();
  Yap_InitStInfo();
  Yap_udi_init();
  Yap_udi_Interval_init();
  Yap_InitSignalCPreds();
  Yap_InitUserCPreds();
  Yap_InitUtilCPreds();
  Yap_InitSortPreds();
  Yap_InitMaVarCPreds();
#ifdef DEPTH_LIMIT
  Yap_InitItDeepenPreds();
#endif
#ifdef ANALYST
  Yap_InitAnalystPreds();
#endif
  Yap_InitLowLevelTrace();
  Yap_InitEval();
  Yap_InitGrowPreds();
  Yap_InitLowProf();
#if defined(YAPOR) || defined(TABLING)
  Yap_init_optyap_preds();
#endif /* YAPOR || TABLING */
#if YAP_JIT
  Yap_InitCPred("jit", 0, p_jit, SafePredFlag | SyncPredFlag);
#endif
  Yap_InitThreadPreds();
  {
    void (*(*(p)))(void) = E_Modules;
    while (*p)
      (*(*p++))();
  }
#if CAMACHO
  {
    extern void InitForeignPreds(void);

    Yap_InitForeignPreds();
  }
#endif
#if APRIL
  {
    extern void init_ol(void), init_time(void);

    init_ol();
    init_time();
  }
#endif
#if SUPPORT_CONDOR
  init_sys();
  init_random();
  //  init_tries();
  init_regexp();
#endif
}

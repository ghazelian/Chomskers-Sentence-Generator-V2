#include "grammar.h"

static const tag_dictionary grammar1[] = {{S, (const tag[]){NP, VP, 0}},
                                          {NP, (const tag[]){Det, N, 0}},
                                          {VP, (const tag[]){V_intr, 0}},
                                          {0, NULL}};

static const tag_dictionary grammar2[] = {
    {S, (const tag[]){S_finite, Conj_c, S_finite, 0}},
    {S_finite, (const tag[]){NP, VP, 0}},
    {NP, (const tag[]){DP, N, 0}},
    {VP, (const tag[]){V_trans, NP, 0}},
    {DP, (const tag[]){Det, Adj, 0}},
    {0, NULL}};

static const tag_dictionary grammar3[] = {
    {S, (const tag[]){NP_name, VP, 0}},
    {S_finite, (const tag[]){NP, VP_finite, 0}},
    {VP, (const tag[]){V_trans, NP, CP, 0}},
    {NP, (const tag[]){DP, N, 0}},
    {NP_name, (const tag[]){N_name, 0}},
    {DP, (const tag[]){Det, AdjP, 0}},
    {AdjP, (const tag[]){Adv, Adj, 0}},
    {CP, (const tag[]){Conj_c, S_finite, 0}},
    {VP_finite, (const tag[]){V_trans, NP, 0}},
    {0, NULL}};

const tag_dictionary *grammar_list[3] = {grammar1, grammar2, grammar3};
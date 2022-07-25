#pragma once
#include "Supervisors.h"
#include "Competitors.h"


void space(std::string& string , int n);
void PRINT_ALL_SUPERVISORS(Supervisors *supervisor[]);
void SORT_SUPERVISORS(Supervisors *supervisor[]);
void PRINT_ALL_COMPETITORS(Competitors *competitor[]);
void PRINT_ALL_COMPETITORS_ALIVE(Competitors *competitor[]);
void RED_LIGHT_GREEN_LIGHT(Competitors *competitor[]);
void ELIMINATE_TEAM(Competitors **team[]);
void TUG_OF_WAR(Competitors **team[][12]);
void MARBLES(Competitors *competitor1, int rand_num_1, Competitors *competitor2, int rand_num_2);
std::string GENKEN_AUX(int num);
int GENKEN(Competitors *competitor1, int num_1, Competitors *competitor2, int num_2);










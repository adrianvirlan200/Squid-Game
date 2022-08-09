#pragma once
#include "Supervisors.h"
#include "Competitors.h"

//function that splits player randomly in competitors ans supervisors
void ASSIGN_PLAYERS(Supervisors *supervisor[], Competitors *competitor[]);

//aux function used to print all data about players 
void space(std::string& string , int n);

void PRINT_ALL_SUPERVISORS(Supervisors *supervisor[]);

void MERGE_SORT(Supervisors *supervisor[],int const left, int const right);
void MERGE(Supervisors *supervisor[], int const left, int const mid, int const right);

void PRINT_ALL_COMPETITORS_ALIVE(Competitors *competitor[]);

void RED_LIGHT_GREEN_LIGHT(Competitors *competitor[]);

void ELIMINATE_TEAM(Competitors **team[]);
void TUG_OF_WAR(Competitors **team[][12]);

void MARBLES(Competitors *competitor1, int rand_num_1, Competitors *competitor2, int rand_num_2);

std::string GENKEN_AUX(int num);
int GENKEN(Competitors *competitor1, int num_1, Competitors *competitor2, int num_2);










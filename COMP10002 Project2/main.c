/*
COMP10002 Project2
Balloting System
Created by He Xin on 15/10/13.
Copyright (c) 2013 He Xin. All rights reserved.
  
All the candidates are stored in an array, each is numbered according to the position they are in the array. The votes stored in voters are the candidates numbers in the preference order (i.e. the first number is the number of the most-preferred candidate of the voter)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NAMELEN 30

/************ structure declaration ************************************/
typedef struct voter voter_t;

struct voter{
    int *votes;
    int current; /*indicate the current vote that is being considered*/
    voter_t *next;
};

typedef struct{
    voter_t *first_voter;
    voter_t *last_voter;
} voterlist_t;

typedef struct{
    char *name;
    int votesnum;
    voterlist_t voterlist;
} candidate_t;

/************* function headers *************************************************/
void init_cand(candidate_t *cand);
void init_voter(voter_t *voter, int numcan);
int voter_input_processing(int numcan, candidate_t *candidates, voter_t *voter);
void free_voter(voter_t *voter);
void append_voter(voterlist_t *voterlist, voter_t *voter);




/*******************************************************************************/

int main(int argc, const char * argv[])
{
    int numcan, numvoter; /*number of candidates*/
    char *nametemp;
    int i; /*to be used in for loops*/
    
    /*read the numcan and candidates names input from the file, and initialise candidates array*/
    nametemp = malloc(sizeof(char)*NAMELEN + 1);
    scanf("%d", &numcan);
    candidate_t candidates[numcan];
    for (i = 0; i < numcan; i++) {
        init_cand(candidates+i);
        assert(scanf("%s", nametemp));
        candidates[i].name = nametemp;
    }
    
    /*process the votes*/
    numvoter = 0;
    for (i = 1; i!=0;) {
        voter_t voter;
        init_voter(&voter, numcan);
        i = voter_input_processing(numcan, candidates, &voter);
        numvoter += 1;
    }
    numvoter -= 1; /*the last voter is not processed*/
    
    
    
}

/*initialise the candidate struct*/
void init_cand(candidate_t *cand){
    cand->name = NULL;
    cand->votesnum = 0;
    cand->voterlist.first_voter = NULL;
    cand->voterlist.last_voter = NULL;
}


/*initialise the struct for one voter*/
void init_voter(voter_t *voter, int numcan) {
    voter->votes = malloc(sizeof(int)*numcan);
    voter->current = 1;
    voter->next = NULL;
}

/*free the dynamic spaces allocated for a voter*/
void free_voter(voter_t *voter){
    assert(voter != NULL);
    free(voter->votes);
    free(voter->next);
    free(voter);
}

/*process the votes of one voter (i.e. one line of number inputs) and add the voter to the voterlist of some candidate
 return 1 if a voter's votes are successfully processed, and 0 if there is no more vote inputs*/
int voter_input_processing(int numcan, candidate_t *candidates, voter_t *voter){
    int i, p, top_cand;
    
    for (i = 0; i < numcan; i++) {
        if(scanf("%d", &p) != 1){
            free_voter(voter);
            return 0;
        }
        printf("%d\n", p);
        voter->votes[p-1] = i; /*candidate i is voter's the pth preferred, so put at voter.votes[p-1]*/
    }
    
    top_cand = voter->votes[0];
    append_voter(&(candidates[top_cand].voterlist), voter);
    candidates[top_cand].votesnum += 1;
    
    return 1;
}

void append_voter(voterlist_t *voterlist, voter_t *voter){
    assert(voter != NULL);
    if (voterlist->first_voter == NULL) {
        voterlist->first_voter = voterlist->last_voter = voter;
    } else {
        voterlist->last_voter->next = voter;
        voterlist->last_voter = voter;
    }
}
















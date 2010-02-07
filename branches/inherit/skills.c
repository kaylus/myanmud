/**********************************************************
 *                     skills.c                           *
 *  Eventually this will contain formulae for skill       *
 *  decay                                                 *
 *  -Hymael                                               *
 **********************************************************/
/* need a header for skills */
#define NOT_SKILLED -1

mapping skills;           		/* our skills */

void delta_skill(string skill, varargs int val){
	if(!skills) skills = ([]);

	if(!val) val = 1;

	skills[skill] += val;
}

int query_skill(string skill){
	if(!skills) skills = ([]);

	if(!skills[skill]) return NOT_SKILLED;

	return skills[skill];
}

mapping query_skills(){/* full mapping, temporary */
	return copy(skills);
}


/**********************************************************
 *                     wealth.c                           *
 *  This is for those people that delight in moneys       *
 *  -Hymael                                               *
 **********************************************************/
#include <money.h>

mapping wealth;    /* le purse */

int has_purse(){ return 1; } /* we know this object wants to hold cash in a purse */

mapping query_wealth(){ return copy(wealth); }

/* with atomic we just do in a catch and print any messages */
/* may make these accept arrays of coins */
atomic void credit(string coin_type, int amount, varargs int slide){
	if(!wealth) wealth = ([]);

	if(member_array(coin_type, COIN_NAMES) == -1)
		error("That is not money.\n");

	if(amount < 1)
		error("Positive money please.\n");

	wealth[coin_type] += amount;

	/* increment weight */
	if(!slide)
		TO->incr_weight(amount);
}

atomic void debit(string coin_type, int amount, varargs int slide){
	if(!wealth) wealth = ([]);

	if(member_array(coin_type, COIN_NAMES) == -1)
		error("That is not money.\n");

	if(amount < 1)
		error("Positive money please.\n");

	wealth[coin_type] -= amount;

	if(wealth[coin_type] < 0)
		error("Not enough money.\n");

	/* decrement weight */
	if(!slide)
		TO->decr_weight(amount);
}

/***************************
 * this moves from a purse *
 * to destination          *
 * NOTE: with no amount we *
 * assume all              *
 ***************************/
atomic void wealth_move(object dest, string type, varargs int amount, int slide){
	if(!amount){
		if(!wealth || !wealth[type])
			error("You haven't any "+type+" coins.\n");

		amount = wealth[type];
	}
	if(amount < 1)
		error("Illegal to deal in negative moneys.\n");

	debit(type, amount, slide);
	{/***VC***/
		object new_stack;
		new_stack = clone_object("/inherit/coin.c");
		new_stack->set_cointype(type);
		new_stack->set_num_coins(amount);
		new_stack->move(dest, slide);
		if(slide)
			dest->incr_weight(amount);
	}/***END VC***/
}

/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/03/16 12:42:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include    <iostream>
#include    <stdio.h>
#include    "Baraja.h"

/* ===  FUNCTION MAIN ===================================================================*/
int main ( int argc, char *argv[] ){
	Baraja *b = new Baraja();
	b->revolver();
	std::cout << *b;
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

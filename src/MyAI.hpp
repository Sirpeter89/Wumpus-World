// ======================================================================
// FILE:        MyAI.hpp
//
// AUTHOR:      Abdullah Younis
//
// DESCRIPTION: This file contains your agent class, which you will
//              implement. You are responsible for implementing the
//              'getAction' function and any helper methods you feel you
//              need.
//
// NOTES:       - If you are having trouble understanding how the shell
//                works, look at the other parts of the code, as well as
//                the documentation.
//
//              - You are only allowed to make changes to this portion of
//                the code. Any changes to other portions of the code will
//                be lost when the tournament runs your code.
// ======================================================================

#ifndef MYAI_LOCK
#define MYAI_LOCK

#include "Agent.hpp"
#include <stack>

using namespace std;

class MyAI : public Agent
{
public:
	MyAI ( void );
	
	Action getAction
	(
		bool stench,
		bool breeze,
		bool glitter,
		bool bump,
		bool scream
	);
	
	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================
	struct loc
        {
        int X;
        int Y;
        };

	loc predict;
	stack<loc> visited;

        loc point;

        int index;

	int homeCount;

        int turnCount;

        int direction;

	bool firstTurned;

        bool haveTraveled;

        bool safe;

        bool done;
        bool home;
        bool decision;
        bool goldFound;

        bool returned;

        bool backTracked;

	bool exists;

        void newLocation(int face);

	void predLocation(int face);
	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
};

#endif

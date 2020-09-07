// ======================================================================
// FILE:        MyAI.cpp
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

#include "MyAI.hpp"
#include <iostream>

using namespace std;

MyAI::MyAI() : Agent()
{
	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================
	turnCount = 0;

        point.X = 0;
        point.Y = 0;

	predict.X = 0;
	predict.Y = 0;

	homeCount = 0;

        safe = true;

        home = false;
        done = false;
        decision = false;
        goldFound = false;

        returned = false;

        backTracked = false;

        haveTraveled = false;

	firstTurned = false;

	exists = false;

        direction = 1; //1 - Up, 2 - Left, 3 - Down, 4 - Right
	
	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
}
	
Agent::Action MyAI::getAction
(
	bool stench,
	bool breeze,
	bool glitter,
	bool bump,
	bool scream
)

{
	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================
		if(!glitter && !goldFound)
		{
		if( visited.empty() )
			{
			visited.push(point);
			//cout << "pushed :" << point.X << ", " << point.Y << endl;
			}
		else if (visited.top().X == point.X && visited.top().Y == point.Y)
			{
			}
		else	{
			//cout << "pushed :" << point.X << ", " << point.Y << endl;
			visited.push(point);
			}
		}

	predict.X = point.X; //current position
	predict.Y = point.Y; //current position

	if(point.X == 0 && point.Y == 0) //back at origin
                {
                home = true;
                }
        else    {
                home = false;
                }

        if (!breeze && !stench) //See if a spot is considered safe
                {
                safe = true;
                }
        else if (breeze || stench)
                {
                safe = false;
                }

	if (bump) //hit a wall turn left or right.
                {
		visited.pop();		

                if (direction == 1) //reverse arithmetic for move.
                        {
                        point.Y--;
                        }
                else if (direction == 2)
                        {
                        point.X++;
                        }
                else if (direction == 3)
                        {
                        point.Y++;
                        }
                else if (direction == 4)
                        {
                        point.X--;
                        }
                if ( ( rand() % 2 ) == 1 )
                        {
			if(direction != 4)
                                        {
                                        direction++;
                                        }
                        else    	{
                                        direction = 1;
                                        }
                	return TURN_LEFT;
                        }
		else    {
			if(direction != 1)
                                        {
                                        direction--;
                                        }
                        else		{
                                        direction = 4;
                                        }

                	return TURN_RIGHT;
                        }
                }

	if (glitter)
                {
                goldFound = true;
		return GRAB;
		}
	else if(goldFound) // go home based on predictions and old indexes
                {
		predLocation(direction);
		if (home)
			{
			return CLIMB;
			}
		else if(predict.X == visited.top().X && predict.Y == visited.top().Y)	
			{
			//cout << "condition met" << endl;
			newLocation(direction);
			//cout << "to be popped :" << visited.top().X << ", " << visited.top().Y << endl;
			visited.pop();
			return FORWARD;
			}
		else	{
			//cout << "We in where we supposed to be" << endl;
			//cout << "safeZones[index-1].X,Y :" << visited.top().X << ", " << visited.top().Y << endl;
			//cout << "predict.X,Y :" << predict.X << ", " << predict.Y << endl;
			if(direction != 4)
                                        {
                                        direction++;
                                        }
                        else            {
                                        direction = 1;
                                        }
                        return TURN_LEFT;
			}
                }
        else if (haveTraveled && home && !goldFound)//left home already and somehow got back
                {
		if(homeCount < 8)
			{
			homeCount++;
			newLocation(direction);
			return FORWARD;
			}
		else if (goldFound)
			{
			return CLIMB;
			}
		else	{
                	return CLIMB;
			}
                }
        else if(home && !safe && !goldFound) //Leave, starting position too risky.
                {
                return CLIMB;
                }
	else if(home && !done && !goldFound) //First move
                {
                direction = 4; //Facing Right
		
                newLocation(direction);
                haveTraveled = true;
                return FORWARD;
                }
        else if(safe && !home && !backTracked && !goldFound) //if its a safe spot and we left home and we havn't backtracked
                {
                //        if( checkArray(safeZones, point) )
                  //              {
                    //            safeZones[index] = point;
                     //           index++;
                    //           }
                newLocation(direction);
                return FORWARD;
                }
	else if(!safe && !decision && !goldFound)//Testing the waters, and it's not safe, go back and make decision later
                {
                        if(turnCount < 2)
                                {
                                turnCount++;
                                if(direction != 4)
                                        {
                                        direction++;
                                        }
                                else    {
                                        direction = 1;
                                        }
                                return TURN_LEFT;
                                }
                        else    {
                                turnCount = 0;
                                newLocation(direction);
                                backTracked = true;
  				return FORWARD;
                                }
                }
	else if (safe && backTracked && !goldFound) //Just came back after a perception, trying new direction.
                {
                        if(turnCount < 1)
                                {
                                turnCount++;
                                if(direction != 1)
                                        {
                                        direction--;
                                        }
                                else    {
                                        direction = 4;
                                        }
                                return TURN_RIGHT;
                                }
                        else    {
                                turnCount = 0;
                                newLocation(direction);
                                backTracked = false;
                                return FORWARD;
                                }
                } 
	else
                {
		newLocation(direction);
		//cout << "wrong condition met" << endl;
                return FORWARD;
                }
	
	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
}

// ======================================================================
// YOUR CODE BEGINS
//
// ======================================================================
void MyAI::newLocation(int face)
                {
                if ( face == 1) //Go Up
                        {
                        point.Y++;
                        }
                else if (face == 3) //Go Down
                        {
                        point.Y--;
                        }
                else if (face == 2) //Go Left
                        {
                        point.X--;
                        }
                else    { //Go Right
                        point.X++;
                        }
                }

void MyAI::predLocation(int face)
                {
                if ( face == 1) //Go Up
                        {
                        predict.Y++;
                        }
                else if (face == 3) //Go Down
                        {
                        predict.Y--;
                        }
                else if (face == 2) //Go Left
                        {
                        predict.X--;
                        }
                else    { //Go Right
                        predict.X++;
                        }
                }


/*bool MyAI::checkArray(loc arr[], loc check)
                {
                for(int a = 0; a < 50 ; a++)
                        {
                        if( check.X == arr[a].X && check.Y == arr[a].Y)
                                return true;
                        }
                return false;
                } */


// ======================================================================
// YOUR CODE ENDS
// ======================================================================

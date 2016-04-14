#ifndef ORGATE_H
#define ORGATE_H

#include <iostream>   // for using cout
#include "Block.h"
    #include "Input.h"
    #include "Wire.h"

    using namespace std;


class OrGate : public Gate
{
	public:
		OrGate();    // constructor
		~OrGate();   // deconstructor
		virtual int getValue();
		virtual void draw();
		
	private:
		// for drawing:
		short xCoord[10];
		short yCoord[10];
		short numPts;
};


// constructor
OrGate::OrGate()
{
	setIn0(NULL);
	setIn1(NULL);

	numPts = 10;
}

// destructor
OrGate::~OrGate()
{
}


int OrGate::getValue()
{
	int left;
	int right;
	left = getIn0()->getValue();
	right = getIn1()->getValue();
	return (left > 0 || right > 0);
}

void OrGate::draw()
{
	
}

#endif
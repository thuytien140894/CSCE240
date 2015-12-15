#include "TrapezoidMethod.h"

/*****************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'TrapezoidMethod' to approximate the area under the curve of 
 * a function using the Trapezoidal Method.
 *
 * This class has the functions to read data from the standard input,    
 * calculate the approximate numerical integration using the Trapezoidal 
 * Method, and output the formatted results.
 *
 * All arithmetic is done in double precision.
 *
 * Author/copyright: Duncan Buell
 *                   modifications by Tien Ho
 * Date last modified: 03 February 2015
*/

/******************************************************************************
 * Constructor
**/
TrapezoidMethod::TrapezoidMethod()
{
}

/******************************************************************************
 * Destructor
**/
TrapezoidMethod::~TrapezoidMethod()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'computeArea' to perform the Trapezoidal Method.
 * 
 * First, we calculate the width of each subinterval on the interval between
 * the left and right points.  Then we run a loop on the number of trapezoids 
 * to calculate the left and right points and the area of each 
 * trapezoid.  The sum area of all the trapezoids is the approximate area 
 * under the curve of the function.  
 *
 * We also use the Utilities class to output for each trapezoid its left and 
 * right points, area, as well as the most updated sum area.
 *
 * Parameters: none
 *
 * Output: the formatted measurements of the trapezoids
 *
 * Returns: the sum area of all the trapezoids as a double value 
**/
double TrapezoidMethod::computeArea()
{
    double subintervalWidth = 0.0;
    double left_x, left_y, right_x, right_y, areaOfTrap;
    double sumOfTrapArea = 0.0;
    string output;
    
    subintervalWidth = (rightPoint - leftPoint)/numberOfTraps;

    for(int i = 0; i < numberOfTraps; ++i)
    {
        left_x = 0.0; 
        right_x = 0.0;
        left_y = 0.0;
        right_y = 0.0;
        areaOfTrap = 0.0;
        output = "";

        left_x = this->leftPoint + i*subintervalWidth;
        left_y = Function::f(left_x);
        right_x= this->leftPoint + (i+1)*subintervalWidth;
        right_y = Function::f(right_x);
        areaOfTrap = 
            subintervalWidth*(left_y + right_y)/2.0;

        sumOfTrapArea += areaOfTrap;
        
        output += Utils::Format(left_x, 10, 6) +  " ";
        output += Utils::Format(left_y, 10, 6) + " ";
        output += Utils::Format(right_x, 10, 6) +  " ";
        output += Utils::Format(right_y, 10, 6) + " ";
        output += Utils::Format(areaOfTrap, 10, 6) + " ";
        output += Utils::Format(sumOfTrapArea, 10, 6) + "\n";

        cout << output;  
    }

    return sumOfTrapArea;
}

/******************************************************************************
 * Function 'readData' to read data.
 *
 * We read data from a file that has the format of the left point on the first
 * line, the right point on the second line, and the number of trapezoids on 
 * the third line.
 *
 * Parameters: none
 *
 * Output: none
 *
 * Returns: none
**/
void TrapezoidMethod::readData()
{
    cin >> leftPoint;
    cin >> rightPoint;
    cin >> numberOfTraps;
}

/******************************************************************************
 * Function 'toString' to output data.
 *
 * We use the Utilities class to convert numerical values into a string with   
 * the output field of 10 and the precision up to 6 decimal places.
 *
 * Parameters: none
 *
 * Ouput: none
 *
 * Returns: a string that includes the number of trapezoids, the left
 *        and right endpoints, and their corresponding function values.
**/
string TrapezoidMethod::toString()
{
    string output = "";

    output += "Number of Trapezoids:   " +    
               Utils::Format(numberOfTraps,10) + "\n";
    output += "Left endpoint:          " +
               Utils::Format(leftPoint, 10, 6) + "\n"; 
    output += "Function at left point: " + 
              Utils::Format(Function::f(leftPoint), 10, 6) + "\n";
    output += "Right endpoint:         " +
               Utils::Format(this->rightPoint, 10, 6) + "\n";
    output += "Function at right point:" + 
               Utils::Format(Function::f(rightPoint), 10, 6) + "\n";

    return output;
}

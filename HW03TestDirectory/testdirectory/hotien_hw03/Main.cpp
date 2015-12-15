#include "Main.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Homework 3 main program.
 *
 * This program reads a sequence of phone book records and provides for
 * output in two sorted orders.
 *
 * Author: Duncan A. Buell
 * Submitted by: Tien Ho
 * Date last modified: 1 January 2015
**/

int main(int argc, char *argv[])
{
    string dataFileName = "";
    string outFileName = "";
    string logFileName = "";
    ofstream outStream;

    Scanner dataStream;

    DoTheWork doTheWork;

    Utils::CheckArgs(3, argc, argv, "datafilename outfilename logfilename");
    dataFileName = static_cast<string>(argv[1]); 
    outFileName = static_cast<string>(argv[2]);
    logFileName = static_cast<string>(argv[3]);

    Utils::LogFileOpen(logFileName);

    Utils::logStream << "Beginning execution\n";
    Utils::logStream.flush();

    Utils::FileOpen(outStream, outFileName);

    Utils::logStream << "datafile  '" << dataFileName << "'\n";
    Utils::logStream << "outfile '" << outFileName << "'\n";
    Utils::logStream << "logfile '" << logFileName << "'\n";

    dataStream.openFile(dataFileName);
    doTheWork.readData(dataStream);

    outStream << "RAW DATA\n" << doTheWork.toString() << endl;
    outStream.flush();

    outStream << "BY NAME\n" << doTheWork.toStringByName() << endl;
    outStream.flush();

    outStream << "BY NUMBER\n" << doTheWork.toStringByNumber() << endl;
    outStream.flush();

    Utils::FileClose(outStream);

    Utils::logStream << "Ending execution\n";
    Utils::logStream.flush();

    Utils::FileClose(Utils::logStream);

    return 0;
}

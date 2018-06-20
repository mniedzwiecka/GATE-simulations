/**
 *  @copyright Copyright 2018 The J-PET Gate Authors. All rights reserved.
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  @file Run.cc
 */
#include <iostream>
#include "GlobalActorReader.hh"
#include <stdexcept>
#include <fstream>
using namespace std;

/**
Code below is just example - modifie as you wish, but remember to take care of exceptions
*/
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cerr<<"Invalid number of variables. Call e.g. ./gar file_name.root or ./gar file_name"<<std::endl;
    }
    else
    {
      std::ofstream outputFile;
      outputFile.open("ParticleStream.txt");
      
        std::string file_name(argv[1]);

        try
        {
            GlobalActorReader gar;
            if(gar.LoadFile(file_name))
                while(gar.Read())
                {
                    //Your code
		  
// 		  if(gar.GetParticleName() == "O15")        // annihilation abbreviation is "annihil"; Decay
//                        {
//                            std::cout << "Particle PGD Coding: " << gar.GetParticlePGDCoding() << std::endl;
//                            std::cout << "Particle Name: " << gar.GetParticleName() << std::endl;
//                            std::cout << "Event ID: " << gar.GetEventID() << std::endl;
//                            std::cout << "Track ID: " << gar.GetTrackID() << std::endl;
//                            std::cout << "Process Name: " << gar.GetProcessName() << std::endl;
//                            //std::cout << "Energy loss: " << gar.GetEnergyLossDuringProcess() << " keV" << std::endl;
//                            //std::cout << "Volume Name: " << gar.GetVolumeName() << std::endl;
//                        }
                       
                       
                          // std::cout << "Particle PGD Coding: " << gar.GetParticlePGDCoding() << std::endl;
                           outputFile << gar.GetParticleName() << "\t" << gar.GetParentID() << "\t" << gar.GetTrackID() << "\t" << gar.GetProcessName() << "\t" << gar.GetEnergyLossDuringProcess() << std::endl;
                           //std::cout << "Volume Name: " << gar.GetVolumeName() << std::endl;
                       
                }
            else
                std::cerr<<"Loading file failed."<<std::endl;
        }
        catch(const std::logic_error& e )
        {
            std::cerr<<e.what()<<std::endl;
        }
        catch(...)
        {
            std::cerr<<"Udefined exception"<<std::endl;
        }
        outputFile.close();
    }
    return 0;
}


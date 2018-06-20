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
 *  @file Variable.hh
 */
#ifndef VARIABLE_HH
#define VARIABLE_HH
#include "TTree.h"
#include <string>
#include <memory>
#include <stdexcept>
#include<iostream>

/**@About: This class is representation of variable from GateGlobalActor and the basic concept used in GlobalActorReader.
 * Class take care of extracing data from branch and take care of extracting valid data.
 * @Author: Mateusz Bała
 * @Email: bala.mateusz@gmail.com
 * Parameters:
 * @param: T - destination type
 * @param: use_pointer - if T represent number type (int, double, float, etc.) then set always FALSE, otherwise TRUE.
*/
template <class T, bool use_pointer>
class Variable
{
public:
    Variable() 
		{
			pBranch = 0;
			pValue = 0;
		}

    ~Variable()
		{
			if(use_pointer)
				delete pValue;
		}

    /** This function return value of variable, but if variable was not initialized (what mean variable does not exist) this function throw exception.
    */
    T GetValue()
    {
				if(use_pointer)
					return *pValue;
				return Value;
    }
    /** Use this method to attach object of this class to branch.
     * This function try attach to branch - if this is imposble (what means that branch does not exist) this function return false.
     * @param: tree - tree from root file
     * @param: branch_name - name of branch conatining variable
     * @return: return false when branch does not exist, otherwise return true
    */
    bool TryAttachToBranch(TTree** tree, std::string branch_name)
    {

        if((*tree)->FindBranch(branch_name.c_str()) == nullptr)
            return false;

				if(use_pointer)
					(*tree)->SetBranchAddress(branch_name.c_str(), &pValue, &pBranch);
				else
        	(*tree)->SetBranchAddress(branch_name.c_str(), &Value, &pBranch);

        return true;
    }

private:
    T Value;
		T* pValue;
		TBranch* pBranch;
};

#endif // VARIABLE_HH

/*
 * PickableModel.h
 *
 *  Created on: Nov 16, 2014
 *      Author: filip
 */

#ifndef PICKABLEMODEL_H_
#define PICKABLEMODEL_H_

#include <fillwave/Fillwave.h>

using namespace fillwave;

class PickableModel: public models::Model{
private:
   pText mText;
   pEffect mPickedEffect;
   std::string mName;
public:
   PickableModel(std::string name,
                 pText text,
                 Engine* engine,
                 pProgram program,
                 const std::string& shapePath,
                 const std::string& texturePath);
   virtual ~PickableModel();
   void onPicked();
   void onUnpicked();
   };

#endif /* PICKABLEMODEL_H_ */

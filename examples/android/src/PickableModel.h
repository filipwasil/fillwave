/*
 * PickableModel.h
 *
 *  Created on: Nov 16, 2014
 *      Author: filip
 */

#ifndef PICKABLEMODEL_H_
#define PICKABLEMODEL_H_

#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>

using namespace fillwave;
using namespace fillwave::framework;

class PickableModel : public Model {
private:
  pText mText;
  pIEffect mPickedEffect;
  std::string mName;
public:
  PickableModel(std::string name, pText text, Engine *engine, core::Program *program, const std::string &shapePath);

  virtual ~PickableModel();

  void onPicked();

  void onUnpicked();
};

#endif /* PICKABLEMODEL_H_ */

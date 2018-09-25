/*
 * PickableModel.h
 *
 *  Created on: Nov 16, 2014
 *      Author: filip
 */

#ifndef PICKABLEMODEL_H_
#define PICKABLEMODEL_H_

#include <flw/Fillwave.h>
#include <flw/Framework.h>

using namespace flw;
using namespace flw::framework;

class PickableModel : public Model {
private:
  flw::flf::ps<flw::flf::Text> mText;
  pIEffect mPickedEffect;
  std::string mName;
public:
  PickableModel(std::string name, flw::flf::ps<flw::flf::Text> text, Engine *engine, flc::Program *program, const std::string &shapePath);

  virtual ~PickableModel();

  void onPicked();

  void onUnpicked();
};

#endif /* PICKABLEMODEL_H_ */

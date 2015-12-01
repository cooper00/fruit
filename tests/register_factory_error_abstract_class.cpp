// expect-compile-error CannotConstructAbstractClassError<ScalerImpl>|The specified class can.t be constructed because it.s an abstract class.
/*
 * Copyright 2014 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fruit/fruit.h>
#include "test_macros.h"
#include <iostream>

using fruit::Component;
using fruit::Injector;
using fruit::Assisted;
using fruit::createComponent;

struct Annotation {};

class Scaler {
public:
  virtual double scale(double x) = 0;
};

class ScalerImpl : public Scaler {
private:
  double factor;
  
public:
  ScalerImpl(double factor)
    : factor(factor) {
  }

  // Note: here we "forgot" to implement scale() (on purpose, for this test) so ScalerImpl is an abstract class.
};

using ScalerFactory = std::function<std::unique_ptr<Scaler>(double)>;

Component<ScalerFactory> getScalerComponent() {
  return createComponent()
    .bind<Scaler, ScalerImpl>()
    .registerFactory<fruit::Annotated<Annotation, ScalerImpl>(Assisted<double>)>([](double) { return (ScalerImpl*)nullptr; });
}

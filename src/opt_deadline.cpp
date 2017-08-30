/*
Copyright 2017 Biagio Festa <info@biagiofesta.it>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <iostream>
#include "Process.hpp"
#include "CoarseGrain.hpp"
#include "FineGrain.hpp"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage:\n"
              << argv[0] << " DATAFILE CONFIGFILE\n";
    return -1;
  }

  opt_common::Configuration opt_deadline_conf;
  opt_deadline_conf.read_configuration_from_file(argv[2]);

  auto process = Process::create_process(argv[1], argv[2]);
  process.set_total_deadline(2 * process.compute_min_deadline());

  // CoarseGrain coarse_grain;
  // coarse_grain.process(&process, &std::cout);

  FineGrain fine_grain(opt_deadline_conf);
  fine_grain.process(&process, &std::cout);

  return 0;
}

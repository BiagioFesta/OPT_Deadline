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
#include <string>
#include "Algorithm1.hpp"
#include "Algorithm2.hpp"
#include "Process.hpp"

enum class AlgorithmSelection { ALGORITHM_1, ALGORITHM_2, ALGORITHM_12 };

AlgorithmSelection parse_algorithm_selection_from_cmd_line(
    const std::string& cmd_option) {
  if (cmd_option == "-1") {
    return AlgorithmSelection::ALGORITHM_1;
  }
  if (cmd_option == "-2") {
    return AlgorithmSelection::ALGORITHM_2;
  }
  if (cmd_option == "-12") {
    return AlgorithmSelection::ALGORITHM_12;
  }
  THROW_RUNTIME_ERROR("Option '" + cmd_option + "' not recognized");
}

std::string AlgorithmType2String(AlgorithmSelection algorithm_type) {
  switch (algorithm_type) {
    case AlgorithmSelection::ALGORITHM_1:
      return "Algorithm1";
    case AlgorithmSelection::ALGORITHM_2:
      return "Algorithm2";
    default:
      THROW_RUNTIME_ERROR("Algorithm type not recognized");
  }
}

opt_common::TimeInstant parse_total_deadline_process(
    const std::string& deadline_str) {
  try {
    return std::stoul(deadline_str);
  } catch (const std::invalid_argument&) {
    THROW_RUNTIME_ERROR("The deadline value '" + deadline_str +
                        "' cannot be matched into a number");
  }
}

int main(int argc, char* argv[]) {
  if (argc < 5) {
    std::cerr << "Usage:\n"
              << argv[0] << " DATAFILE CONFIGFILE DEADLINE (-1|-2|-12)\n";
    return -1;
  }

  // Create configuration
  opt_common::Configuration opt_deadline_conf;
  opt_deadline_conf.read_configuration_from_file(argv[2]);

  // Create process
  const auto total_deadline = parse_total_deadline_process(argv[3]);
  auto process = Process::create_process(argv[1], argv[2], total_deadline);
  // process.set_total_deadline(2 * process.compute_min_deadline());

  // Parse algorithm type
  const auto algorithm_type = parse_algorithm_selection_from_cmd_line(argv[4]);

  std::cout << "Algorithm selected: " << AlgorithmType2String(algorithm_type)
            << "\n";

  // Launch algorithm class in according to type
  switch (algorithm_type) {
    case AlgorithmSelection::ALGORITHM_1:
      Algorithm1 algorithm1;
      algorithm1.process(opt_deadline_conf, &process, &std::cout);
      break;
    case AlgorithmSelection::ALGORITHM_2:
      Algorithm2 algorithm2;
      algorithm2.process(opt_deadline_conf, &process, &std::cout);
      break;
    case AlgorithmSelection::ALGORITHM_12:
      Algorithm1 algorithm1_2;
      Algorithm2 algorithm2_2;
      algorithm1_2.process(opt_deadline_conf, &process, &std::cout);
      algorithm2_2.process(opt_deadline_conf, &process, &std::cout);
      break;
    default:
      THROW_RUNTIME_ERROR("Algorithm type not recognized");
  }

  return 0;
}

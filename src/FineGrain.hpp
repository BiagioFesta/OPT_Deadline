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

#ifndef __OPT_DEADLINE__FINE_GRAIN__HPP
#define __OPT_DEADLINE__FINE_GRAIN__HPP

#include <ostream>
#include <string>
#include <utility>
#include "Process.hpp"

class FineGrain {
 public:
  using TimeInstant = opt_common::TimeInstant;
  using Application = opt_common::Application;

  void set_optIC_command(std::string opt_cmd) {
    m_optIC_command = std::move(opt_cmd);
  }

  void process(Process* process, std::ostream* log, char* argv[]);

 private:
  std::string m_optIC_command;

  std::string invoke_optIC(const Application& application,
                           const std::string& config_filename) const;

  std::string gen_temporary_input_file(const Application& application) const;

  int get_number_of_cores_from_optIC_output(
      const std::string& optIC_output, const Application& application) const;

  std::string get_extented_path_config_file(const Process& process,
                                            char* argv[]) {
    std::string config_file = process.get_config_filename();
    std::string cmd = argv[0];
    cmd = cmd.substr(0, cmd.find_last_of('/'));
    return cmd + "/" + config_file;
  }

#ifndef __unix__
  // TODO(biagio): this assertion could be erased
  static_assert(false,
                "The class FineGrain is for unix architecture");
#endif
};

#endif  // __OPT_DEADLINE__FINE_GRAIN__HPP

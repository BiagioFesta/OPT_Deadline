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
  using Configuration = opt_common::Configuration;

  FineGrain(const Configuration& configuration);

  /*! It launch FineGrain algorithm
    \param [in, out] process    The process to elaborate
    \param [out] log            The stream where log will be written
    \param [out] result_log     The stream where results will be written
   */
  void process(Process* process, std::ostream* log, std::ostream* result_log);

 private:
  static constexpr const char* DAGSIM_SH = "dagsim.sh";
  static constexpr const char* DEFAULT_TMP = "/tmp";

  std::string m_optIC_command;
  std::string m_dagSim_command;
  std::string m_tmp_directory;

  std::string invoke_optIC(const Application& application,
                           const std::string& config_filename,
                           std::ostream* log) const;

  std::string gen_temporary_input_file(const Application& application) const;

  int get_number_of_cores_from_optIC_output(
      const std::string& optIC_output, const Application& application) const;

  std::string invoke_dagSim(const Application& application,
                            int num_cores_to_evaluate, std::ostream* log) const;

  TimeInstant get_execution_time_from_dagSim_output(
      const std::string& dagsim_result) const;

  std::string create_temporary_lua_file(const std::string& abs_lua_filename,
                                        const int num_cores_to_write) const;

  static std::string generate_random_string(const std::size_t len = 6) {
    static constexpr char alphanum_table[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::string rnd_string;
    rnd_string.reserve(len);

    for (std::size_t i = 0; i < len; ++i) {
      char rnd_char = alphanum_table[rand() % (sizeof(alphanum_table) - 1)];
      rnd_string.push_back(rnd_char);
    }

    return rnd_string;
  }
};

#endif  // __OPT_DEADLINE__FINE_GRAIN__HPP

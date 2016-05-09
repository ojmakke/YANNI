/*
 * commands.h
 *
 *  Created on : Apr 24, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "If you have nothing nice to say, then write more code"
 *      Email  : ojmakke@yahoo.com

This file is part of GNU Nets also known as GNUNets

GNU Nets is free software: you can redistribute it and/or modify
it under the terms of the Affero GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

GNU Nets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Affero
GNU General Public License for more details.

You should have received a copy of the Affero GNU General Public License
along with GNU Nets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INTERPRETER_COMMANDS_H_
#define INTERPRETER_COMMANDS_H_

#include <string>

#include "common.h"
#include "networks/fullhidden.h"
#include "activation/activation.h"
#include "interpreter/parser.h"

NNInfo_uptr classic_network(
    const Parser& parser,
    std::vector<FullHidden<double> *>& nets);

// We need to change the reference, hence *&
NNInfo_uptr use_network(
    const Parser& parser,
    const std::vector<FullHidden<double> *>& nets,
    FullHidden<double>* &current_net);

NNInfo_uptr set_io(
    const Parser& parser,
    const std::vector<FullHidden<double> *>& nets,
    FullHidden<double>* const current_net);

NNInfo_uptr train_network(
    const Parser& parser,
    FullHidden<double>* const current_net);

NNInfo_uptr eval_network(
    const Parser& parser,
    FullHidden<double>* const current_net);

NNInfo_uptr scale_network(
    const Parser& parser,
    FullHidden<double>* const net);

NNInfo_uptr plot_square(
    const Parser& parser,
    FullHidden<double>* const net);

NNInfo_uptr reset_network(
    const Parser& parser,
    FullHidden<double>* const net);

NNInfo_uptr retrain_network(
    const Parser& parser,
    FullHidden<double>* const net);

NNInfo_uptr validate_network(
    const Parser& parser,
    FullHidden<double>* const net);

#endif /* INTERPRETER_COMMANDS_H_ */

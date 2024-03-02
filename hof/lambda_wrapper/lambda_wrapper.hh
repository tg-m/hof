/**
 * @file
 * Copyright (C) 2020-present Tomasz G. Markiewicz (software.tgm@gmail.com)
 *
 * Created on Feb 11, 2020
 *
 */

#ifndef HOF_LAMBDA_WRAPPER_LAMBDA_WRAPPER_HH_
#define HOF_LAMBDA_WRAPPER_LAMBDA_WRAPPER_HH_

#include <utility>


namespace hof {

template<typename Lambda_t>
struct lambda_wrapper : Lambda_t {
    lambda_wrapper(Lambda_t lambda) : Lambda_t(std::move(lambda)) {}
    using Lambda_t::operator();
};

} /* namespace hof */

#endif /* HOF_LAMBDA_WRAPPER_LAMBDA_WRAPPER_HH_ */

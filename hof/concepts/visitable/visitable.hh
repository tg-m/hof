/**
 * @file
 * Copyright (C) 2024-present Tomasz G. Markiewicz (software.tgm@gmail.com)
 *
 * Created on Mar 4, 2024
 *
 */

#ifndef HOF_CONCEPS_VISITABLE_VISITABLE_HH_
#define HOF_CONCEPS_VISITABLE_VISITABLE_HH_


#include <concepts>


namespace hof {

template<typename F, typename T>
concept Visitable = requires(F f, T t) {
    { f(t) };
};

enum class visit_result_t {
    do_end_by_visit,
    do_end_normally,
};

} /* namespace hof */

#endif /* HOF_CONCEPS_VISITABLE_VISITABLE_HH_ */

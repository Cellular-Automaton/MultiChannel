/*
** FF, 2024
** CAMI-Desktop/communication_test/plugin_test/include
** File description:
** test
*/

#pragma once

// #include <WrapperInit.hh>
#include <vector>

namespace Wrapper
{
    std::vector<double> simulate_multi_channel(double *tab_init_1D,
                                            int R,
                                            double kernel_mu,
                                            double kernel_sigma,
                                            double *bs,
                                            double *ms,
                                            double *ss,
                                            double *hs,
                                            double *rs,
                                            int *sources,
                                            int *destinations,
                                            double time,
                                            int width,
                                            int height,
                                            int nb_channel,
                                            int nb_couple,
                                            int *nb_rings);

} // namespace Wrapper

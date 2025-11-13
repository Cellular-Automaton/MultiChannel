/*
** File description:
** main
*/

#include <Plugin/MultiChannel.hh>
#include <Wrapper/WrapperMultiChannel.hh>

std::vector<double> Wrapper::simulate_multi_channel(double *tab_init_1D,
                                            int nb_channel,
                                            int nb_couple,
                                            int *nb_rings,
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
                                            int height)
{
    std::vector<std::vector<std::vector<double>>> tab_init_3d{};
    std::vector<double> return_value{};
    std::vector<std::vector<double>> bs_vec{};
    int idx = 0;
    std::vector<double> ms_vec{};
    std::vector<double> ss_vec{};
    std::vector<double> hs_vec{};
    std::vector<double> rs_vec{};
    std::vector<size_t> sources_vec{};
    std::vector<size_t> destinations_vec{};

    for (size_t k{0}; k < nb_channel; k++) {
        std::vector<std::vector<double>> tmp_2d{};
        for (size_t j{0}; j < height; j++) {
            size_t checkpoint{(j * width) + (k * width * height)};
            std::vector<double> tmp{};
            for (size_t i{0}; i < width; i++) {
                tmp.emplace_back(tab_init_1D[i + checkpoint]);
            }
            tmp_2d.emplace_back(tmp);
            tmp.clear();
        }
        tab_init_3d.emplace_back(tmp_2d);
        tmp_2d.clear();
    }
    for (size_t i{0}; i < nb_couple; i++) {
        std::vector<double> tmp{};
        for (size_t j{0}; j < nb_rings[i]; j++) {
            tmp.emplace_back(bs[j + idx]);
        }
        idx += nb_rings[i];
        bs_vec.emplace_back(tmp);
        tmp.clear();
    }
    for (size_t i{0}; i < nb_couple; i++) {
        ms_vec.emplace_back(ms[i]);
        ss_vec.emplace_back(ss[i]);
        hs_vec.emplace_back(hs[i]);
        rs_vec.emplace_back(rs[i]);
        sources_vec.emplace_back(sources[i]);
        destinations_vec.emplace_back(destinations[i]);
    }

    PLC::MultiChannel multi_channel{tab_init_3d, R, kernel_mu, kernel_sigma, bs_vec, ms_vec, ss_vec, hs_vec, rs_vec, sources_vec, destinations_vec, time};
    multi_channel.run();
    std::vector<std::vector<std::vector<double>>> simult_result{multi_channel.getTab()};
    for (size_t k{0}; k < nb_channel; k++) {
        for (size_t j{0}; j < height; j++) {
            for (size_t i{0}; i < width; i++) {
                return_value.emplace_back(simult_result[k][j][i]);
            }
        }
    }
    return return_value;
}

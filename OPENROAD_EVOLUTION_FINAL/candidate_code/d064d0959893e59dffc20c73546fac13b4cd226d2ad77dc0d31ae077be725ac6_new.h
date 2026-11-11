// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12822168;
  double density_weight = 0.20207034;
  double prefix_weight = 0.17006005;
  double neighborhood_weight = 0.16675529;
  double late_weight = 0.17074992;
  double critical_weight = 0.42135626;
  unsigned budget = 8;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning

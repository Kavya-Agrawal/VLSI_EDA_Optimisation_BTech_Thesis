// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01204363;
  double density_weight = 0.47749037;
  double prefix_weight = 0.28878392;
  double neighborhood_weight = 0.04414127;
  double late_weight = 0.07299377;
  double critical_weight = 0.01993562;
  unsigned budget = 7;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning

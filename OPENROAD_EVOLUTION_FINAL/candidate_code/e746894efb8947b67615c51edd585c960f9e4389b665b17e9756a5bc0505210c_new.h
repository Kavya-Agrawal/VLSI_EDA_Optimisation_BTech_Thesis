// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31918410;
  double density_weight = 0.05457145;
  double prefix_weight = 0.27059043;
  double neighborhood_weight = 0.01457955;
  double late_weight = 0.17014763;
  double critical_weight = 0.19982803;
  unsigned budget = 15;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning

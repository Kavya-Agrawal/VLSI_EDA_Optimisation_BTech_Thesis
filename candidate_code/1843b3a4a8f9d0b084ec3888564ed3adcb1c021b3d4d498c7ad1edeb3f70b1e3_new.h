// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30099784;
  double density_weight = 0.07471950;
  double prefix_weight = 0.14978422;
  double neighborhood_weight = 0.18369475;
  double late_weight = 0.19908529;
  double critical_weight = 0.44449846;
  unsigned budget = 26;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning

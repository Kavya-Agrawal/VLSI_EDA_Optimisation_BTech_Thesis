// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56594994;
  double density_weight = 0.48306983;
  double prefix_weight = 0.35715652;
  double neighborhood_weight = 0.00312207;
  double late_weight = 0.13806198;
  double critical_weight = 0.09670271;
  unsigned budget = 4;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning

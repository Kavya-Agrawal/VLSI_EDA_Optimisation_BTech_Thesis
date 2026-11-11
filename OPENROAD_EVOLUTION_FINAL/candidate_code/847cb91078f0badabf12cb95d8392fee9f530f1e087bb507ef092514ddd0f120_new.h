// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67814521;
  double density_weight = 0.07213135;
  double prefix_weight = 0.02457560;
  double neighborhood_weight = 0.31396101;
  double late_weight = 0.14337057;
  double critical_weight = 0.47430980;
  unsigned budget = 21;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning

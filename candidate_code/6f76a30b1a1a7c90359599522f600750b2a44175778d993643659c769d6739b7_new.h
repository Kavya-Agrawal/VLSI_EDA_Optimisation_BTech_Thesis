// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56348565;
  double density_weight = 0.12656438;
  double prefix_weight = 0.32772577;
  double neighborhood_weight = 0.21896704;
  double late_weight = 0.14442420;
  double critical_weight = 0.45334057;
  unsigned budget = 19;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning

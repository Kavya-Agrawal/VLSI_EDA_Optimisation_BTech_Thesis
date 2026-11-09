// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38473030;
  double density_weight = 0.31006164;
  double prefix_weight = 0.38702640;
  double neighborhood_weight = 0.10778540;
  double late_weight = 0.23466246;
  double critical_weight = 0.38585720;
  unsigned budget = 32;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning

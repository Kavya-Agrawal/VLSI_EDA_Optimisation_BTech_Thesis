// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41297882;
  double density_weight = 0.27381113;
  double prefix_weight = 0.49434055;
  double neighborhood_weight = 0.24205295;
  double late_weight = 0.28060186;
  double critical_weight = 0.04268107;
  unsigned budget = 19;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning

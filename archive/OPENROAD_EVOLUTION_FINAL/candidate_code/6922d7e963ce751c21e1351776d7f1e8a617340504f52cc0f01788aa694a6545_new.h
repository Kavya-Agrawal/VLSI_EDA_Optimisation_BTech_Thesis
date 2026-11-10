// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97302043;
  double density_weight = 0.34930430;
  double prefix_weight = 0.26206675;
  double neighborhood_weight = 0.14364100;
  double late_weight = 0.24478605;
  double critical_weight = 0.43452737;
  unsigned budget = 7;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning

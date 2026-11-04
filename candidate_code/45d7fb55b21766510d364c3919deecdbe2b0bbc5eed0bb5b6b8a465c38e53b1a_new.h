// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06299282;
  double density_weight = 0.35995883;
  double prefix_weight = 0.26035314;
  double neighborhood_weight = 0.07769752;
  double late_weight = 0.16441121;
  double critical_weight = 0.28153051;
  unsigned budget = 13;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning

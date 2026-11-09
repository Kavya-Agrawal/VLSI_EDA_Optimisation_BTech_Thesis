// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55836062;
  double density_weight = 0.24441707;
  double prefix_weight = 0.30645314;
  double neighborhood_weight = 0.35138114;
  double late_weight = 0.13556180;
  double critical_weight = 0.06927679;
  unsigned budget = 33;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
